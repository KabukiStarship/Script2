/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tstack.h
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
#if SEAM >= _0_0_0__05
#ifndef INCLUDED_SCRIPT_TSTACK
#define INCLUDED_SCRIPT_TSTACK 1

#include "csocket.h"
#include "tobject.h"
#include "tutf.h"

#if SEAM == _0_0_0__05
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

/* @ingroup ASCIIStack
Stack is an ASCII Data Type designed to use a C-style templated struct in C++
using no dynamic memory and with dynamic memory as a templated C++ warper class
and cross-language bindings and deterministic CPU cache optimizations. */

/* Returns the maximum value of the given signed type. */
template <typename Index>
constexpr Index NaNSigned() {
  enum {
    kMax = (sizeof(Index) == 1)
               ? 0x78
               : (sizeof(Index) == 2)
                     ? 0x7ff8
                     : (sizeof(Index) == 4)
                           ? 0x7ffffff8
                           : (sizeof(Index) == 8) ? 0x7ffffffffffffff8 : 0,
  };
  return kMax;
}

/* Returns the maximum value of the given unsigned type. */
template <typename Size>
constexpr Size UnsignedMax() {
  enum {
    kMax = (sizeof(Size) == 1)
               ? 0xf8
               : (sizeof(Size) == 2)
                     ? 0xfff8
                     : (sizeof(Size) == 4)
                           ? 0xfffffff8
                           : (sizeof(Size) == 8) ? 0xfffffffffffffff8 : 0,
  };
  return kMax;
}

/* An array obj of homogeneous-sized plain-old-data (POD) types.

An array may use two different memory layouts, one for a 1D obj of a
given types, and another for a multi-dimensional array that uses the 1D
array in order to store the dimensions. The only different between them is
that the size_array variable gets set to 0.

# Stack Memory Layout

@code
    +----------------+
    |  Packed Stack  |  <-- Only if header_size = 0
    |----------------|
    |     Buffer     |
    |----------------|
    | Stack Elements |
 ^  |----------------|
 |  | TCStack Header |
0xN +----------------+
@endcode

# Multi-dimensional Array Memory Layout

@code
    +-----------------+
    |  C-Style Array  |  <-- Only if header_size > 0
    |-----------------|
    | Dimension Stack |
 ^  |-----------------|
 |  |  TCStack Header |
0xN +-----------------+
@endcode
*/
template <typename T = SIW, typename Size = uint, typename Index = int>
struct TCStack {
  Size size_array,  //< Used for multi-dimensional array.
      size_stack;   //< Total size of the Stack in 64-bit aligned bytes.
  Index count_max,  //< Max element count.
      count;        //< Element count.
};

/* Gets the size of a Stack with the given count_max. */
template <typename T = SIW, typename Size = uint, typename Index = int>
inline Size StackSize(Index count_max) {
  enum { kCountMaxMin = sizeof(UI8) / sizeof(T) };
  if (count_max < kCountMaxMin) count_max = kCountMaxMin;
  return sizeof(TCStack<T, Size, Index>) + sizeof(T) * count_max;
}

/* Gets the min size of a Stack. */
template <typename T = SIW, typename Size = uint, typename Index = int>
inline Size StackSizeMin() {
  enum {
    kStackCountMin = sizeof(T) > 8 ? 1 : 8 / sizeof(T),
    kStackCountMaxMin =
        sizeof(TCStack<T, Size, Index>) + sizeof(T) * kStackCountMin,
  };
  return kStackCountMaxMin;
}

/*
template<typename T = SIW, typename Size = uint, typename Index = int>
inline Size StackSize (Index count) {
  Size size = sizeof (TCStack<T, Size, Index>) + (sizeof (T) * 8) * count;
  return MemoryAlign8<Size> (size);
}*/

/* Gets the max number_ of elements in an obj with the specific index
width. */
template <typename T = SIW, typename Size = uint, typename Index = int>
inline Index StackCountMax() {
  return (Index)((((~(Size)0) - 7) - (Size)sizeof(TCStack<T, Size, Index>)) /
                 (Size)sizeof(T));
}

