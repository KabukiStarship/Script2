/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_slot.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>
#if SEAM >= _0_0_0__13
#include "tslot.h"

#include "casciidata.h"
#include "csocket.h"
#include "tstr.h"

#if SEAM == _0_0_0__13
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

const Op* ReturnError(Slot* slot, Error error) {
  PRINTF("\n%s", ErrorStrings()[error])
  return reinterpret_cast<const Op*>(error);
}

const Op* ReturnError(Slot* slot, Error error, const UIT* header) {
  PRINTF("\n%s", ErrorStrings()[error])
  return reinterpret_cast<const Op*>(error);
}

const Op* ReturnError(Slot* slot, Error error, const UIT* header, UI1 offset) {
  PRINTF("\n%s", ErrorStrings()[error])
  return reinterpret_cast<const Op*>(error);
}

const Op* ReturnError(Slot* slot, Error error, const UIT* header, UIT offset,
                      char* address) {
  PRINTF("\n%s", ErrorStrings()[error])
  return reinterpret_cast<const Op*>(error);
}

Slot::Slot(UIW* socket, UIW size) {
  ASSERT(socket);
  ASSERT(size >= kSlotSizeMin);
  char* l_begin = reinterpret_cast<char*>(socket);
  begin = l_begin;
  begin = l_begin;
  stop = l_begin;
  stop = l_begin + size - 1;
}

Slot::Slot(BIn* bin) {
  ASSERT(bin);
  char* l_begin = reinterpret_cast<char*>(bin) + sizeof(BIn);
  begin = l_begin;
  begin = l_begin + bin->begin;
  stop = l_begin + bin->stop;
  stop = l_begin + bin->size;
}

Slot::Slot(BOut* bout) {
  ASSERT(bout);
  char* l_begin = reinterpret_cast<char*>(bout) + sizeof(BIn);
  begin = l_begin;
  begin = l_begin + bout->begin;
  stop = l_begin + bout->stop;
  stop = l_begin + bout->size;
}

void* Slot::Contains(void* address) {
  char* begin = reinterpret_cast<char*>(this) + sizeof(Slot);
  if (address < begin) {
    return nullptr;
  }
  char* l_end = stop;
  if (address > l_end) {
    return nullptr;
  }
  return address;
}

void Slot::Wipe() {
  char *l_begin = reinterpret_cast<char*>(this) + sizeof(Slot),
       *l_start = begin, *l_stop = stop, *temp;
  if (l_start > l_stop) {
    temp = l_start;
    begin = l_stop;
    stop = temp;
  }
  while (begin != stop) *begin++ = 0;
}

const Op* Slot::Write(const UIT* params, void** args) {
  ASSERT(params);
  ASSERT(args);

  ASSERT(false);
  // @todo Write me!
  return nullptr;
}

BOL Slot::IsWritable() {
  char* l_stop = begin;
  if (l_stop == begin) {
    if (l_stop != stop) {
      return false;
    }
    return true;
  }
  return begin != stop - 1;
}

BOL Slot::IsReadable() { return begin != stop; }

/*char* SlotRead (Slot* slot, char* write, void* write_end, char* const begin,
                    char* const begin, char* const stop , char* const stop,
                    size_t size) {
    if (!slot) {
        return nullptr;
    }
    if (!write) {
        return nullptr;
    }
    if (write > write_end) {
        return nullptr;
    }

    if ((begin > stop) && (begin + size >= stop)) {
        // Calculate upper chunk size.
        size_t top_chunk = stop - stop;
        size -= top_chunk;

        SocketCopy (target, target_end, begin, top_chunk);
        SocketCopy (reinterpret_cast<char*>(target) + top_chunk, size,
                    begin);
        return begin + size;
    }
    SocketCopy (target, target_end, stop, size);
    return begin + size;
}*/

