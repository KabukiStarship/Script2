// Copyright AStarship <https://astarship.net>.
#include "Crabs.hpp"
#if SEAM >= CRABS_OP
#include "Args.h"
#include "Slot.h"
#include "Op.hpp"
#include "Hash.hpp"
#include "BSeq.hpp"
#if SEAM == CRABS_OP
#include "_Debug.h"
#else
#include "_Release.h"
#endif
namespace _ {

Crabs* StdCrabs() {} {
  static IUA room[CRABS_ROOM_BYTES] = {}
  return reinterpret_cast<Crabs*>(PtrUp(room, ACPUCacheLineSize - 1));
}

inline ISC CrabsHeaderBytes(ISC stack_total) {
  return sizeof(Crabs) + 2 * sizeof(void*) * stack_total;
}

inline const Op* CrabsError(Crabs* crabs, ERC error) {
  D_COUT("\nCrabs " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

inline const Op* CrabsError(Crabs* crabs, ERC error, const DTB* header) {
  D_COUT("\nCrabs " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

inline const Op* CrabsError(Crabs* crabs, ERC error, const DTB* header,
                            IUA offset) {
  D_COUT("\nCrabs " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

inline const Op* CrabsError(Crabs* crabs, ERC error, const DTB* header,
                            IUA offset, IUA* address) {
  D_COUT("\nCrabs " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

inline IUA* CrabsBoofer(Crabs* crabs) {
  return TPtr<IUA>(crabs, sizeof(Crabs));
}

inline BIn* CrabsBIn(Crabs* crabs) {
  if (IsError(crabs)) {
    return NILP;
  }
  return TPtr<BIn>(crabs, crabs->header_bytes);
}

inline BOut* CrabsBOut(Crabs* crabs) {
  if (IsError(crabs)) {
    return NILP;
  }
  BIn* bin = CrabsBIn(crabs);
  return TPtr<BOut>(bin, bin->bytes + sizeof(BIn));
}

/* Initializes the Crabs Machine. */
Crabs* CrabsInit(IUW* socket, ISC boofer_bytes, ISC stack_total, Operand* root,
                 IUW* unpacked_boofer, IUW unpacked_bytes, IUD ctxt) {
  if (IsError(socket) || IsError(root) || IsError(unpacked_boofer) || 
    stack_total < Crabs::StackTotalMin || boofer_bytes < Crabs::BooferTotalMin)
  {
    return NILP;
  }
  D_COUT("\nInitializing Stack with stack_total:" << stack_total << " boofer_bytes:" <<
         boofer_bytes);
  Crabs* crabs        = TPtr<Crabs>(socket);
  ISC stack_bytes     = (stack_total - 1) * ISC(2 * sizeof(Operand*));
  ISC bin_bout_bytes  = (boofer_bytes - sizeof(Crabs) - stack_bytes + 1) >> 1;
  D_COUT("\n  bin_bout_bytes:" << bin_bout_bytes);
  crabs->bout_state   = BOutStateDisconnected;
  crabs->bin_state    = BInStateDisconnected;
  crabs->stack_count  = 1;
  crabs->type         = _NIL;
  crabs->stack_total  = stack_total;
  crabs->num_states   = 0;
  crabs->operand      = NILP;
  crabs->bytes_left   = 0;
  //ISC offset          = sizeof (Crabs) + total_stack_size - sizeof (void*);
  //bin_offset          = sizeof (BIn) + total_stack_size + offset;
  crabs->header_bytes = CrabsHeaderBytes(stack_total);
  crabs->hash         = PRIME_LARGEST_IUB;
  crabs->ctxt         = ctxt;
  crabs->result       = NILP;
  crabs->header       = NILP;
  crabs->header_start = NILP;
  crabs->root         = root;
  crabs->args         = NILP;
  IUW* base_ptr = TPtr<IUW>(crabs) + sizeof(Crabs) + stack_total * sizeof(Operand**);
  crabs->slot.Set(base_ptr, unpacked_bytes);
  BInInit(CrabsBIn(crabs), bin_bout_bytes);
  BOutInit(CrabsBOut(crabs), bin_bout_bytes);
  return crabs;
}

// BOL CrabsIsDynamic (Crabs* crabs) {
//    return crabs->type % 2 == 1;
// }

inline IUA* CrabsEndAddress(Crabs* crabs) { return BInEnd(CrabsBIn(crabs)); }

inline const Op* CrabsReset(Crabs* crabs) { return NILP; }

inline IUA CrabsExitState(Crabs* crabs) {
  D_COUT("\nExiting " << TBInStates<CHR>(crabs->bin_state) << 
         " state back to the state:" <<
         TBInStates<CHR>(crabs->last_bin_state) << '.');
  IUA state = crabs->last_bin_state;
  crabs->bin_state = state;
  return state;
}

inline const Op* CrabsSetState(Crabs* crabs, BInState state) {
  if (state == BInStateLocked)
    return CrabsError(crabs, ErrorReadOnly);
  D_COUT("\nEntering " << TBInStates<CHR>(state) << " state:" << state);
  crabs->bin_state = state;
  return NILP;
}

inline const Op* CrabsEnterState(Crabs* crabs, BInState state) {
  // We are guaranteed crabs is not nil at this point.
  // if (IsError(crabs)) {
  //    return  ASCIIError (CrabsBIn (crabs), ErrorImplementation);
  //}
  D_COUT("\nEntering " << TBInStates<CHR>(state) << " state:" << state);
  crabs->last_bin_state = crabs->bin_state;
  crabs->bin_state = state;
  return NILP;
}

inline IUA CrabsStreamBOut(Crabs* crabs) { return BOutStreamByte(CrabsBOut(crabs)); }

const Op* Push(Crabs* crabs, Operand* operand) {
  if (IsError(crabs)) {
    return CrabsError(crabs, ErrorImplementation);
  }
  if (IsError(operand)) {
    return CrabsError(crabs, ErrorInvalidOperand);
  }
  D_COUT("\nPushing " << operand->Star('?', NILP)->name << " onto the stack");
  ISC stack_count = crabs->stack_count;
  if (stack_count >= crabs->stack_total) {
    return CrabsError(crabs, ErrorStackOverflow);
  }
  CrabsStack(crabs)[stack_count - 1] = crabs->operand;
  crabs->operand = operand;
  crabs->stack_count = stack_count + 1;
#if DEBUG_CRABS_EXPR
  CrabsPrintStack(crabs, Print());
#endif
  return NILP;
}

const Op* Pop(Crabs* crabs) {
  ISC stack_count = crabs->stack_count;
  if (stack_count == 0) {  // This should not happen.
    return CrabsError(crabs, ErrorInvalidOperand);
  }
  if (stack_count == 1) {
    // We ever pop off the root.
    CrabsClose(crabs);
    return NILP;
  }
  D_COUT("\nPopping " << OperandName(crabs->operand) << " off the stack.");
  crabs->operand = CrabsStack(crabs)[stack_count - 2];
  crabs->stack_count = stack_count - 1;
#if DEBUG_CRABS_EXPR
  Slot sout = out;
    D_COUT ("\nTop of stack is now "
            << OperandName (crabs->operand) << '.'
            << CrabsPrintStack (crabs, Print ());
#endif
    return NILP;
}
const Op* CrabsScanBIn(Crabs* crabs) {
  if (IsError(crabs)) {
    return CrabsError(crabs, ErrorImplementation);
  }

  DTB type = 0;          //< Current type.
  ISC size = 0,          //< Size of the ring socket.
      space = 0,         //< Space left in the right socket.
      length = 0,        //< Length of the ring socket data.
      bytes_left = 0,    //< Number of bytes left to scan.
      array_type = 0,    //< The type of array.
      shift_bits = 0,    //< Number of bytes left to scan.
      bytes_shift = 0;   //< Number of bits to shift to scan the current AArray.
  IUA bin_state = 0,     //< Current bin FSM state.
      b = 0;             //< Current IUA being verified.
  IUB hash = 0,          //< Expected hash of the B-Sequence.
      found_hash = 0;    //< Found B-Sequence hash.
  ISD timestamp = 0,     //< Last time when the expression ran.
      delta_t = 0;       //< Time delta between the last timestamp.
  const Op* op = 0;      //< Current operation.
  Operand* operand = NILP; //< The operand.
  BIn* bin = 0;          //< BIn.
  IUA* bin_begin = 0,    //< Beginning of the ring socket.
     * bin_start = 0,    //< Start of the ring socket data.
     * bin_stop = 0,     //< Stop of the ring socket data.
     * bin_end = 0,      //< End of the ring socket.
     * slot_begin = 0,   //< The first byte in the Slot.
     * slot_start = 0,   //< Pointer to the write cursor.
     * slot_stop = 0,    //< The last byte of data in the Slot.
     * slot_end = 0;     //< The byte after the last byte ein the Slot.

  slot_begin = crabs->slot.origin;
  slot_start = crabs->slot.origin;
  slot_stop  = crabs->slot.stop;
  slot_end   = crabs->slot.stop;

  const Op* result;  //< Result of the SScan.
  const DTB* header = crabs->header;

  //< Header of the current Op being verified.
  op = NILP;
  //    if (input == NILP) {
  //#if DEBUG_CRABS_EXPR
  //        PrintDebug ("input = nil");
  //#endif
  //        return;
  //    }

  bin_state = crabs->bin_state;  //< This isn't an optimal solution.
  bin = CrabsBIn(crabs);
  size = bin->bytes;
  hash = crabs->hash;
  timestamp = ClockNow();
  delta_t = timestamp - crabs->last_time;

  if (delta_t <= crabs->timeout_us) {
    if (delta_t < 0)  //< Special case for Epoch (rare)
      delta_t *= -1;
  }

  bin_begin = BInOrigin(bin);
  bin_end = bin_begin + size;
  bin_start = bin_begin + bin->origin;
  bin_stop = bin_begin + bin->stop;
  space = (ISC)SlotSpace(bin_start, bin_stop, size);
  length = size - space;
  D_COUT("\n    Scanning Crabs:0x" << Hexf(crabs) << " with length:" << length);
  for (; length != 0; --length) {
    b = *bin_start;
    *slot_start++ = b;
    //D_COUT(Linef('=') << "\n"  << length << ":\'" <<
    //       "\' state:\'" << TBInStates<CHR>(bin_state) << '\'' << Linef(' = '));

    if (++bin_start >= bin_end) bin_start -= size;
    // Process the rest of the bytes in a loop to reduce setup overhead.
    switch (bin_state) {
      case BInStateAddress: {
        hash = HashIUB(b, hash);
        D_COUT("\nhash:0x%x" << Hexf(hash));
        // When verifying an address, there is guaranteed to be an
        // crabs->op set. We are just looking for nil return values
        // from the Do (IUA, Stack*): const Operand* function,
        // pushing Star() on to the Star stack, and looking for
        // the first procedure call.
        //
        if (b == op->pop) {
          Pop(crabs);
          break;
        }
        if (b == op->close) {
          Pop(crabs);
          crabs->bytes_left = 1;
          CrabsSetState(crabs, BInStateVerifyingHash);
          bin_state = BInStateVerifyingHash;
          break;
        }
        operand = crabs->operand;

        op = operand->Star('?', NILP);
        D_COUT("\nCurrent Op is \"" << op->name << "\"");

        op = operand->Star(b, NILP);
        if (op == NILP) {
          // Could be an invalid op or a Star Stack push.
          // I'm not sure what I was doing here with the no-op, maybe
          // trying to save some CPU resources prematurely and
          // sinfully optimizing things that don't need to be
          // optimized.
          // result = crabs->result;
          // if (result == NILP) {
          //    return Result (crabs, ErrorInvalidOperand);
          //}
          // CrabsPushScan (crabs, crabs->operand);
          // Clear the socket and return.
          // CrabsClear (crabs); //< Do I really need to clear?
          // return crabs->result;
          return CrabsForceDisconnect(crabs, ErrorInvalidOperand);
        }
        const DTB* params = op->in;
        IUW num_ops = IUW(params);
        if (num_ops > CrabsParamsMax) {
          // It's an Op.
          // The software implementer pushes the Op on the stack.

          // D_COUT_BSQ ("\nFound Op with params ", params)

          result = CrabsScanHeader(crabs, params);
          if (result) {
            D_COUT("Crabs::Error reading address.");
            return CrabsForceDisconnect(crabs, ErrorImplementation);
          }

          operand = crabs->operand;
          if (IsError(operand)) {
            D_COUT("\nNull operand found!");
            return CrabsForceDisconnect(crabs, ErrorInvalidOperand);
          }
          header = op->in;
          crabs->params_left = *header;
          crabs->header = header;        //< +1 to bypass the number_ of params
          crabs->header_start = header;  //< Used to utf current header.
          CrabsEnterState(crabs, BInStatePackedArgs);
          bin_state = BInStatePackedArgs;
          type = *(++crabs->header);  //< Setup to read first type.
          auto align_mask = ATypeAlignMask(type);
          D_COUT("\nNext AsciiType to scan:\'" <<
                 ATypef(type) << "\'.");
          slot_start = TPtrUp<IUA>(slot_start, (ISC)type);
          break;
        }
        op = operand->Star(b, crabs);
        break;
      }
      case BInStatePackedArgs: {
        // In this state, a procedure has been called to scan on a valid
        // operand. This state is responsible for loading the next
        // header argument and checking for the stop of the procedure
        // call.

        if (crabs->params_left-- == 0) {
          D_COUT("\nBSQ successfully scanned.");

          break;
        }
        hash = HashIUB(b, hash);
        D_COUT("\nhash:" << Hexf(hash));

        // Switch to next state
        if (type <= _ADR) {
          if (type < _ADR) {  // Address type.
            D_COUT("\nScanning address.");
            CrabsError(crabs, ErrorInvalidType);
            CrabsEnterState(crabs, BInStateLocked);
            bin_state = BInStateLocked;
            break;
          }
          CrabsEnterState(crabs, BInStateAddress);
          bin_state = BInStateAddress;
          break;

        } else if (type == STR_) {  // UTF-8/ASCII  type.
          // Read the max number_ of chars off the header.
          bytes_left = *(++crabs->header);
          D_COUT("\nScanning STR with max length " << bytes_left);
          CrabsEnterState(crabs, BInStatePackedUTF8);
          bin_state = BInStatePackedUTF8;
          break;
        } else if (type < _FPD) {  // Plain-old-data type.
          bytes_left = ATypeSizeOfPOD(type);
          D_COUT("\nScanning POD with bytes_left:" << bytes_left);
          if (bytes_left == 1) {
            // No need to enter a state because there is only one
            // IUA to parse and we already have the IUA loaded.
            D_COUT("\nDone scanning without state change  for \""
                   << ATypef(type) << '\"');
            // Setup to read the next type.
            type = *(++crabs->header);
            D_COUT("\nNext AsciiType to scan:\'"
                   << ATypef(type)
                   /*<< "\' with alignment:" << TypeAlign(slot_start, type)*/);
            slot_start = TPtrUp<IUA>(slot_start, ISC(type));
            break;
          }
          CrabsEnterState(crabs, BInStatePackedPOD);
          bin_state = BInStatePackedPOD;
          break;
        } else if (type < _VUI) {  // Varint type.
          D_COUT("\nScanning Varint.");
          bytes_left = ATypeSizeOfPOD(type);
          CrabsEnterState(crabs, BInStatePackedVarint);
          bin_state = BInStatePackedVarint;
          break;
          /*
          } else if (type == STB) { // UTF-16  type.
              #if DEBUG_CRABS_EXPR
              Write ("\nScanning STB.");
              #endif
              if (bytes_left == 1) {
                  crabs->last_byte = b;
                  break;
              }
              // Read the max number_ of chars off the header.
              bytes_left = *crabs->header++ * 2;
              CrabsEnterState (crabs,
                              BIn::UTF16State);
              bin_state = BIn::UTF16State;
              break;
          }
          else if (type == STC) { // UTF-32  type.
              #if DEBUG_CRABS_EXPR
              Write ("\nScanning STC.");
              #endif
              // Read the max number_ of chars off the header.
              bytes_left = *crabs->header++ * 4;
              CrabsEnterState (crabs, BIn::UTF32State);
              bin_state = BIn::UTF32State;*/
        } else {  // It's not a POD type.
          D_COUT("\nScanning AArray.");
          // Multi-dimension arrays are parsed just like any other
          // _OBJ.
          array_type &= 0x3;
          bytes_left = b;
          if (array_type == 0) {
            // We don't need to enter a state here because we
            // already have the bytes. :-)
            bin_state = BInStatePackedPOD;
            break;
          } else if (array_type == 1) {
            bytes_shift = 0;
            shift_bits = 16;
            CrabsEnterState(crabs, BInStatePackedObj);
            bin_state = BInStatePackedObj;
            break;
          } else if (array_type == 2) {
            bytes_shift = 0;
            shift_bits = 32;
            CrabsEnterState(crabs, BInStatePackedObj);
            bin_state = BInStatePackedObj;
            break;
          } else {  //< array_type == 3
            bytes_shift = 0;
            shift_bits = 64;
            CrabsEnterState(crabs, BInStatePackedObj);
            bin_state = BInStatePackedObj;
            break;
          }
        }
        break;
      }
      case BInStatePackedUTF8: {
        if (bytes_left == 0) {
          CrabsError(crabs, ErrorTextOverflow,
                     CPtr<DTB>(crabs->header), 0, bin_start);
          break;
        }
        hash = HashIUB(b, hash);
        D_COUT("\nhash:" << Hexf(hash));
        // Hash IUA.
        // Check if CHA terminated.
        if (b == 0) {
          // Check if there is another argument to scan.
          CrabsExitState(crabs);
          bin_state = BInStatePackedArgs;
          //< We can't go back from _OBJ to POD for Text Types.
          // Setup to read next type.
          type = *(++crabs->header);
          if (crabs->params_left == 0) {
            CrabsSetState(crabs, BInStateAddress);
            bin_state = BInStateAddress;
            break;
          }
          D_COUT("\nNext AsciiType to scan:\'"
                 << ATypef(type)
                 << "\' with alignment:"/* << TypeAlign(slot_start, type)*/);
          slot_start = TPtrUp<IUA>(slot_start, ISC(type));
          break;
        }
        --bytes_left;
        break;
      }
      case BInStatePackedUTF16: {
        hash = HashIUB(b, hash);
        D_COUT("\nhash:0x" << Hexf(hash));
        CrabsExitState(crabs);
        break;
      }
      case BInStatePackedUTF32: {
        hash = HashIUB(b, hash);
        D_COUT("\nhash:0x" << Hexf(hash));
        CrabsExitState(crabs);
        break;
      }
      case BInStatePackedVarint: {
        hash = HashIUB(b, hash);
        D_COUT("\nhash:0x" << Hexf(hash));
        // When verifying a varint, there is a max number_ of bytes for
        // the type (3, 5, or 9) but the varint may be complete before
        // this number_ of bytes. We're just basically counting down and
        // looking for an overflow situation.
        // Hash IUA.

        if (bytes_left == 1) {
          D_COUT("Checking last IUA:");

          // @warning I am not current saving the offset. I'm not
          // sure  what to do here. The header class uses a variadic
          // template, I'm kind of tempted to switch to an ISC
          // type for the headers so I can just use a normal
          // array bracket initializer. The other option is to
          // add 32 to the first IUA.

          if ((b >> 7) != 1) {
            const DTB* header = CPtr<DTB>(crabs->header);

            CrabsEnterState(crabs, BInStateHandlingError);
            return CrabsError(crabs, ErrorVarintOverflow, header, 0,
                              bin_start);
          }

          break;
        }
        if (b > 127) {
          D_COUT("");
          // Setup to read the next type.
          type = *(++header);
          auto align_mask = ATypeAlignMask(type);
          D_COUT(
              "\nDone scanning varint: "
              "\nNext AsciiType to scan:"
              << ATypef(type)
              << " with alignment:"/* << AlignUp(slot_start, align_mask)*/);
          slot_start = TPtrUp<IUA>(slot_start, ISC(type));
        }
        --bytes_left;
        break;
      }
      case BInStatePackedObj: {
        hash = HashIUB(b, hash);
        D_COUT("\nhash:" << Hexf(hash));
        if (bytes_shift >= shift_bits) {
          // Done shifting.
          D_COUT("\nLoading object of size:" << bytes_left);
          CrabsExitState(crabs);
          CrabsEnterState(crabs, BInStatePackedPOD);
          bin_state = BInStatePackedPOD;
          break;
        }
        bytes_left &= ((ISC)b) << bytes_shift;
        shift_bits += 8;
        break;
      }
      case BInStateVerifyingHash: {
        if (crabs->bytes_left != 0) {  // One more IUA to load.
          crabs->last_byte = b;
          crabs->bytes_left = 0;
          break;
        }
        found_hash = b;
        found_hash = found_hash << 8;
        found_hash |= crabs->last_byte;
        if (hash != found_hash) {
          D_COUT("\nError: expecting hash:0x" << Hexf(hash));
          D_COUT(" and found " << Hexf(found_hash));
          return CrabsForceDisconnect(crabs, ErrorInvalidHash);
        }
        hash = PRIME_LARGEST_IUB;  //< Reset hash to largest 16-bit prime.
        D_COUT(
            "\nSuccess reading hash!"
            "\nResetting hash.\n");
        break;
      }
      case BInStateHandlingError: {
        break;
      }
      case BInStateDisconnected: {
        if (b) {
          CrabsSetState(crabs, BInStateHandlingError);
          bin_state = BInStateHandlingError;
        } else {
          CrabsSetState(crabs, BInStateAck);
          bin_state = BInStateAck;
        }
        break;
      }
      case BInStateAck: {
        if (b) {
          CrabsSetState(crabs, BInStateHandlingError);
          bin_state = BInStateHandlingError;
        } else {
          D_COUT("\nResetting hash.");
          hash = TPrimeMaxUnigned<IUB>();  //< Reset hash to largest 16-bit prime.
          crabs->operand = crabs->root;
          crabs->result = NILP;
          bin_state = BInStateAddress;
          CrabsSetState(crabs, BInStateAddress);
          D_COUT("\nRoot scope:\"" << OperandName(crabs->operand) << '\"');
        }
        break;
      }
      case BInStateLocked: {
        D_COUT("Locked");
        break;
      }
      default: {
        hash = HashIUB(b, hash);
        D_COUT("\nhash:" << Hexf(hash));
        // parsing plain-old-data.
        if (bytes_left == 0) {
          D_COUT("... done!");
          CrabsExitState(crabs);
          bin_state = crabs->bin_state;

          // Setup to read the next type.
          type = *(++header);
          auto align_mask = ATypeAlignMask(type);
          D_COUT("\nNext AsciiType to scan:\'" << ATypef(type) <<
                 " align_mask:" << align_mask);
          slot_start = TPtrUp<IUA>(slot_start, align_mask);
          break;
        }
        --bytes_left;
        // b = input->Pull ();
        D_COUT("\nLoading next IUA:" << Hexf(b));
        hash = HashIUB(b, hash);
        *bin_start = b;
        ++bin_start;
        break;
      }
    }
  }
  //
  crabs->hash = hash;
  crabs->bytes_left = bytes_left;
  bin->origin = TDelta<ISC>(bin_begin, bin_start);
  return NILP;
}

inline BOL CrabsContains(Crabs* crabs, void* address) {
  if (address < TPtr<IUW>(crabs)) return false;
  if (address > CrabsEndAddress(crabs)) return false;
  return true;
}

inline const Op* CrabsScanHeader(Crabs* crabs, const DTB* header) {
  if (crabs->stack_count >= crabs->stack_total) {
    // Handle overflow cleanup:
    return CrabsError(crabs, ErrorStackOverflow, header);
  }

  return 0;
}

inline const ISC* CrabsHeaderStack(Crabs* crabs) {
  return TPtr<const ISC>(TPtr<CHA>(crabs) +
                         sizeof(Crabs) + crabs->stack_count);
}

inline void CrabsClose(Crabs* crabs) {
  D_COUT("\nClosing expression.");
  crabs->stack_count = 1;
}

inline void CrabsCancel(Crabs* crabs) {
  D_COUT("\nCanceling expression.");
  crabs->stack_count = 1;
  crabs->bin_state = BInStateAddress;
  // CrabsPush (crabs->root);
}

inline void CrabsClear(Crabs* crabs) {
  // Erase the socket by writing zeros to it.

  BIn* bin = CrabsBIn(crabs);

  IUA *begin = BInOrigin(bin),
      *end = begin + bin->bytes,
      *origin = begin + bin->origin,
      *stop = begin + bin->stop;

  // ISC boofer_space = SlotSpace (origin, stop, size);

  if (begin == end) return;  //< Nothing to do.
  if (begin > end) {
    ArrayFill(begin, end - begin);
    ArrayFill(begin, begin - begin);
    return;
  }
  ArrayFill(begin, end - begin);
  bin->origin = TDelta< ISC>(crabs, begin);
  bin->stop = TDelta<ISC>(crabs, begin + 1);
}

inline void CrabsRingBell(Crabs* crabs, const CHA* address) {
  BOutRingBell(CrabsBOut(crabs), address);
}

inline void CrabsAckBack(Crabs* crabs, const CHA* address) {
  BOutAckBack(CrabsBOut(crabs), address);
}

inline const Op* CrabsForceDisconnect(Crabs* crabs, ERC error) {
  crabs->bin_state = BInStateDisconnected;
  return CrabsError(crabs, error);
}

/* Reads the Crabs args from the crabs->slot.
inline const Op* CrabsArgs (Crabs* crabs, const ISC* params, void** args) {
   const CHA* cursor = ArgsParse (crabs->args_cursor, crabs->args_end,
                                   params, args);
   if (IsError(cursor)) {
   }
}*/

inline const Op* CrabsArgs(Crabs* crabs, const DTB* params, void** args) {
  A_ASSERT(params);
  A_ASSERT(args);
  Slot slot(CrabsBIn(crabs));
  return slot.Read(params, args);
}

inline const Op* CrabsArgs(Crabs* crabs, const Op& op, void** args) {
  A_ASSERT(crabs);
  A_ASSERT(args);
  Slot slot(CrabsBIn(crabs));
  return slot.Read(op.in, args);
}

inline const Op* CrabsResult(Crabs* crabs, const DTB* params, void** args, 
  IUD pc_ctx) {
  if (IsError(params) || IsError(args)) {
    return NILP;
  }
  return BOutWrite(CrabsBOut(crabs), params, args, pc_ctx);
}

inline const Op* CrabsResult(Crabs* crabs, const Op* op, void** args,
  IUD pc_ctx) {
  if (IsError(op) || IsError(args)) {
    return NILP;
  }
  return BOutWrite(CrabsBOut(crabs), op->out, args, pc_ctx);
}

inline const Op* CrabsResult(Crabs* crabs, const Op& op, void** args, 
                             IUD pc_ctx) {
  if (IsError(&args)) {
    return NILP;
  }
  return BOutWrite(CrabsBOut(crabs), op.out, args, pc_ctx);
}

const Op* CrabsQuery(Crabs* crabs, const Op* op, IUD pc_ctx) {
    if (IsError(op)) return op;

    if (IsError(op)) {
        return CrabsError(crabs, ErrorImplementation);
    }
    void* args[2];
    return BOutWrite(CrabsBOut(crabs),
        TTSQ<STR_, CrabsOpNameLengthMax, _VUI, _VUI, _STR,
        CrabsOpDescriptionLengthMax>(),
        Args(args, op->name, op->in, op->out, op->description),
        crabs->ctxt);
}

const Op* CrabsQuery(Crabs* crabs, const Op& op, IUD pc_ctx) {
    if (crabs) {
        void* args[2];
        IUW num_ops = (IUW)op.in, first_op = (IUW)op.out;
        // @todo Write params to crabs!
        static const DTB* header =
            TTSQ<STR_, CrabsOpNameLengthMax, _VUI, _VUI, _STR,
            CrabsOpDescriptionLengthMax>();
        return BOutWrite(CrabsBOut(crabs), header,
            Args(args, op.name, &num_ops, &first_op, op.description),
            pc_ctx);
    }
    return &op;
}

inline IUA* CrabsBaseAddress(BIn* bin) {
  return TPtr<IUA>(bin) + sizeof(BIn);
}

ISW CrabsSpace(BIn* bin) {
  if (IsError(bin)) {
    return ~0;
  }

  IUA* origin = CrabsBaseAddress(bin);
  return ISW(SlotSpace(origin + bin->origin, origin + bin->stop, bin->bytes));
}

IUW* CrabsBaseAddress(void* ptr, ISC rx_tx_offset) {
  enum {
    SlotHeaderSize = sizeof(BIn) + sizeof(IUW) - sizeof(BIn) % sizeof(IUW),
    //< Offset to the origin of the ring socket.
  };
  CHA* result = TPtr<CHA>(ptr) + rx_tx_offset + SlotHeaderSize;
  return TPtr<IUW>(result);
}

CHA* CrabsEndAddress(BIn* bin) {
  return TPtr<CHA>(bin) + sizeof(BIn) + bin->bytes;
}

}  //< namespace _

#endif
