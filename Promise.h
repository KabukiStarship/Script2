// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_PROMISE_DECL
#define CRABS_PROMISE_DECL
#include <_Config.h>
#if SEAM >= CRABS_OP
namespace _ {

struct BIn;
struct BOut;
struct Crabs;
struct Op;
struct Slot;

// @module Promise
enum {
  PromisePending = 0,
  PromiseFulfilled = 1,
  PromiseRejected = 2
};
IUW PromiseState(Slot* slot);
BOL PromiseIsPending(Slot* slot);
BOL PromiseIsFulfilled(Slot* slot);
BOL PromiseIsRejected(Slot* slot);
TMC PromiseTimestamp(Slot* slot);
const Op* PromiseSetResult(Slot* slot, IUW newState, void* result, const DTB* header);
const Op* PromiseTriggerFulfillment(Crabs* crabs, Slot* promiseSlot);
const Op* PromiseTriggerRejection(Crabs* crabs, Slot* promiseSlot);
// @endmodule

}  //< namespace _

#endif
#endif
