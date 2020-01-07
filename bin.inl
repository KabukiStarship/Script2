/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /bin.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>

#if SEAM >= SCRIPT2_DIC

#include "bin.h"

#include "binary.h"
#include "bout.h"
#include "bsq.h"
#include "hash.h"
#include "typevalue.h"

#if SEAM == SCRIPT2_DIC
#define CLEAR(origin, stop) \
  while (origin <= stop) *origin++ = ' ';
#define D_COUT_BSQ(header, bsq) Console<>().Out() << header << '\n' << Bsq(bsq);
#define D_COUT_BIN(header, bin) Console<>().Out() << header << '\n' << bin;
#else
#define CLEAR(origin, stop)
#define D_COUT_BSQ(header, bsq)
#define D_COUT_BIN(header, bout)
#endif

namespace _ {

inline CHA* BInBegin(BIn* bin) {
  return reinterpret_cast<CHA*>(bin) + sizeof(BIn);
}

CHA* BInEnd(BIn* bin) {
  D_ASSERT(bin);
  return reinterpret_cast<CHA*>(bin) + bin->size;
}

ISW SlotLength(CHA* origin, CHA* stop, UIW size) {
  D_ASSERT(origin < stop);
  return stop - origin;
}

ISW SlotSpace(CHA* origin, CHA* stop, UIW size) {
  D_ASSERT(origin < stop);
  return size - (stop - origin);
}

ISC BInSpace(BIn* bin) {
  D_ASSERT(bin);
  CHA* txb_ptr = reinterpret_cast<CHA*>(bin);
  return (ISC)SlotSpace(txb_ptr + bin->origin, txb_ptr + bin->stop, bin->size);
}

ISC BinBufferLength(BIn* bin) {
  D_ASSERT(bin);
  CHA* origin = BInBegin(bin);
  return (ISC)SlotLength(origin + bin->origin, origin + bin->stop, bin->size);
}

#if USING_SCRIPT2_TEXT == YES_0
const CHA** STRBInStates() {
  static const CHA* kStateStrands[] = {
      "Address",       //< 0
      "Args",          //< 1
      "UTF-8",         //< 2
      "UTF-16",        //< 3
      "UTF-32",        //< 4
      "Varint",        //< 5
      "CObj",          //< 6
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
  D_COUT("\nBIn " << STRError(error) << " error!");
  return reinterpret_cast<const Op*>(error);
}

/* Used to return an erroneous result from a B-Output.
    @param bin    The source BIn.
    @param error   The error type.
    @param header  The B-Sequence Header.
    @param offset  The offset to the type in error in the B-Sequence.
    @param address The address of the IUA in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BInError(BIn* bin, Error error, const ISC* header) {
  D_COUT("\nBIn %s error!", STRError(error));
  return reinterpret_cast<const Op*>(error);
}

/* Used to return an erroneous result from a B-Output.
    @param bin    The source BIn.
    @param error   The error type.
    @param header  The B-Sequence Header.
    @param offset  The offset to the type in error in the B-Sequence.
    @param address The address of the IUA in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BInError(BIn* bin, Error error, const ISC* header,
                          ISC offset) {
  D_COUT("\nBIn " << STRError(error) << " error!");
  return reinterpret_cast<const Op*>(error);
}

/* Used to return an erroneous result from a B-Output.
    @param bin    The source BIn.
    @param error   The error type.
    @param header  The B-Sequence Header.
    @param offset  The offset to the type in error in the B-Sequence.
    @param address The address of the IUA in error.
    @return         Returns a Static Error Op Result. */
inline const Op* BInError(BIn* bin, Error error, const ISC* header, ISC offset,
                          CHA* address) {
  D_COUT("\nBIn " << STRError(error) << " error!");
  return reinterpret_cast<const Op*>(error);
}

BIn* BInInit(UIW* socket, ISC size) {
  D_ASSERT(size >= kSlotSizeMin);

  BIn* bin = reinterpret_cast<BIn*>(socket);
  bin->size = size - sizeof(BIn);
  bin->origin = 0;
  bin->stop = 0;
  bin->read = 0;

#if D_THIS == 1
  MemoryClear(BInBegin(bin), size);
#endif
  return bin;
}

ISC BInStreamByte(BIn* bin) {
  CHA *origin = BInBegin(bin), *stop = origin + bin->size - 1;
  CHA *open = (CHA*)origin + bin->read, *origin = origin + bin->origin,
      *origin = origin;

  ISC length = (ISC)((origin < open) ? open - origin + 1
                                     : (stop - origin) + (open - origin) + 2);

  if (length < 1) {
    BInError(bin, cErrorBufferOverflow, Params<1, kSTR>(), 2, origin);
    return -1;
  }
  // IUA b = *cursor;
  bin->stop = (++origin >= stop) ? static_cast<ISC>(Size(origin, stop))
                                 : static_cast<ISC>(Size(origin, origin));
  return 0;
}

BOL BInIsReadable(BIn* bin) { return BinBufferLength(bin) > 0; }

const Op* BInRead(BIn* bin, const ISC* params, void** args) {
  D_COUT_BSQ("\nReading ", params);
  D_COUT_BIN(" from B-Input:", bin);

  if (!bin) {
    return BInError(bin, cErrorImplementation);
  }
  if (!params) {
    return BInError(bin, cErrorImplementation);
  }
  if (!args) {
    return BInError(bin, cErrorImplementation);
  }
  IUA ui1;       //< Temp variable.
  IUB ui2;       //< Temp variable.
  IUC ui4;       //< Temp variable.
  IUD ui8;       //< Temp variable.
  CHA* ui1_ptr;  //< Pointer to a cIUA.
  // IUB* ui2_ptr;              //< Pointer to a cIUB.
  IUC* ui4_ptr;              //< Pointer to a cIUC.
  IUD* ui8_ptr;              //< Pointer to a cIUA.
  ISC type,                  //< The current type being read.
      size,                  //< Size of the ring socket.
      length,                //< Length of the data in the socket.
      count,                 //< Argument length.
      index,                 //< Index in the params.
      arg_index = 0,         //< Index in the args.
      value,                 //< Temp variable.
      num_params = *params;  //< Number of params.
  IUB hash;                  //< Hash of the incoming data.

  if (num_params == 0) return 0;  //< Nothing to do.

  hash = kPrime2Unsigned;
  size = bin->size;

  CHA *origin = BInBegin(bin),             //< The beginning of the socket.
      *stop = origin + size - 1,           //< The stop of the socket.
          *origin = origin + bin->origin,  //< The origin of the data.
              *stop = origin + bin->stop;  //< The stop of the data.
                                           // const ISC* param = params + 1;
                                           // //< The current param.

  length = (ISC)SlotLength(origin, stop, size);

  // When we scan, we are reading from the beginning of the Slot socket.

  for (index = 1; index <= num_params; ++index) {
    type = params[index];
    D_COUT("\nparam:" << arg_index + 1 << " type:" << STRType(type)
                      << " start:" << TDelta<>(origin, start) << " stop:"
                      << TDelta<>(origin, stop) << " length:" << length);
    switch (type) {
      ;
      case cNIL:
        return BInError(bin, cErrorInvalidType, params, index, origin);
      case kADR:
      case kSTR:  //< _R_e_a_d__S_t_r_i_n_g_-_8____________________
                  // Load buffered-type argument length and increment the index.
        ++num_params;
        count = params[++index];
        //< @todo Replace with pointer arithmetic.
        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<CHA*>(args[arg_index]);
        if (ui1_ptr == nullptr)
          return BInError(bin, cErrorImplementation, params, index, origin);
        D_COUT("\nReading kSTR:0x" << Hexf(ui1_ptr)
                                   << " with length:" << count);
        // Read CHA.
        ui1 = *origin;
        hash = HashPrime16(ui1, hash);
        if (++origin >= stop) origin -= size;
        *ui1_ptr = ui1;
        ++ui1_ptr;
        D_COUT(ui1);
        while ((ui1 != 0) && (count != 0)) {
          --count;
          if (count == 0)  //< Reached count:0 before nil-term CHA.
            return BInError(bin, cErrorBufferUnderflow, params, index, origin);
          ui1 = *origin;  // Read IUA from ring-socket.
          hash = HashPrime16(ui1, hash);
          if (++origin >= stop) origin -= size;
          *ui1_ptr++ = ui1;  // Write IUA to destination.
          D_COUT(ui1);
        }
        D_COUT("\" success!\n");
        if (type != kADR) {
          *ui1_ptr = 0;
          // No need to hash 0.
        }
        break;
      case cISA:  //< _R_e_a_d__1__B_y_t_e__T_y_p_e_s________________
      case cIUA:
      case cBOL:
#if USING_SCRIPT2_1_BYTE_TYPES
        if (length-- == 0)
          return BInError(bin, cErrorBufferUnderflow, params, index, origin);

        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<CHA*>(args[arg_index]);
        if (!ui1_ptr) break;

        // Read type;

        // Byte 1
        ui1 = *origin;  //< Read
        D_COUT(" '" << ui1 << "', ");
        hash = HashPrime16(ui1, hash);         //< Hash
        if (++origin >= stop) origin -= size;  //< Increment
        *ui1_ptr = ui1;                        //< Write
        break;
#else
        return BInError(bin, cErrorInvalidType, params, index, origin);
#endif
      case cISB:  //< _R_e_a_d__1_6_-_b_i_t__T_y_p_e_s_______________
      case cIUB:
      case cFPB:
#if USING_SCRIPT2_2_BYTE_TYPES
        if (length < 2)
          return BInError(bin, cErrorBufferUnderflow, params, index, origin);
        length -= 2;

        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<CHA*>(args[arg_index]);
        if (!ui1_ptr) break;

        // Read type

        // Byte 1
        ui1 = *origin;                         //< Read
        hash = HashPrime16(ui1, hash);         //< Hash
        if (++origin >= stop) origin -= size;  //< Increment
        *ui1_ptr = ui1;                        //< Write

        // Byte 2
        ui1 = *origin;                         //< Read
        hash = HashPrime16(ui1, hash);         //< Hash
        if (++origin >= stop) origin -= size;  //< Increment
        *(ui1_ptr + 1) = ui1;                  //< Write
        break;
#else
        return BInError(bin, cErrorInvalidType, params, index, origin);
#endif
      case SVI:  //< _R_e_a_d__S_i_g_n_e_d__V_a_r_i_n_t______________
      case UVI:  //< _R_e_a_d__U_n_s_i_g_n_e_d__V_a_r_i_n_t___________
#if ALU_SIZE <= 16
                 // Load next pointer and increment args.
        ui2_ptr = reinterpret_cast<IUB*>(args[arg_index]);
        if (ui2_ptr == nullptr)
          return BInError(bin, cErrorImplementation, params, index, origin);
        // SScan IUA 1.
        ui1 = *origin;
        if (++origin >= stop) origin -= size;
        hash = HashPrime16(ui1, hash);
        ui2 = ui1;
        temp = 7;   //< Number of bits to shift ui1 to the left.
        count = 5;  //< The max number_ of Varint4 bytes.
        while (ui1 >> 7 == 0) {
          if (length-- == 0)
            return BInError(bin, cErrorBufferUnderflow, params, index, origin);
          ui1 = *origin;
          if (++origin >= stop) origin -= size;
          hash = HashPrime16(ui1, hash);
          ui4 |= ((IUC)(ui1 & 0x7F)) << temp;
          //< @todo I'm starting to second guess if we need to mask ui1
          //< because we're packing them up and will overwrite.
          temp += 7;
          if (--count == 0)
            return BInError(bin, cErrorVarintOverflow, params, index, origin);
        }
        if (count == 5)  //< If there is only one IUA we need to
          ui4 &= 0x7F;   //< mask off the terminating varint bit.
        if (type == SVI) ui4 = TypeUnpackVarint<IUC>(ui4);
        *ui4_ptr = ui4;
        break;
#else
                 // Load next pointer and increment args.
        ui4_ptr = reinterpret_cast<IUC*>(args[arg_index]);
        if (ui4_ptr == nullptr)
          return BInError(bin, cErrorImplementation, params, index, origin);

        // SScan IUA 1.
        ui1 = *origin;
        if (++origin >= stop) origin -= size;
        hash = HashPrime16(ui1, hash);
        ui4 = ui1;
        ui2 = 7;    //< Number of bits to shift ui1 to the left.
        count = 5;  //< The max number_ of Varint4 bytes.
        while (ui1 >> 7 == 0) {
          if (length-- == 0)
            return BInError(bin, cErrorBufferUnderflow, params, index, origin);
          ui1 = *origin;
          if (++origin >= stop) origin -= size;
          hash = HashPrime16(ui1, hash);
          ui4 |= ((IUC)(ui1 & 0x7F)) << ui2;
          //< @todo I'm starting to second guess if we need to mask ui1
          //< because we're packing them up and will overwrite.
          ui2 += 7;
          if (--count == 0)
            return BInError(bin, cErrorVarintOverflow, params, index, origin);
        }
        if (count == 5)  //< If there is only one IUA we need to
          ui4 &= 0x7F;   //< mask off the terminating varint bit.
        if (type == SVI) ui4 = TypeUnpackVarint<IUC>(ui4);
        *ui4_ptr = ui4;
        break;
#endif
      case cISC:  //< _R_e_a_d__3_2_-_b_i_t__T_y_p_e_s_______________
      case cIUC:
      case cFPC:
      case kTM4:
#if USING_SCRIPT2_4_BYTE_TYPES
        if (length < 4)
          return BInError(bin, cErrorBufferUnderflow, params, index, origin);
        length -= 4;

        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<CHA*>(args[arg_index]);
        if (!ui1_ptr) break;

        // Read type

        for (value = sizeof(IUC); value > 0; --value) {
          // Byte 1
          ui1 = *origin;                         //< Read
          hash = HashPrime16(ui1, hash);         //< Hash
          if (++origin >= stop) origin -= size;  //< Increment
          *ui1_ptr++ = ui1;                      //< Write
        }
#else
        return BInError(bin, cErrorInvalidType, params, index, origin);
#endif
      case kTM8:  //< _R_e_a_d__6_4_-_b_i_t__T_y_p_e_s_______________
      case cISD:
      case cIUD:
      case cFPD:
#if USING_SCRIPT2_8_BYTE_TYPES
        if (length < 8)
          return BInError(bin, cErrorBufferUnderflow, params, index, origin);
        length -= 8;

        // Load next pointer and increment args.
        ui1_ptr = reinterpret_cast<CHA*>(args[arg_index]);
        if (!ui1_ptr) break;

        // Read type
        for (value = sizeof(IUD); value > 0; --value) {
          // Byte 1
          ui1 = *origin;                         //< Read
          hash = HashPrime16(ui1, hash);         //< Hash
          if (++origin >= stop) origin -= size;  //< Increment
          *ui1_ptr++ = ui1;                      //< Write
        }
        break;
#else
        return BInError(bin, cErrorInvalidType, params, index, origin);
#endif
      case SV8:  //< _R_e_a_d__V_a_r_i_n_t__8____________________
      case UV8:
        // Load next pointer and increment args.
        ui8_ptr = reinterpret_cast<IUD*>(args[arg_index]);
        if (!ui8_ptr) {
          return BInError(bin, cErrorImplementation, params, index, origin);
        }
        // SScan IUA 1.
        ui1 = *origin;
        if (++origin >= stop) origin -= size;
        hash = HashPrime16(ui1, hash);
        ui8 = ui1;
        ui2 = 7;    //< Number of bits to shift ui1 to the left.
        count = 9;  //< The max number_ of Varint8 bytes.
        while (ui1 >> 7 == 0) {
          if (length-- == 0)
            return BInError(bin, cErrorBufferUnderflow, params, index, origin);
          ui1 = *origin;
          if (++origin >= stop) origin -= size;
          hash = HashPrime16(ui1, hash);
          if (count == 1) {
            // Varint 8 differs from Varint 2 and 4 in that on the
            // last IUA, IUA 9 of 9, there is no terminating
            // varint bit.
            ui8 |= ((IUD)(ui1)) << ui2;
            break;
          }
          ui8 |= ((IUD)(ui1 & 0x7F)) << ui2;
          //< @todo I'm starting to second guess if we need to mask
          //< ui1 because we're packing them up and will overwrite.
          ui2 += 7;
          if (--count == 0)
            return BInError(bin, cErrorVarintOverflow, params, index, origin);
        }
        if (count == 9)  //< If there is only one IUA we need to
          ui8 &= 0x7F;   //< mask off the terminating varint bit.
        if (type == SV8) ui8 = TypeUnpackVarint<IUD>(ui8);
        *ui8_ptr = ui8;
        break;
      case kBSQ:  //< _B_-_S_e_q_u_e_n_c_e__S_t_r_i_n_g______________
#if USING_BSC
        ui1_ptr = reinterpret_cast<CHA*>(args[arg_index]);
        if (ui1_ptr == nullptr)
          return BInError(bin, cErrorImplementation, params, index, origin);
        ui1 = *origin;
#endif
      default: {  //< It's an Array
        D_COUT("\nIt's an array!\n");
#if USING_SCRIPT2_ARRAY
        switch (type & 0x60) {
          case 0: {
            if ((type < cLST) && (type < kMAP))
              return BInError(bin, cErrorInvalidType, params, index, origin);
            if (length < 1)  // 1 IUA for the width word.
              return BInError(bin, cErrorBufferUnderflow, params, index,
                              origin);

            ui1_ptr = reinterpret_cast<CHA*>(args[arg_index]);
            if (ui1_ptr == nullptr)
              return BInError(bin, cErrorImplementation, params, index, origin);

            ui1 = *origin;
            if (++origin >= stop) origin -= size;
            hash = HashPrime16(ui1, hash);
            if (ui1 > length - 1)
              return BInError(bin, cErrorBufferOverflow, params, index, origin);
            length = length - count - 1;
            count = (UIW)ui1;
            break;
          }
          case 1: {
            if (length < 2)  // 2 IUA for the width word.
              return BInError(bin, cErrorBufferUnderflow, params, index,
                              origin);
            length -= 2;
            ui2_ptr = reinterpret_cast<IUB*>(args[arg_index]);
            if (ui2_ptr == nullptr)
              return BInError(bin, cErrorImplementation, params, index, origin);

            for (temp = 0; temp <= sizeof(IUB); temp += 8) {
              ui1 = *origin;
              if (++origin >= stop) origin -= size;
              hash = HashPrime16(ui1, hash);
              ui2 |= ((IUB)ui1) << temp;
            }
            if (ui2 > length)
              return BInError(bin, cErrorBufferOverflow, params, index, origin);
            length -= count;
            count = (UIW)ui2;
            ui1_ptr = reinterpret_cast<CHA*>(ui2_ptr);
            break;
          }
          case 2: {
            if (length < 4)  // 4 IUA for the width word.
              return BInError(bin, cErrorBufferUnderflow, params, index,
                              origin);
            length -= 4;
            ui4_ptr = reinterpret_cast<IUC*>(args[arg_index]);
            if (ui4_ptr == nullptr)
              return BInError(bin, cErrorImplementation, params, index, origin);

            for (temp = 0; temp <= sizeof(IUC); temp += 8) {
              ui1 = *origin;
              if (++origin >= stop) origin -= size;
              hash = HashPrime16(ui1, hash);
              ui4 |= ((IUC)ui1) << temp;
            }
            if (ui4 >= length)
              return BInError(bin, cErrorBufferOverflow, params, index, origin);
            length -= count;
            count = (UIW)ui4;
            ui1_ptr = reinterpret_cast<CHA*>(ui4_ptr);
            break;
          }
          case 3: {  // 8 IUA for the width word.
            if (length < 9)
              return BInError(bin, cErrorBufferUnderflow, params, index,
                              origin);
            length -= 8;
            ui8_ptr = reinterpret_cast<IUD*>(args[arg_index]);
            if (ui8_ptr == nullptr)
              return BInError(bin, cErrorImplementation, params, index, origin);

            for (temp = 0; temp <= sizeof(IUD); temp += 8) {
              ui1 = *origin;
              if (++origin >= stop) origin -= size;
              hash = HashPrime16(ui1, hash);
              ui8 |= ((IUD)ui1) << temp;
            }
            if (ui8 > length)
              return BInError(bin, cErrorBufferOverflow, params, index, origin);
            length -= count;
            count = (UIW)ui8;
            ui1_ptr = reinterpret_cast<CHA*>(ui8_ptr);
            break;
          }
          default:
            return BInError(bin, cErrorImplementation, params, index, origin);
        }

        if (length < count)
          return BInError(bin, cErrorBufferOverflow, params, index, origin);
        if (count == 0) break;  //< Not sure if this is an error.
        if (origin + count >= stop) {
          for (; size - count > 0; --count) {
            ui1 = *origin;
            if (++origin >= stop) origin -= size;
            hash = HashPrime16(ui1, hash);
            *ui1_ptr = ui1;
            ++ui1_ptr;
          }
          stop = origin - 1;
          for (; count > 0; --count) {
            ui1 = *origin;
            if (++origin >= stop) origin -= size;
            hash = HashPrime16(ui1, hash);
            *ui1_ptr = ui1;
            ++ui1_ptr;
          }
          break;
        }
        for (; count > 0; --count) {
          ui1 = *origin;
          if (++origin >= stop) origin -= size;
          hash = HashPrime16(ui1, hash);
          *ui1_ptr = ui1;
          ++ui1_ptr;
        }
        break;
#endif  //< D_THIS
      }
    }
    ++arg_index;
    D_COUT(" |");
  }
  D_COUT("\nHash expected:0x" << Hexf(hash));
  if (length < 2)
    return BInError(bin, cErrorBufferUnderflow, params, index, origin);
  ui2 = *origin;
  if (++origin >= stop) origin -= size;
  ui1 = *origin;
  if (++origin >= stop) origin -= size;
  ui2 |= (((IUB)ui1) << 8);
  D_COUT("found:0x" << Hexf(ui2));
  if (hash != ui2)
    return BInError(bin, cErrorInvalidHash, params, index, origin);

  D_COUT("\nDone reading\n");
  CLEAR(origin, stop)

  // Convert pointer back to offset
  bin->origin = (ISC)Size(origin, origin);

  return 0;
}

#if USING_SCRIPT2_TEXT
UTF1& Print(UTF1& utf, BIn* bin) {
  D_ASSERT(bin);

  ISC size = bin->size;
  return utf << Line('_', 80) << " size:" << bin->size
             << " start:" << bin->origin << " stop:" << bin->stop
             << " read:" << bin->read
             << Socket(BInBegin(bin), size + sizeof(BIn));
}
#endif

}  // namespace _

#endif
