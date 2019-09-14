/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /bsq.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_DICTIONARY
#ifndef INCLUDED_SCRIPTVARINT
#define INCLUDED_SCRIPTVARINT

namespace _ {

#if ALU_SIZE == ALU_16_BIT
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

}  // namespace _
#endif
#endif
