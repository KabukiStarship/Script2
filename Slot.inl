/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Slot.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "Slot.hpp"
//
#include "String.hpp"
#include "Types.h"
#if SEAM == SCRIPT2_CRABS
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
namespace _ {

const Op* ReturnError(Slot* slot, Error error) {
  D_COUT('\n' << TSTRError<CHA>()[error]));
  return OpError(error);
}

const Op* ReturnError(Slot* slot, Error error, const ISC* header) {
  D_COUT('\n' << TSTRError<CHA>()[error]));
  return OpError(error);
}

const Op* ReturnError(Slot* slot, Error error, const ISC* header, IUA offset) {
  D_COUT('\n' << TSTRError<CHA>()[error]));
  return OpError(error);
}

const Op* ReturnError(Slot* slot, Error error, const ISC* header, ISC offset,
                      CHA* address) {
  D_COUT('\n' << TSTRError<CHA>()[error]));
  return OpError(error);
}

Slot::Slot(IUW* socket, ISW size) {
  A_ASSERT(socket);
  A_ASSERT(size >= cSlotSizeMin);
  CHA* l_begin = TPtr<CHA>(socket);
  origin = l_begin;
  origin = l_begin;
  stop = l_begin;
  stop = l_begin + size - 1;
}

Slot::Slot(BIn* bin) {
  A_ASSERT(bin);
  CHA* l_begin = TPtr<CHA>(bin) + sizeof(BIn);
  origin = l_begin;
  origin = l_begin + bin->origin;
  stop = l_begin + bin->stop;
  stop = l_begin + bin->size;
}

Slot::Slot(BOut* bout) {
  A_ASSERT(bout);
  CHA* l_begin = TPtr<CHA>(bout) + sizeof(BIn);
  origin = l_begin;
  origin = l_begin + bout->origin;
  stop = l_begin + bout->stop;
  stop = l_begin + bout->size;
}

void* Slot::Contains(void* address) {
  CHA* origin = TPtr<CHA>(this) + sizeof(Slot);
  if (address < origin) {
    return nullptr;
  }
  CHA* l_end = stop;
  if (address > l_end) {
    return nullptr;
  }
  return address;
}

void Slot::Wipe() {
  CHA *l_begin = TPtr<CHA>(this) + sizeof(Slot), *l_start = origin,
      *l_stop = stop, *temp;
  if (l_start > l_stop) {
    temp = l_start;
    origin = l_stop;
    stop = temp;
  }
  while (origin != stop) *origin++ = 0;
}

const Op* Slot::Write(const ISC* params, void** args) {
  A_ASSERT(params);
  A_ASSERT(args);

  A_ASSERT(false);
  // @todo Write me!
  return nullptr;
}

BOL Slot::IsWritable() {
  CHA* l_stop = origin;
  if (l_stop == origin) {
    if (l_stop != stop) {
      return false;
    }
    return true;
  }
  return origin != stop - 1;
}

BOL Slot::IsReadable() { return origin != stop; }

/*CHA* SlotRead (Slot* slot, CHA* write, void* write_end, CHA* const origin,
                    CHA* const origin, CHA* const stop , CHA* const stop,
                    ISW size) {
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
        ISW top_chunk = stop - stop;
        size -= top_chunk;

        ArrayCopy (target, target_end, origin, top_chunk);
        ArrayCopy (TPtr<CHA>(target) + top_chunk, size,
                    origin);
        return origin + size;
    }
    ArrayCopy (target, target_end, stop, size);
    return origin + size;
}*/