const Op* Slot::Read(const UIT* params, void** args) {
  ASSERT(params);
  ASSERT(args);
  UI1 ui1;  //< Temp variable to load most types.
  UI2 ui2;  //< Temp variable for working with kUI2 types.
#if USING_CRABS_4_BYTE_TYPES
  UI4 ui4;
#endif
#if USING_CRABS_8_BYTE_TYPES
  UI8 ui8;  //< Temp kUI8 variable.
#endif
  char* ui1_ptr;             //< Pointer to a kUI1.
  UI2* ui2_ptr;              //< Pointer to a kUI2.
  UI4* ui4_ptr;              //< Pointer to a kUI4.
  UI8* ui8_ptr;              //< Pointer to a kUI8.
  UIT type,                  //< Current type being read.
      index,                 //< Index in the escape sequence.
      num_params = *params;  //< Number of params.
  ASSERT(num_params);
  UIW offset;  //< Offset to word align the current type.
  SIW length,  //< Length of the data in the socket.
      count,   //< Argument length.
      size;    //< Size of the ring socket.

  PRINTF("\n\nReading BIn: ")

  char *l_begin = begin,          //< Beginning of the socket.
      *l_end = stop,              //< stop of the socket.
          *l_start = begin,       //< begin of the data.
              *l_stop = stop;     //< stop of the data.
  const UIT* param = params + 1;  //< current param.

  size = l_end - l_begin;

  length = SlotLength(l_start, l_stop, size);

  PRINTF("\n\nReading %i bytes.", (int)length)
  // PRINT_BSQ (params)
  // When we scan, we are reading from the beginning of the BIn socket.

  for (index = 0; index < num_params; ++index) {
    type = (UI1)*param;
    ++param;
    PRINTF("\nindex:%u:\"%s\", start:0x%i, stop:0x%i", (uint)index,
           TypeString(type), (int)Size(l_begin, l_start),
           (int)Size(l_begin, l_stop))

    switch (type) {
      case kNIL:
        return ReturnError(this, kErrorInvalidType);
      case kADR:  //< _R_e_a_d__S_t_r_i_n_g_-_1_______________
      case kSTR:
        // Load buffered-type argument length and increment the
        // index.
        count = *param;
        ++param;

        // std::cout << "\nReading char with max length " << count;

        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<char*>(args[index]);
        if (!ui1_ptr) {
          break;
        }

        // Read from slot and write to the slot:
        ui1 = *l_start;
        if (++l_start > l_end) l_start -= size;
        *ui1_ptr = ui1;
        ++ui1_ptr;

        while (ui1 && count) {
          if (count-- == 0)
            return ReturnError(this, kErrorBufferUnderflow, params, index,
                               l_start);
          PRINT(ui1)

          ui1 = *l_start;  // Read UI1 from ring-socket.
          if (++l_start > l_end) l_start -= size;
          *ui1_ptr = ui1;  // Write UI1 to destination.
          ++ui1_ptr;
        }

        PRINTF(" done!\n")

        if (type == 0) {
          *ui1_ptr = ui1;
        }
        break;
      case kSI1:  //< _R_e_a_d__1__B_y_t_e__T_y_p_e_s___________
      case kUI1:
      case kBOL:
#if USING_CRABS_1_BYTE_TYPES
        if (length == 0) {
          return ReturnError(this, kErrorBufferUnderflow, params, index,
                             l_start);
        }
        --length;

        // Read from socket and write to the stack:
        ui1 = *l_start;
        if (++l_start > l_end) {
          l_start -= size;
        }
        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<char*>(args[index]);
        if (!ui1_ptr) {
          break;
        }
        *ui1_ptr = ui1;  //< Write
        if (++l_start > l_end) {
          l_start -= size;
        }
        break;
#else
        return ReturnError(this, kErrorInvalidType);
#endif
      case kSI2:  //< _R_e_a_d__1_6_-_b_i_t__T_y_p_e_s__________
      case kUI2:
      case kHLF:
#if WORD_SIZE <= 16
      case SVI:
      case UVI:
#endif
#if USING_CRABS_2_BYTE_TYPES
        // Read2ByteType:{
        // Word-align
        offset = AlignUpOffset2(l_start);
        if ((UIW)length < offset + 2) {
          return ReturnError(this, kErrorBufferUnderflow, params, index,
                             l_start);
        }
        length -= (UIT)offset + 2;
        l_start += offset;
        if (l_start > l_end) {
          l_start -= size;
        }
        // Read from socket and write to the stack:
        ui2_ptr = reinterpret_cast<UI2*>(l_start);
        ui2 = *ui2_ptr;
        l_start += sizeof(UI2);
        if (l_start > l_end) {
          l_start -= size;
        }
        // Load next pointer and increment args.
        ui2_ptr = reinterpret_cast<UI2*>(args[index]);
        if (!ui2_ptr) {
          break;
        }
        *ui2_ptr = ui2;
        //}
        break;
#else
        return ReturnError(this, kErrorInvalidType);
#endif
#if USING_CRABS_VARINT2
        goto Read2ByteType;
#else
        return ReturnError(this, kErrorInvalidType);
#endif
#if WORD_SIZE > 16
      case SVI:
      case UVI:
#endif
      case kSI4:  //< _R_e_a_d__3_2_-_b_i_t__T_y_p_e_s__________
      case kUI4:
      case kFLT:
      case kTMS:
#if USING_CRABS_4_BYTE_TYPES
        // Read4ByteType:{
        // Word-align
        offset = AlignUpOffset4(l_start);
        if ((UIW)length < offset + 4) {
          return ReturnError(this, kErrorBufferUnderflow, params, index,
                             l_start);
        }
        length -= (UIT)offset + 4;
        l_start += offset;
        if (l_start > l_end) {
          l_start -= size;  //< Bound
        }
        // Read from socket and write to the stack:
        ui4_ptr = reinterpret_cast<UI4*>(l_start);
        ui4 = *ui4_ptr;          //< Read
        l_start += sizeof(SI4);  //< Increment
        if (l_start > l_end) {
          l_start -= size;  //< Bound
        }
        // Load next pointer and increment args.
        ui4_ptr = reinterpret_cast<UI4*>(args[index]);
        if (!ui4_ptr) {
          break;
        }
        *ui4_ptr = ui1;  //< Write
        break;
//}
#else
        return ReturnError(this, kErrorInvalidType);
#endif
      case kSI8:  //< _R_e_a_d__6_4_-_b_i_t__T_y_p_e_s__________
      case kUI8:
      case kDBL:
      case kTME:
#if USING_CRABS_8_BYTE_TYPES
        // Read8ByteType:{
        // Word-align
        offset = AlignUpOffset8(l_start);
        if ((UIW)length < offset + sizeof(SI8)) {
          return ReturnError(this, kErrorBufferUnderflow, params, index,
                             l_start);
        }
        length -= offset + sizeof(SI8);
        l_start += offset;
        if (l_start > l_end) {
          l_start -= size;  //< Bound
        }
        // Read from socket and write to the stack:
        ui8_ptr = reinterpret_cast<UI8*>(l_start);
        ui8 = *ui8_ptr;          //< Read
        l_start += sizeof(UI8);  //< Increment
        if (l_start > l_end) {
          l_start -= size;  //< Bound
        }
        // Load next pointer and increment args.
        ui8_ptr = reinterpret_cast<UI8*>(args[index]);
        if (ui8_ptr == 0) break;
        *ui8_ptr = ui8;  //< Write.
        break;
//}
#else
        return ReturnError(this, kErrorInvalidType);
#endif
      default: {
#if USING_CRABS_OBJ
        count = type >> 5;  //< count is now the array type bits.
        type &= 0x1f;       //< Now type is the type 0-31
        if (count && (type >= kOBJ)) {
          // Can't make arrays out of objects!
          return ReturnError(this, kErrorInvalidType, params, index, l_start);
        }
        // We don't care if it's a multidimensional array anymore.
        ui1_ptr = reinterpret_cast<char*>(args[index]);
        if (ui1_ptr == nullptr)
          return ReturnError(this, kErrorImplementation, params, index,
                             l_start);
        count &= 0x3;
        switch (count) {
          case 0: {  // It's a 8-bit count.
            if (type >= kLST) {
              // kLST, kBOK, kDIC, and kMAP can't be 8-bit!
              return ReturnError(this, kErrorInvalidType, params, index,
                                 l_start);
            }
            count = (UIW)*ui1_ptr;
            break;
          }
          case 1: {  // It's a 16-bit count.
            if (length < 3) {
              return ReturnError(this, kErrorBufferUnderflow, params, index,
                                 l_start);
            }
            count -= 2;
            ui2_ptr = reinterpret_cast<UI2*>(ui1_ptr);
            count = (UIW)*ui2_ptr;
            if (count > length) {
              return ReturnError(this, kErrorBufferOverflow, params, index,
                                 l_start);
            }
            break;
          }
          case 2: {  // It's a 32-bit count.
            if (length < 5) {
              return ReturnError(this, kErrorBufferUnderflow, params, index,
                                 l_start);
            }
            count -= 4;
            ui4_ptr = reinterpret_cast<UI4*>(ui1_ptr);
            count = (UIW)*ui4_ptr;
            if (count > length) {
              return ReturnError(this, kErrorBufferOverflow, params, index,
                                 l_start);
            }
            break;
          }
          case 3: {  // It's a 64-bit count.
            if (length < 9) {
              return ReturnError(this, kErrorBufferUnderflow, params, index,
                                 l_start);
            }
            count -= 8;
            ui8_ptr = reinterpret_cast<UI8*>(ui1_ptr);
            count = (UIW)*ui8_ptr;
            if (count > length) {
              return ReturnError(this, kErrorBufferOverflow, params, index,
                                 l_start);
            }
            break;
          }
          default: {
            return ReturnError(this, kErrorImplementation, params, index,
                               l_start);
          }
        }
        if (length < count) {
          return ReturnError(this, kErrorBufferOverflow, params, index,
                             l_start);
        }
        if (!count) {
          return ReturnError(this, kErrorBufferOverflow, params, index,
                             l_start);
        }
        if (l_start + count >= l_end) {
          for (; size - count > 0; --count) {
            ui1 = *l_start;
            if (++l_start > l_end) {
              l_start -= size;
            }
            *ui1_ptr = ui1;
            ++ui1_ptr;
          }
          l_stop = l_begin - 1;
          for (; count > 0; --count) {
            ui1 = *l_start;
            if (++l_start > l_end) {
              l_start -= size;
            }
            *ui1_ptr = ui1;
            ++ui1_ptr;
          }
          break;
        }
        for (; count > 0; --count) {
          ui1 = *l_start;
          if (++l_start > l_end) {
            l_start -= size;
          }
          *ui1_ptr = ui1;
          ++ui1_ptr;
        }
        break;
#endif
      }
        PRINTF(" |")
    }
  }
  PRINTF("\nDone reading.")
  // SlotWipe (slot);

  // Convert pointer back to offset
  begin = l_start;

  return 0;
}

const Op* Slot::Read(const Op& op, void** args) { return Read(op.in, args); }

const Op* Slot::Write(const Op& op, void** args) { return Write(op.out, args); }

const Op* Slot::Write(Slot& other) { return nullptr; }

const Op* Slot::Write(const char* message) { return nullptr; }

#if USING_CRABS_TEXT
UTF1& Slot::Print(UTF1& utf) {
  char *l_begin = begin, *l_end = stop;
  return utf << Line('_', 80) << "\nSlot: begin:" << Hex<>(l_begin)
             << " start:" << Hex<>(begin) << "\nstop:" << Hex<>(stop)
             << " end:" << Hex<>(l_end) << Socket(l_begin, l_end);
}
#endif

}  // namespace _

#endif  //> #if SEAM >= _0_0_4
