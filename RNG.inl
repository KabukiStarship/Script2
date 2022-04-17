/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /RNG.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include "RNG.h"
//
#include <random>
//
#include "_Debug.inl"
namespace _ {

// static std::random_device rd;
// static std::default_random_engine rng(rd);
static std::default_random_engine rng;

IUC RandomUI4() { return rng(); }

IUC RandomSeed() { return std::random_device()(); }

void RandomizeSeed() { return rng.seed(RandomSeed()); }

BOL RandomBOL() { return (BOL)RandomUI4(); }

IUA RandomUIA() { return (IUA)RandomUI4(); }

ISA RandomSIA() { return (ISA)RandomUIA(); }

IUB RandomUI2() { return (IUB)RandomUI4(); }

ISB RandomSIB() { return (ISB)RandomUI2(); }

ISC Randomint() { return (ISC)RandomUI4(); }

IUD RandomUI8() {
  IUD a = RandomUI4(), b = RandomUI4();
  return (ISD)(a | (b << 32));
}

ISD RandomSID() { return (ISD)RandomUI8(); }

void RandomNumber(BOL& result) { result = BOL(RandomUI4() & 1); }

void RandomNumber(IUA& result) { result = RandomUIA(); }

void RandomNumber(ISA& result) { result = RandomSIA(); }

void RandomNumber(IUB& result) { result = RandomUI2(); }

void RandomNumber(ISB& result) { result = RandomSIB(); }

void RandomNumber(IUC& result) { result = RandomUI4(); }

void RandomNumber(ISC& result) { result = Randomint(); }

void RandomNumber(IUD& result) { result = RandomUI8(); }

void RandomNumber(ISD& result) { result = RandomSID(); }

template <typename ISZ>
ISZ TRandom(ISZ min, ISZ max) {
  std::uniform_int_distribution<ISZ> dist(min, max);
  return dist(rng);
}

IUA Random(IUA min, IUA max) { return IUA(TRandom<IUB>(min, max)); }

ISA Random(ISA min, ISA max) { return ISA(TRandom<ISB>(min, max)); }

IUB Random(IUB min, IUB max) { return TRandom<IUB>(min, max); }

ISB Random(ISB min, ISB max) { return TRandom<ISB>(min, max); }

IUC Random(IUC min, IUC max) { return TRandom<IUC>(min, max); }

ISC Random(ISC min, ISC max) { return TRandom<ISC>(min, max); }

IUD Random(IUD min, IUD max) { return TRandom<IUD>(min, max); }

ISD Random(ISD min, ISD max) { return TRandom<ISD>(min, max); }

}  //< namespace _
