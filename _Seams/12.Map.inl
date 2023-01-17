/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/12.Map.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (ISZ) 2015-2023 Kabuki Starship <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_MAP
#include "../Map.hpp"
//
#include "../RNG.h"
using namespace _;
#if SEAM == SCRIPT2_MAP
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif

namespace Script2 {
template <typename D, D kDomainMin_, D kDomainMax, typename ISZ,
          ISZ kCodomainMin_, ISZ kCodomainMax_, ISZ cSize_>
void TestMap() {
  D_COUT(Linef("\n\n\n\n\n\n+---\nTesting AMap<D")
         << sizeof(D) << ",ISZ" << CHA('0' + sizeof(ISZ))
         << Linef(">\n+---\n\n"));

  AMap<D, ISZ, cSize_> map;
  D_COUT_OBJ(map);

  D_COUT("map_size:" << map.Size() << " map_size_bytes:" << map.SizeBytes()
                     << " map_size_words:" << map.SizeWords()
                     << " sizeof(TMapBuf<D,ISZ>):" << sizeof(TMapBuf<D, ISZ>)
                     << "\n domain:" << TDelta<>(map.This(), map.Domain())
                     << " codomain:" << TDelta<>(map.This(), map.Codomain()));

  D domain[cSize_];

  D_COUT(Headingf("Generating random domain values..."));

  for (ISZ i = 0; i < cSize_; ++i) {
    D d = Random(kDomainMin_, kDomainMax);
    domain[i] = d;
    D_COUT("\n" << i << ".) " << d);
  }

  for (ISZ i = 0; i < cSize_; ++i) map.Add(domain[i]);

  D_COUT(Headingf("Searching the domain for each domain[i]..."));
  for (ISZ i = 0; i < cSize_; ++i) A_AVOW_INDEX(i, ISZ(map.Find(domain[i])), i);

  D_COUT(Headingf("Remapping the codomain to random numbers..."));

  ISZ codomain[cSize_];

  for (ISZ i = 0; i < cSize_; ++i) {
    ISZ c = Random(kCodomainMin_, kCodomainMax_);
    codomain[i] = c;
    map.RemapCodomain(i, c);
  }
  D_COUT_OBJ(map);
  D_COUT(Headingf("Searching for the remappings..."));

  for (ISZ i = 0; i < cSize_; ++i)
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
