/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/list.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_LIST
#ifndef INCLUDED_SCRIPTTLIST
#define INCLUDED_SCRIPTTLIST

#include "t_set.h"
#include "t_socket.h"
#include "t_stack.h"

#if SEAM == SEAM_SCRIPT2_LIST
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* An ASCII List header.
Like most ASCII AArray Types, the size may only be 16-bit, 32-bit, or
64-bit. The unsigned value must be twice the width of the signed value.

@code
+--------------------------+ -----------
|_______ Buffer            |   ^     ^
|_______ ...               |   |     |
|_______ Data N            |  Data   |
|_______ ...               |   |     |
|_______ Data 0            |   v     |
+--------------------------+ -----   |
|_______ count_max         |   ^     |
|_______ ...               |   |     |
|_______ Data Offset N     |   |     |
|_______ ...               |   |    SIZ
|        Data Offset 1     |   |     |
+--------------------------+ Header  |
|_______ count_max         |   |     |
|_______ ...               |   |     |
|_______ Type N            |   |     |
|_______ ...               |   |     |
|        Type 1            |   |     |   ^ Up in addresses
+--------------------------+   |     |   |
|       TList Header       |   v     v   ^
+--------------------------+ ----------- ^ 0xN
@endcode
*/
template <typename SIZ = UI4, typename Index = SI2>
struct TList {
  SIZ size;
  Index count_max, count;
};

/* Returns the minimum count to align the data struct to a 64-bit boundary. */
template <typename SIZ = UI4, typename Index = SI2>
Index ListCountMaxBoundsLower() {
  return 8 / sizeof(Index);
}

/* Returns the min size of an ASCII List with the given count_max.
The min size is defined as enough memory to store the given count_max with
the largest_expected_type.
*/
template <typename SIZ = UI4, typename Index = SI2,
          SIW largest_expected_type = sizeof(SIW)>
constexpr SIZ ListSizeMin(Index count_max) {
  return (SIZ)sizeof(TList<SIZ, Index>) +
         (SIZ)(count_max * (largest_expected_type + sizeof(SIZ) + 1));
  ///<< 2 to * 4.
}

/* Deletes the list contents by overwriting it with zeros. */
template <typename SIZ = UI4, typename Index = SI2>
void ListWipe(TList<SIZ, Index>* list) {
  A_ASSERT(list)
  list->count = 0;
  SIZ size = list->size - sizeof(TList<SIZ, Index>);
  memset(reinterpret_cast<CH1*>(list) + sizeof(TList<SIZ, Index>), 0, size);
}

/* Initializes a AsciiList from preallocated memory.
count_max must be in multiples of 4. Given there is a fixed size, both the
count_max and size will be downsized to a multiple of 4 automatically. */
template <typename SIZ = UI4, typename Index = SI2>
TList<SIZ, Index>* ListInit(UIW* socket, SIZ size, Index count_max) {
  if (!socket)  // This may be nullptr if ListNew<SIZ,Index> (Index, SIZ)
                // failed.
    return nullptr;
  D_PRINTF("\n  Initializing List with size_bytes:%u and count_max:%i",
           (UIN)size, (SI4)count_max)
  Index count_max_bounds_lower = ListCountMaxBoundsLower<SIZ, Index>();
  if (count_max < count_max_bounds_lower) {
    D_PRINTF("\n count_max == 0 and is now %i", (SI4)count_max_bounds_lower)
    count_max = count_max_bounds_lower;
  } else {
    D_PRINTF("\ncount_max was %i ", (SI4)count_max)
    count_max = AlignUp<Index>(count_max);
    D_PRINTF("\n and now is %i.", (SI4)count_max)
  }

  // count_max = AlignUp<Index> (count_max);
  // D_PRINTF ("\n  Aligning up to count_max:%i", (SI4)count_max)

  TList<SIZ, Index>* list = reinterpret_cast<TList<SIZ, Index>*>(socket);
  list->size = size;
  list->count = 0;
  list->count_max = count_max;
  // WIPE
  ListWipe<SIZ, Index>(list);
  return list;
}

/* Creates a list from dynamic memory. */
template <typename SIZ = UI4, typename Index = SI2>
UIW* ListNew(Index count_max, SIZ size) {
  count_max = TAlignUpUnsigned<UI8, SIZ>(count_max);
  if (size < ListSizeMin<SIZ, Index>(count_max)) return nullptr;
  UIW* socket = new UIW[size >> kWordBitCount];

  TList<SIZ, Index>* list = reinterpret_cast<TList<SIZ, Index>*>(socket);
  list->size = size;
  list->count = 0;
  list->count_max = count_max;
  // WIPE
  ListWipe<SIZ, Index>(list);
  return socket;
}

