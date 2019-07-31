/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /t_array.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_TOBJECT
#define SCRIPT2_TOBJECT 1

#include "c_array.h"

namespace _ {
/* Overwrites the memory with fill_char; functionally identical to memset.
 */
inline CH1* ArrayFill(void* start, void* stop, CH1 fill_char) {
  return ArrayFill(
      start, reinterpret_cast<CH1*>(stop) - reinterpret_cast<CH1*>(start) + 1,
      fill_char);
}

/* The maximum autoject size.
The max ASCII Object size is dictated by the max value allowed that can be
aligned up to a multiple of 8 (i.e. 64-bit word boundary). */
template <typename SI>
inline SI TArraySizeMax() {
  SI count_max = 0;
  return (~count_max) - 15;
}
/* The upper bounds defines exactly how many elements can fit into a space
in memory. */
template <typename T = SIW, typename SIZ = SIN, typename Class>
inline SIZ TArraySizeMax() {
  SIZ max_value = SIZ((~SIZ(0)) >> 1);
  return max_value - SIZ(sizeof(UIW) - 1 - sizeof(Class) / sizeof(T));
}
}  // namespace _

#if SEAM >= SCRIPT2_STACK
#include "t_binary.h"

#if SEAM == SCRIPT2_STACK
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* @ingroup AsciiArray
Please see the ASCII Data Types Specificaiton for DRY documentation.
@link ./spec/data/vector_types/array.md */

/* Deletes the given obj using the obj.factory. */
inline void Delete(Autoject obj) {
  RamFactory ram_factory = obj.ram_factory;
  if (ram_factory) ram_factory(obj.begin, 0);
}

/* An ASCII Array.
Please see the ASCII Data Types Specificaiton for DRY documentation.
@link ./spec/data/vector_types/array.md

@code
+-----------------+
|  C-Style Array  |
|-----------------|  ^
|  TArray Header  |  |
+-----------------+ 0xN
@endcode
*/
template <typename SIZ = SIN>
struct TArray {
  SIZ size;  //< Number of elements in the array.
};

/* Checks if the given autoject count is in the min max bounds of an ASCII
Object. */
template <typename T, typename SI>
inline BOL TArrayCountIsValid(SI index, SI count_min) {
  return (index >= count_min) && (index < TArraySizeMax<T, SI>());
}

/* Gets the first byte of the ASCII Object data section. */
template <typename Class, typename T>
inline T* TArrayStart(Class* autoject) {
  SIW address = reinterpret_cast<SIW>(autoject);
  return reinterpret_cast<T*>(address + sizeof(Class));
}

/* Prints the item to the printer*/
template <typename T, typename SIZ, typename Printer>
Printer& TArrayPrint(Printer& o, TArray<SIZ>* item) {
  SIZ size = item->size;
  o << Linef("\n+---\nTArray<SI") << (char)('0' + sizeof(SIZ))
    << "> size:" << size;
  if (size == 0) return o;
  T* items = TArrayStart<T, SIZ>(item);
  SIZ i = 0;
  for (; i < size; ++i) {
    o << "\n| " << i << ".) " << items[i];
  }
  return o << Linef("\n+---");
}

/* Calculates the size in bytes of an array with given element_count. */
template <typename T, typename SI>
inline SI TSizeOf(SI element_count) {
  return sizeof(T) * element_count;
}

/* Calculates the size in bytes of an array with given element_count including
the Class header. */
template <typename T, typename SI, typename Class>
inline SI TSizeOf(SI size) {
  return sizeof(T) * size + sizeof(Class);
}

/* The minimum size of an array with zero elements. */
template <typename SIZ>
constexpr SIZ TSizeMin() {
  return 0;
}

/* Sets the size to the new_size*/
template <typename SIZ>
inline void TSizeSet(UIW* begin, SIZ new_size) {
  *reinterpret_cast<SIZ*>(begin) = new_size;
}

template <typename SIZ>
inline SIZ TSizeSet(Autoject& autoject, SIZ new_size) {
  return TSizeSet<SIZ>(autoject.begin, new_size);
}

/* Gets the ASCII Autoject size. */
template <typename SIZ>
inline SIZ TSize(UIW* begin) {
  return *reinterpret_cast<SIZ*>(begin);
}

/* Gets the ASCII Autoject size. */
template <typename SIZ>
inline SIZ TSize(Autoject& autoject) {
  return TSize<SIZ>(autoject.begin);
}

