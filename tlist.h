/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /list.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#if SEAM >= _0_0_0__09
#ifndef INCLUDED_SCRIPTTLIST
#define INCLUDED_SCRIPTTLIST

#include "tset.h"
#include "tsocket.h"
#include "tstack.h"

#if SEAM == _0_0_0__09
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

/* An ASCII List header.
Like most ASCII CObject Types, the size may only be 16-bit, 32-bit, or
64-bit. The unsigned value must be twice the width of the signed value.

@code
+==========================+ -----------
|_______ Buffer            |   ^     ^
|_______ ...               |   |     |
|_______ Data N            |  Data   |
|_______ ...               |   |     |
|_______ Data 0            |   v     |
|==========================| -----   |
|_______ count_max         |   ^     |
|_______ ...               |   |     |
|_______ Data Offset N     |   |     |
|_______ ...               |   |    Size
|        Data Offset 1     |   |     |
|==========================| Header  |
|_______ count_max         |   |     |
|_______ ...               |   |     |
|_______ Type UI1 N        |   |     |
|_______ ...               |   |     |
|        Type UI1 1        |   |     |   ^ Up in addresses
|==========================|   |     |   |
|       TList Header       |   v     v   ^
+==========================+ ----------- ^ 0xN
@endcode
*/
template <typename Size = UI4, typename Index = SI2>
struct CList {
  Size size;
  Index count_max, count;
};

/* Returns the minimum count to align the data struct to a 64-bit boundary. */
template <typename Size = UI4, typename Index = SI2>
Index ListCountMaxBoundsLower() {
  return 8 / sizeof(Index);
}

/* Returns the min size of an ASCII List with the given count_max.
The min size is defined as enough memory to store the given count_max with
the largest_expected_type.
*/
template <typename Size = UI4, typename Index = SI2,
          size_t largest_expected_type = sizeof(SIW)>
constexpr Size ListSizeMin(Index count_max) {
  return (Size)sizeof(CList<Size, Index>) +
         (Size)(count_max * (largest_expected_type + sizeof(Size) + 1));
  // << 2 to * 4.
}

/* Deletes the list contents by overwriting it with zeros. */
template <typename Size = UI4, typename Index = SI2>
void ListWipe(CList<Size, Index>* list) {
  ASSERT(list)
  list->count = 0;
  Size size = list->size - sizeof(CList<Size, Index>);
  memset(reinterpret_cast<CH1*>(list) + sizeof(CList<Size, Index>), 0, size);
}

/* Initializes a AsciiList from preallocated memory.
count_max must be in multiples of 4. Given there is a fixed size, both the
count_max and size will be downsized to a multiple of 4 automatically. */
template <typename Size = UI4, typename Index = SI2>
CList<Size, Index>* ListInit(UIW* socket, Size size, Index count_max) {
  if (!socket)  // This may be nullptr if ListNew<Size,Index> (Index, Size)
                // failed.
    return nullptr;
  PRINTF("\n  Initializing List with size_bytes:%u and count_max:%i",
         (uint)size, (int)count_max)
  Index count_max_bounds_lower = ListCountMaxBoundsLower<Size, Index>();
  if (count_max < count_max_bounds_lower) {
    PRINTF("\n count_max == 0 and is now %i", (int)count_max_bounds_lower)
    count_max = count_max_bounds_lower;
  } else {
    PRINTF("\ncount_max was %i ", (int)count_max)
    count_max = AlignUp<Index>(count_max);
    PRINTF("\n and now is %i.", (int)count_max)
  }

  // count_max = AlignUp<Index> (count_max);
  // PRINTF ("\n  Aligning up to count_max:%i", (int)count_max)

  CList<Size, Index>* list = reinterpret_cast<CList<Size, Index>*>(socket);
  list->size = size;
  list->count = 0;
  list->count_max = count_max;
  // WIPE
  ListWipe<Size, Index>(list);
  return list;
}

/* Creates a list from dynamic memory. */
template <typename Size = UI4, typename Index = SI2>
UIW* ListNew(Index count_max, Size size) {
  count_max = TAlignUpUnsigned<UI8, Size>(count_max);
  if (size < ListSizeMin<Size, Index>(count_max)) return nullptr;
  UIW* socket = new UIW[size >> kWordBitCount];

  CList<Size, Index>* list = reinterpret_cast<CList<Size, Index>*>(socket);
  list->size = size;
  list->count = 0;
  list->count_max = count_max;
  // WIPE
  ListWipe<Size, Index>(list);
  return socket;
}

