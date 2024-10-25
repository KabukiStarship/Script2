/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/14.Dic.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_DIC
#include "../Dic.hpp"
using namespace _;
#if SEAM == SCRIPT2_DIC
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#undef TPARAMS
#undef TARGS
#define TPARAMS CHT, ISZ, ISY, DT, HSH
#define TARGS \
  typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM, \
  typename DT = DTB, typename HSH = IUN

namespace Script2 {
template<TARGS>
static void TestDic() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    Size = 512 * sizeof(CHT),
    cCount = 32,
  };
  D_COUT("Testing ADic<IS"
         << CSizef<ISZ> () << ",IU" << CSizef<ISZ> () << ",IS" << CSizef<ISY>() << ",CH"
                                  << CSizef<CHT>()
         << "> with Size:" << Size << " and cCount:" << cCount);

  ADic<TPARAMS, Size> dic(cCount);

  D_COUT("\n\nsize:" << dic.Size() << " bytes:" << dic.SizeBytes()
                     << " size_words:" << dic.SizeWords());
#if D_THIS
  D_COUT("\nPrinting empty dictionary:\n");
  dic.COut();
#endif

  D_COUT("\nPopulating " << cCount << " test words...");

  const CHT *test_words = TTestWords<CHT>::Words(), *word_cursor = test_words;

  for (ISY i = -1; i < 32; ++i) {
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, ISA(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, IUA(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, ISB(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, IUB(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, ISC(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, IUC(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, ISD(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, IUD(i)));
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  for (ISY i = 31; i < 128; ++i) {
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, ISA(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, IUA(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, ISB(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, IUB(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, ISC(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, IUC(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, ISD(i)));
    A_AVOW(ISY(++i), dic.Insert(word_cursor += 16, IUD(i)));
  }

  D_COUT("\n\nAttmpeting to add a very large string...\n");

  CHT large_string[Size] = { 0 };
  CHT* cursor = large_string;
  for (ISN i = 0; i < 1024; ++i) *cursor++ = '*';
  *cursor = 0;
  ISY index = dic.Insert(large_string, 1);

#if D_THIS
  dic.COut();
#endif
}
}  //< namespace Script2
#endif

namespace Script2 {
const CHA* Dic(const CHA* args) {
#if SEAM >= SCRIPT2_DIC
  A_TEST_BEGIN;
  TestDic<CHA, ISB, ISA, IUB>();
  TestDic<CHB, ISB, ISA, IUB>();
  TestDic<CHC, ISB, ISA, IUB>();
#if USING_UTF16 == YES_0
  TestDic<CHA, ISC, ISB, IUC>();
  TestDic<CHB, ISC, ISB, IUC>();
  TestDic<CHC, ISC, ISB, IUC>();
#endif
#if USING_UTF32 == YES_0
  TestDic<CHA, ISD, ISB, IUD>();
  TestDic<CHB, ISD, ISB, IUD>();
  TestDic<CHC, ISD, ISB, IUD>();
#endif
#endif
  return nullptr;
}
}  //< namespace Script2
#undef TARGS
#undef TPARAMS
