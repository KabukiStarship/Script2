/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/11.book.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#if SEAM >= SCRIPT2_BOOK
#include "../book.hpp"
//
#include "test_words.h"
using namespace _;
#define TPARAMS SIZ, UIZ, SIY, CHT
#if SEAM == SCRIPT2_BOOK
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
namespace script2 {
template <typename SIZ = SIN, typename UIZ = UIN, typename SIY = SIG,
          typename CHT = CHR>
void TestBook() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    cSize = 192 * sizeof(CHT),
    cCount = 32,
  };
  D_COUT("Testing ABook<SI"
         << CHT('0' + sizeof(SIZ)) << ",UI" << CHT('0' + sizeof(SIZ)) << ",SI"
         << CHT('0' + sizeof(SIY)) << ",CH" << CHT('0' + sizeof(CHT))
         << "> with cSize:" << cSize << " and cCount:cCount");

  ABook<TPARAMS, cSize, TUIB<cSize>> book(cCount);

  D_COUT("\n\nlist.Size():" << book.Size()
                            << " list.SizeBytes():" << book.SizeBytes()
                            << " list.SizeWords():" << book.SizeWords());
#if D_THIS
  D_COUT("\nPrinting empty book:\n");
  book.COut();
#endif

  D_COUT("\nPopulating " << cCount << " test words...");

  const CHT *test_words = TTestWords<CHT>(), *word_cursor = test_words;

  for (SIY i = 0; i < 4; ++i) {
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, SI1(i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, UI1(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, SI2(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, UI2(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, SI4(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, UI4(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, SI8(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, UI8(++i)));
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  for (SIY i = 32; i < 128; ++i) {
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, SI1(i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, UI1(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, SI2(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, UI2(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, SI4(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, UI4(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, SI8(++i)));
    A_AVOW(SIY(i), book.Insert(word_cursor += 16, UI8(++i)));
  }

  D_COUT("\n\nAttmpeting to add a very large string...\n");

  CHT large_string[cSize];
  CHT* cursor = large_string;
  for (SIN i = 0; i < 1024; ++i) *cursor++ = '*';
  *cursor = 0;
  SIY index = book.Insert(large_string, 1);

#if D_THIS
  book.COut();
#endif
}
}  // namespace script2
#undef TPARAMS
#endif

namespace script2 {
const CH1* Book(const CH1* args) {
#if SEAM >= SCRIPT2_BOOK
  A_TEST_BEGIN;
  TestBook<SI2, UI2, SI1, CH1>();
  TestBook<SI2, UI2, SI1, CH2>();
  TestBook<SI2, UI2, SI1, CH4>();
#if USING_UTF16 == YES_0
  TestBook<SI4, UI4, SI2, CH1>();
  TestBook<SI4, UI4, SI2, CH2>();
  TestBook<SI4, UI4, SI2, CH4>();
#endif
#if USING_UTF32 == YES_0
  TestBook<SI8, UI8, SI2, CH1>();
  TestBook<SI8, UI8, SI2, CH2>();
  TestBook<SI8, UI8, SI2, CH4>();
#endif
#endif
  return nullptr;
}
}  // namespace script2
