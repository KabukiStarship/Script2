/* Script2�
@link    https://github.com/KabukiStarship/Script2.git
@file    /Array.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship� <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_ARRAY_TEMPLATES
#define SCRIPT2_ARRAY_TEMPLATES
#include "Array.h"
#include "Types.hpp"
namespace _ {

/* Overwrites the memory with fill_char; functionally equivalent to memset. */
inline CHA* RAMFill(void* start, void* stop, CHA fill_char) {
  return RAMFill(start, TPtr<CHA>(stop) - TPtr<CHA>(start) + 1, fill_char);
}

/* The maximum autoject size.
The max ASCII Object size is dictated by the max value allowed that can be
aligned up to a multiple of 8 (i.e. 64-bit word boundary). */
template<typename IS>
inline IS TArraySizeMax() {
  IS count_max = 0;
  return (~count_max) - 15;
}
/* The upper bounds defines exactly how many elements can fit into a space
in memory. */
template<typename T = ISW, typename IS = ISN, typename Class>
inline IS TArraySizeMax() {
  IS max_value = IS((~IS(0)) >> 1);
  return max_value - IS(sizeof(IUW) - 1 - sizeof(Class) / sizeof(T));
}
}  //< namespace _

#if SEAM >= SCRIPT2_STACK
#include "Binary.hpp"
#if SEAM == SCRIPT2_STACK
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
namespace _ {

// enum {
//  WordBitCount = (sizeof(void*) == 8) ? 3 : (sizeof(void*) == 4) ? 2 : 1
//};

inline IUW* AutojectBeginSet(Autoject& obj, void* buffer) {
  IUW* ptr = TPtr<IUW>(buffer);
  if (!ptr) return ptr;
  obj.origin = ptr;
  return ptr;
}

/* @ingroup AsciiArray
Please see the ASCII Data Specification for DRY documentation.
@link ./Spec/Data/vector_types/array.md */

/* Deletes the given obj using the obj.factory. */
inline void Delete(Autoject obj) {
  RAMFactory ram = obj.ram;
  if (ram) ram(obj.origin, 0);
}

/* An ASCII Array.
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/VectorTypes/Array.md

@code
+-----------------+
|  C-Style Array  |
|  255-byte array | size=255, requires 8-bits.
|-----------------|  ^
|  TArray Header  |  |
+-----------------+ 0xN
@endcode
*/
template<typename IS = ISN>
struct TArray {
  IS size;  //< Number of elements in the array.
};

/* Checks if the given autoject count is in the min max bounds of an ASCII
Object. */
template<typename T, typename IS>
inline BOL TArrayCountIsValid(IS index, IS count_min) {
  return (index >= count_min) && (index < TArraySizeMax<T, IS>());
}

/* Gets the first byte of the ASCII Object data section. */
template<typename Class, typename T>
inline T* TArrayStart(Class* autoject) {
  ISW address = ISW(autoject);
  return TPtr<T>(address + ISW(sizeof(Class)));
}

/* Prints the item to the printer. */
template<typename T, typename IS, typename Printer>
Printer& TArrayPrint(Printer& o, const TArray<IS>* item) {
  IS size = item->size;
  o << Linef("\n+---\nTArray<IS") << TSizef<IS>()
    << "> size:" << size;
  if (size == 0) return o;
  T* items = TArrayStart<T, IS>(item);
  IS i = 0;
  for (; i < size; ++i) {
    o << "\n| " << i << ".) " << items[i];
  }
  return o << Linef("\n+---");
}

// Copies the source to the destination.
template<typename T, typename IS = ISN, ISA AlignMask>
TArray<IS>* TArrayCopy(void* destination, const void* source) {
  auto dst = TPtr<IS>(destination);
  auto src = TPtr<const IS>(source);
  auto dst_count = *dst;
  auto src_count = *src;
  auto result = RAMCopy(TAlignUpPTR<>(dst + 1, AlignMask),
                        dst_count * sizeof(T),
                        TAlignUpPTR<>(src + 1, AlignMask),
                        src_count * sizeof(T));
  if (result <= 0) return nullptr;
  *dst = src_count;
  return TPtr<TArray<IS>>(dst);
}

/* Calculates the size in bytes of an array with given element_count. */
template<typename T, typename IS>
inline IS TSizeOf(IS element_count) {
  return sizeof(T) * element_count;
}

/* Calculates the size in bytes of an array with given element_count including
the Class header. */
template<typename T, typename IS, typename Class>
inline IS TSizeOf(IS size) {
  return sizeof(T) * size + sizeof(Class);
}

/* The minimum size of an array with zero elements. */
template<typename IS>
constexpr IS CSizeMin() {
  return 0;
}

/* Sets the size to the new_size*/
template<typename IS>
inline IUW* TSizeSet(IUW* origin, IS new_size) {
  *TPtr<IS>(origin) = new_size;
  return origin;
}

template<typename IS>
inline IS TSizeSet(Autoject& autoject, IS new_size) {
  return TSizeSet<IS>(autoject.origin, new_size);
}

/* Gets the ASCII Autoject size. */
template<typename IS>
inline IS TSize(IUW* origin) {
  return *TPtr<IS>(origin);
}

/* Gets the ASCII Autoject size. */
template<typename IS>
inline IS TSize(Autoject& autoject) {
  return TSize<IS>(autoject.origin);
}

/* Gets the ASCII Autoject size. */
template<typename T, typename IS, typename Class>
inline IS TSizeBytes(IS size) {
  return sizeof(Class) + sizeof(T) * size;
}
template<typename T, typename IS, typename Class>
inline IS TSizeBytes(IUW* origin) {
  return TSizeBytes<T, IS, Class>(TSize<IS>(origin));
}
template<typename T, typename IS, typename Class>
inline IS TSizeBytes(Autoject& autoject) {
  return TSizeBytes<T, IS, Class>(autoject.origin);
}

/* Gets the ASCII Autoject size in CPU words. */
template<typename T, typename IS, typename Class>
inline IS TSizeWords(IS size) {
  IS size_aligned_up = AlignUp(TSizeBytes<T, IS, Class>(size));
  return size_aligned_up >> ACPUBitCount;
}
template<typename T, typename IS, typename Class>
inline IS TSizeWords(IUW* origin) {
  return TSizeWords<T, IS, Class>(TSize<IS>(origin));
}
template<typename T, typename IS, typename Class>
inline IS TSizeWords(Autoject& autoject) {
  return TSizeWords<T, IS, Class>(autoject.origin);
}

/* Dynamically allocates a new Array of the given size.
@return Nil upon failure or a pointer to the cloned autoject upon success.
@param socket A raw ASCII Socket to clone. */
template<typename T, typename IS = ISN, typename Class>
IUW* TRAMFactoryNew(RAMFactory factory, IS size) {
  IUW* origin = factory(nullptr, TSizeBytes<T, IS, Class>(size));
  TSizeSet<IS>(origin, size);
  return origin;
}

/* Writes the size to the given word-aligned-down socket, making a new one if
required. */
template<typename T, typename IS>
inline IUW* TArrayInit(Autoject& obj, IUW* buffer, IS size,
                       RAMFactory ram) {
  D_ASSERT(ram);
  D_ASSERT(size >= CSizeMin<IS>());
  obj.ram = ram;
  if (!buffer) {
    IS buffer_size = AlignUp(IS(size * sizeof(T) + sizeof(TArray<IS>)));
    buffer = ram(nullptr, buffer_size);
  }
  D_ARRAY_WIPE(buffer, size * sizeof(T) + sizeof(TArray<IS>));
  TSizeSet<IS>(buffer, size);
  obj.origin = buffer;
  return buffer;
}

/* Writes the source TArray to the destination. */
template<typename T = IUA, typename IS = ISN, typename Class>
TArray<IS>* TArrayWrite(TArray<IS>* destination, TArray<IS>* source,
                         IS size) {
  D_ASSERT(destination);
  D_ASSERT(source);

  ISW size_bytes = (ISW)TSizeBytes<T, IS, Class>(size);
  if (!RAMCopy(destination, size_bytes, source, size_bytes)) return nullptr;
  return destination;
}

template<typename T = IUA, typename IS = ISN, typename Class>
IUW* TArrayWrite(IUW* destination, IUW* source, IS size) {
  TArray<IS>* result =
      TArrayWrite<T, IS, Class>(TPtr<TArray<IS>>(destination),
                                 TPtr<TArray<IS>>(source), size);
  return TPtr<IUW>(result);
}

/* Clones the other ASCII Autoject including possibly unused autoject space.
@return Nil upon failure or a pointer to the cloned autoject upon success.
@param socket A raw ASCII Socket to clone. */
template<typename T = IUA, typename IS = ISN, typename Class>
IUW* TArrayClone(Autoject& obj) {
  RAMFactory factory = obj.ram;
  IUW* origin = obj.origin;
  // if (!factory || !origin) return nullptr;

  TArray<IS>* o = TPtr<TArray<IS>>(origin);
  IS size = o->size;
  IUW* clone = TRAMFactoryNew<T, IS, TArray<IS>>(size);
  return TArrayWrite<T, IS, Class>(clone, origin, size);
}

/* Checks of the given size is able to double in size.
@return True if the autoject can double in size. */
template<typename IS>
BOL TCanGrow(IS size) {
  auto size_new = size >> (sizeof(IS) * 8 - 2);
  if (size_new == 0) return true;
  COut("\n\nError! Max size hit! size:").Star() << size;
  return false;

}

/* Resizes the given array.
@return True upon success and false upon failure. */
template<typename T, typename IS, typename Class>
BOL TArrayResize(Autoject& obj, IS new_size) {
  D_COUT("\nResizing Array to new_size:" << new_size);
  IUW* buffer = obj.origin;
  if (!buffer) return false;
  IS size = TSizeBytes<IS>(buffer);
  if (size < new_size) {
    if (size <= 0) return false;
    TSizeSet<IS>(buffer, new_size);
    return true;
  }
  IUW* new_begin = obj.ram(nullptr, new_size);
  TSizeSet<IS>(new_begin, new_size);
  TArrayWrite<T, IS, Class>(new_begin, buffer, new_size);
  obj.origin = new_begin;
  return true;
}

/* Resizes the given array to double it's prior capacity.
@return True upon success and false upon failure. */
template<typename T, typename IS, typename Class>
BOL TArrayGrow(Autoject& obj) {
  IS size = TSizeBytes<IS>(obj.origin);
  if (!TCanGrow<IS>(size)) return false;
  return TArrayResize<T, IS, Class>(obj, size << 1);
}

/* Gets the last IUA in the ASCII Object.
The autoject end, unlike the UTF which the stop pointer is at the last CHA in
the autoject, the end of a socket is an out of bounds address. For this reason,
it is best to cap the autoject size as the highest possible value that you can
word-align to produce a valid result, which is 3 bytes on 32-bit systems and
7 bytes on 64-bit systems. */
template<typename IS>
inline CHA* TArrayEnd(Autoject stack) {
  IUW* socket = stack.origin;
  A_ASSERT(socket);
  IS size = *TPtr<IS>(socket);
  return TPtr<CHA>(socket) + size;
}

/* Gets the last IUA in the ASCII Object. */
template<typename IS>
inline const CHA* TArrayEnd(const Autoject stack) {
  IUW* socket = stack.origin;
  IS size = *TPtr<IS>(socket);
  return TPtr<const CHA>(socket) + size;
}

/* Returns the start of the OBJ. */
template<typename T = CHA, typename IS, typename Class>
inline T* TArrayStart(TArray<IS>* obj) {
  IUW start = IUW(obj) + sizeof(Class);
  return TPtr<T>(start);
}

/* Returns the start of the OBJ. */
template<typename T = CHA, typename IS>
inline T* TArrayStart(IUW* obj) {
  return TArrayStart<T, IS>(TPtr<TArray<IS>>(obj));
}

/* Gets the stop of the TArray. */
template<typename T = CHA, typename IS>
inline T* TArrayStop(TArray<IS>* ary) {
  return TArrayStart<T, IS>(ary) + ary->size - 1;
}

/* Returns the stop of the OBJ. */
template<typename T = CHA, typename IS>
inline T* TArrayStop(IUW* obj) {
  return TArrayStop<T, IS>(TPtr<TArray<IS>>(obj));
}

/* Prints this autoject to the COut. */
template<typename IS, typename Printer>
Printer& TArrayPrint(Printer& o, Autoject& obj) {
  o << "\nAutoject<IS" << CHA('0' + sizeof(IS)) << '>';
  IUW* origin = obj.origin;
  if (origin) {
    IS size = *TPtr<IS>(origin);
    o << " size:" << (ISW)size;
  }
  return o;
}

/* An invalid index. */
template<typename IS>
constexpr IS CInvalidIndex() {
  return -1;
}

/* Searches for the item in the elements.
@return An invalid index upon failure or a valid index upon success. */
template<typename T, typename IS>
IS TArrayFind(const T* elements, IS element_count, const T& item) {
  for (IS i = 0; i < element_count; ++i)
    if (*elements++ == item) return i;
  return CInvalidIndex<IS>();
}

/* Compares the two memory sockets.
@param start  The start of Array A.
@param stop   The stop of Array A.
@param origin  The origin of Array B.
@param end    The end of Array B.
@return True if they are the same and false if they are not. */
inline ISW RAMCompare(const void* a_begin, const void* end_a,
                        const void* b_begin, const void* end_b) {
  return RAMCompare(a_begin, SizeOf(a_begin, end_a), b_begin,
                      SizeOf(b_begin, end_b));
}

/* Compares the two memory sockets.
@param start The start of Array A.
@param stop  The stop of Array A.
@param origin The origin of Array B.
@param size  The size of Array B.
@return True if they are the same and false if they are not. */
inline ISW RAMCompare(const void* a_begin, void* a_end, const void* b_begin,
                        ISW b_size_bytes) {
  return RAMCompare(a_begin, a_end, a_begin,
                      TPtr<CHA>(b_begin) + b_size_bytes);
}

/* Casts RAMCompare to type T. */
template<typename T>
inline T* TArrayCompare(void* a_begin, void* a_end, void* b_begin,
                        ISW b_size_bytes) {
  return TPtr<T*>(RAMCompare(a_begin, a_end, b_begin, b_size_bytes));
}

/* Casts RAMCompare to type T. */
template<typename T>
inline const T* TArrayCompare(const void* a_begin, void* a_end, const void* b_begin,
  ISW b_size_bytes) {
  return TPtr<const T*>(RAMCompare(a_begin, a_end, b_begin, b_size_bytes));
}

/* A word-aligned array of Size_ elements of T on the progam stack. */
template<ISW Size_ = ACPUCacheLineSize, typename T = IUA, typename IS = ISN,
          typename Class = Nil>
class TBUF {
 public:
  /* Default destructor does nothing. */
  TBUF() : words_() {}

