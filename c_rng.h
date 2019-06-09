/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_rng.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#ifndef INCLUDED_SCRIPTCRNG
#define INCLUDED_SCRIPTCRNG 1

namespace _ {

/* Gets a random generator device seed. */
SDK UI4 RandomSeed();

/* Re-seeds the static mersenne twister engine. */
SDK void RandomizeSeed();

/* Gets a random 8-bit/1-byte unsigned integer. */
SDK UI1 Random(UI1 min, UI1 max);

/* Gets a random 8-bit/1-byte signed integer. */
SDK SI1 Random(SI1 min, SI1 max);

/* Gets a random 16-bit/2-byte unsigned integer. */
SDK UI2 Random(UI2 min, UI2 max);

/* Gets a random 16-bit/2-byte signed integer. */
SDK SI2 Random(SI2 min, SI2 max);

/* Gets a random 32-bit/4-byte unsigned integer. */
SDK UI4 Random(UI4 min, UI4 max);

/* Gets a random 32-bit/4-byte unsigned integer. */
SDK SI4 Random(SI4 min, SI4 max);

/* Gets a random 64-bit/8-byte unsigned integer. */
SDK UI8 Random(UI8 min, UI8 max);

/* Gets a random 64-bit/8-byte signed integer. */
SDK SI8 Random(SI8 min, SI8 max);

/* Gets a random 8-bit/1-UI1 unsigned integer. */
SDK UI1 RandomUI1();

/* Gets a random 8-bit/1-UI1 signed integer. */
SDK SI1 RandomSI1();

/* Gets a random 16-bit/2-UI1 unsigned integer. */
SDK UI2 RandomUI2();

/* Gets a random 16-bit/2-UI1 signed integer. */
SDK SI2 RandomSI2();

/* Gets a random 32-bit/4-UI1 unsigned integer. */
SDK UI4 RandomUI4();

/* Gets a random 32-bit/4-UI1 signed integer. */
SDK SI4 Randomint();

/* Gets a random 64-bit/8-UI1 unsigned integer. */
SDK UI8 RandomUI8();

/* Gets a random 64-bit/8-UI1 signed integer. */
SDK SI8 RandomSI8();

/* Gets a random 8-bit/1-UI1 unsigned integer. */
SDK void RandomNumber(UI1& result);

/* Gets a random 8-bit/1-UI1 signed integer. */
SDK void RandomNumber(SI1& result);

/* Gets a random 16-bit/2-UI1 unsigned integer. */
SDK void RandomNumber(UI2& result);

/* Gets a random 16-bit/2-UI1 signed integer. */
SDK void RandomNumber(SI2& result);

/* Gets a random 32-bit/4-UI1 unsigned integer. */
SDK void RandomNumber(UI4& result);

/* Gets a random 32-bit/4-UI1 signed integer. */
SDK void RandomNumber(SI4& result);

/* Gets a random 64-bit/8-UI1 unsigned integer. */
SDK void RandomNumber(UI8& result);

/* Gets a random 64-bit/8-UI1 signed integer. */
SDK void RandomNumber(SI8& result);

}  // namespace _
#endif  //< INCLUDED_SCRIPTCRNG
