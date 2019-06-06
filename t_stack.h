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
#if SEAM >= SCRIPT2_SEAM_STACK
#ifndef SCRIPT2_TSTACK
#define SCRIPT2_TSTACK 1

#include "c_socket.h"
#include "t_array.h"
#include "t_strand.h"

#if SEAM == SCRIPT2_SEAM_STACK
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

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
 |  | TStack Header  |
0xN +----------------+
@endcode
*/
template <typename SIZ = SI4>
struct TStack {
  SIZ size,   //< Size of the Array in elements.
      count;  //< Element count.
};

/* Gets the size of a Stack with the given count_max. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackSize(SIZ count_max) {
  enum { kCountMaxMin = sizeof(UI8) / sizeof(T) };
  if (count_max < kCountMaxMin) count_max = kCountMaxMin;
  return sizeof(TStack<SIZ>) + sizeof(T) * count_max;
}

/* Gets the min size of a Stack with zero elements. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackSizeMin() {
  enum {
    kStackCountMin = sizeof(T) > 8 ? 1 : 8 / sizeof(T),
    kStackCountMaxMin = sizeof(TStack<SIZ>) + sizeof(T) * kStackCountMin,
  };
  return kStackCountMaxMin;
}

/* Gets the max number_ of elements in an obj with the specific index
width. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackSizeMax() {
  return (SIZ)((((~(SIZ)0) - 7) - (SIZ)sizeof(TStack<SIZ>)) / (SIZ)sizeof(T));
}

/*
template<typename T = SI4, typename SIZ = SI4>
SIZ StackCountMax () {
    return (SIZ)((UnsignedMax<SIZ> () - (SIZ)sizeof (TStack<T, SIZ,
SIZ>)) / (SIZ)sizeof (T));
}*/