  /* Returns the socket as a IUW*. */
  inline IUW* Words() { return words_; }

  /* Gets the end word of the socket. */
  inline IUW* WordsEnd() { return &words_[SizeWords()]; }

  /* Gets the stop word of the socket. */
  inline IUW* WordsStop() { return WordsEnd() - 1; }

  /* Gets the origin element of the socket. */
  template<typename T = CHA>
  inline T* Begin() {
    return TPtr<T>(words_);
  }

  /* Returns the first element of the ASCII Object data section. */
  template<typename RT = T>
  inline RT* Start() {
    ISW address = IUW(words_);
    return TPtr<RT>(address + sizeof(Class));
  }

  /* Gets the end element of the socket. */
  inline T* End() { return &words_[SizeWords()]; }

  /* Returns the last element of the ASCII Object data section. */
  inline T* Stop() { return Start<>() + Size() - 1; }

  /* Gets the origin of the socket. */
  template<typename T = CHA, typename IS = ISW>
  inline T& Element(IS index) {
    if (index < 0 || index >= Size()) return nullptr;
    return Start()[index];
  }

  /* Sets the size to the new value. */
  template<typename ISW>
  inline IUW* SizeSet(ISW size) {
    A_ASSERT((size & ACPUAlignMask) == 0)
    *TPtr<ISW>(words_) = size;
    return words_;
  }

