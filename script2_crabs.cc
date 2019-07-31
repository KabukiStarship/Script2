/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_crabs.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
#include "c_crabs.h"

#include "c_bsq.h"
#include "c_clock.h"
#include "c_hash.h"
#include "c_test.h"

#if SEAM == SCRIPT2_DICTIONARY
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* Used to return an erroneous result from a B-Input.
@return Returns a Static Error Op Result.
@param error The error type. */
inline const Op* CrabsError(Crabs* crabs, Error error) {
  D_COUT("\nCrabs " << ErrorStrand(error) << " Error!");
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Input.
@return         Returns a Static Error Op Result.
@param  crabs    The source Crabs.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error. */
inline const Op* CrabsError(Crabs* crabs, Error error, const SI4* header) {
  D_COUT("\nCrabs " << ErrorStrand(error) << " Error!");
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Input.
@return         Returns a Static Error Op Result.
@param  crabs    The source Crabs.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error. */
inline const Op* CrabsError(Crabs* crabs, Error error, const SI4* header,
                            UI1 offset) {
  D_COUT("\nCrabs " << ErrorStrand(error) << " Error!");
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Input.
@return         Returns a Static Error Op Result.
@param  crabs    The source Crabs.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error. */
inline const Op* CrabsError(Crabs* crabs, Error error, const SI4* header,
                            UI1 offset, CH1* address) {
  D_COUT("\nCrabs " << ErrorStrand(error) << " Error!");
  return reinterpret_cast<const Op*>(1);
}

UIW* CrabsBinAddress(Crabs* crabs) {
  if (!crabs) return nullptr;
  return reinterpret_cast<UIW*>(crabs) + crabs->header_size;
}

CH1* CrabsBuffer(Crabs* crabs) {
  CH1* ptr = reinterpret_cast<CH1*>(crabs);
  return ptr + sizeof(Crabs);
}

BIn* CrabsBIn(Crabs* crabs) {
  return reinterpret_cast<BIn*>(CrabsBinAddress(crabs));
}

UIW* CrabsBOutAddress(Crabs* crabs) {
  if (!crabs) {
    return nullptr;
  }
  return reinterpret_cast<UIW*>(crabs) + crabs->header_size;
}

BOut* CrabsBOut(Crabs* crabs) {
  return reinterpret_cast<BOut*>(CrabsBOutAddress(crabs));
}

Crabs* CrabsInit(UIW* socket, SI4 buffer_size, SI4 stack_size, Operand* root,
                 UIW* unpacked_buffer, UIW unpacked_size) {
  if (!socket) {
    return nullptr;
  }
  if (buffer_size < Crabs::kMinBufferSize) {
    return nullptr;
  }
  if (stack_size < kMinStackSize) {
    stack_size = kMinStackSize;  //< Minimum stack size.
  }
  if (unpacked_buffer == nullptr) {
    D_COUT("\nError: unpacked_buffer was nil!");
  }

  if (root == nullptr) {
    D_COUT("\nError: root can't be nil.");
    return nullptr;
  }

  Crabs* crabs = reinterpret_cast<Crabs*>(socket);

  SI4 total_stack_size = (stack_size - 1) * (2 * sizeof(Operand*));
  // Calculate the size of the Slot and Stack.
  SI4 size = (buffer_size - sizeof(Crabs) - total_stack_size + 1) >> 1;

  //< >>1 to divide by 2
  crabs->bout_state = kBOutStateDisconnected;
  crabs->bin_state = kBInStateDisconnected;
  crabs->stack_count = 1;
  crabs->type = kNIL;
  crabs->stack_size = stack_size;
  crabs->num_states = 0;
  crabs->operand = nullptr;
  D_COUT("\nInitializing Stack with size:" << stack_size << " buffer_size:"
                                           << buffer_size << " size:" << size);
  crabs->bytes_left = 0;
  // SI4 offset    = sizeof (Crabs) + total_stack_size - sizeof (void*);
  // bin_offset       = sizeof (BIn) + total_stack_size + offset;
  crabs->header_size = sizeof(Crabs) + 2 * sizeof(void*) * stack_size;
  crabs->hash = kPrimeLargestUI2;
  crabs->result = nullptr;
  crabs->header = nullptr;
  crabs->header_start = nullptr;
  crabs->root = root;
  UIW* base_ptr =
      reinterpret_cast<UIW*>(crabs) + sizeof(Crabs) + stack_size * sizeof(SI4);
  crabs->slot.Set(base_ptr, unpacked_size);
  D_COUT("crabs->op:0x" << Hexf(crabs->operand));
  BInInit(CrabsBinAddress(crabs), size);
  BOutInit(CrabsBOutAddress(crabs), size);
  return crabs;
}

// BOL CrabsIsDynamic (Crabs* crabs) {
//    return crabs->type % 2 == 1;
//}

CH1* CrabsEndAddress(Crabs* crabs) { return BInEnd(CrabsBIn(crabs)); }

const Op* CrabsReset(Crabs* crabs) { return 0; }

UI1 CrabsExitState(Crabs* crabs) {
  // We are guaranteed crabs is not nil at this point.
  // if (!crabs) {
  //    return  CrabsError (CrabsBIn (crabs), kErrorImplementation);
  //}
  D_COUT("\nExiting " << STRBInStates()[crabs->bin_state]
                      << " state back to the state:"
                      << STRBInStates()[crabs->last_bin_state] << '.');
  UI1 state = crabs->last_bin_state;
  crabs->bin_state = state;
  return state;
}

const Op* CrabsSetState(Crabs* crabs, BInState state) {
  // We are guaranteed crabs is not nil at this point.
  // if (!crabs) {
  //    return  CrabsError (CrabsBIn (crabs), kErrorImplementation);
  //}
  if (state == kBInStateLocked) {
    return CrabsError(crabs, kErrorObjLocked);
  }
  D_COUT("\nEntering " << BInState[state] << " state:" << state);
  crabs->bin_state = state;
  return nullptr;
}

const Op* CrabsEnterState(Crabs* crabs, BInState state) {
  // We are guaranteed crabs is not nil at this point.
  // if (!crabs) {
  //    return  CrabsError (CrabsBIn (crabs), kErrorImplementation);
  //}
  D_COUT("\nEntering " << BInState()[state] << " state:" << state);
  crabs->last_bin_state = crabs->bin_state;
  crabs->bin_state = state;
  return nullptr;
}

UI1 CrabsStreamBOut(Crabs* crabs) { return BOutStreamByte(CrabsBOut(crabs)); }

const Op* Push(Crabs* crabs, Operand* operand) {
  if (!crabs) {
    return CrabsError(crabs, kErrorImplementation);
  }
  if (!operand) {
    return CrabsError(crabs, kErrorInvalidOperand);
  }
  D_COUT("\nPushing " << operand->Star('?', nullptr)->name
                      << " onto the stack");
  SI4 stack_count = crabs->stack_count;
  if (stack_count >= crabs->stack_size) {
    return CrabsError(crabs, kErrorStackOverflow);
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
  SI4 stack_count = crabs->stack_count;
  if (stack_count == 0) {  // This should not happen.
    return CrabsError(crabs, kErrorInvalidOperand);
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
    return CrabsError(crabs, kErrorImplementation);
  }

  SI4 size,          //< Size of the ring socket.
      space,         //< Space left in the right socket.
      length,        //< Length of the ring socket data.
      type,          //< Current type.
      bytes_left,    //< Number of bytes left to scan.
      array_type,    //< The type of array.
      shift_bits,    //< Number of bytes left to scan.
      bytes_shift;   //< Number of bits to shift to scan the current AArray.
  UI1 bin_state,     //< Current bin FSM state.
      b;             //< Current UI1 being verified.
  UI2 hash,          //< Expected hash of the B-Sequence.
      found_hash;    //< Found B-Sequence hash.
  TM8 timestamp,     //< Last time when the expression ran.
      delta_t;       //< Time delta between the last timestamp.
  const Op* op;      //< Current operation.
  Operand* operand;  //< The operand.
  BIn* bin;          //< BIn.
  CH1 *bin_begin,    //< Beginning of the ring socket.
      *bin_start,    //< Start of the ring socket data.
      *bin_stop,     //< Stop of the ring socket data.
      *bin_end,      //< End of the ring socket.
      *slot_begin,   //< The first byte in the Slot.
      *slot_start,   //< Pointer to the write cursor.
      *slot_stop,    //< The last byte of data in the Slot.
      *slot_end;     //< The byte after the last byte ein the Slot

  slot_begin = crabs->slot.begin;
  slot_start = crabs->slot.begin;
  slot_stop = crabs->slot.stop;
  slot_end = crabs->slot.stop;

  const Op* result;  //< Result of the SScan.
  const SI4* header = crabs->header;

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
  bin_start = bin_begin + bin->begin;
  bin_stop = bin_begin + bin->stop;
  space = (SI4)SlotSpace(bin_start, bin_stop, size);
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
      case kBInStateAddress: {
        hash = HashPrime16(b, hash);
        D_COUT("\nhash:0x%x" << Hexf(hash));
        // When verifying an address, there is guaranteed to be an
        // crabs->op set. We are just looking for nil return values
        // from the Do (UI1, Stack*): const Operand* function,
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
          CrabsSetState(crabs, kBInStateVerifyingHash);
          bin_state = kBInStateVerifyingHash;
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
          //    return Result (crabs, kErrorInvalidOperand);
          //}
          // CrabsPushScan (crabs, crabs->operand);
          // Clear the socket and return.
          // CrabsClear (crabs); //< Do I really need to clear?
          // return crabs->result;
          return CrabsForceDisconnect(crabs, kErrorInvalidOperand);
        }
        const SI4* params = op->in;
        UIW num_ops = reinterpret_cast<UIW>(params);
        if (num_ops > kParamsMax) {
          // It's an Op.
          // The software implementer pushes the Op on the stack.

          // D_COUT_BSQ ("\nFound Op with params ", params)

          result = CrabsScanHeader(crabs, params);
          if (result) {
            D_COUT("Crabs::Error reading address.");
            return CrabsForceDisconnect(crabs, kErrorImplementation);
          }

          operand = crabs->operand;
          if (!operand) {
            D_COUT("\nNull operand found!");
            return CrabsForceDisconnect(crabs, kErrorInvalidOperand);
          }
          header = op->in;
          crabs->params_left = *header;
          crabs->header = header;        //< +1 to bypass the number_ of params
          crabs->header_start = header;  //< Used to utf current header.
          CrabsEnterState(crabs, kBInStatePackedArgs);
          bin_state = kBInStatePackedArgs;
          type = *(++crabs->header);  //< Setup to read first type.
          D_COUT("\nNext AsciiType to scan:\'"
                 << STRType(type) << "\' with alignment "
                 << TypeAlign(slot_start, type) << '.');
          slot_start = TypeAlignUpPointer<CH1>(slot_start, (SI4)type);
          break;
        }
        op = operand->Star(b, crabs);
        break;
      }
      case kBInStatePackedArgs: {
        // In this state, a procedure has been called to scan on a valid
        // operand. This state is responsible for loading the next
        // header argument and checking for the stop of the procedure
        // call.

        if (crabs->params_left-- == 0) {
          D_COUT("\nBSQ successfully scanned.");

          break;
        }
        hash = HashPrime16(b, hash);
        D_COUT("\nhash:" << Hexf(hash));

        // Switch to next state
        if (type <= kADR) {
          if (type < kADR) {  // Address type.
            D_COUT("\nScanning address.");
            CrabsError(crabs, kErrorInvalidType);
            CrabsEnterState(crabs, kBInStateLocked);
            bin_state = kBInStateLocked;
            break;
          }
          CrabsEnterState(crabs, kBInStateAddress);
          bin_state = kBInStateAddress;
          break;

        } else if (type == kSTR) {  // UTF-8/ASCII  type.
          // Read the max number_ of chars off the header.
          bytes_left = *(++crabs->header);
          D_COUT("\nScanning STR with max length " << bytes_left);
          CrabsEnterState(crabs, kBInStatePackedUTF8);
          bin_state = kBInStatePackedUTF8;
          break;
        } else if (type < kFP8) {  // Plain-old-data type.
          bytes_left = TypeFixedSize(type);
          D_COUT("\nScanning POD with bytes_left:" << bytes_left);
          if (bytes_left == 1) {
            // No need to enter a state because there is only one
            // UI1 to parse and we already have the UI1 loaded.
            D_COUT("\nDone scanning without state change  for \""
                   << STRType(type) << '\"');
            // Setup to read the next type.
            type = *(++crabs->header);
            D_COUT("\nNext AsciiType to scan:\'"
                   << STRType(type)
                   << "\' with alignment:" << TypeAlign(slot_start, type));
            slot_start = TypeAlignUpPointer<>(slot_start, (SI4)type);
            break;
          }
          CrabsEnterState(crabs, kBInStatePackedPod);
          bin_state = kBInStatePackedPod;
          break;
        } else if (type < UVI) {  // Varint type.
          D_COUT("\nScanning Varint.");
          bytes_left = TypeFixedSize(type);
          CrabsEnterState(crabs, kBInStatePackedVarint);
          bin_state = kBInStatePackedVarint;
          break;
          /*
          } else if (type == ST2) { // UTF-16  type.
              #if DEBUG_SCRIPT2_EXPR
              Write ("\nScanning ST2.");
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
          else if (type == ST4) { // UTF-32  type.
              #if DEBUG_SCRIPT2_EXPR
              Write ("\nScanning ST4.");
              #endif
              // Read the max number_ of chars off the header.
              bytes_left = *crabs->header++ * 4;
              CrabsEnterState (crabs, BIn::UTF32State);
              bin_state = BIn::UTF32State;*/
        } else {  // It's not a POD type.
          D_COUT("\nScanning AArray.");
          // Multi-dimension arrays are parsed just like any other
          // kOBJ.
          array_type &= 0x3;
          bytes_left = b;
          if (array_type == 0) {
            // We don't need to enter a state here because we
            // already have the size_bytes. :-)
            bin_state = kBInStatePackedPod;
            break;
          } else if (array_type == 1) {
            bytes_shift = 0;
            shift_bits = 16;
            CrabsEnterState(crabs, kBInStatePackedObj);
            bin_state = kBInStatePackedObj;
            break;
          } else if (array_type == 2) {
            bytes_shift = 0;
            shift_bits = 32;
            CrabsEnterState(crabs, kBInStatePackedObj);
            bin_state = kBInStatePackedObj;
            break;
          } else {  //< array_type == 3
            bytes_shift = 0;
            shift_bits = 64;
            CrabsEnterState(crabs, kBInStatePackedObj);
            bin_state = kBInStatePackedObj;
            break;
          }
        }
        break;
      }
      case kBInStatePackedUTF8: {
        if (bytes_left == 0) {
          CrabsError(crabs, kErrorTextOverflow,
                     const_cast<const SI4*>(crabs->header), 0, bin_start);
          break;
        }
        hash = HashPrime16(b, hash);
        D_COUT("\nhash:");
        D_COUT_HEX(hash);
        // Hash UI1.
        // Check if CH1 terminated.
        if (b == 0) {
          // Check if there is another argument to scan.
          CrabsExitState(crabs);
          bin_state = kBInStatePackedArgs;
          //< We can't go back from kOBJ to POD for Text Types.
          // Setup to read next type.
          type = *(++crabs->header);
          if (crabs->params_left == 0) {
            CrabsSetState(crabs, kBInStateAddress);
            bin_state = kBInStateAddress;
            break;
          }
          D_COUT("\nNext AsciiType to scan:\'"
                 << STRType(type)
                 << "\' with alignment:" << TypeAlign(slot_start, type));
          slot_start = TypeAlignUpPointer<>(slot_start, (SI4)type);
          break;
        }
        --bytes_left;
        break;
      }
      case kBInStatePackedUTF16: {
        hash = HashPrime16(b, hash);
        D_COUT("\nhash:");
        D_COUT_HEX(hash));
        CrabsExitState(crabs);
        break;
      }
      case kBInStatePackedUTF32: {
        hash = HashPrime16(b, hash);
        D_COUT("\nhash:");
        D_COUT_HEX(hash);
        CrabsExitState(crabs);
        break;
      }
      case kBInStatePackedVarint: {
        hash = HashPrime16(b, hash);
        D_COUT("\nhash:");
        D_COUT_HEX(hash);
        // When verifying a varint, there is a max number_ of bytes for
        // the type (3, 5, or 9) but the varint may be complete before
        // this number_ of bytes. We're just basically counting down and
        // looking for an overflow situation.
        // Hash UI1.

        if (bytes_left == 1) {
          D_COUT("Checking last UI1:");

          // @warning I am not current saving the offset. I'm not
          // sure  what to do here. The header class uses a variadic
          // template, I'm kind of tempted to switch to an SI4
          // type for the headers so I can just use a normal
          // array bracket initializer. The other option is to
          // add 32 to the first UI1.

          if ((b >> 7) != 1) {
            const SI4* header = const_cast<const SI4*>(crabs->header);

            CrabsEnterState(crabs, kBInStateHandlingError);
            return CrabsError(crabs, kErrorVarintOverflow, header, 0,
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
              << STRType(type)
              << " with alignment:" << TypeAlign(slot_start, type));
          slot_start = TAlignUpPointer<>(slot_start, (SI4)type);
        }
        --bytes_left;
        break;
      }
      case kBInStatePackedObj: {
        hash = HashPrime16(b, hash);
        D_COUT("\nhash:" << PrintHex(hash));
        if (bytes_shift >= shift_bits) {
          // Done shifting.
          D_COUT("\nLoading object of size:" << bytes_left);
          CrabsExitState(crabs);
          CrabsEnterState(crabs, kBInStatePackedPod);
          bin_state = kBInStatePackedPod;
          break;
        }
        bytes_left &= ((SI4)b) << bytes_shift;
        shift_bits += 8;
        break;
      }
      case kBInStateVerifyingHash: {
        if (crabs->bytes_left != 0) {  // One more UI1 to load.
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
          return CrabsForceDisconnect(crabs, kErrorInvalidHash);
        }
        hash = kPrimeLargestUI2;  //< Reset hash to largest 16-bit prime.
        D_COUT(
            "\nSuccess reading hash!"
            "\nResetting hash.\n");
        break;
      }
      case kBInStateHandlingError: {
        break;
      }
      case kBInStateDisconnected: {
        if (b) {
          CrabsSetState(crabs, kBInStateHandlingError);
          bin_state = kBInStateHandlingError;
        } else {
          CrabsSetState(crabs, kBInStateAck);
          bin_state = kBInStateAck;
        }
        break;
      }
      case kBInStateAck: {
        if (b) {
          CrabsSetState(crabs, kBInStateHandlingError);
          bin_state = kBInStateHandlingError;
        } else {
          D_COUT("\nResetting hash.");
          hash = kPrimeLargestUI2;  //< Reset hash to largest 16-bit prime.
          crabs->operand = crabs->root;
          crabs->result = nullptr;
          bin_state = kBInStateAddress;
          CrabsSetState(crabs, kBInStateAddress);
          D_COUT("\nRoot scope:\"" << OperandName(crabs->operand) << '\"');
        }
        break;
      }
      case kBInStateLocked: {
        D_COUT("Locked");
        break;
      }
      default: {
        hash = HashPrime16(b, hash);
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
                 STRType(type), TypeAlign(slot_start, type));
          slot_start = TypeAlignUpPointer<>(slot_start, (SI4)type);
          break;
        }
        --bytes_left;
        // b = input->Pull ();
        D_COUT("\nLoading next UI1:");
        D_COUT_HEX(b);
        hash = HashPrime16(b, hash);
        *bin_start = b;
        ++bin_start;
        break;
      }
    }
  }
  //
  crabs->hash = hash;
  crabs->bytes_left = bytes_left;
  bin->begin = (SI4)SocketSize(bin_begin, bin_start);
  return nullptr;
}

