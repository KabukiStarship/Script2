/* Script2�
@link    https://github.com/KabukiStarship/Script2.git
@file    /List.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship� <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
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
#define LST_A  typename ISZ = ISN, typename DT = DTB
#define LST_P ISZ, DT
namespace _ {

/* A collection of type-value tuples.
@see ASCII Data Type Specification.
@link /Spec/Data/MapTypes/Map.md
@code
      List Memory Layout
+============================+
|_______   Buffer            |<--- top
|_______ ^ Value N           |
|        | Value 0           |
|----------------------------|
|_______   Buffer            |
|_______ ^ Type of Value N   |
|        | Type of Value 0   |
|----------------------------|
|_______   Buffer            |
|_______ ^ Offset to Value N |
|        | Offset to Value 0 |
+============================+  ^  Up in addresses.
|        TList Struct        |  |
+============================+ 0xN Base address
@endcode
*/
template<typename ISZ = ISN>
struct TList {
  ISZ size_bytes,   //< Size of the List in bytes.
      top;          //< Offset to the top of the data.
  TStack<ISZ> map;  //< Stack of offset mappings to the list items.
};

/* Calculates the minimum size of a List with all nil objects. */
template<typename ISZ = ISN, typename DT = DTB>
inline ISZ TListSizeMin(ISZ count_max) {
  return sizeof(TList<ISZ>) + count_max * (sizeof(ISZ) + sizeof(DT));
}

/* The maximum theoretical amount of freespace in a List. */
template<typename ISZ = ISN, typename DT = DTB>
inline ISZ TListSizeFreeMax(ISZ size_bytes, ISZ count_max) {
  return size_bytes - sizeof(TList<ISZ>) - 
         count_max * (sizeof(DT) + sizeof(ISZ));
}

/* Gets the base pointer to the Offsets. */
template<typename ISZ = ISN>
inline ISZ* TListValueOffsets(TList<ISZ>* list) {
  return TStackStart<ISZ, ISZ>(&list->map);
}

/* Returns the type bytes array. */
template<LST_A>
inline DT* TListTypes(TList<ISZ>* list) {
  return TPtr<DT>(TListValueOffsets<ISZ>(list) + list->map.count_max);
}

/* Returns the type at the given index. */
template<LST_A>
inline DT* TListType(TList<ISZ>* list, ISZ index) {
  if (index < 0 || index >= list->map->count_max) return NIL;
  return TPtr<DT>(TListValueOffsets<ISZ>(list) + list->map.count_max);
}

/* Gets the first element of the List. */
template<LST_A, typename T>
inline T* TListBase(TList<ISZ>* list) {
  return TPtr<T>(list, sizeof(TList<ISZ>) +
                 list->map.count_max * (sizeof(ISZ) + sizeof(DT)));
}
template<LST_A, typename T>
inline const T* TListBase(const TList<ISZ>* list) {
  return TPtr<T>(list, sizeof(TList<ISZ>) +
                       list->map.count_max * (sizeof(ISZ) + sizeof(DT)));
}

/* Returns the type at the given index. */
template<LST_A>
inline void* TListValue(TList<ISZ>* list, ISZ index) {
  if (index < 0 || index >= list->map->count_max) return NIL;
  return TListValueOffsets<ISZ>(list) + list->map.count_max;
}

/* Returns the type and value offset at the given index. */
template<LST_A>
inline TTypeValueOffset<ISZ> TListTypeValueOffset(TList<ISZ>* list, ISZ index) {
  if (index < 0 || index >= list->map->count_max) return NIL;
  auto values = TListValueOffsets<ISZ, DT>(list);
  auto types = TPtr<DT>(values + list->map->count_max);
  return {types[index], values[index]};
}

