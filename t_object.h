/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_object.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_3
#ifndef SCRIPT2_TOBJECT
#define SCRIPT2_TOBJECT 1

#include "c_object.h"
#include "t_socket.h"

#if SEAM == SCRIPT2_3
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* The minimum size of a NIL ASCII Object which is the size of the Size in
bytes. */
template <typename SIZ>
constexpr SIZ TObjSizeMin() {
  return sizeof(SIZ);
}

template <typename SIZ>
inline SIZ SizeWords(SIZ size) {
  return size >> kWordBitCount;
}

/* Writes the size to the given word-aligned-down socket, making a new one if
required. */
template <typename SIZ>
inline UIW* TObjInit(UIW* socket, SIZ size) {
  PRINT(kLF);
  PRINT_FUNCTION;
  PRINTF(" socket:0x%p size:%i", socket, (SI4)size);
  size = TAlignDownI<SIZ>(size);
  if (size < TObjSizeMin<SIZ>()) return nullptr;
  if (!socket) socket = new UIW[SizeWords<SIZ>(size)];
  *reinterpret_cast<SIZ*>(socket) = size;
  return socket;
}

/* Gets the ASCII CObject size. */
template <typename SIZ>
inline SIZ TObjSize(UIW* object) {
  return *reinterpret_cast<SIZ*>(object);
}

/* Gets the ASCII CObject size. */
template <typename SIZ>
inline SIZ TObjSize(CObject obj) {
  return TObjSize<SIZ>(obj.begin);
}

/* Attempts to set the ASCII CObject size.
@return Zero upon failure and the aligned size upon success. */
template <typename SIZ>
inline SIZ TObjSize(UIW* obj, SIZ size) {
  size = TAlignUpSigned<SIZ>(size);
  if ((size < sizeof(SIZ)) || !obj || (size & ~kWordLSbMask)) return 0;
  *reinterpret_cast<SIZ*>(obj) = size;
  return size;
}

/* Gets the ASCII CObject size. */
template <typename SIZ>
inline SIZ TObjSize(CObject obj, SIZ size) {
  return TObjSize<SIZ>(obj.begin, size);
}

template <typename SIZ>
inline void TObjSizeSet(UIW* begin, SIZ size) {
  *reinterpret_cast<SIZ*>(object) = size;
}

/* The maximum object size.
The max ASCII Object size is dictated by the max value allowed that can be
aligned up to a multiple of 8 (i.e. 64-bit word boundary). */
template <typename SI>
inline SI TObjSizeMax() {
  SI count_max = 0;
  return (~count_max) - 15;
}

/* Checks if the given object count is in the min max bounds of an ASCII
Object. */
template <typename SI>
inline BOL TObjCountIsValid(SI index, SI count_min) {
  return (index >= count_min) && (index < TObjSizeMax<SI>());
}

/* Creates dynamic memory..
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename SIZ = SI4>
UIW* TObjNew(SIZ size) {
  UIW* begin;
  try {
    begin = new UIW[size >> TBitShiftCount<>()];
  } catch (const std::bad_alloc& exception) {
    ObjException(exception.what());
    return nullptr;
  }
  *reinterpret_cast<SIZ*>(begin) = size;
  return begin;
}

/* Clones the other ASCII CObject including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename SIZ = SI4>
UIW* TObjClone(UIW* socket, SIZ size) {
  UIW* clone = TObjNew<SIZ>(SizeWords<SIZ>(size));
  if (!SocketCopy(clone, size, socket, size)) return nullptr;
  *reinterpret_cast<SIZ*>(socket) = size;
  return clone;
}

/* Checks of the given size is able to double in size.
@return True if the object can double in size. */
template <typename SIZ>
SIN TObjCanGrow(SIZ size) {
  return !(size >> (sizeof(SIZ) * 8 - 2));
}

/* Checks if the size is in the min max bounds of an ASCII Object.
@return 0 If the size is valid. */
template <typename SIZ = SIW>
inline SIN TObjCanGrow(SIZ size, SIZ size_min) {
  if (size < size_min) return kFactorySizeInvalid;
  return TObjCanGrow<SIZ>(size);
}

/* Grows the given CObject to the new_size.
It is not possible to shrink a raw ASCII object because one must call the
specific factory function for that type of Object. */
template <typename SIZ>
SIN TObjGrow(CObject& obj, SIZ new_size) {
  UIW* begin = obj.begin;
  if (!begin) return kFactoryNilOBJ;
  SIZ size = *reinterpret_cast<SIZ*>(begin);
  if (!TObjCanGrow<SIZ>(new_size)) return kFactorySizeInvalid;
  size = size << 1;  // size *= 2;
  obj.begin = TObjClone<SIZ>(begin, size);
  return kFactorySuccess;
}

/* Grows the given CObject to the new_size.
It is not possible to shrink a raw ASCII object because one must call the
specific factory function for that type of Object. */
template <typename SIZ>
UIW* TObjGrowDouble(UIW* begin) {
  if (!begin) return nullptr;
  SIZ size = TObjSize<SIZ>(begin) << 1;
  if (!TObjCanGrow<SIZ>(size)) return nullptr;
  return TObjNew<SIZ>(size);
}

template <typename SIZ>
inline SI4 TObjCanGrow(CObject& obj) {
  return TObjGrow(obj, TObjSize<SIZ>(obj) << 1);
}

