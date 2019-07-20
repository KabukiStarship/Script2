/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_hash.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_LOOM
#include "c_hash.h"

#ifndef INCLUDED_SCRIPT2_HASH_T
#define INCLUDED_SCRIPT2_HASH_T 1

namespace _ {

/* Returns the highest signed prime that can fit in type SI.
@return 0 if the sizeof (SI) is not 1, 2, 4, or 8.  */
template <typename SI>
constexpr SI PrimeMaxSigned() {
  SI prime =
      sizeof(SI) == 1
          ? 127
          : sizeof(SI) == 2 ? 32767 :
                            ? sizeof(SI) == 4
                                  ? 2147483647
                                  : sizeof(SI) == 8 ? 9223372036854775783 : 0;
  return prime;
}

/* Returns the highest signed prime that can fit in type UI.
@return 0 if the sizeof (UI) is not 1, 2, 4, or 8. */
template <typename HSH>
constexpr HSH TPrimeMaxUnigned() {
  HSH prime = sizeof(HSH) == 1
                  ? 251
                  : sizeof(HSH) == 2
                        ? 65535
                        : sizeof(HSH) == 4
                              ? 4294967291
                              : sizeof(HSH) == 8 ? 18446744073709551557 : 0;
  return prime;
}

template <typename Char, typename HSH>
HSH THashPrime(Char value, HSH hash) {
  return hash + hash * (HSH)value;
}

template <typename Char, typename HSH>
UI2 THashPrime(const Char* str) {
  HSH c = (HSH)*str;
  HSH hash = TPrimeMaxUnigned<HSH>();
  while (c) {
    hash = THashPrime<Char, HSH>(c, hash);
    ++str;
    c = *str;
  }
  return hash;
}

}  // namespace _
#endif
#endif
