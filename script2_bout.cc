/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_bout.cc
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
#include "cargs.h"
#include "casciidata.h"
#include "cbinary.h"
#include "cbout.h"
#include "cbsq.h"
#include "chash.h"
#include "csocket.h"
#include "ctest.h"
#include "slot.h"

#if SEAM == _0_0_0__13
#include "test_debug.inl"
#define PRINT_BOUT(header, bout) \
  Console<>().Out() << "\n" << header << '\n' << bout;
#else
#include "test_release.inl"
#define PRINT_BOUT(header, bout)
#endif

namespace _ {

/* Used to return an erroneous result from a B-Output.

    @param error The error type.
    @return Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, Error error) {
  std::cerr << "\nBOut " << ErrorString(error) << " Error!";
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Output.
    @param  bout    The source BOut.
    @param  error   The error type.
    @param  header  The B-Sequence Header.
    @param  offset  The offset to the type in error in the B-Sequence.
    @param  address The address of the UI1 in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, Error error, const UIT* header) {
  std::cerr << "\nBOut " << ErrorString(error) << " Error!";
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Output.
    @param  bout    The source BOut.
    @param  error   The error type.
    @param  header  The B-Sequence Header.
    @param  offset  The offset to the type in error in the B-Sequence.
    @param  address The address of the UI1 in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, Error error, const UIT* header,
                           UIT offset) {
  std::cerr << "\nBOut " << ErrorString(error) << " Error!";
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Output.
    @param  bout    The source BOut.
    @param  error   The error type.
    @param  header  The B-Sequence Header.
    @param  offset  The offset to the type in error in the B-Sequence.
    @param  address The address of the UI1 in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, Error error, const UIT* header,
                           UIT offset, char* address) {
  std::cerr << "\nBOut " << ErrorString(error) << " Error!";
  return reinterpret_cast<const Op*>(1);
}

const char** BOutStateStrings() {
  static const char* strings[] = {"WritingState", "kBInStateLocked"};
  return strings;
}

char* BOutBuffer(BOut* bout) {
  ASSERT(bout);
  return reinterpret_cast<char*>(bout) + sizeof(BOut);
}

BOut* BOutInit(UIW* socket, UIT size) {
  if (size < kSlotSizeMin) return nullptr;
  if (socket == nullptr) return nullptr;

  BOut* bout = reinterpret_cast<BOut*>(socket);
  // bout->size  = size - sizeof (BIn); //< Not sure why I did that?
  bout->size = size;
  bout->begin = 0;
  bout->stop = 0;
  bout->read = 0;

#if SEAM_MAJOR == 0 && SEAM_MINOR == 2
  MemoryClear(BOutBuffer(bout), size);
#endif
  return bout;
}

UIT BOutSpace(BOut* bout) {
  if (!bout) {
    return 0;
  }
  char* txb_ptr = reinterpret_cast<char*>(bout);
  return (uint)SlotSpace(txb_ptr + bout->begin, txb_ptr + bout->stop,
                         bout->size);
}

UIT BOutBufferLength(BOut* bout) {
  if (!bout) {
    return 0;
  }
  char* begin = BOutBuffer(bout);
  return (uint)SlotLength(begin + bout->begin, begin + bout->stop, bout->size);
}

char* BOutEndAddress(BOut* bout) {
  return reinterpret_cast<char*>(bout) + (4 * sizeof(UIT)) + bout->size;
}

int BOutStreamByte(BOut* bout) {
  char *begin = BOutBuffer(bout), *stop = begin + bout->size;
  char *open = (char*)begin + bout->read, *begin = begin + bout->begin,
       *begin = begin;

  SIW length = (int)(begin < open) ? open - begin + 1
                                   : (stop - begin) + (open - begin) + 2;

  if (length < 1) {
    BOutError(bout, kErrorBufferOverflow, Params<1, kSTR>(), 2, begin);
    return -1;
  }
  // UI1 b = *cursor;
  bout->stop = (++begin > stop) ? static_cast<UIT>(Size(begin, stop))
                                : static_cast<UIT>(Size(begin, begin));
  return 0;
}

const Op* BOutWrite(BOut* bout, const UIT* params, void** args) {
  PRINT_BSQ("\n\nWriting ", params)
  enum {
    kBOutBufferSize = 1024,
    kBOutBufferSizeWords = kBOutBufferSize >> kWordBitCount
  };
  PRINT_BOUT(" to B-Output:", bout)

  ASSERT(bout);
  ASSERT(params);
  ASSERT(args);

  // Temp variables packed into groups of 8 bytes for memory alignment.
  UI1  // type,
      ui1;
#if USING_CRABS_2_BYTE_TYPES
  UI2 ui2;
#endif
#if USING_CRABS_4_BYTE_TYPES
  UI4 ui4;
#endif
#if USING_CRABS_8_BYTE_TYPES
  UI8 ui8;
#endif

  UIT num_params,  //< Num params in the b-sequence.
      type,        //< Current type.
      size,        //< Size of the socket.
      space,       //< Space in the socket.
      index,       //< Index in the params.
      arg_index,   //< Index in the args.
      length,      //< Length of a type to write.
      value;       //< Temp variable.
  num_params = params[0];
  if (num_params == 0) {
    return 0;  //< Nothing to do.
  }
  arg_index = 0;
  size = bout->size;
  const UIT* param =
      params;  //< Pointer to the current param.
               //* bsc_param;          //< Pointer to the current kBSQ param.
  // Convert the socket offsets to pointers.
  char *begin = BOutBuffer(bout),          //< Beginning of the socket.
      *stop = begin + size,                //< End of the socket.
          *begin = begin + bout->begin,    //< Start of the data.
              *stop = begin + bout->stop;  //< Stop of the data.
  const char* ui1_ptr;                     //< Pointer to a 1-UI1 type.
#if USING_CRABS_2_BYTE_TYPES
  const UI2* ui2_ptr;  //< Pointer to a 2-UI1 type.
#endif
#if USING_CRABS_4_BYTE_TYPES
  const UI4* ui4_ptr;  //< Pointer to a 4-UI1 type.
#endif
#if USING_CRABS_8_BYTE_TYPES
  const UI8* ui8_ptr;  //< Pointer to a 8-UI1 type.
#endif
  UI2 hash = kPrime2Unsigned;  //< Reset hash to largest 16-bit prime.

  space = (UIT)SlotSpace(begin, stop, size);

  // Check if the socket has enough room.
  if (space == 0) return BOutError(bout, kErrorBufferOverflow);
  --space;
  length = params[0];  //< Load the max char length.
  ++param;

  // Write data.
  for (index = 1; index <= num_params; ++index) {
    type = params[index];
    PRINTF("\nparam: %u type: %s start:%i stop:%i space: %u", arg_index + 1,
           TypeString(type), (int)Size(begin, begin), (int)Size(begin, stop),
           space)
    switch (type) {
      case kNIL:
        break;

      case kADR:  //< _W_r_i_t_e__A_d_d_r_e_s_s__S_t_r_i_n_g___________
      case kSTR:  //< _W_r_i_t_e__U_T_F_-_8__S_t_r_i_n_g______________
        if (space == 0)
          return BOutError(bout, kErrorBufferOverflow, params, index, begin);
        if (type != kADR) {
          // We might not need to write anything if it's an kADR with
          // nil string_.
          length = params[++index];  //< Load the max char length.
          ++num_params;
        } else {
          length = kAddressLengthMax;
        }
        // Load the source data pointer and increment args.fs
        ui1_ptr = reinterpret_cast<const char*>(args[arg_index]);
        PRINTF("\"%p", ui1_ptr);

        // We know we will always have at least one nil-term char.
        ui1 = *ui1_ptr;
        while (ui1 != 0) {
          if (space-- == 0)
            return BOutError(bout, kErrorBufferOverflow, params, index, begin);
          hash = Hash16(ui1, hash);

          *stop = ui1;  // Write UI1
          if (++stop >= stop) stop -= size;
          ++ui1_ptr;
          ui1 = *ui1_ptr;  // Read UI1.
        }
        if (type != kADR) {  //< 1 is faster to compare than 2
                             // More likely to have kADR than kSTR
          *stop = 0;         // Write nil-term char.
          if (++stop >= stop) stop -= size;
          break;
        }

        break;
      case kSI1:  //< _W_r_i_t_e__8_-_b_i_t__T_y_p_e_s_______________
      case kUI1:
      case kBOL:
#if USING_CRABS_1_BYTE_TYPES
        // Check if the socket has enough room.
        if (space-- == 0)
          return BOutError(bout, kErrorBufferOverflow, params, index, begin);

        // Load pointer and read data to write.
        ui1_ptr = reinterpret_cast<const char*>(args[arg_index]);
        ui1 = *ui1_ptr;

        // Write data.
        *stop = ui1;
        hash = Hash16(ui1, hash);
        if (++stop >= stop) stop -= size;
        break;
#else
        return BOutError(bout, kErrorInvalidType);
#endif
      case kSI2:  //< _W_r_i_t_e__1_6_-_b_i_t__T_y_p_e_s______________
      case kUI2:
      case kHLF:
#if USING_CRABS_2_BYTE_TYPES
        // Align the socket to a word boundary and check if the
        // socket has enough room.
        if (space < sizeof(UI2))
          return BOutError(bout, kErrorBufferOverflow, params, index, begin);
        space -= sizeof(UI2);

        // Load pointer and value to write.
        ui2_ptr = reinterpret_cast<UI2*>(args[arg_index]);
        ui2 = *ui2_ptr;

        // Write data.

        // Byte 1
        ui1 = (UI1)ui2;
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = Hash16(ui1, hash);

        // Byte 2
        ui1 = (UI1)(ui2 >> 8);
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = Hash16(ui1, hash);
        break;
#else
        return BOutError(bout, kErrorInvalidType);
#endif  // USING_CRABS_2_BYTE_TYPES
#if WORD_SIZE <= 16
      case SVI:  //< _W_r_i_t_e__2_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        ui2_ptr = reinterpret_cast<const UI2*>(args[arg_index]);
        ui2 = *ui2_ptr;
        // We are using the same code to utf both signed and unsigned
        // varints. In order to convert from a negative 2's complement
        // signed integer to a transmittable format, we need to invert
        // the bits and add 1. Then we just shift the bits left one and
        // put the sign bit in the LSB.
        ui2 = TypePackVarint<UI2>(ui2);
        goto WriteVarint2;
      case UVI:  //< _W_r_i_t_e__2_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load next pointer value to write.
        ui2_ptr = reinterpret_cast<const UI2*>(args[arg_index]);
        if (ui2_ptr == nullptr)
          return BOutError(bout, kErrorImplementation, params, index, begin);
        ui2 = *ui2_ptr;

      WriteVarint2 : {
        // Byte 1
        if (space-- == 0)
          return BOutError(bout, kErrorBufferOverflow, params, index, begin);
        ui1 = ui2 & 0x7f;
        ui2 = ui2 >> 7;
        if (ui2 == 0) {
          ui1 |= 0x80;
          *stop = ui1;
          if (++stop >= stop) stop -= size;
          hash = Hash16(ui1, hash);
          break;
        }
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = Hash16(ui1, hash);

        // Byte 2
        if (--space == 0)
          return BOutError(bout, kErrorBufferOverflow, params, index, begin);
        ui1 = ui2 & 0x7f;
        ui2 = ui2 >> 7;
        if (ui2 == 0) {
          ui1 |= 0x80;
          *stop = ui1;
          if (++stop >= stop) stop -= size;
          hash = Hash16(ui1, hash);
          break;
        }
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = Hash16(ui1, hash);

        // Byte 3
        if (--space == 0)
          return BOutError(bout, kErrorBufferOverflow, params, index, begin);
        ui1 = ui2 & 0x7f;
        ui1 |= 0x80;
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = Hash16(ui1, hash);
      } break;
#else
      case SVI:  //< _W_r_i_t_e__4_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        ui4_ptr = reinterpret_cast<const UI4*>(args[arg_index]);
        ui4 = *ui4_ptr;
        ui4 = TypePackVarint<UI4>(ui4);
        goto WriteVarint4;
      case UVI:  //< _W_r_i_t_e__4_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load the 4-UI1 type to write to the socket.
        ui4_ptr = reinterpret_cast<const UI4*>(args[arg_index]);
        ui4 = *ui4_ptr;
      WriteVarint4 : {  //< Optimized manual do while loop.
        ui2 = 5;
        if (space == 0)  //< @todo Benchmark to space--
          return BOutError(bout, kErrorBufferOverflow, params, index, begin);
        --space;  //< @todo Benchmark to space--
        ui1 = ui4 & 0x7f;
        ui4 = ui4 >> 7;
        if (ui4 == 0) {
          ui1 |= 0x80;
          *stop = ui1;
          if (++stop >= stop) stop -= size;
          hash = Hash16(ui1, hash);
          break;
        }
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = Hash16(ui1, hash);
        // This wont happen I don't think.
        // if (--ui2 == 0)
        //    return BOutError (kErrorVarintOverflow, params, index,
        //                       begin);

        goto WriteVarint4;
      } break;
#endif
      case kSI4:  //< _W_r_i_t_e__3_2_-_b_i_t__T_y_p_e_s______________
      case kUI4:
      case kFLT:
      case kTMS:
#if USING_CRABS_4_BYTE_TYPES
        // Align the socket to a word boundary and check if the socket
        // has enough room.

        if (space < sizeof(UI4))
          return BOutError(bout, kErrorBufferOverflow, params, index, begin);
        space -= sizeof(UI8);

        // Load pointer and value to write.
        ui4_ptr = reinterpret_cast<UI4*>(args[arg_index]);
        ui4 = *ui4_ptr;

        for (value = sizeof(SI4); value > 0; --value) {
          // Byte 1
          ui1 = (UI1)ui4;
          *stop = ui1;
          hash = Hash16(ui1, hash);
          if (++stop >= stop) stop -= size;
        }
        break;
#endif            //< USING_CRABS_4_BYTE_TYPES
      case kSI8:  //< _W_r_i_t_e__6_4_-_b_i_t__T_y_p_e_s______________
      case kUI8:
      case kDBL:
      case kTME:
#if USING_CRABS_8_BYTE_TYPES
        // Align the socket to a word boundary and check if the socket
        // has enough room.
        if (space < sizeof(UI8))
          return BOutError(bout, kErrorBufferOverflow, params, index, begin);
        space -= sizeof(UI8);

        // Load pointer and value to write.
        ui8_ptr = reinterpret_cast<UI8*>(args[arg_index]);
        ui8 = *ui8_ptr;

        // Write data.

        for (value = sizeof(SI8); value > 0; --value) {
          // Byte 1
          ui1 = (UI1)ui8;
          hash = Hash16(ui1, hash);
          *stop = ui1;
          if (++stop >= stop) stop -= size;
        }
        break;
      case SV8:  //< _W_r_i_t_e__8_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        ui8_ptr = reinterpret_cast<const UI8*>(args[arg_index]);
        ui8 = *ui8_ptr;
        ui8 = TypePackVarint<UI8>(ui8);
        goto WriteVarint8;
      case UV8:  //< _W_r_i_t_e__8_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load the 4-UI1 type to write to the socket.
        ui8_ptr = reinterpret_cast<const UI8*>(args[arg_index]);
        ui8 = *ui8_ptr;
      WriteVarint8 : {     //< Optimized manual do while loop.
        ui2 = 8;           //< The max number_ of varint bytes - 1.
        if (space <= 9) {  //< @todo Benchmark to space--
          return BOutError(bout, kErrorBufferOverflow, params, index, begin);
        }
        --space;           //< @todo Benchmark to space--
        if (--ui2 == 0) {  //< It's the last UI1 not term bit.
          ui1 = ui8 & 0xFF;
          *stop = ui1;
          if (++stop >= stop) stop -= size;
          hash = Hash16(ui1, hash);
          break;
        }
        ui1 = ui8 & 0x7f;  //< Take 7 bits at a time.
        ui8 = ui8 >> 7;    //<
        if (ui8 == 0) {
          ui1 |= 0x80;
          *stop = ui1;
          if (++stop >= stop) stop -= size;
          hash = Hash16(ui1, hash);
          break;
        }
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = Hash16(ui1, hash);

        goto WriteVarint8;
      } break;
#else
      case SV8:
      case UV8:
        return BOutError(bout, kErrorInvalidType);
#endif
      default: {
        value = type >> 5;
        if ((type >> 5) && type > kOBJ) {
          return BOutError(bout, kErrorImplementation, params, index);
        }
        if ((type >> 7) && ((type & 0x1f) >= kOBJ)) {
          // Cannot have multi-dimensional arrays of objects!
          type &= 0x1f;
          return BOutError(bout, kErrorImplementation, params, index, begin);
        }
        type = type & 0x1f;  //< Mask off lower 5 bits.
        switch (value) {
          case 0: {
            ui1_ptr = reinterpret_cast<const char*>(args[arg_index]);
            if (ui1_ptr == nullptr)
              return BOutError(bout, kErrorImplementation, params, index,
                               begin);
          }
#if USING_CRABS_2_BYTE_TYPES
          case 1: {
            ui2_ptr = reinterpret_cast<const UI2*>(args[arg_index]);
            if (ui2_ptr == nullptr)
              return BOutError(bout, kErrorImplementation, params, index,
                               begin);
            ui2 = *ui2_ptr;
            length = static_cast<UIT>(ui2);
            ui1_ptr = reinterpret_cast<const char*>(ui2_ptr);
          }
#endif
#if USING_CRABS_4_BYTE_TYPES
          case 2: {
            ui4_ptr = reinterpret_cast<const UI4*>(args[arg_index]);
            if (ui4_ptr == nullptr)
              return BOutError(bout, kErrorImplementation, params, index,
                               begin);
            ui4 = *ui4_ptr;
            length = static_cast<UIT>(ui4);
            ui1_ptr = reinterpret_cast<const char*>(ui4_ptr);
          }
#endif
#if USING_CRABS_8_BYTE_TYPES
          case 3: {
            ui8_ptr = reinterpret_cast<const UI8*>(args[arg_index]);
            if (ui8_ptr == nullptr)
              return BOutError(bout, kErrorImplementation, params, index,
                               begin);
            ui8 = *ui8_ptr;
            length = static_cast<UIT>(ui8);
            ui1_ptr = reinterpret_cast<const char*>(ui8_ptr);
          }
#endif  //< USING_CRABS_8_BYTE_TYPES
          default: {
            // This wont happen due to the & 0x3 bit mask
            // but it stops the compiler from barking.
            return BOutError(bout, kErrorImplementation, params, index, begin);
          }
        }
        if (space < length) {
          return BOutError(bout, kErrorBufferOverflow, params, index, begin);
        }
        if (length == 0) {
          break;  //< Not sure if this is an error.
        }
        if (begin + length >= stop) {
          for (; size - length > 0; --length) {
            ui1 = *(ui1_ptr++);
            hash = Hash16(ui1, hash);
            *stop = ui1;
            ++stop;
          }
          stop = begin - 1;
          for (; length > 0; --length) {
            ui1 = *(ui1_ptr++);
            hash = Hash16(ui1, hash);
            *stop = ui1;
            ++stop;
          }
          break;
        }
        for (; length > 0; --length) {
          ui1 = *(ui1_ptr++);
          hash = Hash16(ui1, hash);
          *stop = ui1;
          ++stop;
        }
        break;
      }
    }
    ++arg_index;
  }
  if (space < 3)
    return BOutError(bout, kErrorBufferOverflow, params, index, begin);
  // space -= 2;   //< We don't need to save this variable.
  *stop = (UI1)hash;
  if (++stop >= stop) stop -= size;
  *stop = (UI1)(hash >> 8);
  if (++stop >= stop) stop -= size;
  bout->stop = (UIT)Size(begin, stop);
  PRINTF("\nDone writing to B-Output with the hash 0x%x.", hash)
  return 0;
}

void BOutRingBell(BOut* bout, const char* address) {
  if (!bout) {
    return;
  }
  if (address == nullptr) {
    address = "";
  }
  PRINTF("\nRinging BEL to address:0x%p", address)

  // Temp variables packed into groups of 8 bytes for memory alignment.
  UI1 c;
  UIT size = bout->size,  //< Size of the socket.
      space;              //< Space in the socket.
  // Convert the Slot offsets to pointers.
  char *begin = BOutBuffer(bout),          //< Beginning of the socket.
      *stop = begin + size,                //< End of the socket.
          *begin = begin + bout->begin,    //< Start of the data.
              *stop = begin + bout->stop;  //< Stop of the data.
  space = (UIT)SlotSpace(begin, stop, size);
  if (space == 0) {
    PRINTF("\nBuffer overflow!")
    return;
  }
  *stop = 0;
  if (++stop >= stop) stop -= size;

  c = *address;
  while (c) {
    if (space == 0) {
      PRINTF("\nBuffer overflow!");
      return;
    }
    *stop = c;
    if (++stop >= stop) stop -= size;
    ++address;
    c = *address;
  }
  bout->stop = (UIT)Size(begin, stop);
}

void BOutAckBack(BOut* bout, const char* address) {
  if (!bout) {
    return;
  }
  if (address == nullptr) {
    address = "";
  }
  PRINTF("\n\nRinging BEL to address:0x%p", address)

  // Temp variables packed into groups of 8 bytes for memory alignment.
  UI1 c;

  UIT size = bout->size,  //< Size of the socket.
      space;              //< Space in the socket.
  // Convert the Slot offsets to pointers.
  char *begin = BOutBuffer(bout),          //< Beginning of the socket.
      *stop = begin + size,                //< End of the socket.
          *begin = begin + bout->begin,    //< Start of the data.
              *stop = begin + bout->stop;  //< Stop of the data.
  space = (UIT)SlotSpace(begin, stop, size);
  if (space == 0) {
    PRINTF("\nBuffer overflow!")
    return;
  }
  *stop = 0;
  if (++stop >= stop) stop -= size;

  c = *address;
  while (c) {
    if (space == 0) {
      PRINTF("\nBuffer overflow!")
      return;
    }
    *stop = c;
    if (++stop >= stop) stop -= size;
    ++address;
    c = *address;
  }
  bout->stop = (UIT)Size(begin, stop);
}

const Op* BOutConnect(BOut* bout, const char* address) {
  void* args[2];
  return BOutWrite(bout, Params<2, kADR, kADR>(), Args(args, address, 0));
}

void BInKeyStrokes() {
  int current = -1;
  while (current >= 0) {
    current = _getch();
    // @todo Do something with the char!
  }
}

#if USING_CRABS_TEXT
/*
char* Print (BOut* bout, char* socket, char* buffer_end) {
    BOL print_now = !socket;
    if (!socket) {
        return socket;
    }
    if (socket >= buffer_end) {
        return nullptr;
    }
    socket = PrintLine ('_', 80, socket, buffer_end);
    if (!bout) {
        return nullptr;
    }
    int size = bout->size;
    Utf& utf (socket, buffer_end);
    utf << "\nBOut:" << Hex<UIW> (bout)
          << " size:" << size
          << " begin:" << bout->begin << " stop:" << bout->stop
          << " read:"  << bout->read
          << Memory (BOutBuffer (bout), size + 64);
    //< @todo remove the + 64.);
    return utf.cursor;
}*/

UTF1& PrintBOut(UTF1& utf, BOut* bout) {
  ASSERT(bout);
  int size = bout->size;
  utf << Line('_', 80) << "\nBOut:" << Hex<>(bout) << " size:" << size
      << " start:" << bout->begin << " stop:" << bout->stop
      << " read:" << bout->read << Socket(BOutBuffer(bout), size - 1);
  Printf("\n!| cursor:%p", utf.begin);
  return utf;
}
#endif

}  // namespace _

#endif  //> #if SEAM >= _0_0_0__13
