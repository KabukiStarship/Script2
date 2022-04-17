/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Stack.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#ifndef SCRIPT2_STACK_TEMPLATES
#define SCRIPT2_STACK_TEMPLATES
#if SEAM >= SCRIPT2_STACK
#include "Binary.hpp"
#include "String.hpp"
#if SEAM == SCRIPT2_STACK
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
namespace _ {

/* @ingroup AsciiStack */

/* ASCII Stack
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/vector_types/stack.md */

/* An Array Stack obj of homogeneous-sized plain-old-data (POD) types.
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/vector_types/stack.md

# Stack Memory Layout

@code
+---------------+
|    Buffer     |
|---------------|
| C-Style Array |
|---------------|  ^
|    Header     |  |
+---------------+ 0xN
@endcode
*/
template <typename ISZ = ISN>
struct TStack {
  ISZ count_max,  //< Size of the Array in elements.
      count;      //< Element count.
};

/* Gets the size of a Stack with the given count_max. */
template <typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSize(ISZ count_max) {
  enum { cCountMaxMin = sizeof(IUD) / sizeof(T) };
  if (count_max < cCountMaxMin) count_max = cCountMaxMin;
  return sizeof(TStack<ISZ>) + sizeof(T) * count_max;
}

/* Gets the min size of a Stack with zero elements. */
template <typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeMin() {
  enum {
    cStackCountMin = sizeof(T) > 8 ? 1 : 8 / sizeof(T),
    cStackCountMaxMin = sizeof(TStack<ISZ>) + sizeof(T) * cStackCountMin,
  };
  return cStackCountMaxMin;
}

/* Gets the max number_ of elements in an obj with the specific index
width. */
template <typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeMax() {
  return (ISZ)((((~(ISZ)0) - cWordLSbMask) - (ISZ)sizeof(TStack<ISZ>)) /
               (ISZ)sizeof(T));
}

/*
template<typename T = ISW, typename ISZ = ISN>
ISZ StackCountMax () {
    return (ISZ)((UnsignedMax<ISZ> () - (ISZ)sizeof (TStack<T, ISZ,
ISZ>)) / (ISZ)sizeof (T));
}*/

/* The minimum obj size. */
template <typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeMin(ISZ count_max) {
  ISZ count_upper_bounds = TStackSizeMax<T, ISZ>();
  if (count_max > count_upper_bounds) count_max = count_upper_bounds;
  return (ISZ)(sizeof(TStack<ISZ>) + count_max * sizeof(T));
}

template <typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeOf(ISZ count) {
  return count * sizeof(T) + sizeof(TStack<ISZ>);
}

/* Initializes an obj from a preallocated socket who's size is a multiple of
8 bytes.
@param socket An obj of bytes large enough to fit the obj.
@return A dynamically allocated socket. */
template <typename T = ISW, typename ISZ = ISN>
TStack<ISZ>* TStackInit(TStack<ISZ>* stack, ISZ size) {
  if (!stack || size < 0) return nullptr;
  D_ARRAY_WIPE(stack, ISW(TStackSizeOf<T, ISZ>(size)));
  stack->count_max = size;
  stack->count = 0;
  return stack;
}

/* Initializes an obj from a preallocated socket who's size is a multiple of
8 bytes.
@param socket An obj of bytes large enough to fit the obj.
@return A dynamically allocated socket. */
template <typename T = ISW, typename ISZ = ISN>
TStack<ISZ>* TStackInit(TStack<ISZ>* stack, ISZ size, const T* items,
                        ISZ count) {
  if (!stack || !items || size <= 0 || count < 0) return nullptr;
  D_ARRAY_WIPE(stack, ISW(TStackSizeOf<T, ISZ>(size)));

  stack->count_max = size;
  stack->count = 0;
  return stack;
}

/* Returns the first element in the Stack TMatrix. */
template <typename T = ISW, typename ISZ = ISN>
T* TStackStart(TStack<ISZ>* stack) {
  return TArrayStart<TStack<ISZ>, T>(stack);
}

/* Returns the last element of the stack. */
template <typename T = ISW, typename ISZ = ISN, typename Type = T>
inline Type TStackEnd(TStack<ISZ>* stack) {
  return reinterpret_cast<Type>(TStackStart<T, ISZ>(stack) + stack->count);
}

/* Returns the first empty element of the stack. */
template <typename T = ISW, typename ISZ = ISN>
inline T* TStackTop(TStack<ISZ>* stack) {
  return &TStackStart<T, ISZ>(stack)[stack->count];
}

/* Prints the given obj to the console. */
template <typename Printer, typename T = ISW, typename ISZ = ISN>
Printer& TStackPrint(Printer& o, TStack<ISZ>* stack) {
  D_ASSERT(stack);
  ISZ size = stack->count_max, count = stack->count;
  o << Linef("\n+---\n| TStack<T") << sizeof(T) << ",IS"
    << CHA('0' + sizeof(ISZ)) << ">: size_bytes:" << TStackSizeOf<T, ISZ>(size)
    << " size: " << size << " count:" << count << Linef("\n+---");

  T* elements = TStackStart<T, ISZ>(stack);
  for (ISC i = 0; i < count; ++i) o << "\n| " << i << ".) " << elements[i];
  if (count == 0) o << "\n| Empty";
#if D_THIS
  ISZ size_bytes = TStackSizeOf<T, ISZ>(stack->count_max);
  return o << Linef("\n+---") << Charsf(stack, size_bytes) << '\n';
#else
  return o;
#endif
}

/* Returns the other Stack to the preallocated stack's buffer.
@return An autoject buffer. */
template <typename T = ISW, typename ISZ = ISN>
IUW* TStackClone(TStack<ISZ>* stack, ISZ count_max, TStack<ISZ>* other,
                 ISZ other_count_max, ISZ other_count) {
  if (count_max < other_count_max) return nullptr;
  IUW *source = TPtr<IUW>(stack), *destination = TPtr<IUW>(stack);
  ISZ word_count =
      (stack->count * sizeof(T) + sizeof(TStack<ISZ>)) >> cWordBitCount;
  size -= word_count;
  while (word_count-- > 0) *destination++ = *source++;
  return reinterpret_cast<IUW*>(stack);
}

/* Returns the other Stack to the preallocated stack's buffer.
@return An autoject buffer. */
template <typename T = ISW, typename ISZ = ISN>
inline IUW* TStackClone(TStack<ISZ>* stack, TStack<ISZ>* other) {
  A_ASSERT(stack);
  return TStackClone<T, ISZ>(stack, other, stack->count);
}

/* Returns a clone on the heap.
@return An autoject buffer. */
template <typename T = ISW, typename ISZ = ISN>
IUW* TStackClone(TStack<ISZ>* stack, SocketFactory socket_factory) {
  A_ASSERT(stack);
  ISZ size = stack->count_max;
  IUW* other_buffer = socket_factory(nullptr, size);
  IUW *source = reinterpret_cast<IUW*>(stack),  //
      *destination = other_buffer;
  ISZ data_amount =
      (stack->count * sizeof(T) + sizeof(TStack<ISZ>)) >> cWordBitCount;
  size -= data_amount;
  while (data_amount-- > 0) *destination++ = *source++;
  return destination;
}

/* Clones the other ASCII Autoject including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename T = IUA, typename ISZ = ISN>
IUW* TStackClone(Autoject& obj) {
  SocketFactory factory = obj.socket_factory;
  IUW* origin = obj.origin;
  if (!factory || !origin) return nullptr;

  TStack<ISZ>* o = reinterpret_cast<TStack<ISZ>*>(origin);
  ISZ count = o->count;
  IUW* clone = TArrayNew<T, ISZ, TStack<ISZ>>(count);
  ISW size_bytes = (ISW)TStackSizeOf<T, ISZ>(count);
  if (!ArrayCopy(clone, count, origin, size_bytes)) return nullptr;
  TSizeSet<ISZ>(origin, count);
  return clone;
}

/* Doubles the size of the stack.
@return Returns nil if the size is greater than the amount of memory that
can fit in type ISW, the unaltered socket pointer if the Stack has grown to the
size upper bounds, or a new dynamically allocated socket upon failure. */
template <typename T = ISW, typename ISZ = ISN>
BOL TStackGrow(Autoject& obj) {
  TStack<ISZ>* stack = reinterpret_cast<TStack<ISZ>*>(obj.origin);
  A_ASSERT(stack);
#if D_THIS
  D_COUT("\nAuto-growing Stack...\nBefore:");
  TStackPrint<COut, T, ISZ>(COut().Star(), stack);
#endif
  ISZ size = stack->count_max;
  if (!TCanGrow<ISZ>(size)) return false;
  ISW size_bytes = TStackSizeOf<T, ISZ>(stack->count);
  size = size << 1;
  ISZ new_size_bytes = TStackSizeOf<T, ISZ>(size);
  IUW* new_begin = obj.socket_factory(nullptr, new_size_bytes);
  TStack<ISZ>* other = reinterpret_cast<TStack<ISZ>*>(new_begin);
  other->count_max = size;
  other->count = stack->count;
  D_COUT(" copying data...");
  ArrayCopy(TStackStart<T, ISZ>(other), size_bytes, TStackStart<T, ISZ>(stack),
            size_bytes);
  obj.origin = new_begin;
#if D_THIS
  D_COUT("\nResult:");
  TStackPrint<COut, T, ISZ>(COut().Star(), other);
#endif
  return true;
}

/* Attempts to resize the given Autoject to the new_count.
@return Nil upon failure. */
template <typename T = ISW, typename ISZ = ISN>
BOL TStackResize(Autoject& obj, ISZ new_count) {
  TStack<ISZ> stack = *reinterpret_cast<TStack<ISZ>*>(obj.origin);
  ISZ count = stack.count, count_max = TStackSizeMax<T, ISZ>();
  if (count > count_max || count == new_count) return false;
}

/* Checks if the given index exists in the stack. */
template <typename T = ISW, typename ISZ = ISN>
BOL TStackInBounds(TStack<ISZ>* stack, ISZ index) {
  return index >= 0 && index < stack->count_max;
}

/* Gets the element at the given index.
@param obj    The obj.
@param index The index of the element to get.
@return -1 if a is nil and -2 if the index is out of bounds. */
template <typename T = ISW, typename ISZ = ISN>
T TStackGet(TStack<ISZ>* stack, ISZ index) {
  A_ASSERT(stack);
  if (index < 0 || index >= stack->count) return 0;
  return TStackStart<T, ISZ>(stack)[index];
}

/* Peeks at the top item on the stack without popping it off.
@param stack The base address of the stack.
@return The item popped off the obj. */
template <typename T = ISW, typename ISZ = ISN>
T TStackPeek(TStack<ISZ>* stack) {
  A_ASSERT(stack);
  ISZ count = stack->count;
  if (count == 0) return 0;
  T* items = TStackStart<T, ISZ>(stack);
  T item = items[stack->count - 1];
  return item;
}

/* Inserts the given item at the start stack.
@pre You must perform bounds checking before calling this function. */
template <typename T>
inline void TStackInsert(T* elements, T* elements_end, T item) {
  while (elements_end > elements) {
    *elements_end = *(elements_end - 1);
    --elements_end;
  }
  *elements = item;
}
/* Inserts the given item at the index index the elements of the given count.
@pre You must perform bounds checking before calling this function. */
template <typename T, typename ISZ = ISM>
inline void TStackInsert(T* items, ISZ count, ISZ index, T item) {
  TStackInsert<T>(items + index, items + count, item);
}

/* Adds the given item to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param stack The Ascii Object base poiner.
@param item  The item to push onto the obj. */
template <typename T = ISW, typename ISZ = ISN>
ISZ TStackInsert(TStack<ISZ>* stack, T item, ISZ index = cPush) {
  D_ASSERT(stack);
  ISZ size = stack->count_max, count = stack->count;
  if (count >= size) return cErrorStackOverflow;
  if (index < 0) index = (count == 0) ? 0 : count - 1;
  D_COUT("  Pushing:" << item << " size:" << size << " count:" << count);
  D_COUT("\n| Before:" << Charsf(stack, TStackSizeOf<T, ISZ>(size)));

  T* elements = TStackStart<T, ISZ>(stack);
  elements[count++] = item;
  stack->count = count;
  D_COUT("\n| After:" << Charsf(stack, TStackSizeOf<T, ISZ>(size)));
  return count - 1;
}

/* Adds the given item to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param stack The Ascii Object base poiner.
@param item  The item to push onto the obj. */
template <typename T = ISW, typename ISZ = ISN, typename BUF = Nil>
ISZ TStackInsert(AArray<T, ISZ, BUF>& obj, T item, ISZ index = cPush) {
  TStack<ISZ>* stack = obj.OriginAs<TStack<ISZ>*>();
Insert:
  index = TStackInsert<T, ISZ>(stack, item, index);
  if (index < 0) {
    if (index == cErrorBufferOverflow) return index;
    D_COUT("\nStack overflow! Autogrowing...");
    TStackGrow<T, ISZ>(obj.AJT());
    stack = obj.OriginAs<TStack<ISZ>*>();
    goto Insert;
  }
  return index;
}

/* Adds the given items to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param stack The Ascii Object base poiner.
@param items  The  items to push onto the obj.
@param items_count The number of items to push. */
template <typename T = ISW, typename ISZ = ISN, typename BUF = Nil>
ISZ TStackInsert(AArray<T, ISZ, BUF>& obj, const T* items, ISZ items_count) {
  D_ASSERT(items);
  D_ASSERT(items_count >= 0);
  D_COUT("\nPushing " << items_count << " items:");
  ISZ count = obj->count;
  for (ISN i = 0; i < count; ++i) TStackInsert<T, ISZ>(obj, items[i]);
  return 0;
}

/* Pops the top item off of the obj.
@note We do not delete the item at the
@param a The obj.
@return The item popped off the obj. */
template <typename T = ISW, typename ISZ = ISN>
T TStackPop(TStack<ISZ>* stack) {
  A_ASSERT(stack);
  ISZ count = stack->count;
  if (count == 0) return 0;
  T* items = TStackStart<T, ISZ>(stack);
  stack->count = count - 1;
  T item = items[count - 1];
  return item;
}

/* Shifts the elements down starting at the index element and deletes the index
 * element at the given index.
@pre You must perform bounds checking before calling this function. */
template <typename T>
void TStackRemoveStart(T* elements, T* end) {
  while (elements < end) {
    *elements = *(elements + 1);
    ++elements;
  }
}

/* Shifts the elements down starting at the index element and deletes the index
 * element at the given index.
@pre You must perform bounds checking before calling this function. */
template <typename T>
void TStackRemove(T* elements, ISW element_number, ISW element_count) {
  return TStackRemoveStart<T>(elements + element_number,
                              elements + element_count);
}

/* Removes an element from the given array.
@return The new count of the stack. */
template <typename T = ISW, typename ISZ = ISN>
inline ISZ TStackRemove(T* elements, ISZ count, ISZ index) {
  A_ASSERT(elements);
  if (index < 0 || index >= count) return -1;
  elements += index;
  T* elements_end = elements + --count;
  while (elements <= elements_end) *elements++ = *elements;
  return count;
}

/* Removes the given index from the obj.
@param stack The Ascii Object base poiner.
@param index The index the item to remove.
@return True if the index is out of bounds. */
template <typename T = ISW, typename ISZ = ISN>
ISZ TStackRemove(TStack<ISZ>* stack, ISZ index) {
  A_ASSERT(stack);
  ISZ result =
      TStackRemove<T, ISZ>(TStackStart<T, ISZ>(stack), stack->count, index);
  if (result < 0) return result;
  stack->count = result;
  return result;
}

/* Returns true if the given obj contains the given address.
@return false upon failure. */
template <typename T = ISW, typename ISZ = ISN>
BOL TStackContains(TStack<ISZ>* stack, void* address) {
  A_ASSERT(stack);
  CHA *ptr = TPtr<CHA>(stack),
      *adr = TPtr<CHA>(address);
  if (adr < ptr) return false;
  if (adr >= ptr + stack->size_array) return false;
  return true;
}

/* The obj size in words. */
template <typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeWords(ISZ count) {
  return TStackSizeMin<T, ISZ>(count) / sizeof(IUW);
}

/* An ASCII Stack Autoject.
@see ASCII Data Type Specification.
@link ./Spec/Data/MapTypes/Table.md

@code
 Stack Memory Map
+----------------+
|  Packed Stack  |
|----------------|
|  Word Aligned  |
|     Buffer     |
|----------------|
| Stack Elements |
|----------------|  +
|  Stack struct  |  |
+----------------+ 0x0
@endcode
*/
template <typename T = ISW, typename ISZ = ISN,
          ISZ cSize_ = cStackCountMaxDefault,
          typename BUF = TBUF<cSize_, T, ISZ, TStack<ISZ>>>
class AStack {
  AArray<T, ISZ, BUF> obj_;  //< An Auto-Array.

