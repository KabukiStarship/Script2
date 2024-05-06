/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Crabs.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "Crabs.h"
#include "BSeq.h"
#include "Clock.h"
#include "Test.h"
#if SEAM == SCRIPT2_CRABS
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
namespace _ {

/* Used to return an erroneous result from a B-Input.
@return Returns a Static Error Op Result.
@param error The error type. */
inline const Op* CrabsError(Crabs* crabs, Error error) {
  D_COUT("\nCrabs " << STRError(error) << " Error!");
  return TPtr<const Op>(1);
}

/* Used to return an erroneous result from a B-Input.
@return         Returns a Static Error Op Result.
@param crabs    The source Crabs.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error. */
inline const Op* CrabsError(Crabs* crabs, Error error, const ISC* header) {
  D_COUT("\nCrabs " << STRError(error) << " Error!");
  return TPtr<const Op>(1);
}

/* Used to return an erroneous result from a B-Input.
@return         Returns a Static Error Op Result.
@param crabs    The source Crabs.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error. */
inline const Op* CrabsError(Crabs* crabs, Error error, const ISC* header,
                            IUA offset) {
  D_COUT("\nCrabs " << STRError(error) << " Error!");
  return TPtr<const Op>(1);
}

/* Used to return an erroneous result from a B-Input.
@return         Returns a Static Error Op Result.
@param crabs    The source Crabs.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error. */
inline const Op* CrabsError(Crabs* crabs, Error error, const ISC* header,
                            IUA offset, CHA* address) {
  D_COUT("\nCrabs " << STRError(error) << " Error!");
  return TPtr<const Op>(1);
}

IUW* CrabsBinAddress(Crabs* crabs) {
  if (!crabs) return nullptr;
  return TPtr<IUW>(crabs) + crabs->header_size;
}

CHA* CrabsBuffer(Crabs* crabs) {
  CHA* ptr = TPtr<CHA>(crabs);
  return ptr + sizeof(Crabs);
}

BIn* CrabsBIn(Crabs* crabs) {
  return TPtr<BIn>(CrabsBinAddress(crabs));
}

IUW* CrabsBOutAddress(Crabs* crabs) {
  if (!crabs) {
    return nullptr;
  }
  return TPtr<IUW>(crabs) + crabs->header_size;
}

BOut* CrabsBOut(Crabs* crabs) {
  return TPtr<BOut>(CrabsBOutAddress(crabs));
}

Crabs* CrabsInit(IUW* socket, ISC buffer_size, ISC stack_size, Operand* root,
                 IUW* unpacked_buffer, IUW unpacked_size) {
  if (!socket) {
    return nullptr;
  }
  if (buffer_size < Crabs::cMinBufferSize) {
    return nullptr;
  }
  if (stack_size < cMinStaccSize) {
    stack_size = cMinStaccSize;  //< Minimum stack size.
  }
  if (unpacked_buffer == nullptr) {
    D_COUT("\nError: unpacked_buffer was nil!");
  }

  if (root == nullptr) {
    D_COUT("\nError: root can't be nil.");
    return nullptr;
  }

  Crabs* crabs = TPtr<Crabs>(socket);

  ISC total_stack_size = (stack_size - 1) * (2 * sizeof(Operand*));
  // Calculate the size of the Slot and Stack.
  ISC size = (buffer_size - sizeof(Crabs) - total_stack_size + 1) >> 1;

  //< >>1 to divide by 2
  crabs->bout_state = cBOutStateDisconnected;
  crabs->bin_state = cBInStateDisconnected;
  crabs->stack_count = 1;
  crabs->type = cNIL;
  crabs->stack_size = stack_size;
  crabs->num_states = 0;
  crabs->operand = nullptr;
  D_COUT("\nInitializing Stack with size:" << stack_size << " buffer_size:"
                                           << buffer_size << " size:" << size);
  crabs->bytes_left = 0;
  // ISC offset    = sizeof (Crabs) + total_stack_size - sizeof (void*);
  // bin_offset       = sizeof (BIn) + total_stack_size + offset;
  crabs->header_size = sizeof(Crabs) + 2 * sizeof(void*) * stack_size;
  crabs->hash = PRIME_LARGEST_IUB;
  crabs->result = nullptr;
  crabs->header = nullptr;
  crabs->header_start = nullptr;
  crabs->root = root;
  IUW* base_ptr = TPtr<IUW>(crabs) + sizeof(Crabs) + stack_size * sizeof(ISC);
  crabs->slot.Set(base_ptr, unpacked_size);
  D_COUT("crabs->op:0x" << Hexf(crabs->operand));
  BInInit(CrabsBinAddress(crabs), size);
  BOutInit(CrabsBOutAddress(crabs), size);
  return crabs;
}

// BOL CrabsIsDynamic (Crabs* crabs) {
//    return crabs->type % 2 == 1;
//}

CHA* CrabsEndAddress(Crabs* crabs) { return BInEnd(CrabsBIn(crabs)); }

const Op* CrabsReset(Crabs* crabs) { return 0; }

IUA CrabsExitState(Crabs* crabs) {
  // We are guaranteed crabs is not nil at this point.
  // if (!crabs) {
  //    return  CrabsError (CrabsBIn (crabs), cErrorImplementation);
  //}
  D_COUT("\nExiting " << STRBInStates()[crabs->bin_state]
                      << " state back to the state:"
                      << STRBInStates()[crabs->last_bin_state] << '.');
  IUA state = crabs->last_bin_state;
  crabs->bin_state = state;
  return state;
}

const Op* CrabsSetState(Crabs* crabs, BInState state) {
  // We are guaranteed crabs is not nil at this point.
  // if (!crabs) {
  //    return  CrabsError (CrabsBIn (crabs), cErrorImplementation);
  //}
  if (state == cBInStateLocked) {
    return CrabsError(crabs, cErrorObjLocked);
  }
  D_COUT("\nEntering " << BInState[state] << " state:" << state);
  crabs->bin_state = state;
  return nullptr;
}

const Op* CrabsEnterState(Crabs* crabs, BInState state) {
  // We are guaranteed crabs is not nil at this point.
  // if (!crabs) {
  //    return  CrabsError (CrabsBIn (crabs), cErrorImplementation);
  //}
  D_COUT("\nEntering " << BInState()[state] << " state:" << state);
  crabs->last_bin_state = crabs->bin_state;
  crabs->bin_state = state;
  return nullptr;
}

IUA CrabsStreamBOut(Crabs* crabs) { return BOutStreamByte(CrabsBOut(crabs)); }

const Op* Push(Crabs* crabs, Operand* operand) {
  if (!crabs) {
    return CrabsError(crabs, cErrorImplementation);
  }
  if (!operand) {
    return CrabsError(crabs, cErrorInvalidOperand);
  }
  D_COUT("\nPushing " << operand->Star('?', nullptr)->name
                      << " onto the stack");
  ISC stack_count = crabs->stack_count;
  if (stack_count >= crabs->stack_size) {
    return CrabsError(crabs, cErrorStackOverflow);
  }
  CrabsStack(crabs)[stack_count - 1] = crabs->operand;
  crabs->operand = operand;
  crabs->stack_count = stack_count + 1;
#if DEBUG_SCRIPT2_EXPR
  CrabsPrintStack(crabs, Print());
#endif
  return nullptr;
}

const Op* Pop(Crabs* crabs) {
  ISC stack_count = crabs->stack_count;
  if (stack_count == 0) {  // This should not happen.
    return CrabsError(crabs, cErrorInvalidOperand);
  }
  if (stack_count == 1) {
    // We ever pop off the root.
    CrabsClose(crabs);
    return 0;
  }
  D_COUT("\nPopping " << OperandName(crabs->operand) << " off the stack.");
  crabs->operand = CrabsStack(crabs)[stack_count - 2];
  crabs->stack_count = stack_count - 1;
#if DEBUG_SCRIPT2_EXPR
  Slot sout = out;
    D_COUT ("\nTop of stack is now "
            << OperandName (crabs->operand) << '.'
            << CrabsPrintStack (crabs, Print ());
#endif
    return nullptr;
}

const Op* CrabsScanBIn(Crabs* crabs) {
  if (!crabs) {
    return CrabsError(crabs, cErrorImplementation);
  }

  ISC size,          //< Size of the ring socket.
      space,         //< Space left in the right socket.
      length,        //< Length of the ring socket data.
      type,          //< Current type.
      bytes_left,    //< Number of bytes left to scan.
      array_type,    //< The type of array.
      shift_bits,    //< Number of bytes left to scan.
      bytes_shift;   //< Number of bits to shift to scan the current AArray.
  IUA bin_state,     //< Current bin FSM state.
      b;             //< Current IUA being verified.
  IUB hash,          //< Expected hash of the B-Sequence.
      found_hash;    //< Found B-Sequence hash.
  TMD timestamp,     //< Last time when the expression ran.
      delta_t;       //< Time delta between the last timestamp.
  const Op* op;      //< Current operation.
  Operand* operand;  //< The operand.
  BIn* bin;          //< BIn.
  CHA *bin_begin,    //< Beginning of the ring socket.
      *bin_start,    //< Start of the ring socket data.
      *bin_stop,     //< Stop of the ring socket data.
      *bin_end,      //< End of the ring socket.
      *slot_begin,   //< The first byte in the Slot.
      *slot_start,   //< Pointer to the write cursor.
      *slot_stop,    //< The last byte of data in the Slot.
      *slot_end;     //< The byte after the last byte ein the Slot

  slot_begin = crabs->slot.origin;
  slot_start = crabs->slot.origin;
  slot_stop = crabs->slot.stop;
  slot_end = crabs->slot.stop;

  const Op* result;  //< Result of the SScan.
  const ISC* header = crabs->header;

  //< Header of the current Op being verified.
  op = nullptr;
  //    if (input == nullptr) {
  //#if DEBUG_SCRIPT2_EXPR
  //        PrintDebug ("input = nil");
  //#endif
  //        return;
  //    }

  bin_state = crabs->bin_state;  //< This isn't an optimal solution.
  bin = CrabsBIn(crabs);
  size = bin->size;
  hash = crabs->hash;
  timestamp = ClockNow();
  delta_t = timestamp - crabs->last_time;

  if (delta_t <= crabs->timeout_us) {
    if (delta_t < 0)  //< Special case for Epoch (rare)
      delta_t *= -1;
  }

  bin_begin = BInBegin(bin);
  bin_end = bin_begin + size;
  bin_start = bin_begin + bin->origin;
  bin_stop = bin_begin + bin->stop;
  space = (ISC)SlotSpace(bin_start, bin_stop, size);
  length = size - space;
  D_COUT("\n    Scanning Crabs:0x" << Hexf(crabs) << " with length:" << length);
  for (; length != 0; --length) {
    b = *bin_start;
    *slot_start++ = b;
    D_COUT(Linef('=') << "\n"
                      << length << ":\'" < < < <
           "\' state:\'" << STRBInStates()[bin_state] << "\'" << Linef('='));

    if (++bin_start >= bin_end) bin_start -= size;
    // Process the rest of the bytes in a loop to reduce setup overhead.
    switch (bin_state) {
      case cBInStateAddress: {
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
          CrabsSetState(crabs, cBInStateVerifyingHash);
          bin_state = cBInStateVerifyingHash;
          break;
        }
        operand = crabs->operand;

        op = operand->Star('?', nullptr);
        D_COUT("\nCurrent Op is \"" << op->name << "\"");

        op = operand->Star(b, nullptr);
        if (op == nullptr) {
          // Could be an invalid op or a Star Stack push.
          // I'm not sure what I was doing here with the no-op, maybe
          // trying to save some CPU resources prematurely and
          // sinfully optimizing things that don't need to be
          // optimized.
          // result = crabs->result;
          // if (result == nullptr) {
          //    return Result (crabs, cErrorInvalidOperand);
          //}
          // CrabsPushScan (crabs, crabs->operand);
          // Clear the socket and return.
          // CrabsClear (crabs); //< Do I really need to clear?
          // return crabs->result;
          return CrabsForceDisconnect(crabs, cErrorInvalidOperand);
        }
        const ISC* params = op->in;
        IUW num_ops = IUW(params);
        if (num_ops > cParamsMax) {
          // It's an Op.
          // The software implementer pushes the Op on the stack.

          // D_COUT_BSQ ("\nFound Op with params ", params)

          result = CrabsScanHeader(crabs, params);
          if (result) {
            D_COUT("Crabs::Error reading address.");
            return CrabsForceDisconnect(crabs, cErrorImplementation);
          }

          operand = crabs->operand;
          if (!operand) {
            D_COUT("\nNull operand found!");
            return CrabsForceDisconnect(crabs, cErrorInvalidOperand);
          }
          header = op->in;
          crabs->params_left = *header;
          crabs->header = header;        //< +1 to bypass the number_ of params
          crabs->header_start = header;  //< Used to utf current header.
          CrabsEnterState(crabs, cBInStatePackedArgs);
          bin_state = cBInStatePackedArgs;
          type = *(++crabs->header);  //< Setup to read first type.
          D_COUT("\nNext AsciiType to scan:\'"
                 << STAAType(type) << "\' with alignment "
                 << TypeAlign(slot_start, type) << '.');
          slot_start = TypeAlignUpPointer<CHA>(slot_start, (ISC)type);
          break;
        }
        op = operand->Star(b, crabs);
        break;
      }
      case cBInStatePackedArgs: {
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
        if (type <= cADR) {
          if (type < cADR) {  // Address type.
            D_COUT("\nScanning address.");
            CrabsError(crabs, cErrorInvalidType);
            CrabsEnterState(crabs, cBInStateLocked);
            bin_state = cBInStateLocked;
            break;
          }
          CrabsEnterState(crabs, cBInStateAddress);
          bin_state = cBInStateAddress;
          break;

        } else if (type == STR_) {  // UTF-8/ASCII  type.
          // Read the max number_ of chars off the header.
          bytes_left = *(++crabs->header);
          D_COUT("\nScanning STR with max length " << bytes_left);
          CrabsEnterState(crabs, cBInStatePackedUTF8);
          bin_state = cBInStatePackedUTF8;
          break;
        } else if (type < cFPD) {  // Plain-old-data type.
          bytes_left = TypeFixedSize(type);
          D_COUT("\nScanning POD with bytes_left:" << bytes_left);
          if (bytes_left == 1) {
            // No need to enter a state because there is only one
            // IUA to parse and we already have the IUA loaded.
            D_COUT("\nDone scanning without state change  for \""
                   << STAAType(type) << '\"');
            // Setup to read the next type.
            type = *(++crabs->header);
            D_COUT("\nNext AsciiType to scan:\'"
                   << STAAType(type)
                   << "\' with alignment:" << TypeAlign(slot_start, type));
            slot_start = TypeAlignUpPointer<>(slot_start, (ISC)type);
            break;
          }
          CrabsEnterState(crabs, cBInStatePackedPod);
          bin_state = cBInStatePackedPod;
          break;
        } else if (type < UVI) {  // Varint type.
          D_COUT("\nScanning Varint.");
          bytes_left = TypeFixedSize(type);
          CrabsEnterState(crabs, cBInStatePackedVarint);
          bin_state = cBInStatePackedVarint;
          break;
          /*
          } else if (type == STB) { // UTF-16  type.
              #if DEBUG_SCRIPT2_EXPR
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
              #if DEBUG_SCRIPT2_EXPR
              Write ("\nScanning STC.");
              #endif
              // Read the max number_ of chars off the header.
              bytes_left = *crabs->header++ * 4;
              CrabsEnterState (crabs, BIn::UTF32State);
              bin_state = BIn::UTF32State;*/
        } else {  // It's not a POD type.
          D_COUT("\nScanning AArray.");
          // Multi-dimension arrays are parsed just like any other
          // cOBJ.
          array_type &= 0x3;
          bytes_left = b;
          if (array_type == 0) {
            // We don't need to enter a state here because we
            // already have the size_bytes. :-)
            bin_state = cBInStatePackedPod;
            break;
          } else if (array_type == 1) {
            bytes_shift = 0;
            shift_bits = 16;
            CrabsEnterState(crabs, cBInStatePackedObj);
            bin_state = cBInStatePackedObj;
            break;
          } else if (array_type == 2) {
            bytes_shift = 0;
            shift_bits = 32;
            CrabsEnterState(crabs, cBInStatePackedObj);
            bin_state = cBInStatePackedObj;
            break;
          } else {  //< array_type == 3
            bytes_shift = 0;
            shift_bits = 64;
            CrabsEnterState(crabs, cBInStatePackedObj);
            bin_state = cBInStatePackedObj;
            break;
          }
        }
        break;
      }
      case cBInStatePackedUTF8: {
        if (bytes_left == 0) {
          CrabsError(crabs, cErrorTextOverflow,
                     const_cast<const ISC*>(crabs->header), 0, bin_start);
          break;
        }
        hash = HashIUB(b, hash);
        D_COUT("\nhash:");
        D_COUT_HEX(hash);
        // Hash IUA.
        // Check if CHA terminated.
        if (b == 0) {
          // Check if there is another argument to scan.
          CrabsExitState(crabs);
          bin_state = cBInStatePackedArgs;
          //< We can't go back from cOBJ to POD for Text Types.
          // Setup to read next type.
          type = *(++crabs->header);
          if (crabs->params_left == 0) {
            CrabsSetState(crabs, cBInStateAddress);
            bin_state = cBInStateAddress;
            break;
          }
          D_COUT("\nNext AsciiType to scan:\'"
                 << STAAType(type)
                 << "\' with alignment:" << TypeAlign(slot_start, type));
          slot_start = TypeAlignUpPointer<>(slot_start, (ISC)type);
          break;
        }
        --bytes_left;
        break;
      }
      case cBInStatePackedUTF16: {
        hash = HashIUB(b, hash);
        D_COUT("\nhash:");
        D_COUT_HEX(hash));
        CrabsExitState(crabs);
        break;
      }
      case cBInStatePackedUTF32: {
        hash = HashIUB(b, hash);
        D_COUT("\nhash:");
        D_COUT_HEX(hash);
        CrabsExitState(crabs);
        break;
      }
      case cBInStatePackedVarint: {
        hash = HashIUB(b, hash);
        D_COUT("\nhash:");
        D_COUT_HEX(hash);
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
            const ISC* header = const_cast<const ISC*>(crabs->header);

            CrabsEnterState(crabs, cBInStateHandlingError);
            return CrabsError(crabs, cErrorVarintOverflow, header, 0,
                              bin_start);
          }

          break;
        }
        if (b > 127) {
          D_COUT("");
          // Setup to read the next type.
          type = *(++header);
          D_COUT(
              "\nDone scanning varint: "
              "\nNext AsciiType to scan:"
              << STAAType(type)
              << " with alignment:" << TypeAlign(slot_start, type));
          slot_start = TAlignUpPointer<>(slot_start, (ISC)type);
        }
        --bytes_left;
        break;
      }
      case cBInStatePackedObj: {
        hash = HashIUB(b, hash);
        D_COUT("\nhash:" << PrintHex(hash));
        if (bytes_shift >= shift_bits) {
          // Done shifting.
          D_COUT("\nLoading object of size:" << bytes_left);
          CrabsExitState(crabs);
          CrabsEnterState(crabs, cBInStatePackedPod);
          bin_state = cBInStatePackedPod;
          break;
        }
        bytes_left &= ((ISC)b) << bytes_shift;
        shift_bits += 8;
        break;
      }
      case cBInStateVerifyingHash: {
        if (crabs->bytes_left != 0) {  // One more IUA to load.
          crabs->last_byte = b;
          crabs->bytes_left = 0;
          break;
        }
        found_hash = b;
        found_hash = found_hash << 8;
        found_hash |= crabs->last_byte;
        if (hash != found_hash) {
          D_COUT("\nError: expecting hash:");
          D_COUT_HEX(hash);
          D_COUT(" and found ");
          D_COUT_HEX(found_hash);
          return CrabsForceDisconnect(crabs, cErrorInvalidHash);
        }
        hash = PRIME_LARGEST_IUB;  //< Reset hash to largest 16-bit prime.
        D_COUT(
            "\nSuccess reading hash!"
            "\nResetting hash.\n");
        break;
      }
      case cBInStateHandlingError: {
        break;
      }
      case cBInStateDisconnected: {
        if (b) {
          CrabsSetState(crabs, cBInStateHandlingError);
          bin_state = cBInStateHandlingError;
        } else {
          CrabsSetState(crabs, cBInStateAck);
          bin_state = cBInStateAck;
        }
        break;
      }
      case cBInStateAck: {
        if (b) {
          CrabsSetState(crabs, cBInStateHandlingError);
          bin_state = cBInStateHandlingError;
        } else {
          D_COUT("\nResetting hash.");
          hash = kPrimeLargestUI2;  //< Reset hash to largest 16-bit prime.
          crabs->operand = crabs->root;
          crabs->result = nullptr;
          bin_state = cBInStateAddress;
          CrabsSetState(crabs, cBInStateAddress);
          D_COUT("\nRoot scope:\"" << OperandName(crabs->operand) << '\"');
        }
        break;
      }
      case cBInStateLocked: {
        D_COUT("Locked");
        break;
      }
      default: {
        hash = HashIUB(b, hash);
        D_COUT("\nhash:" << Hexf(hash));
        // parsing plain-old-data.
        if (!bytes_left) {
          D_COUT("... done!");
          CrabsExitState(crabs);
          bin_state = crabs->bin_state;

          // Setup to read the next type.
          type = *(++header);
          D_COUT("\nNext AsciiType to scan:\'" < < < <
                     "\' with alignment:" < < < < "",
                 STAAType(type), TypeAlign(slot_start, type));
          slot_start = TypeAlignUpPointer<>(slot_start, (ISC)type);
          break;
        }
        --bytes_left;
        // b = input->Pull ();
        D_COUT("\nLoading next IUA:");
        D_COUT_HEX(b);
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
  bin->origin = (ISC)SocketSize(bin_begin, bin_start);
  return nullptr;
}

BOL CrabsContains(Crabs* crabs, void* address) {
  if (address < TPtr<IUW>(crabs)) return false;
  if (address > CrabsEndAddress(crabs)) return false;
  return true;
}

const Op* CrabsScanHeader(Crabs* crabs, const ISC* header) {
  if (crabs->stack_count >= crabs->stack_size) {
    // Handle overflow cleanup:
    return CrabsError(crabs, cErrorStackOverflow, header);
  }

  return 0;
}

const ISC* CrabsHeaderStack(Crabs* crabs) {
  return TPtr<const ISC>(TPtr<CHA>(crabs) +
                         sizeof(Crabs) + crabs->stack_count);
}

void CrabsClose(Crabs* crabs) {
  D_COUT("\nClosing expression.");
  crabs->stack_count = 1;
}

void CrabsCancel(Crabs* crabs) {
  D_COUT("\nCanceling expression.");
  crabs->stack_count = 1;
  crabs->bin_state = cBInStateAddress;
  // CrabsPush (crabs->root);
}

void CrabsClear(Crabs* crabs) {
  // Erase the socket by writing zeros to it.

  BIn* bin = CrabsBIn(crabs);

  CHA *origin = BInBegin(bin), *stop = origin + bin->size,
      *origin = origin + bin->origin, *stop = origin + bin->stop;

  // ISC buffer_space = SlotSpace (origin, stop, size);

  if (origin == stop) return;  //< Nothing to do.
  if (origin > stop) {
    RAMFill(origin, stop - origin);
    RAMFill(origin, origin - origin);
    return;
  }
  RAMFill(origin, stop - origin);
  bin->origin = (ISC)Size(crabs, origin);
  bin->stop = (ISC)Size(crabs, origin + 1);
}

void CrabsRingBell(Crabs* crabs, const CHA* address) {
  BOutRingBell(CrabsBOut(crabs), address);
}

void CrabsAckBack(Crabs* crabs, const CHA* address) {
  BOutAckBack(CrabsBOut(crabs), address);
}

const Op* CrabsForceDisconnect(Crabs* crabs, Error error) {
  crabs->bin_state = cBInStateDisconnected;
  return CrabsError(crabs, error);
}

const Op* CrabsQuery(Crabs* crabs, const Op& op) {
  if (crabs) {
    void* args[2];
    IUW num_ops = (IUW)op.in, first_op = (IUW)op.out;
    // @todo Write params to crabs!
    static const ISC* header = Params<5, STR_, cOpNameLengthMax, UVI, UVI, STR_,
                                      cOpDescriptionLengthMax>();
    return BOutWrite(CrabsBOut(crabs), header,
                     Args(args, op.name, &num_ops, &first_op, op.description));
  }
  return &op;
}

CHA* CrabsBaseAddress(BIn* bin) {
  return TPtr<CHA>(bin) + sizeof(BIn);
}

ISC CrabsSpace(BIn* bin) {
  if (!bin) {
    return ~0;
  }

  CHA* origin = CrabsBaseAddress(bin);
  return (ISC)SlotSpace(origin + bin->origin, origin + bin->stop, bin->size);
}

IUW* CrabsBaseAddress(void* ptr, ISC rx_tx_offset) {
  enum {
    cSlotHeaderSize = sizeof(BIn) + sizeof(IUW) - sizeof(BIn) % sizeof(IUW),
    //< Offset to the origin of the ring socket.
  };
  CHA* result = TPtr<CHA>(ptr) + rx_tx_offset + cSlotHeaderSize;
  return TPtr<IUW>(result);
}

CHA* CrabsEndAddress(BIn* bin) {
  return TPtr<CHA>(bin) + sizeof(BIn) + bin->size;
}

const Op* CrabsQuery(Crabs* crabs, const Op* op) {
  if (crabs) {
    if (!op) {
      return CrabsError(crabs, cErrorImplementation);
    }
    void* args[2];
    return BOutWrite(CrabsBOut(crabs),
                     Params<5, STR_, cOpNameLengthMax, UVI, UVI, STR_,
                            cOpDescriptionLengthMax>(),
                     Args(args, op->name, op->in, op->out, op->description));
  }
  return op;
}

#if USING_SCRIPT2_TEXT
UTF1& PrintCrabsStack(UTF1& utf, Crabs* crabs) {
  A_ASSERT(crabs);

  ISC i, stack_count;
  const Op* op;
  Operand* operand;
  Operand** stack = CrabsStack(crabs);

  stack_count = crabs->stack_count;
  utf << "\nOperand stack_count:" << stack_count;

  if (stack_count == 1) {
    return utf << "\nStack Item 1: " << OperandName(crabs->root);
  }
  for (i = 0; i < stack_count - 1; ++i) {
    utf << "\nStack Item " << i + 1 << ":\"";
    operand = stack[i];
    op = operand->Star('?', nullptr);
    utf << op->name << '\"';
  }
  op = crabs->operand->Star('?', nullptr);
  return utf << "\nStack Item " << i + 1 << ":\"" << op->name << "\"";
}

template<typename Printer>
Printer& Print(Printer& o, Crabs* crabs) {
  o << Line('~', 80) << "\nStack:    " << Hexf(crabs) << '\n'
    << Line('_', 80) << "\nbytes_left : " << crabs->bytes_left
    << "\nheader_size: " << crabs->header_size
    << "\nstack_count: " << crabs->stack_count
    << "\nstack_size : " << crabs->stack_size
    << "\nbin_state  : " << BInStateStrings()[crabs->bin_state]
    << "\nbout_state : " << BOutStateStrings()[crabs->bout_state]
    << "\nnum_states : " << crabs->num_states
    << "\nheader_size: " << crabs->header_size << Line('-', 80)
    << crabs->operand << "\nheader     : " << BSeq(crabs->header_start)
    << Line('-', 80);
  PrintCrabsStack(utf, crabs);
  utf << Line('~', 80);
  return utf;
}

#endif

}  //< namespace _

#endif
