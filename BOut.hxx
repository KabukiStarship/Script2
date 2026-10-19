// Copyright AStarship <https://astarship.net>.
#include "BOut.hpp"
#if SEAM >= CRABS_OP
#include "BSeq.hpp"
#include "Hash.hpp"
#include "Varint.hpp"
#include "Slot.hpp"
#include "Args.h"

namespace _ {

inline const CHA* BOutBegin(const BOut* bout) {
  return TPtr<CHA>(bout) + sizeof(BOut);
}

inline CHA* BOutBegin(BOut* bout) {
  return CPtr<CHA>(BOutBegin(CPtr<BOut>(bout)));
}

inline const Op* BOutError(BOut* bout, ERC error) {
  //D_COUT("\nBOut " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

inline const Op* BOutError(BOut* bout, ERC error, const DTB* header) {
  //D_COUT("\nBOut " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

inline const Op* BOutError(BOut* bout, ERC error, const DTB* header,
                           ISN offset) {
  //D_COUT("\nBOut " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

inline const Op* BOutError(BOut* bout, ERC error, const DTB* header,
                           ISN bsq_error, IUA* error_byte) {
  //D_COUT("\nBOut " << TAErrors<>(error) << " Error!");
  return TPtr<const Op>(1);
}

const CHA** BOutStateStrings() {
  static const CHA* Strings[] = {"WritingState", "BInStateLocked"};
  return Strings;
}

IUA* BOutBuffer(BOut* bout) {
  return TPtr<IUA>(bout) + sizeof(BOut);
}

BOut* BOutInit(BOut* bout, ISN buffer_bytes) {
  D_ASSERT_PTR(bout);
  D_ASSERT(buffer_bytes >= SlotBytesMin);
  //if (IsError(bout) || buffer_bytes < SlotBytesMin) return NILP;
  bout->bytes = buffer_bytes - sizeof(BOut);
  bout->origin = 0;
  bout->stop = 0;
  bout->read = 0;
  return bout;
}

ISN BOutSpace(BOut* bout) {
  if (IsError(bout)) {
    return 0;
  }
  IUA* txb_ptr = TPtr<IUA>(bout);
  return TSlotSpace<IUN>(txb_ptr + bout->origin, txb_ptr + bout->stop,
                         bout->bytes);
}

ISN BOutBufferLength(BOut* bout) {
  if (IsError(bout)) {
    return 0;
  }
  IUA* origin = BOutBuffer(bout);
  return TSlotLength<IUN>(origin + bout->origin, origin + bout->stop,
                          bout->bytes);
}

IUA* BOutEndAddress(BOut* bout) {
  return TPtr<IUA>(bout) + (4 * sizeof(ISN)) + bout->bytes;
}

ISN BOutStreamByte(BOut* bout) {
  IUA* begin    = BOutBuffer(bout),
     * end      = begin + bout->bytes,
     * open     = (IUA*)begin + bout->read,
     * origin   = begin + bout->origin,
     * dez_nutz = origin;

  ISW length = (ISN)(origin < open) ? open - origin + 1
                                    : (end - origin) + (open - origin) + 2;

  if (length < 1) {
    BOutError(bout, AErrorBufferOverflow, TTSQ<STR_>(), 2, origin);
    return -1;
  }
  //IUA b = *cursor;
  bout->stop = (++origin > end) ? TDelta<ISN>(origin, end)
                                : TDelta<ISN>(dez_nutz, origin);
  return 0;
}

const Op* BOutWrite(BOut* bout, const DTB* params, void** args,
  IUD pc_ctx) {
  //D_COUT("\n\nWriting ");
  //D_COUT_BSQ(params);
  enum {
    BOutBufferSize = 1024,
    BOutBufferSizeWords = BOutBufferSize >> ACPUBytesLog2
  };
  //D_COUT(" to B-Output:");
  //D_COUT_BOUT(bout);
  A_ASSERT(!IsError(bout));
  A_ASSERT(!IsError(params));
  A_ASSERT(!IsError(args));
  // Temp variables packed into groups of 8 bytes for memory alignment.
  IUA  // type,
      iua;
#ifdef USING_CRABS_2_BYTE_TYPES
  IUB iub;
#endif
#ifdef USING_CRABS_4_BYTE_TYPES
  IUC iuc;
#endif
#ifdef USING_CRABS_8_BYTE_TYPES
  IUD iud;
#endif
  ISN num_params = params[0];
  if (num_params == 0) {
    return 0;  //< Nothing to do.
  }
  DTB type;        //< Current type.
  ISN space,       //< Space in the socket.
      index,       //< Index in the params.
      length,      //< Length of a type to write.
      value;       //< Temp variable.
  ISN arg_index = 0,
      bytes = bout->bytes;
  const DTB* param = params;
         //* bsc_param;
  // Convert the socket offsets to pointers.
  IUA* begin = BOutBuffer(bout),
     * end   = begin + bytes,
     * start = begin + bout->origin,
     * stop  = begin + bout->stop;
  const IUA* iua_ptr;
  const IUB* iub_ptr;
#ifdef USING_CRABS_4_BYTE_TYPES
  const IUC* iuc_ptr;  //< Pointer to a 4-IUA type.
#endif
#ifdef USING_CRABS_8_BYTE_TYPES
  const IUD* iud_ptr;  //< Pointer to an 8-IUA type.
#endif
  IUB hash = PRIME_LARGEST_IUB;

  // Free space = space between the read head (start) and the write head
  // (stop), NOT to the ring end. (Passing `end` here always yields 0 for an
  // empty ring, since stop==end in that case.)
  space = TSlotSpace<ISN>(start, stop, bytes);

  // Check if the socket has enough room.
  if (space == 0) {
    return BOutError(bout, AErrorBufferOverflow);
  }
  --space;
  length = params[0];  //< Load the max IUA length.
  ++param;

  // Write data.
  for (index = 1; index <= num_params; ++index, ++arg_index) {
    type = params[index];
    //D_COUT("\nparam: " << (arg_index + 1) << " type:" << ATypef(type)
    //                   << " start:" << TDelta<>(begin, start) << " stop:"
    //                   << TDelta<>(begin, stop) << " space:" << space);
    if (type <= _CHA) {
     #ifdef USING_CRABS_1_BYTE_TYPES
      if (space-- <= 0)
        return BOutError(bout, AErrorBufferOverflow, params, index, nullptr);

      // Load pointer and read data to write.
      iua_ptr = TPtr<const IUA>(args[arg_index]);
      iua = *iua_ptr;

      // Write data.
      *stop = iua;
      hash = HashIUB(iua, hash);
      ++stop; if (stop >= end) stop = begin;
      continue;
     #else
      return BOutError(bout, AErrorInvalidType);
     #endif
    } else if (type <= _CHB) {
     #ifdef USING_CRABS_2_BYTE_TYPES
      if (space < sizeof(IUB))
        return BOutError(bout, AErrorBufferOverflow, params, index, nullptr);
      space -= sizeof(IUB);

      // Load pointer and value to write.
      iub_ptr = TPtr<IUB>(args[arg_index]);
      iub = *iub_ptr;

      // Write data.

      // Byte 1
      iua = IUA(iub);
      *stop = iua;
      ++stop; if (stop >= end) stop = begin;
      hash = HashIUB(iua, hash);

      // Byte 2
      iua = IUA(iub >> 8);
      *stop = iua;
      ++stop; if (stop >= end) stop = begin;
      hash = HashIUB(iua, hash);
      continue;
     #else
      return BOutError(bout, AErrorInvalidType);
     #endif  // USING_CRABS_4_BYTE_TYPES
    } else if (type <= _CHC) {
     #ifdef USING_CRABS_4_BYTE_TYPES
      if (space < sizeof(IUC))
        return BOutError(bout, AErrorBufferOverflow, params, index, nullptr);
      space -= sizeof(IUC);
      iuc_ptr = TPtr<IUC>(args[arg_index]);
      iuc = *iuc_ptr;
      for (value = sizeof(IUC); value > 0; --value) {
        iua = IUA(iuc);
        iuc >>= 8;
        *stop = iua;
        hash = HashIUB(iua, hash);
        ++stop; if (stop >= end) stop = begin;
      }
      continue;
     #else
      return BOutError(bout, AErrorInvalidType);
     #endif            //< USING_CRABS_4_BYTE_TYPES
    } else if (type <= _SSD) {
     #ifdef USING_CRABS_8_BYTE_TYPES
      if (space < sizeof(IUD))
        return BOutError(bout, AErrorBufferOverflow, params, index, nullptr);
      space -= sizeof(IUD);
      iud_ptr = TPtr<IUD>(args[arg_index]);
      iud = *iud_ptr;
      for (value = sizeof(IUD); value > 0; --value) {
        iua = IUA(iud);
        iud >>= 8;
        *stop = iua;
        hash = HashIUB(iua, hash);
        ++stop; if (stop >= end) stop = begin;
      }
      continue;
#else
      return BOutError(bout, AErrorInvalidType);
#endif            //< USING_CRABS_8_BYTE_TYPES
    } else if (type == STR_) {
      // The next descriptor is the capacity, including the nil code unit.
      if (index == num_params || params[index + 1] <= 0)
        return BOutError(bout, AErrorInvalidType);
      ISN capacity = params[++index];
      iua_ptr = TPtr<const IUA>(args[arg_index]);
      ISN count = 0;
      while (count < capacity && iua_ptr[count]) ++count;
      if (count == capacity || space < count + 1 + ISN(sizeof(IUB)))
        return BOutError(bout, AErrorBufferOverflow);
      ++count;  //< Include the nil code unit in the payload and hash.
      space -= count;
      for (ISN i = 0; i < count; ++i) {
        iua = iua_ptr[i];
        *stop = iua;
        hash = HashIUB(iua, hash);
        ++stop; if (stop >= end) stop = begin;
      }
    } else {
      return BOutError(bout, AErrorInvalidType);
    }
//#if CPU_SIZE <= 16
//      case _VSB:  //< _W_r_i_t_e__2_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
//        // Load number_ to write and increment args.
//        iub_ptr = TPtr<const IUB>(args[arg_index]);
//        iub = *iub_ptr;
//        // We are using the same code to utf both signed and unsigned
//        // varints. In order to convert from a negative 2's complement
//        // signed integer to a transmittable format, we need to invert
//        // the bits and add 1. Then we just shift the bits left one and
//        // put the sign bit in the LSB.
//        iub = TVarintPack<IUB>(iub);
//        goto WriteVarint2;
//      case _VUB:  //< _W_r_i_t_e__2_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
//        // Load next pointer value to write.
//        iub_ptr = TPtr<const IUB>(args[arg_index]);
//        if (iub_ptr == NILP)
//          return BOutError(bout, AErrorImplementation, params, index, start);
//        iub = *iub_ptr;
//
//      WriteVarint2 : {
//        // Byte 1
//        if (space-- == 0)
//          return BOutError(bout, AErrorBufferOverflow, params, index, start);
//        iua = iub & 0x7f;
//        iub = iub >> 7;
//        if (iub == 0) {
//          iua |= 0x80;
//          *end = iua;
//          if (++end >= end) end -= bytes;
//          hash = HashIUB(iua, hash);
//          break;
//        }
//        *end = iua;
//        if (++end >= end) end -= bytes;
//        hash = HashIUB(iua, hash);
//
//        // Byte 2
//        if (--space == 0)
//          return BOutError(bout, AErrorBufferOverflow, params, index, start);
//        iua = iub & 0x7f;
//        iub = iub >> 7;
//        if (iub == 0) {
//          iua |= 0x80;
//          *end = iua;
//          if (++end >= end) end -= bytes;
//          hash = HashIUB(iua, hash);
//          break;
//        }
//        *end = iua;
//        if (++end >= end) end -= bytes;
//        hash = HashIUB(iua, hash);
//
//        // Byte 3
//        if (--space == 0)
//          return BOutError(bout, AErrorBufferOverflow, params, index, start);
//        iua = iub & 0x7f;
//        iua |= 0x80;
//        *end = iua;
//        if (++end >= end) end -= bytes;
//        hash = HashIUB(iua, hash);
//      } break;
//#else
//      case _ISV:  //< _W_r_i_t_e__4_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
//        // Load number_ to write and increment args.
//        iuc_ptr = TPtr<const IUC>(args[arg_index]);
//        iuc = *iuc_ptr;
//        iuc = TypePackVarint<IUC>(iuc);
//        goto WriteVarint4;
//      case _IUV:  //< _W_r_i_t_e__4_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
//        // Load the 4-IUA type to write to the socket.
//        iuc_ptr = TPtr<const IUC>(args[arg_index]);
//        iuc = *iuc_ptr;
//      WriteVarint4 : {  //< Optimized manual do while loop.
//        iub = 5;
//        if (space == 0)  //< @todo Benchmark to space--
//          return BOutError(bout, AErrorBufferOverflow, params, index, origin);
//        --space;  //< @todo Benchmark to space--
//        iua = iuc & 0x7f;
//        iuc = iuc >> 7;
//        if (iuc == 0) {
//          iua |= 0x80;
//          *stop = iua;
//          if (++stop >= stop) stop -= size;
//          hash = HashIUB(iua, hash);
//          break;
//        }
//        *stop = iua;
//        if (++stop >= stop) stop -= size;
//        hash = HashIUB(iua, hash);
//        // This wont happen I don't think.
//        // if (--iub == 0)
//        //    return BOutError (AErrorVarintOverflow, params, index,
//        //                       origin);
//
//        goto WriteVarint4;
//      } break;
//#endif
//#if USING_CRABS_8_BYTE_TYPES
//        // Align the socket to a word boundary and check if the socket
//        // has enough room.
//        if (space < sizeof(IUD))
//          return BOutError(bout, AErrorBufferOverflow, params, index, origin);
//        space -= sizeof(IUD);
//
//        // Load pointer and value to write.
//        iud_ptr = TPtr<IUD>(args[arg_index]);
//        iud = *iud_ptr;
//
//        // Write data.
//
//        for (value = sizeof(ISD); value > 0; --value) {
//          // Byte 1
//          iua = (IUA)iud;
//          hash = HashIUB(iua, hash);
//          *stop = iua;
//          if (++stop >= stop) stop -= size;
//        }
//        break;
//      case VSD:  //< _W_r_i_t_e__8_-_b_y_t_e__S_i_g_n_e_d__V_a_r_i_n_t____
//        // Load number_ to write and increment args.
//        iud_ptr = TPtr<const IUD>(args[arg_index]);
//        iud = *iud_ptr;
//        iud = TypePackVarint<IUD>(iud);
//        goto WriteVarint8;
//      case VUD:  //< _W_r_i_t_e__8_-_b_y_t_e__U_n_s_i_g_n_e_d__V_a_r_i_n_t_
//        // Load the 4-IUA type to write to the socket.
//        iud_ptr = TPtr<const IUD>(args[arg_index]);
//        iud = *iud_ptr;
//      WriteVarint8 : {     //< Optimized manual do while loop.
//        iub = 8;           //< The max number_ of varint bytes - 1.
//        if (space <= 9) {  //< @todo Benchmark to space--
//          return BOutError(bout, AErrorBufferOverflow, params, index, origin);
//        }
//        --space;           //< @todo Benchmark to space--
//        if (--iub == 0) {  //< It's the last IUA not term bit.
//          iua = iud & 0xFF;
//          *stop = iua;
//          if (++stop >= stop) stop -= size;
//          hash = HashIUB(iua, hash);
//          break;
//        }
//        iua = iud & 0x7f;  //< Take 7 bits at a time.
//        iud = iud >> 7;    //<
//        if (iud == 0) {
//          iua |= 0x80;
//          *stop = iua;
//          if (++stop >= stop) stop -= size;
//          hash = HashIUB(iua, hash);
//          break;
//        }
//        *stop = iua;
//        if (++stop >= stop) stop -= size;
//        hash = HashIUB(iua, hash);
//
//        goto WriteVarint8;
//      } break;
//#else
//      case _IUE:
//      case _ISE:
//      case _TME:
//
//      case _VSD:
//      case _VUD:
//        return BOutError(bout, AErrorInvalidType);
//#endif
//      default: {
//        value = type >> 5;
//        auto block_type = value & 0x3;
//        if (block_type == _ARY) {
//          //D_COUT("\nPrinting string.");
//          if (space == 0)
//            return BOutError(bout, AErrorBufferOverflow, params, index,
//                              begin);
//          if (type != _ADR) {
//            // We might not need to write anything if it's an _ADR with
//            // nil .
//            length = params[++index];  //< Load the max IUA length.
//            ++num_params;
//          } else {
//            length = CRAddressLengthMax;
//          }
//          // Load the source data pointer and increment args.fs
//          iua_ptr = TPtr<const IUA>(args[arg_index]);
//          //D_COUT('\"' << Hexf(iua_ptr));
//
//          // We know we will always have at least one nil-term IUA.
//          iua = *iua_ptr;
//          while (iua != 0) {
//            if (space-- == 0)
//              return BOutError(bout, AErrorBufferOverflow, params, index,
//                                begin);
//            hash = HashIUB(iua, hash);
//
//            *end = iua;  // Write IUA
//            if (++end >= end) end -= bytes;
//            ++iua_ptr;
//            iua = *iua_ptr;  // Read IUA.
//          }
//          if (type != _ADR) {  //< 1 is faster to compare than 2
//                                // More likely to have _ADR than STR_
//            *end = 0;         // Write nil-term IUA.
//            if (++end >= end) end -= bytes;
//            break;
//          }
//
//          break;
//        }
//        if ((type >> 5) && type > _OBJ) {
//          return BOutError(bout, AErrorImplementation, params, index);
//        }
//        if ((type >> 7) && ((type & 0x1f) >= _OBJ)) {
//          // Cannot have multi-dimensional arrays of objects!
//          type &= 0x1f;
//          return BOutError(bout, AErrorImplementation, params, index, begin);
//        }
//        type = type & 0x1f;  //< Mask off lower 5 bits.
//        switch (value) {
//          case 0: {
//            iua_ptr = TPtr<const IUA>(args[arg_index]);
//            if (iua_ptr == NILP)
//              return BOutError(bout, AErrorImplementation, params, index,
//                               begin);
//          }
//#if USING_CRABS_2_BYTE_TYPES
//          case 1: {
//            iub_ptr = TPtr<const IUB>(args[arg_index]);
//            if (iub_ptr == NILP)
//              return BOutError(bout, AErrorImplementation, params, index,
//                               origin);
//            iub = *iub_ptr;
//            length = static_cast<ISN>(iub);
//            iua_ptr = TPtr<const IUA>(iub_ptr);
//          }
//#endif
//#if USING_CRABS_4_BYTE_TYPES
//          case 2: {
//            iuc_ptr = TPtr<const IUC>(args[arg_index]);
//            if (iuc_ptr == NILP)
//              return BOutError(bout, AErrorImplementation, params, index,
//                               origin);
//            iuc = *iuc_ptr;
//            length = static_cast<ISN>(iuc);
//            iua_ptr = TPtr<const IUA>(iuc_ptr);
//          }
//#endif
//#if USING_CRABS_8_BYTE_TYPES
//          case 3: {
//            iud_ptr = TPtr<const IUD>(args[arg_index]);
//            if (iud_ptr == NILP)
//              return BOutError(bout, AErrorImplementation, params, index,
//                               origin);
//            iud = *iud_ptr;
//            length = static_cast<ISN>(iud);
//            iua_ptr = TPtr<const IUA>(iud_ptr);
//          }
//#endif  //< USING_CRABS_8_BYTE_TYPES
//          default: {
//            // This wont happen due to the & 0x3 bit mask
//            // but it stops the compiler from barking.
//            return BOutError(bout, AErrorImplementation, params, index, begin);
//          }
//        }
//        if (space < length) {
//          return BOutError(bout, AErrorBufferOverflow, params, index, begin);
//        }
//        if (length == 0) {
//          break;  //< Not sure if this is an error.
//        }
//        if (begin + length >= end) {
//          for (; bytes - length > 0; --length) {
//            iua = *(iua_ptr++);
//            hash = HashIUB(iua, hash);
//            *end = iua;
//            ++end;
//          }
//          end = begin - 1;
//          for (; length > 0; --length) {
//            iua = *(iua_ptr++);
//            hash = HashIUB(iua, hash);
//            *end = iua;
//            ++end;
//          }
//          break;
//        }
//        for (; length > 0; --length) {
//          iua = *(iua_ptr++);
//          hash = HashIUB(iua, hash);
//          *end = iua;
//          ++end;
//        }
//        break;
//      }
//    }
//    ++arg_index;
  }
  if (space < 3)
    return BOutError(bout, AErrorBufferOverflow, params, index, begin);
  // space -= 2;   //< We don't need to save this variable.
  *stop = IUA(hash);
  ++stop; if (stop >= end) stop = begin;
  *stop = IUA(hash >> 8);
  ++stop; if (stop >= end) stop = begin;
  bout->stop = TDelta<ISN>(begin, stop);
  //D_COUT("\nDone writing to B-Output with the hash 0x" << Hexf(hash));
  return 0;
}

void BOutRingBell(BOut* bout, const CHA* address) {
  if (IsError(bout)) {
    return;
  }
  if (address == NILP) {
    address = "";
  }
  //D_COUT("\nRinging BEL to address:0x" << Hexf(address));

  // Temp variables packed into groups of 8 bytes for memory alignment.
  IUA c;
  ISN size = bout->bytes, //< Size of the socket.
      space;              //< Space in the socket.
  // Convert the Slot offsets to pointers.
  IUA* begin = BOutBuffer(bout),     //< Beginning of the socket.
     * end   = begin + size,         //< End of the socket.
     * start = begin + bout->origin, //< Start of the data.
     * stop  = begin + bout->stop;   //< Stop of the data.
  space = TSlotSpace<ISN>(start, stop, size);
  if (space == 0) {
    //D_COUT("\nBuffer overflow!");
    return;
  }
  *stop = 0;
  ++stop; if (stop >= end) stop = begin;

  c = *address;
  while (c) {
    if (space == 0) {
      //D_COUT("\nBuffer overflow!");
      return;
    }
    *stop = c;
    ++stop; if (stop >= end) stop = begin;
    ++address;
    c = *address;
  }
  bout->stop = TDelta <ISN>(start, stop);
}

void BOutAckBack(BOut* bout, const CHA* address) {
  if (IsError(bout)) {
    return;
  }
  if (address == NILP) {
    address = "";
  }
  //D_COUT("\n\nRinging BEL to address:0x" << Hexf(address));

  // Temp variables packed into groups of 8 bytes for memory alignment.
  IUA c;

  ISN size = bout->bytes,  //< Size of the socket.
      space;              //< Space in the socket.
  // Convert the Slot offsets to pointers.
  IUA *begin = BOutBuffer(bout),           //< Beginning of the socket.
      *end   = begin + size,                //< End of the socket.
      *start = begin + bout->origin,  //< Start of the data.
      *stop  = begin + bout->stop;  //< Stop of the data.
  space = TSlotSpace<ISN>(start, stop, size);
  if (space == 0) {
    //D_COUT("\nBuffer overflow!");
    return;
  }
  *stop = 0;
  ++stop; if (stop >= end) stop = begin;

  c = *address;
  while (c) {
    if (space == 0) {
      //D_COUT("\nBuffer overflow!");
      return;
    }
    *stop = c;
    ++stop; if (stop >= end) stop = begin;
    ++address;
    c = *address;
  }
  bout->stop = TDelta<ISN>(begin, stop);
}

const Op* BOutConnect(BOut* bout, const CHA* address, IUD pc_ctx) {
  void* args[2];
  return BOutWrite(bout, TTSQ<_ADR, _ADR>(), Args(args, address, 0), pc_ctx);
}

void BOutTerminate(BOut* bout, const CHA* address) {
}

void BOutReset(BOut* bout, const CHA* address) {
}

/* Links a BOut (producer) and a BIn (consumer) into one shared lock-free SPSC
ring. See the declaration in BOut.h for the contract.
Design: the producer and consumer alias the SAME 16-byte header, so the two
SPSC head counters (write head, read head) are shared memory — exactly how a
kernel pipe works (one buffer, two heads, two descriptors onto it). Place
`bout` and `bin` at the same address (e.g. bout = TPtr<BOut>(block),
bin = TPtr<BIn>(block)); then bout->stop and bin->stop are the same field
(producer write head / consumer's view of it) and bout->origin and bin->origin
are the same field (producer's view of the read head / consumer read head).
The data region (struct + sizeof(struct)) is the shared ring. Each head is
written by exactly one side and read by the other, as a single volatile word —
the SPSC lock-free discipline. */
BIn* BInAttach(BIn* bin, BOut* bout, IUA* buffer, ISN buffer_bytes) {
  D_ASSERT_PTR(bin);
  D_ASSERT_PTR(bout);
  D_ASSERT_PTR(buffer);
  D_ASSERT(buffer_bytes >= SlotBytesMin);
  // bin and bout must alias the same header (same address) for the shared
  // SPSC heads to work; the data region is buffer = header + 16.
  D_ASSERT(IUW(bin) == IUW(bout));
  D_ASSERT(IUW(buffer) == IUW(bout) + sizeof(BOut));
  ISN ring_bytes = buffer_bytes;
  bout->bytes = ring_bytes;
  bin->bytes  = ring_bytes;
  // Zero the two shared heads (and the mirrors, which are the same fields):
  // empty ring, both heads at the start.
  bout->stop   = 0;  //< Producer write head  (== bin->stop).
  bin->origin  = 0;  //< Consumer read head   (== bout->origin).
  bout->read   = 0;
  bin->read    = 0;
  return bin;
}

}  //< namespace _
#endif
