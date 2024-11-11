// Copyright Kabuki Starship� <kabukistarship.com>.
#pragma once
#ifndef SCRIPT_LIST_CODE
#define SCRIPT_LIST_CODE
#include <_Config.h>
#if SEAM >= SCRIPT2_LIST
#include "Binary.hpp"
#include "Set.hpp"
#include "Stack.hpp"
#include "Types.hpp"
#if SEAM == SCRIPT2_LIST
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
#define LST_A typename ISZ = ISR, typename ISY = ISR, typename DT = DTB
#define LST_P ISZ, ISY, DT
namespace _ {

/* A collection of type-value tuples.
@see ASCII Data Type Specification.
@link /Spec/Data/MapTypes/Map.md
@code
      List Memory Layout
+============================+
|_______   Boofer            |<--- top
|_______ ^ Value N           |
|        | Value 0           |
|----------------------------|
|_______   Boofer            |
|_______ ^ Type of Value N   |
|        | Type of Value 0   |
|----------------------------|
|_______   Boofer            |
|_______ ^ Offset to Value N |
|        | Offset to Value 0 | 
+============================+  ^  Up in addresses.
|        TList Struct        |  |
+============================+ 0xN Base address
@endcode

2024-09-02: Right now we're having a problem writing teh complex types because 
we have to be able to autogrow and insert other than push, which has some 
circular inclusion challenges.
*/
template<LST_A>
struct TList {
  ISZ bytes,   //< Size of the List in bytes.
      top;          //< Offset to the top of the data.
  TStack<ISZ> map;  //< Stack of offset mappings to the list items.
};

#define LST TList<LST_P>

/* Calculates the minimum size of a List with all nil objects. */
template<LST_A>
inline ISZ TListSizeMin(ISY total) {
  return sizeof(LST) + total * (sizeof(ISZ) + sizeof(DT));
}

/* The maximum theoretical amount of freespace in a List. */
template<LST_A>
inline ISZ TListSizeFreeMax(ISZ bytes, ISY total) {
  return bytes - sizeof(LST) - 
         total * (sizeof(DT) + sizeof(ISZ));
}

/* Gets the base pointer to the Offsets. */
template<LST_A>
inline ISZ* TListValuesMap(LST* list) {
  return TPtr<ISZ>(list, sizeof(LST));
}
template<LST_A>
inline const ISZ* TListValuesMap(const LST* list) {
  const LST* lst = CPtr<LST>(list);
  return CPtr<ISZ>(TListValuesMap<LST_P>(CPtr<LST>(list)));
}

template<LST_A>
inline DT* TListTypes(LST* list, ISZ total) {
  return TPtr<DT>(TListValuesMap<LST_P>(list) + total);
}
template<LST_A>
inline const DT* TListTypes(const LST* list, ISZ total) {
  return CPtr<DT>(TListTypes<LST_P>(CPtr<LST>(list), total));
}

template<LST_A>
inline DT TListType_NC(const LST* list, ISZ total, ISY index) {
  return TListTypes<LST_P>(list, total)[index];
}

/* Returns the type bytes array. */
template<LST_A>
inline const DT* TListTypes(const LST* list) {
  return TPtr<DT>(TListValuesMap<LST_P>(list) + list->map.total);
}

/* Returns the type bytes array. */
template<LST_A>
inline DT* TListTypes(LST* list) {
  auto lst = CPtr<LST>(list);
  return CPtr<DT>(TListValuesMap<LST_P>(lst) + list->map.total);
}

/* Returns the type at the given index. */
template<LST_A>
inline DT TListType(const LST* list, ISY index) {
  if (index < 0 || index >= list->map->total) return NIL;
  return TListTypes<LST_P>(list)[index];
}

/* Gets the first element of the List. */
template<LST_A, typename T>
inline T* TListBase(const LST* list) {
  return TPtr<T>(list, sizeof(LST) +
                 list->map.total * (sizeof(ISZ) + sizeof(DT)));
}
template<LST_A, typename T>
inline const T* TListBase(const LST* list) {
  return TPtr<T>(list, sizeof(LST) +
                  list->map.total * (sizeof(ISZ) + sizeof(DT)));
}

/* Returns the type at the given index. */

/* Returns the value at the given index.
@return Returns nil if the index is out of the count range. */
template<LST_A, typename T = void>
inline const T* TListValue(const LST* list, ISY index) {
  if (index < 0 || index >= list->map.count) return nullptr;
  return TPtr<T>(list, TListValuesMap<LST_P>(list)[index]);
}

/* Returns the value at the given index.
@return Returns nil if the index is out of the count range. */
template<LST_A, typename T = void>
inline T* TListValue(LST* list, ISY index) {
  return CPtr<T>(TListValue<LST_P>(CPtr<LST>(list), index));
}

/* Returns the value at the given index witout error checking. */
template<LST_A, typename T = void>
T* TListValue_NC(LST* list, ISY index) {
  return TPtr<T>(list, TStackGet_NC<ISZ, ISZ>(&list->map, index));
}

/* Returns the value at the given index.
@return Returns nil if the index is out of the count range. */
template<LST_A, typename T = void>
inline const T* TListValue_NC(const LST* list, ISY index) {
  return CPtr<T>(TListValue_NC<LST_P>(CPtr<LST>(list), index));
}

/* Returns the value at the given index witout error checking. */
template<LST_A>
const ISZ TListValueOffset_NC(const LST* list, ISY index) {
  return TStackStart<SCK_P>(&list->map)[index];
}

/* Returns the type and value offset at the given index. */
template<LST_A>
inline TATypeValue<ISZ> TListTypeValueOffset(LST* list, ISY index) {
  if (index < 0 || index >= list->map->total) return NIL;
  auto values = TListValuesMap<LST_P>(list);
  auto types = TPtr<DT>(values + list->map->total);
  return {types[index], values[index]};
}

/* Gets the base pointer to the values. */
template<LST_A>
inline CHA* TListValues(LST* list, ISZ size) {
  return TPtr<CHA>(TListTypes<LST_P>(list, size) + list->map.total);
}
template<LST_A>
inline CHA* TListValues(LST* list) {
  return TListValues<LST_P>(list, list->map->size);
}

template<LST_A>
inline void* TListTop(LST* list) {
  return TPtr<void*>(list, list->top);
}

/* Returns the TTypeValue at the given index.
@return Returns nil if the index is out of the count range. */
template<LST_A>
inline const TATypeValuePtr<DT> TListTypeValue(LST* list, ISY index) {
  if (index < 0 || index >= list->map.count) return { 0, 0 };
  auto value_offsets = TListValuesMap<LST_P>(list);
  auto types = TPtr<DT>(value_offsets + list->map.total);
  return { types[index], TPtr<void>(list, value_offsets[index])};
}

/* Returns the TTypeValue at the given index.
@return Returns nil if the index is out of the count range. */
template<LST_A>
inline const TATypeValue<ISZ, DT> 
    TListTypeValueOffset(const LST* list, ISY index) {
  if (index < 0 || index >= list->map.count) return { 0, 0 };
  auto value_offsets = TListValuesMap<LST_P>(list);
  auto types = TPtr<DT>(value_offsets + list->map.total);
  return { types[index], value_offsets };
}

// I don't have to have these.
// Prints the list to the output stream.
template<typename Printer, LST_A>
Printer& TListPrintTypeValue(Printer& o, const LST* list, ISY index) {
  return TPrintValue<Printer, DT>(o, TListType<LST_P>(list, index),
                                  TListValue<LST_P>(list, index));
}

// Prints the list to the output stream.
template<typename Printer, LST_A>
Printer& TListPrintValue(Printer& o, const LST* list, ISY index) {
  return TPrintValue<Printer, DT, ISZ>(o, TListTypeValue<LST_P>(list, index));
}

/* Prints the list to the output stream. */
template<typename Printer, LST_A>
Printer& TListPrint(Printer& o, const LST* list) {
  ISY count     = ISY(list->map.count), 
      total = ISY(list->map.total);
  o << Linef("\n\n+---\n| List<IS") << CSizeCodef<ISZ>()
    << "> bytes:" << list->bytes << " total:" << total
    << " count:" << count << Linef("\n+---");

  const ISZ* value_offsets = TListValuesMap<LST_P>(list);
  const DT*  dt_offsets    = TPtr<DT>(value_offsets + total);
  for (ISY index = 0; index < count; ++index) {
    DT type = *dt_offsets++;
    o << "\n| " << Centerf(index, ISW(STRLength(count)) + 2);
    o << ATypef(type) << ' ';
    TPrintValue<Printer, DT>(o, type, TPtr<CHA*>(list, *value_offsets++));
  }
  return o << Linef("\n+---");
}

/* Returns the minimum count to align the data struct to a 64-bit boundary. */
template<LST_A>
constexpr ISZ TListTotalBoundsLower() {
  return 8 / sizeof(ISZ);
}

/* Initializes a AsciiList from preallocated memory.
total must be in multiples of 4. Given there is a fixed size, both the
total and size will be downsized to a multiple of 4 automatically. */
template<LST_A>
LST* TListInit(LST* list, ISZ bytes, ISY total) {
  D_ARRAY_WIPE(list, bytes);
  list->bytes = bytes;
  list->map.count = 0;
  list->map.total = total;
  list->top = sizeof(LST) + total * (sizeof(ISZ) + sizeof(DT));
  return list;
}

/* Returns the min size of an ASCII List with the given total.
The min size is defined as enough memory to store the given total with
the largest_expected_type.
*/
template<LST_A, ISW largest_expected_type = sizeof(ISW)>
constexpr ISY TListSizeMin(ISY total) {
  return sizeof(LST) +
         ISZ(total * (largest_expected_type + sizeof(ISZ) + 1));
}

/* Returns the end byte of the data. */
template<LST_A>
inline CHA* TListEnd(LST* list, ISZ size) {
  return TPtr<CHA>(list) + list->bytes;
  //return TPtr<CHA>(list) + sizeof(LST) + list->bytes;
  //@Todo Why does this not add the size of the struct like the Array?
}
template<LST_A>
inline CHA* TListEnd(LST* list) {
  return TListEnd<LST_P>(list, list->map.total);
}

/* Gets the first addrss in the Values section where you may be able to write
too. */
template<LST_A>
inline const CHA* TListValuesTop(const LST* list) {
  return TPtr<CHA>(list, list->top);
}
template<LST_A>
inline CHA* TListValuesTop(LST* list) {
  return CPtr<CHA>(TListValuesTop<LST_P>(CPtr<LST>(list)));
}

template<LST_A>
inline const CHA* TListValuesEnd(const LST* list) {
  return TPtr<CHA>(list, list->bytes);
}
template<LST_A>
inline CHA* TListValuesEnd(LST* list) {
  return CPtr<CHA>(TListValuesEnd<LST_P>(CPtr<LST>(list)));
}

/* Calculates the amount of space left in the list. */
template<LST_A>
inline ISZ TListFreeSpace(const LST* list) {
  return list->bytes - list->top;
}
    /* Returns the max count an array can handle. */
template<LST_A>
ISZ TListSize() {
  enum {
    MaxISYes = sizeof(ISZ) == 1 ? 120
             : sizeof(ISZ) == 2 ? 8 * 1024
             : sizeof(ISZ) == 4 ? 512 * 1024 * 1024
             : 0,
  };
  return MaxISYes;
}

/* Deletes the list contents without wiping the contents. */
template<LST_A>
void TListClear(LST* list) {
  list->map.count = 0;
  list->top = sizeof(LST) + list->map.total * (sizeof(ISZ) + sizeof(DT));
}

/* Gets an element of the Book by index. */
template<LST_A>
TATypeValue<ISZ, DT> TListTypeValue(const LST* list, ISY index) {
  if (index < 0 || index >= list->map.count) return { _NIL, nullptr };
  auto type_ptr = *TPtr<DT>(list, sizeof(LST) +
    list->map.total * sizeof(ISZ) + index * sizeof(DT));
  return { *type_ptr, *TStackStart<LST_P>(&list->map)[index] };
}

/* Gets an element of the Book by index. */
template<LST_A>
ATypeValue TListTypeValuePtr(const LST* list, ISY index) {
  if (index < 0 || index >= list->map.count) return { _NIL, nullptr };
  DTW type = DTW(*TPtr<DT>(list, sizeof(LST) +
    list->map.total * sizeof(ISZ) + index * sizeof(DT)));
  return { type, TPtr<void>(list, TStackStart<LST_P>(&list->map)[index]) };
}

/* Gets a points to the element of the Book by index. */
template<typename T = void, LST_A>
const T* TListValuePtr(const LST* list, ISY index) {
  if (index < 0 || index >= list->map.count) return nullptr;
  return TPtr<T>(list, TStackStart<ISA, ISZ>(&list->map)[index]);
}

/* Gets a points to the element of the Book by index. */
template<typename T = void, LST_A>
T* TListValuePtr(LST* list, ISY index) {
  return CPtr<T>(TListValuePtr<T, LST_P>(CPtr<LST>(list), index));
}

/* I don't remember what this does, it looks like it might be erroneously
labeled from a botched copy and replace in all files. */
template<typename T, LST_A>
CHA* TListContains(const LST* list, ISZ sizeof_value,
                   ISZ align_mask = sizeof(T) - 1) {
  ISZ size = list->map.total, count = list->map.count;
  if (count >= size) return nullptr;
  ISZ *offsets = TListValuesMap<LST_P>(list, size),  //
      *offsets_end = offsets + size;
  DT* types = TPtr<DT>(offsets_end);
  if (offsets == offsets_end) return nullptr;
  CHA* previous_begin = 0;

  CHA* origin = TPtr<CHA>(list, *offsets++);
  DT type = *types++;
  origin =
      PtrUp(origin, ATypeAlignMask(type)) + TSizeOf<ISZ>(origin, type);
  CHA* end = origin;
  ISY index = 0;
  while (++offsets < offsets_end) {
    end = PtrUp(end, align_mask);
    CHA* origin = TPtr<CHA>(list, *offsets++);
    if (TDelta<>(end, origin)) return index;
    ++index;
    DT type = *types++;
    origin = PtrUp(origin, ATypeAlignMask(type));
    CHA* end = origin + TSizeOf<ISZ>(origin, type);
    previous_begin = origin;
  }
}

/* Searches the list->offsets for the address.
@return An invalid index if the list doesn't dontain the address or the index
of the object if the list contains the address. */
template<LST_A>
ISY TListContains(const LST* list, void* address) {
  if (TListValues<LST_P>(list)) return false;
  return true;
}

/* Finds a tuple that contains the given address. */
template<LST_A>
ISY TListFind(const LST* list, void* address) {
  CHA* adr = TPtr<CHA>(address);
  ISZ size = list->map->size;
  ISZ* data_offsets = TListValuesMap<LST_P>(list, size);

  ISZ *offsets = TListValuesMap<LST_P>(list), *offset_end = offsets + list->count;
  ISZ offset = TDelta<ISZ>(list, address), index = 0;
  while (offsets < offset_end) {
    if (*data_offsets++ == offset) return index;
    ++index;
  }
  return -ErrorInvalidIndex;
}

/* Copies an ASCII List from the origin to the destination
template<LST_A>
struct TList {
  ISZ bytes,       //< Size of the List in bytes.
      top;              //< Offset to the top of the data.
  TStack<SCK_P> offsets;  //< Stack of offsets to the list items.
};
      List Memory Layout
+============================+
|_______   Boofer            |
|_______ ^ Value N           |
|        | Value 0           |
|----------------------------|
|_______   Boofer            |
|_______ ^ Type of Value N   |
|        | Type of Value 1   |
|----------------------------|
|_______   Boofer            |
|_______ ^ Offset to Value N |
|        | Offset to Value 1 |
+============================+  ^  Up in addresses.
|        TList Struct        |  |
+============================+ 0xN Base address

@todo research if it's faster to just copy the Boofer.
*/
template <typename T, LST_A>
LST* TListCopy(const LST* origin, LST* destination) {
  ISZ bytes = origin->bytes;
  if (destination->bytes < bytes) return nullptr;
  ISZ origin_count = origin->map.count,
      delta = TDelta<ISZ>(origin, destination);
  // 1. Copy Offsets.
  RAMCopy(destination, bytes, origin, TStackTop<T, ISZ>(origin->map));
  // 2. Copy Types.
  ISZ r_start = TDelta<ISZ>(origin, TListTypes<LST_P>(origin)),
      size = origin_count * sizeof(DT);
  RAMCopy(TPtr<>(destination, r_start), size, TPtr<>(origin, r_start), size);
  // 3. Copy Values.
  r_start = TDelta<ISZ>(origin, TListValues<LST_P>(origin)),
  size = TDelta<ISZ>(origin, destination->top);
  RAMCopy(TPtr<>(destination, r_start), size, TPtr<>(origin, r_start), size);
  return destination;
}

// Returns the end address of the 
template<typename T, LST_A>
T* TListValueEnd(LST* list, ISY index) {
}

/* Adds a given type-value tuple at the given index and values_begin.
index Codes:
SCKPush: -1  Pushes the value onto the top of the type-value stacks.
SCKPack: -2  Insert-packs the type-value into the first free memory slot.
@todo    Delete this function and use one insert function using the stack.
@return  ErrorInvalidIndex upon failure upon receiving an invalid index.
        ErrorBooferOverflow upon values boofer overflow/out of memory.
@warning Does not check for invalid types! */
template<typename T, LST_A>
ISY TListInsert(LST* list, T value, DT type, ISZ align_mask,
                ISY index, CHA* vbuf_begin, CHA* vbuf_end) {
  ISY count = ISY(list->map.count),
      total = ISY(list->map.total);
  ISZ top   = list->top;
  if (count < 0 || count > total || vbuf_begin > vbuf_end || 
      index >= total)
    return -ErrorInvalidHeader;
  if (count >= total ) return -ErrorStackOverflow;
  D_COUT("\nInserting " << STAATypePOD(type) << ':' << value <<
         " into index:" << index << " count: " << count);
  ISZ* voffsets = TListValuesMap<LST_P>(list);
  DT* types = (DT*)(voffsets + total);
  const BOL IsNotInserting = (index == count) && (index < count);
  ISZ bytes = list->bytes;
  if (index == PSH || index == count || count == 0) {
    D_COUT("\nSCKPush...");
    top = TAlignUp<ISZ>(top, align_mask);
    ISZ top_new = top + ISZ(sizeof(T));
    if (top_new > bytes) return -ErrorBooferOverflow;
    list->top = top_new;
    *(voffsets + index) = top;
    *TPtr<T>(list, top) = value;
    *(types + count) = type;
    list->map.count = ++count;
    return --count;
  } else if (index == PCK) {
    D_COUT("\nSCKPack...");
    ISZ offset_previous = *voffsets++;
    ++types;
    for (index = 1; index < count; ++index) {
      // @todo Do I need to point to the end of the value?
      ISZ offset = TATypeSizeOf<ISZ>(list, *voffsets++, *types++);
      ISZ offset_prev_aligned = TAlignUp<ISZ>(offset_previous, align_mask);
      if (offset - offset_prev_aligned <= sizeof(T)) break;
      offset_previous = offset;
    }
    *(voffsets + index) = top;
    *TPtr<T>(list, offset_previous) = value;
    TArrayInsert_NC<DT>(types + index, total, type);
    list->map.count = ++index;
    return --index;
  } else if(index <= ERR) {
    return -ErrorInvalidIndex;
  }
  D_COUT("\nInserting into into index:" << index);
  auto vbuf_stop = (index == count) ? bytes : voffsets[index];
  auto vbuf_start  = TPtrUp<CHA>(vbuf_begin, align_mask);
  if ((vbuf_start + sizeof(T)) > vbuf_end) return -ErrorBooferOverflow;
  *TPtr<T>(vbuf_start) = value;
  *(voffsets + index) = top;
  TArrayInsert_NC<DT>(types + index, total, type);
  list->map.count = count + 1;
  list->top = top + sizeof(T);
  return count;
}

/* Searches for the first empty spot in the list that can fit the item and
inserts the item to the list at the given index.
@return An invalid index upon failure or the index of the index upon success. */
template<LST_A>
inline ISY TListInsert(LST* list, IUA item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUA, LST_P>(list, item, _IUA, sizeof(IUA) - 1, index,
                                   values_begin, values_end);
}
template<LST_A>
inline ISY TListInsert(LST* list, CHA item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUA, LST_P>(list, ToUnsigned(item), _CHA,
                                   sizeof(IUA) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISY TListInsert(LST* list, ISA item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUA, LST_P>(list, ToUnsigned(item), _ISA,
                                   sizeof(IUA) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISY TListInsert(LST* list, IUB item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUB, LST_P>(list, item, _IUB, sizeof(IUB) - 1, index,
                                   values_begin, values_end);
}
template<LST_A>
inline ISY TListInsert(LST* list, ISB item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUB, LST_P>(list, ToUnsigned(item), _ISB,
                                   sizeof(IUB) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISY TListInsert(LST* list, CHB item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUB, ISZ>(list, ToUnsigned(item), _CHB, sizeof(IUB) - 1,
                               index, values_begin, values_end);
}
//template<LST_A>
//inline ISY TListInsert(LST* list, BOL item, ISY index, CHA* values_begin,
//                       CHA* values_end) {
//  return TListInsert<IUB, LST_P>(list, ToUnsigned(item), _BOL,
//                                   sizeof(BOL) - 1, index, values_begin,
//                                   values_end);
//}
template<LST_A>
inline ISY TListInsert(LST* list, IUC item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUC, LST_P>(list, item, _IUC, sizeof(IUC) - 1, index,
                                   values_begin, values_end);
}
template<LST_A>
inline ISY TListInsert(LST* list, ISC item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUC, LST_P>(list, ToUnsigned(item), _ISC,
                                   sizeof(IUC) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISY TListInsert(LST* list, CHC item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUC, LST_P>(list, ToUnsigned(item), _CHC,
                                   sizeof(IUC) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISY TListInsert(LST* list, FPC item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUC, LST_P>(list, ToUnsigned(item), _FPC,
                                   sizeof(IUC) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISY TListInsert(LST* list, IUD item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUD, LST_P>(list, item, _IUD, ALUWordMask, index,
                                   values_begin, values_end);
}
template<LST_A>
inline ISY TListInsert(LST* list, ISD item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUD, LST_P>(list, ToUnsigned(item), _ISD, ALUWordMask,
                                   index, values_begin, values_end);
}
template<LST_A>
inline ISY TListInsert(LST* list, FPD item, ISY index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUD, LST_P>(list, ToUnsigned(item), _FPD, ALUWordMask,
                                   index, values_begin, values_end);
}

/* Inserts the item into the list at the given index. */
template<LST_A>
inline ISY TListInsert(LST* list, IUA item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, ISA item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, CHA item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
    TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, IUB item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, ISB item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, CHB item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, IUC item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, ISC item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, CHC item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, FPC item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, IUD item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, ISD item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, FPD item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
                              TListValuesEnd<LST_P>(list));
}
template<LST_A>
inline ISY TListInsert(LST* list, BOL item, ISY index = PSH) {
  return TListInsert<LST_P>(list, item, index, TListValuesTop<LST_P>(list),
    TListValuesEnd<LST_P>(list));
}

/* Inserts the item into the list at the given index. */
template<LST_A>
inline ISY TListInsert(LST* list, DT type, const void* value, 
    ISY index = PSH) {
  auto bytes = list->bytes;
  auto top        = list->top;
  ISY  total  = ISY(list->map.total),
       count      = ISY(list->map.count);
  if (index == PSH) index = count;
  if (index < 0 || index > count) return -ErrorInvalidIndex;
  D_COUT("\n\nInserting type:" << ATypef(type) << ":0d" << type << ":0x" << Hexf(type));
  auto align_mask = ATypeAlignMask(type);
  if (index == count) {
    //TListPrint<COut, LST_P>(StdOut(), list);
    auto result = TATypeWrite_NC<ISZ>(TPtr<>(list, top), TPtr<>(list, bytes), 
                                      type, value, align_mask);
    if (result == 0) return -ErrorBooferOverflow;
    TListValuesMap<LST_P>(list)[count] = top;
    TListTypes<LST_P>(list)[count] = type;
    list->map.count = ++count;
    list->top = TDelta<ISZ>(list, result);
    return index;
  }
  D_ASSERT(false); // @todo Fix me!
  ISZ stop = TListValueOffset_NC<LST_P>(list, index + 1);
  auto value_bytes = ATypeBytes(value, type);
  if (value_bytes <= 0) {
    value_bytes *= -1;
    if (bytes - top) return -ErrorStackOverflow;
    return index;
  }
  top = TAlignUp<ISZ>(top, align_mask);
  if (stop - top >= bytes) return -ErrorStackOverflow;
  // @todo finish me.
  return -1;
}

// Allocates memory for an ASCII Object of the given size.
// @return The index of the allocated type-value.
template<LST_A>
inline ISY TListAlloc(LST* list, DT type, ISZ bytes,
    ISY index = PSH) {
  ISA  align_mask = ATypeAlignMask(DTB(type));
  auto top        = TAlignUp<ISZ>(list->top, align_mask);
  ISY  count      = ISY(list->map.count),
       total      = ISY(list->map.total);
  if (top + bytes > list->bytes || count >= total) return -1;
  *TPtr<ISZ>(list, top) = bytes;
  auto voffsets   = TListValuesMap<LST_P>(list);
  voffsets[count] = top;
  auto types      = TPtr<DT>(voffsets + total);
  types[count++]  = type;
  list->top       = top + bytes;
  list->map.count = count--;
  return count;
}

/* Removes the item at the given address from the list. */
template<LST_A>
inline void* TListRemove(LST* list, ISY index) {
  ISY count = ISY(list->map.count);
  ISZ* offsets = TListValuesMap<LST_P>(list);
  TArrayRemove<ISZ, ISY>(offsets, count, index);
  TArrayRemove<DT, ISY>(TListTypes<LST_P>(list), count, index);
  return offsets + index;
}

/* Removes the item at the given address from the list. */
template<LST_A>
inline void* TListRemove(LST* list, void* address) {
  return TListRemove<LST_P>(list, TListFind(list, address));
}

/* Removes a type-value to the stop of the list. */
template<LST_A>
inline void* TListPop(LST* list) {
  return TListRemove<LST_P>(list, ISY(list->map.count) - 1);
}

/* Creates an Autoject boofer large enough to fit a List with the given. */
template<LST_A>
IUW* TListNew(ISZ size_data, ISY total, RAMFactory ram) {
  ISY total_align_lsb_mask = (sizeof(ISZ) / sizeof(DT)) - 1;
  total = AlignUp(total, total_align_lsb_mask);
  ISZ bytes = sizeof(LST) + total * (sizeof(ISZ) + sizeof(DT)) +
                   AlignUp(size_data);
  IUW* boofer = ram(nullptr, ISW(bytes));
  LST* list = TPtr<LST>(boofer);
  return TPtr<IUW>(TListInit<LST_P>(list, bytes, total));
}

/* ASCII List that uses dynamic memory. */
template<typename ISZ = ISR, typename ISY = ISQ, ISZ SizeBytes_ = 512, ISY Total_ = 32,
          typename BUF = TBUF<SizeBytes_, IUA, ISZ, Nil>, typename DT = DTB>
class AList {
  AArray<IUA, ISZ, BUF> obj_;  //< An Auto-array.
 public:
  static constexpr DT Type() { return CTypeMap<DT>(CATypeSize<ISZ>()); }

  /* Constructs a list with a given total with estimated bytes. */
  AList(ISY total = Total_)
      : obj_(TListNew<LST_P>(SizeBytes_, total,
             TRAMFactory<Type()>().Init<BUF>()),
             TRAMFactory<Type()>().Init<BUF>()) {}

  /* Constructs a List with the given bytes and total. */
  AList(ISY total, ISZ bytes)
      : obj_(TListNew<LST_P>(bytes, total,
             TRAMFactory<Type()>().Init<BUF>()),
             TRAMFactory<Type()>().Init<BUF>()) {}

  /* Inserts the given type-value tuple in the list at the given index. */
  inline ISY Insert(IUA type, void* value, ISY index) {
    return TListInsert<LST_P>(This(), type, value, index);
  }

  /* Maximum count of the item in the List. */
  inline ISZ Size() { return TListSize<LST_P>(); }

  /* Count of the item in the List. */
  inline ISY Count() { return TListSize<LST_P>(); }

  /* Count of the item in the List. */
  inline ISZ SizeBytes() { return This()->bytes; }

  /* Count of the item in the List. */
  inline ISZ SizeWords() { return TSizeWords<ISZ>(SizeBytes()); }

  /* Count of the item in the List. */
  inline ISZ Top() { return This()->top; }

  /* Returns true if this crabs contains only the given address.
  @warning This function assumes that the member you're checking for came from
  Script. If it's you're own code calling this, you are required to ensure the
  value came from a ASCII List.
  @return  True if the data lies in the list's memory array. */
  inline CHA* Contains(void* value) {
    return TListContains<ISZ>(This(), value);
  }

  /* Clears the list by setting the count to 0. */
  void Clear() { TListClear<LST_P>(This()); }

  /* Removes the item at the given address from the list. */
  inline BOL Remove(void* address) { return TListRemove<LST_P>(This(), address); }

  /* Removes the item at the given address from the list. */
  inline BOL Remove(ISY index) { return TListRemove<LST_P>(This(), index); }

  /* Searches for the first empty spot in the list that can fit the item and
  inserts the item to the list at the given index.
  @return An invalid index upon failure or the index of the index upon success.
  */
  ISY Insert(IUA item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(ISA item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(CHA item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(IUB item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(ISB item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(CHB item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(BOL item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(IUC item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(ISC item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(CHC item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(FPC item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(IUD item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(ISD item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }
  ISY Insert(FPD item, ISY index = PSH) {
    return TListInsert<LST_P>(This(), item, index);
  }

  inline ISY Insert(DT type, const void* value, ISY index = PSH) {
    return TListInsert<LST_P>(This(), type, value, index);
  }

  /* Removes the last item from the list.
  @returns The address of the object just popped off the stack. */
  inline void* Pop() { return TListPop<LST_P>(This()); }

  /* Gets the obj_'s Autoject. */
  inline Autoject AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array. */
  inline AArray<IUA, ISZ>& AJT_ARY() { return obj_; }

  /* Returns the contiguous ASCII List boofer_. */
  inline LST* This() { return TPtr<LST>(AJT().origin); }

  /* Prints This object to the printer. */
  template<typename Printer>
  Printer& PrintTo(Printer& o) {
    return TListPrint<Printer, ISZ>(o, This());
  }
};

}  //< namespace _

template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, CHA item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, ISA item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, IUA item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, CHB item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, ISB item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, IUB item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, BOL item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, CHC item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, IUC item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, ISC item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, FPC item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, ISD item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, IUD item) {
  list.Add(item);
}
template<LST_A>
inline ::_::LST& operator<<(::_::LST& list, FPD item) {
  list.Add(item);
}

#endif
#endif
