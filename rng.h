/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /RNG.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_Config.h>

#ifndef INCLUDED_SCRIPTCRNG
#define INCLUDED_SCRIPTCRNG 1

namespace _ {

/* Gets a random generator device seed. */
LIB_MEMBER IUC RandomSeed();

/* Re-seeds the static mersenne twister engine. */
LIB_MEMBER void RandomizeSeed();

/* Gets a random 8-bit/1-byte unsigned integer. */
LIB_MEMBER IUA Random(IUA min, IUA max);

/* Gets a random 8-bit/1-byte signed integer. */
LIB_MEMBER ISA Random(ISA min, ISA max);

/* Gets a random 16-bit/2-byte unsigned integer. */
LIB_MEMBER IUB Random(IUB min, IUB max);

/* Gets a random 16-bit/2-byte signed integer. */
LIB_MEMBER ISB Random(ISB min, ISB max);

/* Gets a random 32-bit/4-byte unsigned integer. */
LIB_MEMBER IUC Random(IUC min, IUC max);

/* Gets a random 32-bit/4-byte unsigned integer. */
LIB_MEMBER ISC Random(ISC min, ISC max);

/* Gets a random 64-bit/8-byte unsigned integer. */
LIB_MEMBER IUD Random(IUD min, IUD max);

/* Gets a random 64-bit/8-byte signed integer. */
LIB_MEMBER ISD Random(ISD min, ISD max);

/* Gets a random 8-bit/1-IUA unsigned integer. */
LIB_MEMBER IUA RandomUIA();

/* Gets a random 8-bit/1-IUA signed integer. */
LIB_MEMBER ISA RandomSIA();

/* Gets a random 16-bit/2-IUA unsigned integer. */
LIB_MEMBER IUB RandomUI2();

/* Gets a random 16-bit/2-IUA signed integer. */
LIB_MEMBER ISB RandomSIB();

/* Gets a random 32-bit/4-IUA unsigned integer. */
LIB_MEMBER IUC RandomUI4();

/* Gets a random 32-bit/4-IUA signed integer. */
LIB_MEMBER ISC Randomint();

/* Gets a random 64-bit/8-IUA unsigned integer. */
LIB_MEMBER IUD RandomUI8();

/* Gets a random 64-bit/8-IUA signed integer. */
LIB_MEMBER ISD RandomSID();

/* Gets a random 8-bit/1-IUA unsigned integer. */
LIB_MEMBER void RandomNumber(IUA& result);

/* Gets a random 8-bit/1-IUA signed integer. */
LIB_MEMBER void RandomNumber(ISA& result);

/* Gets a random 16-bit/2-IUA unsigned integer. */
LIB_MEMBER void RandomNumber(IUB& result);

/* Gets a random 16-bit/2-IUA signed integer. */
LIB_MEMBER void RandomNumber(ISB& result);

/* Gets a random 32-bit/4-IUA unsigned integer. */
LIB_MEMBER void RandomNumber(IUC& result);

/* Gets a random 32-bit/4-IUA signed integer. */
LIB_MEMBER void RandomNumber(ISC& result);

/* Gets a random 64-bit/8-IUA unsigned integer. */
LIB_MEMBER void RandomNumber(IUD& result);

/* Gets a random 64-bit/8-IUA signed integer. */
LIB_MEMBER void RandomNumber(ISD& result);

}  // namespace _
#endif  //< INCLUDED_SCRIPTCRNG
