/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Errors.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include "Error.hpp"
#if SEAM >= SCRIPT2_CORE
namespace _ {
const CHA* CrabsError0STA() {
  return TCrabsErrorST<CHA>();
}

const CHA* CrabsErrorSTR(ISA error) {
  error = error < 0 ? -error : error;
  if (error > CrabsErrorCount) error = CrabsErrorCount;
  return &TCrabsErrorST<CHA>()[error * 32];
}
const CHA* CrabsErrorSTR(ISB error) {
  return CrabsErrorSTR(ISA(error));
}
const CHA* CrabsErrorSTR(ISC error) {
  return CrabsErrorSTR(ISA(error));
}
const CHA* CrabsErrorSTR(ISD error) {
  return CrabsErrorSTR(ISA(error));
}

BOL AIsError(const void* result) {
  return TDelta<IUW>(result) < CrabsErrorCount;
}

}  //< namespace _
#endif
