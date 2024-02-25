/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /BSeq.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "BSeq.h"
namespace _ {

ISN BSeqParamNumber(const ISN* params, ISN param_number) {
  if (!params) return 0;
  ISN num_params = *params++;
  if (param_number > num_params) return cNIL;
  ISN i;
  for (i = 0; i < param_number; ++i) {
    ISN value = params[i];
    if (value == cSTR)
      ++param_number;
    else if (value > 31) {  // It's an array!
      value = value >> 5;
      if (value < 4) {  // It's a single dimension!
        param_number += 2;
        break;
      } else if (value > 7) {  // Gratuitous explanation points!
        // D_COUT ("\nError");
        return cNIL;
      } else {
        param_number += params[i] + 1;
      }
    }
  }
  return params[i];
}

}  //< namespace _

#endif
