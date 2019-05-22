/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_bsq.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>
#if SEAM >= SCRIPT2_14
#include "c_bsq.h"

#include "c_test.h"
#include "c_utf1.h"

namespace _ {

SI4 BsqParamNumber(const SI4* params, SI4 param_number) {
  if (!params) return 0;
  SI4 num_params = *params++;
  if (param_number > num_params) return kNIL;
  SI4 i;
  for (i = 0; i < param_number; ++i) {
    SI4 value = params[i];
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

UTF1& PrintBsq(UTF1& utf, const SI4* params) {
  SI4 num_params = *params++, i, type, value = 0;

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
    utf << STRType((SI4)value) << ", ";
    if (type >= kSTR) {
      if (value) {
        utf << "\nError: arrays may only be created from POD "
               "types.";
        return utf;
      }
      // Print out the max length of the .
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
          for (SI4 i = value; i != 0; --i) {
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
          for (SI4 i = value; i != 0; --i) {
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
          for (SI4 i = value; i != 0; --i) {
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
  utf << STRType(value) << ", ";
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
        for (SI4 i = value; i != 0; --i) {
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
        for (SI4 i = value; i != 0; --i) {
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
        for (SI4 i = value; i != 0; --i) {
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

#endif  //> #if SEAM >= SCRIPT2_14