/* Gets the base pointer to the values. */
template<LST_A>
inline CHA* TListValues(TList<ISZ>* list, ISZ size) {
  return TPtr<CHA>(TListTypes<ISZ, DT>(list, size) + list->map.count_max);
}
template<typename ISZ = ISN>
inline CHA* TListValues(TList<ISZ>* list) {
  return TListValues<ISZ>(list, list->map->size);
}

template<typename ISZ = ISN>
inline void* TListTop(TList<ISZ>* list) {
  return TPtr<void*>(list, list->top);
}

/* Returns the value at the given index.
@return Returns nil if the index is out of the count range. */
template<typename ISZ = ISN>
inline const void* TListValue(TList<ISZ>* list, ISZ index) {
  if (index < 0 || index >= list->count) return nullptr;
  return TPtr<CHA>(list) + TListValueOffsets<ISZ>(list)[index];
}

/* Returns the TTypeValue at the given index.
@return Returns nil if the index is out of the count range. */
template<typename IS = ISN, typename DT = DTW>
inline const TTypeValue<DT> TListTypeValue(TList<IS>* list, IS index) {
  if (index < 0 || index >= list->map.count) return { 0, 0 };
  auto value_offsets = TListValueOffsets<IS>(list);
  auto types = TPtr<DT>(value_offsets + list->map.count_max);
  return { types[index], TPtr<void>(list, value_offsets[index])};
}

/* Returns the TTypeValue at the given index.
@return Returns nil if the index is out of the count range. */
template<typename IS = ISN, typename DT = DTW>
inline const TTypeValueOffset<IS, DT> TListTypeValueOffset(TList<IS>* list, IS index) {
  if (index < 0 || index >= list->map.count) return { 0, 0 };
  auto value_offsets = TListValueOffsets<IS>(list);
  auto types = TPtr<DT>(value_offsets + list->map.count_max);
  return { types[index], value_offsets };
}

// I don't have to have these.
// Prints the list to the output stream.
template<typename Printer, LST_A>
Printer& TListPrintTypeValue(Printer& o, TList<ISZ>* list, ISZ index) {
  return TPrintValue<Printer, DT>(o, TListType<ISZ>(list, index),
                                  TListValue<ISZ>(list, index));
}

// Prints the list to the output stream.
template<typename Printer, LST_A>
Printer& TListPrintValue(Printer& o, TList<ISZ>* list, ISZ index) {
  return TPrintValue<Printer, DT, ISZ>(o, TListTypeValue<ISZ, DT>(list, index));
}

/* Prints the list to the output stream. */
template<typename Printer, LST_A>
Printer& TListPrint(Printer& o, TList<ISZ>* list) {
  ISZ count = list->map.count, count_max = list->map.count_max;
  o << Linef("\n\n+---\n| List<IS") << TSizef<ISZ>()
    << "> size_bytes:" << list->size_bytes << " count_max:" << count_max
    << " count:" << count << Linef("\n+---");
  ISZ* data_offsets = TListValueOffsets<ISZ>(list);
  DT* dt_offsets = TPtr<DT>(data_offsets + count_max);
  for (ISZ index = 0; index < count; ++index) {
    ISZ data_offset = *data_offsets++;
    DT data_type = *dt_offsets++;
    o << "\n| " << Centerf(index, ISW(STRLength(count)) + 2)
      << Centerf(STRTypePOD(data_type), 10) << ' ';
    const void* value = TPtr<CHA*>(list, TListValueOffsets<ISZ>(list)[index]);
    TPrintValue<Printer, DT>(o, data_type, value);
  }
  return o << Linef("\n+---");
}

/* Returns the minimum count to align the data struct to a 64-bit boundary. */
template<typename ISZ = ISN>
constexpr ISZ TListCountMaxBoundsLower() {
  return 8 / sizeof(ISZ);
}

