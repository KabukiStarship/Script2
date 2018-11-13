/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tobject.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#if SEAM >= _0_0_0__02
#ifndef INCLUDED_SCRIPTTOBJ
#define INCLUDED_SCRIPTTOBJ

#include "cobject.h"

#include "tsocket.h"

#if SEAM == _0_0_0__02
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {
/* The maximum object size.
The max ASCII Object size is dictated by the max value allowed that can be
aligned up to a multiple of 8 (i.e. 64-bit word boundary). */
template <typename SI>
inline SI TObjSizeMax() {
  SI count_max = 0;
  return (~count_max) - 15;
}

/* Checks if the size is in the min max bounds of an ASCII Object. */
template <typename SI = SIW>
inline BOL TObjSizeIsValid(SI size, SI size_min) {
  return (size >= size_min) && (size <= TObjSizeMax<SI>());
}

/* Checks if the given object count is in the min max bounds of an ASCII
Object. */
template <typename SI>
inline BOL TObjCountIsValid(SI index, SI count_min) {
  return (index >= count_min) && (index < TObjSizeMax<SI>());
}

/* Gets the ASCII OBJ size. */
template <typename Size>
inline Size TObjSize(UIW* object) {
  ASSERT(object);
  return *reinterpret_cast<Size*>(object);
}

/* Gets the ASCII OBJ size. */
template <typename Size>
inline Size TObjSize(CObject obj) {
  ASSERT(obj.begin);
  return *reinterpret_cast<Size*>(obj.begin);
}

template <typename Size>
Size TObjSizeRound(Size size) {
  return size & kObjSizeBuffer;
}

/* Gets the last UI1 in the ASCII Object. */
template <typename Size>
inline char* TObjEnd(CObject obj) {
  UIW buffer = obj.begin;
  ASSERT(buffer);
  Size size = *reinterpret_cast<Size*>(buffer);
  return reinterpret_cast<char*>(buffer + size);
}

/* Gets the last UI1 in the ASCII Object. */
template <typename Size>
inline const char* TObjEnd(const CObject obj) {
  UIW buffer = obj.begin;
  ASSERT(buffer);
  Size size = *reinterpret_cast<Size*>(buffer);
  return reinterpret_cast<const char*>(buffer + size);
}

/* Creates a new object of the given size that is greater than the min_size. */
template <typename Size>
UIW* TObjNew(Size size, Size size_min) {
  if (size < size_min) return nullptr;

  if (!TObjSizeIsValid<Size>(size, size_min)) return nullptr;

  size = AlignUp<UI2, SI2>(size, 7);
  UIW* buffer = new UIW[size >> kWordBitCount];
  *reinterpret_cast<SI2*>(buffer) = size;
  return buffer;
}

/* Clones the other ASCII OBJ. */
template <typename Size = SI4>
UIW* TObjClone(UIW* buffer, Size size) {
  ASSERT(buffer);

  UIW* clone = new UIW[size >> kWordBitCount];
  SocketCopy(clone, size, buffer, size);
  *reinterpret_cast<Size*>(buffer) = size;
  return clone;
}

/* Auto-grows the given obj to the new_size. */
template <typename Size>
Size TObjResize(CObject obj, Size new_size) {
  ASSERT(obj.begin);
  if (!obj.factory) return 0;
  Size size = TObjSize<Size>(obj);
  if (new_size < size) return 0;
  UIW* temp = obj.begin;
  obj.begin = TObjClone<Size>(temp, size);
  delete[] temp;
}

/* Auto-grows the given obj to the new_size. */
template <typename Size = SI4>
UIW* ObjGrow(UIW* begin) {
  ASSERT(begin);
  Size size = *reinterpret_cast<Size*>(begin), new_size = 2 * size;
  if (new_size < size) return 0;
  UIW* temp = begin;
  begin = TObjClone<Size>(temp, size);
  delete[] temp;
  return begin;
}

/* Auto-grows the given obj to the new_size. */
template <typename Size>
Size ObjGrow(CObject obj) {}

/* Rounds the given count up to a 64-bit aligned value. */
template <typename T, typename UI = uint, typename SI = int>
inline SI ObjCountRound(SI count) {
  enum {
    kRoundEpochMask = (sizeof(SI) == 8)
                          ? 7
                          : (sizeof(SI) == 4) ? 3 : (sizeof(SI) == 2) ? 1 : 0,
  };
  return AlignUpSigned<SI>(count);
}

/* A 64-bit word-aligned ASCII OBJ.
ASCII Objects may only use 16-bit, 32-bit, and 64-bit signed integers for their
size. The minimum and maximum bounds of size of ASCII objects are defined by the
minimum size required to store the header with minimum item count, and the
highest positive integer multiple of 8. The fastest way to covert the upper
bounds is to invert the bits and subtract 7 as follows:

@code
SI2 upper_bounds_si2 = (~(SI2)0) - 7;
SI4 upper_bounds_si4 = (~(SI4)0) - 7;
SI8 upper_bounds_si8 = (~(SI8)0) - 7;
@endcode
*/
template <typename Size>
class TObject {
 public:
  /* Constructs a buffer with either statically or dynamically allocated memory
  based on if buffer is nil. */
  TObject() : obj_({nullptr, nullptr}) {
    // Nothing to do here! (:-)-/==<
  }

  /* Constructs a buffer with either statically or dynamically allocated memory
  based on if buffer is nil. */
  TObject(AsciiFactory factory) : obj_({nullptr, factory}) {
    // Nothing to do here! (:-)-/==<
  }

  /* Constructs a buffer with either statically or dynamically allocated memory
  based on if buffer is nil. */
  TObject(Size size, AsciiFactory factory = nullptr)
      : obj_({Buffer(size), factory}) {}

  /* Constructs a buffer with either statically or dynamically allocated
  memory based on if buffer is nil. */
  TObject(Size size, UIW* buffer, AsciiFactory factory = nullptr)
      : obj_({Buffer(size, buffer), factory}) {}

  /* Destructor calls the AsciiFactory factory. */
  ~TObject() { Destruct(obj_); }

  /* Returns the buffer_. */
  UIW* Begin() { return obj_.begin; }

  UIW* SetBegin(UIW* buffer) {
    if (!buffer) return buffer;
    obj_.begin = buffer;
    return buffer;
  }

  /* Returns the buffer_. */
  UIW* GetStart() { return obj_.begin; }

  /* Gets the stopping address of the buffer. */
  char* GetStop() {
    Size size = TObjSize<Size>(obj_.begin);
    return reinterpret_cast<char*>(obj_.begin) + size - 1;
  }

  /* Gets the ASCII Object size. */
  Size GetSize() { return TObjSize<Size>(obj_); }

  /* Gets the AsciiFactory. */
  AsciiFactory GetFactory() { return obj_.factory; }

  /* Gets the CObject. */
  inline CObject& OBJ() { return obj_; }

 private:
  CObject obj_;  //< ASCII OBJ harness.
};
}  // namespace _

#endif  //< INCLUDED_SCRIPTTOBJ
#endif  //< #if SEAM >= _0_0_0__02