/*
template<typename T = SIW, typename Size = uint, typename Index = int>
Index StackCountMax () {
    return (Index)((UnsignedMax<Size> () - (Size)sizeof (TCStack<T, Size,
Index>)) / (Size)sizeof (T));
}*/

/* The minimum obj size. */
template <typename T = SIW, typename Size = uint, typename Index = int>
inline Size StackSizeMin(Index count_max) {
  Index count_upper_bounds = StackCountMax<T, Size, Index>();
  if (count_max > count_upper_bounds) count_max = count_upper_bounds;
  return (Size)(sizeof(TCStack<T, Size, Index>) + count_max * sizeof(T));
}

/* Rounds up the count to the 64-bit align the value. */
template <typename T = SIW, typename Size = uint, typename Index = int>
inline Size StackCountMax(Index count_max) {
  enum {
    kStackCountMax =
        (UnsignedMax<Size>() - (Size)sizeof(TCStack<T, Size, Index>)) /
        (Size)sizeof(T),
  };
  count_max = TAlignUpSigned<Index, Size, Index>(count_max);
  if (count_max > kStackCountMax) count_max = kStackCountMax;
  return count_max;
}

/* Initializes an obj from a preallocated socket who's size is a multiple of
8 bytes.
@param socket An obj of bytes large enough to fit the obj.
@return A dynamically allocated socket. */
template <typename T = SIW, typename Size = uint, typename Index = int>
UIW* StackInit(UIW* socket, Size size) {
  ASSERT(socket);

  TCStack<T, Size, Index>* stack =
      reinterpret_cast<TCStack<T, Size, Index>*>(socket);
  stack->size_array = 0;
  stack->size_stack = size;
  Index count_max =
      (Index)((size - sizeof(TCStack<T, Size, Index>)) >> kWordBitCount);
  stack->count_max = count_max;
  stack->count = 0;
  return socket;
}

/* Initializes an obj from a preallocated socket who's size is a multiple of
8 bytes.
@param socket An obj of bytes large enough to fit the obj.
@return A dynamically allocated socket. */
template <typename T = SIW, typename Size = uint, typename Index = int>
UIW* StackInit(UIW* socket, Size size, Index count_max) {
  ASSERT(socket);

  TCStack<T, Size, Index>* stack =
      reinterpret_cast<TCStack<T, Size, Index>*>(socket);
  stack->size_array = 0;
  stack->size_stack = size;
  stack->count_max = (size - sizeof(TCStack<T, Size, Index>)) >> kWordBitCount;
  stack->count = 0;
  return socket;
}

template <typename T = SIW, typename Size = uint, typename Index = int>
UIW* StackClone(TCStack<T, Size, Index>* stack) {
  ASSERT(stack);
  Size size = stack->size_stack >> kWordBitCount;
  UIW other_buffer = new UIW[size];
  UIW *source = reinterpret_cast<UIW*>(stack), *destination = other_buffer;
  Size data_amount =
      (stack->count * sizeof(T) + sizeof(TCStack<T, Size, Index>)) >>
      kWordBitCount;
  size -= data_amount;
  while (data_amount-- > 0) *destination++ = *source++;
  return destination;
}

/* Clones the given obj. */
template <typename T = SIW, typename Size = uint, typename Index = int>
UIW* StackClone(TCStack<T, Size, Index>* stack,
                TCStack<T, Size, Index>* other) {
  ASSERT(stack);
  ASSERT(other);

  Size this_size = stack->size_stack, other_size = other->size_stack;

  if (this_size < other_size) return StackClone(other);

  // We've got enough room in the obj's memory.

  UIW *read = reinterpret_cast<UIW*>(TStackStart(stack)),
      *write = reinterpret_cast<UIW*>(TStackStart(other));

  Index count = other->count;
  stack->count = count;
  UIW* write_end = write + ((count * sizeof(T)) >> kWordBitCount);
  while (write < write_end) *write++ = *read++;
  return reinterpret_cast<UIW*>(stack);
}