/* Gets the ASCII Autoject size. */
template <typename T, typename SIZ, typename Class>
inline SIZ TSizeBytes(SIZ size) {
  return sizeof(Class) + sizeof(T) * size;
}
template <typename T, typename SIZ, typename Class>
inline SIZ TSizeBytes(UIW* begin) {
  return TSizeBytes<T, SIZ, Class>(TSize<SIZ>(begin));
}
template <typename T, typename SIZ, typename Class>
inline SIZ TSizeBytes(Autoject& autoject) {
  return TSizeBytes<T, SIZ, Class>(autoject.begin);
}

/* Gets the ASCII Autoject size in CPU words. */
template <typename T, typename SIZ, typename Class>
inline SIZ TSizeWords(SIZ size) {
  SIZ size_aligned_up = AlignUp(TSizeBytes<T, SIZ, Class>(size));
  return size_aligned_up >> kWordBitCount;
}
template <typename T, typename SIZ, typename Class>
inline SIZ TSizeWords(UIW* begin) {
  return TSizeWords<T, SIZ, Class>(TSize<SIZ>(begin));
}
template <typename T, typename SIZ, typename Class>
inline SIZ TSizeWords(Autoject& autoject) {
  return TSizeWords<T, SIZ, Class>(autoject.begin);
}

/* Dynamically allocates a new Array of the given size.
@return Nil upon failure or a pointer to the cloned autoject upon success.
@param socket A raw ASCII Socket to clone. */
template <typename T, typename SIZ = SIN, typename Class>
UIW* TArrayNew(RamFactory factory, SIZ size) {
  UIW* begin = factory(nullptr, TSizeBytes<T, SIZ, Class>(size));
  TSizeSet<SIZ>(begin, size);
  return begin;
}

/* Writes the size to the given word-aligned-down socket, making a new one if
required. */
template <typename T, typename SIZ>
inline UIW* TArrayInit(Autoject& obj, UIW* buffer, SIZ size,
                       RamFactory ram_factory) {
  D_ASSERT(ram_factory);
  D_ASSERT(size >= TSizeMin<SIZ>());
  obj.ram_factory = ram_factory;
  if (!buffer) {
    SIZ buffer_size = AlignUp(SIZ(size * sizeof(T) + sizeof(TArray<SIZ>)));
    buffer = ram_factory(nullptr, buffer_size);
  }
  D_ARRAY_WIPE(buffer, size * sizeof(T) + sizeof(TArray<SIZ>));
  TSizeSet<SIZ>(buffer, size);
  obj.begin = buffer;
  return buffer;
}

/* Copies the source to the target functionally identical to memcpy.
@param  start The start of the write socket.
@param  stop  The stop of the write socket.
@param  begin The begin of the read socket.
@param  size  Number of bytes to copy.
@return Pointer to the last UI1 written or nil upon failure. */
inline CH1* ArrayCopy(void* begin, void* stop, const void* read_start,
                      SIW read_size) {
  return ArrayCopy(begin, SizeOf(begin, stop), read_start, read_size);
}

/* Copies the source to the target functionally identical to memcpy.
@param  begin The start of the write socket.
@param  stop  The stop of the write socket.
@param  begin The begin of the read socket.
@param  size  Number of bytes to copy.
@return Pointer to the last UI1 written or nil upon failure. */
inline CH1* ArrayCopy(void* begin, void* stop, const void* read_start,
                      const void* read_stop) {
  return ArrayCopy(begin, SizeOf(begin, stop), read_start,
                   SizeOf(read_start, read_stop));
}

/* Writes the source TArray to the destination. */
template <typename T = UI1, typename SIZ = SIN, typename Class>
TArray<SIZ>* TArrayWrite(TArray<SIZ>* destination, TArray<SIZ>* source,
                         SIZ size) {
  D_ASSERT(destination);
  D_ASSERT(source);

  SIW size_bytes = (SIW)TSizeBytes<T, SIZ, Class>(size);
  if (!ArrayCopy(destination, size_bytes, source, size_bytes)) return nullptr;
  return destination;
}

template <typename T = UI1, typename SIZ = SIN, typename Class>
UIW* TArrayWrite(UIW* destination, UIW* source, SIZ size) {
  TArray<SIZ>* result =
      TArrayWrite<T, SIZ, Class>(reinterpret_cast<TArray<SIZ>*>(destination),
                                 reinterpret_cast<TArray<SIZ>*>(source), size);
  return reinterpret_cast<UIW*>(result);
}

