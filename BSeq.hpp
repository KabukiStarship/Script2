/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /BSeq.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "BSeq.h"
namespace _ {

template <typename Printer>
Printer& TBSeqPrint(Printer& o, const ISN* params) {
  ISN num_params = *params++, i, type, value = 0;

  o << "Param<";
  if (num_params > cParamsMax) {
    o << "\nInvalid num_params: " << num_params;
    return o;
  }
  o << num_params << ": ";
  for (i = 1; i < num_params; ++i) {
    value = *params++;
    type = value & 0x1f;  //< Mask off type.
    value = value >> 5;   //< Shift over array type.
    o << STRType((ISN)value) << ", ";
    if (type >= cSTR) {
      if (value) {
        o << "\nError: arrays may only be created from POD types.";
        return o;
      }
      // Print out the max length of the .
      ++i;
      value = *params++;
      o << value;
    } else if (value > 31) {
      if (value > 127) {  //< It's a multi-dimensional array.
        o << "Multi-dimensional Array:" << value << ", ";
      }
      // Then it's an array.
      ++i;
      switch (value) {  //< Print out the Array type.
        case 0: {
          break;
        }
        case 1: {
          value = *params++;
          o << "IUA:" << value << ", ";
          break;
        }
        case 2: {
          value = *params++;
          o << "IUB:" << value << ", ";
          break;
        }
        case 3: {
          value = *params++;
          o << "IUC:" << value << ", ";
          break;
        }
        case 4: {
          value = *params++;
          o << "UI8:" << value << ", ";
          break;
        }
        case 5: {
          value = *params++;
          if (value == 0) {
            o << "IUA:[0]";
            break;
          }
          o << "IUA:[" << value << ": ";
          for (ISN i = value; i != 0; --i) {
            value = *params++;
            o << value << ", ";
          }
          value = *params++;
          o << value << "]";
          break;
        }
        case 6: {
          value = *params++;
          if (value == 0) {
            o << "IUB:[0]";
            break;
          }
          o << "IUB:[" << value << ": ";
          for (ISN i = value; i != 0; --i) {
            value = *params++;
            o << value << ", ";
          }
          value = *params++;
          o << value << "]";
          break;
        }
        case 7: {
          value = *params++;
          if (value == 0) {
            o << "IUC:[0]";
            break;
          }
          o << "IUC:[" << value << ": ";
          for (ISN i = value; i != 0; --i) {
            value = *params++;
            o << value << ", ";
          }
          value = *params++;
          o << value << "]";
          break;
        }
      }
    }
  }
  // Do the last set without a comma.
  value = *params++;
  o << STRType(value) << ", ";
  if (value == cSTR) {
    ++i;
    value = *params++;
    o << value;
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
        o << "IUA:" << value << ", ";
        break;
      }
      case 2: {
        value = *params++;
        o << "IUB:" << value << ", ";
        break;
      }
      case 3: {
        value = *params++;
        o << "IUC:" << value << ", ";
        break;
      }
      case 4: {
        value = *params++;
        o << "UI5:" << value << ", ";
        break;
      }
      case 5: {
        value = *params++;
        if (value == 0) {
          o << "IUA:[0]";
          break;
        }
        o << "IUA:[" << value << ": ";
        for (ISN i = value; i != 0; --i) {
          value = *params++;
          o << value << ", ";
        }
        value = *params++;
        o << value << "]";
        break;
      }
      case 6: {
        value = *params++;
        if (value == 0) {
          o << "IUB:[0]";
          break;
        }
        o << "IUB:[" << value << ": ";
        for (ISN i = value; i != 0; --i) {
          value = *params++;
          o << value << ", ";
        }
        value = *params++;
        o << value << "]";
        break;
      }
      case 7: {
        value = *params++;
        if (value == 0) {
          o << "IUC:[0]";
          break;
        }
        o << "IUC:[" << value << ": ";
        for (ISN i = value; i != 0; --i) {
          value = *params++;
          o << value << ", ";
        }
        value = *params++;
        o << value << "]";
        break;
      }
    }
  }
  o << '>';
  return o;
}

}  //< namespace _

#endif
