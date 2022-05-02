/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Array.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_ARRAY_TEMPLATES
#define SCRIPT2_ARRAY_TEMPLATES
#include "Array.h"
#include "TypeValue.hpp"
namespace _ {
  
/* Overwrites the memory with fill_char; functionally equivalent to memset. */
inline CHA* ArrayFill(void* start, void* stop, CHA fill_char) {
  return ArrayFill(start, TPtr<CHA>(stop) - TPtr<CHA>(start) + 1, fill_char);
}

/* The maximum autoject size.
The max ASCII Object size is dictated by the max value allowed that can be
aligned up to a multiple of 8 (i.e. 64-bit word boundary). */
template <typename IS>
inline IS TArraySizeMax() {
  IS count_max = 0;
  return (~count_max) - 15;
}
/* The upper bounds defines exactly how many elements can fit into a space
in memory. */
template <typename T = ISW, typename ISZ = ISN, typename Class>
inline ISZ TArraySizeMax() {
  ISZ max_value = ISZ((~ISZ(0)) >> 1);
  return max_value - ISZ(sizeof(IUW) - 1 - sizeof(Class) / sizeof(T));
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
//  cWordBitCount = (sizeof(void*) == 8) ? 3 : (sizeof(void*) == 4) ? 2 : 1
//};

inline IUW* AutojectBeginSet(Autoject& obj, void* buffer) {
  IUW* ptr = reinterpret_cast<IUW*>(buffer);
  if (!ptr) return ptr;
  obj.origin = ptr;
  return ptr;
}

/* @ingroup AsciiArray
Please see the ASCII Data Specification for DRY documentation.
@link ./Spec/Data/vector_types/array.md */

/* Deletes the given obj using the obj.factory. */
inline void Delete(Autoject obj) {
  SocketFactory socket_factory = obj.socket_factory;
  if (socket_factory) socket_factory(obj.origin, 0);
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
template <typename ISZ = ISN>
struct TArray {
  ISZ size;  //< Number of elements in the array.
};

/* Checks if the given autoject count is in the min max bounds of an ASCII
Object. */
template <typename T, typename IS>
inline BOL TArrayCountIsValid(IS index, IS count_min) {
  return (index >= count_min) && (index < TArraySizeMax<T, IS>());
}

/* Gets the first byte of the ASCII Object data section. */
template <typename Class, typename T>
inline T* TArrayStart(Class* autoject) {
  ISW address = reinterpret_cast<ISW>(autoject);
  return reinterpret_cast<T*>(address + sizeof(Class));
}

/* Prints the item to the printer*/
template <typename T, typename ISZ, typename Printer>
Printer& TArrayPrint(Printer& o, TArray<ISZ>* item) {
  ISZ size = item->size;
  o << Linef("\n+---\nTArray<IS") << CSizef<ISZ>()
    << "> size:" << size;
  if (size == 0) return o;
  T* items = TArrayStart<T, ISZ>(item);
  ISZ i = 0;
  for (; i < size; ++i) {
    o << "\n| " << i << ".) " << items[i];
  }
  return o << Linef("\n+---");
}

/* Calculates the size in bytes of an array with given element_count. */
template <typename T, typename IS>
inline IS TSizeOf(IS element_count) {
  return sizeof(T) * element_count;
}

/* Calculates the size in bytes of an array with given element_count including
the Class header. */
template <typename T, typename IS, typename Class>
inline IS TSizeOf(IS size) {
  return sizeof(T) * size + sizeof(Class);
}

/* The minimum size of an array with zero elements. */
template <typename ISZ>
constexpr ISZ CSizeMin() {
  return 0;
}

/* Sets the size to the new_size*/
template <typename ISZ>
inline IUW* TSizeSet(IUW* origin, ISZ new_size) {
  *reinterpret_cast<ISZ*>(origin) = new_size;
  return origin;
}

template <typename ISZ>
inline ISZ TSizeSet(Autoject& autoject, ISZ new_size) {
  return TSizeSet<ISZ>(autoject.origin, new_size);
}

/* Gets the ASCII Autoject size. */
template <typename ISZ>
inline ISZ TSize(IUW* origin) {
  return *reinterpret_cast<ISZ*>(origin);
}

/* Gets the ASCII Autoject size. */
template <typename ISZ>
inline ISZ TSize(Autoject& autoject) {
  return TSize<ISZ>(autoject.origin);
}

/* Gets the ASCII Autoject size. */
template <typename T, typename ISZ, typename Class>
inline ISZ TSizeBytes(ISZ size) {
  return sizeof(Class) + sizeof(T) * size;
}
template <typename T, typename ISZ, typename Class>
inline ISZ TSizeBytes(IUW* origin) {
  return TSizeBytes<T, ISZ, Class>(TSize<ISZ>(origin));
}
template <typename T, typename ISZ, typename Class>
inline ISZ TSizeBytes(Autoject& autoject) {
  return TSizeBytes<T, ISZ, Class>(autoject.origin);
}

/* Gets the ASCII Autoject size in CPU words. */
template <typename T, typename ISZ, typename Class>
inline ISZ TSizeWords(ISZ size) {
  ISZ size_aligned_up = AlignUp(TSizeBytes<T, ISZ, Class>(size));
  return size_aligned_up >> cWordBitCount;
}
template <typename T, typename ISZ, typename Class>
inline ISZ TSizeWords(IUW* origin) {
  return TSizeWords<T, ISZ, Class>(TSize<ISZ>(origin));
}
template <typename T, typename ISZ, typename Class>
inline ISZ TSizeWords(Autoject& autoject) {
  return TSizeWords<T, ISZ, Class>(autoject.origin);
}

/* Dynamically allocates a new Array of the given size.
@return Nil upon failure or a pointer to the cloned autoject upon success.
@param socket A raw ASCII Socket to clone. */
template <typename T, typename ISZ = ISN, typename Class>
IUW* TArrayNew(SocketFactory factory, ISZ size) {
  IUW* origin = factory(nullptr, TSizeBytes<T, ISZ, Class>(size));
  TSizeSet<ISZ>(origin, size);
  return origin;
}

/* Writes the size to the given word-aligned-down socket, making a new one if
required. */
template <typename T, typename ISZ>
inline IUW* TArrayInit(Autoject& obj, IUW* buffer, ISZ size,
                       SocketFactory socket_factory) {
  D_ASSERT(socket_factory);
  D_ASSERT(size >= CSizeMin<ISZ>());
  obj.socket_factory = socket_factory;
  if (!buffer) {
    ISZ buffer_size = AlignUp(ISZ(size * sizeof(T) + sizeof(TArray<ISZ>)));
    buffer = socket_factory(nullptr, buffer_size);
  }
  D_ARRAY_WIPE(buffer, size * sizeof(T) + sizeof(TArray<ISZ>));
  TSizeSet<ISZ>(buffer, size);
  obj.origin = buffer;
  return buffer;
}

/* Copies the source to the target functionally equivalent to memcpy.
@param start The start of the write socket.
@param stop  The stop of the write socket.
@param origin The origin of the read socket.
@param size  Number of bytes to copy.
@return Pointer to the last IUA written or nil upon failure. */
inline CHA* ArrayCopy(void* origin, void* stop, const void* read_start,
                      ISW read_size) {
  return ArrayCopy(origin, SizeOf(origin, stop), read_start, read_size);
}

/* Copies the source to the target functionally equivalent to memcpy.
@param origin The start of the write socket.
@param stop  The stop of the write socket.
@param origin The origin of the read socket.
@param size  Number of bytes to copy.
@return Pointer to the last IUA written or nil upon failure. */
inline CHA* ArrayCopy(void* origin, void* stop, const void* read_start,
                      const void* read_stop) {
  return ArrayCopy(origin, SizeOf(origin, stop), read_start,
                   SizeOf(read_start, read_stop));
}

/* Writes the source TArray to the destination. */
template <typename T = IUA, typename ISZ = ISN, typename Class>
TArray<ISZ>* TArrayWrite(TArray<ISZ>* destination, TArray<ISZ>* source,
                         ISZ size) {
  D_ASSERT(destination);
  D_ASSERT(source);

  ISW size_bytes = (ISW)TSizeBytes<T, ISZ, Class>(size);
  if (!ArrayCopy(destination, size_bytes, source, size_bytes)) return nullptr;
  return destination;
}

template <typename T = IUA, typename ISZ = ISN, typename Class>
IUW* TArrayWrite(IUW* destination, IUW* source, ISZ size) {
  TArray<ISZ>* result =
      TArrayWrite<T, ISZ, Class>(reinterpret_cast<TArray<ISZ>*>(destination),
                                 reinterpret_cast<TArray<ISZ>*>(source), size);
  return reinterpret_cast<IUW*>(result);
}

/* Clones the other ASCII Autoject including possibly unused autoject space.
@return Nil upon failure or a pointer to the cloned autoject upon success.
@param socket A raw ASCII Socket to clone. */
template <typename T = IUA, typename ISZ = ISN, typename Class>
IUW* TArrayClone(Autoject& obj) {
  SocketFactory factory = obj.socket_factory;
  IUW* origin = obj.origin;
  // if (!factory || !origin) return nullptr;

  TArray<ISZ>* o = reinterpret_cast<TArray<ISZ>*>(origin);
  ISZ size = o->size;
  IUW* clone = TArrayNew<T, ISZ, TArray<ISZ>>(size);
  return TArrayWrite<T, ISZ, Class>(clone, origin, size);
}

/* Checks of the given size is able to double in size.
@return True if the autoject can double in size. */
template <typename ISZ>
BOL TCanGrow(ISZ size) {
  return !(size >> (sizeof(ISZ) * 8 - 2));
}

/* Resizes the given array.
@return True upon success and false upon failure. */
template <typename T, typename ISZ, typename Class>
BOL TArrayResize(Autoject& obj, ISZ new_size) {
  D_COUT("\nResizing Array to new_size:" << new_size);
  IUW* buffer = obj.origin;
  if (!buffer) return false;
  ISZ size = TSizeBytes<ISZ>(buffer);
  if (size < new_size) {
    if (size <= 0) return false;
    TSizeSet<ISZ>(buffer, new_size);
    return true;
  }
  IUW* new_begin = obj.socket_factory(nullptr, new_size);
  TSizeSet<ISZ>(new_begin, new_size);
  TArrayWrite<T, ISZ, Class>(new_begin, buffer, new_size);
  obj.origin = new_begin;
  return true;
}

/* Resizes the given array to double it's prior capacity.
@return True upon success and false upon failure. */
template <typename T, typename ISZ, typename Class>
BOL TArrayGrow(Autoject& obj) {
  ISZ size = TSizeBytes<ISZ>(obj.origin);
  if (!TCanGrow<ISZ>(size)) return false;
  return TArrayResize<T, ISZ, Class>(obj, size << 1);
}

/* Gets the last IUA in the ASCII Object.
The autoject end, unlike the UTF which the stop pointer is at the last CHA in
the autoject, the end of a socket is an out of bounds address. For this reason,
it is best to cap the autoject size as the highest possible value that you can
word-align to produce a valid result, which is 3 bytes on 32-bit systems and
7 bytes on 64-bit systems. */
template <typename ISZ>
inline CHA* TArrayEnd(Autoject stack) {
  IUW* socket = stack.origin;
  A_ASSERT(socket);
  ISZ size = *reinterpret_cast<ISZ*>(socket);
  return TPtr<CHA>(socket) + size;
}

/* Gets the last IUA in the ASCII Object. */
template <typename ISZ>
inline const CHA* TArrayEnd(const Autoject stack) {
  IUW* socket = stack.origin;
  ISZ size = *reinterpret_cast<ISZ*>(socket);
  return reinterpret_cast<const CHA*>(socket) + size;
}

/* Returns the start of the OBJ. */
template <typename T = CHA, typename ISZ, typename Class>
inline T* TArrayStart(TArray<ISZ>* obj) {
  IUW start = reinterpret_cast<IUW>(obj) + sizeof(Class);
  return reinterpret_cast<T*>(start);
}

/* Returns the start of the OBJ. */
template <typename T = CHA, typename ISZ>
inline T* TArrayStart(IUW* obj) {
  return TArrayStart<T, ISZ>(reinterpret_cast<TArray<ISZ>*>(obj));
}

/* Gets the stop of the TArray. */
template <typename T = CHA, typename ISZ>
inline T* TArrayStop(TArray<ISZ>* ary) {
  return TArrayStart<T, ISZ>(ary) + ary->size - 1;
}

/* Returns the stop of the OBJ. */
template <typename T = CHA, typename ISZ>
inline T* TArrayStop(IUW* obj) {
  return TArrayStop<T, ISZ>(reinterpret_cast<TArray<ISZ>*>(obj));
}

/* Prints this autoject to the COut. */
template <typename ISZ, typename Printer>
Printer& TArrayPrint(Printer& o, Autoject& obj) {
  o << "\nAutoject<IS" << CHA('0' + sizeof(ISZ)) << '>';
  IUW* origin = obj.origin;
  if (origin) {
    ISZ size = *reinterpret_cast<ISZ*>(origin);
    o << " size:" << (ISW)size;
  }
  return o;
}

/* An invalid index. */
template <typename ISZ>
constexpr ISZ CInvalidIndex() {
  return -1;
}

/* Searches for the item in the elements.
@return An invalid index upon failure or a valid index upon success. */
template <typename T, typename ISZ>
ISZ TArrayFind(const T* elements, ISZ element_count, const T& item) {
  for (ISZ i = 0; i < element_count; ++i)
    if (*elements++ == item) return i;
  return CInvalidIndex<ISZ>();
}

/* Compares the two memory sockets.
@param start  The start of Array A.
@param stop   The stop of Array A.
@param origin  The origin of Array B.
@param end    The end of Array B.
@return True if they are the same and false if they are not. */
inline BOL ArrayCompare(const void* begin_a, const void* end_a,
                        const void* begin_b, const void* end_b) {
  return ArrayCompare(begin_a, SizeOf(begin_a, end_a), begin_b,
                      SizeOf(begin_b, end_b));
}

/* Compares the two memory sockets.
@param start The start of Array A.
@param stop  The stop of Array A.
@param origin The origin of Array B.
@param size  The size of Array B.
@return True if they are the same and false if they are not. */
inline BOL ArrayCompare(const void* begin_a, void* end_a, const void* begin_b,
                        ISW size_b) {
  return ArrayCompare(begin_a, end_a, begin_a,
                      reinterpret_cast<const CHA*>(begin_b) + size_b);
}

/* A word-aligned array of cSize_ elements of T on the progam stack. */
template <ISW cSize_ = cCpuCacheLineSize, typename T = IUA, typename ISZ = ISN,
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
  template <typename T = CHA>
  inline T* Begin() {
    return reinterpret_cast<T*>(words_);
  }

  /* Returns the first element of the ASCII Object data section. */
  template <typename RT = T>
  inline RT* Start() {
    ISW address = reinterpret_cast<IUW>(words_);
    return reinterpret_cast<RT*>(address + sizeof(Class));
  }

  /* Gets the end element of the socket. */
  inline T* End() { return &words_[SizeWords()]; }

  /* Returns the last element of the ASCII Object data section. */
  inline T* Stop() { return Start<>() + Size() - 1; }

  /* Gets the origin of the socket. */
  template <typename T = CHA, typename ISZ = ISW>
  inline T& Element(ISZ index) {
    if (index < 0 || index >= Size()) return nullptr;
    return Start()[index];
  }

  /* Sets the size to the new value. */
  template <typename ISW>
  inline IUW* SizeSet(ISW size) {
    A_ASSERT((size & cWordLSbMask) == 0)
    *reinterpret_cast<ISW*>(words_) = size;
    return words_;
  }

  /* The size in elements. */
  static constexpr ISZ Size() { return ISZ((cSize_ < 0) ? 0 : ISZ(cSize_)); }

  /* The size in bytes including the header. */
  static constexpr ISZ SizeBytes() {
    return Size() * sizeof(T) + sizeof(Class);
  }

  /* The size in words rounded down. */
  static constexpr ISZ SizeWords() { return CSizeWords<ISZ>(SizeBytes()); }

 private:
  IUW words_[SizeWords()];  //< The word-aligned socket.
};

/* A Block of heap. */
template <DTB cType>
class TRamFactory {
  /* SocketFactory for the Stack deletes a non-nil buffer. */
  static IUW* RamFactoryHeap(IUW* buffer, ISW size_bytes) {
    if (size_bytes == 0) return (IUW*)RamFactoryHeap;
    return _::RamFactoryHeap(buffer, size_bytes, cType);
  }

  /* SocketFactory for the Stack doesn't delete a non-nil buffer. */
  static IUW* RamFactoryStack(IUW* buffer, ISW size_bytes) {
    if (size_bytes == 0) return (IUW*)RamFactoryHeap;
    return _::RamFactoryStack(buffer, size_bytes, cType);
  }

  /* Gets the initial SocketFactory for the program stack or heap. */
  template <typename BUF>
  static constexpr SocketFactory RamFactoryInit() {
    return (sizeof(BUF) == 0) ? RamFactoryHeap : RamFactoryStack;
  }

 public:
  /* Does nothing. */
  TRamFactory() {}

  /* Gets the SocketFactory to use upon construction. */
  template <typename BUF>
  inline SocketFactory Init() {
    return RamFactoryInit<BUF>();
  }

  /* Gets the SocketFactory to use upon construction. */
  template <typename BUF>
  inline SocketFactory Init(SocketFactory factory) {
    return (!factory) ? RamFactoryInit<BUF>() : factory;
  }
};

/* An Auto-Array.
Arrays may only use 16-bit, 32-bit, and 64-bit signed integers for their
size. */
template <typename T, typename ISZ = ISN, typename BUF = Nil>
class AArray {
  Autoject obj_;  //< Automatic Object.
  BUF buffer_;    //< Optional buffer on the program stack.

 public:
  /* Gets the ASCII Data Type. */
  static constexpr DTA Type() { return CTypeSize<ISZ, DTA>(cARY); }

  /* Constructs. */
  AArray() {
    TArrayInit<T, ISZ>(obj_, buffer_.Words(), ISZ(buffer_.Size()),
                       TRamFactory<Type()>().Init<BUF>());
  }

  /* Creates a autoject with either statically or dynamically allocated
  memory based on the size can fit in the buffer_. If the buffer_ is
  statically allocated but the size can't fit in the buffer a new block of
  dynamic memory will be created. */
  AArray(ISZ size, SocketFactory socket_factory = nullptr) {
    TArrayInit<T, ISZ>(obj_, buffer_.Words(), size,
                       TRamFactory<Type()>().Init<BUF>(socket_factory));
  }

  /* Stores the origin and socket_factory to the obj_. */
  AArray(IUW* origin, SocketFactory socket_factory) {
    obj_.origin = origin;
    obj_.socket_factory = socket_factory;
  }

  /* Destructor calls the SocketFactory factory. */
  ~AArray() { Delete(obj_); }

  /* Gets the buffer_. */
  inline BUF& Buffer() { return buffer_; }

  /* Returns the buffer_. */
  inline IUW* Origin() { return obj_.origin; }

  template <typename T = TStack<ISZ>>
  inline T OriginAs() {
    return reinterpret_cast<T>(Origin());
  }

  /* Sets the origin to the given pointer.
  @return Nil if the input is nil. */
  inline IUW* OriginSet(void* socket) { return AutojectBeginSet(obj_, socket); }

  /* Gets the ASCII Object size in elements. */
  inline ISZ Size() { return TSize<ISZ>(obj_.origin); }

  /* Gets the total ASCII Object size in bytes. */
  template <typename Class = TArray<ISZ>>
  inline ISZ SizeBytes() {
    return TSizeBytes<T, ISZ, Class>(AJT());
  }

  /* Gets the total ASCII Object size in words. */
  template <typename Class = TArray<ISZ>>
  inline ISZ SizeWords() {
    return TSizeWords<T, ISZ, Class>(AJT());
  }

  /* Returns the start of the OBJ. */
  inline T* Start() {
    IUW ptr = reinterpret_cast<IUW>(obj_.origin) + sizeof(TArray<ISZ>);
    return reinterpret_cast<T*>(ptr);
  }

  /* Gets the stop of the OBJ. */
  inline CHA* Stop() {
    return TPtr<CHA>(obj_.origin) + SizeBytes() - 1;
  }

  /* Gets the Autoject. */
  inline Autoject& AJT() { return obj_; }

  /* Gets the TArray<ISZ> for this object. */
  inline TArray<ISZ>* Array() {
    return reinterpret_cast<TArray<ISZ>*>(obj_.origin);
  }

  /* Attempts to grow the this autoject.
  @return false if the grow op failed. */
  inline BOL CanGrow() { return TCanGrow<ISZ>(obj_); }

  /* Doubles the size of the obj_ array. */
  template <typename Class>
  inline void Grow() {
    TArrayGrow<T, ISZ, Class>(obj_);
  }

  /* Returns true if the buffer is a Socket and false if it's a Nil. */
  static constexpr BOL UsesStack() { return sizeof(buffer_) != 0; }

  /* Prints this autoject to the given printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TArrayPrint<T, ISZ>(o, Array());
  }

  void CPrint() { PrintTo<_::COut>(_::COut().Star()); }
};

}  //< namespace _

#endif
#endif