  constexpr SocketFactory InitRamFactory() {
    return sizeof(BUF) == 0 ? TRamFactory<ISZ>::StackHeap
                            : TRamFactory<ISZ>::StackStack;
  }

  inline SocketFactory InitRamFactory(SocketFactory factory) {
    return !factory ? InitRamFactory() : factory;
  }

 public:
  /* Initializes a stack of n elements to whatever can fit in the BUF. */
  AStack() {
    D_ARRAY_WIPE(Start(), SizeBytes() - sizeof(TStack<ISZ>));
    This()->count = 0;
  }

  /* Attempts to down-size the BUF or creates a dynamically allocated stack.
  @param size The number of elements in the Array. */
  AStack(ISZ stack_height) : obj_(TStackSize<T, ISZ>(stack_height)) {
    ISZ size_bytes = TStack<ISZ>(stack_height) - sizeof(ISZ);
    D_ARRAY_WIPE(Start(), SizeBytes() - sizeof(TStack<ISZ>));
  }

  /* Copies the items into the obj_.Buffer () with some additional
  empty_elements. */
  AStack(ISZ count_max, const T* items, ISZ items_count)
      : obj_(TStackSize<T, ISZ>(items_count)) {
    TStackInsert<T, ISZ>(This().AJT(), items, items_count);
  }

