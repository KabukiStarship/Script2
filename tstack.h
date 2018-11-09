/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script.git
@file    /tstack.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
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
template <typename SI>
constexpr SI NaNSigned() {
  enum {
    kMax = (sizeof(SI) == 1)
               ? 0x78
               : (sizeof(SI) == 2)
                     ? 0x7ff8
                     : (sizeof(SI) == 4)
                           ? 0x7ffffff8
                           : (sizeof(SI) == 8) ? 0x7ffffffffffffff8 : 0,
  };
  return kMax;
}

/* Returns the maximum value of the given unsigned type. */
template <typename UI>
constexpr UI UnsignedMax() {
  enum {
    kMax = (sizeof(UI) == 1)
               ? 0xf8
               : (sizeof(UI) == 2)
                     ? 0xfff8
                     : (sizeof(UI) == 4)
                           ? 0xfffffff8
                           : (sizeof(UI) == 8) ? 0xfffffffffffffff8 : 0,
  };
  return kMax;
}

/* An array stack of homogeneous-sized plain-old-data (POD) types.

An array may use two different memory layouts, one for a 1D stack of a
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
 |  |  CStack struct |
0xN +----------------+
@endcode

# Multi-dimensional Array Memory Layout

@code
    +-----------------+
    |  C-Style Array  |  <-- Only if header_size > 0
    |-----------------|
    | Dimension Stack |
 ^  |-----------------|
 |  |  CStack struct  |
0xN +-----------------+
@endcode
*/
template <typename T = intptr_t, typename UI = uint, typename SI = int>
struct CStack {
  UI size_array,   //< Used for multi-dimensional array.
      size_stack;  //< Total size of the Stack in 64-bit aligned bytes.
  SI count_max,    //< Max element count.
      count;       //< Element count.
};

/* Gets the size of a Stack with the given count_max. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
inline UI StackSize(SI count_max) {
  enum { kCountMaxMin = sizeof(UI8) / sizeof(T) };
  if (count_max < kCountMaxMin) count_max = kCountMaxMin;
  return sizeof(CStack<T, UI, SI>) + sizeof(T) * count_max;
}

/* Gets the min size of a Stack. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
inline UI StackSizeMin() {
  enum {
    kStackCountMin = sizeof(T) > 8 ? 1 : 8 / sizeof(T),
    kStackCountMaxMin = sizeof(CStack<T, UI, SI>) + sizeof(T) * kStackCountMin,
  };
  return kStackCountMaxMin;
}

/*
template<typename T = intptr_t, typename UI = uint, typename SI = int>
inline UI StackSize (SI count) {
    UI size = sizeof (CStack<T, UI, SI>) + (sizeof (T) * 8) * count;
    return MemoryAlign8<UI> (size);
}*/

/* Gets the max number of elements in an stack with the specific index
width. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
inline SI StackCountMax() {
  return (SI)((((~(UI)0) - 7) - (UI)sizeof(CStack<T, UI, SI>)) / (UI)sizeof(T));
}

/*
template<typename T = intptr_t, typename UI = uint, typename SI = int>
SI StackCountMax () {
    return (SI)((UnsignedMax<UI> () - (UI)sizeof (CStack<T, UI, SI>)) /
        (UI)sizeof (T));
}*/

