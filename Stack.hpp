/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Stack.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
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
#define SCK_A typename ISZ
#define SCK_P ISZ
namespace _ {

/* @ingroup AsciiStack */

/* ASCII Stack
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/MapTypes/Stack.md */

/* An Array Stack obj of homogeneous-sized plain-old-data (POD) types.
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/MapTypes/Stack.md

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
template<typename ISZ = ISN>
struct TStack {
  ISZ count_max,  //< Size of the Array in elements.
      count;      //< Element count.
};

/* Returns the first element in the Stack TMatrix. */
template<typename T = ISW, typename ISZ = ISN>
inline const T* TStackStart(const TStack<ISZ>* stack) {
  return TPtr<T>(TPtr<IUA>(stack) + sizeof(TStack<ISZ>));
}

/* Returns the first element in the Stack TMatrix. */
template<typename T = ISW, typename ISZ = ISN>
inline T* TStackStart(TStack<ISZ>* stack) {
  return CPtr<T>(TStackStart<T, ISZ>(CPtr<TStack<ISZ>>(stack)));
}

/* Returns the first empty element of the stack. */
template<typename T = ISW, typename ISZ = ISN>
inline const T* TStackTop(const TStack<ISZ>* stack) {
  return TStackStart<T, ISZ>(stack) + stack->count;
}

/* Returns the first empty element of the stack. */
template<typename T = ISW, typename ISZ = ISN>
inline T* TStackTop(TStack<ISZ>* stack) {
  return CPtr<T>(TStackStart<T, ISZ>(CPtr<TStack<ISZ>>(stack))) + 
         stack->count;
}

template<typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeOf(ISZ count) {
  return count * sizeof(T) + sizeof(TStack<ISZ>);
}

/* Prints the given obj to the console. */
template<typename Printer, typename T = ISW, typename ISZ = ISN>
Printer& TStackPrint(Printer& o, const TStack<ISZ>* stack) {
  ISZ count_max = stack->count_max, count = stack->count;
  o << Linef("\n+---\n| TStack<T") << CHA('@' + sizeof(T)) << ",ISZ"
    << CHA('@' + sizeof(ISZ))
    << ">: size_bytes:" << TStackSizeOf<T, ISZ>(count_max)
    << " count_max: " << count_max << " count:" << count << Linef("\n+---");

  const T* elements = TStackStart<T, ISZ>(stack);
  for (ISC i = 0; i < count; ++i) o << "\n| " << i << ".) " << elements[i];
  if (count == 0) o << "\n| Empty";
#if D_THIS
  ISZ size_bytes = TStackSizeOf<T, ISZ>(stack->count_max);
  return o << Linef("\n+---") << Charsf(stack, size_bytes) << '\n';
#else
  return o;
#endif
}

/* Copies an ASCII Stack from the origin to the destination. */
template<typename T = ISW, typename ISZ = ISN>
inline CHA* TStackCopy(TStack<ISZ>* destination, const TStack<ISZ>* source) {
  return RAMCopy(destination, TStackTop<T, ISZ>(destination), source,
                   TStackTop<T, ISZ>(source));
}

/* Copies an ASCII Stack from the origin to the destination. */
template<typename T = ISW, typename ISZ = ISN>
inline CHA* TStackCopy(TStack<ISZ>* destination, ISZ destination_size,
                       const TStack<ISZ>* source) {
  return RAMCopy(destination, destination_size, source,
                   TStackTop<T, ISZ>(source));
}

// Calculates the size of a TStack<ISZ> in bytes based on the count.
template<typename T, typename ISZ = ISN, typename ISR=ISW>
inline ISR TStackSize(ISZ count) {
  return sizeof(TStack<ISZ>) + ISR(count) * sizeof(T);
}

// Utility to cast Autoject origin to TStack<ISZ>*.
template<typename ISZ>
inline TStack<ISZ>* TStackPtr(IUW* boofer) {
  return TPtr<TStack<ISZ>>(boofer);
}

// Utility to cast Autoject origin to TStack<ISZ>*.
template<typename ISZ>
inline const TStack<ISZ>* TStackPtr(const IUW* boofer) {
  return TPtr<const TStack<ISZ>>(boofer);
}

// Utility to cast Autoject origin to TStack<ISZ>*.
template<typename ISZ>
inline TStack<ISZ>* TStackPtr(Autoject* adj) {
  return TPtr<TStack<ISZ>>(adj.origin);
}

// Utility to cast Autoject origin to TStack<ISZ>*.
template<typename ISZ = ISN>
inline TStack<ISZ>* TStackPtr(Autoject& ajt) {
  return TPtr<TStack<ISZ>>(ajt.origin);
}

/* Creates a new copy of the stack with the new size being the count_max + 
count_delta.
@return Returns nil if the clone cannot grow or shrink. */
template<typename T = ISW, typename ISZ = ISN>
TStack<ISZ>* TStackClone(Autoject& adj, ISZ count_delta) {
  auto stack = TStackPtr<ISZ>(adj);
  D_ASSERT(stack);
  ISZ count_max = stack->count_max;
  D_ASSERT(count_max >= 0);
#if D_THIS
  D_COUT("\nAuto-growing Stack...\nBefore:");
  TStackPrint<COut, T, ISZ>(StdOut(), stack);
#endif
  ISZ count_max_new = count_max + count_delta;
  if (count_max_new < 0) return nullptr;
  ISZ count = stack->count;
  ISZ count_new = count_max_new < count ? count_max_new : count;
  ISW size_old = TStackSize<T, ISZ>(count),
      size_new = TStackSize<T, ISZ>(count_max_new);
  TStack<ISZ>* stack_new = TStackPtr<ISZ>(adj.ram(nullptr, size_new));
  if(!stack_new) return stack_new;
  *stack_new = {count_max_new, count_new};
  D_COUT("\nCopying data..." <<
         "\nstack_new.count: " << stack_new->count <<
         "\nstack_new.count_max: " << stack_new->count_max <<
         "\nsize_old: " << size_old << 
         "\nsize_new: " << size_new <<
         "\nTStackStart<T, ISZ>(stack): " <<  Hexf(TStackStart<T, ISZ>(stack)));
  size_old -= sizeof(TStack<ISZ>);
  RAMCopy(TStackStart<T, ISZ>(stack_new), size_old,
            TStackStart<T, ISZ>(stack), size_old);
#if D_THIS
  D_COUT("\nResult:");
  TStackPrint<COut, T, ISZ>(StdOut(), stack_new);
#endif
  return stack_new;
}

/* Resizes the AutoStack by the given count delta and deletes the old boofer.
@return Nil if it's not possible to resize: either out of memory or negative 
new count_max. */
template<typename T = ISW, typename ISZ = ISN>
TStack<ISZ>* TStackResize(Autoject& adj, ISZ count_delta) {
  auto stack_new = TStackClone<T, ISZ>(adj, count_delta);
  if (!stack_new) return stack_new;
  adj.ram(adj.origin, 0);
  adj.origin = TPtr<IUW>(stack_new);
  return stack_new;
}

/* Doubles the AutoStack count_max and deletes the old boofer. */
template<typename T = ISW, typename ISZ = ISN>
TStack<ISZ>* TStackResize(Autoject& adj) {
  auto stack = TStackPtr<ISZ>(adj.origin);
  auto stack_new = TStackClone<T, ISZ>(adj, stack->count_max);
  if (!stack_new) return stack_new;
  adj.ram(adj.origin, 0);
  adj.origin = TPtr<IUW>(stack_new);
  return stack_new;
}

template<typename ISZ = ISN, typename DT = DTB, DT Type>
constexpr DT TStackType() {
  return (TBitCode<ISZ>() << ATypeVTBit0) | (_SCK << TBitCode<ISZ>()) | Type;
}

/* RAMFactoryStack function for the TStack. */
template<typename ISZ = ISN, typename DT = DTB, DT Type = _ISN>
IUW* TStackFactoryStack(IUW* origin, ISW size_bytes) {
  if (size_bytes <= 0) return TPtr<IUW>(TStackType<ISZ, DT, Type>());
  return RAMFactoryStack(origin, size_bytes);
}

/* RAMFactoryHeap function for the TStack. */
template<typename ISZ = ISN, typename DT = DTB, DT Type = _ISN>
IUW* TStackFactoryHeap(IUW* origin, ISW size_bytes) {
  if (size_bytes <= 0) return TPtr<IUW>(TStackType<ISZ, DT, Type>());
  return RAMFactoryHeap(origin, size_bytes);
}

/* Gets the size of a Stack with the given count_max. */
template<typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSize(ISZ count_max) {
  enum { CountMaxMin = sizeof(IUD) / sizeof(T) };
  if (count_max < CountMaxMin) count_max = CountMaxMin;
  return sizeof(TStack<ISZ>) + sizeof(T) * count_max;
}

/* Gets the min size of a Stack with zero elements. */
template<typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeMin() {
  enum {
    StackCountMin = sizeof(T) > 8 ? 1 : 8 / sizeof(T),
    StackCountMaxMin = sizeof(TStack<ISZ>) + sizeof(T) * StackCountMin,
  };
  return StackCountMaxMin;
}

/* Gets the max number_ of elements in an obj with the specific index
width. */
template<typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeMax() {
  return (ISZ)((((~(ISZ)0) - ALUAlignMask) - (ISZ)sizeof(TStack<ISZ>)) /
               (ISZ)sizeof(T));
}

/*
template<typename T = ISW, typename ISZ = ISN>
ISZ StackCountMax () {
    return (ISZ)((UnsignedMax<ISZ> () - (ISZ)sizeof (TStack<T, ISZ, ISZ>)) / (ISZ)sizeof (T));
}*/

/* The minimum obj size. */
template<typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeMin(ISZ count_max) {
  ISZ count_upper_bounds = TStackSizeMax<T, ISZ>();
  if (count_max > count_upper_bounds) count_max = count_upper_bounds;
  return (ISZ)(sizeof(TStack<ISZ>) + count_max * sizeof(T));
}

/* Initializes an obj from a preallocated socket who's size is a multiple of
8 bytes.
@param socket An obj of bytes large enough to fit the obj.
@return A dynamically allocated socket. */
template<typename T = ISW, typename ISZ = ISN>
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
template<typename T = ISW, typename ISZ = ISN>
TStack<ISZ>* TStackInit(TStack<ISZ>* stack, ISZ size, const T* items,
                        ISZ count) {
  if (!stack || !items || size <= 0 || count < 0) return nullptr;
  D_ARRAY_WIPE(stack, ISW(TStackSizeOf<T, ISZ>(size)));

  stack->count_max = size;
  stack->count = 0;
  return stack;
}

/* Returns the last element of the stack. */
template<typename T = ISW, typename ISZ = ISN, typename Type = T>
inline Type TStackEnd(TStack<ISZ>* stack) {
  return TPtr<Type>(TStackStart<T, ISZ>(stack) + stack->count);
}

/* Attempts to resize the given Autoject to the new_count.
@return Nil upon failure. */
template<typename T = ISW, typename ISZ = ISN>
BOL TStackResize(Autoject& obj, ISZ new_count) {
  TStack<ISZ> stack = *TPtr<TStack<ISZ>>(obj.origin);
  ISZ count = stack.count, count_max = TStackSizeMax<T, ISZ>();
  if (count > count_max || count == new_count) return false;
}

/* Checks if the given index exists in the stack. */
template<typename T = ISW, typename ISZ = ISN>
BOL TStackInBounds(TStack<ISZ>* stack, ISZ index) {
  return index >= 0 && index < stack->count_max;
}

/* Gets the element at the given index.
@param obj    The obj.
@param index The index of the element to get.
@return -1 if a is nil and -2 if the index is out of bounds. */
template<typename T = ISW, typename ISZ = ISN>
T TStackGet(TStack<ISZ>* stack, ISZ index) {
  A_ASSERT(stack);
  if (index < 0 || index >= stack->count) return 0;
  return TStackStart<T, ISZ>(stack)[index];
}

/* Peeks at the top item on the stack without popping it off.
@param stack The base address of the stack.
@return The item popped off the obj. */
template<typename T = ISW, typename ISZ = ISN>
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
template<typename T>
inline void TStackInsert(T* items_start, T* items_end, T item) {
  --items_end;
  while (items_start < items_end) *items_end-- = *items_end;
  *items_start = item;
}

/* Inserts the given item at the start stack.
@pre You must perform bounds checking before calling this function. */
template<typename T, typename ISZ>
inline void TStackInsert(T* elements, ISZ count_max, T item) {
  return TStackInsert<T>(elements, elements + count_max, item);
}

/* Inserts the given item at the index index the elements of the given count.
@pre You must perform bounds checking before calling this function. */
template<typename T, typename ISZ = ISM>
inline void TStackInsert(T* items, ISZ count, ISZ index, T item) {
  TStackInsert<T>(items + index, items + count, item);
}

/* Adds the given item to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param stack The Ascii Object base poiner.
@param item  The item to push onto the obj. */
template<typename T = ISW, typename ISZ = ISN>
inline void TStackPushUnchecked(TStack<ISZ>* stack, T item, ISZ count) {
  TStackStart<T, ISZ>(stack)[count] = item;
  stack->count = count + 1;
}

/* Adds the given item to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param stack The Ascii Object base poiner.
@param item  The item to push onto the obj. */
template<typename T = ISW, typename ISZ = ISN>
ISZ TStackInsert(TStack<ISZ>* stack, T item, ISZ index = PSH) {
  D_ASSERT(stack);
  ISZ count     = stack->count,
     count_max = stack->count_max;
  if (count >= count_max) return -ErrorStackOverflow;
  if (index < 0) index = count;
  D_COUT("  Pushing:" << item << " count_max:" << count_max << " count:" << 
         count);
  D_COUT("\n| Before:" << Charsf(stack, TStackSizeOf<T, ISZ>(count_max)));
  TStackPushUnchecked<T, ISZ>(stack, item, count);
  D_COUT("\n| After:" << Charsf(stack, TStackSizeOf<T, ISZ>(count_max)));
  return count;
}

/* Adds the given item to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param stack The Ascii Object base poiner.
@param item  The item to push onto the obj. */
template<typename T = ISW, typename ISZ = ISN, typename BUF = Nil>
ISZ TStackInsert(AArray<T, ISZ, BUF>& obj, T item, ISZ index = PSH) {
  auto stack = obj.OriginAs<TStack<ISZ>*>();
Insert:
  ISZ result = TStackInsert<T, ISZ>(stack, item, index);
  if (result < 0) {
    //if (result == cErrorBufferOverflow) return index;
    D_COUT("\n\nStack overflow! index:" << index << " result:" << result << 
           " Autogrowing...");
    stack = TStackResize<T, ISZ>(obj.AJT());
    goto Insert;
  }
  return result;
}

/* Adds the given items to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param stack       The Ascii Object base poiner.
@param items       The  items to push onto the obj.
@param items_count The number of items to push. */
template<typename T = ISW, typename ISZ = ISN, typename BUF = Nil>
ISZ TStackInsert(AArray<T, ISZ, BUF>& obj, const T* items, ISZ items_count) {
  D_ASSERT(items);
  D_ASSERT(items_count >= 0);
  D_COUT("\nPushing " << items_count << " items:");
  ISZ count = obj->count;
  auto result = 0;
  for (ISN i = 0; i < count; ++i) {
    result = TStackInsert<T, ISZ>(obj, items[i]);
    if (result < 0) return result;
  }
  return result;
}

/* Pops the top item off of the obj.
@note We do not delete the item at the
@param a The obj.
@return The item popped off the obj. */
template<typename T = ISW, typename ISZ = ISN>
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
template<typename T>
void TStackRemoveStart(T* elements, T* end) {
  while (elements < end) {
    *elements = *(elements + 1);
    ++elements;
  }
}

/* Shifts the elements down starting at the index element and deletes the index
 * element at the given index.
@pre You must perform bounds checking before calling this function. */
template<typename T>
void TStackRemove(T* elements, ISW element_number, ISW element_count) {
  return TStackRemoveStart<T>(elements + element_number,
                              elements + element_count);
}

/* Removes an element from the given array.
@return The new count of the stack. */
template<typename T = ISW, typename ISZ = ISN>
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
template<typename T = ISW, typename ISZ = ISN>
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
template<typename T = ISW, typename ISZ = ISN>
BOL TStackContains(TStack<ISZ>* stack, void* address) {
  A_ASSERT(stack);
  CHA *ptr = TPtr<CHA>(stack),
      *adr = TPtr<CHA>(address);
  if (adr < ptr) return false;
  if (adr >= ptr + stack->size_array) return false;
  return true;
}

/* The obj size in words. */
template<typename T = ISW, typename ISZ = ISN>
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
template<typename T = ISW, typename ISZ = ISN,
          ISZ Size_ = AStackCountMaxDefault,
          typename BUF = TBUF<Size_, T, ISZ, TStack<ISZ>>>
class AStack {
  AArray<T, ISZ, BUF> obj_;  //< An Auto-Array.

