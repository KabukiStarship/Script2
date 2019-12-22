/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/00.uniprinter.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-9 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_UNIPRINTER
#include "../stringf.hpp"
#if SEAM == SCRIPT2_UNIPRINTER
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

using namespace _;

namespace script2 {
inline const CHA* Uniprinter(const CHA* args) {
#if SEAM >= SCRIPT2_UNIPRINTER
  A_TEST_BEGIN;

  D_COUT(Headingf("Testing ArgsToString"));

  CHA arg_String[48] = "C:\\Windows\0Foo\0\0Bar    \0\0\0   420    \0";
  D_COUT("arg_String:\"");
  CHA* cursor = arg_String;
  for (ISN i = 0; i < 35; ++i) D_COUT(*cursor++);
  D_COUT('\"');

  CHA* test_args[] = {arg_String, arg_String + 11, arg_String + 16,
                      arg_String + 26};
  const ISC cArgCount = 4;

  D_COUT("\nArguments:\n");
  for (ISC i = 0; i < cArgCount; ++i) {
    CHA* arg = test_args[i];
    if (arg) {
      D_COUT("\n" << i << ".)\"" << arg << "\" delta:" << arg - arg_String);
    } else {
      D_COUT("\nNil arg.");
    }
  }
  D_COUT("\n\nRunning ArgsToString... ");

  D_ASSERT(ArgsToString(cArgCount, test_args));

  D_COUT("Result:\"");
  D_COUT(test_args[1]);

  CHC ch4_found;

  D_COUT(Headingf("Testing CHA* SPrint (CHA*,CHA*,CHC);"));
  enum {
    cSTAEdgeCondition2 = 0x7f,
    cSTAEdgeCondition3 = 0x7ff,
    cSTAEdgeCondition4 = 0xffff,
    cSTACount = 8
  };
  CHA str1[cSTACount];
  CHA* str1_cursor = SPrint(str1, cSTACount, CHC(0));
  A_ASSERT(str1_cursor);
  const CHA* str1_result = SScan(str1, ch4_found);
  D_ASSERT_INDEX(str1_result, ISC(0));
  A_AVOW_INDEX(CHC(0), ch4_found, 0);

  for (CHC ch4_expected = cSTAEdgeCondition4; ch4_expected < (1 << 21);
       ch4_expected += 64) {
    str1_cursor = SPrint(str1, cSTACount, ch4_expected);
    D_ASSERT_INDEX(str1_cursor, IUC(ch4_expected));
    const CHA* str1_result = SScan(str1, ch4_found);
    D_ASSERT_INDEX(str1_result, IUC(ch4_expected));
    A_AVOW_INDEX(ch4_expected, ch4_found, ISC(ch4_expected));
  }

#if USING_UTF16 == YES_0
  D_COUT(Headingf("Testing Testing CHB* SPrint (CHB*,CHB*,CHC)..."));
  enum {
    cSTRBCount = 4,
  };
  CHB str2[cSTRBCount];
  CHB* str2_cursor = str2;
  str2_cursor = SPrint(str2, cSTRBCount - 1, CHC(0));
  D_COUT(Hexf(str2) << reinterpret_cast<CHA*>(str2 + 3) - 1);
  A_ASSERT(str2_cursor);
  const CHB* str2_result = SScan(str2, ch4_found);
  D_ASSERT_INDEX(str2_result, ISC(0));
  A_AVOW_INDEX(CHC(0), ch4_found, 0);

  for (CHC ch4_expected = 1; ch4_expected < (1 << 10); ++ch4_expected) {
    str2_cursor = SPrint(str2, 3, ch4_expected);
    D_ASSERT_INDEX(str2_cursor, IUC(ch4_expected));
    const CHB* str2_result = SScan(str2, ch4_found);
    D_ASSERT_INDEX(str2_result, IUC(ch4_expected));
    A_AVOW_INDEX(ch4_expected, ch4_found, ISC(ch4_expected));
  }
#endif

#endif
  return 0;
}
}  // namespace script2
