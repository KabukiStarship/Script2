/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tobject.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#if SEAM >= _0_0_0__03
#ifndef SCRIPT2_TOBJECT
#define SCRIPT2_TOBJECT 1

#include "cobject.h"

#include "tsocket.h"

#if SEAM == _0_0_0__03
#include "test_debug.inl"
#else
#include "test_release.inl"
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
  PRINTF("\nsocket:0x%p size:%i", socket, (SI4)size);
  size = TAlignDownI<Size>(size);
  if (size < TObjSizeMin<Size>()) return nullptr;
  if (!socket) socket = new UIW[SizeWords<Size>(size)];
  *reinterpret_cast<Size*>(socket) = size;
  return socket;
}

/* The maximum object size.
The max ASCII Object size is dictated by the max value allowed that can be
aligned up to a multiple of 8 (i.e. 64-bit word boundary). */
template <typename SI>
inline SI TObjSizeMax() {
  SI count_max = 0;
  return (~count_max) - 15;
}

/* Checks if the size is in the min max bounds of an ASCII Object.
@return 0 If the size is valid. */
template <typename Size = SIW>
inline SI4 TObjCanGrow(Size size, Size size_min) {
  if (size < size_min) return kFactorySizeInvalid;
  size = size >> (sizeof(Size) * 8 - 2);
  return (SI4)size;
}

/* Checks if the given object count is in the min max bounds of an ASCII
Object. */
template <typename SI>
inline BOL TObjCountIsValid(SI index, SI count_min) {
  return (index >= count_min) && (index < TObjSizeMax<SI>());
}

/* Gets the ASCII CObject size. */
template <typename Size>
inline Size TObjSize(UIW* object) {
  ASSERT(object);
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
Size TObjSizeRound(Size size) {
  return size & kObjSizeBuffer;
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
  ASSERT(socket);
  Size size = *reinterpret_cast<Size*>(socket);
  return reinterpret_cast<const CH1*>(socket) + size;
}

/* Creates a new object of the given size that is greater than the min_size.
 */
template <typename Size>
UIW* TObjNew(Size size, Size size_min) {
  if (!TObjCanGrow<Size>(size, size_min)) return nullptr;

  size = TAlignUpSigned<SI2>(size, kWordLSbMask);
  UIW* socket = new UIW[SizeWords<Size>(size)];
  *reinterpret_cast<Size*>(socket) = size;
  return socket;
}

/* Clones the other ASCII CObject including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename Size = SI4>
UIW* TObjClone(UIW* socket, Size size) {
  UIW* clone;
  try {
    clone = new UIW[SizeWords<Size>(size)];
  } catch (const std::bad_alloc& exception) {
    ObjException(exception.what());
    return nullptr;
  }
  SocketCopy(clone, size, socket, size);
  *reinterpret_cast<Size*>(socket) = size;
  return clone;
}

/* Clones the other ASCII CObject including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone.
template <typename Size = SI4>
inline UIW* TObjClone(CObject& obj) {
  return TObjFactoryStack<Size>(obj, kFactoryClone, nullptr);
} */

/* Checks of the given size is able to double in size.
@return True if the object can double in size. */
template <typename Size>
SI4 TObjCanGrow(Size size) {
  return (SI4)(size >> (sizeof(Size) * 8 - 2));
}

/* Grows the given CObject to the new_size.
It is not possible to shrink a raw ASCII object because one must call the
specific factory function for that type of Object. */
template <typename Size>
SI4 TObjCanGrow(CObject& obj, Size new_size) {
  UIW* begin = obj.begin;
  if (!begin) return kFactoryNilOBJ;
  Size size = *reinterpret_cast<Size*>(begin);
  if (!TObjCanGrow<Size>(size)) return kFactorySizeInvalid;
  size = size << 1;  // size *= 2;
  obj.begin = TObjClone<Size>(begin, size);
  delete[] begin;
  return kFactorySuccess;
}

template <typename Size>
inline SI4 TObjCanGrow(CObject& obj) {
  return TObjCanGrow(obj, TObjSize<Size>(obj) * 2);
}
/* A contiguous ASCII Object that starts with the size.
 */
template <typename Size>
struct OBJ {
  Size size;  //< The size of the OBJ in bytes.
};

/* A 64-bit word-aligned ASCII CObject.
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
  TObject(Size size, AsciiFactory factory = nullptr)
      : obj_({Buffer(size), factory}) {}

  /* Constructs a object with either statically or dynamically allocated
  memory based on if object is nil. */
  TObject(Size size, UIW* socket = nullptr, AsciiFactory factory = nullptr)
      : obj_({TObjInit<Size>(socket, size), factory}) {}

  /* Constructs a object with either statically or dynamically allocated
  memory based on if object is nil. */
  TObject(UIW* socket, Size size, AsciiFactory factory = nullptr)
      : obj_({TObjInit<Size>(socket, size), factory}) {}

  TObject(UIW* socket, AsciiFactory factory = nullptr)
      : obj_({socket, factory}) {}

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
  template <typename T = char>
  inline T* Start() {
    UIW ptr = reinterpret_cast<UIW>(obj_.begin);
    return reinterpret_cast<T*>(ptr + sizeof(Size));
  }

  /* Gets the stopping address of the object, AKA the address of the last
  element. */
  inline CH1* Stop() {
    Size size = TObjSize<Size>(obj_.begin);
    return reinterpret_cast<CH1*>(obj_.begin) + size - 1;
  }

  /* Gets the ASCII Object size. */
  inline Size SizeBytes() { return TObjSize<Size>(obj_); }

  /* Gets the AsciiFactory. */
  inline AsciiFactory Factory() { return obj_.factory; }

  /* Gets the CObject. */
  inline CObject& Obj() { return obj_; }

  /* Attempts to grow the this object.
  @return false if the grow op failed. */
  inline BOL Grow() { return TObjCanGrow<Size>(obj_); }

  /* Prints this object to the COut. */
  void Print() {
    ::_::Print("\nTObject<SI");
    ::_::Print('0' + sizeof(Size));
    ::_::Print(">");
    UIW* begin = obj_.begin;
    if (begin) {
      Size size = *reinterpret_cast<Size>(begin);
      ::_::Print(" size:");
      ::_::Print(size);
    }
    AsciiFactory factory = obj_.factory;
    if (factory) {
      ::_::Print(" factory:\"");
      const CH1 info_string;
      if (factory(obj_, kFactoryInfo, &info_string)) {
        ::_::Print(info_string);
      }
      ::_::Print('\"');
    }
  }

 private:
  CObject obj_;  //< ASCII CObject harness.
};               //< namespace _

}  // namespace _

#endif  //< SCRIPT2_TOBJECT
#endif  //< #if SEAM >= _0_0_0__03
