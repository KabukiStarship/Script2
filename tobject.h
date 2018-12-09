/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tobject.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
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
#ifndef INCLUDED_SCRIPT2_TOBJECT
#define INCLUDED_SCRIPT2_TOBJECT

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

/* Gets the ASCII CObj size. */
template <typename Size>
inline Size TObjSize(UIW* object) {
  ASSERT(object);
  return *reinterpret_cast<Size*>(object);
}

/* Gets the ASCII CObj size. */
template <typename Size>
inline Size TObjSize(CObject obj) {
  ASSERT(obj.begin);
  return *reinterpret_cast<Size*>(obj.begin);
}

template <typename Size>
Size TObjSizeRound(Size size) {
  return size & kObjSizeBuffer;
}

/* Gets the last UI1 in the ASCII Object.
The object end, unlike the UTF which the stop pointer is at the last char in
the object, the end of a socket is an out of bounds address. For this reason,
it is best to cap the object size as the highest possible value that you can
word-align to produce a valid result, which is 3 bytes on 32-bit systems and
7 bytes on 64-bit systems. */
template <typename Size>
inline char* TObjEnd(CObject stack) {
  UIW* socket = stack.begin;
  ASSERT(socket);
  Size size = *reinterpret_cast<Size*>(socket);
  return reinterpret_cast<char*>(socket) + size;
}

/* Gets the last UI1 in the ASCII Object. */
template <typename Size>
inline const char* TObjEnd(const CObject stack) {
  UIW* socket = stack.begin;
  ASSERT(socket);
  Size size = *reinterpret_cast<Size*>(socket);
  return reinterpret_cast<const char*>(socket) + size;
}

/* Creates a new object of the given size that is greater than the min_size.
 */
template <typename Size>
UIW* TObjNew(Size size, Size size_min) {
  if (!TObjSizeIsValid<Size>(size, size_min)) return nullptr;

  size = TAlignUp<UI2, SI2>(size, 7);
  UIW* socket = new UIW[size >> kWordBitCount];
  *reinterpret_cast<Size*>(socket) = size;
  return socket;
}

/* Clones the other ASCII CObj including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename Size = SI4>
UIW* TObjClone(UIW* socket, Size size) {
  UIW* clone = new UIW[size >> kWordBitCount];
  SocketCopy(clone, size, socket, size);
  *reinterpret_cast<Size*>(socket) = size;
  return clone;
}

/* Clones the other ASCII CObj including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone.
template <typename Size = SI4>
inline UIW* TObjClone(CObject& obj) {
  return TObjFactory<Size>(obj, kFactoryClone, nullptr);
} */

/* Checks of the given size is able to double in size.
@return True if the object can double in size. */
template <typename Size>
BOL TObjCanGrow(Size size) {
  return (BOL)(size >> (sizeof(Size) * 8 - 2));
}

template <typename Size>
int TObjFactoryHeap(CObject& obj, SIW function, void* arg);

/* Standard ASCII Object Factory.
The ASCII Object Factory function table is defined by the kFactoryDelete enum.
*/
template <typename Size>
int TObjFactory(CObject& obj, SIW function, void* arg) {
  Size size;
  UIW *begin, *temp;
  switch (function) {
    case kFactoryDelete:
      return 0;
    case kFactoryNew:
      if (!arg) return kFactoryNilArg;
      size = TAlignUpSigned<Size>(*reinterpret_cast<Size*>(arg));
      if (size & kWordBitCount) return kFactorySizeInvalid;
      begin = new UIW[size >> kWordBitCount];
      obj.begin = begin;
      return 0;
    case kFactoryGrow:
      size = *reinterpret_cast<Size*>(obj.begin);
      if (!TObjCanGrow<Size>(size)) return kFactoryCantGrow;
      size = size << 1;  // << 1 to * 2
      temp = obj.begin;
      obj.begin = TObjClone<Size>(temp, size);
      return 0;
    case kFactoryClone:
      if (!arg) return kFactoryNilArg;
      CObject* other = reinterpret_cast<CObject*>(arg);
      begin = obj.begin;
      size = *reinterpret_cast<Size*>(begin);
      other->begin = TObjClone<Size>(begin, size);
      other->factory = TObjFactoryHeap<Size>;
      return 0;
  }
  return 0;
}

