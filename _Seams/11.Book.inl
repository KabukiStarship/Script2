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
  typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM, typename DT = DT2
#undef  TPARAMS
#define TPARAMS CHT, ISZ, ISY, DT
#if SEAM == SCRIPT2_BOOK
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
namespace Script2 {
template <typename ISZ = ISN, typename IUZ = IUN, typename ISY = ISM,
          typename CHT = CHR, typename DT = DT2>
void TestBook() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    cSize = 256 * sizeof(CHT),
    cCount = 32,
  };

  D_COUT("\n\nAttempting to make a Book of size:" << cSize << 
         " TBookSizeMin: " << CBookSizeMin<TPARAMS>(cCount) << "\n\n");

  D_COUT("Testing ABook<IS" << CSizef<ISZ>() << ",IU" << CSizef<IUZ>() << ",IS"
         << CSizef<ISY>() << ",CH" << CSizef<CHT>() << "> with cSize:" << cSize 
         << " and cCount:" << cCount);

  ABook<TPARAMS, cSize> book(cCount, cSize);

  D_COUT("\n\nAfter ABook\nsize:" << book.Size() << " size_bytes:" 
         << book.SizeBytes() << " size_words:" << book.SizeWords() 
         << "\nKeys\n");
  TListPrint<COut, ISZ, DT>(COut().Star(), book.List());
#if D_THIS
  D_COUT("\nPrinting empty book:\n");
  book.COut();
#endif

  D_COUT("\nPopulating " << cCount << " test words...");

  const CHT *test_words = TTestWords<CHT>::Words(), *word_cursor = test_words;

  for (ISY i = -1; i < 32; ++i) {
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, ISA(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, IUA(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, ISB(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, IUB(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, ISC(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, IUC(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, ISD(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, IUD(i)));
    D_COUT("\n\nFoo baby\n\n");
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  for (ISY i = 31; i < 128; ++i) {
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, ISA(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, IUA(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, ISB(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, IUB(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, ISC(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, IUC(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, ISD(i)));
    A_AVOW(ISY(++i), book.Insert(word_cursor += 16, IUD(i)));
    D_COUT("\n\nFoo dady\n\n");
  }

  D_COUT("\n\nAttmpeting to add a very large string...\n");

  CHT large_string[cSize];
  CHT* cursor = large_string;
  for (ISN i = 0; i < 1024; ++i) *cursor++ = '*';
  *cursor = 0;
  ISY index = book.Insert(large_string, 1);

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