/* The minimum stack size. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
inline UI StackSizeMin(SI count_max) {
  SI count_upper_bounds = StackCountMax<T, UI, SI>();
  if (count_max > count_upper_bounds) count_max = count_upper_bounds;
  return (UI)(sizeof(CStack<T, UI, SI>) + count_max * sizeof(T));
}

/* Rounds up the count to the 64-bit align the value. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
inline UI StackCountMax(SI count_max) {
  enum {
    kStackCountMax =
        (UnsignedMax<UI>() - (UI)sizeof(CStack<T, UI, SI>)) / (UI)sizeof(T),
  };
  count_max = AlignUpSigned<SI, UI, SI>(count_max);
  if (count_max > kStackCountMax) count_max = kStackCountMax;
  return count_max;
}

/* Initializes an stack from a preallocated buffer who's size is a multiple of
8 bytes.
@param buffer An stack of bytes large enough to fit the stack.
@return A dynamically allocated buffer. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
uintptr_t* StackInit(uintptr_t* buffer, UI size) {
  ASSERT(buffer);

  CStack<T, UI, SI>* stack = reinterpret_cast<CStack<T, UI, SI>*>(buffer);
  stack->size_array = 0;
  stack->size_stack = size;
  SI count_max = (SI)((size - sizeof(CStack<T, UI, SI>)) >> kWordBitCount);
  stack->count_max = count_max;
  stack->count = 0;
  return buffer;
}

/* Initializes an stack from a preallocated buffer who's size is a multiple of
8 bytes.
@param buffer An stack of bytes large enough to fit the stack.
@return A dynamically allocated buffer. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
uintptr_t* StackInit(uintptr_t* buffer, UI size, SI count_max) {
  ASSERT(buffer);

  CStack<T, UI, SI>* stack = reinterpret_cast<CStack<T, UI, SI>*>(buffer);
  stack->size_array = 0;
  stack->size_stack = size;
  stack->count_max = (size - sizeof(CStack<T, UI, SI>)) >> kWordBitCount;
  stack->count = 0;
  return buffer;
}

template <typename T = intptr_t, typename UI = uint, typename SI = int>
uintptr_t* StackClone(CStack<T, UI, SI>* stack) {
  ASSERT(stack);
  UI size = stack->size_stack >> kWordBitCount;
  uintptr_t other_buffer = new uintptr_t[size];
  uintptr_t *source = reinterpret_cast<uintptr_t*>(stack),
            *destination = other_buffer;
  UI data_amount =
      (stack->count * sizeof(T) + sizeof(CStack<T, UI, SI>)) >> kWordBitCount;
  size -= data_amount;
  while (data_amount-- > 0) *destination++ = *source++;
  return destination;
}

/* Clones the given stack. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
uintptr_t* StackClone(CStack<T, UI, SI>* stack, CStack<T, UI, SI>* other) {
  ASSERT(stack);
  ASSERT(other);

  UI this_size = stack->size_stack, other_size = other->size_stack;

  if (this_size < other_size) return StackClone(other);

  // We've got enough room in the stack's memory.

  uintptr_t *read = reinterpret_cast<uintptr_t*>(StackStart(stack)),
            *write = reinterpret_cast<uintptr_t*>(StackStart(other));

  SI count = other->count;
  stack->count = count;
  uintptr_t* write_end = write + ((count * sizeof(T)) >> kWordBitCount);
  while (write < write_end) *write++ = *read++;
  return reinterpret_cast<uintptr_t*>(stack);
}

/* Returns the first element in the Stack vector. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
T* StackStart(CStack<T, UI, SI>* stack) {
  ASSERT(stack);
  return reinterpret_cast<T*>(reinterpret_cast<char*>(stack) +
                              sizeof(CStack<T, UI, SI>));
}

/* Returns the first element in the Stack vector. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
T* StackStop(CStack<T, UI, SI>* stack) {
  ASSERT(stack);
  return StackStart<T, UI, SI>(stack) + stack->count - 1;
}

/* Inserts the item into the stack at the given index.
@warning Function does not check for bounds and pushing to the top
if the Stack (@see SI StackInsert<UI, SI> (T*, SI, T, SI)).
@param items Pointer to element 0 of the array.
@param item  The item to insert.
@param index The index to insert at.
@return -1 if a is nil and -2 if the stack is full. */
template <typename T = intptr_t, typename SI = int>
inline SI StackInsert(T* items, SI count, T item, SI index) {
  T *target = items + index, *end = items + count;
  // Shift the elements up.
  while (target < end) *end-- = *end;
  *target = item;
  return count + 1;
}

/* Inserts the item into the stack at the given index.
@param items Pointer to element 0 of the array.
@param item  The item to insert.
@param index The index to insert at.
@return -1 if a is nil and -2 if the stack is full. */
template <typename T = intptr_t, typename SI = int>
inline SI StackAdd(T* items, SI count, T item, SI index) {
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
  return StackInsert<T, SI>(T, count, item, index);
}

