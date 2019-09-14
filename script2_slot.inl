/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_slot.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
#include "c_slot.h"

#include "c_typevalue.h"
#include "c_binary.h"
#include "t_strand.h"

#if SEAM == SCRIPT2_DICTIONARY
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

const Op* ReturnError(Slot* slot, Error error) {
  D_COUT('\n' << TSTRError<CH1>()[error]));
  return reinterpret_cast<const Op*>(error);
}

const Op* ReturnError(Slot* slot, Error error, const SI4* header) {
  D_COUT('\n' << TSTRError<CH1>()[error]));
  return reinterpret_cast<const Op*>(error);
}

const Op* ReturnError(Slot* slot, Error error, const SI4* header, UI1 offset) {
  D_COUT('\n' << TSTRError<CH1>()[error]));
  return reinterpret_cast<const Op*>(error);
}

const Op* ReturnError(Slot* slot, Error error, const SI4* header, SI4 offset,
                      CH1* address) {
  D_COUT('\n' << TSTRError<CH1>()[error]));
  return reinterpret_cast<const Op*>(error);
}

Slot::Slot(UIW* socket, SI4 size) {
  A_ASSERT(socket);
  A_ASSERT(size >= kSlotSizeMin);
  CH1* l_begin = reinterpret_cast<CH1*>(socket);
  origin = l_begin;
  origin = l_begin;
  stop = l_begin;
  stop = l_begin + size - 1;
}

Slot::Slot(BIn* bin) {
  A_ASSERT(bin);
  CH1* l_begin = reinterpret_cast<CH1*>(bin) + sizeof(BIn);
  origin = l_begin;
  origin = l_begin + bin->origin;
  stop = l_begin + bin->stop;
  stop = l_begin + bin->size;
}

Slot::Slot(BOut* bout) {
  A_ASSERT(bout);
  CH1* l_begin = reinterpret_cast<CH1*>(bout) + sizeof(BIn);
  origin = l_begin;
  origin = l_begin + bout->origin;
  stop = l_begin + bout->stop;
  stop = l_begin + bout->size;
}

void* Slot::Contains(void* address) {
  CH1* origin = reinterpret_cast<CH1*>(this) + sizeof(Slot);
  if (address < origin) {
    return nullptr;
  }
  CH1* l_end = stop;
  if (address > l_end) {
    return nullptr;
  }
  return address;
}

void Slot::Wipe() {
  CH1 *l_begin = reinterpret_cast<CH1*>(this) + sizeof(Slot), *l_start = origin,
      *l_stop = stop, *temp;
  if (l_start > l_stop) {
    temp = l_start;
    origin = l_stop;
    stop = temp;
  }
  while (origin != stop) *origin++ = 0;
}

const Op* Slot::Write(const SI4* params, void** args) {
  A_ASSERT(params);
  A_ASSERT(args);

  A_ASSERT(false);
  // @todo Write me!
  return nullptr;
}

BOL Slot::IsWritable() {
  CH1* l_stop = origin;
  if (l_stop == origin) {
    if (l_stop != stop) {
      return false;
    }
    return true;
  }
  return origin != stop - 1;
}

BOL Slot::IsReadable() { return origin != stop; }

/*CH1* SlotRead (Slot* slot, CH1* write, void* write_end, CH1* const origin,
                    CH1* const origin, CH1* const stop , CH1* const stop,
                    SIW size) {
    if (!slot) {
        return nullptr;
    }
    if (!write) {
        return nullptr;
    }
    if (write > write_end) {
        return nullptr;
    }

    if ((origin > stop) && (origin + size >= stop)) {
        // Calculate upper chunk size.
        SIW top_chunk = stop - stop;
        size -= top_chunk;

        ArrayCopy (target, target_end, origin, top_chunk);
        ArrayCopy (reinterpret_cast<CH1*>(target) + top_chunk, size,
                    origin);
        return origin + size;
    }
    ArrayCopy (target, target_end, stop, size);
    return origin + size;
}*/

