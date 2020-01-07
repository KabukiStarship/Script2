/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /errors.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>
#if SEAM >= SCRIPT2_LIST
#include "error.h"

namespace _ {

const CHA** STRErrors() {
  static const CHA* cErrors[] = {
      "Success",                  //<  0
      "Invalid input",            //<  1
      "Input nil",                //<  2
      "Stack overflow",           //<  3
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
      "Too many pops",            //< 14
      "Text buffer overflow",     //< 15
      "Invalid error handler",    //< 16
      "Invalid Oerand",           //< 17
      "Array overflow",           //< 18
      "Invalid Op",               //< 19
      "Malformed UTF-8",          //< 20
      "Malformed UTF-16",         //< 21
      "Malformed UTF-32",         //< 22
      "Obj Locked",               //< 23
      "Invalid args",             //< 24
      "Authentication error",     //< 25
      "Room not found"            //< 26
      "Implementation error",     //< 27
  };
  return cErrors;
}

const CHA* STRError(ISN error) {
  if (error < 0) error = -error;
  if (error >= cErrorImplementation) error = cErrorImplementation;
  return STRErrors()[error];
}

}  // namespace _
#endif
