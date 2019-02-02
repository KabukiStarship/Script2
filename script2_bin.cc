/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_bin.cc
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
#include "c_bin.h"

#include "bout.h"
#include "c_asciidata.h"
#include "c_bsq.h"
#include "c_hash.h"
#include "c_socket.h"
#include "hex.h"
#include "line.h"
#include "slot.h"

#if SEAM == SCRIPT2_14
#define CLEAR(begin, stop) \
  while (begin <= stop) *begin++ = ' ';
#define PRINT_BSQ(header, bsq) Console<>().Out() << header << '\n' << Bsq(bsq);
#define PRINT_BIN(header, bin) Console<>().Out() << header << '\n' << bin;
#else
#define CLEAR(begin, stop)
#define PRINT_BSQ(header, bsq)
#define PRINT_BIN(header, bout)
#endif

namespace _ {

inline CH1* BInBegin(BIn* bin) {
  return reinterpret_cast<CH1*>(bin) + sizeof(BIn);
}

CH1* BInEnd(BIn* bin) {
  ASSERT(bin)
  return reinterpret_cast<CH1*>(bin) + bin->size;
}

SIW SlotLength(CH1* begin, CH1* stop, UIW size) {
  ASSERT(begin < stop)
  return stop - begin;
}

SIW SlotSpace(CH1* begin, CH1* stop, UIW size) {
  ASSERT(begin < stop)
  return size - (stop - begin);
}

SI4 BInSpace(BIn* bin) {
  ASSERT(bin)
  CH1* txb_ptr = reinterpret_cast<CH1*>(bin);
  return (SI4)SlotSpace(txb_ptr + bin->begin, txb_ptr + bin->stop, bin->size);
}

SI4 BinBufferLength(BIn* bin) {
  ASSERT(bin)
  CH1* begin = BInBegin(bin);
  return (SI4)SlotLength(begin + bin->begin, begin + bin->stop, bin->size);
}

#if USING_SCRIPT2_TEXT
const CH1** BInStateStrands() {
  static const CH1* kStateStrands[] = {
      "Address",       //< 0
      "Args",          //< 1
      "UTF-8",         //< 2
      "UTF-16",        //< 3
      "UTF-32",        //< 4
      "Varint",        //< 5
      "CObj",           //< 6
      "Hash",          //< 7
      "Error",         //< 8
      "Disconnected",  //< 9
      "ACK",           //< 10
      "Locked",        //< 11
      "POD"            //< 12
  };
  return kStateStrands;
}
#endif

/* Used to return an erroneous result from a B-Output.
@param error The error type.
@return Returns a Static Error Op Result. */
inline const Op* BInError(BIn* bin, Error error) {
  PRINTF("\nBIn %s error!", ErrorStrand(error))
  return reinterpret_cast<const Op*>(error);
}

/* Used to return an erroneous result from a B-Output.
    @param  bin    The source BIn.
    @param  error   The error type.
    @param  header  The B-Sequence Header.
    @param  offset  The offset to the type in error in the B-Sequence.
    @param  address The address of the UI1 in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BInError(BIn* bin, Error error, const SI4* header) {
  PRINTF("\nBIn %s error!", ErrorStrand(error))
  return reinterpret_cast<const Op*>(error);
}

/* Used to return an erroneous result from a B-Output.
    @param  bin    The source BIn.
    @param  error   The error type.
    @param  header  The B-Sequence Header.
    @param  offset  The offset to the type in error in the B-Sequence.
    @param  address The address of the UI1 in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BInError(BIn* bin, Error error, const SI4* header,
                          SI4 offset) {
  PRINTF("\nBIn %s error!", ErrorStrand(error))
  return reinterpret_cast<const Op*>(error);
}

/* Used to return an erroneous result from a B-Output.
    @param  bin    The source BIn.
    @param  error   The error type.
    @param  header  The B-Sequence Header.
    @param  offset  The offset to the type in error in the B-Sequence.
    @param  address The address of the UI1 in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BInError(BIn* bin, Error error, const SI4* header, SI4 offset,
                          CH1* address) {
  PRINTF("\nBIn %s error!", ErrorStrand(error))
  return reinterpret_cast<const Op*>(error);
}

BIn* BInInit(UIW* socket, SI4 size) {
  ASSERT(socket);
  ASSERT(size >= kSlotSizeMin);

  BIn* bin = reinterpret_cast<BIn*>(socket);
  bin->size = size - sizeof(BIn);
  bin->begin = 0;
  bin->stop = 0;
  bin->read = 0;

#if SCRIPT2_DEBUG == 1
  MemoryClear(BInBegin(bin), size);
#endif
  return bin;
}

SI4 BInStreamByte(BIn* bin) {
  CH1 *begin = BInBegin(bin), *stop = begin + bin->size - 1;
  CH1 *open = (CH1*)begin + bin->read, *begin = begin + bin->begin,
      *begin = begin;

  SI4 length = (SI4)((begin < open) ? open - begin + 1
                                    : (stop - begin) + (open - begin) + 2);

  if (length < 1) {
    BInError(bin, kErrorBufferOverflow, Params<1, kSTR>(), 2, begin);
    return -1;
  }
  // UI1 b = *cursor;
  bin->stop = (++begin >= stop) ? static_cast<SI4>(Size(begin, stop))
                                : static_cast<SI4>(Size(begin, begin));
  return 0;
}

BOL BInIsReadable(BIn* bin) { return BinBufferLength(bin) > 0; }

const Op* BInRead(BIn* bin, const SI4* params, void** args) {
  PRINT_BSQ("\nReading ", params)
  PRINT_BIN(" from B-Input:", bin)

  if (!bin) {
    return BInError(bin, kErrorImplementation);
  }
  if (!params) {
    return BInError(bin, kErrorImplementation);
  }
  if (!args) {
    return BInError(bin, kErrorImplementation);
  }
  UI1 ui1;       //< Temp variable.
  UI2 ui2;       //< Temp variable.
  UI4 ui4;       //< Temp variable.
  UI8 ui8;       //< Temp variable.
  CH1* ui1_ptr;  //< Pointer to a kUI1.
  // UI2* ui2_ptr;              //< Pointer to a kUI2.
  UI4* ui4_ptr;              //< Pointer to a kUI4.
  UI8* ui8_ptr;              //< Pointer to a kUI1.
  SI4 type,                  //< The current type being read.
      size,                  //< Size of the ring socket.
      length,                //< Length of the data in the socket.
      count,                 //< Argument length.
      index,                 //< Index in the params.
      arg_index = 0,         //< Index in the args.
      value,                 //< Temp variable.
      num_params = *params;  //< Number of params.
  hash16_t hash;             //< Hash of the incoming data.

  if (num_params == 0) return 0;  //< Nothing to do.

  hash = kPrime2Unsigned;
  size = bin->size;

  CH1 *begin = BInBegin(bin),             //< The beginning of the socket.
      *stop = begin + size - 1,           //< The stop of the socket.
          *begin = begin + bin->begin,    //< The begin of the data.
              *stop = begin + bin->stop;  //< The stop of the data.
                                          // const SI4* param = params + 1;
                                          // //< The current param.

  length = (SI4)SlotLength(begin, stop, size);

  // When we scan, we are reading from the beginning of the Slot socket.

  for (index = 1; index <= num_params; ++index) {
    type = params[index];
    PRINTF("\nparam:%u type:%s start:%i stop:%i length:%u", arg_index + 1,
           TypeStrand(type), (SI4)Size(begin, begin), (SI4)Size(begin, stop),
           length)
    switch (type) {
      case kNIL:
        return BInError(bin, kErrorInvalidType, params, index, begin);
      case kADR:
      case kSTR:  //< _R_e_a_d__S_t_r_i_n_g_-_8____________________
                  // Load buffered-type argument length and increment the index.
        ++num_params;
        count = params[++index];
        //< @todo Replace with pointer arithmetic.
        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<CH1*>(args[arg_index]);
        if (ui1_ptr == nullptr)
          return BInError(bin, kErrorImplementation, params, index, begin);
        PRINTF("\nReading kSTR:0x%p with length:%u", ui1_ptr, count)
        // Read CH1.
        ui1 = *begin;
        hash = Hash16(ui1, hash);
        if (++begin >= stop) begin -= size;
        *ui1_ptr = ui1;
        ++ui1_ptr;
        PRINT(ui1)
        while ((ui1 != 0) && (count != 0)) {
          --count;
          if (count == 0)  //< Reached count:0 before nil-term CH1.
            return BInError(bin, kErrorBufferUnderflow, params, index, begin);
          ui1 = *begin;  // Read UI1 from ring-socket.
          hash = Hash16(ui1, hash);
          if (++begin >= stop) begin -= size;
          *ui1_ptr++ = ui1;  // Write UI1 to destination.
          PRINT(ui1)
        }
        PRINTF("\" success!\n")
        if (type != kADR) {
          *ui1_ptr = 0;
          // No need to hash 0.
        }
        break;
      case kSI1:  //< _R_e_a_d__1__B_y_t_e__T_y_p_e_s________________
      case kUI1:
      case kBOL:
#if USING_SCRIPT2_1_BYTE_TYPES
        if (length-- == 0)
          return BInError(bin, kErrorBufferUnderflow, params, index, begin);

        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<CH1*>(args[arg_index]);
        if (!ui1_ptr) break;

        // Read type;

        // Byte 1
        ui1 = *begin;  //< Read
        PRINTF(" \'%u\', ", ui1)
        hash = Hash16(ui1, hash);            //< Hash
        if (++begin >= stop) begin -= size;  //< Increment
        *ui1_ptr = ui1;                      //< Write
        break;
#else
        return BInError(bin, kErrorInvalidType, params, index, begin);
#endif
      case kSI2:  //< _R_e_a_d__1_6_-_b_i_t__T_y_p_e_s_______________
      case kUI2:
      case kHLF:
#if USING_SCRIPT2_2_BYTE_TYPES
        if (length < 2)
          return BInError(bin, kErrorBufferUnderflow, params, index, begin);
        length -= 2;

        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<CH1*>(args[arg_index]);
        if (!ui1_ptr) break;

        // Read type

        // Byte 1
        ui1 = *begin;                        //< Read
        hash = Hash16(ui1, hash);            //< Hash
        if (++begin >= stop) begin -= size;  //< Increment
        *ui1_ptr = ui1;                      //< Write

        // Byte 2
        ui1 = *begin;                        //< Read
        hash = Hash16(ui1, hash);            //< Hash
        if (++begin >= stop) begin -= size;  //< Increment
        *(ui1_ptr + 1) = ui1;                //< Write
        break;
#else
        return BInError(bin, kErrorInvalidType, params, index, begin);
#endif
      case SVI:  //< _R_e_a_d__S_i_g_n_e_d__V_a_r_i_n_t______________
      case UVI:  //< _R_e_a_d__U_n_s_i_g_n_e_d__V_a_r_i_n_t___________
#if ALU_SIZE <= 16
                 // Load next pointer and increment args.
        ui2_ptr = reinterpret_cast<UI2*>(args[arg_index]);
        if (ui2_ptr == nullptr)
          return BInError(bin, kErrorImplementation, params, index, begin);
        // Scan UI1 1.
        ui1 = *begin;
        if (++begin >= stop) begin -= size;
        hash = Hash16(ui1, hash);
        ui2 = ui1;
        temp = 7;   //< Number of bits to shift ui1 to the left.
        count = 5;  //< The max number_ of Varint4 bytes.
        while (ui1 >> 7 == 0) {
          if (length-- == 0)
            return BInError(bin, kErrorBufferUnderflow, params, index, begin);
          ui1 = *begin;
          if (++begin >= stop) begin -= size;
          hash = Hash16(ui1, hash);
          ui4 |= ((UI4)(ui1 & 0x7F)) << temp;
          //< @todo I'm starting to second guess if we need to mask ui1
          //< because we're packing them up and will overwrite.
          temp += 7;
          if (--count == 0)
            return BInError(bin, kErrorVarintOverflow, params, index, begin);
        }
        if (count == 5)  //< If there is only one UI1 we need to
          ui4 &= 0x7F;   //< mask off the terminating varint bit.
        if (type == SVI) ui4 = TypeUnpackVarint<UI4>(ui4);
        *ui4_ptr = ui4;
        break;
#else
                 // Load next pointer and increment args.
        ui4_ptr = reinterpret_cast<UI4*>(args[arg_index]);
        if (ui4_ptr == nullptr)
          return BInError(bin, kErrorImplementation, params, index, begin);

        // Scan UI1 1.
        ui1 = *begin;
        if (++begin >= stop) begin -= size;
        hash = Hash16(ui1, hash);
        ui4 = ui1;
        ui2 = 7;    //< Number of bits to shift ui1 to the left.
        count = 5;  //< The max number_ of Varint4 bytes.
        while (ui1 >> 7 == 0) {
          if (length-- == 0)
            return BInError(bin, kErrorBufferUnderflow, params, index, begin);
          ui1 = *begin;
          if (++begin >= stop) begin -= size;
          hash = Hash16(ui1, hash);
          ui4 |= ((UI4)(ui1 & 0x7F)) << ui2;
          //< @todo I'm starting to second guess if we need to mask ui1
          //< because we're packing them up and will overwrite.
          ui2 += 7;
          if (--count == 0)
            return BInError(bin, kErrorVarintOverflow, params, index, begin);
        }
        if (count == 5)  //< If there is only one UI1 we need to
          ui4 &= 0x7F;   //< mask off the terminating varint bit.
        if (type == SVI) ui4 = TypeUnpackVarint<UI4>(ui4);
        *ui4_ptr = ui4;
        break;
#endif
      case kint:  //< _R_e_a_d__3_2_-_b_i_t__T_y_p_e_s_______________
      case kUI4:
      case kFLT:
      case kTM4:
#if USING_SCRIPT2_4_BYTE_TYPES
        if (length < 4)
          return BInError(bin, kErrorBufferUnderflow, params, index, begin);
        length -= 4;

        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<CH1*>(args[arg_index]);
        if (!ui1_ptr) break;

        // Read type

        for (value = sizeof(UI4); value > 0; --value) {
          // Byte 1
          ui1 = *begin;                        //< Read
          hash = Hash16(ui1, hash);            //< Hash
          if (++begin >= stop) begin -= size;  //< Increment
          *ui1_ptr++ = ui1;                    //< Write
        }
#else
        return BInError(bin, kErrorInvalidType, params, index, begin);
#endif
      case kTM8:  //< _R_e_a_d__6_4_-_b_i_t__T_y_p_e_s_______________
      case kSI8:
      case kUI8:
      case kDBL:
#if USING_SCRIPT2_8_BYTE_TYPES
        if (length < 8)
          return BInError(bin, kErrorBufferUnderflow, params, index, begin);
        length -= 8;

        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<CH1*>(args[arg_index]);
        if (!ui1_ptr) break;

        // Read type
        for (value = sizeof(UI8); value > 0; --value) {
          // Byte 1
          ui1 = *begin;                        //< Read
          hash = Hash16(ui1, hash);            //< Hash
          if (++begin >= stop) begin -= size;  //< Increment
          *ui1_ptr++ = ui1;                    //< Write
        }
        break;
#else
        return BInError(bin, kErrorInvalidType, params, index, begin);
#endif
      case SV8:  //< _R_e_a_d__V_a_r_i_n_t__8____________________
      case UV8:
        // Load next pointer and increment args.
        ui8_ptr = reinterpret_cast<UI8*>(args[arg_index]);
        if (!ui8_ptr) {
          return BInError(bin, kErrorImplementation, params, index, begin);
        }
        // Scan UI1 1.
        ui1 = *begin;
        if (++begin >= stop) begin -= size;
        hash = Hash16(ui1, hash);
        ui8 = ui1;
        ui2 = 7;    //< Number of bits to shift ui1 to the left.
        count = 9;  //< The max number_ of Varint8 bytes.
        while (ui1 >> 7 == 0) {
          if (length-- == 0)
            return BInError(bin, kErrorBufferUnderflow, params, index, begin);
          ui1 = *begin;
          if (++begin >= stop) begin -= size;
          hash = Hash16(ui1, hash);
          if (count == 1) {
            // Varint 8 differs from Varint 2 and 4 in that on the
            // last UI1, UI1 9 of 9, there is no terminating
            // varint bit.
            ui8 |= ((UI8)(ui1)) << ui2;
            break;
          }
          ui8 |= ((UI8)(ui1 & 0x7F)) << ui2;
          //< @todo I'm starting to second guess if we need to mask
          //< ui1 because we're packing them up and will overwrite.
          ui2 += 7;
          if (--count == 0)
            return BInError(bin, kErrorVarintOverflow, params, index, begin);
        }
        if (count == 9)  //< If there is only one UI1 we need to
          ui8 &= 0x7F;   //< mask off the terminating varint bit.
        if (type == SV8) ui8 = TypeUnpackVarint<UI8>(ui8);
        *ui8_ptr = ui8;
        break;
      case kBSQ:  //< _B_-_S_e_q_u_e_n_c_e__S_t_r_i_n_g______________
#if USING_BSC
        ui1_ptr = reinterpret_cast<CH1*>(args[arg_index]);
        if (ui1_ptr == nullptr)
          return BInError(bin, kErrorImplementation, params, index, begin);
        ui1 = *begin;
#endif
      default: {  //< It's an Array
        PRINTF("\nIt's an array!\n")
#if USING_SCRIPT2_ARRAY
        switch (type & 0x60) {
          case 0: {
            if ((type < kLST) && (type < kMAP))
              return BInError(bin, kErrorInvalidType, params, index, begin);
            if (length < 1)  // 1 UI1 for the width word.
              return BInError(bin, kErrorBufferUnderflow, params, index, begin);

            ui1_ptr = reinterpret_cast<CH1*>(args[arg_index]);
            if (ui1_ptr == nullptr)
              return BInError(bin, kErrorImplementation, params, index, begin);

            ui1 = *begin;
            if (++begin >= stop) begin -= size;
            hash = Hash16(ui1, hash);
            if (ui1 > length - 1)
              return BInError(bin, kErrorBufferOverflow, params, index, begin);
            length = length - count - 1;
            count = (UIW)ui1;
            break;
          }
          case 1: {
            if (length < 2)  // 2 UI1 for the width word.
              return BInError(bin, kErrorBufferUnderflow, params, index, begin);
            length -= 2;
            ui2_ptr = reinterpret_cast<UI2*>(args[arg_index]);
            if (ui2_ptr == nullptr)
              return BInError(bin, kErrorImplementation, params, index, begin);

            for (temp = 0; temp <= sizeof(UI2); temp += 8) {
              ui1 = *begin;
              if (++begin >= stop) begin -= size;
              hash = Hash16(ui1, hash);
              ui2 |= ((UI2)ui1) << temp;
            }
            if (ui2 > length)
              return BInError(bin, kErrorBufferOverflow, params, index, begin);
            length -= count;
            count = (UIW)ui2;
            ui1_ptr = reinterpret_cast<CH1*>(ui2_ptr);
            break;
          }
          case 2: {
            if (length < 4)  // 4 UI1 for the width word.
              return BInError(bin, kErrorBufferUnderflow, params, index, begin);
            length -= 4;
            ui4_ptr = reinterpret_cast<UI4*>(args[arg_index]);
            if (ui4_ptr == nullptr)
              return BInError(bin, kErrorImplementation, params, index, begin);

            for (temp = 0; temp <= sizeof(UI4); temp += 8) {
              ui1 = *begin;
              if (++begin >= stop) begin -= size;
              hash = Hash16(ui1, hash);
              ui4 |= ((UI4)ui1) << temp;
            }
            if (ui4 >= length)
              return BInError(bin, kErrorBufferOverflow, params, index, begin);
            length -= count;
            count = (UIW)ui4;
            ui1_ptr = reinterpret_cast<CH1*>(ui4_ptr);
            break;
          }
          case 3: {  // 8 UI1 for the width word.
            if (length < 9)
              return BInError(bin, kErrorBufferUnderflow, params, index, begin);
            length -= 8;
            ui8_ptr = reinterpret_cast<UI8*>(args[arg_index]);
            if (ui8_ptr == nullptr)
              return BInError(bin, kErrorImplementation, params, index, begin);

            for (temp = 0; temp <= sizeof(UI8); temp += 8) {
              ui1 = *begin;
              if (++begin >= stop) begin -= size;
              hash = Hash16(ui1, hash);
              ui8 |= ((UI8)ui1) << temp;
            }
            if (ui8 > length)
              return BInError(bin, kErrorBufferOverflow, params, index, begin);
            length -= count;
            count = (UIW)ui8;
            ui1_ptr = reinterpret_cast<CH1*>(ui8_ptr);
            break;
          }
          default:
            return BInError(bin, kErrorImplementation, params, index, begin);
        }

        if (length < count)
          return BInError(bin, kErrorBufferOverflow, params, index, begin);
        if (count == 0) break;  //< Not sure if this is an error.
        if (begin + count >= stop) {
          for (; size - count > 0; --count) {
            ui1 = *begin;
            if (++begin >= stop) begin -= size;
            hash = Hash16(ui1, hash);
            *ui1_ptr = ui1;
            ++ui1_ptr;
          }
          stop = begin - 1;
          for (; count > 0; --count) {
            ui1 = *begin;
            if (++begin >= stop) begin -= size;
            hash = Hash16(ui1, hash);
            *ui1_ptr = ui1;
            ++ui1_ptr;
          }
          break;
        }
        for (; count > 0; --count) {
          ui1 = *begin;
          if (++begin >= stop) begin -= size;
          hash = Hash16(ui1, hash);
          *ui1_ptr = ui1;
          ++ui1_ptr;
        }
        break;
#endif  //< SCRIPT2_DEBUG
      }
    }
    ++arg_index;
    PRINTF(" |")
  }
  PRINTF("\nHash expected:0x%x", hash)
  if (length < 2)
    return BInError(bin, kErrorBufferUnderflow, params, index, begin);
  ui2 = *begin;
  if (++begin >= stop) begin -= size;
  ui1 = *begin;
  if (++begin >= stop) begin -= size;
  ui2 |= (((UI2)ui1) << 8);
  PRINTF("found:0x%x", ui2)
  if (hash != ui2)
    return BInError(bin, kErrorInvalidHash, params, index, begin);

  PRINTF("\nDone reading\n")
  CLEAR(begin, stop)

  // Convert pointer back to offset
  bin->begin = (SI4)Size(begin, begin);

  return 0;
}

#if USING_SCRIPT2_TEXT
UTF1& Print(UTF1& utf, BIn* bin) {
  ASSERT(bin);

  SI4 size = bin->size;
  return utf << Line('_', 80) << " size:" << bin->size
             << " start:" << bin->begin << " stop:" << bin->stop
             << " read:" << bin->read
             << Socket(BInBegin(bin), size + sizeof(BIn));
}
#endif

}  // namespace _

#undef PRINTF
#undef PRINT
#undef CLEAR
#undef PRINT_BSQ
#undef PRINT_BIN
#undef DEBUG
#endif  //< #if SEAM >= SCRIPT2_14