BOL CrabsContains(Crabs* crabs, void* address) {
  if (address < reinterpret_cast<UIW*>(crabs)) return false;
  if (address > CrabsEndAddress(crabs)) return false;
  return true;
}

const Op* CrabsScanHeader(Crabs* crabs, const SI4* header) {
  if (crabs->stack_count >= crabs->stack_size) {
    // Handle overflow cleanup:
    return CrabsError(crabs, kErrorStackOverflow, header);
  }

  return 0;
}

const SI4* CrabsHeaderStack(Crabs* crabs) {
  return reinterpret_cast<const SI4*>(reinterpret_cast<CH1*>(crabs) +
                                      sizeof(Crabs) + crabs->stack_count);
}

void CrabsClose(Crabs* crabs) {
  D_COUT("\nClosing expression.");
  crabs->stack_count = 1;
}

void CrabsCancel(Crabs* crabs) {
  D_COUT("\nCanceling expression.");
  crabs->stack_count = 1;
  crabs->bin_state = kBInStateAddress;
  // CrabsPush (crabs->root);
}

void CrabsClear(Crabs* crabs) {
  // Erase the socket by writing zeros to it.

  BIn* bin = CrabsBIn(crabs);

  CH1 *begin = BInBegin(bin), *stop = begin + bin->size,
      *begin = begin + bin->begin, *stop = begin + bin->stop;

  // SI4 buffer_space = SlotSpace (begin, stop, size);

  if (begin == stop) return;  //< Nothing to do.
  if (begin > stop) {
    ArrayFill(begin, stop - begin);
    ArrayFill(begin, begin - begin);
    return;
  }
  ArrayFill(begin, stop - begin);
  bin->begin = (SI4)Size(crabs, begin);
  bin->stop = (SI4)Size(crabs, begin + 1);
}

