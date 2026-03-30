// Copyright AStarship <https://astarship.net>.
#include "RNG.h"
#if SEAM < CRABS_RNG
#include <random>
namespace _ {

// static std::random_device rd;
// static std::default_random_engine rng(rd);
static std::default_random_engine rng;

IUC RandomSeed() { /*return std::random_device();*/ return 0; }

template<typename I>
I TRandom(I min, I max) {
  std::uniform_int_distribution<I> dist(min, max);
  return dist(rng);
}

template<typename I>
void TRandomBits(I& result, I bit_count) {
  if (bit_count < 0) {
    result = 0;
    return;
  }
	if (bit_count >= sizeof(I) * 8) bit_count = sizeof(I) *  8;
  std::uniform_int_distribution<I> dist(0, (I(1) << (bit_count - 1)) - 1);
  result = dist(rng);
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
//  return ISD(a | (b << 32));
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

inline BOL BOLRandom() { return BOL(IUCRandom()); }

inline ISA ISARandom() { return ISA(IUARandom()); }

inline ISB ISBRandom() { return ISB(IUBRandom()); }

inline ISC ISCRandom() { return ISC(IUCRandom()); }

inline ISD ISDRandom() { return (ISD)IUDRandom(); }

inline void RandomNumber(BOL& result) { result = BOL(IUCRandom() & 1); }

inline void RandomNumber(IUA& result) { result = IUARandom(); }

inline void RandomNumber(ISA& result) { result = ISARandom(); }

inline void RandomNumber(IUB& result) { result = IUBRandom(); }

inline void RandomNumber(ISB& result) { result = ISBRandom(); }

inline void RandomNumber(IUC& result) { result = IUCRandom(); }

inline void RandomNumber(ISC& result) { result = ISCRandom(); }

inline void RandomNumber(IUD& result) { result = IUDRandom(); }

inline void RandomNumber(ISD& result) { result = ISDRandom(); }

inline void RandomProbability(FPC& result) { 
  //result = TRandom<FPC>(-1.0f, 1.0f);
}

inline void RandomProbability(FPD& result) {
  //result = TRandom<FPD>(-1.0, 1.0);
}

inline void RandomProbabilitySigned(FPC& result) {
  //result = TRandom<FPC>(-1.0f, 1.0f);
}

inline void RandomProbabilitySigned(FPD& result) {
  //result = TRandom<FPD>(-1.0, 1.0);
}

IUA Random(IUA min, IUA max) { return IUA(TRandom<IUB>(min, max)); }

ISA Random(ISA min, ISA max) { return ISA(TRandom<ISB>(min, max)); }

IUB Random(IUB min, IUB max) { return TRandom<IUB>(min, max); }

ISB Random(ISB min, ISB max) { return TRandom<ISB>(min, max); }

IUC Random(IUC min, IUC max) { return TRandom<IUC>(min, max); }

ISC Random(ISC min, ISC max) { return TRandom<ISC>(min, max); }

IUD Random(IUD min, IUD max) { return TRandom<IUD>(min, max); }

ISD Random(ISD min, ISD max) { return TRandom<ISD>(min, max); }

void RandomBits(ISA& result, ISA bit_count) {
  ISB resultb = 0;
  TRandomBits<ISB>(resultb, bit_count);
  result = ISA(resultb);
}

void RandomBits(ISB& result, ISB bit_count) {
  TRandomBits<ISB>(result, bit_count);
}

void RandomBits(ISC& result, ISC bit_count) {
  TRandomBits<ISC>(result, bit_count);
}

void RandomBits(ISD& result, ISD bit_count) {
  TRandomBits<ISD>(result, bit_count);
}

}  //< namespace _
