/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/10.List.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */

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

template<typename ISZ>
static void TestList() {
  D_COUT(Linef("\n\n\n\n+---\n Testing AList<IS")
         << sizeof(ISZ) << Linef(">\n+---"));
  AList<ISZ, 1024, 40> list;
  D_COUT("\n\nlist.Size():" << list.Size()
                            << " list.SizeBytes():" << list.SizeBytes()
                            << " list.SizeWords():" << list.SizeWords());
  D_COUT_OBJ(list);
  D_COUT("\n\nPushing items on to the List stack...\n");

  const CHA test_cha[] = {'a', 'b', 'c', 'd'};
  const ISC test_isc[] = {'0', '1', '2', '3'};
  const FPC test_fpc[] = {1.0f, 2.0f, 3.0f, 4.0f};
  const IUD test_iud[] = {'w', 'x', 'y', 'z'};
  const char* test_sta[] = {"A", "B", "C", "D"};

  enum { TestCount = 1 };
  ISZ count = 0;
  for (ISZ i = 0; i < TestCount; ++i) {
    for (ISZ j = 0; j < 4; ++j) {
      A_AVOW(count++, list.Insert(test_cha[j]));
    }
  }
  
  D_COUT_OBJ(list);
  for (ISZ i = 0; i < TestCount; ++i) {
    for (ISZ j = 0; j < 4; ++j) {
      A_AVOW(count++, list.Insert(test_isc[j]));
    }
  }
  D_COUT_OBJ(list);
  for (ISZ i = 0; i < TestCount; ++i) {
    for (ISZ j = 0; j < 4; ++j) {
      A_AVOW(count++, list.Insert(test_cha[j]));
      A_AVOW(count++, list.Insert(test_isc[j]));
      A_AVOW(count++, list.Insert(test_fpc[j]));
      A_AVOW(count++, list.Insert(test_iud[j]));
    }
  }
  D_COUT_OBJ(list);
  for (ISZ i = TestCount - 1; i >= 0; --i) list.Pop();
  
  D_COUT("\n\nTesting STKPack...");
  list.Clear();
  count = 0;

  //for (ISZ j = 0; j < 3; ++j)
  //  A_AVOW(count++, list.Insert(test_cha[j]));
  //A_AVOW(ISZ(3), list.Insert(test_isc[0]));
  //D_COUT_OBJ(list);
  //A_AVOW(ISZ(3), list.Insert(test_cha[3], STKPack));
  // @todo Add more STKPack test cases.
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
  for (DTB type = TEST_MIN; type < TEST_MAX; ++type) {
    D_COUT('\n' << type << ".) ");
    D_COUT(TPrintType<COut>(COut().Star(), type));
  }

  D_COUT("\n\nTTypePrint: ARY_CHA");
#if SEAM == SCRIPT2_LIST
  TPrintType<COut>(COut().Star(), DTB(_ARY | _CHA));
#endif
#endif
  return nullptr;
}
}  //< namespace Script2
#undef TEST_MIN
#undef TEST_MAX
