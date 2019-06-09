/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_random.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#include <random>

#include "c_rng.h"

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

SI4 Randomint() { return (SI4)RandomUI4(); }

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

void RandomNumber(SI4& result) { result = Randomint(); }

void RandomNumber(UI8& result) { result = RandomUI8(); }

void RandomNumber(SI8& result) { result = RandomSI8(); }

template <typename I>
I Random(I min, I max) {
  std::uniform_int_distribution<I> dist(min, max);
  return dist(rng);
}

UI1 Random(UI1 min, UI1 max) { return (UI1)Random<UI2>(min, max); }

SI1 Random(SI1 min, SI1 max) { return (SI1)Random<UI2>(min, max); }

UI2 Random(UI2 min, UI2 max) { return Random<UI2>(min, max); }

SI2 Random(SI2 min, SI2 max) { return (SI2)Random<UI2>(min, max); }

UI4 Random(UI4 min, UI4 max) { return Random<UI4>(min, max); }

SI4 Random(SI4 min, SI4 max) { return (SI4)Random<UI4>(min, max); }

UI8 Random(UI8 min, UI8 max) { return Random<UI8>(min, max); }

SI8 Random(SI8 min, SI8 max) { return (SI8)Random<UI8>(min, max); }

}  // namespace _