  /* The size in elements. */
  static constexpr IS Size() { return IS((Size_ < 0) ? 0 : IS(Size_)); }

  /* The size in bytes including the header. */
  static constexpr IS SizeBytes() {
    return Size() * sizeof(T) + sizeof(Class);
  }

  /* The size in words rounded down. */
  static constexpr IS SizeWords() { return CSizeWords<IS>(SizeBytes()); }

 private:
  IUW words_[SizeWords()];  //< The word-aligned socket.
};

/* A Block of heap. */
template<DTB Type>
class TRAMFactory {
  /* RAMFactory for the Stack deletes a non-nil buffer. */
  static IUW* RAMFactoryHeap(IUW* buffer, ISW size_bytes) {
    if (size_bytes == 0) return (IUW*)RAMFactoryHeap;
    if (size_bytes < 0) return TPtr<IUW>(IUW(Type));
    return _::RAMFactoryHeap(buffer, size_bytes);
  }

  /* RAMFactory for the Stack doesn't delete a non-nil buffer. */
  static IUW* RAMFactoryStack(IUW* buffer, ISW size_bytes) {
    if (size_bytes == 0) return (IUW*)RAMFactoryHeap;
    if (size_bytes < 0) return TPtr<IUW>(Type);
    return _::RAMFactoryStack(buffer, size_bytes);
  }