/* Initializes a AsciiList from preallocated memory.
count_max must be in multiples of 4. Given there is a fixed size, both the
count_max and size will be downsized to a multiple of 4 automatically. */
template<LST_A>
TList<ISZ>* TListInit(TList<ISZ>* list, ISZ size_bytes, ISZ count_max) {
  D_ARRAY_WIPE(list, size_bytes);
  list->size_bytes = size_bytes;
  list->map.count = 0;
  list->map.count_max = count_max;
  list->top = sizeof(TList<ISZ>) + count_max * (sizeof(ISZ) + sizeof(DT));
  return list;
}

/* Returns the min size of an ASCII List with the given count_max.
The min size is defined as enough memory to store the given count_max with
the largest_expected_type.
*/
template<typename ISZ = ISN, ISW largest_expected_type = sizeof(ISW)>
constexpr ISZ TListSizeMin(ISZ count_max) {
  return sizeof(TList<ISZ>) +
         ISZ(count_max * (largest_expected_type + sizeof(ISZ) + 1));
}

/* Returns the end byte of the data. */
template<typename ISZ = ISN>
inline CHA* TListEnd(TList<ISZ>* list, ISZ size) {
  return TPtr<CHA>(list) + list->size_bytes;
  //return TPtr<CHA>(list) + sizeof(TList<ISZ>) + list->size_bytes;
  //@Todo Why does this not add the size of the struct like the Array?
}
template<typename ISZ = ISN>
inline CHA* TListEnd(TList<ISZ>* list) {
  return TListEnd<ISZ>(list, list->map.count_max);
}

/* Gets the first addrss in the Values section where you may be able to write
too. */
template<typename ISZ = ISN>
inline CHA* TListValuesTop(TList<ISZ>* list) {
  return TPtr<CHA>(list, list->top);
}

template<typename ISZ = ISN>
inline CHA* TListValuesEnd(TList<ISZ>* list) {
  return TPtr<CHA>(list, list->size_bytes);
}

/* Calculates the amount of space left in the data socket. */
template<typename ISZ = ISN>
inline ISZ TListFreeSpace(TList<ISZ>* list) {
  return list->size_bytes - list->top;
}
    /* Returns the max count an array can handle. */
template<typename ISZ = ISN>
ISZ TListSize() {
  enum {
    cMaxSIYes = sizeof(ISZ) == 1 ? 120
              : sizeof(ISZ) == 2 ? 8 * 1024
              : sizeof(ISZ) == 4 ? 512 * 1024 * 1024
              : 0,
  };
  return cMaxSIYes;
}

/* Deletes the list contents without wiping the contents. */
template<LST_A>
void TListClear(TList<ISZ>* list) {
  list->count = 0;
  list->top = sizeof(TList<ISZ>) + list->map.count_max * (sizeof(ISZ) + sizeof(DT));
}

/* Gets a points to the element of the Book by index. */
template<typename ISZ = ISN>
ISA* TListGetPtr(TList<ISZ>* list, ISZ index) {
  if (index < 0 || index >= list->map.count) return nullptr;
  return TPtr<ISA>(list, TStackStart<ISA, ISZ>(&list->map)[index]);
}

/* Gets an element of the Book by index. */
template<typename ISZ, typename DT = DTB>
TypeWordValue TListGet(TList<ISZ>* list, ISZ index) {
  if (index < 0 || index >= list->map.count) return { _NIL, nullptr };
  DTW type = DTW(*TPtr<DT>(list, sizeof(TList<ISZ>) +
    list->map.count_max * sizeof(ISZ) + index * sizeof(DT)));
  void* value = TPtr<void>(list, TStackStart<ISZ, ISZ>(&list->map)[index]);
  return { type, value };
}

