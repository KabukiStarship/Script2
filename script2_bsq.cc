/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_bsq.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>
#if SEAM >= _0_0_0__14
#include "cbsq.h"

#include "ctest.h"
#include "cstr1.h"

namespace _ {

UIT BsqParamNumber(const UIT* params, int param_number) {
  if (!params) return 0;
  UIT num_params = *params++;
  if (param_number > num_params) return kNIL;
  int i;
  for (i = 0; i < param_number; ++i) {
    UIT value = params[i];
    if (value == kSTR)
      ++param_number;
    else if (value > 31) {  // It's an array!
      value = value >> 5;
      if (value < 4) {  // It's a single dimension!
        param_number += 2;
        break;
      } else if (value > 7) {  // Gratuitous explanation points!
        // PRINTF ("\nError";
        return kNIL;
      } else {
        param_number += params[i] + 1;
      }
    }
  }
  return params[i];
}

UTF1& PrintBsq(UTF1& utf, const UIT* params) {
  UIT num_params = *params++, i, type, value = 0;

  utf << "Param<";
  if (num_params > kParamsMax) {
    utf << "\nInvalid num_params: " << num_params;
    return utf;
  }
  utf << num_params << ": ";
  for (i = 1; i < num_params; ++i) {
    value = *params++;
    type = value & 0x1f;  //< Mask off type.
    value = value >> 5;   //< Shift over array type.
    utf << TypeString((SIN)value) << ", ";
    if (type >= kSTR) {
      if (value) {
        utf << "\nError: arrays may only be created from POD "
               "types.";
        return utf;
      }
      // Print out the max length of the string_.
      ++i;
      value = *params++;
      utf << value;
    } else if (value > 31) {
      if (value > 127) {  //< It's a multi-dimensional array.
        utf << "Multi-dimensional Array:" << value << ", ";
      }
      // Then it's an array.
      ++i;
      switch (value) {  //< Print out the Array type.
        case 0: {
          break;
        }
        case 1: {
          value = *params++;
          utf << "kUI1:" << value << ", ";
          break;
        }
        case 2: {
          value = *params++;
          utf << "kUI2:" << value << ", ";
          break;
        }
        case 3: {
          value = *params++;
          utf << "kUI4:" << value << ", ";
          break;
        }
        case 4: {
          value = *params++;
          utf << "kUI8:" << value << ", ";
          break;
        }
        case 5: {
          value = *params++;
          if (value == 0) {
            utf << "kUI1:[0]";
            break;
          }
          utf << "kUI1:[" << value << ": ";
          for (UIT i = value; i != 0; --i) {
            value = *params++;
            utf << value << ", ";
          }
          value = *params++;
          utf << value << "]";
          break;
        }
        case 6: {
          value = *params++;
          if (value == 0) {
            utf << "kUI2:[0]";
            break;
          }
          utf << "kUI2:[" << value << ": ";
          for (UIT i = value; i != 0; --i) {
            value = *params++;
            utf << value << ", ";
          }
          value = *params++;
          utf << value << "]";
          break;
        }
        case 7: {
          value = *params++;
          if (value == 0) {
            utf << "kUI4:[0]";
            break;
          }
          utf << "kUI4:[" << value << ": ";
          for (UIT i = value; i != 0; --i) {
            value = *params++;
            utf << value << ", ";
          }
          value = *params++;
          utf << value << "]";
          break;
        }
      }
    }
  }
  // Do the last set without a comma.
  value = *params++;
  utf << TypeString(value) << ", ";
  if (value == kSTR) {
    ++i;
    value = *params++;
    utf << value;
  } else if (value > 31) {
    // Then it's an array.
    type = value & 0x1f;  //< Mask off type.
    value = value >> 5;   //< Shift over array type.
    ++i;
    switch (value) {
      case 0: {
        break;
      }
      case 1: {
        value = *params++;
        utf << "kUI1:" << value << ", ";
        break;
      }
      case 2: {
        value = *params++;
        utf << "kUI2:" << value << ", ";
        break;
      }
      case 3: {
        value = *params++;
        utf << "kUI4:" << value << ", ";
        break;
      }
      case 4: {
        value = *params++;
        utf << "UI5:" << value << ", ";
        break;
      }
      case 5: {
        value = *params++;
        if (value == 0) {
          utf << "kUI1:[0]";
          break;
        }
        utf << "kUI1:[" << value << ": ";
        for (UIT i = value; i != 0; --i) {
          value = *params++;
          utf << value << ", ";
        }
        value = *params++;
        utf << value << "]";
        break;
      }
      case 6: {
        value = *params++;
        if (value == 0) {
          utf << "kUI2:[0]";
          break;
        }
        utf << "kUI2:[" << value << ": ";
        for (UIT i = value; i != 0; --i) {
          value = *params++;
          utf << value << ", ";
        }
        value = *params++;
        utf << value << "]";
        break;
      }
      case 7: {
        value = *params++;
        if (value == 0) {
          utf << "kUI4:[0]";
          break;
        }
        utf << "kUI4:[" << value << ": ";
        for (UIT i = value; i != 0; --i) {
          value = *params++;
          utf << value << ", ";
        }
        value = *params++;
        utf << value << "]";
        break;
      }
    }
  }
  utf << '>';
  return utf;
}

}  // namespace _

#endif  //> #if SEAM >= _0_0_0__14
