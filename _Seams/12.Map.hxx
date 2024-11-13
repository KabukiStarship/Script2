// Copyright Kabuki Starship™ <kabukistarship.com>.
#if SEAM >= SCRIPT2_MAP
#include "../Map.hpp"
//
#include "../RNG.h"
#if SEAM == SCRIPT2_MAP
#include "../_Debug.hxx"
#else
#include "../_Release.hxx"
#endif
using namespace _;
namespace Script2 {

template<typename D, D DomainMin_, D DomainMax_, typename ISZ,
          ISZ CodomainMin_, ISZ CodomainMax_, ISZ Size_>
void TestMap() {
  D_COUT(Linef("\n\n\n\n\n\n+---\nTesting AMap<D")
         << sizeof(D) << ",ISZ" << CHA('0' + sizeof(ISZ))
         << Linef(">\n+---\n\n"));

  AMap<MAP_P, Size_> map;
  D_COUT_OBJ(map);

  D_COUT("map_size:" << map.Size() << " map_bytes:" << map.SizeBytes()
                     << " map_size_words:" << map.SizeWords()
                     << " sizeof(TMapBuf<D,ISZ>):" << sizeof(TMapBuf<D, ISZ>)
                     << "\n domain:" << TDelta<>(map.This(), map.Domain())
                     << " codomain:" << TDelta<>(map.This(), map.Codomain()));

  D domain[Size_];

  D_COUT(Headingf("Generating random domain values..."));

  for (ISZ i = 0; i < Size_; ++i) {
    D d = Random(DomainMin_, DomainMax_);
    domain[i] = d;
    D_COUT("\n" << i << ".) " << d);
  }

  for (ISZ i = 0; i < Size_; ++i) map.Add(domain[i]);

  D_COUT_MAP(map.This());

  D_COUT(Headingf("Searching the domain for each domain[i]..."));
  for (ISZ i = 0; i < Size_; ++i) A_AVOW_INDEX(i, ISZ(map.Find(domain[i])), i);

  D_COUT(Headingf("Remapping the codomain to random numbers..."));

  ISZ codomain[Size_];

  for (ISZ i = 0; i < Size_; ++i) {
    ISZ c = Random(CodomainMin_, CodomainMax_);
    codomain[i] = c;
    map.RemapCodomain(i, c);
  }
  D_COUT_OBJ(map);
  D_COUT(Headingf("Searching for the remappings..."));

  for (ISZ i = 0; i < Size_; ++i)
    A_AVOW_INDEX(i, ISZ(map.FindCodomain(codomain[i])), i);
  D_COUT_OBJ(map);
}
}  //< namespace Script2
#endif

namespace Script2 {
const CHA* Map(const CHA* args) {
#if SEAM >= SCRIPT2_MAP
  A_TEST_BEGIN;

  TestMap<ISB, CSignedMin<ISB>(), CSignedMax<ISB>(), ISB, CSignedMin<ISB>(),
          CSignedMax<ISB>(), 8>();
  TestMap<ISB, CSignedMin<ISB>(), CSignedMax<ISB>(), ISC, CSignedMin<ISB>(),
          CSignedMax<ISB>(), 8>();
  TestMap<ISB, CSignedMin<ISB>(), CSignedMax<ISB>(), ISD, CSignedMin<ISB>(),
          CSignedMax<ISB>(), 8>();

  TestMap<ISC, CSignedMin<ISB>(), CSignedMax<ISB>(), ISB, CSignedMin<ISB>(),
          CSignedMax<ISB>(), 8>();
  TestMap<ISC, CSignedMin<ISB>(), CSignedMax<ISB>(), ISC, CSignedMin<ISB>(),
          CSignedMax<ISB>(), 8>();
  TestMap<ISC, CSignedMin<ISB>(), CSignedMax<ISB>(), ISD, CSignedMin<ISB>(),
          CSignedMax<ISB>(), 8>();

  TestMap<ISD, CSignedMin<ISB>(), CSignedMax<ISB>(), ISB, CSignedMin<ISB>(),
          CSignedMax<ISB>(), 8>();
  TestMap<ISD, CSignedMin<ISB>(), CSignedMax<ISB>(), ISC, CSignedMin<ISB>(),
          CSignedMax<ISB>(), 8>();
  TestMap<ISD, CSignedMin<ISB>(), CSignedMax<ISB>(), ISD, CSignedMin<ISB>(),
          CSignedMax<ISB>(), 8>();

#endif
  return nullptr;
}
}  //< namespace Script2