  constexpr RAMFactory InitRamFactory() {
    return sizeof(BUF) == 0 ? TRAMFactory<ISZ>::StackHeap
                            : TRAMFactory<ISZ>::StackStack;
  }

  inline RAMFactory InitRamFactory(RAMFactory factory) {
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

  /* Gets the max elements that can fit in the stack boofer. */
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
    ISZ count = This()->count;
    return TStackResize<T, ISZ>(obj_, new_count - count);
  }

  /* Doubles the size of the obj.
  @return False upon failure. */
  inline BOL Resize() { return TStackResize<T, ISZ>(obj_.AJT()); }

  /* Doubles the size of the obj.
  @return False upon failure. */
  inline BOL ResizeDelta(ISZ size_delta) {
    return TStackResize<T, ISZ>(obj_.AJT(), size_delta);
  }

  /* Gets this ASCII Object. */
  inline TStack<ISZ>* This() {
    return TPtr<TStack<ISZ>>(obj_.Origin());
  }

  /* Gets this AArray. */
  inline AArray<T, ISZ, BUF>& AJT() { return obj_; }

  /* Prints this object to a Printer. */
  template<typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TStackPrint<Printer, T, ISZ>(o, This());
  }

  /* Prints this object to the given UTF. */
  inline void CPrint() { PrintTo<_::COut>(_::StdOut()); }

