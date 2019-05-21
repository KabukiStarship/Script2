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
template <typename Size>
constexpr Size TObjSizeMin() {
  return sizeof(Size);
}

template <typename Size>
inline Size SizeWords(Size size) {
  return size >> kWordBitCount;
}

/* Writes the size to the given word-aligned-down socket, making a new one if
required. */
template <typename Size>
inline UIW* TObjInit(UIW* socket, Size size) {
  PRINT(kLF);
  PRINT_FUNCTION;
  PRINTF(" socket:0x%p size:%i", socket, (SI4)size);
  size = TAlignDownI<Size>(size);
  if (size < TObjSizeMin<Size>()) return nullptr;
  if (!socket) socket = new UIW[SizeWords<Size>(size)];
  *reinterpret_cast<Size*>(socket) = size;
  return socket;
}

/* Gets the ASCII CObject size. */
template <typename Size>
inline Size TObjSize(UIW* object) {
  return *reinterpret_cast<Size*>(object);
}

/* Gets the ASCII CObject size. */
template <typename Size>
inline Size TObjSize(CObject obj) {
  return TObjSize<Size>(obj.begin);
}

/* Attempts to set the ASCII CObject size.
@return Zero upon failure and the aligned size upon success. */
template <typename Size>
inline Size TObjSize(UIW* obj, Size size) {
  size = TAlignUpSigned<Size>(size);
  if ((size < sizeof(Size)) || !obj || (size & ~kWordLSbMask)) return 0;
  *reinterpret_cast<Size*>(obj) = size;
  return size;
}

/* Gets the ASCII CObject size. */
template <typename Size>
inline Size TObjSize(CObject obj, Size size) {
  return TObjSize<Size>(obj.begin, size);
}