/* Creates a list from dynamic memory. */
template <typename Size = UI4, typename Index = SI2,
          size_t largest_expected_type = sizeof(SIW)>
inline UIW* ListNew(Index count_max) {
  count_max = AlignUp<Index>(count_max);
  Size size = ListSizeMin<Size, Index, largest_expected_type>(count_max);
  UIW* socket = new UIW[size >> kWordBitCount];

  CList<Size, Index>* list = reinterpret_cast<CList<Size, Index>*>(socket);
  list->size = size;
  list->count = 0;
  list->count_max = count_max;
  // WIPE
  ListWipe<Size, Index>(list);
  return socket;
}

/* Returns the type bytes array. */
template <typename Size = UI4, typename Index = SI2>
SIN* ListTypes(CList<Size, Index>* list) {
  ASSERT(list)
  return reinterpret_cast<SIN*>(list) + sizeof(CList<Size, Index>);
}

/* Gets a pointer to the begging of the data socket. */
template <typename Size = UI4, typename Index = SI2>
inline CH1* ListDataBegin(CList<Size, Index>* list) {
  ASSERT(list)
  return reinterpret_cast<CH1*>(list) + list->count_max * (sizeof(Index) + 1);
}

/* Gets the base element 0 of the list's offset array. */
template <typename Size = UI4, typename Index = SI2>
inline Size* ListOffsets(CList<Size, Index>* list) {
  UIW ptr = reinterpret_cast<UIW>(list) + sizeof(CList<Size, Index>) +
            list->count_max;
  return reinterpret_cast<Size*>(ptr);
}

/* Returns the last UI1 in the data array. */
template <typename Size = UI4, typename Index = SI2>
inline CH1* ListDataEnd(CList<Size, Index>* list) {
  ASSERT(list)
  return reinterpret_cast<CH1*>(list) + list->size - 1;
}

/* Returns the last UI1 in the data array. */
template <typename Size = UI4, typename Index = SI2>
inline CH1* ListDataEnd(CList<Size, Index>* list, Index index) {
  ASSERT(list)
  if (index < 0 || index >= index->count) return nullptr;
  return reinterpret_cast<CH1*>(list) + list->size - 1;
}

/* Returns a pointer to the begging of the data socket. */
template <typename Size = UI4, typename Index = SI2>
Socket ListDataVector(CList<Size, Index>* list) {
  return Socket(ListDataBegin<Size, Index>(list),
                ListDataEnd<Size, Index>(list));
}

/* Returns the last UI1 in the data array. */
template <typename Size = UI4, typename Index = SI2>
inline CH1* ListDataStop(CList<Size, Index>* list, Index index = -1) {
  ASSERT(list)
  Index count = list->count;
  if (count == 0) {
    if (index != -1) return nullptr;
    return ListDataBegin<Size, Index>(list);
  }
  SIN type = ListTypes<Size, Index>(list)[index];
  Size offset = ListOffsets<Size, Index>(list)[index];
  PRINTF("!offset %u", offset)
  CH1* pointer = reinterpret_cast<CH1*>(list) + offset;
  return ObjEnd<Size>(pointer, type);
}

template <typename Size = UI4, typename Index = SI2>
void ListDataSpaceBelow(CList<Size, Index>* list, Index index,
                        Socket& free_space) {
  ASSERT(list)
  CH1* data_stop;
  if (index == 0) {
    data_stop = ListDataBegin<Size, Index>(list);
    free_space.begin = free_space.stop = data_stop;
    return;
  }
  ASSERT(index >= 0 && index <= list->count)
  if (index == list->count) {
    free_space.begin = ListDataStop<Size, Index>(list);
    free_space.stop = ListDataEnd<Size, Index>(list);
    return;
  }
  data_stop = ListDataStop<Size, Index>(list, index);
  Size* offsets = ListOffsets<Size, Index>(list);
  Size offset_low = offsets[index], offset_high = offsets[index + 1];
}

/* Insets the given type-value tuple.
    @return -1 upon failure or the index upon success. */
