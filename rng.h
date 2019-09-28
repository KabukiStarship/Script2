/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /rng.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#ifndef INCLUDED_SCRIPTCRNG
#define INCLUDED_SCRIPTCRNG 1

namespace _ {

/* Gets a random generator device seed. */
LIB_MEMBER UI4 RandomSeed();

/* Re-seeds the static mersenne twister engine. */
LIB_MEMBER void RandomizeSeed();

/* Gets a random 8-bit/1-byte unsigned integer. */
LIB_MEMBER UI1 Random(UI1 min, UI1 max);

/* Gets a random 8-bit/1-byte signed integer. */
LIB_MEMBER SI1 Random(SI1 min, SI1 max);

/* Gets a random 16-bit/2-byte unsigned integer. */
LIB_MEMBER UI2 Random(UI2 min, UI2 max);

/* Gets a random 16-bit/2-byte signed integer. */
LIB_MEMBER SI2 Random(SI2 min, SI2 max);

/* Gets a random 32-bit/4-byte unsigned integer. */
LIB_MEMBER UI4 Random(UI4 min, UI4 max);

/* Gets a random 32-bit/4-byte unsigned integer. */
LIB_MEMBER SI4 Random(SI4 min, SI4 max);

/* Gets a random 64-bit/8-byte unsigned integer. */
LIB_MEMBER UI8 Random(UI8 min, UI8 max);

/* Gets a random 64-bit/8-byte signed integer. */
LIB_MEMBER SI8 Random(SI8 min, SI8 max);

/* Gets a random 8-bit/1-UI1 unsigned integer. */
LIB_MEMBER UI1 RandomUI1();

/* Gets a random 8-bit/1-UI1 signed integer. */
LIB_MEMBER SI1 RandomSI1();

/* Gets a random 16-bit/2-UI1 unsigned integer. */
LIB_MEMBER UI2 RandomUI2();

/* Gets a random 16-bit/2-UI1 signed integer. */
LIB_MEMBER SI2 RandomSI2();

/* Gets a random 32-bit/4-UI1 unsigned integer. */
LIB_MEMBER UI4 RandomUI4();

/* Gets a random 32-bit/4-UI1 signed integer. */
LIB_MEMBER SI4 Randomint();

/* Gets a random 64-bit/8-UI1 unsigned integer. */
LIB_MEMBER UI8 RandomUI8();

/* Gets a random 64-bit/8-UI1 signed integer. */
LIB_MEMBER SI8 RandomSI8();

/* Gets a random 8-bit/1-UI1 unsigned integer. */
LIB_MEMBER void RandomNumber(UI1& result);

/* Gets a random 8-bit/1-UI1 signed integer. */
LIB_MEMBER void RandomNumber(SI1& result);

/* Gets a random 16-bit/2-UI1 unsigned integer. */
LIB_MEMBER void RandomNumber(UI2& result);

/* Gets a random 16-bit/2-UI1 signed integer. */
LIB_MEMBER void RandomNumber(SI2& result);

/* Gets a random 32-bit/4-UI1 unsigned integer. */
LIB_MEMBER void RandomNumber(UI4& result);

/* Gets a random 32-bit/4-UI1 signed integer. */
LIB_MEMBER void RandomNumber(SI4& result);

/* Gets a random 64-bit/8-UI1 unsigned integer. */
LIB_MEMBER void RandomNumber(UI8& result);

/* Gets a random 64-bit/8-UI1 signed integer. */
LIB_MEMBER void RandomNumber(SI8& result);

}  // namespace _
#endif  //< INCLUDED_SCRIPTCRNG