template <typename Size>
inline void TObjSizeSet(UIW* begin, Size size) {
  *reinterpret_cast<Size*>(object) = size;
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

/* Clones the other ASCII CObject including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename Size = SI4>
UIW* TObjNew(Size size) {
  UIW* begin;
  try {
    begin = new UIW[size >> TBitShiftCount<>()];
  } catch (const std::bad_alloc& exception) {
    ObjException(exception.what());
    return nullptr;
  }
  *reinterpret_cast<Size*>(begin) = size;
  return begin;
}

/* Clones the other ASCII CObject including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename Size = SI4>
UIW* TObjClone(UIW* socket, Size size) {
  UIW* clone = TObjNew<Size>(SizeWords<Size>(size));
  if (!SocketCopy(clone, size, socket, size)) return nullptr;
  *reinterpret_cast<Size*>(socket) = size;
  return clone;
}

/* Checks of the given size is able to double in size.
@return True if the object can double in size. */
template <typename Size>
SIN TObjCanGrow(Size size) {
  return !(size >> (sizeof(Size) * 8 - 2));
}

/* Checks if the size is in the min max bounds of an ASCII Object.
@return 0 If the size is valid. */
template <typename Size = SIW>
inline SIN TObjCanGrow(Size size, Size size_min) {
  if (size < size_min) return kFactorySizeInvalid;
  return TObjCanGrow<Size>(size);
}

/* Grows the given CObject to the new_size.
It is not possible to shrink a raw ASCII object because one must call the
specific factory function for that type of Object. */
template <typename Size>
SIN TObjGrow(CObject& obj, Size new_size) {
  UIW* begin = obj.begin;
  if (!begin) return kFactoryNilOBJ;
  Size size = *reinterpret_cast<Size*>(begin);
  if (!TObjCanGrow<Size>(new_size)) return kFactorySizeInvalid;
  size = size << 1;  // size *= 2;
  obj.begin = TObjClone<Size>(begin, size);
  return kFactorySuccess;
}

/* Grows the given CObject to the new_size.
It is not possible to shrink a raw ASCII object because one must call the
specific factory function for that type of Object. */
template <typename Size>
UIW* TObjGrowDouble(UIW* begin) {
  if (!begin) return nullptr;
  Size size = TObjSize<Size>(begin) << 1;
  if (!TObjCanGrow<Size>(size)) return nullptr;
  return TObjNew<Size>(size);
}

template <typename Size>
inline SI4 TObjCanGrow(CObject& obj) {
  return TObjGrow(obj, TObjSize<Size>(obj) << 1);
}

/* Gets the last UI1 in the ASCII Object.
The object end, unlike the UTF which the stop pointer is at the last CH1 in
the object, the end of a socket is an out of bounds address. For this reason,
it is best to cap the object size as the highest possible value that you can
word-align to produce a valid result, which is 3 bytes on 32-bit systems and
7 bytes on 64-bit systems. */
template <typename Size>
inline CH1* TObjEnd(CObject stack) {
  UIW* socket = stack.begin;
  ASSERT(socket);
  Size size = *reinterpret_cast<Size*>(socket);
  return reinterpret_cast<CH1*>(socket) + size;
}

/* Gets the last UI1 in the ASCII Object. */
template <typename Size>
inline const CH1* TObjEnd(const CObject stack) {
  UIW* socket = stack.begin;
  Size size = *reinterpret_cast<Size*>(socket);
  return reinterpret_cast<const CH1*>(socket) + size;
}

/* Creates a new object of the given size that is greater than the min_size.
 */
template <typename Size>
UIW* TObjNew(Size size, Size size_min) {
  if (!TObjCanGrow<Size>(size, size_min)) return nullptr;

  size = TAlignUpSigned<Size>(size, kWordLSbMask);
  UIW* socket = new UIW[SizeWords<Size>(size)];
  *reinterpret_cast<Size*>(socket) = size;
  return socket;
}

/* A contiguous ASCII Object that starts with the size.
 */
template <typename Size>
struct OBJ {
  Size size;  //< The size of the OBJ in bytes.
};

/* A 64-bit word-aligned ASCII CObject.
ASCII Objects may only use 16-bit, 32-bit, and 64-bit signed integers for their
size.
*/
template <typename SIZ>
class TObject {
 public:
  /* Constructs a object with dynamically allocated memory based on if object is
  nil. */
  TObject() : obj_({nullptr, nullptr}) {
    // Nothing to do here! (:-)-/==<
  }

  /* Constructs a object with either statically or dynamically allocated memory
  based on if object is nil. */
  TObject(AsciiFactory factory)
      : obj_({factory(obj_, kFactoryNew, nullptr), factory}) {
    factory(obj_, 0, nullptr);
  }

  /* Constructs a object with either statically or dynamically allocated memory
  based on if object is nil. */
  TObject(SIZ size, AsciiFactory factory = nullptr)
      : obj_({Buffer(size), factory}) {}

  /* Constructs a object with either statically or dynamically allocated
  memory based on if object is nil. */
  TObject(SIZ size, UIW* socket = nullptr, AsciiFactory factory = nullptr)
      : obj_({factory, TObjInit<SIZ>(socket, size)}) {}

  /* Constructs a object with either statically or dynamically allocated
  memory based on if object is nil. */
  TObject(UIW* socket, SIZ size, AsciiFactory factory = nullptr)
      : obj_({factory, TObjInit<SIZ>(socket, size)}) {}

  TObject(UIW* socket, AsciiFactory factory = nullptr)
      : obj_({factory, socket}) {}

  /* Destructor calls the AsciiFactory factory. */
  ~TObject() { Delete(obj_); }

  /* Returns the buffer_. */
  inline UIW* Begin() { return obj_.begin; }

  /* Sets the begin to the given pointer.
  @return Nil if the input is nil. */
  inline UIW* SetBegin(UIW* socket) {
    if (!socket) return socket;
    obj_.begin = socket;
    return socket;
  }

  /* Returns the begin of the OBJ. */
  template <typename T = CH1>
  inline T* Start() {
    UIW ptr = reinterpret_cast<UIW>(obj_.begin);
    return reinterpret_cast<T*>(ptr + sizeof(SIZ));
  }

  /* Gets the stopping address of the object, AKA the address of the last
  element. */
  inline CH1* Stop() {
    SIZ size = TObjSize<SIZ>(obj_.begin);
    return reinterpret_cast<CH1*>(obj_.begin) + size - 1;
  }

  /* Gets the ASCII Object size. */
  inline SIZ Size() { return TObjSize<SIZ>(obj_); }

  /* Gets the AsciiFactory. */
  inline AsciiFactory Factory() { return obj_.factory; }

  inline AsciiFactory SetFactory(AsciiFactory factory) {
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

  /* Prints this object to the COut. */
  template <typename Printer>
  Printer& PrintTo(Printer& o) {
    o << "\nTObject<SI" << (CH1)('0' + sizeof(SIZ)) << '>';
    UIW* begin = obj_.begin;
    if (begin) {
      SIZ size = *reinterpret_cast<SIZ*>(begin);
      o << " size:" << (SIW)size;
    }
    AsciiFactory factory = obj_.factory;
    if (factory) {
      o << ".";
      CH1* info_string = 0;
      if (!factory(obj_, kFactoryInfo, &info_string)) {
        o << info_string;
      }
    }
    return o;
  }

 private:
  CObject obj_;  //< ASCII CObject harness.
};

}  // namespace _

#endif
#endif
