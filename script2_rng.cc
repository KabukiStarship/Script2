/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_random.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#include "crng.h"

#include <random>

namespace _ {

// static std::random_device rd;
// static std::default_random_engine rng(rd);
static std::default_random_engine rng;

UI4 RandomUI4() { return rng(); }

UI4 RandomSeed() { return std::random_device()(); }

void RandomizeSeed() { return rng.seed(RandomSeed()); }

BOL RandomBOL() { return (BOL)RandomUI4(); }

UI1 RandomUI1() { return (UI1)RandomUI4(); }

SI1 RandomSI1() { return (SI1)RandomUI1(); }

UI2 RandomUI2() { return (UI2)RandomUI4(); }

SI2 RandomSI2() { return (SI2)RandomUI2(); }

SI4 RandomSI4() { return (SI4)RandomUI4(); }

UI8 RandomUI8() {
  UI8 a = RandomUI4(), b = RandomUI4();
  return (SI8)(a | (b << 32));
}

SI8 RandomSI8() { return (SI8)RandomUI8(); }

void RandomNumber(BOL& result) { result = (BOL)RandomUI4() & 1; }

void RandomNumber(UI1& result) { result = RandomUI1(); }

void RandomNumber(SI1& result) { result = RandomSI1(); }

void RandomNumber(UI2& result) { result = RandomUI2(); }

void RandomNumber(SI2& result) { result = RandomSI2(); }

void RandomNumber(UI4& result) { result = RandomUI4(); }

void RandomNumber(SI4& result) { result = RandomSI4(); }

void RandomNumber(UI8& result) { result = RandomUI8(); }

void RandomNumber(SI8& result) { result = RandomSI8(); }

template <typename I>
I Random(I min, I max) {
  std::uniform_int_distribution<I> dist(min, max);
  return dist(rng);
}

UI2 Random(UI2 min, UI2 max) { return Random<UI2>(min, max); }

UI2 Random(SI2 min, SI2 max) { return Random<SI2>(min, max); }

UI4 Random(UI4 min, UI4 max) { return Random<UI4>(min, max); }

UI8 Random(UI8 min, UI8 max) { return Random<UI8>(min, max); }

UI8 Random(SI8 min, SI8 max) { return Random<SI8>(min, max); }

}  // namespace _
