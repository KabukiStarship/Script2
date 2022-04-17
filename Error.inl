/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Errors.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_LIST
#include "Error.h"
namespace _ {

const CHA** STRErrors() {
  static const CHA* cErrors[] = {
    "Success",                  //<   0
    "Invalid input",            //<  -1
    "Input nil",                //<  -2
    "Invalid hash",             //<  -3
    "Invalid type",             //<  -4
    "Invalid index",            //<  -5
    "Invalid equerry",          //<  -6
    "Invalid argument number",  //<  -7
    "Invalid door",             //<  -8
    "Invalid error handler",    //<  -9
    "Invalid Oerand",           //< -10
    "Invalid Op",               //< -11
    "Invalid args",             //< -12
    "Too many parameters",      //< -13
    "Too many pops",            //< -14
    "Stack overflow",           //< -15
    "Varint overflow",          //< -16
    "Array overflow",           //< -17
    "Text overflow",            //< -18
    "Buffer overflow",          //< -19
    "Buffer underflow",         //< -20
    "Malformed UTF-8",          //< -21
    "Malformed UTF-16",         //< -22
    "Malformed UTF-32",         //< -23
    "Object Locked",            //< -24
    "Authentication error",     //< -25
    "Room not found",           //< -26
    "Implementation error",     //< -27
  };
  return cErrors;
}

const CHA* STRError(ISN error) {
  if (error < 0) error = -error;
  ISN error_max = -cErrorImplementation;
  if (error > error_max) error = error_max;
  return STRErrors()[error];
}

}  //< namespace _
#endif
