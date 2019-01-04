/* Script
@version 0.x
@file    /cbsq.h
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
#if SEAM >= _0_0_0__14
#ifndef INCLUDED_SCRIPTVARINT
#define INCLUDED_SCRIPTVARINT

#include "config.h"

namespace _ {

#if WORD_SIZE == 16
inline SI2 UnpackSVI(SI2 value) {
  if (value < 0) {
    UI2 result = 0x8000 return result | ~(value - 1);
  }
  return value;
}

inline SI2 PackSVI(SI2 value) {
  if (value < 0) {
    UI2 result = 1 << 15;
    return result | ((~value + 1) << 1);
  }
  return value;
}
#else
inline SI4 UnpackSVI(SI4 value) {
  if (value < 0) {
    UI4 result = 0x80000000;
    return result | ~(value - 1);
  }
  return value;
}

inline SI4 PackSVI(SI4 value) {
  if (value < 0) {
    SI4 result = 0x80000000;
    return result | ((~value + 1) << 1);
  }
  return value;
}
#endif

inline SI8 UnpackSV8(SI8 value) {
  if (value < 0) {
    SI8 result = 0x8000000000000000;
    return result | ~(value - 1);
  }
  return value;
}

inline SI8 PackSV8(SI8 value) {
  if (value < 0) {
    SI8 result = 0x8000000000000000;
    return result | ((~value + 1) << 1);
  }
  return value;
}

// template<typename T>
// T UnpackSVI (T value) {
//    T temp = value << sizeof (T) * 8 - 1;
//    temp |= value;
//    return temp;
//}

}  //< namespace _
#endif  //< INCLUDED_SCRIPTVARINT
#endif  //< #if SEAM >= _0_0_0__14
