/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /BSeq.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_BSEQ_DELC
#define SCRIPT2_BSEQ_DELC
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "TypeValue.h"
namespace _ {

/* Utility class for printing B-Sequences. */
struct BSeq {
  const ISC* params;  //< BSeq params.

  BSeq(const ISC* params) : params(params) {
    // Nothing to do here! (:-)-+=<
  }
};

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

constexpr ISC CBSeqSize(const ISC* params) {
  if (!params) {
    return 0;
  }
  ISC size_bytes = sizeof(ISC), count = *params++;

  if (count > cParamsMax) {
    return 0;
  }

  for (; count > 0; --count) {
    ISC param = *params++;

    if (param == cNIL) {  // This is illegal.
      return 0;
    }
    //if (param <= cTKN) {
    //  size_bytes += sizeof(ISC);
    //  ++params;
    //}
    if (param == cISE) {
      size_bytes += sizeof(ISC);
      ++params;
    }
    if (param == cIUE) {
      size_bytes += sizeof(ISC);
      ++params;
    }
    //if (param >= cLST && param <= cMAP) {  // This is illegal.
    //  return 0;
    //}
    //if (param > cMAP) {
    //  if (param >> 8) {  // This is an error.
    //    return 0;
    //  }
    //  if (param & 0x20) {     // It's a multi-dimensional array so
    //    param = *params;      // add the number_ of dimensions + 1;
    //    params += param + 1;  // for the dimension count.
    //  }
    //}
    size_bytes += sizeof(ISC);
  }
  return size_bytes;
}

/* Creates a immutable Script B-Sequence.
C++11 variadic template to ensure only one copy in ROM
and to eliminate some redundant typing. */
template <const ISC... N>
inline const ISC* TParams() {
  static const ISC cSize = 0,  // BsqSize ({ N... })
      cList[sizeof...(N)] = {N...};
  return &cSize;
}

/*< Returns the requested parameter number_. */
LIB_MEMBER ISC BSeqParamNumber(const ISN* bsq, ISN param_number);

}  //< namespace _

#endif
#endif