/* Clones the other ASCII Autoject including possibly unused autoject space.
@return Nil upon failure or a pointer to the cloned autoject upon success.
@param socket A raw ASCII Socket to clone. */
template <typename T = UI1, typename SIZ = SIN, typename Class>
UIW* TArrayClone(Autoject& obj) {
  RamFactory factory = obj.ram_factory;
  UIW* begin = obj.begin;
  // if (!factory || !begin) return nullptr;

  TArray<SIZ>* o = reinterpret_cast<TArray<SIZ>*>(begin);
  SIZ size = o->size;
  UIW* clone = TArrayNew<T, SIZ, TArray<SIZ>>(size);
  return TArrayWrite<T, SIZ, Class>(clone, begin, size);
}

/* Checks of the given size is able to double in size.
@return True if the autoject can double in size. */
template <typename SIZ>
BOL TCanGrow(SIZ size) {
  return !(size >> (sizeof(SIZ) * 8 - 2));
}

/* Resizes the given array.
@return True upon success and false upon failure. */
template <typename T, typename SIZ, typename Class>
BOL TArrayResize(Autoject& obj, SIZ new_size) {
  D_COUT("\nResizing Array to new_size:" << new_size);
  UIW* buffer = obj.begin;
  if (!buffer) return false;
  SIZ size = TSizeBytes<SIZ>(buffer);
  if (size < new_size) {
    if (size <= 0) return false;
    TSizeSet<SIZ>(buffer, new_size);
    return true;
  }
  UIW* new_begin = obj.ram_factory(nullptr, new_size);
  TSizeSet<SIZ>(new_begin, new_size);
  TArrayWrite<T, SIZ, Class>(new_begin, buffer, new_size);
  obj.begin = new_begin;
  return true;
}

/* Resizes the given array to double it's prior capacity.
@return True upon success and false upon failure. */
template <typename T, typename SIZ, typename Class>
BOL TArrayGrow(Autoject& obj) {
  SIZ size = TSizeBytes<SIZ>(obj.begin);
  if (!TCanGrow<SIZ>(size)) return false;
  return TArrayResize<T, SIZ, Class>(obj, size << 1);
}

/* Gets the last UI1 in the ASCII Object.
The autoject end, unlike the UTF which the stop pointer is at the last CH1 in
the autoject, the end of a socket is an out of bounds address. For this reason,
it is best to cap the autoject size as the highest possible value that you can
word-align to produce a valid result, which is 3 bytes on 32-bit systems and
7 bytes on 64-bit systems. */
template <typename SIZ>
inline CH1* TArrayEnd(Autoject stack) {
  UIW* socket = stack.begin;
  A_ASSERT(socket);
  SIZ size = *reinterpret_cast<SIZ*>(socket);
  return reinterpret_cast<CH1*>(socket) + size;
}

/* Gets the last UI1 in the ASCII Object. */
template <typename SIZ>
inline const CH1* TArrayEnd(const Autoject stack) {
  UIW* socket = stack.begin;
  SIZ size = *reinterpret_cast<SIZ*>(socket);
  return reinterpret_cast<const CH1*>(socket) + size;
}

/* Returns the start of the OBJ. */
template <typename T = CH1, typename SIZ, typename Class>
inline T* TArrayStart(TArray<SIZ>* obj) {
  UIW start = reinterpret_cast<UIW>(obj) + sizeof(Class);
  return reinterpret_cast<T*>(start);
}

/* Returns the start of the OBJ. */
template <typename T = CH1, typename SIZ>
inline T* TArrayStart(UIW* obj) {
  return TArrayStart<T, SIZ>(reinterpret_cast<TArray<SIZ>*>(obj));
}

/* Gets the stop of the TArray. */
template <typename T = CH1, typename SIZ>
inline T* TArrayStop(TArray<SIZ>* ary) {
  return TArrayStart<T, SIZ>(ary) + ary->size - 1;
}

/* Returns the stop of the OBJ. */
template <typename T = CH1, typename SIZ>
inline T* TArrayStop(UIW* obj) {
  return TArrayStop<T, SIZ>(reinterpret_cast<TArray<SIZ>*>(obj));
}

/* Prints this autoject to the COut. */
template <typename SIZ, typename Printer>
Printer& TArrayPrint(Printer& o, Autoject& obj) {
  o << "\nAutoject<SI" << (CH1)('0' + sizeof(SIZ)) << '>';
  UIW* begin = obj.begin;
  if (begin) {
    SIZ size = *reinterpret_cast<SIZ*>(begin);
    o << " size:" << (SIW)size;
  }
  return o;
}

