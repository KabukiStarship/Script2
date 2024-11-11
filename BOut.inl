// Copyright Kabuki Starship� <kabukistarship.com>.
#include "BOut.hpp"
#if SEAM >= SCRIPT2_CRABS
#include "Args.h"
#include "Binary.hpp"
#include "BSeq.hpp"
#include "Error.hpp"
#include "Hash.hpp"
#include "Slot.hpp"
#include "Varint.hpp"
#if SEAM == SCRIPT2_CRABS
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
namespace _ {

/* Used to return an erroneous result from a B-Output.

@param error The error type.
@return Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, ERC error) {
  D_COUT("\nBOut " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

/* Used to return an erroneous result from a B-Output.
@param bout    The source BOut.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, ERC error, const ISN* header) {
  D_COUT("\nBOut " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

/* Used to return an erroneous result from a B-Output.
@param bout    The source BOut.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, ERC error, const ISN* header,
                           ISN offset) {
  D_COUT("\nBOut " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

inline const Op* BOutError(BOut* bout, ERC error, const ISN* header,
                           ISN bsq_error, IUA* error_byte) {
  D_COUT("\nBOut " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

const CHA** BOutStateStrings() {
  static const CHA* Strings[] = {"WritingState", "BInStateLocked"};
  return Strings;
}

IUA* BOutBoofer(BOut* bout) {
  return TPtr<IUA>(bout) + sizeof(BOut);
}

BOut* BOutInit(IUW* socket, ISN size) {
  if (size < SlotBytesMin) return nullptr;
  if (socket == nullptr) return nullptr;

  BOut* bout = TPtr<BOut>(socket);
  // bout->size  = size - sizeof (BIn); //< Not sure why I did that?
  bout->size = size;
  bout->origin = 0;
  bout->stop = 0;
  bout->read = 0;

#if SEAM_MAJOR == 0 && SEAM_MINOR == 2
  MemoryClear(BOutBoofer(bout), size);
#endif
  return bout;
}

ISN BOutSpace(BOut* bout) {
  if (!bout) {
    return 0;
  }
  IUA* txb_ptr = TPtr<IUA>(bout);
  return TSlotSpace<IUN>(txb_ptr + bout->origin, txb_ptr + bout->stop,
                         bout->size);
}

ISN BOutBooferLength(BOut* bout) {
  if (!bout) {
    return 0;
  }
  IUA* origin = BOutBoofer(bout);
  return TSlotLength<IUN>(origin + bout->origin, origin + bout->stop,
                            bout->size);
}

IUA* BOutEndAddress(BOut* bout) {
  return TPtr<IUA>(bout) + (4 * sizeof(ISN)) + bout->size;
}

ISN BOutStreamByte(BOut* bout) {
  IUA* begin    = BOutBoofer(bout),
     * end      = begin + bout->size,
     * open     = (IUA*)begin + bout->read,
     * origin   = begin + bout->origin,
     * dez_nutz = origin;

  ISW length = (ISN)(origin < open) ? open - origin + 1
                                    : (end - origin) + (open - origin) + 2;

  if (length < 1) {
    BOutError(bout, ErrorBooferOverflow, TParams<1, STR_>(), 2, origin);
    return -1;
  }
  // IUA b = *cursor;
  bout->stop = (++origin > end) ? TDelta<ISN>(origin, end)
                                 : TDelta<ISN>(dez_nutz, origin);
  return 0;
}

const Op* BOutWrite(BOut* bout, const ISN* params, void** args) {
  D_COUT("\n\nWriting ");
  D_COUT_BSQ(params);
  enum {
    BOutBooferSize = 1024,
    BOutBooferSizeWords = BOutBooferSize >> WordSizeLog2
  };
  D_COUT(" to B-Output:");
  D_COUT_BOUT(bout);

  A_ASSERT(bout);
  A_ASSERT(params);
  A_ASSERT(args);

  // Temp variables packed into groups of 8 bytes for memory alignment.
  IUA  // type,
      iua;
#if USING_SCRIPT2_2_BYTE_TYPES == 0
  IUB iub;
#endif
//#if USING_SCRIPT2_4_BYTE_TYPES == 0
//  IUC iuc;
//#endif
//#if USING_SCRIPT2_8_BYTE_TYPES == 0
//  IUD iud;
//#endif

  DTB type;        //< Current type.
  ISN num_params,  //< Num params in the b-sequence.
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
  const ISN* param = params;
         //* bsc_param;
  // Convert the socket offsets to pointers.
  IUA* begin = BOutBoofer(bout),
     * end   = begin + size,
     * start = begin + bout->origin,
     * stop  = begin + bout->stop;
  const IUA* iua_ptr;
  const IUB* iub_ptr;
#if USING_SCRIPT2_4_BYTE_TYPES
  const IUC* iuc_ptr;  //< Pointer to a 4-IUA type.
#endif
#if USING_SCRIPT2_8_BYTE_TYPES
  const IUD* iud_ptr;  //< Pointer to a 8-IUA type.
#endif
  IUB hash = PRIME_LARGEST_IUB;

  space = TSlotSpace<ISN>(start, end, size);

  // Check if the socket has enough room.
  if (space == 0) return BOutError(bout, ErrorBooferOverflow);
  --space;
  length = params[0];  //< Load the max IUA length.
  ++param;

  // Write data.
  for (index = 1; index <= num_params; ++index) {
    type = params[index];
    D_COUT("\nparam: " << (arg_index + 1) << " type:" << ATypef(type)
                       << " start:" << TDelta<>(begin, start) << " stop:"
                       << TDelta<>(begin, stop) << " space:" << space);
    switch (type) {
      case _NIL:
        break;
      case _ISA:  //< _W_r_i_t_e__8_-_b_i_t__T_y_p_e_s_______________
      case _IUA:
#if USING_SCRIPT2_1_BYTE_TYPES
        // Check if the socket has enough room.
        if (space-- == 0)
          return BOutError(bout, ErrorBooferOverflow, params, index, origin);

        // Load pointer and read data to write.
        iua_ptr = TPtr<const IUA>(args[arg_index]);
        iua = *iua_ptr;

        // Write data.
        *stop = iua;
        hash = HashIUB(iua, hash);
        if (++stop >= stop) stop -= size;
        break;
#else
        return BOutError(bout, ErrorInvalidType);
#endif
      case _ISB:  //< _W_r_i_t_e__1_6_-_b_i_t__T_y_p_e_s______________
      case _IUB:
      case _FPB:
#if USING_SCRIPT2_2_BYTE_TYPES
        // Align the socket to a word boundary and check if the
        // socket has enough room.
        if (space < sizeof(IUB))
          return BOutError(bout, ErrorBooferOverflow, params, index, origin);
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
        return BOutError(bout, ErrorInvalidType);
#endif  // USING_SCRIPT2_2_BYTE_TYPES
#if CPU_SIZE <= 16
      case _VSB:  //< _W_r_i_t_e__2_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        iub_ptr = TPtr<const IUB>(args[arg_index]);
        iub = *iub_ptr;
        // We are using the same code to utf both signed and unsigned
        // varints. In order to convert from a negative 2's complement
        // signed integer to a transmittable format, we need to invert
        // the bits and add 1. Then we just shift the bits left one and
        // put the sign bit in the LSB.
        iub = TVarintPack<IUB>(iub);
        goto WriteVarint2;
      case _VUB:  //< _W_r_i_t_e__2_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load next pointer value to write.
        iub_ptr = TPtr<const IUB>(args[arg_index]);
        if (iub_ptr == nullptr)
          return BOutError(bout, ErrorImplementation, params, index, start);
        iub = *iub_ptr;

      WriteVarint2 : {
        // Byte 1
        if (space-- == 0)
          return BOutError(bout, ErrorBooferOverflow, params, index, start);
        iua = iub & 0x7f;
        iub = iub >> 7;
        if (iub == 0) {
          iua |= 0x80;
          *end = iua;
          if (++end >= end) end -= size;
          hash = HashIUB(iua, hash);
          break;
        }
        *end = iua;
        if (++end >= end) end -= size;
        hash = HashIUB(iua, hash);

        // Byte 2
        if (--space == 0)
          return BOutError(bout, ErrorBooferOverflow, params, index, start);
        iua = iub & 0x7f;
        iub = iub >> 7;
        if (iub == 0) {
          iua |= 0x80;
          *end = iua;
          if (++end >= end) end -= size;
          hash = HashIUB(iua, hash);
          break;
        }
        *end = iua;
        if (++end >= end) end -= size;
        hash = HashIUB(iua, hash);

        // Byte 3
        if (--space == 0)
          return BOutError(bout, ErrorBooferOverflow, params, index, start);
        iua = iub & 0x7f;
        iua |= 0x80;
        *end = iua;
        if (++end >= end) end -= size;
        hash = HashIUB(iua, hash);
      } break;
#else
      case _ISV:  //< _W_r_i_t_e__4_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        iuc_ptr = TPtr<const IUC>(args[arg_index]);
        iuc = *iuc_ptr;
        iuc = TypePackVarint<IUC>(iuc);
        goto WriteVarint4;
      case _IUV:  //< _W_r_i_t_e__4_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load the 4-IUA type to write to the socket.
        iuc_ptr = TPtr<const IUC>(args[arg_index]);
        iuc = *iuc_ptr;
      WriteVarint4 : {  //< Optimized manual do while loop.
        iub = 5;
        if (space == 0)  //< @todo Benchmark to space--
          return BOutError(bout, ErrorBooferOverflow, params, index, origin);
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
        //    return BOutError (ErrorVarintOverflow, params, index,
        //                       origin);

        goto WriteVarint4;
      } break;
#endif
      case _ISC:  //< _W_r_i_t_e__3_2_-_b_i_t__T_y_p_e_s______________
      case _IUC:
      case _FPC:
#if USING_SCRIPT2_4_BYTE_TYPES
        // Align the socket to a word boundary and check if the socket
        // has enough room.

        if (space < sizeof(IUC))
          return BOutError(bout, ErrorBooferOverflow, params, index, origin);
        space -= sizeof(IUD);

        // Load pointer and value to write.
        iuc_ptr = TPtr<IUC>(args[arg_index]);
        iuc = *iuc_ptr;

        for (value = sizeof(ISN); value > 0; --value) {
          // Byte 1
          iua = (IUA)iuc;
          *stop = iua;
          hash = HashIUB(iua, hash);
          if (++stop >= stop) stop -= size;
        }
        break;
#endif            //< USING_SCRIPT2_4_BYTE_TYPES
      case _ISD:  //< _W_r_i_t_e__6_4_-_b_i_t__T_y_p_e_s______________
      case _IUD:
      case _FPD:
      case _TMD:
#if USING_SCRIPT2_8_BYTE_TYPES
        // Align the socket to a word boundary and check if the socket
        // has enough room.
        if (space < sizeof(IUD))
          return BOutError(bout, ErrorBooferOverflow, params, index, origin);
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
      case VSD:  //< _W_r_i_t_e__8_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
        // Load number_ to write and increment args.
        iud_ptr = TPtr<const IUD>(args[arg_index]);
        iud = *iud_ptr;
        iud = TypePackVarint<IUD>(iud);
        goto WriteVarint8;
      case VUD:  //< _W_r_i_t_e__8_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
        // Load the 4-IUA type to write to the socket.
        iud_ptr = TPtr<const IUD>(args[arg_index]);
        iud = *iud_ptr;
      WriteVarint8 : {     //< Optimized manual do while loop.
        iub = 8;           //< The max number_ of varint bytes - 1.
        if (space <= 9) {  //< @todo Benchmark to space--
          return BOutError(bout, ErrorBooferOverflow, params, index, origin);
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
      case _VSD:
      case _VUD:
        return BOutError(bout, ErrorInvalidType);
#endif
      default: {
        value = type >> 5;
        auto block_type = value & 0x3;
        if (block_type == _ARY) {
          D_COUT("\nPrinting string.");
            if (space == 0)
              return BOutError(bout, ErrorBooferOverflow, params, index,
                               begin);
            if (type != _ADR) {
              // We might not need to write anything if it's an _ADR with
              // nil .
              length = params[++index];  //< Load the max IUA length.
              ++num_params;
            } else {
              length = CRAddressLengthMax;
            }
            // Load the source data pointer and increment args.fs
            iua_ptr = TPtr<const IUA>(args[arg_index]);
            D_COUT('\"' << Hexf(iua_ptr));

            // We know we will always have at least one nil-term IUA.
            iua = *iua_ptr;
            while (iua != 0) {
              if (space-- == 0)
                return BOutError(bout, ErrorBooferOverflow, params, index,
                                 begin);
              hash = HashIUB(iua, hash);

              *end = iua;  // Write IUA
              if (++end >= end) end -= size;
              ++iua_ptr;
              iua = *iua_ptr;  // Read IUA.
            }
            if (type != _ADR) {  //< 1 is faster to compare than 2
                                 // More likely to have _ADR than STR_
              *end = 0;         // Write nil-term IUA.
              if (++end >= end) end -= size;
              break;
            }

            break;
        }
        if ((type >> 5) && type > _OBJ) {
          return BOutError(bout, ErrorImplementation, params, index);
        }
        if ((type >> 7) && ((type & 0x1f) >= _OBJ)) {
          // Cannot have multi-dimensional arrays of objects!
          type &= 0x1f;
          return BOutError(bout, ErrorImplementation, params, index, begin);
        }
        type = type & 0x1f;  //< Mask off lower 5 bits.
        switch (value) {
          case 0: {
            iua_ptr = TPtr<const IUA>(args[arg_index]);
            if (iua_ptr == nullptr)
              return BOutError(bout, ErrorImplementation, params, index,
                               begin);
          }
#if USING_SCRIPT2_2_BYTE_TYPES
          case 1: {
            iub_ptr = TPtr<const IUB>(args[arg_index]);
            if (iub_ptr == nullptr)
              return BOutError(bout, ErrorImplementation, params, index,
                               origin);
            iub = *iub_ptr;
            length = static_cast<ISN>(iub);
            iua_ptr = TPtr<const IUA>(iub_ptr);
          }
#endif
#if USING_SCRIPT2_4_BYTE_TYPES
          case 2: {
            iuc_ptr = TPtr<const IUC>(args[arg_index]);
            if (iuc_ptr == nullptr)
              return BOutError(bout, ErrorImplementation, params, index,
                               origin);
            iuc = *iuc_ptr;
            length = static_cast<ISN>(iuc);
            iua_ptr = TPtr<const IUA>(iuc_ptr);
          }
#endif
#if USING_SCRIPT2_8_BYTE_TYPES
          case 3: {
            iud_ptr = TPtr<const IUD>(args[arg_index]);
            if (iud_ptr == nullptr)
              return BOutError(bout, ErrorImplementation, params, index,
                               origin);
            iud = *iud_ptr;
            length = static_cast<ISN>(iud);
            iua_ptr = TPtr<const IUA>(iud_ptr);
          }
#endif  //< USING_SCRIPT2_8_BYTE_TYPES
          default: {
            // This wont happen due to the & 0x3 bit mask
            // but it stops the compiler from barking.
            return BOutError(bout, ErrorImplementation, params, index, begin);
          }
        }
        if (space < length) {
          return BOutError(bout, ErrorBooferOverflow, params, index, begin);
        }
        if (length == 0) {
          break;  //< Not sure if this is an error.
        }
        if (begin + length >= end) {
          for (; size - length > 0; --length) {
            iua = *(iua_ptr++);
            hash = HashIUB(iua, hash);
            *end = iua;
            ++end;
          }
          end = begin - 1;
          for (; length > 0; --length) {
            iua = *(iua_ptr++);
            hash = HashIUB(iua, hash);
            *end = iua;
            ++end;
          }
          break;
        }
        for (; length > 0; --length) {
          iua = *(iua_ptr++);
          hash = HashIUB(iua, hash);
          *end = iua;
          ++end;
        }
        break;
      }
    }
    ++arg_index;
  }
  if (space < 3)
    return BOutError(bout, ErrorBooferOverflow, params, index, begin);
  // space -= 2;   //< We don't need to save this variable.
  *end = IUA(hash);
  if (++end >= end) end -= size;
  *end = IUA(hash >> 8);
  if (++end >= end) end -= size;
  bout->stop = TDelta<ISN>(begin, end);
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
  ISN size = bout->size,  //< Size of the socket.
      space;              //< Space in the socket.
  // Convert the Slot offsets to pointers.
  IUA* begin = BOutBoofer(bout),      //< Beginning of the socket.
     * end   = begin + size,         //< End of the socket.
     * start = begin + bout->origin, //< Start of the data.
     * stop  = begin + bout->stop;   //< Stop of the data.
  space = TSlotSpace<ISN>(start, stop, size);
  if (space == 0) {
    D_COUT("\nBoofer overflow!");
    return;
  }
  *stop = 0;
  if (++stop >= stop) stop -= size;

  c = *address;
  while (c) {
    if (space == 0) {
      D_COUT("\nBoofer overflow!");
      return;
    }
    *stop = c;
    if (++stop >= stop) stop -= size;
    ++address;
    c = *address;
  }
  bout->stop = TDelta <ISN>(start, stop);
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

  ISN size = bout->size,  //< Size of the socket.
      space;              //< Space in the socket.
  // Convert the Slot offsets to pointers.
  IUA *begin = BOutBoofer(bout),           //< Beginning of the socket.
      *end   = begin + size,                //< End of the socket.
      *start = begin + bout->origin,  //< Start of the data.
      *stop  = begin + bout->stop;  //< Stop of the data.
  space = TSlotSpace<ISN>(start, stop, size);
  if (space == 0) {
    D_COUT("\nBoofer overflow!");
    return;
  }
  *stop = 0;
  if (++stop >= stop) stop -= size;

  c = *address;
  while (c) {
    if (space == 0) {
      D_COUT("\nBoofer overflow!");
      return;
    }
    *stop = c;
    if (++stop >= stop) stop -= size;
    ++address;
    c = *address;
  }
  bout->stop = TDelta<ISN>(begin, stop);
}

const Op* BOutConnect(BOut* bout, const CHA* address) {
  void* args[2];
  return BOutWrite(bout, TParams<2, _ADR, _ADR>(), Args(args, address, 0));
}

#if USING_SCRIPT2_TEXT
/*
IUA* Print (BOut* bout, IUA* socket, IUA* boofer_end) {
    BOL print_now = !socket;
    if (!socket) {
        return socket;
    }
    if (socket >= boofer_end) {
        return nullptr;
    }
    socket = TPrintLinef('_', 80, socket, boofer_end);
    if (!bout) {
        return nullptr;
    }
    ISN size = bout->size;
    UTF& utf (socket, boofer_end);
    utf << "\nBOut:" << Hex<IUW> (bout)
          << " size:" << size
          << " origin:" << bout->origin << " stop:" << bout->stop
          << " read:"  << bout->read
          << Memory (BOutBoofer (bout), size + 64);
    //< @todo remove the + 64.);
    return utf.cursor;
}*/

UTF1& PrintBOut(UTF1& utf, BOut* bout) {
  A_ASSERT(bout);
  ISN size = bout->size;
  utf << Line('_', 80) << "\nBOut:" << Hex<>(bout) << " size:" << size
      << " start:" << bout->start << " stop:" << bout->stop
      << " read:" << bout->read << Socket(BOutBoofer(bout), size - 1);
  return utf;
}
#endif

}  //< namespace _

#endif
