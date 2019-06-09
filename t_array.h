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

#if SEAM >= SCRIPT2_SEAM_STACK
#ifndef SCRIPT2_TOBJECT
#define SCRIPT2_TOBJECT 1

#include "c_autoject.h"
#include "t_socket.h"

#if SEAM == SCRIPT2_SEAM_STACK
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* @ingroup AsciiStack
Stack is an ASCII Data Type designed to use a C-style templated struct in C++
using no dynamic memory and with dynamic memory as a templated C++ warper class
and cross-language bindings and deterministic CPU cache optimizations. */

/* Returns the maximum value of the given unsigned type. */
template <typename UI>
inline UI TNaNUnsigned() {
  return ~((UI)0);
}

/* Returns the maximum value of the given signed type. */
template <typename SIZ>
constexpr SIZ TNaNSigned() {
  return (~ToUnsigned(SIZ)) >> 1;
}

/* An 1-dimensional array of homogeneous kind and size types in the C format.

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

/* The upper bounds defines exactly how many elements can fit into a space
in memory. */
template <typename T = SI4, typename SIZ = SI4, typename Class = TArray<SIZ>>
constexpr SIZ TArraySizeMax() {
  return (SIZ)((((~(SIZ)0) - 7) - (SIZ)sizeof(TStack<SIZ>)) / (SIZ)sizeof(T));
}

/* Gets the ASCII Autoject size. */
template <typename T, typename SIZ, typename Class = TArray<SIZ>>
inline SIW TArraySizeOf(SIZ size) {
  return (SIW)sizeof(Class) + ((SIW)sizeof(T) * (SIW)size);
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

/* Dynamically allocates a new Array of the given size.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename T, typename SIZ = SI4, typename Class = TArray<SIZ>>
UIW* TArrayNew(SIZ size) {
  UIW* begin = New(TArraySizeOf<T, SIZ, Class>(size));
  TSizeSet<SIZ>(begin, size);
  return begin;
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
  DASSERT(size >= TSizeMin<SIZ>());
  obj.factory = factory;
  if (!buffer) {
    SIZ buffer_size =
        TAlignUpSigned<SIZ>(size * sizeof(T) + sizeof(TArray<SIZ>));
    buffer = reinterpret_cast<UIW*>(factory(obj, kFactoryNew, buffer_size));
  }
  SOCKET_WIPE(buffer, size * sizeof(T) + sizeof(TArray<SIZ>));
  TSizeSet<SIZ>(buffer, size);
  obj.begin = buffer;
  return buffer;
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

template <typename T = UI1, typename SIZ = SI4, typename Class = TArray<SIZ>>
TArray<SIZ>* TArrayWrite(TArray<SIZ>* destination, TArray<SIZ>* source,
                         SIZ size) {
  DASSERT(destination && source);

  SIW size_bytes = (SIW)TArraySizeOf<T, SIZ, Class>(size);
  if (!SocketCopy(destination, size_bytes, source, size_bytes)) return nullptr;
  return destination;
}

template <typename T = UI1, typename SIZ = SI4, typename Class = TArray<SIZ>>
UIW* TArrayWrite(UIW* destination, UIW* source, SIZ size) {
  TArray<SIZ>* result =
      TArrayWrite<T, SIZ, Class>(reinterpret_cast<TArray<SIZ>*>(destination),
                                 reinterpret_cast<TArray<SIZ>*>(source), size);
  return reinterpret_cast<UIW*>(result);
}

/* Clones the other ASCII Autoject including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename T = UI1, typename SIZ = SI4, typename Class = TArray<SIZ>>
UIW* TArrayClone(Autoject& obj) {
  AsciiFactory factory = obj.factory;
  UIW* begin = obj.begin;
  // if (!factory || !begin) return nullptr;

  TArray<SIZ>* o = reinterpret_cast<TArray<SIZ>*>(begin);
  SIZ size = o->size;
  UIW* clone = TArrayNew<T, SIZ, TArray<SIZ>>(size);
  return TArrayWrite<T, SIZ, Class>(clone, begin, size);
}

/* Checks of the given size is able to double in size.
@return True if the object can double in size. */
template <typename SIZ>
BOL TArrayCanGrow(SIZ size) {
  return !(size >> (sizeof(SIZ) * 8 - 2));
}

/* Resizes the given array. */
template <typename T, typename SIZ, typename Class = TArray<SIZ>>
SIW TArrayResize(Autoject& obj, SIZ new_size) {
  UIW* begin = obj.begin;
  if (!begin) return kFactoryNilOBJ;
  SIZ size = TSize<SIZ>(begin);
  if (size < new_size) {
    if (size <= 0) return kFactorySizeInvalid;
    TSizeSet<SIZ>(begin, size);
    return kFactorySuccess;
  }
  UIW* new_begin = reinterpret_cast<UIW*>(obj.factory(obj, kFactoryNew, size));
  TArrayWrite<T, SIZ, Class>(new_begin, begin, new_size);
  obj.begin = new_begin;
  return kFactorySuccess;
}

/* Resizes the given array to double it's prior capacity.
@return an AsciiFactoryError code. */
template <typename T, typename SIZ, typename Class = TArray<SIZ>>
SIW TArrayGrow(Autoject& obj) {
  SIZ size = TSize<SIZ>(obj.begin);
  if (!TArrayCanGrow<SIZ>(size)) return kFactorySizeInvalid;
  return TArrayResize<T, SIZ, Class>(obj, size << 1);
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
  UIW start = reinterpret_cast<UIW>(obj) + sizeof TArray<SIZ>;
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
    const CH1* info_string = factory(obj, kFactoryName, nullptr);
    if (info_string) o << info_string;
    o << '\"';
  }
  return o;
}

