/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_errors.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>
#if SEAM >= SCRIPT2_SEAM_DIC
// Dependencies:
#include "c_error.h"
// End dependencies.

namespace _ {

const CH1** ErrorStrands() {
  static const CH1* kErrors[] = {
      "Not an error",             //<  0
      "Input nil",                //<  1
      "Input too low",            //<  2
      "Input too high",           //<  3
      "Buffer overflow",          //<  4
      "Buffer underflow",         //<  5
      "Varint overflow",          //<  6
      "Invalid hash",             //<  7
      "Invalid type",             //<  8
      "Invalid index",            //<  9
      "Invalid equerry",          //< 10
      "Invalid argument number",  //< 11
      "Invalid door",             //< 12
      "Too many parameters",      //< 13
      "Stack overflow",           //< 14
      "Invalid subset",           //< 15
      "Too many pops",            //< 16
      "Text buffer overflow",     //< 17
      "Invalid error handler",    //< 18
      "Invalid op",               //< 19
      "Array overflow",           //< 20
      "Invalid Set",              //< 21
      "Malformed UTF-8",          //< 22
      "Malformed UTF-16",         //< 23
      "Malformed UTF-32",         //< 24
      "BIn Locked",               //< 25
      "Invalid args",             //< 26
      "Invalid credentials",      //< 27
      "CObj locked"                //< 28
      "Implementation error",     //< 29
  };
  return kErrors;
}

const CH1* ErrorStrand(Error error) {
  if (error >= kErrorImplementation) {
    return ErrorStrands()[kErrorImplementation];
  }
  return ErrorStrands()[error];
}

}  // namespace _
#endif  //> #if SEAM >= SCRIPT2_SEAM_DIC
