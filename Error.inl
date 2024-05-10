/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Errors.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include "Error.hpp"
#if SEAM >= SCRIPT2_LIST
namespace _ {
const CHA* CrabsError0STA() {
  return TCrabsErrorST0<CHA>();
  /*
  static const CHA error_strings[ErrorCountMax][32] = {
    "ErrorA",                 //< Error 00.
    "Authentication error",   //< Error 01.
    "Array overflow",         //< Error 02.
    "Buffer overflow",        //< Error 03.
    "Buffer underflow",       //< Error 04.
    "Input invalid",          //< Error 05.
    "Input nil",              //< Error 06.
    "Invalid args",           //< Error 07.
    "Invalid argument",       //< Error 08.
    "Invalid buffer",         //< Error 09.
    "Invalid door",           //< Error 10.
    "Invalid error handler",  //< Error 11.
    "Invalid header",         //< Error 12.
    "Invalid hash",           //< Error 13.
    "Invalid index",          //< Error 14.
    "Invalid inquiry",        //< Error 15.
    "Invalid op",             //< Error 16.
    "Invalid operand",        //< Error 17.
    "Invalid Room number",    //< Error 18.
    "Invalid type",           //< Error 19.
    "Invalid UTF-8",          //< Error 20.
    "Invalid UTF-16",         //< Error 21.
    "Invalid UTF-32",         //< Error 22.
    "OBJ locked",             //< Error 23.
    "Parameter overflow",     //< Error 24.
    "Stack overflow",         //< Error 25.
    "Stack underflow",        //< Error 26.
    "Text overflow",          //< Error 27.
    "Varint overflow",        //< Error 28.
    "Implementation error"    //< Error 29.
  };
  return &error_strings[0][0]; */
}

const CHA* CrabsErrorSTR(ISA error) {
  error = error < 0 ? -error : error;
  if (error > CrabsErrorCountMax) error = CrabsErrorCountMax;
  return &TCrabsErrorST0<CHA>()[error * 32];
}
const CHA* CrabsErrorSTR(ISB error) {
  return CrabsErrorSTR(ISA(error));
}
const CHA* CrabsErrorSTR(ISC error) {
  return CrabsErrorSTR(ISC(error));
}
const CHA* CrabsErrorSTR(ISD error) {
  return CrabsErrorSTR(ISD(error));
}

}  //< namespace _
#endif
