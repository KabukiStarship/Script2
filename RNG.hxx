// Copyright AStarship <https://astarship.net>.
#include "RNG.h"
// 
#if SEAM < CRABS_RNG
#include <random>
namespace _ {

// static std::random_device rd;
// static std::default_random_engine rng(rd);
static std::default_random_engine rng;

IUC RandomSeed() { /*return std::random_device();*/ return 0; }

template<typename IS>
IS TRandom(IS min, IS max) {
  static std::uniform_int_distribution<IS> dist(min, max);
  return dist(rng);
}

IUA IUARandom() { return IUA(IUBRandom()); }

IUB IUBRandom() { return TRandom<IUB>(0, ~IUB(0)); }

IUC IUCRandom() { return TRandom<IUC>(0, ~IUC(0)); }

IUD IUDRandom() { return TRandom<IUD>(0, ~IUD(0)); }

void RandomizeSeed() { return rng.seed(RandomSeed()); }

}  // namespace _
#else
//#include <random>
//namespace _ {
//// static std::random_device rd;
//// static std::default_random_engine rng(rd);
//static std::default_random_engine rng;
//
//IUC RandomSeed() { /*return std::random_device();*/ return 0; }
//
//IUA IUARandom() { return TRandom<IUA>(0, ~IUA(0)); }
//
//IUB IUBRandom() { return TRandom<IUB>(0, ~IUB(0)); }
//
//IUC IUCRandom() { return TRandom<IUC>(0, ~IUC(0)); }
//
//IUD IUDRandom() {
//  IUD a = IUCRandom(),
//      b = IUCRandom();
//  return (ISD)(a | (b << 32));
//}
//
//template<typename IS>
//IS TRandom(IS min = 0, IS max = IMax(IS(0))) {
//  std::uniform_int_distribution<IS> dist(min, max);
//  return dist(rng);
//}
//}
//void RandomizeSeed() { return rng.seed(RandomSeed()); }
#endif

namespace _ {

BOL BOLRandom() { return BOL(IUCRandom()); }

ISA ISARandom() { return ISA(IUARandom()); }

ISB ISBRandom() { return ISB(IUBRandom()); }

ISC ISCRandom() { return ISC(IUCRandom()); }

ISD ISDRandom() { return (ISD)IUDRandom(); }

void RandomNumber(BOL& result) { result = BOL(IUCRandom() & 1); }

void RandomNumber(IUA& result) { result = IUARandom(); }

void RandomNumber(ISA& result) { result = ISARandom(); }

void RandomNumber(IUB& result) { result = IUBRandom(); }

void RandomNumber(ISB& result) { result = ISBRandom(); }

void RandomNumber(IUC& result) { result = IUCRandom(); }

void RandomNumber(ISC& result) { result = ISCRandom(); }

void RandomNumber(IUD& result) { result = IUDRandom(); }

void RandomNumber(ISD& result) { result = ISDRandom(); }

IUA Random(IUA min, IUA max) { return IUA(TRandom<IUB>(min, max)); }

ISA Random(ISA min, ISA max) { return ISA(TRandom<ISB>(min, max)); }

IUB Random(IUB min, IUB max) { return TRandom<IUB>(min, max); }

ISB Random(ISB min, ISB max) { return TRandom<ISB>(min, max); }

IUC Random(IUC min, IUC max) { return TRandom<IUC>(min, max); }

ISC Random(ISC min, ISC max) { return TRandom<ISC>(min, max); }

IUD Random(IUD min, IUD max) { return TRandom<IUD>(min, max); }

ISD Random(ISD min, ISD max) { return TRandom<ISD>(min, max); }

}  //< namespace _