/* Inserts the item into the stack at the given index.
@param a     The stack.
@param item  The item to insert.
@param index The index to insert at.
@return -1 if a is nil and -2 if the stack is full.
template<typename T = intptr_t, typename UI = uint, typename SI = int>
T StackAdd (CStack<T, UI, SI>* stack, T item, T index) {
  ASSERT (stack);
  SI count_max  = stack->count_max,
      count = stack->count;
  if (count >= count_max)
      return -1;
  T* items = StackStart<T, UI, SI> (This ());
  return StackAdd<T, SI> (items, count, item, index);
} */

/* Removes an element from the given array. */
template <typename T = intptr_t, typename SI = intptr_t>
inline SI StackRemove(T* elements, SI size, SI index) {
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

/* Removes the given index from the stack.
@param  a     The stack.
@param  index The index the item to remove.
@return True if the index is out of bounds. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
SI StackRemove(CStack<T, UI, SI>* stack, SI index) {
  ASSERT(stack);
  SI result =
      StackRemove<T, SI>(StackStart<T, UI, SI>(stack), stack->count, index);
  if (result < 0) return result;
  stack->count = result;
  return result;
}

/* Adds the given item to the end of the stack.
@param  a    The stack.
@param  item The item to push onto the stack.
@return The index of the newly stacked item. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
SI StackPush(CStack<T, UI, SI>* stack, T item) {
  ASSERT(stack);
  SI count_max = stack->count_max, count = stack->count;
  if (count >= count_max) return -1;
  T* items = StackStart<T, UI, SI>(stack);
  items[count] = item;
  stack->count = count + 1;
  return count;
}

/* Pops the top item off of the stack.
@note We do not delete the item at the
@param  a The stack.
@return The item popped off the stack. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
T StackPop(CStack<T, UI, SI>* stack) {
  ASSERT(stack);
  SI count = stack->count;
  if (count == 0) return 0;
  T* items = StackStart<T, UI, SI>(stack);
  stack->count = count - 1;
  T item = items[count - 1];
  return item;
}

/* Pops the top item off of the stack.
@note We do not delete the item at the
@param  a The stack.
@return The item popped off the stack. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
T StackPeek(CStack<T, UI, SI>* stack) {
  ASSERT(stack);
  SI count = stack->count;
  if (count == 0) return 0;
  T* items = StackStart<T, UI, SI>(stack);
  T item = items[stack->count - 1];
  return item;
}

/* Gets the element at the given index.
@param  stack    The stack.
@param  index The index of the element to get.
@return -1 if a is nil and -2 if the index is out of bounds. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
T StackGet(CStack<T, UI, SI>* stack, SI index) {
  ASSERT(stack);
  if (index >= stack->count) return 0;
  char* address = reinterpret_cast<char*>(stack) + sizeof(CStack<T, UI, SI>);
  return reinterpret_cast<T*>(address)[index];
}

/* Returns true if the given stack contains the given address.
@return false upon failure. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
BOL StackContains(CStack<T, UI, SI>* stack, void* address) {
  ASSERT(stack);
  char *ptr = reinterpret_cast<char*>(stack),
       *adr = reinterpret_cast<char*>(address);
  if (adr < ptr) return false;
  if (adr >= ptr + stack->size_array) return false;
  return true;
}

/* The stack size in words. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
inline UI StackSizeWords(SI count) {
  return StackSizeMin<T, UI, SI>(count) / sizeof(uintptr_t);
}

/* The upper bounds defines exactly how many elements can fit into a space
in memory.
@warning Anything above this threshold may cause a critical error; AND
sizeof (T) must be 1, 2, 4, or 8. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
inline SI StackCountUpperBounds() {
  enum {
    kShift = (sizeof(T) == 8) ? 3 :             //< Used to divide by 8.
                 (sizeof(T) == 4) ? 2 :         //< Used to divide by 4.
                     (sizeof(T) == 2) ? 1 : 0,  //< Used to divide by 2.
  };
  return (SI)((((~(UI)0) - 7) - (UI)sizeof(CStack<T, UI, SI>)) / (UI)sizeof(T));
}

/* Doubles the size of the array until the max count is reached.
@return Returns nil if the count_max is greater than the amount of memory that
can fit in type UI, the unaltered buffer pointer if the Stack has grown to the
count_max upper bounds, or a new dynamically allocated buffer upon failure. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
BOL StackGrow(CObject& obj) {
  static SI count_max_auto_size_init = kStackCountMaxDefault;

  uintptr_t* buffer = obj.buffer;

  ASSERT(buffer);

  CStack<T, UI, SI>* stack = reinterpret_cast<CStack<T, UI, SI>*>(buffer);
  SI count_max = stack->count_max,
     count_uppoer_bounds = StackCountUpperBounds<T, UI, SI>();
  if (count_max > count_uppoer_bounds || count_max >= count_uppoer_bounds)
    return false;
  count_max += count_max;
  if (count_max > count_uppoer_bounds) count_max = count_uppoer_bounds;
  UI new_size = sizeof(CStack<T, UI, SI>) + count_max * sizeof(T), word_count;
  if ((new_size & 0x7) == 0)
    word_count = new_size >> kWordBitCount;
  else
    word_count = (new_size >> kWordBitCount) + 1;
  uintptr_t* new_buffer = new uintptr_t[word_count];
  CStack<T, UI, SI>* new_stack =
      reinterpret_cast<CStack<T, UI, SI>*>(new_buffer);
  new_stack->size_array = 0;
  new_stack->size_stack = new_size;
  SI count = stack->count;
  new_stack->count = count;
  new_stack->count_max = count_max;

  T *source = StackStart(stack), *destination = StackStart(new_stack);
  for (; count > 0; count--) *destination++ = *source++;
  delete[] buffer;
  return true;
}

/* Attempts to resize the given OBJ to the new_count.
@return NIL upon failure. */
template <typename T = intptr_t, typename UI = uint, typename SI = int>
BOL StackResize(CObject obj, SI new_count) {
  CStack<T, UI, SI> stack = *reinterpret_cast<CStack<T, UI, SI>*>(obj.begin);
  SI count = stack.count, count_max = StackCountMax<T, UI, SI>();
  if (count > count_max || count == new_count) return false;
}

/* Prints the given stack to the console. */
template <typename T = intptr_t, typename UI = uint, typename SI = int,
          typename Char = char>
TUTF<Char>& PrintStack(TUTF<Char>& utf, CStack<T, UI, SI>* stack) {
  ASSERT(stack);
  UI size_array = stack->size_array;
  SI count = stack->count;
  if (size_array != 0) return utf << "\n\nStack: count: Invalid size_array!";
  utf << "\n\nStack: count: " << count << " count_max:" << stack->count_max
      << " size_stack:" << stack->size_stack;
  if (stack->size_array != 0) utf << " size_array:invalid";
  T* elements = StackStart(stack);
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
template <typename T = intptr_t, typename UI = uint, typename SI = int>
class TStack {
 public:
  /* Initializes an stack of n elements of the given type.
  @param count_max The max number of elements that can fit in memory in this
  Stack. */
  TStack(SI count_max = 0) {
    // Align the count_max to a 64-bit word boundary
    if (count_max == 0) {
      count_max = 32;
    }
    UI size = StackSize<T, UI, SI>(count_max);
    uintptr_t* buffer = new uintptr_t[size >> kWordBitCount];
    obj_->begin = buffer;
    StackInit(buffer, size, count_max);
  }

  /* Copy constructor. */
  TStack(const TStack& other) : obj_(other.OBJ()) {}

  /* Deallocates the buffer_. */
  ~TStack() {}

  /* Returns a clone from dynamic memory. */
  TStack<T, UI, SI>& Clone() { StackClone<T, UI, SI>(OBJ()); }

  /* Clones the other object. */
  TStack<T, UI, SI>& Clone(TStack<T, UI, SI>& other) {
    StackClone<T, UI, SI>(OBJ(), *other);
  }

  /* Gets the max number of elements in an stack with the specific index
  width. */
  inline SI GetElementsMax() { return StackCountMax<T, UI, SI>(); }

  /* Gets the size of the entire Stack, including header, in bytes. */
  inline UI GetSize() { return OBJ()->size; }

  /* Gets the min size of the entire Stack, including header, in bytes. */
  inline UI GetSizeMin() { return StackSizeMin<T, UI, SI>(); }

  /* Gets the count of the items on the stack. */
  inline SI GetCount() { return Header().count; }

  /* Gets a pointer to the first element in the stack. */
  inline T* Start() { return StackStart<T, UI, SI>(OBJ()); }

  /* Gets a pointer to the first element in the stack. */
  inline T* Stop() { return Start() + GetCount(); }

  /* Inserts the item into the stack at the given index.
  @return -1 if a is nil and -2 if the stack is full.
  @param item  The item to insert.
  @param index The index to insert at. */
  T Insert(T item, T index) { return TStack<T, UI, SI>(OBJ(), item, index); }

  /* Removes the given index from the stack.
  @param  index The index the item to remove.
  @return True if the index is out of bounds. */
  BOL Remove(SI index) { return StackRemove<T, UI, SI>(OBJ(), index); }

  /* Adds the given item to the end of the stack.
  @return The index of the newly stacked item.
  @param  item The item to push onto the stack. */
  SI Push(T item) {
    SI result = StackPush<T, UI, SI>(OBJ(), item);
    // std::count << "\n  Pushing " << item;
    if (result < 0) {
      // Printf (" and growing.");
      Grow();
      SI result = StackPush<T, UI, SI>(OBJ(), item);
      // COUT << this;
      if (result < 0) return -1;
      return result;
    }
    return result;
  }

  /* Pops the top item off of the stack.
  @return The item popped off the stack. */
  inline T Pop() {
    T value = StackPop<T, UI, SI>(OBJ());
    PRINT("\n  Popping ");
    PRINT(value);
    return value;
  }

  /* Peeks the top item off of the stack without popping it.
  @return The item popped off the stack. */
  inline T Peek() { return StackPeek<T, UI, SI>(OBJ()); }

  /* Gets the element at the given index.
  @return -1 if a is nil and -2 if the index is out of bounds.
  @param  index The index of the element to get. */
  inline T Get(SI index) { return StackGet<T, UI, SI>(OBJ(), index); }

  /* Returns true if the given stack contains the given address.
  @return false upon failure. */
  inline BOL Contains(void* address) {
    return StackContains<T, UI, SI>(OBJ(), address);
  }

  /* Resizes the stack to the new_count.
  @return False upon failure. */
  inline BOL Resize(SI new_count) {
    return StackResize<T, UI, SI>(obj_, new_count);
  }

  /* Doubles the size of the stack.
  @return False upon failure. */
  inline BOL Grow() { return StackGrow<T, UI, SI>(obj_); }

  /* Gets this TObject. */
  inline TObject<SI>& OBJ() { return obj_; }

  /* Gets this TObject. */
  inline CObject& COBJ() { return obj_.OBJ(); }

  /* Returns the CStack kOBJ. */
  inline CStack<T, UI, SI>* Header() {
    return reinterpret_cast<CStack<T, UI, SI>*>(obj_.Begin());
  }

  /* Prints this object to the given UTF. */
  inline UTF1& Print(UTF1& out = COUT) { return out << Header(); }

  /* Clones the other object. */
  inline TStack<T, UI, SI>& operator[](const TStack<T, UI, SI>& other) {
    Clone(other);
    return *this;
  }

  /* Clones the other object. */
  inline TStack<T, UI, SI>& operator=(const TStack<T, UI, SI>& other) {
    Clone(other);
    return *this;
  }

  /* Gets a reference to the given element index. */
  T& operator[](size_t index) { return Start()[index]; }

  /* Gets a const reference to the given element index. */
  const T& operator[](size_t index) const { return Start()[index]; }

 private:
  TObject<SI> obj_;  //< ASCII Object.

  inline void SetBuffer(CStack<T, UI, SI>* stack) {
    ASSERT(stack);
    obj_->begin = reinterpret_cast<uintptr_t*>(stack);
  }
};

}  // namespace _

#include "test_footer.inl"
#endif  //< INCLUDED_SCRIPT_TSTACK
#endif  //< #if SEAM >= _0_0_0__05