/* Returns the first element in the Stack vector. */
template <typename T = SIW, typename Size = uint, typename Index = int>
T* TStackStart(TCStack<T, Size, Index>* stack) {
  ASSERT(stack);
  return reinterpret_cast<T*>(reinterpret_cast<char*>(stack) +
                              sizeof(TCStack<T, Size, Index>));
}

/* Returns the first element in the Stack vector. */
template <typename T = SIW, typename Size = uint, typename Index = int>
T* StackStop(TCStack<T, Size, Index>* stack) {
  ASSERT(stack);
  return TStackStart<T, Size, Index>(stack) + stack->count - 1;
}

/* Inserts the item into the obj at the given index.
@warning Function does not check for bounds and pushing to the top
if the Stack (@see Index StackInsert<Size, Index> (T*, Index, T, Index)).
@param items Pointer to element 0 of the array.
@param item  The item to insert.
@param index The index to insert at.
@return -1 if a is nil and -2 if the obj is full. */
template <typename T = SIW, typename Index = int>
inline Index StackInsert(T* items, Index count, T item, Index index) {
  T *target = items + index, *stop = items + count;
  // Shift the elements up.
  while (target < stop) *stop-- = *stop;
  *target = item;
  return count + 1;
}

/* Inserts the item into the obj at the given index.
@param items Pointer to element 0 of the array.
@param item  The item to insert.
@param index The index to insert at.
@return -1 if a is nil and -2 if the obj is full. */
template <typename T = SIW, typename Index = int>
inline Index StackAdd(T* items, Index count, T item, Index index) {
  ASSERT(items);
  if (index < 0 || index > count) return -1;
  if (index == count) {
    items[count] = item;
    return count + 1;
  }
  if (count == 1) {
    items[1] = items[0];
    items[0] = item;
    return 1;
  }
  return StackInsert<T, Index>(T, count, item, index);
}

/* Inserts the item into the obj at the given index.
@param a     The obj.
@param item  The item to insert.
@param index The index to insert at.
@return -1 if a is nil and -2 if the obj is full.
template<typename T = SIW, typename Size = uint, typename Index = int>
T StackAdd (TCStack<T, Size, Index>* obj, T item, T index) {
  ASSERT (obj);
  Index count_max  = obj->count_max,
      count = obj->count;
  if (count >= count_max)
      return -1;
  T* items = TStackStart<T, Size, Index> (This ());
  return StackAdd<T, Index> (items, count, item, index);
} */

/* Removes an element from the given array. */
template <typename T = SIW, typename Index = SIW>
inline Index TStackRemove(T* elements, Index size, Index index) {
  ASSERT(elements);
  if (index < 0) return index;
  if (size < 0) return size;
  if (size == 1) return 1;
  if (index >= size) return index * -1;
  elements += index;
  T* elements_end = elements + --size;
  while (elements <= elements_end) *elements++ = *elements;
  return size;
}

/* Removes the given index from the obj.
@param  a     The obj.
@param  index The index the item to remove.
@return True if the index is out of bounds. */
template <typename T = SIW, typename Size = uint, typename Index = int>
Index TStackRemove(TCStack<T, Size, Index>* stack, Index index) {
  ASSERT(stack);
  Index result = TStackRemove<T, Index>(TStackStart<T, Size, Index>(stack),
                                        stack->count, index);
  if (result < 0) return result;
  stack->count = result;
  return result;
}

/* Adds the given item to the stop of the obj.
@param  a    The obj.
@param  item The item to push onto the obj.
@return The index of the newly stacked item. */
template <typename T = SIW, typename Size = uint, typename Index = int>
Index TStackPush(TCStack<T, Size, Index>* stack, T item) {
  ASSERT(stack);
  Index count_max = stack->count_max, count = stack->count;
  if (count >= count_max) return -1;
  T* items = TStackStart<T, Size, Index>(stack);
  items[count] = item;
  stack->count = count + 1;
  return count;
}

