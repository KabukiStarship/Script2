/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /BOut.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "Args.h"
#include "Binary.hpp"
#include "BOut.h"
#include "BSeq.h"
#include "hash.h"
#include "Slot.h"
#include "Test.h"
#include "TypeValue.h"
#include "Uniprinter.hpp"

#if SEAM == SCRIPT2_CRABS
#include "_Debug.inl"
#define D_COUT_BOUT(header, bout) \
  Console<>().Out() << "\n" << header << '\n' << bout;
#else
#include "_Release.inl"
#define D_COUT_BOUT(header, bout)
#endif

namespace _ {

/* Used to return an erroneous result from a B-Output.

    @param error The error type.
    @return Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, Error error) {
  std::cerr << "\nBOut " << STRError(error) << " Error!";
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Output.
    @param bout    The source BOut.
    @param error   The error type.
    @param header  The B-Sequence Header.
    @param offset  The offset to the type in error in the B-Sequence.
    @param address The address of the IUA in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, Error error, const ISC* header) {
  std::cerr << "\nBOut " << STRError(error) << " Error!";
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Output.
    @param bout    The source BOut.
    @param error   The error type.
    @param header  The B-Sequence Header.
    @param offset  The offset to the type in error in the B-Sequence.
    @param address The address of the IUA in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, Error error, const ISC* header,
                           ISC offset) {
  std::cerr << "\nBOut " << STRError(error) << " Error!";
  return reinterpret_cast<const Op*>(1);
}

/* Used to return an erroneous result from a B-Output.
    @param bout    The source BOut.
    @param error   The error type.
    @param header  The B-Sequence Header.
    @param offset  The offset to the type in error in the B-Sequence.
    @param address The address of the IUA in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, Error error, const ISC* header,
                           ISC offset, CHA* address) {
  std::cerr << "\nBOut " << STRError(error) << " Error!";
  return reinterpret_cast<const Op*>(1);
}

const CHA** BOutStateStrings() {
  static const CHA* Strings[] = {"WritingState", "cBInStateLocked"};
  return Strings;
}

CHA* BOutBuffer(BOut* bout) {
  A_ASSERT(bout);
  return reinterpret_cast<CHA*>(bout) + sizeof(BOut);
}

BOut* BOutInit(IUW* socket, ISC size) {
  if (size < cSlotSizeMin) return nullptr;
  if (socket == nullptr) return nullptr;

  BOut* bout = reinterpret_cast<BOut*>(socket);
  // bout->size  = size - sizeof (BIn); //< Not sure why I did that?
  bout->size = size;
  bout->origin = 0;
  bout->stop = 0;
  bout->read = 0;

#if SEAM_MAJOR == 0 && SEAM_MINOR == 2
  MemoryClear(BOutBuffer(bout), size);
#endif
  return bout;
}

ISC BOutSpace(BOut* bout) {
  if (!bout) {
    return 0;
  }
  CHA* txb_ptr = reinterpret_cast<CHA*>(bout);
  return (IUN)SlotSpace(txb_ptr + bout->origin, txb_ptr + bout->stop,
                        bout->size);
}

ISC BOutBufferLength(BOut* bout) {
  if (!bout) {
    return 0;
  }
  CHA* origin = BOutBuffer(bout);
  return (IUN)SlotLength(origin + bout->origin, origin + bout->stop,
                         bout->size);
}

CHA* BOutEndAddress(BOut* bout) {
  return reinterpret_cast<CHA*>(bout) + (4 * sizeof(ISC)) + bout->size;
}

ISC BOutStreamByte(BOut* bout) {
  CHA *origin = BOutBuffer(bout), *stop = origin + bout->size;
  CHA *open = (CHA*)origin + bout->read, *origin = origin + bout->origin,
      *origin = origin;

  ISW length = (ISC)(origin < open) ? open - origin + 1
                                    : (stop - origin) + (open - origin) + 2;

  if (length < 1) {
    BOutError(bout, cErrorBufferOverflow, Params<1, cSTR>(), 2, origin);
    return -1;
  }
  // IUA b = *cursor;
  bout->stop = (++origin > stop) ? static_cast<ISC>(Size(origin, stop))
                                 : static_cast<ISC>(Size(origin, origin));
  return 0;
}

const Op* BOutWrite(BOut* bout, const ISC* params, void** args) {
  D_COUT_BSQ("\n\nWriting ", params);
  enum {
    cBOutBufferSize = 1024,
    cBOutBufferSizeWords = cBOutBufferSize >> cWordBitCount
  };
  D_COUT_BOUT(" to B-Output:", bout)

  A_ASSERT(bout);
  A_ASSERT(params);
  A_ASSERT(args);

  // Temp variables packed into groups of 8 bytes for memory alignment.
  IUA  // type,
      ui1;
#if USING_SCRIPT2_2_BYTE_TYPES
  IUB ui2;
#endif
#if USING_SCRIPT2_4_BYTE_TYPES
  IUC ui4;
#endif
#if USING_SCRIPT2_8_BYTE_TYPES
  IUD ui8;
#endif

  ISC num_params,  //< Num params in the b-sequence.
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
  const ISC* param =
      params;  //< Pointer to the current param.
               //* bsc_param;          //< Pointer to the current cBSQ param.
  // Convert the socket offsets to pointers.
  CHA *origin = BOutBuffer(bout),           //< Beginning of the socket.
      *stop = origin + size,                //< End of the socket.
          *origin = origin + bout->origin,  //< Start of the data.
              *stop = origin + bout->stop;  //< Stop of the data.
  const CHA* ui1_ptr;                       //< Pointer to a 1-IUA type.
#if USING_SCRIPT2_2_BYTE_TYPES
  const IUB* ui2_ptr;  //< Pointer to a 2-IUA type.
#endif
#if USING_SCRIPT2_4_BYTE_TYPES
  const IUC* ui4_ptr;  //< Pointer to a 4-IUA type.
#endif
#if USING_SCRIPT2_8_BYTE_TYPES
  const IUD* ui8_ptr;  //< Pointer to a 8-IUA type.
#endif
  IUB hash = PRIME_LARGEST_IUB;

  space = (ISC)SlotSpace(origin, stop, size);

  // Check if the socket has enough room.
  if (space == 0) return BOutError(bout, cErrorBufferOverflow);
  --space;
  length = params[0];  //< Load the max CHA length.
  ++param;

  // Write data.
  for (index = 1; index <= num_params; ++index) {
    type = params[index];
    D_COUT("\nparam: " << arg_index + 1 << " type:" << STRType(type)
                       << " start:" << TDelta<>(origin, origin) << " stop:"
                       << TDelta<>(origin, stop) << " space:" << space);
    switch (type) {
      case cNIL:
        break;

      case kADR:  //< _W_r_i_t_e__A_d_d_r_e_s_s__S_t_r_i_n_g___________
      case cSTR:  //< _W_r_i_t_e__U_T_F_-_8__S_t_r_i_n_g______________
        if (space == 0)
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        if (type != kADR) {
          // We might not need to write anything if it's an kADR with
          // nil .
          length = params[++index];  //< Load the max CHA length.
          ++num_params;
        } else {
          length = cAddressLengthMax;
        }
        // Load the source data pointer and increment args.fs
        ui1_ptr = reinterpret_cast<const CHA*>(args[arg_index]);
        D_COUT('\"' << Hexf(ui1_ptr));

        // We know we will always have at least one nil-term CHA.
        ui1 = *ui1_ptr;
        while (ui1 != 0) {
          if (space-- == 0)
            return BOutError(bout, cErrorBufferOverflow, params, index, origin);
          hash = HashIUB(ui1, hash);

          *stop = ui1;  // Write IUA
          if (++stop >= stop) stop -= size;
          ++ui1_ptr;
          ui1 = *ui1_ptr;  // Read IUA.
        }
        if (type != kADR) {  //< 1 is faster to compare than 2
                             // More likely to have kADR than cSTR
          *stop = 0;         // Write nil-term CHA.
          if (++stop >= stop) stop -= size;
          break;
        }

        break;
      case cISA:  //< _W_r_i_t_e__8_-_b_i_t__T_y_p_e_s_______________
      case cIUA:
      case cBOL:
#if USING_SCRIPT2_1_BYTE_TYPES
        // Check if the socket has enough room.
        if (space-- == 0)
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);

        // Load pointer and read data to write.
        ui1_ptr = reinterpret_cast<const CHA*>(args[arg_index]);
        ui1 = *ui1_ptr;

        // Write data.
        *stop = ui1;
        hash = HashIUB(ui1, hash);
        if (++stop >= stop) stop -= size;
        break;
#else
        return BOutError(bout, cErrorInvalidType);
#endif
      case cISB:  //< _W_r_i_t_e__1_6_-_b_i_t__T_y_p_e_s______________
      case cIUB:
      case cFPB:
#if USING_SCRIPT2_2_BYTE_TYPES
        // Align the socket to a word boundary and check if the
        // socket has enough room.
        if (space < sizeof(IUB))
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        space -= sizeof(IUB);

        // Load pointer and value to write.
        ui2_ptr = reinterpret_cast<IUB*>(args[arg_index]);
        ui2 = *ui2_ptr;

        // Write data.

        // Byte 1
        ui1 = (IUA)ui2;
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(ui1, hash);

        // Byte 2
        ui1 = (IUA)(ui2 >> 8);
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(ui1, hash);
        break;
#else
        return BOutError(bout, cErrorInvalidType);
#endif  // USING_SCRIPT2_2_BYTE_TYPES
#if ALU_SIZE <= 16
      case SVI:  //< _W_r_i_t_e__2_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        ui2_ptr = reinterpret_cast<const IUB*>(args[arg_index]);
        ui2 = *ui2_ptr;
        // We are using the same code to utf both signed and unsigned
        // varints. In order to convert from a negative 2's complement
        // signed integer to a transmittable format, we need to invert
        // the bits and add 1. Then we just shift the bits left one and
        // put the sign bit in the LSB.
        ui2 = TypePackVarint<IUB>(ui2);
        goto WriteVarint2;
      case UVI:  //< _W_r_i_t_e__2_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load next pointer value to write.
        ui2_ptr = reinterpret_cast<const IUB*>(args[arg_index]);
        if (ui2_ptr == nullptr)
          return BOutError(bout, cErrorImplementation, params, index, origin);
        ui2 = *ui2_ptr;

      WriteVarint2 : {
        // Byte 1
        if (space-- == 0)
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        ui1 = ui2 & 0x7f;
        ui2 = ui2 >> 7;
        if (ui2 == 0) {
          ui1 |= 0x80;
          *stop = ui1;
          if (++stop >= stop) stop -= size;
          hash = HashIUB(ui1, hash);
          break;
        }
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(ui1, hash);

        // Byte 2
        if (--space == 0)
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        ui1 = ui2 & 0x7f;
        ui2 = ui2 >> 7;
        if (ui2 == 0) {
          ui1 |= 0x80;
          *stop = ui1;
          if (++stop >= stop) stop -= size;
          hash = HashIUB(ui1, hash);
          break;
        }
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(ui1, hash);

        // Byte 3
        if (--space == 0)
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        ui1 = ui2 & 0x7f;
        ui1 |= 0x80;
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(ui1, hash);
      } break;
#else
      case SVI:  //< _W_r_i_t_e__4_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        ui4_ptr = reinterpret_cast<const IUC*>(args[arg_index]);
        ui4 = *ui4_ptr;
        ui4 = TypePackVarint<IUC>(ui4);
        goto WriteVarint4;
      case UVI:  //< _W_r_i_t_e__4_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load the 4-IUA type to write to the socket.
        ui4_ptr = reinterpret_cast<const IUC*>(args[arg_index]);
        ui4 = *ui4_ptr;
      WriteVarint4 : {  //< Optimized manual do while loop.
        ui2 = 5;
        if (space == 0)  //< @todo Benchmark to space--
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        --space;  //< @todo Benchmark to space--
        ui1 = ui4 & 0x7f;
        ui4 = ui4 >> 7;
        if (ui4 == 0) {
          ui1 |= 0x80;
          *stop = ui1;
          if (++stop >= stop) stop -= size;
          hash = HashIUB(ui1, hash);
          break;
        }
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(ui1, hash);
        // This wont happen I don't think.
        // if (--ui2 == 0)
        //    return BOutError (cErrorVarintOverflow, params, index,
        //                       origin);

        goto WriteVarint4;
      } break;
#endif
      case cISC:  //< _W_r_i_t_e__3_2_-_b_i_t__T_y_p_e_s______________
      case cIUC:
      case cFPC:
      case kTM4:
#if USING_SCRIPT2_4_BYTE_TYPES
        // Align the socket to a word boundary and check if the socket
        // has enough room.

        if (space < sizeof(IUC))
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        space -= sizeof(IUD);

        // Load pointer and value to write.
        ui4_ptr = reinterpret_cast<IUC*>(args[arg_index]);
        ui4 = *ui4_ptr;

        for (value = sizeof(ISC); value > 0; --value) {
          // Byte 1
          ui1 = (IUA)ui4;
          *stop = ui1;
          hash = HashIUB(ui1, hash);
          if (++stop >= stop) stop -= size;
        }
        break;
#endif            //< USING_SCRIPT2_4_BYTE_TYPES
      case cISD:  //< _W_r_i_t_e__6_4_-_b_i_t__T_y_p_e_s______________
      case cIUD:
      case cFPD:
      case kTM8:
#if USING_SCRIPT2_8_BYTE_TYPES
        // Align the socket to a word boundary and check if the socket
        // has enough room.
        if (space < sizeof(IUD))
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        space -= sizeof(IUD);

        // Load pointer and value to write.
        ui8_ptr = reinterpret_cast<IUD*>(args[arg_index]);
        ui8 = *ui8_ptr;

        // Write data.

        for (value = sizeof(ISD); value > 0; --value) {
          // Byte 1
          ui1 = (IUA)ui8;
          hash = HashIUB(ui1, hash);
          *stop = ui1;
          if (++stop >= stop) stop -= size;
        }
        break;
      case SV8:  //< _W_r_i_t_e__8_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        ui8_ptr = reinterpret_cast<const IUD*>(args[arg_index]);
        ui8 = *ui8_ptr;
        ui8 = TypePackVarint<IUD>(ui8);
        goto WriteVarint8;
      case UV8:  //< _W_r_i_t_e__8_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load the 4-IUA type to write to the socket.
        ui8_ptr = reinterpret_cast<const IUD*>(args[arg_index]);
        ui8 = *ui8_ptr;
      WriteVarint8 : {     //< Optimized manual do while loop.
        ui2 = 8;           //< The max number_ of varint bytes - 1.
        if (space <= 9) {  //< @todo Benchmark to space--
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        }
        --space;           //< @todo Benchmark to space--
        if (--ui2 == 0) {  //< It's the last IUA not term bit.
          ui1 = ui8 & 0xFF;
          *stop = ui1;
          if (++stop >= stop) stop -= size;
          hash = HashIUB(ui1, hash);
          break;
        }
        ui1 = ui8 & 0x7f;  //< Take 7 bits at a time.
        ui8 = ui8 >> 7;    //<
        if (ui8 == 0) {
          ui1 |= 0x80;
          *stop = ui1;
          if (++stop >= stop) stop -= size;
          hash = HashIUB(ui1, hash);
          break;
        }
        *stop = ui1;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(ui1, hash);

        goto WriteVarint8;
      } break;
#else
      case SV8:
      case UV8:
        return BOutError(bout, cErrorInvalidType);
#endif
      default: {
        value = type >> 5;
        if ((type >> 5) && type > kOBJ) {
          return BOutError(bout, cErrorImplementation, params, index);
        }
        if ((type >> 7) && ((type & 0x1f) >= kOBJ)) {
          // Cannot have multi-dimensional arrays of objects!
          type &= 0x1f;
          return BOutError(bout, cErrorImplementation, params, index, origin);
        }
        type = type & 0x1f;  //< Mask off lower 5 bits.
        switch (value) {
          case 0: {
            ui1_ptr = reinterpret_cast<const CHA*>(args[arg_index]);
            if (ui1_ptr == nullptr)
              return BOutError(bout, cErrorImplementation, params, index,
                               origin);
          }
#if USING_SCRIPT2_2_BYTE_TYPES
          case 1: {
            ui2_ptr = reinterpret_cast<const IUB*>(args[arg_index]);
            if (ui2_ptr == nullptr)
              return BOutError(bout, cErrorImplementation, params, index,
                               origin);
            ui2 = *ui2_ptr;
            length = static_cast<ISC>(ui2);
            ui1_ptr = reinterpret_cast<const CHA*>(ui2_ptr);
          }
#endif
#if USING_SCRIPT2_4_BYTE_TYPES
          case 2: {
            ui4_ptr = reinterpret_cast<const IUC*>(args[arg_index]);
            if (ui4_ptr == nullptr)
              return BOutError(bout, cErrorImplementation, params, index,
                               origin);
            ui4 = *ui4_ptr;
            length = static_cast<ISC>(ui4);
            ui1_ptr = reinterpret_cast<const CHA*>(ui4_ptr);
          }
#endif
#if USING_SCRIPT2_8_BYTE_TYPES
          case 3: {
            ui8_ptr = reinterpret_cast<const IUD*>(args[arg_index]);
            if (ui8_ptr == nullptr)
              return BOutError(bout, cErrorImplementation, params, index,
                               origin);
            ui8 = *ui8_ptr;
            length = static_cast<ISC>(ui8);
            ui1_ptr = reinterpret_cast<const CHA*>(ui8_ptr);
          }
#endif  //< USING_SCRIPT2_8_BYTE_TYPES
          default: {
            // This wont happen due to the & 0x3 bit mask
            // but it stops the compiler from barking.
            return BOutError(bout, cErrorImplementation, params, index, origin);
          }
        }
        if (space < length) {
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        }
        if (length == 0) {
          break;  //< Not sure if this is an error.
        }
        if (origin + length >= stop) {
          for (; size - length > 0; --length) {
            ui1 = *(ui1_ptr++);
            hash = HashIUB(ui1, hash);
            *stop = ui1;
            ++stop;
          }
          stop = origin - 1;
          for (; length > 0; --length) {
            ui1 = *(ui1_ptr++);
            hash = HashIUB(ui1, hash);
            *stop = ui1;
            ++stop;
          }
          break;
        }
        for (; length > 0; --length) {
          ui1 = *(ui1_ptr++);
          hash = HashIUB(ui1, hash);
          *stop = ui1;
          ++stop;
        }
        break;
      }
    }
    ++arg_index;
  }
  if (space < 3)
    return BOutError(bout, cErrorBufferOverflow, params, index, origin);
  // space -= 2;   //< We don't need to save this variable.
  *stop = (IUA)hash;
  if (++stop >= stop) stop -= size;
  *stop = (IUA)(hash >> 8);
  if (++stop >= stop) stop -= size;
  bout->stop = (ISC)Size(origin, stop);
  D_COUT("\nDone writing to B-Output with the hash 0x" << Hexf(hash));
  return 0;
}

void BOutRingBell(BOut* bout, const CHA* address) {
  if (!bout) {
    return;
  }
  if (address == nullptr) {
    address = "";
  }
  D_COUT("\nRinging BEL to address:0x" << Hexf(address));

  // Temp variables packed into groups of 8 bytes for memory alignment.
  IUA c;
  ISC size = bout->size,  //< Size of the socket.
      space;              //< Space in the socket.
  // Convert the Slot offsets to pointers.
  CHA *origin = BOutBuffer(bout),           //< Beginning of the socket.
      *stop = origin + size,                //< End of the socket.
          *origin = origin + bout->origin,  //< Start of the data.
              *stop = origin + bout->stop;  //< Stop of the data.
  space = (ISC)SlotSpace(origin, stop, size);
  if (space == 0) {
    D_COUT("\nBuffer overflow!");
    return;
  }
  *stop = 0;
  if (++stop >= stop) stop -= size;

  c = *address;
  while (c) {
    if (space == 0) {
      D_COUT("\nBuffer overflow!");
      return;
    }
    *stop = c;
    if (++stop >= stop) stop -= size;
    ++address;
    c = *address;
  }
  bout->stop = (ISC)Size(origin, stop);
}

void BOutAckBack(BOut* bout, const CHA* address) {
  if (!bout) {
    return;
  }
  if (address == nullptr) {
    address = "";
  }
  D_COUT("\n\nRinging BEL to address:0x" << Hexf(address));

  // Temp variables packed into groups of 8 bytes for memory alignment.
  IUA c;

  ISC size = bout->size,  //< Size of the socket.
      space;              //< Space in the socket.
  // Convert the Slot offsets to pointers.
  CHA *origin = BOutBuffer(bout),           //< Beginning of the socket.
      *stop = origin + size,                //< End of the socket.
          *origin = origin + bout->origin,  //< Start of the data.
              *stop = origin + bout->stop;  //< Stop of the data.
  space = (ISC)SlotSpace(origin, stop, size);
  if (space == 0) {
    D_COUT("\nBuffer overflow!");
    return;
  }
  *stop = 0;
  if (++stop >= stop) stop -= size;

  c = *address;
  while (c) {
    if (space == 0) {
      D_COUT("\nBuffer overflow!");
      return;
    }
    *stop = c;
    if (++stop >= stop) stop -= size;
    ++address;
    c = *address;
  }
  bout->stop = (ISC)Size(origin, stop);
}

const Op* BOutConnect(BOut* bout, const CHA* address) {
  void* args[2];
  return BOutWrite(bout, Params<2, kADR, kADR>(), Args(args, address, 0));
}

void BInKeyStrokes() {
  ISC current = -1;
  while (current >= 0) {
    current = _getch();
    // @todo Do something with the CHA!
  }
}

#if USING_SCRIPT2_TEXT
/*
CHA* Print (BOut* bout, CHA* socket, CHA* buffer_end) {
    BOL print_now = !socket;
    if (!socket) {
        return socket;
    }
    if (socket >= buffer_end) {
        return nullptr;
    }
    socket = TPrintLinef('_', 80, socket, buffer_end);
    if (!bout) {
        return nullptr;
    }
    ISC size = bout->size;
    UTF& utf (socket, buffer_end);
    utf << "\nBOut:" << Hex<IUW> (bout)
          << " size:" << size
          << " origin:" << bout->origin << " stop:" << bout->stop
          << " read:"  << bout->read
          << Memory (BOutBuffer (bout), size + 64);
    //< @todo remove the + 64.);
    return utf.cursor;
}*/

UTF1& PrintBOut(UTF1& utf, BOut* bout) {
  A_ASSERT(bout);
  ISC size = bout->size;
  utf << Line('_', 80) << "\nBOut:" << Hex<>(bout) << " size:" << size
      << " start:" << bout->origin << " stop:" << bout->stop
      << " read:" << bout->read << Socket(BOutBuffer(bout), size - 1);
  Printf("\n!| cursor:%p", utf.start);
  return utf;
}
#endif

}  // namespace _

#endif