const Op* Slot::Read(const SI4* params, void** args) {
  A_ASSERT(params);
  A_ASSERT(args);
  UI1 ui1;  //< Temp variable to load most types.
  UI2 ui2;  //< Temp variable for working with kUI2 types.
#if USING_SCRIPT2_4_BYTE_TYPES
  UI4 ui4;
#endif
#if USING_SCRIPT2_8_BYTE_TYPES
  UI8 ui8;  //< Temp kUI8 variable.
#endif
  CH1* ui1_ptr;              //< Pointer to a kUI1.
  UI2* ui2_ptr;              //< Pointer to a kUI2.
  UI4* ui4_ptr;              //< Pointer to a kUI4.
  UI8* ui8_ptr;              //< Pointer to a kUI8.
  SI4 type,                  //< Current type being read.
      index,                 //< Index in the escape sequence.
      num_params = *params;  //< Number of params.
  SI4 offset,                //< Offset to word align the current type.
      length,                //< Length of the data in the socket.
      count,                 //< Argument length.
      size;                  //< Size of the ring socket.

  A_ASSERT(num_params);

  D_COUT ("\n\nReading BIn: ");

  CH1 *l_begin = origin,           //< Beginning of the socket.
      *l_end = stop,              //< stop of the socket.
          *l_start = origin,       //< origin of the data.
              *l_stop = stop;     //< stop of the data.
  const SI4* param = params + 1;  //< current param.

  size = l_end - l_begin;

  length = SlotLength(l_start, l_stop, size);

  D_COUT ("\n\nReading " << length << " bytes.");
  // D_COUT_BSQ (params)
  // When we scan, we are reading from the beginning of the BIn socket.

  for (index = 0; index < num_params; ++index) {
    type = (UI1)*param;
    ++param;
    D_COUT("\nindex:" << index << ":\"" << STRType(type) << "\" start:0x"
                      << TDelta<>(l_begin, start) << " stop:0x"
                      << TDelta<>(l_begin, stop));

    switch (type) {
      case kNIL:
        return ReturnError(this, kErrorInvalidType);
      case kADR:  //< _R_e_a_d__S_t_r_i_n_g_-_1_______________
      case kSTR:
        // Load buffered-type argument length and increment the
        // index.
        count = *param;
        ++param;

        // std::cout << "\nReading CH1 with max length " << count;

        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<CH1*>(args[index]);
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
          D_COUT(ui1);

          ui1 = *l_start;  // Read UI1 from ring-socket.
          if (++l_start > l_end) l_start -= size;
          *ui1_ptr = ui1;  // Write UI1 to destination.
          ++ui1_ptr;
        }

        D_COUT(" done!\n");

        if (type == 0) {
          *ui1_ptr = ui1;
        }
        break;
      case kSI1:  //< _R_e_a_d__1__B_y_t_e__T_y_p_e_s___________
      case kUI1:
      case kBOL:
#if USING_SCRIPT2_1_BYTE_TYPES
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
        ui1_ptr = reinterpret_cast<CH1*>(args[index]);
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
      case kFP2:
#if ALU_SIZE <= 16
      case SVI:
      case UVI:
#endif
#if USING_SCRIPT2_2_BYTE_TYPES
        // Read2ByteType:{
        // Word-align
        offset = AlignUpOffset2(l_start);
        if ((UIW)length < offset + 2) {
          return ReturnError(this, kErrorBufferUnderflow, params, index,
                             l_start);
        }
        length -= (SI4)offset + 2;
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
#if USING_SCRIPT2_VARINT2
        goto Read2ByteType;
#else
        return ReturnError(this, kErrorInvalidType);
#endif
#if ALU_SIZE > 16
      case SVI:
      case UVI:
#endif
      case kSI4:  //< _R_e_a_d__3_2_-_b_i_t__T_y_p_e_s__________
      case kUI4:
      case kFP4:
      case kTM4:
#if USING_SCRIPT2_4_BYTE_TYPES
        // Read4ByteType:{
        // Word-align
        offset = AlignUpOffset4(l_start);
        if ((UIW)length < offset + 4) {
          return ReturnError(this, kErrorBufferUnderflow, params, index,
                             l_start);
        }
        length -= (SI4)offset + 4;
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
      case kFP8:
      case kTM8:
#if USING_SCRIPT2_8_BYTE_TYPES
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
#if USING_SCRIPT2_OBJ
        count = type >> 5;  //< count is now the array type bits.
        type &= 0x1f;       //< Now type is the type 0-31
        if (count && (type >= kOBJ)) {
          // Can't make arrays out of objects!
          return ReturnError(this, kErrorInvalidType, params, index, l_start);
        }
        // We don't care if it's a multidimensional array anymore.
        ui1_ptr = reinterpret_cast<CH1*>(args[index]);
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
        D_COUT(" |");
    }
  }
  D_COUT("\nDone reading.");
  // SlotWipe (slot);

  // Convert pointer back to offset
  origin = l_start;

  return 0;
}

const Op* Slot::Read(const Op& op, void** args) { return Read(op.in, args); }

const Op* Slot::Write(const Op& op, void** args) { return Write(op.out, args); }

const Op* Slot::Write(Slot& other) { return nullptr; }

const Op* Slot::Write(const CH1* message) { return nullptr; }

#if USING_SCRIPT2_TEXT
UTF1& Slot::Print(UTF1& utf) {
  CH1 *l_begin = origin, *l_end = stop;
  return utf << Line('_', 80) << "\nSlot: origin:" << Hex<>(l_begin)
             << " start:" << Hex<>(origin) << "\nstop:" << Hex<>(stop)
             << " end:" << Hex<>(l_end) << Socket(l_begin, l_end);
}
#endif

}  // namespace _

#endif  //> #if SEAM >= _0_0_4