  /* Copies the items into the obj_.Buffer () with some additional
  empty_elements. */
  AStack(const T* items, ISZ items_count)
      : obj_(TStackSize<T, ISZ>(items_count)) {
    TStackInsert<T, ISZ>(obj_.AJT(), items, items_count);
  }

  /* Destructs nothing. */
  ~AStack() {}

  /* Creates a dynamically allocated clone. */
  inline IUW* TClone() { TStackClone<T, ISZ>(AJT()); }

  /* Clones the other object.
  @return true upon success and false upon failure. */
  inline BOL Clone(TStack<ISZ>* other) { TStackClone<T, ISZ>(AJT(), other); }

  /* Checks if the given index is a valid element.
  @return true if the index is in bounds. */
  inline BOL InBounds(ISZ index) {
    return TStackInBounds<T, ISZ>(obj_.OBJ(), index);
  }

  /* Gets the max number_ of elements in an obj with the specific index
  width. */
  inline ISZ SizeMax() { return TStackSizeMax<T, ISZ>(); }

  /* Gets the min size of the entire Stack, including header, in bytes. */
  inline ISZ SizeMin() { return TStackSizeMin<T, ISZ>(); }

  /* Gets the max elements that can fit in the stack buffer. */
  inline ISZ Height() { return This()->count_max; }

