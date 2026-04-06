// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_PROMISE_HXX
#define CRABS_PROMISE_HXX
#include "Promise.h"
#if SEAM >= CRABS_OP
namespace _ {

/* Gets the promise state from a Slot.
@param slot The promise Slot.
@return Returns the state (0=pending, 1=fulfilled, 2=rejected). */
inline IUW PromiseState(Slot* slot) {
  if (!slot || !slot->IsReadable())
    return PromisePending;

  void* args[5];
  TMC* timestamp = TPtr<TMC>(&args[0]);
  IUW* state = TPtr<IUW>(&args[1]);
  void** result = TPtr<void*>(&args[2]);
  CHA** fulfilledKey = TPtr<CHA*>(&args[3]);
  CHA** rejectedKey = TPtr<CHA*>(&args[4]);

  static const DTB params[] = { 5, _TMC, _IUW, _PMS, _CHA, _CHA };
  const Op* op = slot->Read(params, args);
  if (op)
    return PromisePending;
  return *state;
}

/* Checks if promise is in pending state. */
inline BOL PromiseIsPending(Slot* slot) {
  return PromiseState(slot) == PromisePending;
}

/* Checks if promise is fulfilled. */
inline BOL PromiseIsFulfilled(Slot* slot) {
  return PromiseState(slot) == PromiseFulfilled;
}

/* Checks if promise is rejected. */
inline BOL PromiseIsRejected(Slot* slot) {
  return PromiseState(slot) == PromiseRejected;
}

/* Gets the resolution timestamp from a promise.
@param slot The promise Slot.
@return Returns the TMC timestamp. */
inline TMC PromiseTimestamp(Slot* slot) {
  if (!slot || !slot->IsReadable())
    return 0;
  void* args[5];
  TMC* timestamp = TPtr<TMC>(&args[0]);
  IUW* state = TPtr<IUW>(&args[1]);

  static const DTB params[] = { 5, _TMC, _IUW, _PMS, _CHA, _CHA };
  const Op* op = slot->Read(params, args);
  if (op)
    return 0;
  return *timestamp;
}

/* Sets the promise state and records the result.
@param slot The promise Slot.
@param newState The new state (1=fulfilled, 2=rejected).
@param result Pointer to the result data.
@param header BSeq header for the result type.
@return Returns nil upon success or an Error Op upon failure. */
inline const Op* PromiseSetResult(Slot* slot, IUW newState, void* result,
  const DTB* header) {
  if (!slot || !result || !header)
    return OpError(AErrorNil);
  if (newState != PromiseFulfilled && newState != PromiseRejected)
    return OpError(AErrorInvalid);

  Slot& target = *slot;
  target.Clear();

  IUD pcCtx = 0;
  const Op* op = NILP; // BOutConnect(target.bout, "", pcCtx);
  if (op) return op;

  void* args[5];
  TMC* timestamp = TPtr<TMC>(&args[0]);
  IUW* state = TPtr<IUW>(&args[1]);
  void** resultPtr = TPtr<void*>(&args[2]);
  CHA** fulfilledKey = TPtr<CHA*>(&args[3]);
  CHA** rejectedKey = TPtr<CHA*>(&args[4]);

  *timestamp = StdCrabs()->epoch;
  *state = newState;
  *resultPtr = result;
  *fulfilledKey = NILP;
  *rejectedKey = NILP;

  static const DTB outParams[] = { 5, _TMC, _IUW, _PMS, _CHA, _CHA };
  return NILP; // BOutWrite(target.bout, outParams, args, pcCtx);
}

/* Triggers fulfillment callbacks by writing result to output BOut. */
inline const Op* PromiseTriggerFulfillment(Crabs* crabs, Slot* promise_slot) {
  if (IsError(crabs) || !promise_slot) return OpError(AErrorNil);
  if (!PromiseIsFulfilled(promise_slot))
    return OpError(AErrorInvalid);

  // Write result to the Crabs' BOut for execution
  return CrabsWritePromiseResult(CrabsBOut(crabs), promise_slot);
}

/* Triggers rejection handlers. */
inline const Op* PromiseTriggerRejection(Crabs* crabs, Slot* promise_slot) {
  if (IsError(crabs) || !promise_slot)
    return OpError(AErrorNil);
  if (!PromiseIsRejected(promise_slot))
    return OpError(AErrorInvalid);

  // Write error to  Crabs BOut for handler execution
  return CrabsWritePromiseResult(CrabsBOut(crabs), promise_slot);
}

/* Creates a new promise context.
@param crabs The Crabs machine.
@param timestamp Unix epoch (TMC) for when promise was created.
@return Returns a pointer to the newly created promise Slot, or nil on error. */
inline Slot* CrabsCreatePromise(Crabs* crabs, TMC timestamp) {
  if (IsError(crabs))
    return NILP;
  Slot& slot = crabs->slot;
  slot.Clear();
  void* args[5];
  *TPtr<TMC>  (&args[0]) = timestamp;
  *TPtr<IUW>  (&args[1]) = PromisePending;
	*TPtr<void*>(&args[2]) = NILP;  //< Result pointer
	*TPtr<CHA*> (&args[3]) = NILP;   //< Fulfillment callback key
  *TPtr<CHA*> (&args[4]) = NILP;   //< Rejected
  
  static const DTB params[] = { 5, _TMC, _IUW, _PMS, _CHA, _CHA };
  IUD pcCtx = 0;
  const Op* op = slot.Write(params, args);
  if (op)
    return NILP; 
  return &crabs->slot;
}

/* Resolves a promise with a value.
@param crabs The Crabs machine.
@param promise_slot The promise Slot to resolve.
@param value Pointer to the result value.
@return Returns nil upon success or an Error Op upon failure. */
inline const Op* CrabsResolvePromise(Crabs* crabs, Slot* promise_slot, void* value) {
  if (IsError(crabs) || !promise_slot || !value) return OpError(AErrorNil);
  
  return PromiseSetResult(promise_slot, PromiseFulfilled, value, NILP);
}

/* Rejects a promise with an error reason.
@param crabs The Crabs machine.
@param promise_slot The promise Slot to reject.
@param error Pointer to the error reason.
@return Returns nil upon success or an Error Op upon failure. */
inline const Op* CrabsRejectPromise(Crabs* crabs, Slot* promise_slot, void* error) {
  if (IsError(crabs) || !promise_slot || !error)
    return OpError(AErrorNil);
  return PromiseSetResult(promise_slot, PromiseRejected, error, NILP);
}

/* Attaches a fulfillment handler to a promise (.then()).
@param crabs The Crabs machine.
@param promise_slot The promise Slot.
@param onFulfilledKey The key for the fulfillment callback operand.
@return Returns nil upon success or an Error Op upon failure. */
inline const Op* CrabsThenPromise(Crabs* crabs, Slot* promise_slot, CHA* onFulfilledKey) {
  if (IsError(crabs) || !promise_slot)
    return OpError(AErrorNil);
  void* args[5];
  TMC* timestamp = TPtr<TMC>(&args[0]);
  IUW* state = TPtr<IUW>(&args[1]);
  void** result = TPtr<void*>(&args[2]);
  CHA** fulfilledKey = TPtr<CHA*>(&args[3]);
  CHA** rejectedKey = TPtr<CHA*>(&args[4]);
  
  static const DTB ReadParams[] = { 5, _TMC, _IUW, _PMS, _CHA, _CHA };
  const Op* op = promise_slot->Read(ReadParams, args);
  if (op) return op;
  
  *fulfilledKey = onFulfilledKey;
  
  IUD pcCtx = 0;
  static const DTB WriteParams[] = { 5, _TMC, _IUW, _PMS, _CHA, _CHA };
  return promise_slot->Write(WriteParams, args);
}

/* Attaches a rejection handler to a promise (.catch()).
@param crabs The Crabs machine.
@param promise_slot The promise Slot.
@param on_rejected_key The key for the rejection callback operand.
@return Returns nil upon success or an Error Op upon failure. */
inline const Op* CrabsCatchPromise(Crabs* crabs, Slot* promise_slot, CHA* on_rejected_key) {
  if (IsError(crabs) || !promise_slot)
    return OpError(AErrorNil);
  void* args[5];
  TMC* timestamp = TPtr<TMC>(&args[0]);
  IUW* state = TPtr<IUW>(&args[1]);
  void** result = TPtr<void*>(&args[2]);
  CHA** fulfilledKey = TPtr<CHA*>(&args[3]);
  CHA** rejectedKey = TPtr<CHA*>(&args[4]);
  
  static const DTB readParams[] = { 5, _TMC, _IUW, _PMS, _CHA, _CHA };
  const Op* op = promise_slot->Read(readParams, args);
  if (op) return op;
  
  *rejectedKey = on_rejected_key;
  
  IUD pcCtx = 0;
  static const DTB writeParams[] = { 5, _TMC, _IUW, _PMS, _CHA, _CHA };
  return promise_slot->Write(writeParams, args);
}

/* Reads a promise from a BIn socket.
@param bin The BIn socket to read from.
@return Returns the promise state word (0=pending, 1=fulfilled, 2=rejected). */
inline IUW CrabsReadPromiseState(BIn* bin) {
  if (!bin) return PromisePending;
  
  void* args[5];
  TMC* timestamp = TPtr<TMC>(&args[0]);
  IUW* state = TPtr<IUW>(&args[1]);
  
  static const DTB readParams[] = { 5, _TMC, _IUW, _PMS, _CHA, _CHA };
  const Op* op = BInRead(bin, readParams, args, 0);
  if (op) return PromisePending;
  
  return *state;
}

/* Writes a promise result to a BOut socket.
@param bout The BOut socket to write to.
@param promise_slot The promise Slot containing the result.
@return Returns nil upon success or an Error Op upon failure. */
inline const Op* CrabsWritePromiseResult(BOut* bout, Slot* promise_slot) {
  if (!bout || !promise_slot) return OpError(AErrorNil);
  
  void* args[5];
  TMC* timestamp = TPtr<TMC>(&args[0]);
  IUW* state = TPtr<IUW>(&args[1]);
  void** result = TPtr<void*>(&args[2]);
  
  static const DTB readParams[] = { 5, _TMC, _IUW, _PMS, _CHA, _CHA };
  const Op* op = promise_slot->Read(readParams, args);
  if (op) return op;
  
  IUD pcCtx = 0;
  static const DTB writeParams[] = { 3, _TMC, _IUW, _PMS };
  return BOutWrite(bout, writeParams, args, pcCtx);
}

}  //< namespace _

#endif
#endif