/* Inserts the given item at the start of the elements.
@pre You must perform bounds checking before calling this function. */
template <typename T>
inline void TArrayInsertAtStart(T* elements, T* elements_end, const T& item) {
  while (elements_end > elements) {
    *elements_end = *(elements_end - 1);
    --elements_end;
  }
  *elements = item;
}
/* Inserts the given item at the index index the elements of the given count.
@pre You must perform bounds checking before calling this function. */
template <typename T>
inline void TArrayInsert(T* elements, SIW index, SIW count, const T& item) {
  return TArrayInsertAtStart<T>(elements + index, elements + count, item);
}

/* Shifts the elements down starting at the index element and deletes the index
 * element at the given index.
@pre You must perform bounds checking before calling this function. */
template <typename T>
void TArrayRemoveStart(T* elements, T* end) {
  while (elements < end) {
    *elements = *(elements + 1);
    ++elements;
  }
}

/* Shifts the elements down starting at the index element and deletes the index
 * element at the given index.
@pre You must perform bounds checking before calling this function. */
template <typename T>
void TArrayRemove(T* elements, SIW element_number, SIW element_count) {
  return TArrayRemoveStart<T>(elements + element_number,
                              elements + element_count);
}

/* An invalid index. */
template <typename SIZ>
inline SIZ TInvalidIndex() {
  return -1;
}

/* Searches for the item in the elements.
@return An invalid index upon failure or a valid index upon success. */
template <typename T, typename SIZ>
SIZ TArrayFind(const T* elements, SIZ element_count, const T& item) {
  for (SIZ i = 0; i < element_count; ++i)
    if (*elements++ == item) return i;
  return TInvalidIndex<SIZ>();
}

/* Compares the two memory sockets.
@param  start  The start of Array A.
@param  stop   The stop of Array A.
@param  begin  The begin of Array B.
@param  end    The end of Array B.
@return True if they are the same and false if they are not. */
inline BOL ArrayCompare(const void* begin_a, const void* end_a,
                        const void* begin_b, const void* end_b) {
  return ArrayCompare(begin_a, SizeOf(begin_a, end_a), begin_b,
                      SizeOf(begin_b, end_b));
}

/* Compares the two memory sockets.
@param  start The start of Array A.
@param  stop  The stop of Array A.
@param  begin The begin of Array B.
@param  size  The size of Array B.
@return True if they are the same and false if they are not. */
inline BOL ArrayCompare(const void* begin_a, void* end_a, const void* begin_b,
                        SIW size_b) {
  return ArrayCompare(begin_a, end_a, begin_a,
                      reinterpret_cast<const CH1*>(begin_b) + size_b);
}

/* A word-aligned array of kSize_ elements of T on the progam stack. */
template <SIW kSize_ = kCpuCacheLineSize, typename T = UI1, typename SIZ = SIN,
          typename Class = Nil>
class TBuf {
 public:
  /* Default destructor does nothing. */
  TBuf() : words_() {}

  /* Returns the socket as a UIW*. */
  inline UIW* Words() { return words_; }

  /* Gets the end word of the socket. */
  inline UIW* WordsEnd() { return &words_[SizeWords()]; }

  /* Gets the stop word of the socket. */
  inline UIW* WordsStop() { return WordsEnd() - 1; }

  /* Gets the begin element of the socket. */
  template <typename T = CH1>
  inline T* Begin() {
    return reinterpret_cast<T*>(words_);
  }

  /* Returns the first element of the ASCII Object data section. */
  template <typename RT = T>
  inline RT* Start() {
    SIW address = reinterpret_cast<UIW>(words_);
    return reinterpret_cast<RT*>(address + sizeof(Class));
  }

  /* Gets the end element of the socket. */
  inline T* End() { return &words_[SizeWords()]; }

  /* Returns the last element of the ASCII Object data section. */
  inline T* Stop() { return Start<>() + Size() - 1; }

  /* Gets the begin of the socket. */
  template <typename T = CH1, typename SIZ = SIW>
  inline T& Element(SIZ index) {
    if (index < 0 || index >= Size()) return nullptr;
    return Start()[index];
  }

  /* Sets the size to the new value. */
  template <typename SIW>
  inline UIW* SetSize(SIW size) {
    A_ASSERT((size & kWordLSbMask) == 0)
    *reinterpret_cast<SIW*>(words_) = size;
    return words_;
  }

  /* The size in elements. */
  static constexpr SIZ Size() { return (SIZ(kSize_) < 0) ? 0 : SIZ(kSize_); }

