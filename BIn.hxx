// Copyright Kabuki Starship <kabukistarship.com>.
#include "BIn.hpp"
#if SEAM >= SCRIPT2_CRABS
#include "Error.hpp"
#include "Op.h"
#include "Slot.hpp"
#include "Varint.hpp"
#include "BOut.hpp"
#include "BSeq.hpp"
#include "Hash.hpp"
//#include "Slot.hpp"
#if SEAM == SCRIPT2_CRABS
#include "_Debug.hxx"
#define CLEAR(origin, stop) \
  while (origin <= stop) *origin++ = ' ';
#else
#include "_Release.hxx"
#define CLEAR(origin, stop)
#endif
namespace _ {

  IUA* BInEnd(BIn* bin) { return TPtr<IUA>(bin) + bin->size; }

ISW SlotLength(IUA* origin, IUA* stop, IUW size) {
  return stop - origin;
}

ISW SlotSpace(IUA* origin, IUA* stop, IUW size) {
  return size - (stop - origin);
}

ISN BInSpace(BIn* bin) {
  IUA* txb_ptr = TPtr<IUA>(bin);
  return ISN(SlotSpace(txb_ptr + bin->origin, txb_ptr + bin->stop, bin->size));
}

ISN BinBooferLength(BIn* bin) {
  IUA* origin = BInBegin(bin);
  return ISN(SlotLength(origin + bin->origin, origin + bin->stop, bin->size));
}

/* Used to return an erroneous result from a B-Output.
@param error The error type.
@return Returns a Static Error Op Result. */
inline const Op* BInError(BIn* bin, ERC error) {
  D_COUT("\nBIn " << TAErrors<>(error) << " error!");
  return OpError(error);
}

/* Used to return an erroneous result from a B-Output.
@param bin    The source BIn.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Op Result. */
inline const Op* BInError(BIn* bin, ERC error, const ISN* header) {
  D_COUT("\nBIn %s error!" << TAErrors<>(error));
  return OpError(error);
}

/* Used to return an erroneous result from a B-Output.
@param bin    The source BIn.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Op Result. */
inline const Op* BInError(BIn* bin, ERC error, const ISN* header,
                          ISN offset) {
  D_COUT("\nBIn " << TAErrors<>(error) << " error!");
  return OpError(error);
}

/* Used to return an erroneous result from a B-Output.
@param bin        The source BIn.
@param error      The error type.
@param header     The B-Sequence Header.
@param bsq_error  The offset to the type in error in the B-Sequence.
@param error_byte The address of the IUA in error.
@return Returns a Static Error Op Result. */
inline const Op* BInError(BIn* bin, ERC error, const ISN* header, ISN bsq_error,
                          IUA* error_byte) {
  D_COUT("\nBIn " << TAErrors<>(error) << " error at " <<
         TDelta<>(BInBegin(bin), error_byte));
  return OpError(error);
}

BIn* BInInit(IUW* socket, ISN size) {
  D_ASSERT(size >= SlotBytesMin);

  BIn* bin = TPtr<BIn>(socket);
  bin->size = size - sizeof(BIn);
  bin->origin = 0;
  bin->stop = 0;
  bin->read = 0;
  D_ARRAY_WIPE(BInBegin(bin), size);
  return bin;
}

ISN BInStreamByte(BIn* bin) {
  IUA* begin  = BInBegin(bin),
     * end    = begin + bin->size - 1,
     * read   = begin + bin->read, 
     * origin = begin + bin->origin;

  ISN length = (ISN)((origin < read) ? read - origin + 1
                                     : (end - origin) + (read - origin) + 2);

  if (length < 1) {
    BInError(bin, ErrorBooferOverflow, TParams<1, _STR>(), 2, origin);
    return -1;
  }
  bin->stop = (++origin >= end) ? TDelta<ISN>(origin, end)
                                 : TDelta<ISN>(origin, origin);
  return 0;
}

BOL BInIsReadable(BIn* bin) { return BinBooferLength(bin) > 0; }

const Op* BInRead(BIn* bin, const ISN* params, void** args) {
  D_COUT("\nReading ");
  D_COUT_BSQ(params);
  D_COUT(" from B-Input:");
  D_COUT_BIN(bin);

  if (!bin) {
    return BInError(bin, ErrorImplementation);
  }
  if (!params) {
    return BInError(bin, ErrorImplementation);
  }
  if (!args) {
    return BInError(bin, ErrorImplementation);
  }
  IUA  iua;                   //< Temp variable.
  IUB  iub;                   //< Temp variable.
  IUC  iuc;                   //< Temp variable.
  IUD  iud;                   //< Temp variable.
  CHA* iua_ptr;               //< Pointer to a _IUA.
  IUB* iub_ptr;               //< Pointer to a _IUB.
  IUC* iuc_ptr;               //< Pointer to a _IUC.
  IUD* iud_ptr;               //< Pointer to a _IUA.
  DTB  type;                  //< The current type being read.
  ISN  size,                  //< Size of the ring socket.
       length,                //< Length of the data in the socket.
       count,                 //< Argument length.
       index,                 //< Index in the params.
       arg_index = 0,         //< Index in the args.
       num_params = *params;  //< Number of params.
  IUB  hash;                  //< Hash of the incoming data.

  if (num_params == 0) return 0;  //< Nothing to do.

  hash = PRIME_LARGEST_IUB;
  size = bin->size;

  IUA* begin  = BInBegin(bin),        //< The beginning of the socket.
     * end    = begin + size - 1,     //< The end of the socket.
     * origin = begin + bin->origin,  //< The origin of the data.
     * stop   = begin + bin->stop;    //< The stop of the data.
  // const ISN* param = params + 1;   //< The current param.

  length = TSlotLength<ISN>(origin, stop, size);
  
  IUC temp = 0; //@todo This won't let me init this in the cases?

  // When we scan, we are reading from the beginning of the Slot socket.

  for (index = 1; index <= num_params; ++index) {
    type = params[index];
    D_COUT("\nparam:" << arg_index + 1 << " type:" << ATypef(type) <<
           " origin:" << TDelta<>(origin, origin) << " stop:" <<
           TDelta<>(origin, stop) << " length:" << length);
    switch (type) {
      case _NIL:
        return BInError(bin, ErrorInvalidType, params, index, origin);
      case _ISA:  //< _R_e_a_d__1__B_y_t_e__T_y_p_e_s________________
      case _IUA:
#if USING_SCRIPT2_1_BYTE_TYPES
        if (length-- == 0)
          return BInError(bin, ErrorBooferUnderflow, params, index, origin);

        // Load next pointer and increment args.
        iua_ptr = TPtr<CHA>(args[arg_index]);
        if (!iua_ptr) break;

        // Read type;

        // Byte 1
        iua = *origin;  //< Read
        D_COUT(" '" << iua << "', ");
        hash = THash<IUB>(iua, hash);         //< Hash
        if (++origin >= stop) origin -= size; //< Increment
        *iua_ptr = iua;                       //< Write
        break;
#else
        return BInError(bin, ErrorInvalidType, params, index, origin);
#endif
      case _ISB:  //< _R_e_a_d__1_6_-_b_i_t__T_y_p_e_s_______________
      case _IUB:
      case _FPB:
//#if CPU_WORD_SIZE == CPU_16_BIT
//      case _BOL:
//#endif
#if USING_SCRIPT2_2_BYTE_TYPES
        if (length < 2)
          return BInError(bin, ErrorBooferUnderflow, params, index, origin);
        length -= 2;

        // Load next pointer and increment args.
        iua_ptr = TPtr<CHA>(args[arg_index]);
        if (!iua_ptr) break;

        // Read type

        // Byte 1
        iua = *origin;                         //< Read
        hash = HashIUB(iua, hash);             //< Hash
        if (++origin >= stop) origin -= size;  //< Increment
        *iua_ptr = iua;                        //< Write

        // Byte 2
        iua = *origin;                         //< Read
        hash = HashIUB(iua, hash);             //< Hash
        if (++origin >= stop) origin -= size;  //< Increment
        *(iua_ptr + 1) = iua;                  //< Write
        break;
#else
        return BInError(bin, ErrorInvalidType, params, index, origin);
#endif
      case _ISC:  //< _R_e_a_d__3_2_-_b_i_t__T_y_p_e_s_______________
      case _IUC:
      case _FPC:
#if USING_SCRIPT2_4_BYTE_TYPES
        if (length < 4)
          return BInError(bin, ErrorBooferUnderflow, params, index, origin);
        length -= 4;

        // Load next pointer and increment args.
        iua_ptr = TPtr<CHA>(args[arg_index]);
        if (!iua_ptr) break;

        // Read type

        for (ISN value = sizeof(IUC); value > 0; --value) {
          // Byte 1
          iua = *origin;                         //< Read
          hash = HashIUB(iua, hash);             //< Hash
          if (++origin >= stop) origin -= size;  //< Increment
          *iua_ptr++ = iua;                      //< Write
        }
#else
        return BInError(bin, ErrorInvalidType, params, index, origin);
#endif
      case _ISD:  //< _R_e_a_d__6_4_-_b_i_t__T_y_p_e_s_______________
      case _IUD:
      case _FPD:
#if USING_SCRIPT2_8_BYTE_TYPES
        if (length < 8)
          return BInError(bin, ErrorBooferUnderflow, params, index, origin);
        length -= 8;

        // Load next pointer and increment args.
        iua_ptr = TPtr<CHA>(args[arg_index]);
        if (!iua_ptr) break;

        // Read type
        for (ISN value = sizeof(IUD); value > 0; --value) {
          // Byte 1
          iua = *origin;                         //< Read
          hash = HashIUB(iua, hash);             //< Hash
          if (++origin >= stop) origin -= size;  //< Increment
          *iua_ptr++ = iua;                      //< Write
        }
        break;
#else
        return BInError(bin, ErrorInvalidType, params, index, origin);
#endif
      case STR_:  //< _R_e_a_d__S_t_r_i_n_g_-_8____________________
        // Load boofered-type argument length and increment the index.
        ++num_params;
        count = params[++index];
        //< @todo Replace with pointer arithmetic.
        // Load next pointer and increment args.
        iua_ptr = TPtr<CHA>(args[arg_index]);
        if (iua_ptr == nullptr)
          return BInError(bin, ErrorImplementation, params, index, origin);
        D_COUT("\nReading STR_:0x" << Hexf(iua_ptr) << " with length:" << 
               count);
        // Read CHA.
        iua = *origin;
        hash = HashIUB(iua, hash);
        if (++origin >= stop) origin -= size;
        *iua_ptr = iua;
        ++iua_ptr;
        D_COUT(iua);
        while ((iua != 0) && (count != 0)) {
          --count;
          if (count == 0)  //< Reached count:0 before nil-term CHA.
            return BInError(bin, ErrorBooferUnderflow, params, index, origin);
          iua = *origin;  // Read IUA from ring-socket.
          hash = HashIUB(iua, hash);
          if (++origin >= stop) origin -= size;
          *iua_ptr++ = iua;  // Write IUA to destination.
          D_COUT(iua);
        }
        D_COUT("\" success!\n");
        if (type != _ADR) {
          *iua_ptr = 0;
          // No need to hash 0.
        }
        break;
      //case _ISV:  //< _R_e_a_d__S_i_g_n_e_d__V_a_r_i_n_t______________
      //case _IUV:  //< _R_e_a_d__U_n_s_i_g_n_e_d__V_a_r_i_n_t___________
#if CPU_SIZE <= 16
                 // Load next pointer and increment args.
        iub_ptr = TPtr<IUB>(args[arg_index]);
        if (iub_ptr == nullptr)
          return BInError(bin, ErrorImplementation, params, index, origin);
        // SScan IUA 1.
        iua = *origin;
        if (++origin >= stop) origin -= size;
        hash = HashIUB(iua, hash);
        iub = iua;
        //ISN temp = 7;   //< Number of bits to shift iua to the left.
        temp = 7;   //< Number of bits to shift iua to the left.
        count = 5;  //< The max number_ of Varint4 bytes.
        while (iua >> 7 == 0) {
          if (length-- == 0)
            return BInError(bin, ErrorBooferUnderflow, params, index, origin);
          iua = *origin;
          if (++origin >= stop) origin -= size;
          hash = HashIUB(iua, hash);
          iuc |= IUC(iua & 0x7F) << temp;
          //< @todo I'm starting to second guess if we need to mask iua
          //< because we're packing them up and will overwrite.
          temp += 7;
          if (--count == 0)
            return BInError(bin, ErrorVarintOverflow, params, index, origin);
        }
        if (count == 5)  //< If there is only one IUA we need to
          iuc &= 0x7F;   //< mask off the terminating varint bit.
        if (type == _VSC) iuc = VSCUnpack(iuc);
        *iuc_ptr = iuc;
        break;
#else
                 // Load next pointer and increment args.
        iuc_ptr = TPtr<IUC>(args[arg_index]);
        if (iuc_ptr == nullptr)
          return BInError(bin, ErrorImplementation, params, index, origin);

        // SScan IUA 1.
        iua = *origin;
        if (++origin >= stop) origin -= size;
        hash = HashIUB(iua, hash);
        iuc = iua;
        iub = 7;    //< Number of bits to shift iua to the left.
        count = 5;  //< The max number_ of Varint4 bytes.
        while (iua >> 7 == 0) {
          if (length-- == 0)
            return BInError(bin, ErrorBooferUnderflow, params, index, origin);
          iua = *origin;
          if (++origin >= stop) origin -= size;
          hash = HashIUB(iua, hash);
          iuc |= ((IUC)(iua & 0x7F)) << iub;
          //< @todo I'm starting to second guess if we need to mask iua
          //< because we're packing them up and will overwrite.
          iub += 7;
          if (--count == 0)
            return BInError(bin, ErrorVarintOverflow, params, index, origin);
        }
        if (count == 5)  //< If there is only one IUA we need to
          iuc &= 0x7F;   //< mask off the terminating varint bit.
        if (type == SVI) iuc = TTypeUnpackVarint<IUC>(iuc);
        *iuc_ptr = iuc;
        break;
#endif
      case _VSD:  //< _R_e_a_d__V_a_r_i_n_t__8____________________
      case _VUD:
        // Load next pointer and increment args.
        iud_ptr = TPtr<IUD>(args[arg_index]);
        if (!iud_ptr) {
          return BInError(bin, ErrorImplementation, params, index, origin);
        }
        // SScan IUA 1.
        iua = *origin;
        if (++origin >= stop) origin -= size;
        hash = HashIUB(iua, hash);
        iud = iua;
        iub = 7;    //< Number of bits to shift iua to the left.
        count = 9;  //< The max number_ of Varint8 bytes.
        while (iua >> 7 == 0) {
          if (length-- == 0)
            return BInError(bin, ErrorBooferUnderflow, params, index, origin);
          iua = *origin;
          if (++origin >= stop) origin -= size;
          hash = HashIUB(iua, hash);
          if (count == 1) {
            // Varint 8 differs from Varint 2 and 4 in that on the
            // last IUA, IUA 9 of 9, there is no terminating
            // varint bit.
            iud |= ((IUD)(iua)) << iub;
            break;
          }
          iud |= ((IUD)(iua & 0x7F)) << iub;
          //< @todo I'm starting to second guess if we need to mask
          //< iua because we're packing them up and will overwrite.
          iub += 7;
          if (--count == 0)
            return BInError(bin, ErrorVarintOverflow, params, index, origin);
        }
        if (count == 9)  //< If there is only one IUA we need to
          iud &= 0x7F;   //< mask off the terminating varint bit.
        if (type == _VSD) iud = VSDUnpack(iud);
        *iud_ptr = iud;
        break;
      case _BSQ:  //< _B_-_S_e_q_u_e_n_c_e__S_t_r_i_n_g______________
#if USING_BSQ
        iua_ptr = TPtr<CHA>(args[arg_index]);
        if (iua_ptr == nullptr)
          return BInError(bin, ErrorImplementation, params, index, origin);
        iua = *origin;
#endif
      default: {
        D_COUT("\nIt's an array!\n");
#if USING_SCRIPT2_ARRAY
        switch (type & 0x60) {
          case 0: {
            if ((type < _LST) && (type < _MAP))
              return BInError(bin, ErrorInvalidType, params, index, origin);
            if (length < 1)  // 1 IUA for the width word.
              return BInError(bin, ErrorBooferUnderflow, params, index,
                              origin);

            iua_ptr = TPtr<CHA>(args[arg_index]);
            if (iua_ptr == nullptr)
              return BInError(bin, ErrorImplementation, params, index, origin);

            iua = *origin;
            if (++origin >= stop) origin -= size;
            hash = HashIUB(iua, hash);
            if (iua > length - 1)
              return BInError(bin, ErrorBooferOverflow, params, index, origin);
            length = length - count - 1;
            count = IUW(iua);
            break;
          }
          case 1: {
            if (length < 2)  // 2 IUA for the width word.
              return BInError(bin, ErrorBooferUnderflow, params, index,
                              origin);
            length -= 2;
            iub_ptr = TPtr<IUB>(args[arg_index]);
            if (iub_ptr == nullptr)
              return BInError(bin, ErrorImplementation, params, index, origin);

            for (ISN i = 0; i <= sizeof(IUB); i += 8) {
              iua = *origin;
              if (++origin >= stop) origin -= size;
              hash = HashIUB(iua, hash);
              iub |= ((IUB)iua) << i;
            }
            if (iub > length)
              return BInError(bin, ErrorBooferOverflow, params, index, origin);
            length -= count;
            count = IUW(iub);
            iua_ptr = TPtr<CHA>(iub_ptr);
            break;
          }
          case 2: {
            if (length < 4)  // 4 IUA for the width word.
              return BInError(bin, ErrorBooferUnderflow, params, index,
                              origin);
            length -= 4;
            iuc_ptr = TPtr<IUC>(args[arg_index]);
            if (iuc_ptr == nullptr)
              return BInError(bin, ErrorImplementation, params, index, origin);

            for (ISN i = 0; i <= sizeof(IUC); i += 8) {
              iua = *origin;
              if (++origin >= stop) origin -= size;
              hash = HashIUB(iua, hash);
              iuc |= IUC(iua) << i;
            }
            if (iuc >= length)
              return BInError(bin, ErrorBooferOverflow, params, index, origin);
            length -= count;
            count = IUW(iuc);
            iua_ptr = TPtr<CHA>(iuc_ptr);
            break;
          }
          case 3: {  // 8 IUA for the width word.
            if (length < 9)
              return BInError(bin, ErrorBooferUnderflow, params, index,
                              origin);
            length -= 8;
            iud_ptr = TPtr<IUD>(args[arg_index]);
            if (iud_ptr == nullptr)
              return BInError(bin, ErrorImplementation, params, index, origin);

            for (ISN i = 0; i <= sizeof(IUD); i += 8) {
              iua = *origin;
              if (++origin >= stop) origin -= size;
              hash = HashIUB(iua, hash);
              iud |= IUD(iua) << i;
            }
            if (iud > length)
              return BInError(bin, ErrorBooferOverflow, params, index, origin);
            length -= count;
            count = IUW(iud);
            iua_ptr = TPtr<CHA>(iud_ptr);
            break;
          }
          default:
            return BInError(bin, ErrorImplementation, params, index, origin);
        }

        if (length < count)
          return BInError(bin, ErrorBooferOverflow, params, index, origin);
        if (count == 0) break;  //< Not sure if this is an error.
        if (origin + count >= stop) {
          for (; size - count > 0; --count) {
            iua = *origin;
            if (++origin >= stop) origin -= size;
            hash = HashIUB(iua, hash);
            *iua_ptr = iua;
            ++iua_ptr;
          }
          stop = origin - 1;
          for (; count > 0; --count) {
            iua = *origin;
            if (++origin >= stop) origin -= size;
            hash = HashIUB(iua, hash);
            *iua_ptr = iua;
            ++iua_ptr;
          }
          break;
        }
        for (; count > 0; --count) {
          iua = *origin;
          if (++origin >= stop) origin -= size;
          hash = HashIUB(iua, hash);
          *iua_ptr = iua;
          ++iua_ptr;
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
    return BInError(bin, ErrorBooferUnderflow, params, index, origin);
  iub = *origin;
  if (++origin >= stop) origin -= size;
  iua = *origin;
  if (++origin >= stop) origin -= size;
  iub |= (((IUB)iua) << 8);
  D_COUT("found:0x" << Hexf(iub));
  if (hash != iub)
    return BInError(bin, ErrorInvalidHash, params, index, origin);

  D_COUT("\nDone reading\n");
  CLEAR(origin, stop)

  // Convert pointer back to offset
  bin->origin = TDelta<ISN>(origin, origin);

  return 0;
}

const Op* BInRead(BOut* bout, const ISN* params, void** args) {
  return BInRead(TPtr<BIn>(bout), params, args);
}

}  //< namespace _

#endif