/* Standard ASCII Object Factory.
The ASCII Object Factory function table is defined by the kFactoryDelete enum.
*/
template <typename Size>
int TObjFactoryHeap(CObject& obj, SIW function, void* arg) {
  Size size;
  UIW *begin, *temp;
  switch (function) {
    case kFactoryDelete:
      begin = obj.begin;
      if (!begin) return kFactoryNilOBJ;
      delete[] begin;
      return 0;
    case kFactoryNew:
      size = TAlignUpSigned<Size>(*reinterpret_cast<Size*>(arg));
      if (size & kWordBitCount) return kFactorySizeInvalid;
      obj.begin = new UIW[size >> kWordBitCount];
      return 0;
    case kFactoryGrow:
      size = *reinterpret_cast<Size*>(obj.begin);
      if (!TObjCanGrow<Size>(size)) return kFactoryCantGrow;
      size = size << 1;  // << 1 to * 2
      temp = obj.begin;
      obj.begin = TObjClone<Size>(temp, size);
      delete[] temp;
      return 0;
    case kFactoryClone:
      if (!arg) return kFactoryNilArg;
      CObject* other = reinterpret_cast<CObject*>(arg);
      begin = obj.begin;
      size = *reinterpret_cast<Size*>(begin);
      other->begin = TObjClone<Size>(begin, size);
      other->factory = TObjFactoryHeap<Size>;
      return 0;
  }
  return 0;
}

template <typename Size>
UIW* TObjFactoryHeap(UIW* obj, SIW function, void* ptr) {}
/* Grows the given CObj to the new_size.
It is not possible to shrink a raw ASCII object because one must call the
specific factory function for that type of Object. */
template <typename Size>
int TObjGrow(CObject& obj, Size new_size) {
  return TObjFactory<Size>(obj, kFactoryGrow, nullptr);
}

/* Grows the given CObj to the new_size.
It is not possible to shrink a raw ASCII object. It is only possible to */
template <typename Size>
inline int TObjGrow(CObject& obj) {
  return TObjFactory<Size>(obj, kFactoryGrow, nullptr);
}

/* A contiguous ASCII Object that starts with the size.
 */
template <typename Size>
struct OBJ {
  Size size;  //< The size of the OBJ in bytes.
};

/* A 64-bit word-aligned ASCII CObj.
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
  /* Constructs a object with dynamically allocated memory
  based on if object is nil. */
  TObject() : obj_({nullptr, nullptr}) {
    // Nothing to do here! (:-)-/==<
  }

  /* Constructs a object with either statically or dynamically allocated memory
  based on if object is nil. */
  TObject(AsciiFactory factory)
      : obj_({factory(obj_, kFactoryNew, nullptr), factory}) {
    UIW* begin = factory(obj_, 0, nullptr);
    *reinterpret_cast<Size*>(begin) =
        (Size) reinterpret_cast<uintptr_t>(factory(nullptr, 0, begin));
  }

  /* Constructs a object with either statically or dynamically allocated memory
  based on if object is nil. */
  TObject(Size size, AsciiFactory factory = nullptr)
      : obj_({Buffer(size), factory}) {}

  /* Constructs a object with either statically or dynamically allocated
  memory based on if object is nil. */
  TObject(Size size, UIW* socket, AsciiFactory factory = nullptr)
      : obj_({Buffer(size, socket), factory}) {}

  TObject(UIW* socket, AsciiFactory factory = nullptr)
      : obj_({socket, factory}) {}

  /* Destructor calls the AsciiFactory factory. */
  ~TObject() { Delete(obj_); }

  /* Returns the buffer_. */
  inline UIW* Begin() { return obj_.begin; }

  inline UIW* SetBegin(UIW* socket) {
    if (!socket) return socket;
    obj_.begin = socket;
    return socket;
  }

  /* Returns the buffer_. */
  inline UIW* GetStart() { return obj_.begin; }

  /* Gets the stopping address of the object. */
  inline char* GetStop() {
    Size size = TObjSize<Size>(obj_.begin);
    return reinterpret_cast<char*>(obj_.begin) + size - 1;
  }

  /* Gets the ASCII Object size. */
  inline Size GetSize() { return TObjSize<Size>(obj_); }

  /* Gets the AsciiFactory. */
  inline AsciiFactory Factory() { return obj_.factory; }

  /* Gets the CObject. */
  inline CObject& CObj() { return obj_; }

  /* Attempts to grow the this object.
  @return false if the grow op failed. */
  inline BOL Grow() { return TObjGrow<Size>(obj_); }

 private:
  CObject obj_;  //< ASCII CObj harness.
};

}  // namespace _

#endif  //< INCLUDED_SCRIPT2_TOBJECT
#endif  //< #if SEAM >= _0_0_0__02