/* Pops the top item off of the obj.
@note We do not delete the item at the
@param  a The obj.
@return The item popped off the obj. */
template <typename T = SIW, typename Size = uint, typename Index = int>
T TStackPop(TCStack<T, Size, Index>* stack) {
  ASSERT(stack);
  Index count = stack->count;
  if (count == 0) return 0;
  T* items = TStackStart<T, Size, Index>(stack);
  stack->count = count - 1;
  T item = items[count - 1];
  return item;
}

/* Peeks at the top item on the stack without popping it off.
@param  a The obj.
@return The item popped off the obj. */
template <typename T = SIW, typename Size = uint, typename Index = int>
T TStackPeek(TCStack<T, Size, Index>* stack) {
  ASSERT(stack);
  Index count = stack->count;
  if (count == 0) return 0;
  T* items = TStackStart<T, Size, Index>(stack);
  T item = items[stack->count - 1];
  return item;
}

/* Gets the element at the given index.
@param  obj    The obj.
@param  index The index of the element to get.
@return -1 if a is nil and -2 if the index is out of bounds. */
template <typename T = SIW, typename Size = uint, typename Index = int>
T TStackGet(TCStack<T, Size, Index>* stack, Index index) {
  ASSERT(stack);
  if (index >= stack->count) return 0;
  char* address =
      reinterpret_cast<char*>(stack) + sizeof(TCStack<T, Size, Index>);
  return reinterpret_cast<T*>(address)[index];
}

/* Returns true if the given obj contains the given address.
@return false upon failure. */
template <typename T = SIW, typename Size = uint, typename Index = int>
BOL TStackContains(TCStack<T, Size, Index>* stack, void* address) {
  ASSERT(stack);
  char *ptr = reinterpret_cast<char*>(stack),
       *adr = reinterpret_cast<char*>(address);
  if (adr < ptr) return false;
  if (adr >= ptr + stack->size_array) return false;
  return true;
}

/* The obj size in words. */
template <typename T = SIW, typename Size = uint, typename Index = int>
inline Size TStackSizeWords(Index count) {
  return StackSizeMin<T, Size, Index>(count) / sizeof(UIW);
}

/* The upper bounds defines exactly how many elements can fit into a space
in memory.
@warning Anything above this threshold may cause a critical error; AND
sizeof (T) must be 1, 2, 4, or 8. */
template <typename T = SIW, typename Size = uint, typename Index = int>
inline Index TStackCountUpperBounds() {
  enum {
    kShift = (sizeof(T) == 8) ? 3 :             //< Used to divide by 8.
                 (sizeof(T) == 4) ? 2 :         //< Used to divide by 4.
                     (sizeof(T) == 2) ? 1 : 0,  //< Used to divide by 2.
  };
  return (Index)((((~(Size)0) - 7) - (Size)sizeof(TCStack<T, Size, Index>)) /
                 (Size)sizeof(T));
}

/* Doubles the size of the array until the max count is reached.
@return Returns nil if the count_max is greater than the amount of memory that
can fit in type Size, the unaltered socket pointer if the Stack has grown to the
count_max upper bounds, or a new dynamically allocated socket upon failure. */
template <typename T = SIW, typename Size = uint, typename Index = int>
BOL TStackGrow(CObject obj) {
  static Index count_max_auto_size_init = kStackCountMaxDefault;

  UIW* socket = obj.start;

  ASSERT(socket);

  TCStack<T, Size, Index>* stack =
      reinterpret_cast<TCStack<T, Size, Index>*>(socket);
  Index count_max = stack->count_max,
        count_uppoer_bounds = TStackCountUpperBounds<T, Size, Index>();
  if (count_max > count_uppoer_bounds || count_max >= count_uppoer_bounds)
    return false;
  count_max += count_max;
  if (count_max > count_uppoer_bounds) count_max = count_uppoer_bounds;
  Size new_size = sizeof(TCStack<T, Size, Index>) + count_max * sizeof(T);
  new_size = TAlignUpSigned<Size>(new_size, 7);
  UIW* new_buffer = new UIW[new_size >> kWordBitCount];
  TCStack<T, Size, Index>* new_stack =
      reinterpret_cast<TCStack<T, Size, Index>*>(new_buffer);
  new_stack->size_array = 0;
  new_stack->size_stack = new_size;
  Index count = stack->count;
  new_stack->count = count;
  new_stack->count_max = count_max;

  T *source = TStackStart(stack), *destination = TStackStart(new_stack);
  for (; count > 0; count--) *destination++ = *source++;
  AsciiFactory factory = obj.factory;
  if (factory) factory(socket, 0, 0);
  return true;
}