/* The minimum obj size. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackSizeMin(SIZ count_max) {
  SIZ count_upper_bounds = TStackSizeMax<T, SIZ>();
  if (count_max > count_upper_bounds) count_max = count_upper_bounds;
  return (SIZ)(sizeof(TStack<SIZ>) + count_max * sizeof(T));
}

/* Rounds up the count to the 64-bit align the value. */
template <typename T = SI4, typename SIZ = SI4>
inline SIZ TStackSizeMax(SIZ count_max) {
  enum {
    kStackCountMax =
        (TUnsignedMax<SIZ>() - (SIZ)sizeof(TStack<SIZ>)) / (SIZ)sizeof(T),
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
TStack<SIZ>* TStackInit(TStack<SIZ>* stack, SIZ count_max) {
  DASSERT(stack);
  DASSERT(count_max < sizeof(TStack<SIZ>)) return nullptr;
  stack->size = count_max;
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
  DASSERT(size > sizeof(TStack<SI4>));

  if (!items || count < 0) return nullptr;

  TStack<SIZ>* stack = reinterpret_cast<TStack<SIZ>*>(socket);
  stack->size_stack = size;
  stack->size = (size - sizeof(TStack<SIZ>)) >> kWordBitCount;
  stack->count = 0;
  return socket;
}

template <typename T = SI4, typename SIZ = SI4>
UIW* TStackClone(TStack<SIZ>* stack) {
  ASSERT(stack);
  SIZ size = stack->size_stack >> kWordBitCount;
  UIW other_buffer = new UIW[size];
  UIW *source = reinterpret_cast<UIW*>(stack), *destination = other_buffer;
  SIZ data_amount =
      (stack->count * sizeof(T) + sizeof(TStack<SIZ>)) >> kWordBitCount;
  size -= data_amount;
  while (data_amount-- > 0) *destination++ = *source++;
  return destination;
}

/* Clones the given obj. */
template <typename T = SI4, typename SIZ = SI4>
UIW* TStackClone(TStack<SIZ>* stack, TStack<SIZ>* other) {
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

/* Returns the first element in the Stack TMatrix. */
template <typename T = SI4, typename SIZ = SI4>
T* TStackStart(TStack<SIZ>* stack) {
  return reinterpret_cast<T*>(reinterpret_cast<UIW>(stack) +
                              sizeof(TStack<SIZ>));
}

/* Returns the last element of the stack. */
template <typename T = SI4, typename SIZ = SI4>
inline T* TStackStop(TStack<SIZ>* stack) {
  return TStackStart<T, SIZ>(stack) + stack->count - 1;
}

/* Returns the first empty element of the stack. */
template <typename T = SI4, typename SIZ = SI4>
inline T* TStackCursor(TStack<SIZ>* stack) {
  return TStackStart<T, SIZ>(stack) + stack->count;
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
T TStackAdd (TStack<SIZ>* obj, T item, T index) {
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
SIZ TStackRemove(TStack<SIZ>* stack, SIZ index) {
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
@return The index of the newly stacked item or -1 upon failure. */
template <typename T = SI4, typename SIZ = SI4>
SIZ TStackPush(TStack<SIZ>* stack, T item) {
  ASSERT(stack);
  SIZ size = stack->size, count = stack->count;
  if (count >= size) return -1;
  T* items = TStackStart<T, SIZ>(stack);
  items[count] = item;
  stack->count = count + 1;
  return count;
}

/* Adds the given items to the stop of the obj.
@param  stack The Ascii Object base poiner.
@param  items  The  items to push onto the obj.
@param  items_count The number of items to push.
@return The index of the newly stacked item or -1 upon failure. */
template <typename T = SI4, typename SIZ = SI4>
SIZ TStackPush(TStack<SIZ>* stack, const T* items, SIZ items_count) {
  DASSERT(items);
  DASSERT(count >= 0);
  SIZ count = stack->count, count_max = stack->size;
  if (count_max - count < count) return -1;
  T* cursor = TStackTop<T, SIZ>(stack);
  while (count-- > 0) *cursor++ = *items++;
  return 0;
}

/* Pops the top item off of the obj.
@note We do not delete the item at the
@param  a The obj.
@return The item popped off the obj. */
template <typename T = SI4, typename SIZ = SI4>
T TStackPop(TStack<SIZ>* stack) {
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
T TStackPeek(TStack<SIZ>* stack) {
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
T TStackGet(TStack<SIZ>* stack, SIZ index) {
  ASSERT(stack);
  if (index >= stack->count) return 0;
  CH1* address = reinterpret_cast<CH1*>(stack) + sizeof(TStack<SIZ>);
  return reinterpret_cast<T*>(address)[index];
}

/* Returns true if the given obj contains the given address.
@return false upon failure. */
template <typename T = SI4, typename SIZ = SI4>
BOL TStackContains(TStack<SIZ>* stack, void* address) {
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
  return (SIZ)((((~(SIZ)0) - 7) - (SIZ)sizeof(TStack<SIZ>)) / (SIZ)sizeof(T));
}

/* Doubles the size of the array until the max count is reached.
@return Returns nil if the count_max is greater than the amount of memory that
can fit in type SIZ, the unaltered socket pointer if the Stack has grown to the
count_max upper bounds, or a new dynamically allocated socket upon failure. */
template <typename T = SI4, typename SIZ = SI4>
BOL TStackGrow(Autoject& obj) {
  static SIZ count_max_auto_size_init = kStackCountMaxDefault;

  UIW* socket = obj.begin;

  ASSERT(socket);

  TStack<SIZ>* stack = reinterpret_cast<TStack<SIZ>*>(socket);
  SIZ count_max = stack->size,
      count_uppoer_bounds = TStackCountUpperBounds<T, SIZ>();
  if (count_max > count_uppoer_bounds || count_max >= count_uppoer_bounds)
    return false;
  count_max += count_max;
  if (count_max > count_uppoer_bounds) count_max = count_uppoer_bounds;
  SIZ new_size = sizeof(TStack<SIZ>) + count_max * sizeof(T);
  new_size = TAlignUpSigned<SIZ>(new_size, 7);
  UIW* new_buffer = new UIW[new_size >> kWordBitCount];
  TStack<SIZ>* new_stack = reinterpret_cast<TStack<SIZ>*>(new_buffer);
  new_stack->size_array = 0;
  new_stack->size_stack = new_size;
  SIZ count = stack->count;
  new_stack->count = count;
  new_stack->size = count_max;

  T *source = TStackStart(stack), *destination = TStackStart(new_stack);
  for (; count > 0; count--) *destination++ = *source++;
  AsciiFactory factory = obj.factory;
  if (factory) factory(obj, kFactoryDelete, nullptr);
  return true;
}

/* Attempts to resize the given Autoject to the new_count.
@return Nil upon failure. */
template <typename T = SI4, typename SIZ = SI4>
BOL TStackResize(Autoject& obj, SIZ new_count) {
  TStack<SIZ> stack = *reinterpret_cast<TStack<SIZ>*>(obj.begin);
  SIZ count = obj.count, count_max = TStackSizeMax<T, SIZ>();
  if (count > count_max || count == new_count) return false;
}

template <typename T = SI4, typename SIZ = SI4>
BOL TStackInBounds(TStack<SIZ>* stack, SIZ index) {
  return index >= 0 && index < stack->size;
}

/* Prints the given obj to the console. */
template <typename Printer, typename T = SI4, typename SIZ = SI4>
Printer& TStackPrint(Printer& o, TStack<SIZ>* stack) {
  DASSERT(stack);
  SIZ size = stack->size, count = stack->count;
  o << "\n\nStack: count: " << count << " size:" << size;

  T* elements = TStackStart(stack);
  for (SI4 i = 0; i < count; ++i) o << kLF << i + 1 << ", " << elements[i];

  return o;
}

template <typename T, typename SIZ>
void* TStackFactory(Autoject& obj, SIW function, void* arg, BOL using_heap) {
  SI4 size;
  switch (function) {
    case kFactoryDelete: {
      PRINT("\nEntering Strand.Factory.Delete:");
      return Delete(obj, using_heap);
    }
    case kFactoryNew: {
      PRINTF("\nEntering Stack.Factory.%s.New:", using_heap ? "Heap" : "Stack");
      return New(reinterpret_cast<SIW>(arg));
    }
    case kFactoryGrow: {
      PRINT("\nEntering Strand.Factory.Grow:");
      if (!arg) return kFactoryNilArg;
      UIW *begin = obj.begin, *new_begin = TArrayGrowDouble<SI4>(begin);
      if (!new_begin) return kFactoryCantGrow;

      TUTF<Char> new_utf(new_begin);
      PRINTF(" new size:%i", (SIN)TSize<SIZ>(new_begin));
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
      Autoject* other = reinterpret_cast<Autoject*>(arg);
      UIW* begin = obj.begin;
      UIW* obj = TArrayClone<SI4>(obj);
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

static void* TStackFactoryStack(Autoject& obj, SIW function, void* arg) {
  return Factory(obj, function, arg, kStack);
}

/* Heap factory function. */
static void* TStackFactoryHeap(Autoject& obj, SIW function, void* arg) {
  return Factory(obj, function, arg, kHeap);
}

/* An ASCII Stack with an AsciiFactory.

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
  @param size The number of elements in the Array. */
  AStack(SIZ size = 1) : obj_(TStackSize<T, SIZ>(size)) {}

  /* Copies the items into the obj_.Buffer () with some additional
  empty_elements. */
  AStack(SIZ count_max, const T* items, SIZ items_count)
      : obj_(TStackSize<T, SIZ>(items_count + empty_elements)) {
    TStackPush<T, SIZ>(items, items_count);
  }

  /* Copies the items into the obj_.Buffer () with some additional
  empty_elements. */
  AStack(const T* items, SIZ items_count)
      : obj_(TStackSize<T, SIZ>(items_count)) {
    TStackPush<T, SIZ>(items, items_count);
  }

  /* Copy constructor. */
  AStack(const AStack& other) : obj_(other.OBJ(), other.Factory()) {}

  /* Destructs nothing. */
  ~AStack() {}

  /* Creates a dynamically allocated clone. */
  AStack<T, SIZ>& Clone() { TStackClone<T, SIZ>(OBJ()); }

  /* Clones the other object. */
  AStack<T, SIZ>& Clone(AStack<T, SIZ>& other) {
    TStackClone<T, SIZ>(OBJ(), *other);
  }

  /* Checks if the given index is a valid element.
  @return true if the index is in bounds. */
  inline BOL InBounds(SIZ index) {
    return TStackInBounds<T, SIZ>(obj_.OBJ(), index);
  }

  /* Gets the size of the entire Stack, including header, in bytes. */
  inline SIZ SizeBytes() { return OBJ()->SizeBytes(); }

  /* Gets the max number_ of elements in an obj with the specific index
  width. */
  inline SIZ SizeMax() { return TStackSizeMax<T, SIZ>(); }

  /* Gets the min size of the entire Stack, including header, in bytes. */
  inline SIZ SizeMin() { return TStackSizeMin<T, SIZ>(); }

  /* Gets the count of the items on the obj. */
  inline SIZ Count() { return Obj().count; }

  /* Gets a pointer to the first element in the obj. */
  inline T* Start() { return TStackStart<T, SIZ>(OBJ()); }

  /* Gets a pointer to the first element in the obj. */
  inline T* Stop() { return Start() + Count(); }

  /* Inserts the item into the obj at the given index.
  @return -1 if a is nil and -2 if the obj is full.
  @param item  The item to insert.
  @param index The index to insert at. */
  inline T Insert(T item, T index) {
    return AStack<T, SIZ>(OBJ(), item, index);
  }

  /* Removes the given index from the obj.
  @return True if the index is out of bounds.
  @param  index The index the item to remove. */
  inline BOL Remove(SIZ index) { return TStackRemove<T, SIZ>(OBJ(), index); }

  /* Adds the given item to the stop of the obj.
  @return The index of the newly stacked item.
  @param  item The item to push onto the obj. */
  inline SIZ Push(T item) { return TStackPush<T, SIZ>(Obj(), item); }

  /* Pops the top item off of the obj.
  @return The item popped off the obj. */
  inline T Pop() { return TStackPop<T, SIZ>(Obj()); }

  /* Peeks the top item off of the obj without popping it.
  @return The item popped off the obj. */
  inline T Peek() { return TStackPeek<T, SIZ>(OBJ()); }

  /* Gets the element at the given index.
  @return -1 if a is nil and -2 if the index is out of bounds.
  @param  index The index of the element to get. */
  inline T Get(SIZ index) { return TStackGet<T, SIZ>(OBJ(), index); }

  /* Returns true if the given obj contains the given address.
  @return false upon failure. */
  inline BOL Contains(void* address) {
    return TStackContains<T, SIZ>(OBJ(), address);
  }

  /* Resizes the obj to the new_count.
  @return False upon failure. */
  inline BOL Resize(SIZ new_count) {
    return TStackResize<T, SIZ>(obj_, new_count);
  }

  /* Doubles the size of the obj.
  @return False upon failure. */
  inline BOL Grow() { return TStackGrow<T, SIZ>(obj_.AObj()); }

  /* Gets the ASCII Object. */
  inline TStack<SIZ>* Obj() {
    return reinterpret_cast<TStack<SIZ>*>(obj_.Begin());
  }

  /* Gets this AArray. */
  inline Autoject& AObj() { return obj_.AObj(); }

  /* Gets this AArray. */
  inline AArray<T, SIZ, BUF>& OBJ() { return obj_; }

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
  AArray<T, SIZ, BUF> obj_;  //< AArray.

  /* Stack factory function. */
  static SIW Factory(Autoject& obj, SIW function, void* arg, BOL using_heap) {
    return TStackFactory<T, SIZ>(obj, function, arg, using_heap);
  }

  static constexpr AsciiFactory Factory() {
    return obj_.HasBuffer() ? FactoryStack : FactoryHeap;
  }
};

}  // namespace _

template <typename T = SI4, typename SIZ = SI4, typename BUF = Nil>
::_::AArray<T, SIZ, BUF>& operator<<(::_::AArray<T, SIZ, BUF>& obj, T item) {
  obj.Push(item);
  return obj;
}

template <typename T = SI4, typename SIZ = SI4, typename BUF = Nil>
::_::AArray<T, SIZ, BUF>& operator>>(T& item, ::_::AArray<T, SIZ, BUF>& obj) {
  item = obj.Pop();
  return obj;
}

#endif
#endif