/* Gets the last UI1 in the ASCII Object.
The object end, unlike the UTF which the stop pointer is at the last CH1 in
the object, the end of a socket is an out of bounds address. For this reason,
it is best to cap the object size as the highest possible value that you can
word-align to produce a valid result, which is 3 bytes on 32-bit systems and
7 bytes on 64-bit systems. */
template <typename SIZ>
inline CH1* TObjEnd(CObject stack) {
  UIW* socket = stack.begin;
  ASSERT(socket);
  SIZ size = *reinterpret_cast<SIZ*>(socket);
  return reinterpret_cast<CH1*>(socket) + size;
}

/* Gets the last UI1 in the ASCII Object. */
template <typename SIZ>
inline const CH1* TObjEnd(const CObject stack) {
  UIW* socket = stack.begin;
  SIZ size = *reinterpret_cast<SIZ*>(socket);
  return reinterpret_cast<const CH1*>(socket) + size;
}

/* Creates a new object of the given size that is greater than the min_size.
 */
template <typename SIZ>
UIW* TObjNew(SIZ size, SIZ size_min) {
  if (!TObjCanGrow<SIZ>(size, size_min)) return nullptr;

  size = TAlignUpSigned<SIZ>(size, kWordLSbMask);
  UIW* socket = new UIW[SizeWords<SIZ>(size)];
  *reinterpret_cast<SIZ*>(socket) = size;
  return socket;
}

/* Prints this object to the COut. */
template <typename SIZ, typename Printer>
Printer& TObjPrintTo(Printer& o, CObject& obj) {
  o << "\nTObject<SI" << (CH1)('0' + sizeof(SIZ)) << '>';
  UIW* begin = obj.begin;
  if (begin) {
    SIZ size = *reinterpret_cast<SIZ*>(begin);
    o << " size:" << (SIW)size;
  }
  AsciiFactory factory = obj.factory;
  if (factory) {
    o << " factory:\"";
    CH1* info_string = 0;
    if (factory(obj, kFactoryInfo, &info_string)) {
      o << info_string;
    }
    o << '\"';
  }
  return o;
}

/* A contiguous ASCII Object that starts with the size.
 */
template <typename SIZ>
struct SOBJ {
  SIZ size;  //< The size of the OBJ in bytes.
};

/* A word-aligned Auto-Object with Ascii Factory.
ASCII Objects may only use 16-bit, 32-bit, and 64-bit signed integers for their
size. */
template <typename SIZ, typename BUF = Nil>
class AObject {
 public:
  /* Constructs a object with dynamically allocated memory based on if object is
  nil. */
  AObject() : obj_({nullptr, nullptr}) {
    // Nothing to do here! (:-)-/==<
  }

  /* Constructs a object with either statically or dynamically allocated memory
  based on if object is nil. */
  AObject(AsciiFactory factory)
      : obj_({factory(obj_, kFactoryNew, nullptr), factory}) {
    factory(obj_, 0, nullptr);
  }

  /* Constructs a object with either statically or dynamically allocated memory
  based on if object is nil. */
  AObject(SIZ size, AsciiFactory factory = nullptr)
      : obj_({BUF(size), factory}) {}

  /* Constructs a object with either statically or dynamically allocated
  memory based on if object is nil. */
  AObject(SIZ size, UIW* socket = nullptr, AsciiFactory factory = nullptr)
      : obj_({factory, TObjInit<SIZ>(socket, size)}) {}

  /* Constructs a object with either statically or dynamically allocated
  memory based on if object is nil. */
  AObject(UIW* socket, SIZ size, AsciiFactory factory = nullptr)
      : obj_({factory, TObjInit<SIZ>(socket, size)}) {}

  AObject(UIW* socket, AsciiFactory factory = nullptr)
      : obj_({factory, socket}) {}

  /* Destructor calls the AsciiFactory factory. */
  ~AObject() { Delete(obj_); }

  inline void BufferSet(Nil value) {}

  template <SIZ kSize_>
  inline void BufferSet(Nil value) {}

  inline BUF& Socket() { return socket_; }

  /* Returns the buffer_. */
  inline UIW* Begin() { return obj_.begin; }

  /* Sets the begin to the given pointer.
  @return Nil if the input is nil. */
  inline UIW* BeginSet(void* socket) { return ObjBeginSet(socket); }

  /* Returns the start of the OBJ. */
  template <typename T = CH1>
  inline T* Start() {
    UIW ptr = reinterpret_cast<UIW>(obj_.begin);
    return reinterpret_cast<T*>(ptr + sizeof(SIZ));
  }

  /* Gets the stop of the OBJ. */
  inline CH1* Stop() {
    SIZ size = TObjSize<SIZ>(obj_.begin);
    return reinterpret_cast<CH1*>(obj_.begin) + size - 1;
  }

  /* Gets the ASCII Object size in bytes. */
  inline SIZ Size() { return TObjSize<SIZ>(obj_); }

  /* Gets the AsciiFactory. */
  inline AsciiFactory Factory() { return obj_.factory; }

  inline AsciiFactory FactorySet(AsciiFactory factory) {
    obj_.factory = factory;
    return factory;
  }

  inline SI4 Do(SIW function, void* arg = nullptr) {
    return ObjDo(obj_, function, arg);
  }

  /* Gets the CObject. */
  inline CObject& CObj() { return obj_; }

  /* Attempts to grow the this object.
  @return false if the grow op failed. */
  inline BOL Grow() { return TObjCanGrow<SIZ>(obj_); }

  /* Sets the obj_ to the socket. */
  template <SIZ kSize_>
  AObject<SIZ, BUF>& operator=(const TSocket<SIZ, kSize_>& socket) {}

  AObject<SIZ, BUF>& operator=(const Nil& socket) {}

 private:
  CObject obj_;  //< ASCII CObject harness.
  BUF socket_;   //< An optional socket.
};

}  // namespace _

#endif
#endif
