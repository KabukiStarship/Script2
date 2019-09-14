/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /list.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_LIST
#ifndef INCLUDED_SCRIPTTLIST
#define INCLUDED_SCRIPTTLIST

#include "binary.hpp"
#include "set.hpp"
#include "stack.hpp"
#include "typevalue.hpp"

#if SEAM == SCRIPT2_LIST
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* A collection of type-value tuples.
@see ASCII Data Type Specification.
@link file://./spec/data/map_types/map.md
@code
      List Memory Layout
+----------------------------+
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
|----------------------------|  ^ Up in addresses.
|        TList Struct        |  |
+----------------------------+ 0xN
@endcode
*/
template <typename SIZ = SIN>
struct TList {
  SIZ size_bytes,  //< Size of the List in bytes.
      top;         //< Offset to the top of the data.
  TStack<SIZ> offsets;
};

/* Gets the base pointer to the Offsets. */
template <typename SIZ = SIN>
SIZ* TListOffsets(TList<SIZ>* list) {
  return TStackStart<SIZ, SIZ>(&list->offsets);
}

/* Calculates the data_types pointer from the data_offsets and the count. */
template <typename SIZ = SIN, typename DT = DT2>
inline DT* TListTypes(SIZ* data_offsets, SIZ list_size) {
  return reinterpret_cast<DT*>(data_offsets + list_size);
}

/* Returns the type bytes array. */
template <typename SIZ = SIN, typename DT = DT2>
DT* TListTypes(TList<SIZ>* list) {
  return TListTypes<SIZ, DT>(TListOffsets<SIZ>(list), list->offsets.count_max);
}

/* Prints the given AsciiList to the console. */
template <typename Printer, typename SIZ = SIN, typename DT = DT2>
Printer& TListPrint(Printer& o, TList<SIZ>* list) {
  D_ASSERT(list);

  SIZ count = list->offsets.count, count_max = list->offsets.count_max;
  o << Linef("\n\n+---\n| List<SI") << CH1('0' + sizeof(SIZ))
    << "> size:" << list->size_bytes << " size:" << count_max
    << " count:" << count << Linef("\n+---");
  SIZ* data_offsets = TListOffsets<SIZ>(list);
  DT* data_types = TListTypes<SIZ, DT>(data_offsets, count_max);
  for (SIZ index = 0; index < count; ++index) {
    SIZ data_offset = *data_offsets++;
    DT data_type = *data_types++;
    o << "\n| " << Centerf(index, SIW(STRLength(count)) + 2)
      << Centerf(TypeSTR(data_type), 10);
  }
  return o << Linef("\n+---");
}

/* Returns the minimum count to align the data struct to a 64-bit boundary. */
template <typename SIZ = SIN>
SIZ TListCountMaxBoundsLower() {
  return 8 / sizeof(SIZ);
}

/* Initializes a AsciiList from preallocated memory.
count_max must be in multiples of 4. Given there is a fixed size, both the
count_max and size will be downsized to a multiple of 4 automatically. */
template <typename SIZ = SIN, typename DT = DT2>
TList<SIZ>* TListInit(TList<SIZ>* list, SIZ size_bytes, SIZ count_max) {
  D_ASSERT(list);
  D_ARRAY_WIPE(list, size_bytes);
  list->size_bytes = size_bytes;
  list->offsets.count = 0;
  list->offsets.count_max = count_max;
  list->top = TDelta<SIZ>(list, TListTypes<SIZ, DT>(list) + count_max);
  return list;
}

/* Returns the min size of an ASCII List with the given count_max.
The min size is defined as enough memory to store the given count_max with
the largest_expected_type.
*/
template <typename SIZ = SIN, SIW largest_expected_type = sizeof(SIW)>
constexpr SIZ CListSizeMin(SIZ count_max) {
  return sizeof(TList<SIZ>) +
         SIZ(count_max * (largest_expected_type + sizeof(SIZ) + 1));
}

