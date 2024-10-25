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
//@todo Change SCP_A to typename ISZ = ISN, typename ISY = ISZ
namespace _ {

/* @ingroup AsciiStack */

/* ASCII Stack
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/MapTypes/Stack.md

An Array Stack obj of homogeneous-sized plain-old-data (POD) types.
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/MapTypes/Stack.md

# Stack Memory Layout

@code
+---------------+
|    Boofer     |
|---------------|
| C-Style Array |
|---------------|  ^
|    Header     |  |
+---------------+ 0xN
@endcode
*/
template<typename ISZ = ISN>
struct TStack {
  ISZ total,  //< Size of the Array in elements.
      count;  //< Element count.
};

/* Returns the first element in the Stack TMatrix. */
template<typename T = ISW, typename ISZ = ISN>
inline const T* TStackStart(const TStack<SCK_P>* stack) {
  return TPtr<T>(stack, sizeof(TStack<SCK_P>));
}

/* Returns the first element in the Stack TMatrix. */
template<typename T = ISW, typename ISZ = ISN>
inline T* TStackStart(TStack<SCK_P>* stack) {
  return CPtr<T>(TStackStart<T, SCK_P>(CPtr<TStack<SCK_P>>(stack)));
}

/* Returns the first empty element of the stack. */
template<typename T = ISW, typename ISZ = ISN>
inline const T* TStackTop(const TStack<SCK_P>* stack) {
  return TStackStart<T, SCK_P>(stack) + stack->count;
}

/* Returns the first empty element of the stack. */
template<typename T = ISW, typename ISZ = ISN>
inline T* TStackTop(TStack<SCK_P>* stack) {
  return CPtr<T>(TStackStart<T, SCK_P>(CPtr<TStack<SCK_P>>(stack))) + 
         stack->count;
}

template<typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeOf(ISZ count) {
  return count * sizeof(T) + sizeof(TStack<SCK_P>);
}

/* Prints the given obj to the console. */
template<typename Printer, typename T = ISW, typename ISZ = ISN>
Printer& TStackPrint(Printer& o, const TStack<SCK_P>* stack) {
  ISZ total = stack->total, count = stack->count;
  o << Linef("\n+---\n| TStack<T") << CHA('@' + sizeof(T)) << ",ISZ"
    << CHA('@' + sizeof(ISZ))
    << ">: bytes:" << TStackSizeOf<T, SCK_P>(total)
    << " total: " << total << " count:" << count << Linef("\n+---");

  const T* elements = TStackStart<T, SCK_P>(stack);
  for (ISC i = 0; i < count; ++i) o << "\n| " << i << ".) " << elements[i];
  if (count == 0) o << "\n| Empty";
#if D_THIS
  ISZ bytes = TStackSizeOf<T, SCK_P>(stack->total);
  return o << Linef("\n+---") << Charsf(stack, bytes) << '\n';
#else
  return o;
#endif
}

/* Copies an ASCII Stack from the origin to the destination. */
template<typename T = ISW, typename ISZ = ISN>
inline CHA* TStackCopy(TStack<SCK_P>* destination, const TStack<SCK_P>* source) {
  return RAMCopy(destination, TStackTop<T, SCK_P>(destination), source,
                   TStackTop<T, SCK_P>(source));
}

/* Copies an ASCII Stack from the origin to the destination. */
template<typename T = ISW, typename ISZ = ISN>
inline CHA* TStackCopy(TStack<SCK_P>* destination, ISZ destination_size,
                       const TStack<SCK_P>* Source
) {
  return RAMCopy(destination, destination_size, Source,
                   TStackTop<T, SCK_P>(Source));
}

// Calculates the size of a TStack<SCK_P> in bytes based on the count.
template<typename T, typename ISZ = ISN, typename ISR=ISW>
inline ISR TStackSize(ISZ count) {
  return sizeof(TStack<SCK_P>) + ISR(count) * sizeof(T);
}

// Utility to cast Autoject origin to TStack<SCK_P>*.
template<typename ISZ = ISR>
inline TStack<SCK_P>* TStackPtr(IUW* boofer) {
  return TPtr<TStack<SCK_P>>(boofer);
}

// Utility to cast Autoject origin to TStack<SCK_P>*.
template<typename ISZ = ISR>
inline const TStack<SCK_P>* TStackPtr(const IUW* boofer) {
  return TPtr<const TStack<SCK_P>>(boofer);
}

// Utility to cast Autoject origin to TStack<SCK_P>*.
template<typename ISZ = ISR>
inline TStack<SCK_P>* TStackPtr(Autoject* adj) {
  return TPtr<TStack<SCK_P>>(adj.origin);
}

// Utility to cast Autoject origin to TStack<SCK_P>*.
template<typename ISZ = ISN>
inline TStack<SCK_P>* TStackPtr(Autoject& ajt) {
  return TPtr<TStack<SCK_P>>(ajt.origin);
}

/* Creates a new copy of the stack with the new size being the total + 
count_delta.
@return Returns nil if the clone cannot grow or shrink. */
template<typename T = ISW, typename ISZ = ISN>
TStack<SCK_P>* TStackClone(Autoject& adj, ISZ count_delta) {
  auto stack = TStackPtr<ISZ>(adj);
  D_ASSERT(stack);
  ISZ total = stack->total;
  D_ASSERT(total >= 0);
#if D_THIS
  D_COUT("\nAuto-growing Stack...\nBefore:");
  TStackPrint<COut, T, ISZ>(StdOut(), stack);
#endif
  ISZ total_new = total + count_delta;
  if (total_new < 0) return nullptr;
  ISZ count = stack->count;
  ISZ count_new = total_new < count ? total_new : count;
  ISW size_old = TStackSize<T, SCK_P>(count),
      size_new = TStackSize<T, SCK_P>(total_new);
  TStack<SCK_P>* stack_new = TStackPtr<ISZ>(adj.ram(nullptr, size_new));
  if(!stack_new) return stack_new;
  *stack_new = {total_new, count_new};
  D_COUT("\nCopying data..." <<
         "\nstack_new.count: " << stack_new->count <<
         "\nstack_new.total: " << stack_new->total <<
         "\nsize_old: " << size_old << 
         "\nsize_new: " << size_new <<
         "\nTStackStart<T, SCK_P>(stack): " <<  Hexf(TStackStart<T, SCK_P>(stack)));
  size_old -= sizeof(TStack<SCK_P>);
  RAMCopy(TStackStart<T, SCK_P>(stack_new), size_old,
            TStackStart<T, SCK_P>(stack), size_old);
#if D_THIS
  D_COUT("\nResult:");
  TStackPrint<COut, T, ISZ>(StdOut(), stack_new);
#endif
  return stack_new;
}

/* Resizes the AutoStack by the given count delta and deletes the old boofer.
@return Nil if it's not possible to resize: either out of memory or negative 
new total. */
template<typename T = ISW, typename ISZ = ISN>
TStack<SCK_P>* TStackResize(Autoject& adj, ISZ count_delta) {
  auto stack_new = TStackClone<T, SCK_P>(adj, count_delta);
  if (!stack_new) return stack_new;
  adj.ram(adj.origin, 0);
  adj.origin = TPtr<IUW>(stack_new);
  return stack_new;
}

/* Doubles the AutoStack total and deletes the old boofer. */
template<typename T = ISW, typename ISZ = ISN>
TStack<SCK_P>* TStackResize(Autoject& adj) {
  auto stack = TStackPtr<ISZ>(adj.origin);
  auto stack_new = TStackClone<T, SCK_P>(adj, stack->total);
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
IUW* TStackFactoryStack(IUW* origin, ISW bytes) {
  if (bytes <= 0) return TPtr<IUW>(TStackType<ISZ, DT, Type>());
  return RAMFactoryStack(origin, bytes);
}

/* RAMFactoryHeap function for the TStack. */
template<typename ISZ = ISN, typename DT = DTB, DT Type = _ISN>
IUW* TStackFactoryHeap(IUW* origin, ISW bytes) {
  if (bytes <= 0) return TPtr<IUW>(TStackType<ISZ, DT, Type>());
  return RAMFactoryHeap(origin, bytes);
}

/* Gets the size of a Stack with the given total. */
template<typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSize(ISZ total) {
  enum { CountMaxMin = sizeof(IUD) / sizeof(T) };
  if (total < CountMaxMin) total = CountMaxMin;
  return sizeof(TStack<SCK_P>) + sizeof(T) * total;
}

/* Gets the min size of a Stack with zero elements. */
template<typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeMin() {
  enum {
    StackCountMin = sizeof(T) > 8 ? 1 : 8 / sizeof(T),
    StackCountMaxMin = sizeof(TStack<SCK_P>) + sizeof(T) * StackCountMin,
  };
  return StackCountMaxMin;
}

/* Gets the max number_ of elements in an obj with the specific index
width. */
template<typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeMax() {
  return (ISZ)((((~(ISZ)0) - ALUWordMask) - (ISZ)sizeof(TStack<SCK_P>)) /
               (ISZ)sizeof(T));
}

/*
template<typename T = ISW, typename ISZ = ISN>
ISZ StackCountMax () {
    return (ISZ)((UnsignedMax<ISZ> () - (ISZ)sizeof (TStack<T, ISZ, ISZ>)) / (ISZ)sizeof (T));
}*/

/* The minimum obj size. */
template<typename T = ISW, typename ISZ = ISN>
inline ISZ TStackSizeMin(ISZ total) {
  ISZ count_upper_bounds = TStackSizeMax<T, SCK_P>();
  if (total > count_upper_bounds) total = count_upper_bounds;
  return (ISZ)(sizeof(TStack<SCK_P>) + total * sizeof(T));
}

/* Initializes an obj from a preallocated socket who's size is a multiple of
8 bytes.
@param socket An obj of bytes large enough to fit the obj.
@return A dynamically allocated socket. */
template<typename T = ISW, typename ISZ = ISN>
TStack<SCK_P>* TStackInit(TStack<SCK_P>* stack, ISZ size) {
  if (!stack || size < 0) return nullptr;
  D_ARRAY_WIPE(stack, ISW(TStackSizeOf<T, SCK_P>(size)));
  stack->total = size;
  stack->count = 0;
  return stack;
}

/* Initializes an obj from a preallocated socket who's size is a multiple of
8 bytes.
@param socket An obj of bytes large enough to fit the obj.
@return A dynamically allocated socket. */
template<typename T = ISW, typename ISZ = ISN>
TStack<SCK_P>* TStackInit(TStack<SCK_P>* stack, ISZ size, const T* items,
                        ISZ count) {
  if (!stack || !items || size <= 0 || count < 0) return nullptr;
  D_ARRAY_WIPE(stack, ISW(TStackSizeOf<T, SCK_P>(size)));

  stack->total = size;
  stack->count = 0;
  return stack;
}

/* Returns the last element of the stack. */
template<typename T = ISW, typename ISZ = ISN, typename Type = T>
inline Type TStackEnd(TStack<SCK_P>* stack) {
  return TPtr<Type>(TStackStart<T, SCK_P>(stack) + stack->count);
}

/* Attempts to resize the given Autoject to the new_count.
@return Nil upon failure. */
template<typename T = ISW, typename ISZ = ISN>
BOL TStackResize(Autoject& obj, ISZ new_count) {
  TStack<SCK_P> stack = *TPtr<TStack<SCK_P>>(obj.origin);
  ISZ count = stack.count, total = TStackSizeMax<T, SCK_P>();
  if (count > total || count == new_count) return false;
}

/* Checks if the given index exists in the stack. */
template<typename T = ISW, typename ISZ = ISN>
BOL TStackInBounds(const TStack<SCK_P>* stack, ISZ index) {
  return index >= 0 && index < stack->total;
}

/* Gets the element at the given index.
@param obj    The obj.
@param index The index of the element to get.
@return -1 if a is nil and -2 if the index is out of bounds. */
template<typename T = ISW, typename ISZ = ISN>
T TStackGet(const TStack<SCK_P>* stack, ISZ index) {
  A_ASSERT(stack);
  if (index < 0 || index >= stack->count) return 0;
  return TStackStart<T, SCK_P>(stack)[index];
}

template<typename T = ISW, typename ISZ = ISN>
T TStackGet_NC(const TStack<SCK_P>* stack, ISZ index) {
  return TStackStart<T, SCK_P>(stack)[index];
}

/* Peeks at the top item on the stack without popping it off.
@param stack The base address of the stack.
@return The item popped off the obj. */
template<typename T = ISW, typename ISZ = ISN>
T TStackPeek(const TStack<SCK_P>* stack) {
  A_ASSERT(stack);
  ISZ count = stack->count;
  if (count == 0) return 0;
  T* items = TStackStart<T, SCK_P>(stack);
  T item = items[stack->count - 1];
  return item;
}

/* Adds the given item to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param stack The Ascii Object base poiner.
@param item  The item to push onto the obj. */
template<typename T = ISW, typename ISZ = ISN>
inline void TStackPush_NC(TStack<SCK_P>* stack, T item, ISZ count) {
  TStackStart<T, SCK_P>(stack)[count] = item;
  stack->count = count + 1;
}

/* Adds the given item to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param stack The Ascii Object base poiner.
@param item  The item to push onto the obj. */
template<typename T = ISW, typename ISZ = ISN, typename ISY = ISZ>
inline ISY TStackInsert(T* start, ISZ total, ISZ count, T item, ISY index = PSH) {
  if (count >= total) return -ErrorStackOverflow;
  if (index < 0) return -ErrorInvalidIndex;
  //if (index < 0) index = count;
  TArrayInsert_NC<T, SCK_P>(start, count, item);
  return index;
}
template<typename T = ISW, typename ISZ = ISN, typename ISY = ISZ>
inline ISY TStackInsert(TStack<SCK_P>* stack, T item, ISY index = PSH) {
  //D_CHECK_PTR_TRETURN(ISY, stack);
  if (index < PSH) return -ErrorInvalidIndex;
  ISY count = ISY(stack->count),
      total = ISY(stack->total);
  if (count >= total) return -ErrorStackOverflow;
  if (index == PSH) index = count;
  D_COUT("  Pushing:" << item << " total:" << total << " count:" << count << 
         "\n| Before:" << Charsf(stack, TStackSizeOf<T, SCK_P>(total)));
  TArrayInsert_NC<T, SCK_P>(TStackStart<T, SCK_P>(stack), count++, index, item);
  D_COUT("\n| After:" << Charsf(stack, TStackSizeOf<T, SCK_P>(total)));
  stack->count = count;
  return index;
}

/* Adds the given item to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param stack The Ascii Object base poiner.
@param item  The item to push onto the obj. */
template<typename T = ISW, typename ISZ = ISW, typename ISY = ISZ>
inline ISY TStackInsertDown(T* start, ISZ total, ISZ count, T item, 
  ISY index = PSH) {
  if (count >= total) return -ErrorStackOverflow;
  if (index > 0) return -ErrorInvalidIndex;
  TArrayInsertDown_NC<T, SCK_P>(start, count, item);
  return index;
}

/* Adds the given item to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param stack The Ascii Object base poiner.
@param item  The item to push onto the obj. */
template<typename T = ISW, typename ISZ = ISN, typename BUF = Nil>
ISZ TStackInsert(AArray<T, ISZ, BUF>& obj, T item, ISZ index = PSH) {
  auto stack = obj.OriginAs<TStack<SCK_P>*>();
Insert:
  ISZ result = TStackInsert<T, SCK_P>(stack, item, index);
  if (result < 0) {
    D_COUT("\n\nError " << result << ": " << TCrabsErrorST<>(result) <<
           " at index:" << index << "\nAutogrowing...");
    stack = TStackResize<T, SCK_P>(obj.AJT());
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
    result = TStackInsert<T, SCK_P>(obj, items[i]);
    if (result < 0) return result;
  }
  return result;
}

/* Pops the top item off of the obj.
@note We do not delete the item at the
@param a The obj.
@return The item popped off the obj. */
template<typename T = ISW, typename ISZ = ISN>
T TStackPop(TStack<SCK_P>* stack) {
  A_ASSERT(stack);
  ISZ count = stack->count;
  if (count == 0) return 0;
  T* items = TStackStart<T, SCK_P>(stack);
  stack->count = count - 1;
  T item = items[count - 1];
  return item;
}

/* Shifts the elements down starting at the index element and deletes the index
element at the given index.
@pre You must perform bounds checking before calling this function. */
template<typename T>
void TStackRemove(T* elements, ISW element_number, ISW element_count) {
  return TArrayRemove<T>(elements + element_number,
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
ISZ TStackRemove(TStack<SCK_P>* stack, ISZ index) {
  A_ASSERT(stack);
  ISZ result =
      TStackRemove<T, SCK_P>(TStackStart<T, SCK_P>(stack), stack->count, index);
  if (result < 0) return result;
  stack->count = result;
  return result;
}

/* Returns true if the given obj contains the given address.
@return false upon failure. */
template<typename T = ISW, typename ISZ = ISN>
BOL TStackContains(TStack<SCK_P>* stack, void* address) {
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
  return TStackSizeMin<T, SCK_P>(count) / sizeof(IUW);
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
|     Boofer     |
|----------------|
| Stack Elements |
|----------------|  +
|  Stack struct  |  |
+----------------+ 0x0
@endcode
*/
template<typename T = ISW, typename ISZ = ISN,
          ISZ Size_ = AStackCountMaxDefault,
          typename BUF = TBUF<Size_, T, ISZ, TStack<SCK_P>>>
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
    D_ARRAY_WIPE(Start(), SizeBytes() - sizeof(TStack<SCK_P>));
    This()->count = 0;
  }

  /* Attempts to down-size the BUF or creates a dynamically allocated stack.
  @param size The number of elements in the Array. */
  AStack(ISZ stack_height) : obj_(TStackSize<T, SCK_P>(stack_height)) {
    ISZ bytes = TStack<SCK_P>(stack_height) - sizeof(ISZ);
    D_ARRAY_WIPE(Start(), SizeBytes() - sizeof(TStack<SCK_P>));
  }

  /* Copies the items into the obj_.Boofer () with some additional
  empty_elements. */
  AStack(ISZ total, const T* items, ISZ items_count)
      : obj_(TStackSize<T, SCK_P>(items_count)) {
    TStackInsert<T, SCK_P>(This().AJT(), items, items_count);
  }

  /* Copies the items into the obj_.Boofer () with some additional
  empty_elements. */
  AStack(const T* items, ISZ items_count)
      : obj_(TStackSize<T, SCK_P>(items_count)) {
    TStackInsert<T, SCK_P>(obj_.AJT(), items, items_count);
  }

  /* Destructs nothing. */
  ~AStack() {}

  /* Creates a dynamically allocated clone. */
  inline IUW* TClone() { TStackClone<T, SCK_P>(AJT()); }

  /* Clones the other object.
  @return true upon success and false upon failure. */
  inline BOL Clone(TStack<SCK_P>* other) { TStackClone<T, SCK_P>(AJT(), other); }

  /* Checks if the given index is a valid element.
  @return true if the index is in bounds. */
  inline BOL InBounds(ISZ index) {
    return TStackInBounds<T, SCK_P>(obj_.OBJ(), index);
  }

  /* Gets the max number_ of elements in an obj with the specific index
  width. */
  inline ISZ SizeMax() { return TStackSizeMax<T, SCK_P>(); }

  /* Gets the min size of the entire Stack, including header, in bytes. */
  inline ISZ SizeMin() { return TStackSizeMin<T, SCK_P>(); }

  /* Gets the max elements that can fit in the stack boofer. */
  inline ISZ Height() { return This()->total; }

  /* Gets the count of the items on the obj. */
  inline ISZ Count() { return This()->count; }

  /* Gets the size of the entire Stack, including header, in bytes. */
  inline ISZ SizeBytes() { return TStackSizeOf<T, SCK_P>(Height()); }

  /* Gets a pointer to the first element in the obj. */
  inline T* Start() { return TStackStart<T, SCK_P>(This()); }

  /* Gets a pointer to the first element in the obj. */
  inline T* Stop() { return Start() + Count(); }

  /* Inserts the item into the obj at the given index.
  @return -1 if a is nil and -2 if the obj is full.
  @param item  The item to insert.
  @param index The index to insert at. */
  inline T Insert(T item, T index) {
    return AStack<T, SCK_P>(AJT(), item, index);
  }
  /* Adds the given item to the stop of the obj.
  @return The index of the newly stacked item.
  @param item The item to push onto the obj. */
  inline ISZ Push(T item) { return TStackInsert<T, SCK_P>(AJT(), item); }

  /* Adds the given item to the stop of the obj.
  @return The index of the newly stacked item.
  @param item The item to push onto the obj. */
  inline ISZ Push(T* item, ISZ item_count) {
    return TStackInsert<T, SCK_P>(AJT(), item, item_count);
  }

  /* Pops the top item off of the obj.
  @return The item popped off the obj. */
  inline T Pop() { return TStackPop<T, SCK_P>(This()); }

  /* Removes the given index from the obj.
  @return True if the index is out of bounds.
  @param index The index the item to remove. */
  inline BOL Remove(ISZ index) { return TStackRemove<T, SCK_P>(This(), index); }

  /* Peeks the top item off of the obj without popping it.
  @return The item popped off the obj. */
  inline T Peek() { return TStackPeek<T, SCK_P>(AJT()); }

  /* Gets the element at the given index.
  @return -1 if a is nil and -2 if the index is out of bounds.
  @param index The index of the element to get. */
  inline T Get(ISZ index) { return TStackGet<T, SCK_P>(AJT(), index); }

  /* Returns true if the given obj contains the given address.
  @return false upon failure. */
  inline BOL Contains(void* address) {
    return TStackContains<T, SCK_P>(AJT(), address);
  }

  /* Resizes the obj to the new_count.
  @return False upon failure. */
  inline BOL Resize(ISZ new_count) {
    ISZ count = This()->count;
    return TStackResize<T, SCK_P>(obj_, new_count - count);
  }

  /* Doubles the size of the obj.
  @return False upon failure. */
  inline BOL Resize() { return TStackResize<T, SCK_P>(obj_.AJT()); }

  /* Doubles the size of the obj.
  @return False upon failure. */
  inline BOL ResizeDelta(ISZ size_delta) {
    return TStackResize<T, SCK_P>(obj_.AJT(), size_delta);
  }

  /* Gets this ASCII Object. */
  inline TStack<SCK_P>* This() {
    return TPtr<TStack<SCK_P>>(obj_.Origin());
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
