/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/14.dic.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-9 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_DIC
#include "../dic.hpp"
using namespace _;
#if SEAM == SCRIPT2_DIC
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif

namespace script2 {
template <typename ISZ = ISN, typename IUZ = IUN, typename ISY = ISM,
          typename CHT = CHR>
static void TestDic() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    cSize = 512 * sizeof(CHT),
    cCount = 32,
  };
  D_COUT("Testing ADictionary<IS"
         << CHT('@' + sizeof(ISZ)) << ",IU" << CHT('@' + sizeof(ISZ)) << ",IS"
         << CHT('@' + sizeof(ISY)) << ",CH" << CHT('@' + sizeof(CHT))
         << "> with cSize:" << cSize << " and cCount:" << cCount);

  ABook<TPARAMS, cSize> dic(cCount);

  D_COUT("\n\nsize:" << dic.Size() << " size_bytes:" << dic.SizeBytes()
                     << " size_words:" << dic.SizeWords());
#if D_THIS
  D_COUT("\nPrinting empty dictionary:\n");
  dic.COut();
#endif

  D_COUT("\nPopulating " << cCount << " test words...");

  const CHT *test_words = TTestWords<CHT>(), *word_cursor = test_words;

  for (ISY i = 0; i < 4; ++i) {
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, ISA(i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, IUA(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, ISB(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, IUB(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, ISC(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, IUC(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, ISD(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, IUD(++i)));
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  for (ISY i = 32; i < 128; ++i) {
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, ISA(i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, IUA(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, ISB(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, IUB(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, ISC(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, IUC(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, ISD(++i)));
    A_AVOW(ISY(i), dic.Insert(word_cursor += 16, IUD(++i)));
  }

  D_COUT("\n\nAttmpeting to add a very large string...\n");

  CHT large_string[cSize];
  CHT* cursor = large_string;
  for (ISN i = 0; i < 1024; ++i) *cursor++ = '*';
  *cursor = 0;
  ISY index = dic.Insert(large_string, 1);

#if D_THIS
  dic.COut();
#endif
}
}  // namespace script2
#endif

namespace script2 {
const CHA* Dic(const CHA* args) {
#if SEAM >= SCRIPT2_DIC
  A_TEST_BEGIN;
  TestDic<ISB, IUB, ISA, CHA>();
  TestDic<ISB, IUB, ISA, CHB>();
  TestDic<ISB, IUB, ISA, CHC>();
#if USING_UTF16 == YES_0
  TestDic<ISC, IUC, ISB, CHA>();
  TestDic<ISC, IUC, ISB, CHB>();
  TestDic<ISC, IUC, ISB, CHC>();
#endif
#if USING_UTF32 == YES_0
  TestDic<ISD, IUD, ISB, CHA>();
  TestDic<ISD, IUD, ISB, CHB>();
  TestDic<ISD, IUD, ISB, CHC>();
#endif
#endif
  return nullptr;
}
}  // namespace script2
