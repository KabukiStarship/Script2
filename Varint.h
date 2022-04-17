/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Varint.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_Config.h>

#if SEAM >= SCRIPT2_DIC
#ifndef INCLUDED_SCRIPTVARINT
#define INCLUDED_SCRIPTVARINT

namespace _ {

#if ALU_SIZE == ALU_16_BIT
inline ISB UnpackSVI(ISB value) {
  if (value < 0) {
    IUB result = 0x8000 return result | ~(value - 1);
  }
  return value;
}

inline ISB PackSVI(ISB value) {
  if (value < 0) {
    IUB result = 1 << 15;
    return result | ((~value + 1) << 1);
  }
  return value;
}
#else
inline ISC UnpackSVI(ISC value) {
  if (value < 0) {
    IUC result = 0x80000000;
    return result | ~(value - 1);
  }
  return value;
}

inline ISC PackSVI(ISC value) {
  if (value < 0) {
    ISC result = 0x80000000;
    return result | ((~value + 1) << 1);
  }
  return value;
}
#endif

inline ISD UnpackSV8(ISD value) {
  if (value < 0) {
    ISD result = 0x8000000000000000;
    return result | ~(value - 1);
  }
  return value;
}

inline ISD PackSV8(ISD value) {
  if (value < 0) {
    ISD result = 0x8000000000000000;
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
#endif
#endif
