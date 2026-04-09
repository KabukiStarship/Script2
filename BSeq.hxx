// Copyright AStarship <https://astarship.net>.
#include "BSeq.h"
#if SEAM >= CRABS_OP
namespace _ {

ISC BSeqParamNumber(const DTB* params, ISN param_number) {
  enum {
    StateNormal = 0,
    StateVarint = 1,
  };
  if (IsError(params))
    return 0;
  ISC param_count = ISC(*params++);
  if (param_number > param_count)
    return _NIL;
  if (param_count < 0) {
    param_count ^= DTB(1) << 15;
    param_count |= ISC(*params++) << 15;
  }
  ISC state = 0,
    bits_shift = 0;
  ISC i;
  for (i = 0; i < param_number; ++i) {
    DTB value = *params++;
		if (ATypeIsVarLength(value)) {
      if (state == StateNormal) {
        state = StateVarint;
        bits_shift = 0;
      }
      value ^= DTB(1) << 15;
      value |= ISC(*params++) << 15;
    }
  }
  return *params++;
}
}  //< namespace _
#endif