template <typename T, typename SIZ>
SIW TArrayFactory(Autoject& obj, SIW function, SIW arg, BOL using_heap) {
  PRINT_FACTORY_FUNCTION("Array", function, using_heap);
  switch (function) {
    case kFactoryDelete: {
      Delete(obj.begin, using_heap);
      return 0;
    }
    case kFactoryNew: {
      return reinterpret_cast<SIW>(TArrayNew<T, SIZ>(arg));
    }
    case kFactoryGrow: {
      return TArrayGrow<T, SIZ>(obj);
    }
    case kFactoryClone: {
      return reinterpret_cast<SIW>(TArrayClone<T, SIZ>(obj));
    }
    case kFactoryName: {
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
  /* Constructs. */
  AArray() {
    TArrayInit<T, SIZ>(obj_, buffer_.Buffer(), buffer_.Size(), FactoryInit());
  }

  /* Constructs a object with either statically or dynamically allocated memory
  based on if object is nil. */
  explicit AArray(AsciiFactory factory) {
    TArrayInit<T, SIZ>(obj_, buffer_.Buffer(), buffer_.Size(),
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
  inline SIZ SizeBytes() { return TArraySizeOf<T, SIZ>(Size()); }

  /* Gets the AsciiFactory. */
  inline AsciiFactory Factory() { return obj_.factory; }

  /* Calls an AsciiFactory function with the given arg. */
  inline SIW Factory(SIW function, SIW arg) {
    return obj_.factory(obj_, function, arg);
  }

  inline AsciiFactory FactorySet(AsciiFactory factory) {
    obj_.factory = factory;
    return factory;
  }
  /* Gets the Autoject. */
  inline Autoject& AObj() { return obj_; }

  /* Attempts to grow the this object.
  @return false if the grow op failed. */
  inline BOL CanGrow() { return TArrayCanGrow<SIZ>(obj_); }

  template <typename Class = TArray<SIZ>>
  inline void Grow() {
    Factory(kFactoryGrow, 0);
  }

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
