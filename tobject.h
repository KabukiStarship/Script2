/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script.git
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
inline SI ObjSizeMax() {
  SI count_max = 0;
  return (~count_max) - 15;
}

/* Checks if the size is in the min max bounds of an ASCII Object. */
template <typename SI = intptr_t>
inline BOL ObjSizeIsValid(SI size, SI size_min) {
  return (size >= size_min) && (size <= ObjSizeMax<SI>());
}

/* Checks if the given object count is in the min max bounds of an ASCII
Object. */
template <typename SI>
inline BOL ObjCountIsValid(SI index, SI count_min) {
  return (index >= count_min) && (index < ObjSizeMax<SI>());
}

/* Gets the ASCII kOBJ size. */
template <typename Size>
inline Size ObjSize(uintptr_t* object) {
  ASSERT(object);
  return *reinterpret_cast<Size*>(object);
}

/* Gets the ASCII kOBJ size. */
template <typename Size>
inline Size ObjSize(CObject obj) {
  ASSERT(obj.begin);
  return *reinterpret_cast<Size*>(obj.begin);
}

/* Gets the last byte in the ASCII Object. */
template <typename Size>
inline char* ObjEnd(CObject obj) {
  uintptr_t buffer = obj.begin;
  ASSERT(buffer);
  Size size = *reinterpret_cast<Size*>(buffer);
  return reinterpret_cast<char*>(buffer + size);
}

/* Gets the last byte in the ASCII Object. */
template <typename Size>
inline const char* ObjEnd(const CObject obj) {
  uintptr_t buffer = obj.begin;
  ASSERT(buffer);
  Size size = *reinterpret_cast<Size*>(buffer);
  return reinterpret_cast<const char*>(buffer + size);
}

/* Creates a new object of the given size that is greater than the min_size. */
template <typename Size>
uintptr_t* ObjNew(Size size, Size size_min) {
  if (size < size_min) return nullptr;

  if (!ObjSizeIsValid<Size>(size, size_min)) return nullptr;

  size = AlignUp<UI2, SI2>(size, 7);
  uintptr_t* buffer = new uintptr_t[size >> kWordBitCount];
  *reinterpret_cast<SI2*>(buffer) = size;
  return buffer;
}

/* Auto-grows the given obj to the new_size. */
template <typename Size>
Size ObjResize(CObject obj, Size new_size) {
  ASSERT(obj.begin);
  if (!obj.manager) return 0;
  Size size = ObjSize<Size>(obj);
  if (new_size < size) return 0;
  uintptr_t* temp = obj.begin;
  obj.begin = ObjClone<Size>(temp, size);
  delete[] temp;
}

/* Auto-grows the given obj to the new_size. */
template <typename Size>
Size ObjGrow(CObject obj) {
  ASSERT(obj.begin);
  if (!obj.manager) return 0;
  Size size = ObjSize<Size>(obj), new_size = 2 * size;
  if (new_size < size) return 0;
  uintptr_t* temp = obj.begin;
  obj.begin = ObjClone<Size>(temp, size);
  delete[] temp;
}

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

/* Clones the other ASCII kOBJ. */
template <typename Size = SI4>
uintptr_t* ObjClone(uintptr_t* buffer, Size size) {
  ASSERT(buffer);

  uintptr_t* clone = new uintptr_t[size >> kWordBitCount];
  SocketCopy(clone, size, buffer, size);
  *reinterpret_cast<Size*>(buffer) = size;
  return clone;
}

/* A 64-bit word-aligned ASCII kOBJ.
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
  TObject(HeapManager destructor) : obj_({nullptr, destructor}) {
    // Nothing to do here! (:-)-/==<
  }

  /* Constructs a buffer with either statically or dynamically allocated memory
  based on if buffer is nil. */
  TObject(Size size, HeapManager destructor = nullptr)
      : obj_({Buffer(size), destructor}) {}

  /* Constructs a buffer with either statically or dynamically allocated
  memory based on if buffer is nil. */
  TObject(Size size, uintptr_t* buffer, HeapManager destructor = nullptr)
      : obj_({Buffer(size, buffer), destructor}) {}

  /* HeapManager deletes dynamic memory if is_dynamic_ is true. */
  ~TObject() { Delete(obj_); }

  /* Returns the buffer_. */
  uintptr_t* Begin() { return obj_.begin; }

  /* Returns the buffer_. */
  uintptr_t* GetStart() { return obj_.begin; }

  /* Gets the stopping address of the buffer. */
  char* GetStop() {
    Size size = ObjSize<Size>(obj_.begin);
    return reinterpret_cast<char*>(obj_.begin) + size - 1;
  }

  /* Gets the ASCII Object size. */
  Size GetSize() { return ObjSize<Size>(obj_); }

  /* Doubles the size of the buffer and copies the given byte_count.
  @return A positive size of the new buffer upon success and -1 upon failure.
  @param byte_count The number of bytes to copy after growing the buffer. */
  Size Grow(Size new_size) { return ObjGrow<Size>(obj_, new_size); }

  /* Gets the CObject. */
  inline CObject& OBJ() { return obj_.begin; }

 private:
  CObject obj_;  //< ASCII kOBJ harness.
};
}  // namespace _
#include "test_footer.inl"
#endif  //< INCLUDED_SCRIPTTOBJ
#endif  //< #if SEAM >= _0_0_0__02