  /* Gets the initial RAMFactory for the program stack or heap. */
  template<typename BUF>
  static constexpr RAMFactory RamFactoryInit() {
    return (sizeof(BUF) == 0) ? RAMFactoryHeap : RAMFactoryStack;
  }

 public:
  /* Does nothing. */
  TRAMFactory() {}

  /* Gets the RAMFactory to use upon construction. */
  template<typename BUF>
  inline RAMFactory Init() {
    return RamFactoryInit<BUF>();
  }

  /* Gets the RAMFactory to use upon construction. */
  template<typename BUF>
  inline RAMFactory Init(RAMFactory factory) {
    return (!factory) ? RamFactoryInit<BUF>() : factory;
  }
};

/* An Auto-Array.
Arrays may only use 16-bit, 32-bit, and 64-bit signed integers for their
size. */
template<typename T, typename IS = ISN, typename BUF = Nil>
class AArray {
  Autoject obj_;  //< Automatic Object.
  BUF buffer_;    //< Optional buffer on the program stack.

 public:
  /* Gets the ASCII Data Type. */
  static constexpr DTA Type() { return CATypeSize<IS, DTA>(_ARY); }

  /* Constructs. */
  AArray() {
    TArrayInit<T, IS>(obj_, buffer_.Words(), IS(buffer_.Size()),
                       TRAMFactory<Type()>().Init<BUF>());
  }

