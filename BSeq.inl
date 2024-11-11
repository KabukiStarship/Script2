// Copyright Kabuki Starship� <kabukistarship.com>.
#include "BSeq.h"
#if SEAM >= SCRIPT2_CRABS
namespace _ {

ISN BSeqParamNumber(const ISN* params, ISN param_number) {
  if (!params) return 0;
  ISN num_params = *params++;
  if (param_number > num_params) return _NIL;
  ISN i;
  for (i = 0; i < param_number; ++i) {
    ISN value = params[i];
    if (value == STR_)
      ++param_number;
    else if (value > 31) {  // It's an array!
      value = value >> 5;
      if (value < 4) {  // It's a single dimension!
        param_number += 2;
        break;
      } else if (value > 7) {  // Gratuitous explanation points!
        // D_COUT ("\nError");
        return _NIL;
      } else {
        param_number += params[i] + 1;
      }
    }
  }
  return params[i];
}

}  //< namespace _

#endif