/* I don't remember what this does, it looks like it might be erroneously
labeled from a botched copy and replace in all files. */
template<typename T, typename ISZ = ISN, typename DT = DTB>
CHA* TListContains(TList<ISZ>* list, ISZ sizeof_value,
                   ISZ align_mask = sizeof(T) - 1) {
  ISZ size = list->map.count_max, count = list->map.count;
  if (count >= size) return nullptr;
  ISZ *offsets = TListValueOffsets<ISZ>(list, size),  //
      *offsets_end = offsets + size;
  DT* types = TPtr<DT>(offsets_end);
  if (offsets == offsets_end) return nullptr;
  CHA* previous_begin = 0;

  CHA* origin = TPtr<CHA>(list, *offsets++);
  DT type = *types++;
  origin =
      AlignUpPTR(origin, TypeAlignmentMask(type)) + TSizeOf<ISZ>(origin, type);
  CHA* end = origin;
  ISZ index = 0;
  while (++offsets < offsets_end) {
    end = AlignUpPTR(end, align_mask);
    CHA* origin = TPtr<CHA>(list, *offsets++);
    if (TDelta<>(end, origin)) return index;
    ++index;
    DT type = *types++;
    origin = AlignUpPTR(origin, TypeAlignmentMask(type));
    CHA* end = origin + TSizeOf<ISZ>(origin, type);
    previous_begin = origin;
  }
}

/* Searches the list->offsets for the address.
@return An invalid index if the list doesn't dontain the address or the index
of the object if the list contains the address. */
template<typename ISZ = ISN>
ISZ TListContains(TList<ISZ>* list, void* address) {
  if (TListValues<ISZ>(list)) return false;
  return true;
}

/* Finds a tuple that contains the given address. */
template<typename ISZ = ISN>
ISZ TListFind(TList<ISZ>* list, void* address) {
  CHA* adr = TPtr<CHA>(address);
  ISZ size = list->map->size;
  ISZ* data_offsets = TListValueOffsets<ISZ>(list, size);

  ISZ *offsets = TListValueOffsets<ISZ>(list), *offset_end = offsets + list->count;
  ISZ offset = TDelta<ISZ>(list, address), index = 0;
  while (offsets < offset_end) {
    if (*data_offsets++ == offset) return index;
    ++index;
  }
  return ErrorInvalidIndex;
}

/* Copies an ASCII List from the origin to the destination
* template<typename ISZ = ISN>
struct TList {
  ISZ size_bytes,       //< Size of the List in bytes.
      top;              //< Offset to the top of the data.
  TStack<ISZ> offsets;  //< Stack of offsets to the list items.
};
      List Memory Layout
+============================+
|_______   Buffer            |
|_______ ^ Value N           |
|        | Value 0           |
|----------------------------|
|_______   Buffer            |
|_______ ^ Type of Value N   |
|        | Type of Value 1   |
|----------------------------|
|_______   Buffer            |
|_______ ^ Offset to Value N |
|        | Offset to Value 1 |
+============================+  ^  Up in addresses.
|        TList Struct        |  |
+============================+ 0xN Base address

@todo research if it's faster to just copy the Buffer.
*/
template <LST_A>
TList<ISZ>* TListCopy(const TList<ISZ>* origin, TList<ISZ>* destination) {
  ISZ size_bytes = origin->size_bytes;
  if (destination->size_bytes < size_bytes) return nullptr;
  ISZ origin_count = origin->map.count,
      delta = TDelta<ISZ>(origin, destination);
  // 1. Copy Offsets.
  ArrayCopy(destination, size_bytes, origin, TStackTop<T, ISZ>(origin->map));
  // 2. Copy Types.
  ISZ r_start = TDelta<ISZ>(origin, TListTypes<ISZ, DT>(origin)),
      size = origin_count * sizeof(DT);
  ArrayCopy(TPtr<>(destination, r_start), size, TPtr<>(origin, r_start), size);
  // 3. Copy Values.
  r_start = TDelta<ISZ>(origin, TListValues<ISZ, DT>(origin)),
  size = TDelta<ISZ>(origin, destination->top);
  ArrayCopy(TPtr<>(destination, r_start), size, TPtr<>(origin, r_start), size);
  return destination;
}

