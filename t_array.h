/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_array.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_SEAM_STRAND
#ifndef SCRIPT2_TOBJECT
#define SCRIPT2_TOBJECT 1

#include "c_autoject.h"
#include "t_socket.h"

#if SEAM == SCRIPT2_SEAM_STRAND
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
constexpr SIZ TNaNSigned() {
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
constexpr SIZ TUnsignedMax() {
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

/* An array of homogeneous type and size types in the C format.

An array

# Array Memory Layout

@code
    +----------------+
    |  Packed Array  |  <-- Only if header_size = 0
    |----------------|
    |     Buffer     |
    |----------------|
    | Array Elements |
 ^  |----------------|
 |  | TArray Header  |
0xN +----------------+
@endcode
*/
template <typename SIZ = SI4>
struct TArray {
  SIZ size;  //< Size of the Array in elements.
};

/* The minimum size of an array with zero elements. */
template <typename SIZ>
constexpr SIZ TSizeMin() {
  return 0;
}

/* Gets the ASCII Autoject size. */
template <typename AsciiObject, typename T, typename SIZ>
inline SIZ TSizeOf() {
  return sizeof(AsciiObject) + (sizeof(T) * SIZ);
}

/* Gets the ASCII Autoject size. */
template <typename SIZ>
inline SIZ TSize(UIW* obj) {
  return *reinterpret_cast<SIZ*>(obj);
}

/* Gets the ASCII Autoject size. */
template <typename SIZ>
inline SIZ TSize(Autoject& object) {
  return TSize<SIZ>(object.begin);
}

template <typename SIZ>
inline void TSizeSet(UIW* obj, SIZ size) {
  *reinterpret_cast<SIZ*>(obj) = size;
}

/* Writes the size to the given word-aligned-up socket, making a new one if
required. */
template <typename SIZ>
inline UIW* TArrayInit(UIW* begin, SIZ size) {
  DASSERT(begin);
  DASSERT(size >= TSizeMin<SIZ>());
  TSizeSet<SIZ>(begin, size);
  return begin;
}

/* Writes the size to the given word-aligned-down socket, making a new one if
required. */
template <typename T, typename SIZ>
inline UIW* TArrayInit(Autoject& obj, UIW* buffer, SIZ size,
                       AsciiFactory factory) {
  DASSERT(factory);
  obj.factory = factory;
  if (!buffer) {
    SIZ buffer_size =
        TAlignUpSigned<SIZ>(size * sizeof(T) + sizeof(TArray<SIZ>));
    buffer = reinterpret_cast<UIW*>(factory(obj, kFactoryNew, buffer_size));
  }
  SOCKET_WIPE(buffer, size);
  obj.begin = buffer;
  return TArrayInit<SIZ>(buffer, size);
}

/* The maximum object size.
The max ASCII Object size is dictated by the max value allowed that can be
aligned up to a multiple of 8 (i.e. 64-bit word boundary). */
template <typename SI>
inline SI TArraySizeMax() {
  SI count_max = 0;
  return (~count_max) - 15;
}

/* Checks if the given object count is in the min max bounds of an ASCII
Object. */
template <typename SI>
inline BOL TArrayCountIsValid(SI index, SI count_min) {
  return (index >= count_min) && (index < TArraySizeMax<SI>());
}

/* Clones the other ASCII Autoject including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename SIZ = SI4>
UIW* TArrayClone(UIW* begin, SIZ size) {
  UIW* clone = TArrayNew<SIZ>(TSizeWords<SIZ>(size));
  if (!SocketCopy(clone, size, begin, size)) return nullptr;
  TSizeSet<SIZ>(begin, size);
  return clone;
}

/* Checks of the given size is able to double in size.
@return True if the object can double in size. */
template <typename SIZ>
SIN TArrayCanGrow(SIZ size) {
  return !(size >> (sizeof(SIZ) * 8 - 2));
}

/* Checks if the size is in the min max bounds of an ASCII Object.
@return 0 If the size is valid. */
template <typename SIZ = SIW>
inline SIN TArrayCanGrow(SIZ size, SIZ size_min) {
  if (size < size_min) return kFactorySizeInvalid;
  return TArrayCanGrow<SIZ>(size);
}

/* Grows the given Autoject to the new_size.
It is not possible to shrink a raw ASCII object because one must call the
specific factory function for that type of Object. */
template <typename SIZ>
SIN TArrayGrow(Autoject& obj, SIZ new_size) {
  UIW* begin = obj.begin;
  if (!begin) return kFactoryNilOBJ;
  SIZ size = *reinterpret_cast<SIZ*>(begin);
  if (!TArrayCanGrow<SIZ>(new_size)) return kFactorySizeInvalid;
  size = size << 1;  // size *= 2;
  obj.begin = TArrayClone<SIZ>(begin, size);
  return kFactorySuccess;
}

/* Grows the given Autoject to the new_size.
It is not possible to shrink a raw ASCII object because one must call the
specific factory function for that type of Object. */
template <typename SIZ>
UIW* TArrayGrowDouble(UIW* begin) {
  if (!begin) return nullptr;
  SIZ size = TSize<SIZ>(begin) << 1;
  if (!TArrayCanGrow<SIZ>(size)) return nullptr;
  return TArrayNew<SIZ>(size);
}

template <typename SIZ>
inline SI4 TArrayCanGrow(Autoject& obj) {
  return TArrayGrow(obj, TSize<SIZ>(obj) << 1);
}

/* Gets the last UI1 in the ASCII Object.
The object end, unlike the UTF which the stop pointer is at the last CH1 in
the object, the end of a socket is an out of bounds address. For this reason,
it is best to cap the object size as the highest possible value that you can
word-align to produce a valid result, which is 3 bytes on 32-bit systems and
7 bytes on 64-bit systems. */
template <typename SIZ>
inline CH1* TArrayEnd(Autoject stack) {
  UIW* socket = stack.begin;
  ASSERT(socket);
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
template <typename T = CH1, typename SIZ>
inline T* TArrayStart(TArray<SIZ>* obj) {
  UIW start = reinterpret_cast<UIW>(obj);
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

/* Creates a new object of the given size that is greater than the min_size.
 */
template <typename SIZ>
UIW* TArrayNew(SIZ size, SIZ size_min) {
  if (!TArrayCanGrow<SIZ>(size, size_min)) return nullptr;

  UIW* socket = New(TSizeWords<SIZ>(size));
  *reinterpret_cast<SIZ*>(socket) = size;
  return socket;
}

/* Creates dynamic memory..
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename SIZ = SI4>
UIW* TArrayNew(SIZ size) {
  UIW* begin;
  begin = New(size + sizeof(TArray<SIZ>));
  TSizeSet<SIZ>(begin, size);
  return begin;
}

template <typename T, typename SIZ, typename This = TArray<SIZ>>
UIW* TArrayClone(TArray<SIZ>* obj) {
  UIW* o = New(obj->size);
  if (!o) return o;

  return o;
}

/* Prints this object to the COut. */
template <typename SIZ, typename Printer>
Printer& TArrayPrintTo(Printer& o, Autoject& obj) {
  o << "\nAutoArray<SI" << (CH1)('0' + sizeof(SIZ)) << '>';
  UIW* begin = obj.begin;
  if (begin) {
    SIZ size = *reinterpret_cast<SIZ*>(begin);
    o << " size:" << (SIW)size;
  }
  AsciiFactory factory = obj.factory;
  if (factory) {
    o << " factory:\"";
    const CH1* info_string = factory(obj, kFactoryInfo, nullptr);
    if (info_string) o << info_string;
    o << '\"';
  }
  return o;
}

template <typename T, typename SIZ>
SIW TArrayFactory(Autoject& obj, SIW function, SIW arg, BOL using_heap) {
  SIZ size;
  UIW *begin, *new_begin;
  switch (function) {
    case kFactoryDelete: {
      PRINTF("\nEntering Array.Factory.%s.Delete:",
             using_heap ? "Heap" : "Stack");
      Delete(obj.begin, using_heap);
      return 0;
    }
    case kFactoryNew: {
      size = (SIZ)arg;
      PRINTF("\nEntering Array.Factory.%s.New: size:%i",
             using_heap ? "Heap" : "Stack", size);
      return reinterpret_cast<SIW>(New(size));
    }
    case kFactoryGrow: {
      PRINTF("\nEntering Array.Factory.Grow:", using_heap ? "Heap" : "Stack");
      begin = obj.begin;
      size = TSize<SIZ>(begin) << 1;
      if (!TArrayCanGrow<SIZ>(size)) return kFactoryCantGrow;
      new_begin = TArrayNew<SIZ>(size);
      if (!new_begin) return kFactoryCantGrow;
      goto Clone;
    }
    case kFactoryClone: {
      PRINTF("\nEntering Array.Factory.%s.Clone:",
             using_heap ? "Heap" : "Stack");
      begin = obj.begin;
      size = *reinterpret_cast<SIZ*>(begin);
      new_begin = nullptr;
      SocketCopy(TArrayStart<T, SIZ>(new_begin), size,
                 TArrayStart<T, SIZ>(begin), size >> 1);
      if (using_heap) Delete(begin);
      obj.begin = new_begin;
    Clone:
      new_begin = TArrayClone<T, SI4>(reinterpret_cast<TArray<SIZ>*>(arg));
      if (!new_begin) return kFactoryCantGrow;
      return reinterpret_cast<SIW>(new_begin);
    }
    case kFactoryInfo: {
      return reinterpret_cast<SIW>("Array");
    }
  }
  return function;
}

/* */
template <typename T, typename SIZ>
SIW TArrayFactoryStack(Autoject& obj, SIW function, SIW arg) {
  return TArrayFactory<T, SIZ>(obj, function, arg, kStack);
}

/* */
template <typename T, typename SIZ>
SIW TArrayFactoryHeap(Autoject& obj, SIW function, SIW arg) {
  return TArrayFactory<T, SIZ>(obj, function, arg, kHeap);
}

/* An Autoject Array of type T.
Arrays may only use 16-bit, 32-bit, and 64-bit signed integers for their
size. */
template <typename T, typename SIZ = SIN, typename BUF = Nil>
class AArray {
 public:
  /* Constructs . */
  AArray() {
    TArrayInit<T, SIZ>(obj_, buffer_.Buffer(), BufferCount(), FactoryInit());
  }

  /* Constructs a object with either statically or dynamically allocated memory
  based on if object is nil. */
  explicit AArray(AsciiFactory factory) {
    TArrayInit<T, SIZ>(obj_, buffer_.Buffer(), BufferCount(),
                       FactoryInit(factory));
  }

  /* Constructs a object with either statically or dynamically allocated memory
  based on if object is nil. */
  AArray(SIZ size) {
    TArrayInit<T, SIZ>(obj_, buffer_.Buffer(), size, FactoryInit());
  }

  /* Constructs a object with either statically or dynamically allocated memory
  based on the size can fit in the buffer_.
  If the buffer_ is statically allocated but the size can't fit in the buffer a
  new block of dynamic memory will be created. */
  AArray(SIZ size, AsciiFactory factory) {
    TArrayInit<T, SIZ>(obj_, buffer_.Buffer(), size, FactoryInit(factory));
  }

  /* Destructor calls the AsciiFactory factory. */
  ~AArray() { Delete(obj_); }

  /* Gets the number of elements the buffer_ can store. */
  constexpr SIZ BufferCount() {
    if (buffer_.Size() <= sizeof(TArray<SIZ>)) return 0;
    return (buffer_.Size() - sizeof(TArray<SIZ>)) / sizeof(T);
  }

  /* Gets the buffer_. */
  inline BUF& Buffer() { return buffer_; }

  /* Returns the buffer_. */
  inline UIW* BeginWord() { return obj_.begin; }

  /* Sets the begin to the given pointer.
  @return Nil if the input is nil. */
  inline UIW* BeginSet(void* socket) { return AutojectBeginSet(socket); }

  /* Returns the start of the OBJ. */
  inline T* Start() {
    UIW ptr = reinterpret_cast<UIW>(obj_.begin) + sizeof(TArray<SIZ>);
    return reinterpret_cast<T*>(ptr);
  }

  /* Gets the stop of the OBJ. */
  inline CH1* Stop() {
    SIZ size = TSize<SIZ>(obj_.begin);
    return reinterpret_cast<CH1*>(obj_.begin) + size - 1;
  }

  /* Gets the ASCII Object size in elements minus the header size. */
  inline SIZ Size() { return TSize<SIZ>(obj_.begin); }

  /* Gets the ASCII Object size in elements including the header size. */
  inline SIZ SizeBytes() { return TArraySizeBytes<SIZ>(obj_); }

  /* Gets the AsciiFactory. */
  inline AsciiFactory Factory() { return obj_.factory; }

  inline AsciiFactory FactorySet(AsciiFactory factory) {
    obj_.factory = factory;
    return factory;
  }
  /* Gets the Autoject. */
  inline Autoject& AObj() { return obj_; }

  /* Attempts to grow the this object.
  @return false if the grow op failed. */
  inline BOL Grow() { return TArrayCanGrow<SIZ>(obj_); }

  /* Returns true if the buffer is a Socket and false if it's a Nil. */
  static constexpr BOL UsesStack() { return sizeof(buffer_) != 0; }

  /* Prints this object to the given printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    SIZ size = TSize<SIZ>(obj_);
    o << "\nTArray<SI" << (char)('0' + sizeof(SIZ)) << "> size:" << size;
    if (size == 0) return o;
    T* ptr = Start();
    for (SIZ i = 0; i < size - 1; ++i) o << ptr++ << ", ";
    return o << ptr;
  }

 private:
  Autoject obj_;  //< Automatic Object.
  BUF buffer_;    //< Optional socket on the program stack.

  /* Gets the AsciiFactory based on if the BUF is Nil or a TSocket. */
  inline AsciiFactory FactoryInit() {
    return buffer_.Size() ? TArrayFactoryStack<T, SIZ>
                          : TArrayFactoryHeap<T, SIZ>;
  }

  /* Gets the AsciiFactory based on if the BUF is Nil or a TSocket. */
  inline AsciiFactory FactoryInit(AsciiFactory factory) {
    return factory ? factory : FactoryInit();
  }
};

}  // namespace _

#endif
#endif
