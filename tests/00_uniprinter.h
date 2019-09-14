/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /00_uniprinter.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#include "stringf.hpp"

#if SEAM == SCRIPT2_UNIPRINTER
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
inline const CH1* Uniprinter(const CH1* args) {
#if SEAM >= SCRIPT2_UNIPRINTER
  A_TEST_BEGIN;

  D_COUT(Headingf("Testing ArgsToString"));

  CH1 arg_String[48] = "C:\\Windows\0Foo\0\0Bar    \0\0\0   420    \0";
  D_COUT("arg_String:\"");
  CH1* cursor = arg_String;
  for (SIN i = 0; i < 35; ++i) D_COUT(*cursor++);
  D_COUT('\"');

  CH1* test_args[] = {arg_String, arg_String + 11, arg_String + 16,
                      arg_String + 26};
  const SI4 kArgCount = 4;

  D_COUT("\nArguments:\n");
  for (SI4 i = 0; i < kArgCount; ++i) {
    CH1* arg = test_args[i];
    if (arg) {
      D_COUT("\n" << i << ".)\"" << arg << "\" delta:" << arg - arg_String);
    } else {
      D_COUT("\nNil arg.");
    }
  }
  D_COUT("\n\nRunning ArgsToString... ");

  D_ASSERT(ArgsToString(kArgCount, test_args));

  D_COUT("Result:\"");
  D_COUT(test_args[1]);

  CH4 ch4_found;

  D_COUT(Headingf("Testing CH1* SPrint (CH1*,CH1*,CH4);"));
  enum {
    kUTF8EdgeCondition2 = 0x7f,
    kUTF8EdgeCondition3 = 0x7ff,
    kUTF8EdgeCondition4 = 0xffff,
    kSTR1Count = 8
  };
  CH1 str1[kSTR1Count];
  CH1* str1_cursor = SPrint(str1, kSTR1Count, CH4(0));
  A_ASSERT(str1_cursor);
  const CH1* str1_result = SScan(str1, ch4_found);
  D_ASSERT_INDEX(str1_result, SI4(0));
  A_AVOW_INDEX(CH4(0), ch4_found, 0);

  for (CH4 ch4_expected = kUTF8EdgeCondition4; ch4_expected < (1 << 21);
       ch4_expected += 64) {
    str1_cursor = SPrint(str1, kSTR1Count, ch4_expected);
    D_ASSERT_INDEX(str1_cursor, UI4(ch4_expected));
    const CH1* str1_result = SScan(str1, ch4_found);
    D_ASSERT_INDEX(str1_result, UI4(ch4_expected));
    A_AVOW_INDEX(ch4_expected, ch4_found, SI4(ch4_expected));
  }

#if USING_UTF16 == YES_0
  D_COUT(Headingf("Testing Testing CH2* SPrint (CH2*,CH2*,CH4)..."));
  enum {
    kSTR2Count = 4,
  };
  CH2 str2[kSTR2Count];
  CH2* str2_cursor = str2;
  str2_cursor = SPrint(str2, kSTR2Count - 1, CH4(0));
  D_COUT(Hexf(str2) << reinterpret_cast<CH1*>(str2 + 3) - 1);
  A_ASSERT(str2_cursor);
  const CH2* str2_result = SScan(str2, ch4_found);
  D_ASSERT_INDEX(str2_result, SI4(0));
  A_AVOW_INDEX(CH4(0), ch4_found, 0);

  for (CH4 ch4_expected = 1; ch4_expected < (1 << 10); ++ch4_expected) {
    str2_cursor = SPrint(str2, 3, ch4_expected);
    D_ASSERT_INDEX(str2_cursor, UI4(ch4_expected));
    const CH2* str2_result = SScan(str2, ch4_found);
    D_ASSERT_INDEX(str2_result, UI4(ch4_expected));
    A_AVOW_INDEX(ch4_expected, ch4_found, SI4(ch4_expected));
  }
#endif

#endif
  return 0;
}
}  // namespace script2