/* Attempts to resize the given Obj to the new_count.
@return Nil upon failure. */
template <typename T = SIW, typename Size = uint, typename Index = int>
BOL TStackResize(CObject obj, Index new_count) {
  TCStack<T, Size, Index> stack =
      *reinterpret_cast<TCStack<T, Size, Index>*>(obj.start);
  Index count = obj.count, count_max = StackCountMax<T, Size, Index>();
  if (count > count_max || count == new_count) return false;
}

/* Prints the given obj to the console. */
template <typename T = SIW, typename Size = uint, typename Index = int,
          typename Char = char>
TUTF<Char>& TPrintStack(TUTF<Char>& utf, TCStack<T, Size, Index>* stack) {
  ASSERT(stack);

  Size size_array = stack->size_array;
  Index count = stack->count;
  if (size_array != 0) return utf << "\n\nStack: Invalid size_array";
  utf << "\n\nStack: count: " << count << " count_max:" << stack->count_max
      << " size_stack:" << stack->size_stack;
  if (stack->size_array != 0) utf << " size_array:invalid";
  T* elements = TStackStart(stack);
  for (int i = 0; i < count; ++i) {
    utf << '\n' << i + 1 << ".) " << elements[i];
  }
  return utf;
}

/* A stack of data.
This is a wrapper class for the

# Stack Memory Map

@code
+----------------+
|  Packed Stack  |  <-- Only if header_size = 0
|----------------|
| 64-bit Aligned |
|     Buffer     |
|----------------|
| Stack Elements |
|----------------|  +
|  Stack struct  |  |
+----------------+ 0x0
@endcode
*/
template <typename T = SIW, typename Size = uint, typename Index = int>
class TStack {
 public:
  /* Initializes a stack of n elements of the given type.
  @param count_max The max number_ of elements that can fit in memory in this
  Stack. */
  TStack(Index count_max = 0) {
    // Align the count_max to a 64-bit word boundary.
    if (count_max == 0) {
      count_max = 32;
    }
    Size size = StackSize<T, Size, Index>(count_max);
    UIW* socket = new UIW[size >> kWordBitCount];
    obj_.SetBegin(socket);
    StackInit(socket, size, count_max);
  }

  /* Copy constructor. */
  TStack(const TStack& other) : obj_(other.Obj()) {}

  /* Destructs nothing.
  @see ~TObject<Index> */
  ~TStack() {}

  /* Returns a clone from dynamic memory. */
  TStack<T, Size, Index>& Clone() { StackClone<T, Size, Index>(Obj()); }

  /* Clones the other object. */
  TStack<T, Size, Index>& Clone(TStack<T, Size, Index>& other) {
    StackClone<T, Size, Index>(Obj(), *other);
  }

  /* Gets the max number_ of elements in an obj with the specific index
  width. */
  inline Index GetElementsMax() { return StackCountMax<T, Size, Index>(); }

  /* Gets the size of the entire Stack, including header, in bytes. */
  inline Size GetSize() { return Obj()->size; }

  /* Gets the min size of the entire Stack, including header, in bytes. */
  inline Size GetSizeMin() { return StackSizeMin<T, Size, Index>(); }

  /* Gets the count of the items on the obj. */
  inline Index GetCount() { return Header().count; }

  /* Gets a pointer to the first element in the obj. */
  inline T* Start() { return TStackStart<T, Size, Index>(Obj()); }

  /* Gets a pointer to the first element in the obj. */
  inline T* Stop() { return Start() + GetCount(); }