  /* Creates a autoject with either statically or dynamically allocated
  memory based on the size can fit in the buffer_. If the buffer_ is
  statically allocated but the size can't fit in the buffer a new block of
  dynamic memory will be created. */
  AArray(IS size, RAMFactory ram = nullptr) {
    TArrayInit<T, IS>(obj_, buffer_.Words(), size,
                       TRAMFactory<Type()>().Init<BUF>(ram));
  }

  /* Stores the origin and ram to the obj_. */
  AArray(IUW* origin, RAMFactory ram) {
    obj_.origin = origin;
    obj_.ram = ram;
  }

  /* Destructor calls the RAMFactory factory. */
  ~AArray() { Delete(obj_); }

  /* Gets the buffer_. */
  inline BUF& Buffer() { return buffer_; }

  /* Returns the buffer_. */
  inline IUW* Origin() { return obj_.origin; }

  template<typename T = TStack<IS>>
  inline T OriginAs() {
    return reinterpret_cast<T>(Origin());
  }

  /* Sets the origin to the given pointer.
  @return Nil if the input is nil. */
  inline IUW* OriginSet(void* socket) { return AutojectBeginSet(obj_, socket); }

  /* Gets the ASCII Object size in elements. */
  inline IS Size() { return TSize<IS>(obj_.origin); }

  /* Gets the total ASCII Object size in bytes. */
  template<typename Class = TArray<IS>>
  inline IS SizeBytes() {
    return TSizeBytes<T, IS, Class>(AJT());
  }

  /* Gets the total ASCII Object size in words. */
  template<typename Class = TArray<IS>>
  inline IS SizeWords() {
    return TSizeWords<T, IS, Class>(AJT());
  }

  /* Returns the start of the OBJ. */
  inline T* Start() {
    IUW ptr = IUW(obj_.origin) + sizeof(TArray<IS>);
    return TPtr<T>(ptr);
  }

  /* Gets the stop of the OBJ. */
  inline CHA* Stop() {
    return TPtr<CHA>(obj_.origin) + SizeBytes() - 1;
  }

  /* Gets the Autoject. */
  inline Autoject& AJT() { return obj_; }

  /* Gets the TArray<ISZ> for this object. */
  inline TArray<IS>* Array() {
    return TPtr<TArray<IS>>(obj_.origin);
  }

  /* Attempts to grow the this autoject.
  @return false if the grow op failed. */
  inline BOL CanGrow() { return TCanGrow<IS>(obj_); }

  /* Doubles the size of the obj_ array. */
  template<typename Class>
  inline void Grow() {
    TArrayGrow<T, IS, Class>(obj_);
  }

  /* Returns true if the buffer is a Socket and false if it's a Nil. */
  static constexpr BOL UsesStack() { return sizeof(buffer_) != 0; }

  /* Prints this autoject to the given printer. */
  template<typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TArrayPrint<T, IS>(o, Array());
  }

  void CPrint() { PrintTo<_::COut>(_::StdOut()); }
};

}  //< namespace _

#endif
#endif