  /* Gets a reference to the given element index. */
  inline T& operator[](ISZ index) { return Start()[index]; }

  /* Gets a const reference to the given element index. */
  inline const T& operator[](ISZ index) const { return Start()[index]; }
};  //< namespace _

}  //< namespace _

template<typename T = ISW, typename ISZ = ISN, typename BUF = _::Nil>
_::AArray<T, ISZ, BUF>& operator<<(_::AArray<T, ISZ, BUF>& obj, T item) {
  obj.Push(item);
  return obj;
}

template<typename T = ISW, typename ISZ = ISN, typename BUF = _::Nil>
_::AArray<T, ISZ, BUF>& operator>>(T& item, _::AArray<T, ISZ, BUF>& obj) {
  item = obj.Pop();
  return obj;
}

#endif
#endif

/* Returns the other Stack to the preallocated stack's boofer.
@return An autoject boofer.
template<typename T = ISW, typename ISZ = ISN>
IUW* TStackClone(TStack<ISZ>* stack, ISZ count_max, TStack<ISZ>* other,
                 ISZ other_count_max, ISZ other_count) {
  if (count_max < other_count_max) return nullptr;
  IUW *source = TPtr<IUW>(stack), *destination = TPtr<IUW>(stack);
  ISZ word_count =
      (stack->count * sizeof(T) + sizeof(TStack<ISZ>)) >> WordBitCount;
  size -= word_count;
  while (word_count-- > 0) *destination++ = *source++;
  return TPtr<IUW>(stack);
} */

