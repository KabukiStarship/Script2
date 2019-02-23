/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_bsq.h
@author  Cale McCollough <cale@astartup.net>
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
#if SEAM >= SCRIPT2_14
#ifndef SCRIPT2_BSQ_C
#define SCRIPT2_BSQ_C

#include "c_asciidata.h"
#include "c_utf1.h"

namespace _ {

/* Utility class for printing B-Sequences. */
struct Bsq {
  const SI4* params;  //< Bsq params.

  Bsq(const SI4* params) : params(params) {
    // Nothing to do here! (:-)-+=<
  }
};

#if ALU_SIZE == 16
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

constexpr SI4 BsqSize(const SI4* params) {
  if (!params) {
    return 0;
  }
  SI4 size_bytes = sizeof(SI4), count = *params++;

  if (count > kParamsMax) {
    return 0;
  }

  for (; count > 0; --count) {
    SI4 param = *params++;

    if (param == kNIL) {  // This is illegal.
      return 0;
    }
    if (param <= kTKN) {
      size_bytes += sizeof(SI4);
      ++params;
    }
    if (param == kSIH) {
      size_bytes += sizeof(SI4);
      ++params;
    }
    if (param == kUIH) {
      size_bytes += sizeof(SI4);
      ++params;
    }
    if (param >= kLST && param <= kMAP) {  // This is illegal.
      return 0;
    }
    if (param > kMAP) {
      if (param >> 8) {  // This is an error.
        return 0;
      }
      if (param & 0x20) {     // It's a multi-dimensional array so
        param = *params;      // add the number_ of dimensions + 1;
        params += param + 1;  // for the dimension count.
      }
    }
    size_bytes += sizeof(SI4);
  }
  return size_bytes;
}

/* Creates a immutable Script B-Sequence.
    C++11 variadic template to ensure only one copy in ROM
    and to eliminate some redundant typing. */
template <const SI4... N>
inline const SI4* Params() {
  static const SI4 kSize = 0,  // BsqSize ({ N... })
      kList[sizeof...(N)] = {N...};
  return &kSize;
}

/* Prints out the kBSQ parameters. */
SDK UTF1& PrintBsq(UTF1& printer, const SI4* params);

/*  Prints out the parameters. */
// SDK UTF& PrintBsq (const SI4* bsq, UTF& utf);

/*< Returns the requested parameter number_. */
SDK SI4 BsqParamNumber(const SI4* bsq, SI4 param_number);

}  // namespace _

#if USING_UTF8 == YES
/*  Prints out the parameters. */
inline ::_::UTF1& operator<<(::_::UTF1& printer, ::_::Bsq bsq) {
  return ::_::PrintBsq(printer, bsq.params);
}
#endif  //< USING_UTF8
#if USING_UTF16 == YES
/*  Prints out the parameters. */
inline ::_::UTF2& operator<<(::_::UTF2& printer, ::_::Bsq bsq) {
  return ::_::PrintBsq(printer, bsq.params);
}
#endif  //< USING_UTF16
#if USING_UTF32 == YES
/*  Prints out the parameters. */
inline ::_::UTF4& operator<<(::_::UTF4& printer, ::_::Bsq bsq) {
  return ::_::PrintBsq(printer, bsq.params);
}
#endif  //< USING_UTF8 == YES

#endif  //< SCRIPT2_BSQ_C
#endif  //< #if SEAM >= SCRIPT2_14