  /* Gets the count of the items on the obj. */
  inline ISZ Count() { return This()->count; }

  /* Gets the size of the entire Stack, including header, in bytes. */
  inline ISZ SizeBytes() { return TStackSizeOf<T, ISZ>(Height()); }

  /* Gets a pointer to the first element in the obj. */
  inline T* Start() { return TStackStart<T, ISZ>(This()); }

  /* Gets a pointer to the first element in the obj. */
  inline T* Stop() { return Start() + Count(); }

  /* Inserts the item into the obj at the given index.
  @return -1 if a is nil and -2 if the obj is full.
  @param item  The item to insert.
  @param index The index to insert at. */
  inline T Insert(T item, T index) {
    return AStack<T, ISZ>(AJT(), item, index);
  }
  /* Adds the given item to the stop of the obj.
  @return The index of the newly stacked item.
  @param item The item to push onto the obj. */
  inline ISZ Push(T item) { return TStackInsert<T, ISZ>(AJT(), item); }

  /* Adds the given item to the stop of the obj.
  @return The index of the newly stacked item.
  @param item The item to push onto the obj. */
  inline ISZ Push(T* item, ISZ item_count) {
    return TStackInsert<T, ISZ>(AJT(), item, item_count);
  }

  /* Pops the top item off of the obj.
  @return The item popped off the obj. */
  inline T Pop() { return TStackPop<T, ISZ>(This()); }