/* Creates a list from dynamic memory. */
template <typename SIZ = UI4, typename Index = SI2,
          SIW largest_expected_type = sizeof(SIW)>
inline UIW* ListNew(Index count_max) {
  count_max = AlignUp<Index>(count_max);
  SIZ size = ListSizeMin<SIZ, Index, largest_expected_type>(count_max);
  UIW* socket = new UIW[size >> kWordBitCount];

  TList<SIZ, Index>* list = reinterpret_cast<TList<SIZ, Index>*>(socket);
  list->size = size;
  list->count = 0;
  list->count_max = count_max;
  // WIPE
  ListWipe<SIZ, Index>(list);
  return socket;
}

/* Returns the type bytes array. */
template <typename SIZ = UI4, typename Index = SI2>
SI4* ListTypes(TList<SIZ, Index>* list) {
  A_ASSERT(list)
  return reinterpret_cast<SI4*>(list) + sizeof(CList<SIZ, Index>);
}

/* Gets a pointer to the begging of the data socket. */
template <typename SIZ = UI4, typename Index = SI2>
inline CH1* ListDataBegin(TList<SIZ, Index>* list) {
  A_ASSERT(list)
  return reinterpret_cast<CH1*>(list) + list->count_max * (sizeof(Index) + 1);
}

/* Gets the base element 0 of the list's offset array. */
template <typename SIZ = UI4, typename Index = SI2>
inline SIZ* ListOffsets(TList<SIZ, Index>* list) {
  UIW ptr =
      reinterpret_cast<UIW>(list) + sizeof(TList<SIZ, Index>) + list->count_max;
  return reinterpret_cast<SIZ*>(ptr);
}

/* Returns the last UI1 in the data array. */
template <typename SIZ = UI4, typename Index = SI2>
inline CH1* ListDataEnd(TList<SIZ, Index>* list) {
  A_ASSERT(list)
  return reinterpret_cast<CH1*>(list) + list->size - 1;
}

/* Returns the last UI1 in the data array. */
template <typename SIZ = UI4, typename Index = SI2>
inline CH1* ListDataEnd(TList<SIZ, Index>* list, Index index) {
  A_ASSERT(list)
  if (index < 0 || index >= index->count) return nullptr;
  return reinterpret_cast<CH1*>(list) + list->size - 1;
}

/* Returns a pointer to the begging of the data socket. */
template <typename SIZ = UI4, typename Index = SI2>
Socket ListDataVector(TList<SIZ, Index>* list) {
  return Socket(ListDataBegin<SIZ, Index>(list), ListDataEnd<SIZ, Index>(list));
}

/* Returns the last UI1 in the data array. */
template <typename SIZ = UI4, typename Index = SI2>
inline CH1* ListDataStop(TList<SIZ, Index>* list, Index index = -1) {
  A_ASSERT(list)
  Index count = list->count;
  if (count == 0) {
    if (index != -1) return nullptr;
    return ListDataBegin<SIZ, Index>(list);
  }
  SI4 type = ListTypes<SIZ, Index>(list)[index];
  SIZ offset = ListOffsets<SIZ, Index>(list)[index];
  D_PRINTF("!offset %u", offset)
  CH1* pointer = reinterpret_cast<CH1*>(list) + offset;
  return ObjEnd<SIZ>(pointer, type);
}

template <typename SIZ = UI4, typename Index = SI2>
void ListDataSpaceBelow(TList<SIZ, Index>* list, Index index,
                        Socket& free_space) {
  A_ASSERT(list)
  CH1* data_stop;
  if (index == 0) {
    data_stop = ListDataBegin<SIZ, Index>(list);
    free_space.begin = free_space.stop = data_stop;
    return;
  }
  A_ASSERT(index >= 0 && index <= list->count)
  if (index == list->count) {
    free_space.begin = ListDataStop<SIZ, Index>(list);
    free_space.stop = ListDataEnd<SIZ, Index>(list);
    return;
  }
  data_stop = ListDataStop<SIZ, Index>(list, index);
  SIZ* offsets = ListOffsets<SIZ, Index>(list);
  SIZ offset_low = offsets[index], offset_high = offsets[index + 1];
}

/* Insets the given type-value tuple.
    @return -1 upon failure or the index upon success. */