  /* The size in bytes including the header. */
  static constexpr SIZ SizeBytes() {
    return Size() * sizeof(T) + sizeof(Class);
  }

  /* The size in words rounded down. */
  static constexpr SIZ SizeWords() { return CSizeWords<SIZ>(SizeBytes()); }

 private:
  UIW words_[SizeWords()];  //< The word-aligned socket.
};

/* An Autoject Array of type T.
Arrays may only use 16-bit, 32-bit, and 64-bit signed integers for their
size. */
template <typename T, typename SIZ = SIN, typename BUF = Nil>
class AArray {
  Autoject obj_;  //< Automatic Object.
  BUF buffer_;    //< Optional buffer on the program stack.

 public:
  /* Constructs. */
  AArray() {
    TArrayInit<T, SIZ>(obj_, buffer_.Words(), SIZ(buffer_.Size()),
                       RamFactoryInit());
  }

  /* Creates a autoject with either statically or dynamically allocated
  memory based on the size can fit in the buffer_. If the buffer_ is
  statically allocated but the size can't fit in the buffer a new block of
  dynamic memory will be created. */
  AArray(SIZ size, RamFactory factory = nullptr) {
    TArrayInit<T, SIZ>(obj_, buffer_.Words(), size, RamFactoryInit(factory));
  }

  /* Constructs a autoject with either statically or dynamically allocated
  memory based on if autoject is nil. */
  AArray(RamFactory ram_factory) {
    TArrayInit<T, SIZ>(obj_, buffer_.Words(), buffer_.Size(),
                       RamFactoryInit(ram_factory));
  }

  /* Stores the begin and ram_factory to the obj_. */
  AArray(UIW* begin, RamFactory ram_factory) : obj_({begin, ram_factory}) {}

  /* Destructor calls the RamFactory factory. */
  ~AArray() { Delete(obj_); }

  /* Gets the buffer_. */
  inline BUF& Buffer() { return buffer_; }

  /* Returns the buffer_. */
  inline UIW* Begin() { return obj_.begin; }

  template <typename T = TStack<SIZ>>
  inline T* BeginAs() {
    return reinterpret_cast<T*>(Begin());
  }

  /* Sets the begin to the given pointer.
  @return Nil if the input is nil. */
  inline UIW* BeginSet(void* socket) { return AutojectBeginSet(obj_, socket); }

  /* Gets the ASCII Object size in elements. */
  inline SIZ Size() { return TSize<SIZ>(obj_.begin); }

  /* Gets the total ASCII Object size in bytes. */
  template <typename Class = TArray<SIZ>>
  inline SIZ SizeBytes() {
    return TSizeBytes<T, SIZ, Class>(AJT());
  }

  /* Gets the total ASCII Object size in words. */
  template <typename Class = TArray<SIZ>>
  inline SIZ SizeWords() {
    return TSizeWords<T, SIZ, Class>(AJT());
  }

  /* Returns the start of the OBJ. */
  inline T* Start() {
    UIW ptr = reinterpret_cast<UIW>(obj_.begin) + sizeof(TArray<SIZ>);
    return reinterpret_cast<T*>(ptr);
  }

  /* Gets the stop of the OBJ. */
  inline CH1* Stop() {
    return reinterpret_cast<CH1*>(obj_.begin) + SizeBytes() - 1;
  }

  /* Gets the Autoject. */
  inline Autoject& AJT() { return obj_; }

  /* . */
  inline TArray<SIZ>* Array() {
    return reinterpret_cast<TArray<SIZ>*>(obj_.begin);
  }

  /* Attempts to grow the this autoject.
  @return false if the grow op failed. */
  inline BOL CanGrow() { return TCanGrow<SIZ>(obj_); }

  /* Doubles the size of the obj_ array. */
  template <typename Class>
  inline void Grow() {
    TArrayGrow<T, SIZ, Class>(obj_);
  }

  /* Returns true if the buffer is a Socket and false if it's a Nil. */
  static constexpr BOL UsesStack() { return sizeof(buffer_) != 0; }

  /* Prints this autoject to the given printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TArrayPrint<T, SIZ>(o, Array());
  }

  void CPrint() { PrintTo<_::COut>(_::COut().Star()); }

 private:
  /* Gets the correct */
  RamFactory RamFactoryInit() {
    return sizeof(BUF) == 0 ? RamFactoryHeap : RamFactoryStack;
  }

  RamFactory RamFactoryInit(RamFactory factory) {
    return !factory ? RamFactoryInit() : factory;
  }
};

}  // namespace _

#endif
#endif
