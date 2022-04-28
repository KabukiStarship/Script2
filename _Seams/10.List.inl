/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/10.List.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_LIST
#include "../List.hpp"
#include "../RNG.h"
using namespace _;
#if SEAM == SCRIPT2_LIST
#include "../_Debug.inl"
#define TEST_MIN 0
#define TEST_MAX 0xffff
#else
#include "../_Release.inl"
#define TEST_MIN 0
#define TEST_MAX 0xffff
#endif

namespace Script2 {

template <typename ISZ>
static void TestList() {
  D_COUT(Linef("\n\n\n\n+---\n Testing AList<IS")
         << sizeof(ISZ) << Linef(">\n+---"));

  AList<ISZ, 1024, 40> list;
  D_COUT("\n\nlist.Size():" << list.Size()
                            << " list.SizeBytes():" << list.SizeBytes()
                            << " list.SizeWords():" << list.SizeWords());
  D_COUT_OBJ(list);
  D_COUT("\n\nPushing items on to the List stack...\n");

  const CHA test_ch1[] = {'a', 'b', 'c', 'd'};
  const ISC test_si4[] = {'0', '1', '2', '3'};
  const FPC test_fp4[] = {1.0f, 2.0f, 3.0f, 4.0f};
  const IUD test_ui8[] = {'w', 'x', 'y', 'z'};
  const char* test_st1[] = {"A", "B", "C", "D"};

  enum { cTestCount = 1 };
  ISZ count = 0;
  for (ISZ i = 0; i < cTestCount; ++i) {
    for (ISZ i = 0; i < 4; ++i) {
      A_AVOW(count++, list.Insert(test_ch1[i]));
    }
  }
  D_COUT_OBJ(list);
  for (ISZ i = 0; i < cTestCount; ++i) {
    for (ISZ i = 0; i < 4; ++i) {
      A_AVOW(count++, list.Insert(test_si4[i]));
    }
  }
  D_COUT_OBJ(list);
  for (ISZ i = 0; i < cTestCount; ++i) {
    for (ISZ i = 0; i < 4; ++i) {
      A_AVOW(count++, list.Insert(test_ch1[i]));
      A_AVOW(count++, list.Insert(test_si4[i]));
      A_AVOW(count++, list.Insert(test_fp4[i]));
      A_AVOW(count++, list.Insert(test_ui8[i]));
      //A_AVOW(count++, list.Insert(test_st1[i]));
    }
  }
  D_COUT_OBJ(list);
  for (ISZ i = cTestCount - 1; i >= 0; --i) list.Pop();
}
}  //< namespace Script2
#endif

namespace Script2 {
static const CHA* List(const CHA* args) {
#if SEAM >= SCRIPT2_LIST
  A_TEST_BEGIN;
  TestList<ISB>();
  TestList<ISC>();
  TestList<ISD>();
  D_COUT("\n\nTesting TTypePrint...\n");
  for (ISC type = TEST_MIN; type < TEST_MAX; ++type) {
    D_COUT('\n' << type << ".) ");
    D_COUT(TTypePrint<COut>(COut().Star(), type));
  }
#endif
  return nullptr;
}
}  //< namespace Script2
#undef TEST_MIN
#undef TEST_MAX