template <typename Size = UI4, typename Index = SI2>
Index ListInsert(CList<Size, Index>* list, SIN type, const void* value,
                 Index index) {
  ASSERT(list)
  ASSERT(value)
  PRINTF("\nInserting type:")
  PRINT_TYPE(type, value)
  PRINTF(" into index:%i", index)

  Index count = list->count, count_max = list->count_max;
  if (count >= count_max || index > count || !TypeIsValid(type) || index < 0) {
    PRINTF("\nError inserting type:%s into index %i", TypeString(type),
           (int)index);
    return -1;
  }
  PRINTF(" when count is %i", (int)count)

  SIN* types = ListTypes<Size, Index>(list);

  // 1. Check for stack push operation.
  if (index == count) {
    PRINTF("\nPushing element...")
    // Push type onto the top of the type stack.
    types[index] = type;
    //  Push the offset onto the top of the offset stack.
    CH1* data_stop = ListDataStop<Size, Index>(list, count - 1);
    PRINTF("\n  Aligning data_stop from %i to ", (int)Size(list, data_stop))
    data_stop = TypeAlignUpPointer<CH1>(data_stop, type);
    PRINTF("%i", (int)Size(list, data_stop))
    Size stop_offset = (Size)(data_stop - reinterpret_cast<CH1*>(list));
    ListOffsets<Size, Index>(list)[index] = stop_offset;
    // Write the value to the top of the value stack.
    PRINTF(" leaving %i bytes.",
           (int)(ListDataEnd<Size, Index>(list) - data_stop))
    if (!Write(data_stop, ListDataEnd<Size, Index>(list), type, value))
      return -2;
    list->count = count + 1;
    return index;
  }

  // 2. Shift up the types.
  StackInsert<SIN, Index>(types, count, type, index);

  // 3. Calculate the offset to insert at.
  CH1* aligned_begin = ListDataStop<Size, Index>(list, index);
  PRINTF("\nListDataStop<Size, Index> (list) starts as %p then is aligned to ",
         aligned_begin)
  aligned_begin = TypeAlignUpPointer<CH1>(aligned_begin, type);
  PRINTF("%p", aligned_begin)

  // 4. Insert the offset.
  PRINTF("\nInserting into ")
  StackInsert<Size, Index>(ListOffsets<Size, Index>(list), count, type, index);

  Size space_needed = ObjSize<Size>(value, type);

  // 5. Check if there is enough room to insert the value without shifting up
  // any data.
  Socket free_space;
  ListDataSpaceBelow<Size, Index>(list, index, free_space);
  if (Write(free_space.begin, free_space.stop, type, value)) return index;

  // 6. Shift up the data enough to fit the new value.

  // 5. Write the value to the data socket.
  if (!Write(aligned_begin, ListDataEnd<Size, Index>(list), type, value))
    return -1;
  list->count = ++count;
  return count;
}

/* Adds a type-value to the stop of the list. */
template <typename Size = UI4, typename Index = SI2>
inline Index ListPush(CList<Size, Index>* list, SIN type, const void* value) {
  return ListInsert<Size, Index>(list, type, value, list->count);
}

/* Removes a type-value to the stop of the list. */
template <typename Size = UI4, typename Index = SI2>
inline Index ListPop(CList<Size, Index>* list) {
  return ListRemove<Size, Index>(list, list->count - 1);
}

/* Returns the max count an array can handle. */
template <typename Size = UI4, typename Index = SI2>
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
template <typename Size = UI4, typename Index = SI2>
void ListClear(CList<Size, Index>* list) {
  ASSERT(list)
  list->count = 0;
}

/* Checks if this crabs contains only the given address.
@return  True if the data lies in the list's memory socket.

@warning This function assumes that the member you're checking for came
from Script. If it's you're own code calling this, you are
required to ensure the value came from a ASCII List. */
template <typename Size = UI4, typename Index = SI2>
BOL ListContains(CList<Size, Index>* list, void* address) {
  ASSERT(list)
  if (reinterpret_cast<CH1*>(address) < reinterpret_cast<CH1*>(list))
    return false;
  if (reinterpret_cast<CH1*>(address) > ListEndByte()) return false;
  return true;
}

/* Removes the item at the given address from the list. */
template <typename Size = UI4, typename Index = SI2>
Index ListRemove(CList<Size, Index>* list, Index index) {
  Index count = list->count;
  TStackRemove<Size, Index>(ListOffsets<Size, Index>(list), count, index);
  return TStackRemove<SIN, Index>(ListTypes<Size, Index>(list), count, index);
}

/* Finds a tuple that contains the given pointer. */
template <typename Size = UI4, typename Index = SI2>
Index ListFind(CList<Size, Index>* list, void* adress) {
  ASSERT(list)
  Size *offsets = ListOffsets<Size, Index>(list),
       *offset_end = offsets + list->count;
  while (offsets < offset_end) {
    CH1 *begin = reinterpret_cast<CH1*>(list) + *offsets++,
         *stop = ListDataStop<Size, Index>(list, index);
    if (reinterpret_cast<CH1*>(address) >= begin &&
        reinterpret_cast<CH1*>(address) <= stop)
      return true;
  }
  return -1;
}