  /* Removes the given index from the obj.
  @return True if the index is out of bounds.
  @param index The index the item to remove. */
  inline BOL Remove(ISZ index) { return TStackRemove<T, ISZ>(This(), index); }

  /* Peeks the top item off of the obj without popping it.
  @return The item popped off the obj. */
  inline T Peek() { return TStackPeek<T, ISZ>(AJT()); }

  /* Gets the element at the given index.
  @return -1 if a is nil and -2 if the index is out of bounds.
  @param index The index of the element to get. */
  inline T Get(ISZ index) { return TStackGet<T, ISZ>(AJT(), index); }

  /* Returns true if the given obj contains the given address.
  @return false upon failure. */
  inline BOL Contains(void* address) {
    return TStackContains<T, ISZ>(AJT(), address);
  }

  /* Resizes the obj to the new_count.
  @return False upon failure. */
  inline BOL Resize(ISZ new_count) {
    return TStackResize<T, ISZ>(obj_, new_count);
  }

  /* Doubles the size of the obj.
  @return False upon failure. */
  inline BOL Grow() { return TStackGrow<T, ISZ>(obj_.AJT()); }

  /* Gets this ASCII Object. */
  inline TStack<ISZ>* This() {
    return reinterpret_cast<TStack<ISZ>*>(obj_.Origin());
  }

  /* Gets this AArray. */
  inline AArray<T, ISZ, BUF>& AJT() { return obj_; }

  /* Prints this object to a Printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TStackPrint<Printer, T, ISZ>(o, This());
  }

  /* Prints this object to the given UTF. */
  inline void CPrint() { PrintTo<_::COut>(_::COut().Star()); }

  /* Gets a reference to the given element index. */
  inline T& operator[](ISZ index) { return Start()[index]; }

  /* Gets a const reference to the given element index. */
  inline const T& operator[](ISZ index) const { return Start()[index]; }
};  //< namespace _

}  //< namespace _

template <typename T = ISW, typename ISZ = ISN, typename BUF = _::Nil>
_::AArray<T, ISZ, BUF>& operator<<(_::AArray<T, ISZ, BUF>& obj, T item) {
  obj.Push(item);
  return obj;
}

template <typename T = ISW, typename ISZ = ISN, typename BUF = _::Nil>
_::AArray<T, ISZ, BUF>& operator>>(T& item, _::AArray<T, ISZ, BUF>& obj) {
  item = obj.Pop();
  return obj;
}

#endif
#endif
