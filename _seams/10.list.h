/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/10.list.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_LIST
#include "../list.hpp"
#include "../rng.h"
using namespace _;
#if SEAM == SCRIPT2_LIST
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif

namespace script2 {
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

  enum { kTestCount = 1 };
  ISZ count = 0;
  for (ISZ i = 0; i < kTestCount; ++i) {
    for (ISZ i = 0; i < 4; ++i) {
      A_AVOW(count++, list.Push(test_ch1[i]));
    }
  }
  D_COUT_OBJ(list);
  for (ISZ i = 0; i < kTestCount; ++i) {
    for (ISZ i = 0; i < 4; ++i) {
      A_AVOW(count++, list.Push(test_si4[i]));
    }
  }
  D_COUT_OBJ(list);
  for (ISZ i = 0; i < kTestCount; ++i) {
    for (ISZ i = 0; i < 4; ++i) {
      A_AVOW(count++, list.Push(test_ch1[i]));
      A_AVOW(count++, list.Push(test_si4[i]));
      A_AVOW(count++, list.Push(test_fp4[i]));
      A_AVOW(count++, list.Push(test_ui8[i]));
      // A_AVOW(count++, list.Push(test_st1[i]));
    }
  }
}
}  // namespace script2
#endif

namespace script2 {
static const CHA* List(const CHA* args) {
#if SEAM >= SCRIPT2_LIST
  A_TEST_BEGIN;
  /*TestList<ISB>();
  TestList<ISC>();
  TestList<ISD>();*/
#endif
  return nullptr;
}
}  // namespace script2
