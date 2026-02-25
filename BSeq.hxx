// Copyright AStarship <https://astarship.net>.
#include "BSeq.h"
#if SEAM >= CRABS_OPERATION
namespace _ {

ISC BSeqParamNumber(const DTB* params, ISN param_number) {
  if (IsError(params)) return 0;
  DTB num_params = *params++;
  if (param_number > num_params) return _NIL;
  DTB i;
  for (i = 0; i < param_number; ++i) {
    DTB value = params[i];
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
