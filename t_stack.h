/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_stack.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_7
#ifndef SCRIPT2_TSTACK
#define SCRIPT2_TSTACK 1

#include "c_socket.h"
#include "t_object.h"
#include "t_strand.h"

#if SEAM == SCRIPT2_7
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* @ingroup AsciiStack
Stack is an ASCII Data Type designed to use a C-style templated struct in C++
using no dynamic memory and with dynamic memory as a templated C++ warper class
and cross-language bindings and deterministic CPU cache optimizations. */

/* Returns the maximum value of the given signed type. */
template <typename SIZ>
constexpr SIZ NaNSigned() {
  enum {
    kMax = (sizeof(SIZ) == 1)
               ? 0x78
               : (sizeof(SIZ) == 2)
                     ? 0x7ff8
                     : (sizeof(SIZ) == 4)
                           ? 0x7ffffff8
                           : (sizeof(SIZ) == 8) ? 0x7ffffffffffffff8 : 0,
  };
  return kMax;
}

/* Returns the maximum value of the given unsigned type. */
template <typename SIZ>
constexpr SIZ UnsignedMax() {
  enum {
    kMax = (sizeof(SIZ) == 1)
               ? 0xf8
               : (sizeof(SIZ) == 2)
                     ? 0xfff8
                     : (sizeof(SIZ) == 4)
                           ? 0xfffffff8
                           : (sizeof(SIZ) == 8) ? 0xfffffffffffffff8 : 0,
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
 |  | SStack Header  |
0xN +----------------+
@endcode

# Multi-dimensional Array Memory Layout

@code
    +-----------------+
    |  C-Style Array  |  <-- Only if header_size > 0
    |-----------------|
    | Dimension Stack |
 ^  |-----------------|
 |  |  SStack Header  |
0xN +-----------------+
@endcode
*/
template <typename SIZ = SI4>
struct SStack {
  SIZ size,   //< SIZ of the Stack in bytes.
      count;  //< Element count.
};

/* Gets the size of a Stack with the given count_max. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackSize(SIZ count_max) {
  enum { kCountMaxMin = sizeof(UI8) / sizeof(T) };
  if (count_max < kCountMaxMin) count_max = kCountMaxMin;
  return sizeof(SStack<SIZ>) + sizeof(T) * count_max;
}

/* Gets the min size of a Stack with zero elements. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackSizeMin() {
  enum {
    kStackCountMin = sizeof(T) > 8 ? 1 : 8 / sizeof(T),
    kStackCountMaxMin = sizeof(SStack<SIZ>) + sizeof(T) * kStackCountMin,
  };
  return kStackCountMaxMin;
}

/*
template<typename T = SI4, typename SIZ = SI4>
inline SIZ StackSize (SIZ count) {
  SIZ size = sizeof (SStack<SIZ>) + (sizeof (T) * 8) * count;
  return MemoryAlign8<SIZ> (size);
}*/

/* Gets the max number_ of elements in an obj with the specific index
width. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackCountMax() {
  return (SIZ)((((~(SIZ)0) - 7) - (SIZ)sizeof(SStack<SIZ>)) / (SIZ)sizeof(T));
}

/*
template<typename T = SI4, typename SIZ = SI4>
SIZ StackCountMax () {
    return (SIZ)((UnsignedMax<SIZ> () - (SIZ)sizeof (SStack<T, SIZ,
SIZ>)) / (SIZ)sizeof (T));
}*/

/* The minimum obj size. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackSizeMin(SIZ count_max) {
  SIZ count_upper_bounds = TStackCountMax<T, SIZ>();
  if (count_max > count_upper_bounds) count_max = count_upper_bounds;
  return (SIZ)(sizeof(SStack<SIZ>) + count_max * sizeof(T));
}

/* Rounds up the count to the 64-bit align the value. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackCountMax(SIZ count_max) {
  enum {
    kStackCountMax =
        (UnsignedMax<SIZ>() - (SIZ)sizeof(SStack<SIZ>)) / (SIZ)sizeof(T),
  };
  count_max = TAlignUpSigned<SIZ, SIZ, SIZ>(count_max);
  if (count_max > kStackCountMax) count_max = kStackCountMax;
  return count_max;
}

/* Initializes an obj from a preallocated socket who's size is a multiple of
8 bytes.
@param socket An obj of bytes large enough to fit the obj.
@return A dynamically allocated socket. */
template <typename T = SI4, typename SIZ = SI4>
SStack<SIZ>* TStackInit(SStack<SIZ>* stack, SIZ size) {
  if (!stack || size < sizeof(SStack<SIZ>)) return nullptr;
  stack->size = size;
  stack->count = 0;
  return stack;
}

/* Initializes an obj from a preallocated socket who's size is a multiple of
8 bytes.
@param socket An obj of bytes large enough to fit the obj.
@return A dynamically allocated socket. */
template <typename T = SI4, typename SIZ = SI4>
UIW* TStackInit(UIW* socket, SIZ size, const T* items, SIZ count) {
  DASSERT(socket);
  if (!items || count < 0) return nullptr;

  SStack<SIZ>* stack = reinterpret_cast<SStack<SIZ>*>(socket);
  stack->size_stack = size;
  stack->count_max = (size - sizeof(SStack<SIZ>)) >> kWordBitCount;
  stack->count = 0;
  return socket;
}

template <typename T = SI4, typename SIZ = SI4>
UIW* TStackClone(SStack<SIZ>* stack) {
  ASSERT(stack);
  SIZ size = stack->size_stack >> kWordBitCount;
  UIW other_buffer = new UIW[size];
  UIW *source = reinterpret_cast<UIW*>(stack), *destination = other_buffer;
  SIZ data_amount =
      (stack->count * sizeof(T) + sizeof(SStack<SIZ>)) >> kWordBitCount;
  size -= data_amount;
  while (data_amount-- > 0) *destination++ = *source++;
  return destination;
}

/* Clones the given obj. */
template <typename T = SI4, typename SIZ = SI4>
UIW* TStackClone(SStack<SIZ>* stack, SStack<SIZ>* other) {
  ASSERT(stack);
  ASSERT(other);

  SIZ this_size = stack->size_stack, other_size = other->size_stack;

  if (this_size < other_size) return TStackClone(other);

  // We've got enough room in the obj's memory.

  UIW *read = reinterpret_cast<UIW*>(TStackStart(stack)),
      *write = reinterpret_cast<UIW*>(TStackStart(other));

  SIZ count = other->count;
  stack->count = count;
  UIW* write_end = write + ((count * sizeof(T)) >> kWordBitCount);
  while (write < write_end) *write++ = *read++;
  return reinterpret_cast<UIW*>(stack);
}

/* Returns the first element in the Stack TArray. */
template <typename T = SI4, typename SIZ = SI4>
T* TStackStart(SStack<SIZ>* stack) {
  return reinterpret_cast<T*>(reinterpret_cast<UIW>(stack) +
                              sizeof(SStack<SIZ>));
}

/* Returns the first element in the Stack TArray. */
template <typename T = SI4, typename SIZ = SI4>
T* TStackStop(SStack<SIZ>* stack) {
  return TStackStart<T, SIZ>(stack) + stack->count - 1;
}

/* Inserts the item into the obj at the given index.
@warning Function does not check for bounds and pushing to the top
if the Stack (@see SIZ TStackInsert<SIZ, SIZ> (T*, SIZ, T, SIZ)).
@param items Pointer to element 0 of the array.
@param item  The item to insert.
@param index The index to insert at.
@return -1 if a is nil and -2 if the obj is full. */
template <typename T = SIW, typename SIZ = SI4>
inline SIZ TStackInsert(T* items, SIZ count, T item, SIZ index) {
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
template <typename T = SIW, typename SIZ = SI4>
inline SIZ TStackAdd(T* items, SIZ count, T item, SIZ index) {
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
  return TStackInsert<T, SIZ>(T, count, item, index);
}

/* Inserts the item into the obj at the given index.
@param a     The obj.
@param item  The item to insert.
@param index The index to insert at.
@return -1 if a is nil and -2 if the obj is full.
template<typename T = SI4, typename SIZ = SI4>
T TStackAdd (SStack<SIZ>* obj, T item, T index) {
  ASSERT (obj);
  SIZ count_max  = obj->count_max,
      count = obj->count;
  if (count >= count_max)
      return -1;
  T* items = TStackStart<T, SIZ> (This ());
  return TStackAdd<T, SIZ> (items, count, item, index);
} */

/* Removes an element from the given array. */
template <typename T = SIW, typename SIZ = SIW>
inline SIZ TStackRemove(T* elements, SIZ size, SIZ index) {
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
@param  stack The Ascii Object base poiner.
@param  index The index the item to remove.
@return True if the index is out of bounds. */
template <typename T = SI4, typename SIZ = SI4>
SIZ TStackRemove(SStack<SIZ>* stack, SIZ index) {
  ASSERT(stack);
  SIZ result =
      TStackRemove<T, SIZ>(TStackStart<T, SIZ>(stack), stack->count, index);
  if (result < 0) return result;
  stack->count = result;
  return result;
}

/* Adds the given item to the stop of the obj.
@param  stack The Ascii Object base poiner.
@param  item  The item to push onto the obj.
@return The index of the newly stacked item. */
template <typename T = SI4, typename SIZ = SI4>
SIZ TStackPush(SStack<SIZ>* stack, T item) {
  ASSERT(stack);
  SIZ size = stack->size, count = stack->count;
  if (count >= size) return -1;
  T* items = TStackStart<T, SIZ>(stack);
  items[count] = item;
  stack->count = count + 1;
  return count;
}

/* Pops the top item off of the obj.
@note We do not delete the item at the
@param  a The obj.
@return The item popped off the obj. */
template <typename T = SI4, typename SIZ = SI4>
T TStackPop(SStack<SIZ>* stack) {
  ASSERT(stack);
  SIZ count = stack->count;
  if (count == 0) return 0;
  T* items = TStackStart<T, SIZ>(stack);
  stack->count = count - 1;
  T item = items[count - 1];
  return item;
}

/* Peeks at the top item on the stack without popping it off.
@param  stack The base address of the stack.
@return The item popped off the obj. */
template <typename T = SI4, typename SIZ = SI4>
T TStackPeek(SStack<SIZ>* stack) {
  ASSERT(stack);
  SIZ count = stack->count;
  if (count == 0) return 0;
  T* items = TStackStart<T, SIZ>(stack);
  T item = items[stack->count - 1];
  return item;
}

/* Gets the element at the given index.
@param  obj    The obj.
@param  index The index of the element to get.
@return -1 if a is nil and -2 if the index is out of bounds. */
template <typename T = SI4, typename SIZ = SI4>
T TStackGet(SStack<SIZ>* stack, SIZ index) {
  ASSERT(stack);
  if (index >= stack->count) return 0;
  CH1* address = reinterpret_cast<CH1*>(stack) + sizeof(SStack<SIZ>);
  return reinterpret_cast<T*>(address)[index];
}

/* Returns true if the given obj contains the given address.
@return false upon failure. */
template <typename T = SI4, typename SIZ = SI4>
BOL TStackContains(SStack<SIZ>* stack, void* address) {
  ASSERT(stack);
  CH1 *ptr = reinterpret_cast<CH1*>(stack),
      *adr = reinterpret_cast<CH1*>(address);
  if (adr < ptr) return false;
  if (adr >= ptr + stack->size_array) return false;
  return true;
}

/* The obj size in words. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackSizeWords(SIZ count) {
  return TStackSizeMin<T, SIZ>(count) / sizeof(UIW);
}

/* The upper bounds defines exactly how many elements can fit into a space
in memory.
@warning Anything above this threshold may cause a critical error; AND
sizeof (T) must be 1, 2, 4, or 8. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackCountUpperBounds() {
  enum {
    kShift = (sizeof(T) == 8) ? 3 :             //< Used to divide by 8.
                 (sizeof(T) == 4) ? 2 :         //< Used to divide by 4.
                     (sizeof(T) == 2) ? 1 : 0,  //< Used to divide by 2.
  };
  return (SIZ)((((~(SIZ)0) - 7) - (SIZ)sizeof(SStack<SIZ>)) / (SIZ)sizeof(T));
}

/* Doubles the size of the array until the max count is reached.
@return Returns nil if the count_max is greater than the amount of memory that
can fit in type SIZ, the unaltered socket pointer if the Stack has grown to the
count_max upper bounds, or a new dynamically allocated socket upon failure. */
template <typename T = SI4, typename SIZ = SI4>
BOL TStackGrow(CObject& obj) {
  static SIZ count_max_auto_size_init = kStackCountMaxDefault;

  UIW* socket = obj.begin;

  ASSERT(socket);

  SStack<SIZ>* stack = reinterpret_cast<SStack<SIZ>*>(socket);
  SIZ count_max = stack->count_max,
      count_uppoer_bounds = TStackCountUpperBounds<T, SIZ>();
  if (count_max > count_uppoer_bounds || count_max >= count_uppoer_bounds)
    return false;
  count_max += count_max;
  if (count_max > count_uppoer_bounds) count_max = count_uppoer_bounds;
  SIZ new_size = sizeof(SStack<SIZ>) + count_max * sizeof(T);
  new_size = TAlignUpSigned<SIZ>(new_size, 7);
  UIW* new_buffer = new UIW[new_size >> kWordBitCount];
  SStack<SIZ>* new_stack = reinterpret_cast<SStack<SIZ>*>(new_buffer);
  new_stack->size_array = 0;
  new_stack->size_stack = new_size;
  SIZ count = stack->count;
  new_stack->count = count;
  new_stack->count_max = count_max;

  T *source = TStackStart(stack), *destination = TStackStart(new_stack);
  for (; count > 0; count--) *destination++ = *source++;
  AsciiFactory factory = obj.factory;
  if (factory) factory(obj, kFactoryDelete, nullptr);
  return true;
}

/* Attempts to resize the given CObject to the new_count.
@return Nil upon failure. */
template <typename T = SI4, typename SIZ = SI4>
BOL TStackResize(CObject& obj, SIZ new_count) {
  SStack<SIZ> stack = *reinterpret_cast<SStack<SIZ>*>(obj.begin);
  SIZ count = obj.count, count_max = TStackCountMax<T, SIZ>();
  if (count > count_max || count == new_count) return false;
}

template <typename T = SI4, typename SIZ = SI4>
BOL TStackInBounds(SStack<SIZ>* stack, SIZ index) {
  return index >= 0 && index < stack->count_max;
}

/* Prints the given obj to the console. */
template <typename Printer, typename T = SI4, typename SIZ = SI4>
Printer& TStackPrint(Printer& o, SStack<SIZ>* stack) {
  DASSERT(stack);
  SIZ size = stack->size, count = stack->count;
  o << "\n\nStack: count: " << count << " size:" << size;

  T* elements = TStackStart(stack);
  for (SI4 i = 0; i < count; ++i) o << kLF << i + 1 << ", " << elements[i];

  return o;
}

template <typename T, typename SIZ>
SIN TStackFactory(CObject& obj, SIW function, void* arg, BOL using_heap) {
  SI4 size;
  switch (function) {
    case kFactoryDelete: {
      PRINT("\nEntering Strand.Factory.Delete:");
      return Delete(obj, using_heap);
    }
    case kFactoryGrow: {
      PRINT("\nEntering Strand.Factory.Grow:");
      if (!arg) return kFactoryNilArg;
      UIW *begin = obj.begin, *new_begin = TObjGrowDouble<SI4>(begin);
      if (!new_begin) return kFactoryCantGrow;

      TUTF<Char> new_utf(new_begin);
      PRINTF(" new size:%i", TObjSize<SI4>(new_begin));
      Char* start = TSTRStart<Char>(begin);
      new_utf << start;
      reinterpret_cast<TUTF<Char>*>(arg)->Set(new_utf);
      Char* new_start = TSTRStart<Char>(new_begin);
      PRINTF("\nCopying \"%s\" with result:\"%s\"", start, new_start);

      if (using_heap) delete[] begin;
      obj.begin = new_begin;
      return 0;
    }
    case kFactoryClone: {
      PRINT("\nEntering Strand.Factory.Clone:");
      if (!arg) return kFactoryNilArg;
      CObject* other = reinterpret_cast<CObject*>(arg);
      UIW* begin = obj.begin;
      UIW* obj = TObjClone<SI4>(obj);
      if (!obj) return kFactoryCantGrow;
      other->begin = obj;
      other->factory = other->factory;
      return 0;
    }
    case kFactoryInfo: {
      *reinterpret_cast<const CH1**>(arg) = "Strand";
      return 0;
    }
  }
  return 0;
}

/* A SStack of data with an AsciiFactory.

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
template <typename T = SI4, typename SIZ = SI4, typename BUF = Nil>
class AStack {
 public:
  /* Initializes a stack of n elements of the given type.
  @param size The max element count. */
  AStack(SIZ size = 0) {}

  AStack(SIZ size, const T* items) {}

  /* Copy constructor. */
  AStack(const AStack& other) : obj_(other.CObj()) {}

  /* Destructs nothing. */
  ~AStack() {}

  /* Returns a clone from dynamic memory. */
  AStack<T, SIZ>& Clone() { TStackClone<T, SIZ>(AObj()); }

  /* Clones the other object. */
  AStack<T, SIZ>& Clone(AStack<T, SIZ>& other) {
    TStackClone<T, SIZ>(AObj(), *other);
  }

  /* Checks if the given index is a valid element.
  @return true if the index is in bounds. */
  inline BOL InBounds(SIZ index) {
    return TStackInBounds<T, SIZ>(obj_.CObj(), index);
  }

  /* Gets the max number_ of elements in an obj with the specific index
  width. */
  inline SIZ ElementsMax() { return TStackCountMax<T, SIZ>(); }

  /* Gets the size of the entire Stack, including header, in bytes. */
  inline SIZ SizeBytes() { return AObj()->SizeBytes(); }

  /* Gets the min size of the entire Stack, including header, in bytes. */
  inline SIZ SizeMin() { return TStackSizeMin<T, SIZ>(); }

  /* Gets the count of the items on the obj. */
  inline SIZ Count() { return Obj().count; }

  /* Gets a pointer to the first element in the obj. */
  inline T* Start() { return TStackStart<T, SIZ>(AObj()); }

  /* Gets a pointer to the first element in the obj. */
  inline T* Stop() { return Start() + Count(); }

  /* Inserts the item into the obj at the given index.
  @return -1 if a is nil and -2 if the obj is full.
  @param item  The item to insert.
  @param index The index to insert at. */
  inline T Insert(T item, T index) {
    return AStack<T, SIZ>(AObj(), item, index);
  }

  /* Removes the given index from the obj.
  @return True if the index is out of bounds.
  @param  index The index the item to remove. */
  inline BOL Remove(SIZ index) { return TStackRemove<T, SIZ>(AObj(), index); }

  /* Adds the given item to the stop of the obj.
  @return The index of the newly stacked item.
  @param  item The item to push onto the obj. */
  inline SIZ Push(T item) { return TStackPush<T, SIZ>(Obj(), item); }

  /* Pops the top item off of the obj.
  @return The item popped off the obj. */
  inline T Pop() { return TStackPop<T, SIZ>(Obj()); }

  /* Peeks the top item off of the obj without popping it.
  @return The item popped off the obj. */
  inline T Peek() { return TStackPeek<T, SIZ>(AObj()); }

  /* Gets the element at the given index.
  @return -1 if a is nil and -2 if the index is out of bounds.
  @param  index The index of the element to get. */
  inline T Get(SIZ index) { return TStackGet<T, SIZ>(AObj(), index); }

  /* Returns true if the given obj contains the given address.
  @return false upon failure. */
  inline BOL Contains(void* address) {
    return TStackContains<T, SIZ>(AObj(), address);
  }

  /* Resizes the obj to the new_count.
  @return False upon failure. */
  inline BOL Resize(SIZ new_count) {
    return TStackResize<T, SIZ>(obj_, new_count);
  }

  /* Doubles the size of the obj.
  @return False upon failure. */
  inline BOL Grow() { return TStackGrow<T, SIZ>(obj_.CObj()); }

  /* Gets the ASCII Object. */
  inline SStack<SIZ>* Obj() {
    return reinterpret_cast<SStack<SIZ>*>(obj_.Begin());
  }

  /* Gets this AObject. */
  inline CObject& CObj() { return obj_.CObj(); }

  /* Gets this AObject. */
  inline AObject<SIZ, BUF>& AObj() { return obj_; }

  /* Prints this object to a Printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& utf) {
    return TStackPrint<Printer, T, SIZ>(utf, Obj());
  }

  /* Prints this object to the given UTF. */
  inline void COut() { PrintTo<::_::COut>(::_::COut().Star()); }

  /* Clones the other object. */
  inline AStack<T, SIZ>& operator[](const AStack<T, SIZ>& other) {
    Clone(other);
    return *this;
  }

  /* Clones the other object. */
  inline AStack<T, SIZ>& operator=(const AStack<T, SIZ>& other) {
    Clone(other);
    return *this;
  }

  /* Gets a reference to the given element index. */
  inline T& operator[](SIW index) { return Start()[index]; }

  /* Gets a const reference to the given element index. */
  inline const T& operator[](SIW index) const { return Start()[index]; }

 private:
  AObject<SIZ, BUF> obj_;  //< ASCII Object.

  static SI4 FactoryStack(CObject& obj, SIW function, void* arg) {
    return Factory(obj, function, arg, kStack);
  }

  static SI4 FactoryHeap(CObject& obj, SIW function, void* arg) {
    return Factory(obj, function, arg, kHeap);
  }

  /* Stack factory. */
  static SIN Factory(CObject& obj, SIW function, void* arg, BOL using_heap) {
    return TStackFactory<T, SIZ>(obj, function, arg, using_heap);
  }
};

}  // namespace _

#endif
#endif