/* Pushes a an ASCII Array onto the List stack. */
template<typename T, LST_A>
T* TListPush(TList<ISZ>* list, ISZ size_bytes_new, DT type, 
             ISW align_mask = WordLSbMask) {
  // Offset to the value pointer.
  auto dest = AlignUpPTR(TPtr<void>(list, list->top), align_mask);
  ISZ value_offset = TDelta<ISZ>(list, dest),
      size_buffer  = list->size_bytes - value_offset,
      count        = list->map.count;
  if (count >= list->map.count_max ||
      size_buffer < size_bytes_new) return nullptr;
  TStackPushUnchecked<ISZ, ISZ>(&list->map, value_offset, count);
  list->top = value_offset + size_bytes_new;
  auto ptr = TPtr<ISZ>(list, value_offset);
  *ptr = size_bytes_new;
  // Push the DT onto the Data Types stack.
  TListTypes<LST_P>(list)[count] = type;
  return TPtr<T>(ptr);
}

/* Adds a given POD type-value tuple at the given index and values_begin.
@return cErrorInvalidIndex upon failure or the index upon success. */
template<typename T, LST_A>
ISZ TListInsert(TList<ISZ>* list, T item, DT type, ISZ alignment_mask,
                ISZ index, CHA* values_begin, CHA* values_end) {
  ISZ count = list->map.count, size = list->map.count_max;
  D_ASSERT(count >= 0 && values_begin < values_end);
  D_COUT("\nInserting " << STRTypePOD(type) << ':' << item
         << " into index:" << index << " count: " << count);
  if (index == STKPush) {
    // look for the first place in the stack to put the item.
    ISZ* offsets = TListValueOffsets<ISZ>(list);
    ISW base_addr = TDelta<ISW>(list);
    for (ISZ i = 0; i <= count; ++i) {
      ISZ offset = *offsets++;
      ISW address = base_addr + offset;
      // @todo Fix me!
    }
  }
  if (index < 0 || index > count || count >= size || !TypeIsSupported(type))
    return ErrorInputInvalid;

  values_begin = TAlignUpPTR<CHA>(values_begin, alignment_mask);
  if ((values_begin + sizeof(T)) > values_end) return ErrorInvalidIndex;
  *TPtr<T>(values_begin) = item;

  ISZ* offsets = TListValueOffsets<ISZ>(list);
  DT* types = TListTypes<ISZ, DT>(list);

  TStackInsert<ISZ, ISZ>(TStackStart<ISZ, ISZ>(&list->map), count, index,
                         TDelta<ISZ>(list, values_begin));
  TStackInsert<DT, ISZ>(types, count, index, type);
  list->map.count = count + 1;
  return count;
}

