// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef SCRIPT_BSQ_INLINE_CODE
#define SCRIPT_BSQ_INLINE_CODE
#include "BSeq.h"
#if SEAM >= SCRIPT2_CRABS
namespace _ {

template<typename Printer>
Printer& TBSeqPrint(Printer& o, const ISN* params) {
  ISN param_count = *params++,
      i     = 0;
  DTB type  = 0,
      value = 0;

  o << "Param<";
  if (param_count > BSQMax) {
    o << "\nInvalid num_params: " << param_count;
    return o;
  }
  o << param_count << ": ";
  for (i = 1; i < param_count; ++i) {
    value = *params++;
    type = value & 0x1f;  //< Mask off type.
    value = value >> 5;   //< Shift over array type.
    o << ATypef(value) << ", ";
    if (type >= STR_) {
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
  o << ATypef(value) << ", ";
  if (value == STR_) {
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
#endif
