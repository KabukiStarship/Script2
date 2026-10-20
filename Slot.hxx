// Copyright AStarship <https://astarship.net>.
#include "Slot.hpp"
#if SEAM >= CRABS_OP
//#include "String.hpp"
//#include "AType.h"
#if SEAM == CRABS_OP
#include "_Debug.h"
#else
#include "_Release.h"
#include "AType.hpp"
#endif
namespace _ {
// @defgroup Slot
// @{

const Op* ReturnError(Slot* slot, ERC error) {
  D_COUT('\n' << TSError<CHR>()[error]);
  return OpError(error);
}

const Op* ReturnError(Slot* slot, ERC error, const DTB* header) {
  D_COUT('\n' << TSError<CHR>()[error]);
  return OpError(error);
}

const Op* ReturnError(Slot* slot, ERC error, const DTB* header, IUA offset) {
  D_COUT('\n' << TSError<CHR>()[error]);
  return OpError(error);
}

const Op* ReturnError(Slot* slot, ERC error, const DTB* header, ISC offset,
                      IUA* address) {
  D_COUT('\n' << TSError<CHR>()[error]);
  return OpError(error);
}

/* Initializes the ring socket with the given socket origin and size.
@param socket Pointer to the beginning of the ring socket.
@param size   The size of the ring socket in bytes. */
Slot* SlotInit(IUW* socket, ISW size) {
  A_ASSERT(socket);
  A_ASSERT(size >= SlotBytesMin);
  Slot* slot = TPtr<Slot>(socket, sizeof(Slot));
  IUA* begin = TPtr<IUA>(socket, sizeof(Slot));
  slot->origin = begin;
  slot->start  = begin;
  slot->stop   = begin;
  slot->end    = begin + size - 1;
  return slot;
}

/* Initializes the slot from the TBIn. */
Slot* SlotInit(TBIn<ISC>* bin) {
  A_ASSERT(bin);
  Slot* slot = TPtr<Slot>(bin);
  IUA* begin = TPtr<IUA>(bin, sizeof(TBIn<ISC>));
  slot->origin = begin;
  slot->start  = begin + bin->origin;
  slot->stop   = begin + bin->stop;
  slot->end    = begin + bin->bytes;
  return slot;
}

/* Initializes the slot from the TBOut. */
Slot* SlotInit(TBOut<ISC>* bout) {
  A_ASSERT(bout);
  Slot* slot = TPtr<Slot>(bout);
  IUA* begin = TPtr<IUA>(bout, sizeof(TBOut<ISC>));
  slot->origin = begin;
  slot->start  = begin + bout->origin;
  slot->stop   = begin + bout->stop;
  slot->end    = begin + bout->bytes;
  return slot;
}

/* Sets the ring socket to the given socket origin and size.
@param slot   The slot to set.
@param socket Pointer to the beginning of the ring socket.
@param size   The size of the ring socket in bytes. */
inline BOL SlotSet(Slot* slot, IUW* socket, IUW size) {
  if (IsError(socket)) return true;
  IUA* begin = TPtr<IUA>(socket, sizeof(Slot));
  slot->origin = begin;
  slot->stop   = begin + size;
  slot->start  = begin;
  slot->end    = begin + size - 1;
  return false;
}

/* Checks if this slot contains the given address.
@return Returns inputted address if this Slot contains the given address
and nil else wise. */
void* SlotContains(Slot* slot, void* address) {
  IUA* origin = slot->origin;
  if (address < origin) {
    return NILP;
  }
  IUA* l_end = slot->stop;
  if (address > l_end) {
    return NILP;
  }
  return address;
}

/* Clears the socket without zeroing it out. */
inline void SlotClear(Slot* slot) {
  slot->origin = slot->stop = slot->origin;
}

/* Zeros out the Slot. */
void SlotWipe(Slot* slot) {
  IUA* l_start = slot->origin, *l_stop = slot->stop, *temp;
  if (l_start > l_stop) {
    temp = l_start;
    slot->origin = l_stop;
    slot->stop   = temp;
  }
  while (slot->origin != slot->stop) *slot->origin++ = 0;
}

/* Writes the given Operation output parameters from the slot to the args.
@param slot   The slot to write to.
@param params The param types.
@param args   The args array of pointers to write to. */
const Op* SlotWrite(Slot* slot, const DTB* params, void** args) {
  //D_CHECK_TPTR_RETURN(Op, params);
  A_ASSERT(args);

  A_ASSERT(false);
  // @todo Write me!
  return NILP;
}

/* Checks if there is space in the socket.
@return True if the socket has space. */
BOL SlotIsWritable(Slot* slot) {
  IUA* l_stop = slot->origin;
  if (l_stop == slot->origin) {
    if (l_stop != slot->stop) {
      return false;
    }
    return true;
  }
  return slot->origin != slot->stop - 1;
}

/* Checks if there is data in the socket.
@return True if the socket has data. */
BOL SlotIsReadable(Slot* slot) { return slot->origin != slot->stop; }

/*IUA* SlotRead (Slot* slot, IUA* write, void* write_end, IUA* const origin,
                    IUA* const origin, IUA* const stop , IUA* const stop,
                    ISW size) {
    if (IsError(slot)) {
        return NILP;
    }
    if (IsError(write)) {
        return NILP;
    }
    if (write > write_end) {
        return NILP;
    }

    if ((origin > stop) && (origin + size >= stop)) {
        // Calculate upper chunk size.
        ISW top_chunk = stop - stop;
        size -= top_chunk;

        ArrayCopy (target, target_end, origin, top_chunk);
        ArrayCopy (TPtr<IUA>(target) + top_chunk, size,
                    origin);
        return origin + size;
    }
    ArrayCopy (target, target_end, stop, size);
    return origin + size;
}*/

const Op* SlotRead(Slot* slot, const DTB* params, void** args) {
  A_ASSERT(params);
  A_ASSERT(args);
  IUA iua;  //< Temp variable to load most types.
  IUB iub;  //< Temp variable for working with _IUB types.
#ifdef USING_CRABS_4_BYTE_TYPES
  IUC iuc;
#endif
#ifdef USING_CRABS_8_BYTE_TYPES
  IUD iud;  //< Temp _IUD variable.
#endif
  IUA* iua_ptr;             //< Pointer to a _IUA.
  IUB* iub_ptr;             //< Pointer to a _IUB.
  IUC* iuc_ptr;             //< Pointer to a _IUC.
  IUD* iud_ptr;             //< Pointer to a _IUD.
  DTB type;                 //< Current type being read.
  ISC index,                //< Index in the escape sequence.
      num_params = *params; //< Number of params.
  ISC offset;               //< Offset to word align the current type.
  ISC length,               //< Length of the data in the socket.
      count,                //< Argument length.
      size;                 //< Size of the ring socket.

  A_ASSERT(num_params);

  D_COUT("\n\nReading TBIn: ");

  IUA *l_begin = slot->origin,       //< Beginning of the socket.
      *l_end = slot->stop,           //< stop of the socket.
      *l_start = slot->origin,       //< origin of the data.
      *l_stop = slot->stop;          //< stop of the data.
  const DTB* param = params + 1;  //< current param.

  size = TDelta<ISC>(l_end, l_begin);

  length = ISC(SlotLength(l_start, l_stop, size));

  D_COUT("\n\nReading " << length << " bytes.");
  // D_COUT_BSQ (params)
  // When we scan, we are reading from the beginning of the TBIn socket.

  for (index = 0; index < num_params; ++index) {
    type = (IUA)*param;
    ++param;
    D_COUT("\nindex:" << index << ":\\"" << ATypef(type) << "\\" start:0x"
                      << TDelta<>(l_begin, slot->start) << " stop:0x"
                      << TDelta<>(l_begin, slot->stop));

    switch (type) {
      case _NIL:
        return ReturnError(slot, AErrorInvalidType);
      case _ADR:  //< _R_e_a_d__S_t_r_i_n_g_-_1_______________
      //case STR_:
        // Load boofered-type argument length and increment the
        // index.
        count = *param;
        ++param;

        // StdOut() << "\nReading IUA with max length " << count;

        // Load next pointer and increment args.
        iua_ptr = TPtr<IUA>(args[index]);
        if (IsError(iua_ptr)) {
          break;
        }

        // Read from slot and write to the slot:
        iua = *l_start;
        if (++l_start > l_end) l_start -= size;
        *iua_ptr = iua;
        ++iua_ptr;

        while (iua && count) {
          if (count-- == 0)
            return ReturnError(slot, AErrorBooferUnderflow, params, index,
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
      case _ISA:  //< _R_e_a_d__1__B_y_t_e__T_y_p_e_s___________
      case _IUA:
#ifdef USING_CRABS_1_BYTE_TYPES
        if (length == 0) {
          return ReturnError(slot, AErrorBooferUnderflow, params, index,
                             l_start);
        }
        --length;

        // Read from socket and write to the stack:
        iua = *l_start;
        if (++l_start > l_end) {
          l_start -= size;
        }
        // Load next pointer and increment args.
        iua_ptr = TPtr<IUA>(args[index]);
        if (IsError(iua_ptr)) {
          break;
        }
        *iua_ptr = iua;  //< Write
        if (++l_start > l_end) {
          l_start -= size;
        }
        break;
#else
        return ReturnError(slot, AErrorInvalidType);
#endif
      case _ISB:  //< _R_e_a_d__1_6_-_b_i_t__T_y_p_e_s__________
      case _IUB:
      case _FPB:
#ifdef USING_CRABS_2_BYTE_TYPES
        // Read2ByteType:{
        // Word-align
        offset = AlignUpB(l_start);
        if (IUW(length) < offset + 2) {
          return ReturnError(slot, AErrorBooferUnderflow, params, index,
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
        if (IsError(iub_ptr)) {
          break;
        }
        *iub_ptr = iub;
        //}
        break;
#else
        return ReturnError(slot, AErrorInvalidType);
#endif
#if USING_CRABS_VARINT2
        goto Read2ByteType;
#else
        return ReturnError(slot, AErrorInvalidType);
#endif
#if CPU_SIZE > 16
      case SVI:
      case UVI:
#endif
      case _ISC:  //< _R_e_a_d__3_2_-_b_i_t__T_y_p_e_s__________
      case _IUC:
      case _FPC:
#ifdef USING_CRABS_4_BYTE_TYPES
        // Read4ByteType:{
        // Word-align
        offset = AlignUpC(l_start);
        if (length < offset + 4) {
          return ReturnError(slot, AErrorBooferUnderflow, params, index,
                             l_start);
        }
        length -= ISC(offset + 4);
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
        if (IsError(iuc_ptr)) {
          break;
        }
        *iuc_ptr = iua;  //< Write
        break;
//}
#else
        return ReturnError(slot, AErrorInvalidType);
#endif
      case _ISD:  //< _R_e_a_d__6_4_-_b_i_t__T_y_p_e_s__________
      case _IUD:
      case _FPD:
      case _SSD:
#ifdef USING_CRABS_8_BYTE_TYPES
        // Read8ByteType:{
        // Word-align
        offset = ISC(AlignUpD(l_start));
        if (IUW(length) < offset + sizeof(ISD)) {
          return ReturnError(slot, AErrorBooferUnderflow, params, index,
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
        return ReturnError(slot, AErrorInvalidType);
#endif
      default: {
#if USING_CRABS_OBJ
        count = type >> 5;  //< count is now the array type bits.
        type &= 0x1f;       //< Now type is the type 0-31
        if (count && (type >= _OBJ)) {
          // Can't make arrays out of objects!
          return ReturnError(slot, AErrorInvalidType, params, index, l_start);
        }
        // We don't care if it's a multidimensional array anymore.
        iua_ptr = TPtr<IUA>(args[index]);
        if (iua_ptr == NILP)
          return ReturnError(slot, AErrorImplementation, params, index,
                             l_start);
        count &= 0x3;
        switch (count) {
          case 0: {  // It's a 8-bit count.
            if (type >= _LST) {
              // _LST, kBOK, kDIC, and _MAP can't be 8-bit!
              return ReturnError(slot, AErrorInvalidType, params, index,
                                 l_start);
            }
            count = (IUW)*iua_ptr;
            break;
          }
          case 1: {  // It's a 16-bit count.
            if (length < 3) {
              return ReturnError(slot, AErrorBooferUnderflow, params, index,
                                 l_start);
            }
            count -= 2;
            iub_ptr = TPtr<IUB>(iua_ptr);
            count = (IUW)*iub_ptr;
            if (count > length) {
              return ReturnError(slot, AErrorBooferOverflow, params, index,
                                 l_start);
            }
            break;
          }
          case 2: {  // It's a 32-bit count.
            if (length < 5) {
              return ReturnError(slot, AErrorBooferUnderflow, params, index,
                                 l_start);
            }
            count -= 4;
            iuc_ptr = TPtr<IUC>(iua_ptr);
            count = (IUW)*iuc_ptr;
            if (count > length) {
              return ReturnError(slot, AErrorBooferOverflow, params, index,
                                 l_start);
            }
            break;
          }
          case 3: {  // It's a 64-bit count.
            if (length < 9) {
              return ReturnError(slot, AErrorBooferUnderflow, params, index,
                                 l_start);
            }
            count -= 8;
            iud_ptr = TPtr<IUD>(iua_ptr);
            count = (IUW)*iud_ptr;
            if (count > length) {
              return ReturnError(slot, AErrorBooferOverflow, params, index,
                                 l_start);
            }
            break;
          }
          default: {
            return ReturnError(slot, AErrorImplementation, params, index,
                               l_start);
          }
        }
        if (length < count) {
          return ReturnError(slot, AErrorBooferOverflow, params, index,
                             l_start);
        }
        if (!count) {
          return ReturnError(slot, AErrorBooferOverflow, params, index,
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
  slot->origin = l_start;

  return 0;
}

const Op* SlotRead(Slot* slot, const Op& op, void** args) {
  return SlotRead(slot, op.in, args);
}

const Op* SlotWrite(Slot* slot, const Op& op, void** args) {
  return SlotWrite(slot, op.out, args);
}

const Op* SlotWrite(Slot* slot, Slot& other) { return NILP; }

const Op* SlotWrite(Slot* slot, const IUA* message) { return NILP; }

#if USING_CRABS_TEXT
UTF1& SlotPrint(UTF1& utf, Slot* slot) {
  IUA* l_begin = slot->origin, *l_end = slot->stop;
  return utf << Line('_', 80) << "\nSlot: origin:" << Hex<>(l_begin)
             << " start:" << Hex<>(slot->origin) << "\nstop:" << Hex<>(slot->stop)
             << " end:" << Hex<>(l_end) << Socket(l_begin, l_end);
}
#endif
//< @} Slot
}
#endif