void CrabsRingBell(Crabs* crabs, const CH1* address) {
  BOutRingBell(CrabsBOut(crabs), address);
}

void CrabsAckBack(Crabs* crabs, const CH1* address) {
  BOutAckBack(CrabsBOut(crabs), address);
}

const Op* CrabsForceDisconnect(Crabs* crabs, Error error) {
  crabs->bin_state = kBInStateDisconnected;
  return CrabsError(crabs, error);
}

const Op* CrabsQuery(Crabs* crabs, const Op& op) {
  if (crabs) {
    void* args[2];
    UIW num_ops = (UIW)op.in, first_op = (UIW)op.out;
    // @todo Write params to crabs!
    static const SI4* header = Params<5, kSTR, kOpNameLengthMax, UVI, UVI, kSTR,
                                      kOpDescriptionLengthMax>();
    return BOutWrite(CrabsBOut(crabs), header,
                     Args(args, op.name, &num_ops, &first_op, op.description));
  }
  return &op;
}

CH1* CrabsBaseAddress(BIn* bin) {
  return reinterpret_cast<CH1*>(bin) + sizeof(BIn);
}

SI4 CrabsSpace(BIn* bin) {
  if (!bin) {
    return ~0;
  }

  CH1* begin = CrabsBaseAddress(bin);
  return (SI4)SlotSpace(begin + bin->begin, begin + bin->stop, bin->size);
}