/* Removes the item at the given address from the list. */
template <typename Size = UI4, typename Index = SI2>
BOL ListRemove(CList<Size, Index>* list, void* adress) {
  return ListRemove<Size, Index>(list, ListFind(list, address));
}

/* Returns the value at the given index.
    @return Returns nil if the index is out of the count range. */
template <typename Size = UI4, typename Index = SI2>
const void* ListValue(CList<Size, Index>* list, Index index) {
  ASSERT(list)
  if (index < 0 || index >= list->count) return nullptr;
  return reinterpret_cast<CH1*>(list) + ListOffsets<Size, Index>(list)[index];
}

/* Prints the given AsciiList to the console. */
template <typename Size = UI4, typename Index = SI2>
UTF1& PrintList(UTF1& printer, CList<Size, Index>* list) {
  ASSERT(list)

  Index count = list->count;
  printer << "\n\nList: size:" << list->size << " count:" << count
          << " count_max:" << list->count_max;
  for (Index index = 0; index < count; ++index) {
    printer << '\n'
            << index << ".) "
            << TypeValue(ListTypes<Size, Index>(list)[index],
                         ListValue<Size, Index>(list, index));
  }
  return printer;
}

/* ASCII List that uses dynamic memory. */
template <typename Size = UI4, typename Index = SI2>
class List {
 public:
  /* Constructs a list with a given count_max with estimated size_bytes. */
  List(Index count_max = 0) : begin(ListNew<Size, Index>(count_max)) {
    // Nothing to do here! (:-)|==<,
  }

  /* Constructs a List with the given size_bytes and count_max.
  size_bytes and count_max both get rounded down to a multiple of 64
  before allocating the socket. If the count_max is not enough for the
  socket then the size_bytes will be increased to the minimum size to
  make a valid ASCII List. */
  List(Index count_max, Size size)
      : begin(ListNew<Size, Index>(count_max, size)) {
    // Nothing to do here! (:-)+==<
  }

  /* Deletes the dynamically allocated socket. */
  ~List() { delete[] begin; }

  inline Index Push(SIN type, const void* value) {
    return ListPush<Size, Index>(CObject(), type, value);
  }

  /* Inserts the given type-value tuple in the list at the given index. */
  inline Index Insert(UI1 type, void* value, Index index) {
    return ListInsert<Size, Index>(CObject(), type, value, index);
  }

  /* Returns the maximum count of the give list in the current memory
      profile. */
  inline Index CountMax() { return ListCountMax<Size, Index>(); }

  /* Clears the list without overwriting the contents. */
  void Clear(CList<Size, Index>* list) { ListClear<Size, Index>(CObject()); }

  /* Deletes the list contents by overwriting it with zeros. */
  inline void Wipe() { ListWipe<Size, Index>(CObject()); }

  /* Returns true if this crabs contains only the given address.
      @warning This function assumes that the member you're checking for came
               from Script. If it's you're own code calling this, you
               are required to ensure the value came from a ASCII List.
      @return  True if the data lies in the list's memory socket. */
  inline BOL Contains(void* value) {
    return ListContains<Size, Index>(CObject(), value);
  }

  /* Removes the item at the given address from the list. */
  inline BOL Remove(void* adress) {
    return ListRemove<Size, Index>(CObject(), adress);
  }

  /* Removes the item at the given address from the list. */
  inline BOL Remove(Index index) {
    return ListRemove<Size, Index>(CObject(), index);
  }

  /* Removes the last item from the list. */
  inline Index Pop() { return ListPop<Size, Index>(CObject()); }

  /* Prints the given AsciiList to the console. */
  inline UTF1& Print(UTF1& printer) {
    return PrintList<Size, Index>(printer, CObject());
  }

  /* Returns the contiguous ASCII List buffer_. */
  inline CList<Size, Index>* CObject() {
    return reinterpret_cast<CList<Size, Index>*>(begin);
  }

 private:
  CObject obj_;  //< Dynamically allocated word-aligned socket.
};

}  // namespace _

/* Overloaded operator<< prints the list. */
template <typename Size = UI4, typename Index = SI2>
inline _::UTF1& operator<<(_::UTF1& printer, _::List<Size, Index>& list) {
  return list.Print(printer);
}

/* Overloaded operator<< prints the list. */
template <typename Size = UI4, typename Index = SI2>
inline _::UTF1& operator<<(_::UTF1& printer, _::CList<Size, Index>* list) {
  return _::PrintList<Size, Index>(printer, list);
}

#endif  //< INCLUDED_SCRIPTTLIST
#endif  //< #if SEAM >= _0_0_0__09