  /* Inserts the item into the obj at the given index.
  @return -1 if a is nil and -2 if the obj is full.
  @param item  The item to insert.
  @param index The index to insert at. */
  inline T Insert(T item, T index) {
    return TStack<T, Size, Index>(Obj(), item, index);
  }

  /* Removes the given index from the obj.
  @return True if the index is out of bounds.
  @param  index The index the item to remove. */
  inline BOL Remove(Index index) {
    return TStackRemove<T, Size, Index>(Obj(), index);
  }

  /* Adds the given item to the stop of the obj.
  @return The index of the newly stacked item.
  @param  item The item to push onto the obj. */
  inline Index Push(T item) {
    Index result = TStackPush<T, Size, Index>(Header(), item);
    // std::count << "\n  Pushing " << item;
    if (result < 0) {
      // Printf (" and growing.");
      Grow();
      Index result = TStackPush<T, Size, Index>(Header(), item);
      // COUT << this;
      if (result < 0) return -1;
      return result;
    }
    return result;
  }

  /* Pops the top item off of the obj.
  @return The item popped off the obj. */
  inline T Pop() {
    T value = TStackPop<T, Size, Index>(Header());
    PRINT("\n  Popping ");
    PRINT(value);
    return value;
  }

  /* Peeks the top item off of the obj without popping it.
  @return The item popped off the obj. */
  inline T Peek() { return TStackPeek<T, Size, Index>(Obj()); }

  /* Gets the element at the given index.
  @return -1 if a is nil and -2 if the index is out of bounds.
  @param  index The index of the element to get. */
  inline T Get(Index index) { return TStackGet<T, Size, Index>(Obj(), index); }

  /* Returns true if the given obj contains the given address.
  @return false upon failure. */
  inline BOL Contains(void* address) {
    return TStackContains<T, Size, Index>(Obj(), address);
  }

  /* Resizes the obj to the new_count.
  @return False upon failure. */
  inline BOL Resize(Index new_count) {
    return TStackResize<T, Size, Index>(obj_, new_count);
  }

  /* Doubles the size of the obj.
  @return False upon failure. */
  inline BOL Grow() { return TStackGrow<T, Size, Index>(obj_.Obj()); }

  /* Gets this TObject. */
  inline TObject<Index>& Obj() { return obj_; }

  /* Gets this TObject. */
  inline CObject& CObj() { return obj_.Obj(); }

  /* Returns the TCStack Object. */
  inline TCStack<T, Size, Index>* Header() {
    return reinterpret_cast<TCStack<T, Size, Index>*>(obj_.Begin());
  }

  /* Prints this object to the given UTF. */
  template <typename Char = char>
  inline TUTF<Char>& Print(TUTF<Char>& utf) {
    return TPrintStack<T, Size, Index, Char>(utf, Header());
  }

  /* Prints this object to the SIO. */
  template <typename Char = char, SIW size = kObjSizeDefault>
  inline void Print(AsciiFactory factory = TCOutAuto<UI4, Char>) {
    TStrand<UI4, char> utf(factory);  //< The UTF.
    Print<Char>(utf);
  }

  /* Clones the other object. */
  inline TStack<T, Size, Index>& operator[](
      const TStack<T, Size, Index>& other) {
    Clone(other);
    return *this;
  }

  /* Clones the other object. */
  inline TStack<T, Size, Index>& operator=(
      const TStack<T, Size, Index>& other) {
    Clone(other);
    return *this;
  }

  /* Gets a reference to the given element index. */
  inline T& operator[](size_t index) { return Start()[index]; }

  /* Gets a const reference to the given element index. */
  const T& operator[](size_t index) const { return Start()[index]; }

 private:
  TObject<Index> obj_;  //< ASCII Object.

  /* Sets the socket to the new pointer. */
  inline void SetBuffer(TCStack<T, Size, Index>* stack) {
    ASSERT(stack);
    obj_->start = reinterpret_cast<UIW*>(stack);
  }
};

}  // namespace _

#endif  //< INCLUDED_SCRIPT_TSTACK
#endif  //< #if SEAM >= _0_0_0__05