const Op* Slot::Read(const ISC* params, void** args) {
  A_ASSERT(params);
  A_ASSERT(args);
  IUA iua;  //< Temp variable to load most types.
  IUB iub;  //< Temp variable for working with cIUB types.
#if USING_SCRIPT2_4_BYTE_TYPES
  IUC iuc;
#endif
#if USING_SCRIPT2_8_BYTE_TYPES
  IUD iud;  //< Temp cIUD variable.
#endif
  CHA* iua_ptr;              //< Pointer to a cIUA.
  IUB* iub_ptr;              //< Pointer to a cIUB.
  IUC* iuc_ptr;              //< Pointer to a cIUC.
  IUD* iud_ptr;              //< Pointer to a cIUD.
  ISC type,                  //< Current type being read.
      index,                 //< Index in the escape sequence.
      num_params = *params;  //< Number of params.
  ISC offset,                //< Offset to word align the current type.
      length,                //< Length of the data in the socket.
      count,                 //< Argument length.
      size;                  //< Size of the ring socket.

  A_ASSERT(num_params);

  D_COUT("\n\nReading BIn: ");

  CHA *l_begin = origin,          //< Beginning of the socket.
      *l_end = stop,              //< stop of the socket.
          *l_start = origin,      //< origin of the data.
              *l_stop = stop;     //< stop of the data.
  const ISC* param = params + 1;  //< current param.

  size = l_end - l_begin;

  length = SlotLength(l_start, l_stop, size);

  D_COUT("\n\nReading " << length << " bytes.");
  // D_COUT_BSQ (params)
  // When we scan, we are reading from the beginning of the BIn socket.

  for (index = 0; index < num_params; ++index) {
    type = (IUA)*param;
    ++param;
    D_COUT("\nindex:" << index << ":\"" << STRType(type) << "\" start:0x"
                      << TDelta<>(l_begin, start) << " stop:0x"
                      << TDelta<>(l_begin, stop));

    switch (type) {
      case cNIL:
        return ReturnError(this, cErrorInvalidType);
      case cADR:  //< _R_e_a_d__S_t_r_i_n_g_-_1_______________
      case cSTR:
        // Load buffered-type argument length and increment the
        // index.
        count = *param;
        ++param;

        // std::cout << "\nReading CHA with max length " << count;

        // Load next pointer and increment args.
        iua_ptr = TPtr<CHA>(args[index]);
        if (!iua_ptr) {
          break;
        }

        // Read from slot and write to the slot:
        iua = *l_start;
        if (++l_start > l_end) l_start -= size;
        *iua_ptr = iua;
        ++iua_ptr;

        while (iua && count) {
          if (count-- == 0)
            return ReturnError(this, cErrorBufferUnderflow, params, index,
                               l_start);
          D_COUT(iua);

          iua = *l_start;  // Read IUA from ring-socket.
          if (++l_start > l_end) l_start -= size;
          *iua_ptr = iua;  // Write IUA to destination.
          ++iua_ptr;
        }

        D_COUT(" done!\n");

        if (type == 0) {
          *iua_ptr = iua;
        }
        break;
      case cISA:  //< _R_e_a_d__1__B_y_t_e__T_y_p_e_s___________
      case cIUA:
      case cBOL:
#if USING_SCRIPT2_1_BYTE_TYPES
        if (length == 0) {
          return ReturnError(this, cErrorBufferUnderflow, params, index,
                             l_start);
        }
        --length;

        // Read from socket and write to the stack:
        iua = *l_start;
        if (++l_start > l_end) {
          l_start -= size;
        }
        // Load next pointer and increment args.
        iua_ptr = TPtr<CHA>(args[index]);
        if (!iua_ptr) {
          break;
        }
        *iua_ptr = iua;  //< Write
        if (++l_start > l_end) {
          l_start -= size;
        }
        break;
#else
        return ReturnError(this, cErrorInvalidType);
#endif
      case cISB:  //< _R_e_a_d__1_6_-_b_i_t__T_y_p_e_s__________
      case cIUB:
      case cFPB:
#if CPU_SIZE <= 16
      case SVI:
      case UVI:
#endif
#if USING_SCRIPT2_2_BYTE_TYPES
        // Read2ByteType:{
        // Word-align
        offset = AlignUpOffset2(l_start);
        if ((IUW)length < offset + 2) {
          return ReturnError(this, cErrorBufferUnderflow, params, index,
                             l_start);
        }
        length -= (ISC)offset + 2;
        l_start += offset;
        if (l_start > l_end) {
          l_start -= size;
        }
        // Read from socket and write to the stack:
        iub_ptr = TPtr<IUB>(l_start);
        iub = *iub_ptr;
        l_start += sizeof(IUB);
        if (l_start > l_end) {
          l_start -= size;
        }
        // Load next pointer and increment args.
        iub_ptr = TPtr<IUB>(args[index]);
        if (!iub_ptr) {
          break;
        }
        *iub_ptr = iub;
        //}
        break;
#else
        return ReturnError(this, cErrorInvalidType);
#endif
#if USING_SCRIPT2_VARINT2
        goto Read2ByteType;
#else
        return ReturnError(this, cErrorInvalidType);
#endif
#if CPU_SIZE > 16
      case SVI:
      case UVI:
#endif
      case cISC:  //< _R_e_a_d__3_2_-_b_i_t__T_y_p_e_s__________
      case cIUC:
      case cFPC:
#if USING_SCRIPT2_4_BYTE_TYPES
        // Read4ByteType:{
        // Word-align
        offset = AlignUpOffset4(l_start);
        if ((IUW)length < offset + 4) {
          return ReturnError(this, cErrorBufferUnderflow, params, index,
                             l_start);
        }
        length -= (ISC)offset + 4;
        l_start += offset;
        if (l_start > l_end) {
          l_start -= size;  //< Bound
        }
        // Read from socket and write to the stack:
        iuc_ptr = TPtr<IUC>(l_start);
        iuc = *iuc_ptr;          //< Read
        l_start += sizeof(ISC);  //< Increment
        if (l_start > l_end) {
          l_start -= size;  //< Bound
        }
        // Load next pointer and increment args.
        iuc_ptr = TPtr<IUC>(args[index]);
        if (!iuc_ptr) {
          break;
        }
        *iuc_ptr = iua;  //< Write
        break;
//}
#else
        return ReturnError(this, cErrorInvalidType);
#endif
      case cISD:  //< _R_e_a_d__6_4_-_b_i_t__T_y_p_e_s__________
      case cIUD:
      case cFPD:
      case cTME:
#if USING_SCRIPT2_8_BYTE_TYPES
        // Read8ByteType:{
        // Word-align
        offset = AlignUpOffset8(l_start);
        if ((IUW)length < offset + sizeof(ISD)) {
          return ReturnError(this, cErrorBufferUnderflow, params, index,
                             l_start);
        }
        length -= offset + sizeof(ISD);
        l_start += offset;
        if (l_start > l_end) {
          l_start -= size;  //< Bound
        }
        // Read from socket and write to the stack:
        iud_ptr = TPtr<IUD>(l_start);
        iud = *iud_ptr;          //< Read
        l_start += sizeof(IUD);  //< Increment
        if (l_start > l_end) {
          l_start -= size;  //< Bound
        }
        // Load next pointer and increment args.
        iud_ptr = TPtr<IUD>(args[index]);
        if (iud_ptr == 0) break;
        *iud_ptr = iud;  //< Write.
        break;
//}
#else
        return ReturnError(this, cErrorInvalidType);
#endif
      default: {
#if USING_SCRIPT2_OBJ
        count = type >> 5;  //< count is now the array type bits.
        type &= 0x1f;       //< Now type is the type 0-31
        if (count && (type >= cOBJ)) {
          // Can't make arrays out of objects!
          return ReturnError(this, cErrorInvalidType, params, index, l_start);
        }
        // We don't care if it's a multidimensional array anymore.
        iua_ptr = TPtr<CHA>(args[index]);
        if (iua_ptr == nullptr)
          return ReturnError(this, cErrorImplementation, params, index,
                             l_start);
        count &= 0x3;
        switch (count) {
          case 0: {  // It's a 8-bit count.
            if (type >= cLST) {
              // cLST, kBOK, kDIC, and cMAP can't be 8-bit!
              return ReturnError(this, cErrorInvalidType, params, index,
                                 l_start);
            }
            count = (IUW)*iua_ptr;
            break;
          }
          case 1: {  // It's a 16-bit count.
            if (length < 3) {
              return ReturnError(this, cErrorBufferUnderflow, params, index,
                                 l_start);
            }
            count -= 2;
            iub_ptr = TPtr<IUB>(iua_ptr);
            count = (IUW)*iub_ptr;
            if (count > length) {
              return ReturnError(this, cErrorBufferOverflow, params, index,
                                 l_start);
            }
            break;
          }
          case 2: {  // It's a 32-bit count.
            if (length < 5) {
              return ReturnError(this, cErrorBufferUnderflow, params, index,
                                 l_start);
            }
            count -= 4;
            iuc_ptr = TPtr<IUC>(iua_ptr);
            count = (IUW)*iuc_ptr;
            if (count > length) {
              return ReturnError(this, cErrorBufferOverflow, params, index,
                                 l_start);
            }
            break;
          }
          case 3: {  // It's a 64-bit count.
            if (length < 9) {
              return ReturnError(this, cErrorBufferUnderflow, params, index,
                                 l_start);
            }
            count -= 8;
            iud_ptr = TPtr<IUD>(iua_ptr);
            count = (IUW)*iud_ptr;
            if (count > length) {
              return ReturnError(this, cErrorBufferOverflow, params, index,
                                 l_start);
            }
            break;
          }
          default: {
            return ReturnError(this, cErrorImplementation, params, index,
                               l_start);
          }
        }
        if (length < count) {
          return ReturnError(this, cErrorBufferOverflow, params, index,
                             l_start);
        }
        if (!count) {
          return ReturnError(this, cErrorBufferOverflow, params, index,
                             l_start);
        }
        if (l_start + count >= l_end) {
          for (; size - count > 0; --count) {
            iua = *l_start;
            if (++l_start > l_end) {
              l_start -= size;
            }
            *iua_ptr = iua;
            ++iua_ptr;
          }
          l_stop = l_begin - 1;
          for (; count > 0; --count) {
            iua = *l_start;
            if (++l_start > l_end) {
              l_start -= size;
            }
            *iua_ptr = iua;
            ++iua_ptr;
          }
          break;
        }
        for (; count > 0; --count) {
          iua = *l_start;
          if (++l_start > l_end) {
            l_start -= size;
          }
          *iua_ptr = iua;
          ++iua_ptr;
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

const Op* Slot::Write(const CHA* message) { return nullptr; }

#if USING_SCRIPT2_TEXT
UTF1& Slot::Print(UTF1& utf) {
  CHA *l_begin = origin, *l_end = stop;
  return utf << Line('_', 80) << "\nSlot: origin:" << Hex<>(l_begin)
             << " start:" << Hex<>(origin) << "\nstop:" << Hex<>(stop)
             << " end:" << Hex<>(l_end) << Socket(l_begin, l_end);
}
#endif

}  //< namespace _

#endif  //> #if SEAM >= _0_0_4