template <typename SIZ = UI4, typename Index = SI2>
Index ListInsert(TList<SIZ, Index>* list, SI4 type, const void* value,
                 Index index) {
  A_ASSERT(list)
  A_ASSERT(value)
  D_PRINTF("\nInserting type:")
  D_COUT_TYPE(type, value)
  D_PRINTF(" into index:%i", index)

  Index count = list->count, count_max = list->count_max;
  if (count >= count_max || index > count || !TypeIsSupported(type) ||
      index < 0) {
    D_PRINTF("\nError inserting type:%s into index %i", STRType(type),
             (SI4)index);
    return -1;
  }
  D_PRINTF(" when count is %i", (SI4)count)

  SI4* types = ListTypes<SIZ, Index>(list);

  // 1. Check for stack push operation.
  if (index == count) {
    D_PRINTF("\nPushing element...")
    // Push type onto the top of the type stack.
    types[index] = type;
    //  Push the offset onto the top of the offset stack.
    CH1* data_stop = ListDataStop<SIZ, Index>(list, count - 1);
    D_PRINTF("\n  Aligning data_stop from %i to ", (SI4)SIZ(list, data_stop))
    data_stop = TypeAlignUpPointer<CH1>(data_stop, type);
    D_PRINTF("%i", (SI4)SIZ(list, data_stop))
    SIZ stop_offset = (SIZ)(data_stop - reinterpret_cast<CH1*>(list));
    ListOffsets<SIZ, Index>(list)[index] = stop_offset;
    // Write the value to the top of the value stack.
    D_PRINTF(" leaving %i bytes.",
             (SI4)(ListDataEnd<SIZ, Index>(list) - data_stop))
    if (!Write(data_stop, ListDataEnd<SIZ, Index>(list), type, value))
      return -2;
    list->count = count + 1;
    return index;
  }

  // 2. Shift up the types.
  TStackInsert<SI4, Index>(types, count, type, index);

  // 3. Calculate the offset to insert at.
  CH1* aligned_begin = ListDataStop<SIZ, Index>(list, index);
  D_PRINTF("\nListDataStop<SIZ, Index> (list) starts as %p then is aligned to ",
           aligned_begin)
  aligned_begin = TypeAlignUpPointer<CH1>(aligned_begin, type);
  D_PRINTF("%p", aligned_begin)

  // 4. Insert the offset.
  D_PRINTF("\nInserting into ")
  TStackInsert<SIZ, Index>(ListOffsets<SIZ, Index>(list), count, type, index);

  SIZ space_needed = ObjSize<SIZ>(value, type);

  // 5. Check if there is enough room to insert the value without shifting up
  // any data.
  Socket free_space;
  ListDataSpaceBelow<SIZ, Index>(list, index, free_space);
  if (Write(free_space.begin, free_space.stop, type, value)) return index;

  // 6. Shift up the data enough to fit the new value.

  // 5. Write the value to the data socket.
  if (!Write(aligned_begin, ListDataEnd<SIZ, Index>(list), type, value))
    return -1;
  list->count = ++count;
  return count;
}

/* Adds a type-value to the stop of the list. */
template <typename SIZ = UI4, typename Index = SI2>
inline Index ListPush(TList<SIZ, Index>* list, SI4 type, const void* value) {
  return ListInsert<SIZ, Index>(list, type, value, list->count);
}

/* Removes a type-value to the stop of the list. */
template <typename SIZ = UI4, typename Index = SI2>
inline Index ListPop(TList<SIZ, Index>* list) {
  return ListRemove<SIZ, Index>(list, list->count - 1);
}

/* Returns the max count an array can handle. */
template <typename SIZ = UI4, typename Index = SI2>
Index ListCountMax() {
  enum {
    kMaxIndexes = sizeof(Index) == 1
                      ? 120
                      : sizeof(Index) == 2
                            ? 8 * 1024
                            : sizeof(Index) == 4 ? 512 * 1024 * 1024 : 0,
  };
  return kMaxIndexes;
}

/* Deletes the list contents without wiping the contents. */
template <typename SIZ = UI4, typename Index = SI2>
void ListClear(TList<SIZ, Index>* list) {
  A_ASSERT(list)
  list->count = 0;
}

/* Checks if this crabs contains only the given address.
@return  True if the data lies in the list's memory socket.

@warning This function assumes that the member you're checking for came
from Script. If it's you're own code calling this, you are
required to ensure the value came from a ASCII List. */
template <typename SIZ = UI4, typename Index = SI2>
BOL ListContains(TList<SIZ, Index>* list, void* address) {
  A_ASSERT(list)
  if (reinterpret_cast<CH1*>(address) < reinterpret_cast<CH1*>(list))
    return false;
  if (reinterpret_cast<CH1*>(address) > ListEndByte()) return false;
  return true;
}

/* Removes the item at the given address from the list. */
template <typename SIZ = UI4, typename Index = SI2>
Index ListRemove(TList<SIZ, Index>* list, Index index) {
  Index count = list->count;
  TStackRemove<SIZ, Index>(ListOffsets<SIZ, Index>(list), count, index);
  return TStackRemove<SI4, Index>(ListTypes<SIZ, Index>(list), count, index);
}