/* Returns the other Stack to the preallocated stack's boofer.
@return An autoject boofer.
template<typename T = ISW, typename ISZ = ISN>
inline IUW* TStackClone(TStack<ISZ>* stack, TStack<ISZ>* other) {
  A_ASSERT(stack);
  return TStackClone<T, ISZ>(stack, other, stack->count);
} */

/* Returns a clone on the heap.
@return An autoject boofer.
template<typename T = ISW, typename ISZ = ISN>
IUW* TStackClone(TStack<ISZ>* stack, RAMFactory ram) {
  A_ASSERT(stack);
  ISZ size = stack->count_max;
  IUW* other_buffer = ram(nullptr, size);
  IUW *source = TPtr<IUW>(stack),  //
      *destination = other_buffer;
  ISZ data_amount =
      (stack->count * sizeof(T) + sizeof(TStack<ISZ>)) >> WordBitCount;
  size -= data_amount;
  while (data_amount-- > 0) *destination++ = *source++;
  return destination;
} */

/* Clones the other ASCII Autoject including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone.
template<typename T = IUA, typename ISZ = ISN>
IUW* TStackClone(Autoject& obj) {
  RAMFactory factory = obj.ram;
  IUW* origin = obj.origin;
  if (!factory || !origin) return nullptr;

  TStack<ISZ>* o = TPtr<TStack<ISZ>>(origin);
  ISZ count = o->count;
  IUW* clone = TArrayNew<T, ISZ, TStack<ISZ>>(count);
  ISW size_bytes = (ISW)TStackSizeOf<T, ISZ>(count);
  if (!RAMCopy(clone, count, origin, size_bytes)) return nullptr;
  TSizeSet<ISZ>(origin, count);
  return clone;
} */