UIW* CrabsBaseAddress(void* ptr, SI4 rx_tx_offset) {
  enum {
    kSlotHeaderSize = sizeof(BIn) + sizeof(UIW) - sizeof(BIn) % sizeof(UIW),
    //< Offset to the begin of the ring socket.
  };
  CH1* result = reinterpret_cast<CH1*>(ptr) + rx_tx_offset + kSlotHeaderSize;
  return reinterpret_cast<UIW*>(result);
}

CH1* CrabsEndAddress(BIn* bin) {
  return reinterpret_cast<CH1*>(bin) + sizeof(BIn) + bin->size;
}

const Op* CrabsQuery(Crabs* crabs, const Op* op) {
  if (crabs) {
    if (!op) {
      return CrabsError(crabs, kErrorImplementation);
    }
    void* args[2];
    return BOutWrite(CrabsBOut(crabs),
                     Params<5, kSTR, kOpNameLengthMax, UVI, UVI, kSTR,
                            kOpDescriptionLengthMax>(),
                     Args(args, op->name, op->in, op->out, op->description));
  }
  return op;
}

#if USING_SCRIPT2_TEXT
UTF1& PrintCrabsStack(UTF1& utf, Crabs* crabs) {
  A_ASSERT(crabs);

  SI4 i, stack_count;
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

Printer& Print(Printer& o, Crabs* crabs) {
  o << Line('~', 80) << "\nStack:    " << CHex<UIW>(crabs) << '\n'
    << Line('_', 80) << "\nbytes_left : " << crabs->bytes_left
    << "\nheader_size: " << crabs->header_size
    << "\nstack_count: " << crabs->stack_count
    << "\nstack_size : " << crabs->stack_size
    << "\nbin_state  : " << BInStateStrands()[crabs->bin_state]
    << "\nbout_state : " << BOutStateStrands()[crabs->bout_state]
    << "\nnum_states : " << crabs->num_states
    << "\nheader_size: " << crabs->header_size << Line('-', 80)
    << crabs->operand << "\nheader     : " << Bsq(crabs->header_start)
    << Line('-', 80);
  PrintCrabsStack(utf, crabs);
  utf << Line('~', 80);
  return utf;
}

#endif

}  // namespace _

#endif