/* Finds a tuple that contains the given pointer. */
template <typename SIZ = UI4, typename Index = SI2>
Index ListFind(TList<SIZ, Index>* list, void* adress) {
  A_ASSERT(list)
  SIZ *offsets = ListOffsets<SIZ, Index>(list),
      *offset_end = offsets + list->count;
  while (offsets < offset_end) {
    CH1 *begin = reinterpret_cast<CH1*>(list) + *offsets++,
        *stop = ListDataStop<SIZ, Index>(list, index);
    if (reinterpret_cast<CH1*>(address) >= begin &&
        reinterpret_cast<CH1*>(address) <= stop)
      return true;
  }
  return -1;
}

/* Removes the item at the given address from the list. */
template <typename SIZ = UI4, typename Index = SI2>
BOL ListRemove(TList<SIZ, Index>* list, void* adress) {
  return ListRemove<SIZ, Index>(list, ListFind(list, address));
}

/* Returns the value at the given index.
    @return Returns nil if the index is out of the count range. */
template <typename SIZ = UI4, typename Index = SI2>
const void* ListValue(TList<SIZ, Index>* list, Index index) {
  A_ASSERT(list)
  if (index < 0 || index >= list->count) return nullptr;
  return reinterpret_cast<CH1*>(list) + ListOffsets<SIZ, Index>(list)[index];
}

/* Prints the given AsciiList to the console. */
template <typename Printer, typename SIZ = UI4, typename Index = SI2>
Printer& PrintList(Printer& o, TList<SIZ, Index>* list) {
  A_ASSERT(list)

  Index count = list->count;
  o << "\n\nList: size:" << list->size << " count:" << count
    << " count_max:" << list->count_max;
  for (Index index = 0; index < count; ++index) {
    o << kLF << index << ".) "
      << AValue(ListTypes<SIZ, Index>(list)[index],
                ListValue<SIZ, Index>(list, index));
  }
  return o;
}

/* ASCII List that uses dynamic memory. */
template <typename SIZ = UI4, typename Index = SI2>
class AList {
 public:
  /* Constructs a list with a given count_max with estimated size_bytes. */
  AList(Index count_max = 0) : begin(ListNew<SIZ, Index>(count_max)) {
    // Nothing to do here! (:-)|==<,
  }

  /* Constructs a List with the given size_bytes and count_max.
  size_bytes and count_max both get rounded down to a multiple of 64
  before allocating the socket. If the count_max is not enough for the
  socket then the size_bytes will be increased to the minimum size to
  make a valid ASCII List. */
  AList(Index count_max, SIZ size)
      : begin(ListNew<SIZ, Index>(count_max, size)) {
    // Nothing to do here! (:-)+==<
  }

  /* Deletes the dynamically allocated socket. */
  ~AList() { delete[] begin; }

  inline Index Push(SI4 type, const void* value) {
    return ListPush<SIZ, Index>(AArray(), type, value);
  }

  /* Inserts the given type-value tuple in the list at the given index. */
  inline Index Insert(UI1 type, void* value, Index index) {
    return ListInsert<SIZ, Index>(AArray(), type, value, index);
  }

  /* Returns the maximum count of the give list in the current memory
      profile. */
  inline Index CountMax() { return ListCountMax<SIZ, Index>(); }

  /* Clears the list without overwriting the contents. */
  void Clear(TList<SIZ, Index>* list) { ListClear<SIZ, Index>(AArray()); }

  /* Deletes the list contents by overwriting it with zeros. */
  inline void Wipe() { ListWipe<SIZ, Index>(AArray()); }

  /* Returns true if this crabs contains only the given address.
  @warning This function assumes that the member you're checking for came from
  Script. If it's you're own code calling this, you are required to ensure the
  value came from a ASCII List.
  @return  True if the data lies in the list's memory socket. */
  inline BOL Contains(void* value) {
    return ListContains<SIZ, Index>(AArray(), value);
  }

  /* Removes the item at the given address from the list. */
  inline BOL Remove(void* adress) {
    return ListRemove<SIZ, Index>(AArray(), adress);
  }

  /* Removes the item at the given address from the list. */
  inline BOL Remove(Index index) {
    return ListRemove<SIZ, Index>(AArray(), index);
  }

  /* Removes the last item from the list. */
  inline Index Pop() { return ListPop<SIZ, Index>(AArray()); }

  /* Prints the given AsciiList to the console. */
  inline UTF1& Print(UTF1& printer) {
    return PrintList<SIZ, Index>(printer, AArray());
  }

  /* Returns the contiguous ASCII List buffer_. */
  inline TList<SIZ, Index>* AArray() {
    return reinterpret_cast<TList<SIZ, Index>*>(begin);
  }

  template <typename Printer>
  Printer& PrinterTo(Printer& o) {
    return PrintList<Printer>(;
  }

  void CPrint() { return PrintTo<COut>(COut()); }

 private:
  AArray obj_;  //< An Auto-array.
};

}  // namespace _

#endif
#endif
