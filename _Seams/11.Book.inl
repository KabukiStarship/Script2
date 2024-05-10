/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/11.Book.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */
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
template<typename ISZ = ISN, typename ISY = ISM,
         typename CHT = CHR, typename  DT = DTB>
void TestBook() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    SizeBytes = 512 * sizeof(CHT)
  };

  D_COUT("\n\nTesting ABook<IS" << CATypeSWCH<ISZ>() << ",IS" << CATypeSWCH<ISY>() << 
         ",CH" << CATypeSWCH<CHT>() << ",DT" << CATypeSWCH<DT>() << 
         "> with SizeBytes:" << SizeBytes);

  ABook<TPARAMS, SizeBytes> book;

  D_COUT("\n\nAfter TBookInit book.SizeBytes():" << book.SizeBytes() << 
         " book.Count():" << book.Count() << 
         " book.CountMax():" << book.CountMax());
#if D_THIS
  D_COUT("\nPrinting empty book:\n");
  book.COut();
#endif

  ISZ test_word_count = book.CountMax();
  D_COUT("\nPopulating " << test_word_count << " test words...");

  const CHT *test_words = TTestWords<CHT>::Words(), *word_cursor = test_words;
  ISZ word_step = TTestWords<CHT>::CharsMax;
  D_COUT("\n\nStep 0:\n" << Linef("---") << '\n');

  D_COUT("\n\nStep 1:\n" << Linef("---") << '\n');
  A_AVOW(ISY(1), book.Insert(word_cursor += word_step, ISA(1)));
  D_COUT("\n\nStep 2:\n" << Linef("---") << '\n');
  A_AVOW(ISY(2), book.Insert(word_cursor += word_step, IUA(2)));
  D_COUT("\n\nStep 3:\n" << Linef("---") << '\n');
  A_AVOW(ISY(3), book.Insert(word_cursor += word_step, ISB(3)));
  D_COUT("\n\nStep 4:\n" << Linef("---") << '\n');
  A_AVOW(ISY(4), book.Insert(word_cursor += word_step, IUB(4)));
  D_COUT("\n\nStep 5:\n" << Linef("---") << 
         "\nWill have 1-byte unused space.\n");
  A_AVOW(ISY(5), book.Insert(word_cursor += word_step, ISC(5)));
  D_COUT("\n\nStep 6:\n" << Linef("---") << '\n');
  A_AVOW(ISY(6), book.Insert(word_cursor += word_step, IUC(6)));
  D_COUT("\n\nStep 7:\n" << Linef("---") << '\n');
  A_AVOW(ISY(7), book.Insert(word_cursor += word_step, ISD(7)));
  book.COut();

  D_COUT("\n\nStep 8:\n" << Linef("---") << "\nTesting Factory.Grow...\n");
  A_AVOW(ISY(8), book.Insert(word_cursor += word_step, IUD(8)));
  book.COut();


  for (ISY i = ISY(test_word_count - 1);
       i < ISY(TTestWords<CHT>::WordsMax) - test_word_count; ++i) {
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

  CHT large_string[SizeBytes] = {0};
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
  TestBook<ISB, ISA, CHA>();
  TestBook<ISB, ISA, CHB>();
  TestBook<ISB, ISA, CHC>();
#if USING_UTF16 == YES_0
  TestBook<ISC, ISB, CHA>();
  TestBook<ISC, ISB, CHB>();
  TestBook<ISC, ISB, CHC>();
#endif
#if USING_UTF32 == YES_0
  TestBook<ISD, ISB, CHA>();
  TestBook<ISD, ISB, CHB>();
  TestBook<ISD, ISB, CHC>();
#endif
#endif
  return nullptr;
}
}  //< namespace Script2
