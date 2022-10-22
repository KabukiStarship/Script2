/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/11.Book.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#if SEAM >= SCRIPT2_BOOK
#include "../Book.hpp"
//
#include "TestWords.h"
using namespace _;
#undef  TARGS
#define TARGS \
  typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM, typename DT = DTB
#undef  TPARAMS
#define TPARAMS CHT, ISZ, ISY, DT
#if SEAM == SCRIPT2_BOOK
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
namespace Script2 {
template <typename ISZ = ISN, typename IUZ = IUN, typename ISY = ISM,
          typename CHT = CHR, typename DT = DTB>
void TestBook() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    cSizeBytes = 256 * sizeof(CHT)
  };

  D_COUT("\n\nTesting ABook<IS" << CSizef<ISZ>() << ",IU" << CSizef<IUZ>() << ",IS"
         << CSizef<ISY>() << ",CH" << CSizef<CHT>() << "> with cSizeBytes:" 
         << cSizeBytes);

  ABook<TPARAMS, cSizeBytes> book;

  D_COUT("\n\nAfter TBookInit book.SizeBytes():" << book.SizeBytes()
         << " book.Count():" << book.Count()
         << " book.CountMax():" << book.CountMax());
#if D_THIS
  D_COUT("\nPrinting empty book:\n");
  book.COut();
#endif

  ISZ count_max = book.CountMax();
  D_COUT("\nPopulating " << count_max << " test words...");

  const CHT *test_words = TTestWords<CHT>::Words(), *word_cursor = test_words;
  ISZ word_step = TTestWords<CHT>::cCharsMax;
  for (ISY i = 0; i < count_max; ++i) {
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, ISA(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, IUA(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, ISB(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, IUB(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, ISC(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, IUC(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, ISD(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, IUD(i)));
    D_COUT("\n\nFoo baby!\n\n");
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  for (ISY i = ISY(count_max - 1); i < ISY(TTestWords<CHT>::cWordsMax) - count_max;
       ++i) {
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, ISA(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, IUA(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, ISB(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, IUB(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, ISC(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, IUC(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, ISD(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += word_step, IUD(i)));
    D_COUT("\n\nFoo dady\n\n");
  }

  D_COUT("\n\nAttmpeting to add a very large string...\n");

  CHT large_string[cSizeBytes];
  CHT* cursor = large_string;
  for (ISN i = 0; i < 1024; ++i) *cursor++ = '*';
  *cursor = 0;
  ISZ index = book.Insert(large_string, 1);

#if D_THIS
  book.COut();
#endif
}
}  //< namespace Script2
#undef TPARAMS
#endif

namespace Script2 {
const CHA* Book(const CHA* args) {
#if SEAM >= SCRIPT2_BOOK
  A_TEST_BEGIN;
  TestBook<ISB, IUB, ISA, CHA>();
  TestBook<ISB, IUB, ISA, CHB>();
  TestBook<ISB, IUB, ISA, CHC>();
#if USING_UTF16 == YES_0
  TestBook<ISC, IUC, ISB, CHA>();
  TestBook<ISC, IUC, ISB, CHB>();
  TestBook<ISC, IUC, ISB, CHC>();
#endif
#if USING_UTF32 == YES_0
  TestBook<ISD, IUD, ISB, CHA>();
  TestBook<ISD, IUD, ISB, CHB>();
  TestBook<ISD, IUD, ISB, CHC>();
#endif
#endif
  return nullptr;
}
}  //< namespace Script2
