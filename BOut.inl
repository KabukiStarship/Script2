/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /BOut.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "BOut.hpp"
//
//#include "Args.h"
#include "Binary.hpp"
#include "BSeq.hpp"
#include "Error.h"
#include "Hash.hpp"
#include "Slot.hpp"
//#include "TypeValue.h"
//#include "Uniprinter.hpp"
#if SEAM == SCRIPT2_CRABS
#include "_Debug.inl"
#define D_COUT_BOUT(message, bout) \
  _::CPrint().Star() << message;   \
  _::TBOutPrint<COut>(COut().Star(), bout)
#else
#include "_Release.inl"
#define D_COUT_BOUT(message, bout)
#endif
namespace _ {

/* Used to return an erroneous result from a B-Output.

@param error The error type.
@return Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, Error error) {
  D_COUT("\nBOut " << STRError(error) << " Error!");
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
  D_COUT("\nBOut " << STRError(error) << " Error!");
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
  D_COUT("\nBOut " << STRError(error) << " Error!");
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
  D_COUT("\nBOut " << STRError(error) << " Error!");
  return reinterpret_cast<const Op*>(1);
}

const CHA** BOutStateStrings() {
  static const CHA* Strings[] = {"WritingState", "cBInStateLocked"};
  return Strings;
}

CHA* BOutBuffer(BOut* bout) {
  return TPtr<CHA>(bout) + sizeof(BOut);
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
  CHA* txb_ptr = TPtr<CHA>(bout);
  return TSlotSpace<IUN>(txb_ptr + bout->origin, txb_ptr + bout->stop,
                         bout->size);
}

ISC BOutBufferLength(BOut* bout) {
  if (!bout) {
    return 0;
  }
  CHA* origin = BOutBuffer(bout);
  return TSlotLength<IUN>(origin + bout->origin, origin + bout->stop,
                            bout->size);
}

CHA* BOutEndAddress(BOut* bout) {
  return TPtr<CHA>(bout) + (4 * sizeof(ISC)) + bout->size;
}

ISC BOutStreamByte(BOut* bout) {
  CHA *origin = BOutBuffer(bout), *stop = origin + bout->size;
  CHA *open = (CHA*)origin + bout->read, *origin = origin + bout->origin,
      *origin = origin;

  ISW length = (ISC)(origin < open) ? open - origin + 1
                                    : (stop - origin) + (open - origin) + 2;

  if (length < 1) {
    BOutError(bout, cErrorBufferOverflow, TParams<1, cSTR>(), 2, origin);
    return -1;
  }
  // IUA b = *cursor;
  bout->stop = (++origin > stop) ? TDelta<ISC>(origin, stop)
                                 : TDelta<ISC>(origin, origin);
  return 0;
}

const Op* BOutWrite(BOut* bout, const ISC* params, void** args) {
  D_COUT("\n\nWriting ");
  D_COUT_BSQ(params);
  enum {
    cBOutBufferSize = 1024,
    cBOutBufferSizeWords = cBOutBufferSize >> cWordBitCount
  };
  D_COUT_BOUT(" to B-Output:", bout);

  A_ASSERT(bout);
  A_ASSERT(params);
  A_ASSERT(args);

  // Temp variables packed into groups of 8 bytes for memory alignment.
  IUA  // type,
      iua;
#if USING_SCRIPT2_2_BYTE_TYPES == 0
  IUB iub;
#endif
#if USING_SCRIPT2_4_BYTE_TYPES == 0
  IUC iuc;
#endif
#if USING_SCRIPT2_8_BYTE_TYPES == 0
  IUD iud;
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
  const ISC* param = params;  //< Pointer to the current param.
         //* bsc_param;       //< Pointer to the current cBSQ param.
  // Convert the socket offsets to pointers.
  CHA* origin = BOutBuffer(bout),       //< Beginning of the socket.
     * stop = origin + size,            //< End of the socket.
     * origin = origin + bout->origin,  //< Start of the data.
     * stop = origin + bout->stop;      //< Stop of the data.
  const CHA* iua_ptr;
  const IUB* iub_ptr;  //< Pointer to a 2-IUA type.
#if USING_SCRIPT2_4_BYTE_TYPES
  const IUC* iuc_ptr;  //< Pointer to a 4-IUA type.
#endif
#if USING_SCRIPT2_8_BYTE_TYPES
  const IUD* iud_ptr;  //< Pointer to a 8-IUA type.
#endif
  IUB hash = PRIME_LARGEST_IUB;

  space = TSlotSpace<ISC>(origin, stop, size);

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
      case cISA:  //< _W_r_i_t_e__8_-_b_i_t__T_y_p_e_s_______________
      case cIUA:
      case cBOL:
#if USING_SCRIPT2_1_BYTE_TYPES
        // Check if the socket has enough room.
        if (space-- == 0)
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);

        // Load pointer and read data to write.
        iua_ptr = TPtr<const CHA>(args[arg_index]);
        iua = *iua_ptr;

        // Write data.
        *stop = iua;
        hash = HashIUB(iua, hash);
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
        iub_ptr = TPtr<IUB>(args[arg_index]);
        iub = *iub_ptr;

        // Write data.

        // Byte 1
        iua = (IUA)iub;
        *stop = iua;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(iua, hash);

        // Byte 2
        iua = (IUA)(iub >> 8);
        *stop = iua;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(iua, hash);
        break;
#else
        return BOutError(bout, cErrorInvalidType);
#endif  // USING_SCRIPT2_2_BYTE_TYPES
#if ALU_SIZE <= 16
      case cSVI:  //< _W_r_i_t_e__2_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        iub_ptr = TPtr<const IUB>(args[arg_index]);
        iub = *iub_ptr;
        // We are using the same code to utf both signed and unsigned
        // varints. In order to convert from a negative 2's complement
        // signed integer to a transmittable format, we need to invert
        // the bits and add 1. Then we just shift the bits left one and
        // put the sign bit in the LSB.
        iub = TypePackVarint<IUB>(iub);
        goto WriteVarint2;
      case cUVI:  //< _W_r_i_t_e__2_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load next pointer value to write.
        iub_ptr = TPtr<const IUB>(args[arg_index]);
        if (iub_ptr == nullptr)
          return BOutError(bout, cErrorImplementation, params, index, origin);
        iub = *iub_ptr;

      WriteVarint2 : {
        // Byte 1
        if (space-- == 0)
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        iua = iub & 0x7f;
        iub = iub >> 7;
        if (iub == 0) {
          iua |= 0x80;
          *stop = iua;
          if (++stop >= stop) stop -= size;
          hash = HashIUB(iua, hash);
          break;
        }
        *stop = iua;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(iua, hash);

        // Byte 2
        if (--space == 0)
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        iua = iub & 0x7f;
        iub = iub >> 7;
        if (iub == 0) {
          iua |= 0x80;
          *stop = iua;
          if (++stop >= stop) stop -= size;
          hash = HashIUB(iua, hash);
          break;
        }
        *stop = iua;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(iua, hash);

        // Byte 3
        if (--space == 0)
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        iua = iub & 0x7f;
        iua |= 0x80;
        *stop = iua;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(iua, hash);
      } break;
#else
      case cSVI:  //< _W_r_i_t_e__4_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        iuc_ptr = TPtr<const IUC>(args[arg_index]);
        iuc = *iuc_ptr;
        iuc = TypePackVarint<IUC>(iuc);
        goto WriteVarint4;
      case cUVI:  //< _W_r_i_t_e__4_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load the 4-IUA type to write to the socket.
        iuc_ptr = TPtr<const IUC>(args[arg_index]);
        iuc = *iuc_ptr;
      WriteVarint4 : {  //< Optimized manual do while loop.
        iub = 5;
        if (space == 0)  //< @todo Benchmark to space--
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        --space;  //< @todo Benchmark to space--
        iua = iuc & 0x7f;
        iuc = iuc >> 7;
        if (iuc == 0) {
          iua |= 0x80;
          *stop = iua;
          if (++stop >= stop) stop -= size;
          hash = HashIUB(iua, hash);
          break;
        }
        *stop = iua;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(iua, hash);
        // This wont happen I don't think.
        // if (--iub == 0)
        //    return BOutError (cErrorVarintOverflow, params, index,
        //                       origin);

        goto WriteVarint4;
      } break;
#endif
      case cISC:  //< _W_r_i_t_e__3_2_-_b_i_t__T_y_p_e_s______________
      case cIUC:
      case cFPC:
#if USING_SCRIPT2_4_BYTE_TYPES
        // Align the socket to a word boundary and check if the socket
        // has enough room.

        if (space < sizeof(IUC))
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        space -= sizeof(IUD);

        // Load pointer and value to write.
        iuc_ptr = TPtr<IUC>(args[arg_index]);
        iuc = *iuc_ptr;

        for (value = sizeof(ISC); value > 0; --value) {
          // Byte 1
          iua = (IUA)iuc;
          *stop = iua;
          hash = HashIUB(iua, hash);
          if (++stop >= stop) stop -= size;
        }
        break;
#endif            //< USING_SCRIPT2_4_BYTE_TYPES
      case cISD:  //< _W_r_i_t_e__6_4_-_b_i_t__T_y_p_e_s______________
      case cIUD:
      case cFPD:
      case cTME:
#if USING_SCRIPT2_8_BYTE_TYPES
        // Align the socket to a word boundary and check if the socket
        // has enough room.
        if (space < sizeof(IUD))
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        space -= sizeof(IUD);

        // Load pointer and value to write.
        iud_ptr = TPtr<IUD>(args[arg_index]);
        iud = *iud_ptr;

        // Write data.

        for (value = sizeof(ISD); value > 0; --value) {
          // Byte 1
          iua = (IUA)iud;
          hash = HashIUB(iua, hash);
          *stop = iua;
          if (++stop >= stop) stop -= size;
        }
        break;
      case SV8:  //< _W_r_i_t_e__8_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        iud_ptr = TPtr<const IUD>(args[arg_index]);
        iud = *iud_ptr;
        iud = TypePackVarint<IUD>(iud);
        goto WriteVarint8;
      case UV8:  //< _W_r_i_t_e__8_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load the 4-IUA type to write to the socket.
        iud_ptr = TPtr<const IUD>(args[arg_index]);
        iud = *iud_ptr;
      WriteVarint8 : {     //< Optimized manual do while loop.
        iub = 8;           //< The max number_ of varint bytes - 1.
        if (space <= 9) {  //< @todo Benchmark to space--
          return BOutError(bout, cErrorBufferOverflow, params, index, origin);
        }
        --space;           //< @todo Benchmark to space--
        if (--iub == 0) {  //< It's the last IUA not term bit.
          iua = iud & 0xFF;
          *stop = iua;
          if (++stop >= stop) stop -= size;
          hash = HashIUB(iua, hash);
          break;
        }
        iua = iud & 0x7f;  //< Take 7 bits at a time.
        iud = iud >> 7;    //<
        if (iud == 0) {
          iua |= 0x80;
          *stop = iua;
          if (++stop >= stop) stop -= size;
          hash = HashIUB(iua, hash);
          break;
        }
        *stop = iua;
        if (++stop >= stop) stop -= size;
        hash = HashIUB(iua, hash);

        goto WriteVarint8;
      } break;
#else
      case cSVD:
      case cUVD:
        return BOutError(bout, cErrorInvalidType);
#endif
      default: {
        value = type >> 5;
        auto block_type = value & 0x3;
        if (block_type == ARY) {
          D_COUT("\nPrinting string.");
            if (space == 0)
              return BOutError(bout, cErrorBufferOverflow, params, index,
                               origin);
            if (type != cADR) {
              // We might not need to write anything if it's an cADR with
              // nil .
              length = params[++index];  //< Load the max CHA length.
              ++num_params;
            } else {
              length = cAddressLengthMax;
            }
            // Load the source data pointer and increment args.fs
            iua_ptr = TPtr<const CHA>(args[arg_index]);
            D_COUT('\"' << Hexf(iua_ptr));

            // We know we will always have at least one nil-term CHA.
            iua = *iua_ptr;
            while (iua != 0) {
              if (space-- == 0)
                return BOutError(bout, cErrorBufferOverflow, params, index,
                                 origin);
              hash = HashIUB(iua, hash);

              *stop = iua;  // Write IUA
              if (++stop >= stop) stop -= size;
              ++iua_ptr;
              iua = *iua_ptr;  // Read IUA.
            }
            if (type != cADR) {  //< 1 is faster to compare than 2
                                 // More likely to have cADR than cSTR
              *stop = 0;         // Write nil-term CHA.
              if (++stop >= stop) stop -= size;
              break;
            }

            break;
        }
        if ((type >> 5) && type > cOBJ) {
          return BOutError(bout, cErrorImplementation, params, index);
        }
        if ((type >> 7) && ((type & 0x1f) >= cOBJ)) {
          // Cannot have multi-dimensional arrays of objects!
          type &= 0x1f;
          return BOutError(bout, cErrorImplementation, params, index, origin);
        }
        type = type & 0x1f;  //< Mask off lower 5 bits.
        switch (value) {
          case 0: {
            iua_ptr = TPtr<const CHA>(args[arg_index]);
            if (iua_ptr == nullptr)
              return BOutError(bout, cErrorImplementation, params, index,
                               origin);
          }
#if USING_SCRIPT2_2_BYTE_TYPES
          case 1: {
            iub_ptr = TPtr<const IUB>(args[arg_index]);
            if (iub_ptr == nullptr)
              return BOutError(bout, cErrorImplementation, params, index,
                               origin);
            iub = *iub_ptr;
            length = static_cast<ISC>(iub);
            iua_ptr = TPtr<const CHA>(iub_ptr);
          }
#endif
#if USING_SCRIPT2_4_BYTE_TYPES
          case 2: {
            iuc_ptr = TPtr<const IUC>(args[arg_index]);
            if (iuc_ptr == nullptr)
              return BOutError(bout, cErrorImplementation, params, index,
                               origin);
            iuc = *iuc_ptr;
            length = static_cast<ISC>(iuc);
            iua_ptr = TPtr<const CHA>(iuc_ptr);
          }
#endif
#if USING_SCRIPT2_8_BYTE_TYPES
          case 3: {
            iud_ptr = TPtr<const IUD>(args[arg_index]);
            if (iud_ptr == nullptr)
              return BOutError(bout, cErrorImplementation, params, index,
                               origin);
            iud = *iud_ptr;
            length = static_cast<ISC>(iud);
            iua_ptr = TPtr<const CHA>(iud_ptr);
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
            iua = *(iua_ptr++);
            hash = HashIUB(iua, hash);
            *stop = iua;
            ++stop;
          }
          stop = origin - 1;
          for (; length > 0; --length) {
            iua = *(iua_ptr++);
            hash = HashIUB(iua, hash);
            *stop = iua;
            ++stop;
          }
          break;
        }
        for (; length > 0; --length) {
          iua = *(iua_ptr++);
          hash = HashIUB(iua, hash);
          *stop = iua;
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
  *stop = IUA(hash);
  if (++stop >= stop) stop -= size;
  *stop = IUA(hash >> 8);
  if (++stop >= stop) stop -= size;
  bout->stop = TDelta<ISC>(origin, stop);
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
  space = TSlotSpace<ISC>(origin, stop, size);
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
  bout->stop = TDelta <ISC>(origin, stop);
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
  space = TSlotSpace<ISC>(origin, stop, size);
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
  bout->stop = TDelta <ISC>(origin, stop);
}

const Op* BOutConnect(BOut* bout, const CHA* address) {
  void* args[2];
  return BOutWrite(bout, TParams<2, cADR, cADR>(), Args(args, address, 0));
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

}  //< namespace _

#endif