/* Searches for the first empty spot in the list that can fit the item and
inserts the item to the list at the given index.
@return An invalid index upon failure or the index of the index upon success. */
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUA item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUA, ISZ, DT>(list, item, _IUA, sizeof(IUA) - 1, index,
                                   values_begin, values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, CHA item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUA, ISZ, DT>(list, ToUnsigned(item), _CHA,
                                   sizeof(IUA) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISA item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUA, ISZ, DT>(list, ToUnsigned(item), _ISA,
                                   sizeof(IUA) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUB item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUB, ISZ, DT>(list, item, _IUB, sizeof(IUB) - 1, index,
                                   values_begin, values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISB item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUB, ISZ, DT>(list, ToUnsigned(item), _ISB,
                                   sizeof(IUB) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, CHB item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUB, ISZ>(list, ToUnsigned(item), _CHB, sizeof(IUB) - 1,
                               index, values_begin, values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, BOL item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUB, ISZ, DT>(list, ToUnsigned(item), _BOL,
                                   sizeof(BOL) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUC item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUC, ISZ, DT>(list, item, _IUC, sizeof(IUC) - 1, index,
                                   values_begin, values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISC item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUC, ISZ, DT>(list, ToUnsigned(item), _ISC,
                                   sizeof(IUC) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, CHC item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUC, ISZ, DT>(list, ToUnsigned(item), _CHC,
                                   sizeof(IUC) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, FPC item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUC, ISZ, DT>(list, ToUnsigned(item), _FPC,
                                   sizeof(IUC) - 1, index, values_begin,
                                   values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUD item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUD, ISZ, DT>(list, item, _IUD, WordLSbMask, index,
                                   values_begin, values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISD item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUD, ISZ, DT>(list, ToUnsigned(item), _ISD, WordLSbMask,
                                   index, values_begin, values_end);
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, FPD item, ISZ index, CHA* values_begin,
                       CHA* values_end) {
  return TListInsert<IUD, ISZ, DT>(list, ToUnsigned(item), _FPD, WordLSbMask,
                                   index, values_begin, values_end);
}

/* Pushes the item onto the List stack. */
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUA item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, CHA item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISA item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUB item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISB item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, CHB item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUC item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISC item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, BOL item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, CHC item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, FPC item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUD item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISD item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, FPD item) {
  return TListInsert<ISZ, DT>(list, item, list->map.count_max,
                              TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}

/* Inserts the item into the list at the given index. */
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUA item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, CHA item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISA item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUB item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISB item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, CHB item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUC item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISC item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, BOL item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, CHC item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, FPC item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, IUD item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, ISD item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}
template<LST_A>
inline ISZ TListInsert(TList<ISZ>* list, FPD item, ISZ index) {
  return TListInsert<ISZ, DT>(list, item, index, TListValuesTop<ISZ>(list),
                              TListValuesEnd<ISZ>(list));
}

template<typename ISZ = ISN>
inline ISZ TSizeOf(void* value, DTB type) {
  ISW size_bytes = TypeSizeOf(type);
  if (size_bytes != 0) return size_bytes;
}

/* Removes the item at the given address from the list. */
template<LST_A>
inline void* TListRemove(TList<ISZ>* list, ISZ index) {
  ISZ count = list->map.count;
  ISZ* offsets = TListValueOffsets<ISZ>(list);
  TStackRemove<ISZ, ISZ>(offsets, count, index);
  TStackRemove<DT, ISZ>(TListTypes<ISZ, DT>(list), count, index);
  return offsets + index;
}

/* Removes the item at the given address from the list. */
template<typename ISZ = ISN>
inline void* TListRemove(TList<ISZ>* list, void* address) {
  return TListRemove<ISZ>(list, TListFind(list, address));
}

/* Removes a type-value to the stop of the list. */
template<typename ISZ = ISN>
inline void* TListPop(TList<ISZ>* list) {
  return TListRemove<ISZ>(list, list->map.count - 1);
}

/* Creates an Autoject buffer large enough to fit a List with the given. */
template<typename ISZ = ISN, typename DT = DTB>
IUW* TListNew(ISZ size_data, ISZ count_max, RAMFactory ram) {
  ISZ count_max_align_lsb_mask = (sizeof(ISZ) / sizeof(DT)) - 1;
  count_max = AlignUp(count_max, count_max_align_lsb_mask);
  ISZ size_bytes = sizeof(TList<ISZ>) + count_max * (sizeof(ISZ) + sizeof(DT)) +
                   AlignUp(size_data);
  IUW* buffer = ram(nullptr, ISW(size_bytes));
  TList<ISZ>* list = TPtr<TList<ISZ>>(buffer);
  return TPtr<IUW>(TListInit<ISZ>(list, size_bytes, count_max));
}

/* ASCII List that uses dynamic memory. */
template<typename ISZ = ISN, ISZ cSizeBytes_ = 512, ISZ cCountMax_ = 32,
          typename BUF = TBUF<cSizeBytes_, IUA, ISZ, Nil>, typename DT = DTB>
class AList {
  AArray<IUA, ISZ, BUF> obj_;  //< An Auto-array.
 public:
  static constexpr DT Type() { return CTypeMap<DT>(CTypeSize<ISZ>()); }

  /* Constructs a list with a given count_max with estimated size_bytes. */
  AList(ISZ count_max = cCountMax_)
      : obj_(TListNew<ISZ, DT>(cSizeBytes_, count_max,
                                    TRamFactory<Type()>().Init<BUF>()),
             TRamFactory<Type()>().Init<BUF>()) {}

  /* Constructs a List with the given size_bytes and count_max. */
  AList(ISZ count_max, ISZ size_bytes)
      : obj_(TListNew<ISZ, DT>(size_bytes, count_max,
                                    TRamFactory<Type()>().Init<BUF>()),
             TRamFactory<Type()>().Init<BUF>()) {}

  /* Inserts the given type-value tuple in the list at the given index. */
  inline ISZ Insert(IUA type, void* value, ISZ index) {
    return TListInsert<ISZ, DT>(This(), type, value, index);
  }

  /* Maximum count of the item in the List. */
  inline ISZ Size() { return TListSize<ISZ>(); }

  /* Count of the item in the List. */
  inline ISZ Count() { return TListSize<ISZ>(); }

  /* Count of the item in the List. */
  inline ISZ SizeBytes() { return This()->size_bytes; }

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
  void Clear(TList<ISZ>* list) { TListClear<ISZ>(This()); }

  /* Removes the item at the given address from the list. */
  inline BOL Remove(void* address) { return TListRemove<ISZ>(This(), address); }

  /* Removes the item at the given address from the list. */
  inline BOL Remove(ISZ index) { return TListRemove<ISZ>(This(), index); }

  /* Searches for the first empty spot in the list that can fit the item and
  inserts the item to the list at the given index.
  @return An invalid index upon failure or the index of the index upon success.
  */
  ISZ Insert(IUA item, ISZ index) { return TListInsert<IUA>(This(), item); }
  ISZ Insert(ISA item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(CHA item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(IUB item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(ISB item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(CHB item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(BOL item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(IUC item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(ISC item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(CHC item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(FPC item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(IUD item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(ISD item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }
  ISZ Insert(FPD item, ISZ index) { return TListInsert<ISZ, DT>(This(), item); }

  /* Pushes the item onto the List stack.
  @return An invalid index upon failure or the index of the item in the list
  upon success. */
  ISZ Insert(IUA item) { return TListInsert<IUA>(This(), item); }
  ISZ Insert(ISA item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(CHA item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(IUB item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(ISB item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(CHB item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(BOL item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(IUC item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(ISC item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(CHC item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(FPC item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(IUD item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(ISD item) { return TListInsert<ISZ>(This(), item); }
  ISZ Insert(FPD item) { return TListInsert<ISZ>(This(), item); }

  inline ISZ Insert(DT type, const void* value) {
    return TListInsert<ISZ, DT>(This(), type, value);
  }

  /* Removes the last item from the list.
  @returns The address of the object just popped off the stack. */
  inline void* Pop() { return TListPop<ISZ>(This()); }

  /* Gets the obj_'s Autoject. */
  inline Autoject AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array. */
  inline AArray<IUA, ISZ>& AJT_ARY() { return obj_; }

  /* Returns the contiguous ASCII List buffer_. */
  inline TList<ISZ>* This() { return TPtr<TList<ISZ>>(AJT().origin);
  }

  /* Prints This object to the printer. */
  template<typename Printer>
  Printer& PrintTo(Printer& o) {
    return TListPrint<Printer, ISZ>(o, This());
  }
};

}  //< namespace _

template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, CHA item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, ISA item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, IUA item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, CHB item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, ISB item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, IUB item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, BOL item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, CHC item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, IUC item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, ISC item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, FPC item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, ISD item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, IUD item) {
  list.Add(item);
}
template<typename ISZ = ISN>
inline _::TList<ISZ>& operator<<(_::TList<ISZ>& list, FPD item) {
  list.Add(item);
}

#endif
#endif
