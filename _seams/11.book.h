/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/11.book.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#if SEAM >= SCRIPT2_BOOK
#include "../book.hpp"
using namespace _;
#if SEAM == SCRIPT2_BOOK
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

namespace script2 {
static const CHA* TestBook(const CHA* args) {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    kSize = 192 * sizeof(Char),
    kCount = 32,
  };
  D_COUT("Testing ALoom<CH"
         << Char('0' + sizeof(Char)) << ",SI" << Char('0' + sizeof(SIZ))
         << "> with kSize:" << kSize << " and kCount:kCount");

  ALoom<Char, SIZ, kSize, TUIB<kSize>> book(kCount);
#if D_THIS
  D_COUT("\nPrinting empty book:\n");
  book.COut();
#endif

  enum {
    kLengthMax = (kSize << 2) - 1,
  };

  Char string[kLengthMax + 1];
  Char* String_end = &string[kLengthMax];

  for (SIN i = 0; i < 32; ++i) {
    TSPrint<Char>(string, String_end, i);
    A_AVOW((SIZ)i, book.Add(string));
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  TSPrint<Char>(string, String_end, 32);
  A_AVOW((SIZ)32, book.Add(string));

  for (SIN i = 33; i < 96; ++i) {
    TSPrint<Char>(string, String_end, i);
    A_AVOW((SIZ)(i), book.Add(string));
  }

  TSPrint<Char>(string, String_end, 96);
  A_AVOW((SIZ)96, book.Add(string));

  D_COUT("\n\nAttmpeting to add a very large string...\n");

  for (SIN i = 0; i < kLengthMax; ++i) string[i] = '*';

  string[kLengthMax] = 0;

  SIZ index = book.Add(string);
#if D_THIS
  book.COut();
#endif
  A_AVOW((SIZ)97, index);

#if D_THIS
  D_COUT('\n');
  book.COut();
  D_COUT('\n');
#endif

  D_COUT("\nTesting TLoomFind...\n");

  static const Char a[] = {'A', '\0'}, b[] = {'B', '\0'}, c[] = {'C', '\0'},
                    d[] = {'D', '\0'}, abc[] = {'a', 'b', 'c', '\0'},
                    bac[] = {'b', 'a', 'c', '\0'},
                    cba[] = {'c', 'b', 'a', '\0'},
                    cab[] = {'c', 'a', 'b', '\0'},
                    test[] = {'t', 'e', 's', 't', '\0'};

  A_AVOW((SIZ)98, book.Add(d));

  A_AVOW((SIZ)98, book.Find(d));

  A_AVOW((SIZ)99, book.Add(c));
  A_AVOW((SIZ)98, book.Find(d));
  A_AVOW((SIZ)99, book.Find(c));

  A_AVOW((SIZ)100, book.Add(b));
  A_AVOW((SIZ)98, book.Find(d));
  A_AVOW((SIZ)99, book.Find(c));
  A_AVOW((SIZ)100, book.Find(b));

  A_AVOW((SIZ)101, book.Add(a));
  A_AVOW((SIZ)98, book.Find(d));
  A_AVOW((SIZ)99, book.Find(c));
  A_AVOW((SIZ)100, book.Find(b));
  A_AVOW((SIZ)101, book.Find(a));

  A_AVOW((SIZ)102, book.Add(abc));
  A_AVOW((SIZ)102, book.Find(abc));

  A_AVOW((SIZ)103, book.Add(bac));
  A_AVOW((SIZ)102, book.Find(abc));
  A_AVOW((SIZ)103, book.Find(bac));

  A_AVOW((SIZ)104, book.Add(cba));
  A_AVOW((SIZ)102, book.Find(abc));
  A_AVOW((SIZ)103, book.Find(bac));
  A_AVOW((SIZ)104, book.Find(cba));

  A_AVOW((SIZ)105, book.Add(cab));
  A_AVOW((SIZ)102, book.Find(abc));
  A_AVOW((SIZ)103, book.Find(bac));
  A_AVOW((SIZ)104, book.Find(cba));
  A_AVOW((SIZ)105, book.Find(cab));

#if D_THIS
  D_COUT('\n');
  book.COut();
  D_COUT('\n');
#endif

  A_AVOW((SIZ)-1, book.Find(test));
}
}  // namespace script2
#endif

namespace script2 {
static const CHA* Book(const CHA* args) {
#if SEAM >= SCRIPT2_BOOK
  A_TEST_BEGIN;
  TestBook<CHA, ISB>();
  TestBook<CHA, ISC>();
#if USING_UTF16 == YES_0
  TestBook<CHB, ISB>();
  TestBook<CHB, ISC>();
#endif
#if USING_UTF32 == YES_0
  TestBook<CHC, ISC>();
#endif
#endif
  return nullptr;
}
}  // namespace script2
