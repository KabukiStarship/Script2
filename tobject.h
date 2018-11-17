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

/* Gets the ASCII Obj size. */
template <typename Size>
inline Size TObjSize(UIW* object) {
  ASSERT(object);
  return *reinterpret_cast<Size*>(object);
}

/* Gets the ASCII Obj size. */
template <typename Size>
inline Size TObjSize(CObject stack) {
  ASSERT(stack.start);
  return *reinterpret_cast<Size*>(stack.start);
}

template <typename Size>
Size TObjSizeRound(Size size) {
  return size & kObjSizeBuffer;
}

/* Gets the last UI1 in the ASCII Object.
The object end, unlike the UTF which the stop pointer is at the last char in
the obj, the end of a socket is an out of bounds address. For this reason,
it is best to cap the obj size as the highest possible value that you can
word-align to produce a valid result, which is 3 bytes on 32-bit systems and
7 bytes on 64-bit systems. */
template <typename Size>
inline char* TObjEnd(CObject stack) {
  UIW socket = stack.start;
  ASSERT(socket);
  Size size = *reinterpret_cast<Size*>(socket);
  return reinterpret_cast<char*>(socket) + size;
}

/* Gets the last UI1 in the ASCII Object. */
template <typename Size>
inline const char* TObjEnd(const CObject stack) {
  UIW socket = stack.start;
  ASSERT(socket);
  Size size = *reinterpret_cast<Size*>(socket);
  return reinterpret_cast<const char*>(socket) + size;
}

/* Creates a new object of the given size that is greater than the min_size. */
template <typename Size>
UIW* TObjNew(Size size, Size size_min) {
  if (size < size_min) return nullptr;

  if (!TObjSizeIsValid<Size>(size, size_min)) return nullptr;

  size = TAlignUp<UI2, SI2>(size, 7);
  UIW* socket = new UIW[size >> kWordBitCount];
  *reinterpret_cast<Size*>(socket) = size;
  return socket;
}

/* Clones the other ASCII Obj including possibly unused obj space.
@return Nil upon failure or a pointer to the cloned obj upon success. */
template <typename Size = SI4>
UIW* TObjClone(UIW* socket) {
  if (!socket) return socket;
  Size size = *reinterpret_cast<Size*>(socket);
  UIW* clone = new UIW[size >> kWordBitCount];
  SocketCopy(clone, size, socket, size);
  *reinterpret_cast<Size*>(socket) = size;
  return clone;
}

/* Grows the given Obj to the new_size. */
template <typename Size>
Size TObjGrow(CObject stack, Size new_size) {
  if (!stack.start || !stack.factory) return 0;
  Size size = TObjSize<Size>(stack);
  if (new_size < size) return 0;
  UIW* temp = stack.start;
  stack.start = TObjClone<Size>(temp, size);
  delete[] temp;
}

/* Auto-grows the given Obj to double the current size; if possible.
@return Nil upon failure. */
template <typename Size = SI4>
UIW* TObjGrow(UIW* start) {
  ASSERT(start);
  Size size = *reinterpret_cast<Size*>(start), new_size = 2 * size;
  if (new_size < size) return 0;
  UIW* temp = start;
  start = TObjClone<Size>(temp, size);
  delete[] temp;
  return start;
}

/* Rounds the given count up to a 64-bit aligned value. */
template <typename T, typename UI = uint, typename SI = int>
inline SI TObjCountRound(SI count) {
  enum {
    kRoundEpochMask = (sizeof(SI) == 8)
                          ? 7
                          : (sizeof(SI) == 4) ? 3 : (sizeof(SI) == 2) ? 1 : 0,
  };
  return TAlignUpSigned<SI>(count);
}

/* A 64-bit word-aligned ASCII Obj.
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
  /* Constructs a obj with either statically or dynamically allocated memory
  based on if obj is nil. */
  TObject() : obj_({nullptr, nullptr}) {
    // Nothing to do here! (:-)-/==<
  }

  /* Constructs a obj with either statically or dynamically allocated memory
  based on if obj is nil. */
  TObject(AsciiFactory factory) : obj_({factory(0, 0, nullptr), factory}) {
    UIW* begin = factory(nullptr, 0, nullptr);
    *reinterpret_cast<Size*>(begin) =
        (Size) reinterpret_cast<uintptr_t>(factory(nullptr, 0, begin));
  }

  /* Constructs a obj with either statically or dynamically allocated memory
  based on if obj is nil. */
  TObject(Size size, AsciiFactory factory = nullptr)
      : obj_({Buffer(size), factory}) {}

  /* Constructs a obj with either statically or dynamically allocated
  memory based on if obj is nil. */
  TObject(Size size, UIW* socket, AsciiFactory factory = nullptr)
      : obj_({Buffer(size, socket), factory}) {}

  TObject(UIW* socket, AsciiFactory factory) : obj_({socket, factory}) {}

  /* Destructor calls the AsciiFactory factory. */
  ~TObject() { Destroy(obj_); }

  /* Returns the buffer_. */
  UIW* Begin() { return obj_.start; }

  UIW* SetBegin(UIW* socket) {
    if (!socket) return socket;
    obj_.start = socket;
    return socket;
  }

  /* Returns the buffer_. */
  UIW* GetStart() { return obj_.start; }

  /* Gets the stopping address of the obj. */
  char* GetStop() {
    Size size = TObjSize<Size>(obj_.start);
    return reinterpret_cast<char*>(obj_.start) + size - 1;
  }

  /* Gets the ASCII Object size. */
  Size GetSize() { return TObjSize<Size>(obj_); }

  /* Gets the AsciiFactory. */
  AsciiFactory GetFactory() { return obj_.factory; }

  /* Gets the CObject. */
  inline CObject& Obj() { return obj_; }

 private:
  CObject obj_;  //< ASCII Obj harness.
};

/* AsciiFactory prints the start to the console without deleting the
start.
@return If (size == 0 && start) then nil indicating success deleting the
memory. If passing in a . */
template <typename Size = int>
UIW* TObjectFactory(UIW* start, SIW function, void* arg) {
  switch (function) {
    case 0: {
      if (start) {
        delete[] start;
        return nullptr;
      }
      try {
        Size size = arg ? *reinterpret_cast<Size*>(arg) : kObjSizeDefault;
        return new UIW[size >> kWordBitCount];
      } catch (...) {
        return nullptr;
      }
    }
    case kFactoryGrow: {
      return TObjClone<Size>(start);
    }
    case kFactoryClone: {
      return TObjClone<Size>(start);
    }
  }
  return nullptr;
}

}  // namespace _

#endif  //< INCLUDED_SCRIPTTOBJ
#endif  //< #if SEAM >= _0_0_0__02