/* Gets origin byte of the of the data. */
template <typename SIZ = SIN, typename DT = DT2>
inline CH1* TListValues(TList<SIZ>* list, SIZ size) {
  return reinterpret_cast<CH1*>(TListTypes<SIZ, DT>(list, size) +
                                list->offsets.count_max);
}
template <typename SIZ = SIN>
inline CH1* TListValues(TList<SIZ>* list) {
  return TListValues<SIZ>(list, list->offsets->size);
}

/* Returns the end byte of the data. */
template <typename SIZ = SIN>
inline CH1* TListDataEnd(TList<SIZ>* list, SIZ size) {
  return reinterpret_cast<CH1*>(list) + list->size_bytes;
}
template <typename SIZ = SIN>
inline CH1* TListDataEnd(TList<SIZ>* list) {
  return TListDataEnd<SIZ>(list, list->offsets->size);
}

/* Gets the first addrss in the Values section where you may be able to write
too. */
template <typename SIZ = SIN>
inline CH1* TListValuesTop(TList<SIZ>* list) {
  return TPtr<CH1>(list, list->top);
}

template <typename SIZ = SIN>
inline CH1* TListValuesEnd(TList<SIZ>* list) {
  return TPtr<CH1>(list, list->size_bytes);
}

/* Returns the max count an array can handle. */
template <typename SIZ = SIN>
SIZ TListSize() {
  enum {
    kMaxSIYes = sizeof(SIZ) == 1
                    ? 120
                    : sizeof(SIZ) == 2
                          ? 8 * 1024
                          : sizeof(SIZ) == 4 ? 512 * 1024 * 1024 : 0,
  };
  return kMaxSIYes;
}

/* Deletes the list contents without wiping the contents. */
template <typename SIZ = SIN>
void TListClear(TList<SIZ>* list) {
  D_ASSERT(list);
  list->count = 0;
}

template <typename T, typename SIZ = SIN, typename DT = DT2>
CH1* TListContains(TList<SIZ>* list, SIZ sizeof_value,
                   SIZ align_mask = sizeof(T) - 1) {
  SIZ size = list->offsets.count_max, count = list->offsets.count;
  if (count >= size) return nullptr;
  SIZ *offsets = TListOffsets<SIZ>(list, size),  //
      *offsets_end = offsets + size;
  DT* types = reinterpret_cast<DT*>(offsets_end);
  if (offsets == offsets_end) return nullptr;
  CH1* previous_begin = 0;

  CH1* origin = TPtr<CH1>(list, *offsets++);
  DT type = *types++;
  origin =
      AlignUpPTR(origin, TypeAlignmentMask(type)) + TSizeOf<SIZ>(origin, type);
  CH1* end = origin;
  SIZ index = 0;
  while (++offsets < offsets_end) {
    end = AlignUpPTR(end, align_mask);
    CH1* origin = TPtr<CH1>(list, *offsets++);
    if (TDelta<>(end, origin)) return index;
    ++index;
    DT type = *types++;
    origin = AlignUpPTR(origin, TypeAlignmentMask(type));
    CH1* end = origin + TSizeOf<SIZ>(origin, type);
    previous_begin = origin;
  }
}

/* Searches the list->offsets for the address.
@return An invalid index if the list doesn't dontain the address or the index
of the object if the list contains the address. */
template <typename SIZ = SIN>
SIZ TListContains(TList<SIZ>* list, void* address) {
  D_ASSERT(list);
  if (TListValues<SIZ>(list)) return false;
  return true;
}
template <typename T, typename SIZ = SIN>
inline SIZ TListInsert(TList<SIZ>* list, T item) {
  CH1* values_begin = TListContains<SIZ>(list, sizeof(T));
}

