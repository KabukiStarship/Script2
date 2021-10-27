/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Hash.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#ifndef SCRIPT2_HASH_HEADER_IMPL
#define SCRIPT2_HASH_HEADER_IMPL
namespace _ {
/* Returns the highest signed prime that can fit in type IS.
@return 0 if the sizeof (IS) is not 1, 2, 4, or 8.  */
template <typename IS>
inline IS PrimeMaxSigned() {
  IS prime = (sizeof(IS) == 1)   ? 127
             : (sizeof(IS) == 2) ? 32767
             : (sizeof(IS) == 4) ? 2147483647
             : (sizeof(IS) == 8) ? 9223372036854775783
                                 : 0;
  return prime;
}

/* Returns the highest signed prime that can fit in type IU.
@return 0 if the sizeof (IU) is not 1, 2, 4, or 8. */
template <typename HSH>
inline HSH TPrimeMaxUnigned() {
  HSH prime = sizeof(HSH) == 1   ? 251
              : sizeof(HSH) == 2 ? 65535
              : sizeof(HSH) == 4 ? 4294967291
              : sizeof(HSH) == 8 ? 18446744073709551557
                                 : 0;
  return prime;
}

template <typename HSH, typename CHT = CHR>
inline HSH THashPrime(CHT value, HSH hash) {
  return hash + hash * (HSH)value;
}

template <typename HSH = IUN, typename CHT = CHR>
inline HSH THashPrime(const CHT* str) {
  CHT c = (CHT)*str++;
  HSH hash = TPrimeMaxUnigned<HSH>();
  while (c) {
    hash = THashPrime<HSH, CHT>(c, hash);
    c = *str++;
  }
  return hash;
}

inline IUB HashIUB(IUB value, IUB hash) {
  IUB prime = TPrimeMaxUnigned<IUB>();
  hash = ((value & 0xff) * prime) + hash;
  hash = ((value >> 8) * prime) + hash;
  return hash;
}

inline IUB HashIUBC(IUC value, IUB hash) {
  IUB prime = TPrimeMaxUnigned<IUB>();
  hash = ((value & 0xff) * prime) + hash;
  hash = (((value >> 8) & 0xff) * prime) + hash;
  hash = (((value >> 16) & 0xff) * prime) + hash;
  hash = (((value >> 24) & 0xff) * prime) + hash;
  return hash;
}

inline IUB HashIUBD(IUD value, IUB hash) {
  IUB prime = TPrimeMaxUnigned<IUB>();
  hash = ((value & 0xff) * prime) + hash;
  hash = (((value >> 8) & 0xff) * prime) + hash;
  hash = (((value >> 16) & 0xff) * prime) + hash;
  hash = (((value >> 24) & 0xff) * prime) + hash;
  hash = (((value >> 32) & 0xff) * prime) + hash;
  hash = (((value >> 40) & 0xff) * prime) + hash;
  hash = (((value >> 48) & 0xff) * prime) + hash;
  hash = (((value >> 56) & 0xff) * prime) + hash;
  return hash;
}
}  // namespace _
#endif