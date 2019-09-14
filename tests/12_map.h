/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /12_map.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (SIZ) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>

#include "t_map.h"
//
#include "c_rng.h"

#if SEAM == SCRIPT2_MAP
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
template <typename D, D kDomainMin_, D kDomainMax, typename SIZ,
          SIZ kCodomainMin_, SIZ kCodomainMax_, SIZ kSize_>
void TestMap() {
  D_COUT(Linef("\n\n\n\n\n\n+---\nTesting AMap<D")
         << sizeof(D) << ",SIZ" << CH1('0' + sizeof(SIZ))
         << Linef(">\n+---\n\n"));

  AMap<D, SIZ, kSize_> map;
  D_COUT_OBJ(map);

  D_COUT("map_size:" << map.Size() << " map_size_bytes:" << map.SizeBytes()
                     << " map_size_words:" << map.SizeWords()
                     << " sizeof(TMapBuf<D,SIZ>):" << sizeof(TMapBuf<D, SIZ>)
                     << "\n domain:" << TDelta<>(map.This(), map.Domain())
                     << " codomain:" << TDelta<>(map.This(), map.Codomain()));

  D domain[kSize_];

  D_COUT(Headingf("Generating random domain values..."));

  for (SIZ i = 0; i < kSize_; ++i) {
    D d = Random(kDomainMin_, kDomainMax);
    domain[i] = d;
    D_COUT("\n" << i << ".) " << d);
  }

  for (SIZ i = 0; i < kSize_; ++i) map.Add(domain[i]);

  D_COUT(Headingf("Searching the domain for each domain[i]..."));
  for (SIZ i = 0; i < kSize_; ++i) A_AVOW_INDEX(i, SIZ(map.Find(domain[i])), i);

  D_COUT(Headingf("Remapping the codomain to random numbers..."));

  SIZ codomain[kSize_];

  for (SIZ i = 0; i < kSize_; ++i) {
    SIZ c = Random(kCodomainMin_, kCodomainMax_);
    codomain[i] = c;
    map.RemapCodomain(i, c);
  }
  D_COUT_OBJ(map);
  D_COUT(Headingf("Searching for the remappings..."));

  for (SIZ i = 0; i < kSize_; ++i)
    A_AVOW_INDEX(i, SIZ(map.FindCodomain(codomain[i])), i);
  D_COUT_OBJ(map);
}

static const CH1* Map(const CH1* args) {
#if SEAM >= SCRIPT2_MAP
  A_TEST_BEGIN;

  TestMap<SI2, CSignedMin<SI2>(), CSignedMax<SI2>(), SI2, CSignedMin<SI2>(),
          CSignedMax<SI2>(), 8>();
  TestMap<SI2, CSignedMin<SI2>(), CSignedMax<SI2>(), SI4, CSignedMin<SI2>(),
          CSignedMax<SI2>(), 8>();
  TestMap<SI2, CSignedMin<SI2>(), CSignedMax<SI2>(), SI8, CSignedMin<SI2>(),
          CSignedMax<SI2>(), 8>();

  TestMap<SI4, CSignedMin<SI2>(), CSignedMax<SI2>(), SI2, CSignedMin<SI2>(),
          CSignedMax<SI2>(), 8>();
  TestMap<SI4, CSignedMin<SI2>(), CSignedMax<SI2>(), SI4, CSignedMin<SI2>(),
          CSignedMax<SI2>(), 8>();
  TestMap<SI4, CSignedMin<SI2>(), CSignedMax<SI2>(), SI8, CSignedMin<SI2>(),
          CSignedMax<SI2>(), 8>();

  TestMap<SI8, CSignedMin<SI2>(), CSignedMax<SI2>(), SI2, CSignedMin<SI2>(),
          CSignedMax<SI2>(), 8>();
  TestMap<SI8, CSignedMin<SI2>(), CSignedMax<SI2>(), SI4, CSignedMin<SI2>(),
          CSignedMax<SI2>(), 8>();
  TestMap<SI8, CSignedMin<SI2>(), CSignedMax<SI2>(), SI8, CSignedMin<SI2>(),
          CSignedMax<SI2>(), 8>();

#endif
  return nullptr;
}
}  // namespace script2
