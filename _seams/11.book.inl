/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/11.book.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#if SEAM >= SCRIPT2_BOOK
#include "../book.hpp"
//
#include "test_words.h"
using namespace _;
#define TPARAMS CHT, ISZ, ISY
#if SEAM == SCRIPT2_BOOK
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
namespace script2 {
template <typename ISZ = ISN, typename IUZ = IUN, typename ISY = ISM,
          typename CHT = CHR>
void TestBook() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    cSize = 256 * sizeof(CHT),
    cCount = 32,
  };
  D_COUT("Testing ABook<IS"
         << CHT('@' + sizeof(ISZ)) << ",IU" << CHT('@' + sizeof(ISZ)) << ",IS"
         << CHT('@' + sizeof(ISY)) << ",CH" << CHT('@' + sizeof(CHT))
         << "> with cSize:" << cSize << " and cCount:" << cCount);

  ABook<TPARAMS, cSize> book(cCount);

  D_COUT("\n\nsize:" << book.Size() << " size_bytes:" << book.SizeBytes()
                     << " size_words:" << book.SizeWords());
#if D_THIS
  D_COUT("\nPrinting empty book:\n");
  book.COut();
#endif

  D_COUT("\nPopulating " << cCount << " test words...");

  const CHT *test_words = TTestWords<CHT>(), *word_cursor = test_words;

  for (ISY i = 0; i < 4; ++i) {
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, ISA(i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, IUA(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, ISB(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, IUB(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, ISC(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, IUC(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, ISD(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, IUD(++i)));
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  for (ISY i = 32; i < 128; ++i) {
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, ISA(i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, IUA(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, ISB(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, IUB(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, ISC(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, IUC(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, ISD(++i)));
    A_AVOW(ISY(i), book.Insert(word_cursor += 16, IUD(++i)));
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
}  // namespace script2
#undef TPARAMS
#endif

namespace script2 {
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
}  // namespace script2