/* Finds a tuple  the given pointer. */
template <typename SIZ = SIN>
SIZ TListFind(TList<SIZ>* list, void* address) {
  D_ASSERT(list);
  CH1* adr = reinterpret_cast<CH1*>(address);
  SIZ size = list->offsets->size;
  SIZ* data_offsets = TListOffsets<SIZ>(list, size);

  SIZ *offsets = TListOffsets<SIZ>(list), *offset_end = offsets + list->count;
  SIZ offset = TDelta<SIZ>(list, address), index = 0;
  while (offsets < offset_end) {
    if (*data_offsets++ == offset) return index;
    ++index;
  }
  return CInvalidIndex<SIZ>();
}

/* Adds a given POD type-value tuple at the given index and
values_begin.
@return CInvalidIndex<SIZ>() upon failure or the index upon success. */
template <typename T, typename SIZ = SIN, typename DT = DT2>
SIZ TListAdd(TList<SIZ>* list, T item, DT type, SIZ alignment_mask, SIZ index,
             CH1* values_begin, CH1* values_end) {
  D_ASSERT(list);
  SIZ count = list->offsets.count, size = list->offsets.count_max;
  D_ASSERT(count >= 0 && values_begin < values_end);
  D_COUT("\nInserting " << TypeSTR(type) << ':' << item
                        << " into index:" << index << " count: " << count);
  if (index < 0 || index > count || count >= size || !TypeIsSupported(type))
    return CInvalidIndex<SIZ>();

  values_begin = TAlignUpPTR<CH1>(values_begin, alignment_mask);
  if ((values_begin + sizeof(T)) > values_end) return CInvalidIndex<SIZ>();
  *reinterpret_cast<T*>(values_begin) = item;

  SIZ* offsets = TListOffsets<SIZ>(list);
  DT* types = TListTypes<SIZ, DT>(list);

  TStackInsert<SIZ, SIZ>(TStackStart<SIZ, SIZ>(&list->offsets), count, index,
                         TDelta<SIZ>(list, values_begin));
  TStackInsert<DT, SIZ>(types, count, index, type);
  list->offsets.count = count + 1;
  return count;
}

