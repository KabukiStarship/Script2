/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /errors.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>
#if SEAM >= SCRIPT2_DIC
#include "error.h"

namespace _ {

const CH1** ErrorStrands() {
  static const CH1* cErrors[] = {
      "Not an error",             //<  0
      "Unspecified",              //<  1
      "Input nil",                //<  2
      "Input too low",            //<  3
      "Input too high",           //<  4
      "Buffer overflow",          //<  5
      "Buffer underflow",         //<  6
      "Varint overflow",          //<  7
      "Invalid hash",             //<  8
      "Invalid type",             //<  9
      "Invalid index",            //< 10
      "Invalid equerry",          //< 11
      "Invalid argument number",  //< 12
      "Invalid door",             //< 13
      "Too many parameters",      //< 14
      "Stack overflow",           //< 15
      "Invalid subset",           //< 16
      "Too many pops",            //< 17
      "Text buffer overflow",     //< 18
      "Invalid error handler",    //< 19
      "Invalid op",               //< 20
      "Array overflow",           //< 21
      "Invalid Set",              //< 22
      "Malformed UTF-8",          //< 23
      "Malformed UTF-16",         //< 24
      "Malformed UTF-32",         //< 25
      "BIn Locked",               //< 26
      "Invalid args",             //< 27
      "Invalid credentials",      //< 28
      "Object locked"             //< 29
      "Implementation error",     //< 30
  };
  return cErrors;
}

const CH1* ErrorStrand(Error error) {
  if (error >= cErrorImplementation) {
    return ErrorStrands()[cErrorImplementation];
  }
  return ErrorStrands()[error];
}

}  // namespace _
#endif
