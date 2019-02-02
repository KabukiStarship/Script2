/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_crabs.cc
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>
#if SEAM >= SCRIPT2_14
#include "c_crabs.h"

#include "c_bsq.h"
#include "c_hash.h"
#include "c_lock.h"
#include "c_test.h"

#if SEAM == SCRIPT2_14
#include "global_debug.inl"
#else
#include "global_release.inl"
#endif

namespace _ {

/* Used to return an erroneous result from a B-Input.
@return Returns a Static Error Op Result.
@param error The error type. */
inline const Op* CrabsError(CCrabs* crabs, Error error) {
  PRINTF("\nCrabs %s Error!", ErrorStrand(error))
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Input.
@return         Returns a Static Error Op Result.
@param  crabs    The source CCrabs.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error. */
inline const Op* CrabsError(CCrabs* crabs, Error error, const SI4* header) {
  PRINTF("\nCrabs %s Error!", ErrorStrand(error))
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Input.
@return         Returns a Static Error Op Result.
@param  crabs    The source CCrabs.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error. */
inline const Op* CrabsError(CCrabs* crabs, Error error, const SI4* header,
                            UI1 offset) {
  PRINTF("\nCrabs %s Error!", ErrorStrand(error))
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Input.
@return         Returns a Static Error Op Result.
@param  crabs    The source CCrabs.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error. */
inline const Op* CrabsError(CCrabs* crabs, Error error, const SI4* header,
                            UI1 offset, CH1* address) {
  PRINTF("\nCrabs %s Error!", ErrorStrand(error))
  return reinterpret_cast<const Op*>(1);
}

UIW* CrabsBinAddress(CCrabs* crabs) {
  if (!crabs) return nullptr;
  return reinterpret_cast<UIW*>(crabs) + crabs->header_size;
}

CH1* CrabsBuffer(CCrabs* crabs) {
  CH1* ptr = reinterpret_cast<CH1*>(crabs);
  return ptr + sizeof(CCrabs);
}

BIn* CrabsBIn(CCrabs* crabs) {
  return reinterpret_cast<BIn*>(CrabsBinAddress(crabs));
}

UIW* CrabsBOutAddress(CCrabs* crabs) {
  if (!crabs) {
    return nullptr;
  }
  return reinterpret_cast<UIW*>(crabs) + crabs->header_size;
}

BOut* CrabsBOut(CCrabs* crabs) {
  return reinterpret_cast<BOut*>(CrabsBOutAddress(crabs));
}

CCrabs* CrabsInit(UIW* socket, SI4 buffer_size, SI4 stack_size, Operand* root,
                  UIW* unpacked_buffer, UIW unpacked_size) {
  if (!socket) {
    return nullptr;
  }
  if (buffer_size < CCrabs::kMinBufferSize) {
    return nullptr;
  }
  if (stack_size < kMinStackSize) {
    stack_size = kMinStackSize;  //< Minimum stack size.
  }
  if (unpacked_buffer == nullptr) {
    PRINTF("\nError: unpacked_buffer was nil!")
  }

  if (root == nullptr) {
    PRINTF("\nError: root can't be nil.")
    return nullptr;
  }

  CCrabs* crabs = reinterpret_cast<CCrabs*>(socket);

  SI4 total_stack_size = (stack_size - 1) * (2 * sizeof(Operand*));
  // Calculate the size of the Slot and Stack.
  SI4 size = (buffer_size - sizeof(CCrabs) - total_stack_size + 1) >> 1;

  //< >>1 to divide by 2
  crabs->bout_state = kBOutStateDisconnected;
  crabs->bin_state = kBInStateDisconnected;
  crabs->stack_count = 1;
  crabs->type = kNIL;
  crabs->stack_size = stack_size;
  crabs->num_states = 0;
  crabs->operand = nullptr;
#if DEBUG_SCRIPT2_EXPR
    PRINTF ("\nInitializing Stack with size:" << stack_size
            << " buffer_size:" << buffer_size << " size:" << size;
#endif
    crabs->bytes_left = 0;
    //SI4 offset    = sizeof (CCrabs) + total_stack_size - sizeof (void*);
    //bin_offset       = sizeof (BIn) + total_stack_size + offset;
    crabs->header_size = sizeof (CCrabs) + 2 * sizeof (void*) * stack_size;
    crabs->hash = kPrime2Unsigned;
    crabs->result = nullptr;
    crabs->header = nullptr;
    crabs->header_start = nullptr;
    crabs->root = root;
    UIW* base_ptr = reinterpret_cast<UIW*> (crabs) + sizeof (CCrabs) +
                          stack_size * sizeof (SI4);
    crabs->slot.Set (base_ptr, unpacked_size);
#if DEBUG_SCRIPT2_EXPR
    PRINTF ("crabs->op:" << OutHex (crabs->operand);
#endif
    BInInit (CrabsBinAddress (crabs), size);
    BOutInit (CrabsBOutAddress (crabs), size);
    return crabs;
}

// BOL CrabsIsDynamic (CCrabs* crabs) {
//    return crabs->type % 2 == 1;
//}

CH1* CrabsEndAddress(CCrabs* crabs) { return BInEnd(CrabsBIn(crabs)); }

const Op* CrabsReset(CCrabs* crabs) { return 0; }

UI1 CrabsExitState(CCrabs* crabs) {
  // We are guaranteed crabs is not nil at this point.
  // if (!crabs) {
  //    return  CrabsError (CrabsBIn (crabs), kErrorImplementation);
  //}
#if DEBUG_SCRIPT2_EXPR
    PRINTF ("\nExiting " << BInState ()[crabs->bin_state]
            << " state back to the " << BInState ()[crabs->last_bin_state]
            << " state .";
#endif
    UI1 state = crabs->last_bin_state;
    crabs->bin_state = state;
    return state;
}

const Op* CrabsSetState(CCrabs* crabs, BInState state) {
  // We are guaranteed crabs is not nil at this point.
  // if (!crabs) {
  //    return  CrabsError (CrabsBIn (crabs), kErrorImplementation);
  //}
  if (state == kBInStateLocked) {
    return CrabsError(crabs, kErrorObjLocked);
  }
#if DEBUG_SCRIPT2_EXPR
    PRINTF ("\nEntering " << BInState ()[state]
            << " state:" << state;
#endif
    crabs->bin_state = state;
    return nullptr;
}

const Op* CrabsEnterState(CCrabs* crabs, BInState state) {
  // We are guaranteed crabs is not nil at this point.
  // if (!crabs) {
  //    return  CrabsError (CrabsBIn (crabs), kErrorImplementation);
  //}
#if DEBUG_SCRIPT2_EXPR
    PRINTF ("\nEntering " << BInState ()[state]
            << " state:" << state;
#endif
    crabs->last_bin_state = crabs->bin_state;
    crabs->bin_state = state;
    return nullptr;
}

UI1 CrabsStreamBOut(CCrabs* crabs) { return BOutStreamByte(CrabsBOut(crabs)); }

const Op* Push(CCrabs* crabs, Operand* operand) {
  if (!crabs) {
    return CrabsError(crabs, kErrorImplementation);
  }
  if (!operand) {
    return CrabsError(crabs, kErrorInvalidOperand);
  }
  PRINTF("\nPushing %s onto the stack", operand->Star('?', nullptr)->name);
  SI4 stack_count = crabs->stack_count;
  if (stack_count >= crabs->stack_size) {
    return CrabsError(crabs, kErrorStackOverflow);
  }
  CrabsStack(crabs)[stack_count - 1] = crabs->operand;
  crabs->operand = operand;
  crabs->stack_count = stack_count + 1;
#if DEBUG_SCRIPT2_EXPR
    PRINTF (CrabsPrintStack (crabs, Print ());
#endif
    return nullptr;
}

const Op* Pop(CCrabs* crabs) {
  SI4 stack_count = crabs->stack_count;
  if (stack_count == 0) {  // This should not happen.
    return CrabsError(crabs, kErrorInvalidOperand);
  }
  if (stack_count == 1) {
    // We ever pop off the root.
    CrabsClose(crabs);
    return 0;
  }
  PRINTF("\nPopping %s off the stack.", OperandName(crabs->operand))
  crabs->operand = CrabsStack(crabs)[stack_count - 2];
  crabs->stack_count = stack_count - 1;
#if DEBUG_SCRIPT2_EXPR
  Slot sout = out;
    PRINTF ("\nTop of stack is now "
            << OperandName (crabs->operand) << "."
            << CrabsPrintStack (crabs, Print ());
#endif
    return nullptr;
}

const Op* CrabsUnpack(CCrabs* crabs) {
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
      bytes_shift;   //< Number of bits to shift to scan the current CObject.
  UI1 bin_state,     //< Current bin FSM state.
      b;             //< Current UI1 being verified.
  hash16_t hash,     //< Expected hash of the B-Sequence.
      found_hash;    //< Found B-Sequence hash.
  TM8 timestamp,     //< Last time when the expression ran.
      delta_t;       //< Time delta between the last timestamp.
  const Op* op;      //< Current Op.
  Operand* operand;  //< The operand.
  BIn* bin;          //< BIn.
  CH1 *bin_begin,   //< Beginning of the ring socket.
      *bin_start,    //< Start of the ring socket data.
      *bin_stop,     //< Stop of the ring socket data.
      *bin_end,      //< End of the ring socket.
          *slot_begin = crabs->slot.begin,
          *slot_start = crabs->slot.begin,  //< Write cursor,
              *slot_stop = crabs->slot.stop, *slot_end = crabs->slot.stop;
  const Op* result;  //< Result of the Scan.
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
  PRINTF("\n    Scanning CCrabs:0x%p with length:%i", crabs, length)
  for (; length != 0; --length) {
    b = *bin_start;
    *slot_start++ = b;
#if DEBUG_SCRIPT2_EXPR
            PRINTF (out.Line ('=') << '\n' << length
                    << ":\'"
                    << ((b < 32 || b == 127) ? (PRINTF (AsciiText ((AsciiCode)b))
                    : (PRINTF (b))
                    << "\' " << BInState ()[bin_state] << " state"
                    << out.Line ()));
#endif

            if (++bin_start >= bin_end) bin_start -= size;
            // Process the rest of the bytes in a loop to reduce setup overhead.
            switch (bin_state) {
      case kBInStateAddress: {
        hash = Hash16(b, hash);
        PRINTF("\nhash:0x%x", hash)
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
        PRINTF("\nCurrent Op is \"%s\"", op->name)

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

          // PRINT_BSQ ("\nFound Op with params ", params)

          result = CrabsScanHeader(crabs, params);
          if (result) {
#if DEBUG_SCRIPT2_EXPR
            PRINTF("CCrabs::Error reading address.");
#endif
            return CrabsForceDisconnect(crabs, kErrorImplementation);
          }

          operand = crabs->operand;
          if (!operand) {
#if DEBUG_SCRIPT2_EXPR
            PRINTF("\nNull operand found!");
#endif
            return CrabsForceDisconnect(crabs, kErrorInvalidOperand);
          }
          header = op->in;
          crabs->params_left = *header;
          crabs->header = header;        //< +1 to bypass the number_ of params
          crabs->header_start = header;  //< Used to utf current header.
          CrabsEnterState(crabs, kBInStatePackedArgs);
          bin_state = kBInStatePackedArgs;
          type = *(++crabs->header);  //< Setup to read first type.
#if DEBUG_SCRIPT2_EXPR
          PRINTF("\nNext AsciiType to scan:\'"
                 << TypeStrand(type) << "\' with alignment "
                 << TypeAlign(slot_start, type) << '.');
#endif
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
#if DEBUG_SCRIPT2_EXPR
          PRINTF("\nBSQ successfully scanned.");
#endif

          break;
        }
        hash = Hash16(b, hash);
#if DEBUG_SCRIPT2_EXPR
                    Print () << "\nhash:" << PrintHex (hash));
#endif

                    // Switch to next state
                    if (type <= kADR) {
                      if (type < kADR) {  // Address type.
#if DEBUG_SCRIPT2_EXPR
                        Write("\nScanning address.");
#endif
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
                      PRINTF("\nScanning kSTR with max length %u",
                             (uint)bytes_left);
                      CrabsEnterState(crabs, kBInStatePackedUTF8);
                      bin_state = kBInStatePackedUTF8;
                      break;
                    } else if (type < kDBL) {  // Plain-old-data type.
                      bytes_left = TypeFixedSize(type);
                      PRINTF("\nScanning POD with bytes_left:%u",
                             (uint)bytes_left);
                      if (bytes_left == 1) {
                        // No need to enter a state because there is only one
                        // UI1 to parse and we already have the UI1 loaded.
                        PRINTF(
                            "\nDone scanning without state change "
                            "for \"%s\"",
                            TypeStrand(type))
                        // Setup to read the next type.
                        type = *(++crabs->header);
#if DEBUG_SCRIPT2_EXPR
                        PRINTF("\nNext AsciiType to scan:\'"
                               << TypeStrand(type) << "\' with alignment "
                               << TypeAlign(slot_start, type) << '.');
#endif
                        slot_start =
                            TypeAlignUpPointer<>(slot_start, (SI4)type);
                        break;
                      }
                      CrabsEnterState(crabs, kBInStatePackedPod);
                      bin_state = kBInStatePackedPod;
                      break;
                    } else if (type < UVI) {  // Varint type.
#if DEBUG_SCRIPT2_EXPR
                      Write("\nScanning Varint.");
#endif
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
#if DEBUG_SCRIPT2_EXPR
                      Write("\nScanning TObject.");
#endif
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
        hash = Hash16(b, hash);
#if DEBUG_SCRIPT2_EXPR
        PRINTF("\nhash:" << PrintHex(hash));
#endif
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
#if DEBUG_SCRIPT2_EXPR
          PRINTF("\nNext AsciiType to scan:\'"
                 << TypeStrand(type) << "\' with alignment "
                 << TypeAlign(slot_start, type) << '.');
#endif
          slot_start = TypeAlignUpPointer<>(slot_start, (SI4)type);
          break;
        }
        --bytes_left;
        break;
      }
      case kBInStatePackedUTF16: {
        hash = Hash16(b, hash);
#if DEBUG_SCRIPT2_EXPR
        Write("\nhash:" << PrintHex(hash));
#endif
        CrabsExitState(crabs);
        break;
      }
      case kBInStatePackedUTF32: {
        hash = Hash16(b, hash);
#if DEBUG_SCRIPT2_EXPR
        Write("\nhash:" << PrintHex(hash));
#endif
        CrabsExitState(crabs);
        break;
      }
      case kBInStatePackedVarint: {
        hash = Hash16(b, hash);
#if DEBUG_SCRIPT2_EXPR
        Write("\nhash:" << PrintHex(hash));
#endif
        // When verifying a varint, there is a max number_ of bytes for
        // the type (3, 5, or 9) but the varint may be complete before
        // this number_ of bytes. We're just basically counting down and
        // looking for an overflow situation.
        // Hash UI1.

        if (bytes_left == 1) {
#if DEBUG_SCRIPT2_EXPR
          Write("Checking last UI1:");
#endif

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
#if DEBUG_SCRIPT2_EXPR
          Write("\nDone scanning varint: ");
#endif
          // Setup to read the next type.
          type = *(++header);
#if DEBUG_SCRIPT2_EXPR
          PRINTF("\nNext AsciiType to scan:\'"
                 << TypeStrand(type) << "\' with alignment "
                 << TypeAlign(slot_start, type) << '.');
#endif
          slot_start = TypeAlignUpPointer<>(slot_start, (SI4)type);
        }
        --bytes_left;
        break;
      }
      case kBInStatePackedObj: {
        hash = Hash16(b, hash);
#if DEBUG_SCRIPT2_EXPR
        Write("\nhash:" << PrintHex(hash));
#endif
        if (bytes_shift >= shift_bits) {
                  // Done shifting.
#if DEBUG_SCRIPT2_EXPR
          PRINTF("\nLoading object of size:" << bytes_left);
#endif
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
#if DEBUG_SCRIPT2_EXPR
          Write("\nError: expecting hash:" << PrintHex(hash) << " and found "
                                           << PrintHex(found_hash));
#endif
          return CrabsForceDisconnect(crabs, kErrorInvalidHash);
        }
#if DEBUG_SCRIPT2_EXPR
        Write("\nSuccess reading hash!");
#endif
        hash = kPrime2Unsigned;  //< Reset hash to largest 16-bit prime.
#if DEBUG_SCRIPT2_EXPR
        Write("\nResetting hash.\n");
#endif
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
#if DEBUG_SCRIPT2_EXPR
          Write("\nResetting hash.");
#endif
          hash = kPrime2Unsigned;  //< Reset hash to largest 16-bit prime.
          crabs->operand = crabs->root;
          crabs->result = nullptr;
          bin_state = kBInStateAddress;
          CrabsSetState(crabs, kBInStateAddress);
#if DEBUG_SCRIPT2_EXPR
          PRINTF("\nRoot scope: \"" << OperandName(crabs->operand) << '\"');
#endif
        }
        break;
      }
      case kBInStateLocked: {
#if DEBUG_SCRIPT2_EXPR
        Write("Locked");
#endif
        break;
      }
      default: {
        hash = Hash16(b, hash);
#if DEBUG_SCRIPT2_EXPR
        PRINTF("\nhash:" << PrintHex(hash));
#endif
        // parsing plain-old-data.
        if (!bytes_left) {
#if DEBUG_SCRIPT2_EXPR
          Write("... done!");
#endif
          CrabsExitState(crabs);
          bin_state = crabs->bin_state;

          // Setup to read the next type.
          type = *(++header);
#if DEBUG_SCRIPT2_EXPR
          PRINTF("\nNext AsciiType to scan:\'"
                 << TypeStrand(type) << "\' with alignment "
                 << TypeAlign(slot_start, type) << '.');
#endif
          slot_start = TypeAlignUpPointer<>(slot_start, (SI4)type);
          break;
        }
        --bytes_left;
                // b = input->Pull ();
#if DEBUG_SCRIPT2_EXPR
        PRINTF("\nLoading next UI1:" << PrintHex(b));
#endif
        hash = Hash16(b, hash);
        *bin_start = b;
        ++bin_start;
        break;
      }
            }
  }
  //
  crabs->hash = hash;
  crabs->bytes_left = bytes_left;
  bin->begin = (SI4)Size(bin_begin, bin_start);
  return nullptr;
}

BOL CrabsContains(CCrabs* crabs, void* address) {
  if (address < reinterpret_cast<UIW*>(crabs)) return false;
  if (address > CrabsEndAddress(crabs)) return false;
  return true;
}

const Op* CrabsScanHeader(CCrabs* crabs, const SI4* header) {
  if (crabs->stack_count >= crabs->stack_size) {
    // Handle overflow cleanup:
    return CrabsError(crabs, kErrorStackOverflow, header);
  }

  return 0;
}

const SI4* CrabsHeaderStack(CCrabs* crabs) {
  return reinterpret_cast<const SI4*>(reinterpret_cast<CH1*>(crabs) +
                                      sizeof(CCrabs) + crabs->stack_count);
}

void CrabsClose(CCrabs* crabs) {
#if DEBUG_SCRIPT2_EXPR
  Write("\nClosing expression.");
#endif
  crabs->stack_count = 1;
}

void CrabsCancel(CCrabs* crabs) {
#if DEBUG_SCRIPT2_EXPR
  Write("\nCanceling expression.");
#endif
  crabs->stack_count = 1;
  crabs->bin_state = kBInStateAddress;
  // CrabsPush (crabs->root);
}

void CrabsClear(CCrabs* crabs) {
  // Erase the socket by writing zeros to it.

  BIn* bin = CrabsBIn(crabs);

  CH1 *begin = BInBegin(bin), *stop = begin + bin->size,
       *begin = begin + bin->begin, *stop = begin + bin->stop;

  // SI4 buffer_space = SlotSpace (begin, stop, size);

  if (begin == stop) return;  //< Nothing to do.
  if (begin > stop) {
    SocketFill(begin, stop - begin);
    SocketFill(begin, begin - begin);
    return;
  }
  SocketFill(begin, stop - begin);
  bin->begin = (SI4)Size(crabs, begin);
  bin->stop = (SI4)Size(crabs, begin + 1);
}

void CrabsRingBell(CCrabs* crabs, const CH1* address) {
  BOutRingBell(CrabsBOut(crabs), address);
}

void CrabsAckBack(CCrabs* crabs, const CH1* address) {
  BOutAckBack(CrabsBOut(crabs), address);
}

const Op* CrabsForceDisconnect(CCrabs* crabs, Error error) {
  crabs->bin_state = kBInStateDisconnected;
  return CrabsError(crabs, error);
}

const Op* CrabsQuery(CCrabs* crabs, const Op& op) {
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

const Op* CrabsQuery(CCrabs* crabs, const Op* op) {
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
UTF1& PrintCrabsStack(UTF1& utf, CCrabs* crabs) {
  ASSERT(crabs);

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

UTF1& PrintCrabs(UTF1& utf, CCrabs* crabs) {
  ASSERT(crabs);

  utf << Line('~', 80) << "\nStack:    " << CHex<UIW>(crabs) << '\n'
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

#endif  //> #if SEAM >= SCRIPT2_14