/* Pushes the item onto the List stack. */
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, UI1 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI1, SIZ, DT>(list, item, kUI1, sizeof(UI1) - 1, index,
                                values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, CH1 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI1, SIZ, DT>(list, ToUnsigned(item), kCH1, sizeof(UI1) - 1,
                                index, values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, SI1 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI1, SIZ, DT>(list, ToUnsigned(item), kSI1, sizeof(UI1) - 1,
                                index, values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, UI2 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI2, SIZ, DT>(list, item, kUI2, sizeof(UI2) - 1, index,
                                values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, SI2 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI2, SIZ, DT>(list, ToUnsigned(item), kSI2, sizeof(UI2) - 1,
                                index, values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, CH2 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI2, SIZ>(list, ToUnsigned(item), kCH2, sizeof(UI2) - 1,
                            index, values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, BOL item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI2, SIZ, DT>(list, ToUnsigned(item), kBOL, sizeof(BOL) - 1,
                                index, values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, UI4 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI4, SIZ, DT>(list, item, kUI4, sizeof(UI4) - 1, index,
                                values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, SI4 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI4, SIZ, DT>(list, ToUnsigned(item), kSI4, sizeof(UI4) - 1,
                                index, values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, CH4 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI4, SIZ, DT>(list, ToUnsigned(item), kCH4, sizeof(UI4) - 1,
                                index, values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, FP4 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI4, SIZ, DT>(list, ToUnsigned(item), kFP4, sizeof(UI4) - 1,
                                index, values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, UI8 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI8, SIZ, DT>(list, item, kUI8, kWordLSbMask, index,
                                values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, SI8 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI8, SIZ, DT>(list, ToUnsigned(item), kSI8, kWordLSbMask,
                                index, values_begin, values_end);
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListAdd(TList<SIZ>* list, FP8 item, SIZ index, CH1* values_begin,
                    CH1* values_end) {
  return TListAdd<UI8, SIZ, DT>(list, ToUnsigned(item), kFP8, kWordLSbMask,
                                index, values_begin, values_end);
}

/* Pushes the item onto the List stack. */
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, UI1 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, CH1 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, SI1 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, UI2 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, SI2 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, CH2 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, UI4 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, SI4 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, BOL item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, CH4 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, FP4 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, UI8 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, SI8 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}
template <typename SIZ = SIN, typename DT = DT2>
inline SIZ TListPush(TList<SIZ>* list, FP8 item) {
  return TListAdd<SIZ, DT>(list, item, list->offsets.count_max,
                           TListValuesTop<SIZ>(list),
                           TListValuesEnd<SIZ>(list));
}

template <typename SIZ = SIN>
inline SIZ TSizeOf(void* value, DT2 type) {
  SIW size_bytes = TypeSizeOf(type);
  if (size_bytes != 0) return size_bytes;
}

/* Removes the item at the given address from the list. */
template <typename SIZ = SIN, typename DT = DT2>
void* TListRemove(TList<SIZ>* list, SIZ index) {
  SIZ count = list->offsets.count;
  SIZ* offsets = TListOffsets<SIZ>(list);
  TStackRemove<SIZ, SIZ>(offsets, count, index);
  TStackRemove<DT, SIZ>(TListTypes<SIZ, DT>(list), count, index);
  return offsets + index;
}

/* Removes the item at the given address from the list. */
template <typename SIZ = SIN>
void* TListRemove(TList<SIZ>* list, void* address) {
  D_ASSERT(list);
  return TListRemove<SIZ>(list, TListFind(list, address));
}

/* Removes a type-value to the stop of the list. */
template <typename SIZ = SIN>
inline void* TListPop(TList<SIZ>* list) {
  return TListRemove<SIZ>(list, list->offsets.count - 1);
}

/* Returns the value at the given index.
@return Returns nil if the index is out of the count range. */
template <typename SIZ = SIN>
const void* TListValue(TList<SIZ>* list, SIZ index) {
  D_ASSERT(list);
  if (index < 0 || index >= list->count) return nullptr;
  return reinterpret_cast<CH1*>(list) + TListOffsets<SIZ>(list)[index];
}

/* Creates an Autoject buffer large enough to fit a List with the given. */
template <typename SIZ = SIN, typename SIY = SIG, typename DT>
UIW* TListNew(SIZ size_data, SIZ count_max, SocketFactory socket_factory) {
  SIZ count_max_align_lsb_mask = (sizeof(SIZ) / sizeof(DT)) - 1;
  count_max = AlignUp(count_max, count_max_align_lsb_mask);
  SIZ size_bytes = sizeof(TList<SIZ>) + count_max * (sizeof(SIZ) + sizeof(DT)) +
                   AlignUp(size_data);
  UIW* buffer = socket_factory(nullptr, SIW(size_bytes));
  TList<SIZ>* list = reinterpret_cast<TList<SIZ>*>(buffer);
  return reinterpret_cast<UIW*>(TListInit<SIZ>(list, size_bytes, count_max));
}

/* ASCII List that uses dynamic memory. */
template <typename SIZ = SIN, SIZ kSizeBytes_ = 512, SIZ kCountMax_ = 32,
          typename BUF = TUIB<kSizeBytes_, UI1, SIZ, Nil>, typename DT = DT2>
class AList {
  AArray<UI1, SIZ, BUF> obj_;  //< An Auto-array.
 public:
  static constexpr DT Type() { return CTypeMap<DT>(CTypeSize<SIZ>()); }

  /* Constructs a list with a given count_max with estimated size_bytes. */
  AList(SIZ count_max = kCountMax_)
      : obj_(TListNew<SIZ, SIZ, DT>(kSizeBytes_, count_max,
                                    TRamFactory<Type()>().Init<BUF>()),
             TRamFactory<Type()>().Init<BUF>()) {}

  /* Constructs a List with the given size_bytes and count_max. */
  AList(SIZ count_max, SIZ size_bytes)
      : obj_(TListNew<SIZ, SIZ, DT>(size_bytes, count_max,
                                    TRamFactory<Type()>().Init<BUF>()),
             TRamFactory<Type()>().Init<BUF>()) {}

  inline SIZ Push(SI4 type, const void* value) {
    return TListAdd<SIZ, DT>(This(), type, value);
  }

  /* Inserts the given type-value tuple in the list at the given index. */
  inline SIZ Insert(UI1 type, void* value, SIZ index) {
    return TListAdd<SIZ, DT>(This(), type, value, index);
  }

  /* Maximum count of the item in the List. */
  inline SIZ Size() { return TListSize<SIZ>(); }

  /* Count of the item in the List. */
  inline SIZ Count() { return TListSize<SIZ>(); }

  /* Count of the item in the List. */
  inline SIZ SizeBytes() { return This()->size_bytes; }

  /* Count of the item in the List. */
  inline SIZ SizeWords() { return TSizeWords<SIZ>(SizeBytes()); }

  /* Count of the item in the List. */
  inline SIZ Top() { return This()->top; }

  /* Returns true if this crabs contains only the given address.
  @warning This function assumes that the member you're checking for came from
  Script. If it's you're own code calling this, you are required to ensure the
  value came from a ASCII List.
  @return  True if the data lies in the list's memory array. */
  inline CH1* Contains(void* value) {
    return TListContains<SIZ>(This(), value);
  }

  /* Clears the list by setting the count to 0. */
  void Clear(TList<SIZ>* list) { TListClear<SIZ>(This()); }

  /* Removes the item at the given address from the list. */
  inline BOL Remove(void* address) { return TListRemove<SIZ>(This(), address); }

  /* Removes the item at the given address from the list. */
  inline BOL Remove(SIZ index) { return TListRemove<SIZ>(This(), index); }

  /* Searches for the first empty spot in the list that can fit the item and
  inserts the item to the list at the given index.
  @return An invalid index upon failure or the index of the index upon success.
  */
  SIZ Add(UI1 item, SIZ index) { return TListAdd<UI1>(This(), item); }
  SIZ Add(SI1 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(CH1 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(UI2 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(SI2 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(CH2 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(BOL item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(UI4 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(SI4 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(CH4 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(FP4 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(UI8 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(SI8 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }
  SIZ Add(FP8 item, SIZ index) { return TListAdd<SIZ, DT>(This(), item); }

  /* Pushes the item onto the List stack.
  @return An invalid index upon failure or the index of the item in the list
  upon success. */
  SIZ Push(UI1 item) { return TListAdd<UI1>(This(), item); }
  SIZ Push(SI1 item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(CH1 item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(UI2 item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(SI2 item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(CH2 item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(BOL item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(UI4 item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(SI4 item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(CH4 item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(FP4 item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(UI8 item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(SI8 item) { return TListPush<SIZ>(This(), item); }
  SIZ Push(FP8 item) { return TListPush<SIZ>(This(), item); }

  /* Removes the last item from the list.
  @returns The address of the object just popped off the stack. */
  inline void* Pop() { return TListPop<SIZ>(This()); }

  /* Gets the obj_'s Autoject. */
  inline Autoject AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array. */
  inline AArray<UI1, SIZ>& AJT_ARY() { return obj_; }

  /* Returns the contiguous ASCII List buffer_. */
  inline TList<SIZ>* This() {
    return reinterpret_cast<TList<SIZ>*>(AJT().origin);
  }

  /* Prints This object to the printer. */
  template <typename Printer>
  Printer& PrintTo(Printer& o) {
    return TListPrint<Printer, SIZ>(o, This());
  }
};

}  // namespace _

template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, CH1 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, SI1 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, UI1 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, CH2 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, SI2 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, UI2 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, BOL item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, CH4 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, UI4 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, SI4 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, FP4 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, SI8 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, UI8 item) {
  list.Add(item);
}
template <typename SIZ>
inline _::TList<SIZ>& operator<<(_::TList<SIZ>& list, FP8 item) {
  list.Add(item);
}

#endif
#endif
