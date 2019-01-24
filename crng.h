/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/crng.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#ifndef INCLUDED_SCRIPTCRNG
#define INCLUDED_SCRIPTCRNG 1

namespace _ {

/* Gets a random generator device seed. */
SDK UI4 RandomSeed();

/* Re-seeds the static mersenne twister engine. */
SDK void RandomizeSeed();

/* Gets a random 16-bit/2-UI1 unsigned integer. */
SDK UI2 RandomNumber(UI2 min, UI2 max);

/* Gets a random 8-bit/1-UI1 unsigned integer. */
SDK UI1 RandomNumber(UI1 min, UI1 max);

/* Gets a random 8-bit/1-UI1 signed integer. */
SDK UI1 RandomNumber(SI1 min, SI1 max);

/* Gets a random 16-bit/2-UI1 signed integer. */
SDK UI2 RandomNumber(SI2 min, SI2 max);

/* Gets a random 32-bit/4-UI1 unsigned integer. */
SDK UI4 RandomNumber(UI4 min, UI4 max);

/* Gets a random 64-bit/8-UI1 unsigned integer. */
SDK UI8 RandomNumber(UI8 min, UI8 max);

/* Gets a random 64-bit/8-UI1 signed integer. */
SDK UI8 RandomNumber(SI8 min, SI8 max);

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
SDK SI4 RandomSI4();

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
