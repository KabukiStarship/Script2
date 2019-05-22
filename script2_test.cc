/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_test.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#include "c_cout.h"
#include "c_test.h"
#include "module_debug.inl"
#include "t_uniprinter.h"

namespace _ {

void TestFunctionLine(SI4 line, const CH1* function, const CH1* file) {
  Printf("line %d in %s in \"%s\"", line, function, file);
}

BOL TestWarn(SI4 line, const CH1* function, const CH1* file,
             const CH1* header) {
  PrintNL();
  Print(header);
  TestFunctionLine(line, function, file);
  return true;
}

BOL TestFail(SI4 line, const CH1* function, const CH1* file) {
  BOL result = TestWarn(line, function, file);
  return result;
}

SI4 SeamTreeTest(SI4 arg_count, CH1** args, CH1* seam_log, SI4 seam_log_size,
                 TestCase* tests, SI4 test_count) {
  if (seam_log_size < 0) return APP_EXIT_FAILURE;
  const CH1* result = TestTree(seam_log, seam_log + seam_log_size - 1,
                               ArgsToSring(arg_count, args), tests, test_count);
  if (result) {
    Print("\nERROR: ", result);
    PAUSE("");
    return APP_EXIT_FAILURE;
  }
  PAUSE("");
  return APP_EXIT_SUCCESS;
}

const CH1* TestTree(CH1* seam_log, CH1* seam_end, const CH1* args,
                    TestCase* tests, SI4 count) {
  ASSERT(seam_log || seam_end || args || tests);
  for (SI4 i = 0; i < count; ++i) {
    TestCase test = tests[i];
    if (!test) {
      Print("\nERROR: Test ");
      Print(i);
      Print(" missing!");
      return "";
    }
    const CH1* seam = test(nullptr, nullptr, nullptr);
    if (!seam) {
      Print("\nERROR: SEAM ");
      Print(i + 1);
      Print(" missing!");
      return "";
    }
    PrintHeadingf("Testing ", nullptr, 80, seam);
    const CH1* error = test(seam_log, seam_end, args);
    if (error) return error;
    Print("\nDone testing ", seam);
    PrintNL();
  }
  Print("\n\nUnit test finished successfully! (:-)+==<\n");
  return nullptr;
}

BOL TestBegin(CH1* seam_log, CH1* seam_end, const CH1* args) {
  return !(!seam_log || !seam_end || !args);
}

BOL Test(BOL condition) { return condition; }

static const CH1 kStrandErrorExpecting[] = "\nERROR: Expecting:\0";
static const CH1 kStrandFound[] = "\n           Found:\0";
static const CH1 kStrandDifference[] = "\n      Difference:\0";
static const CH1 kStrandErrorNil[] = "\nERROR: value was nil!\0";

BOL Test(const CH1* a, const CH1* b) {
  SI4 result = ::_::TSTRCompare<const CH1>(a, b);
  if (!result) return true;
  Print(kStrandErrorExpecting);
  Print(a);
  Print(kStrandFound);
  Print(b);
  Print(kStrandDifference);
  Print(result);
  return false;
}

BOL Test(const CH2* a, const CH2* b) {
  SI4 result = ::_::TSTRCompare<const CH2>(a, b);
  if (!result) return true;
  Print(kStrandErrorExpecting);
  Print(a);
  Print(kStrandFound);
  Print(b);
  Print(kStrandDifference);
  Print(result);
  return false;
}

#if SEAM >= SCRIPT2_1
BOL Test(const CH4* a, const CH4* b) {
  SI4 result = ::_::TSTRCompare<const CH4>(a, b);
  if (!result) return true;
  Print(kStrandErrorExpecting);
  Print(a);
  Print("   ");
  PrintHex(a);
  Print(kStrandFound);
  Print(b);
  Print(kStrandDifference);
  Print(result);
  return false;
}

BOL Test(CH1 a, CH1 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(CH2 a, CH2 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(CH4 a, CH4 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(const void* a, const void* b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(kStrandFound);
  PrintHex(b);
  return false;
}

BOL Test(UI1 a, UI1 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(SI1 a, SI1 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(UI2 a, UI2 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  Print(a);
  Print("   ");
  PrintHex(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(SI2 a, SI2 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(UI4 a, UI4 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(SI4 a, SI4 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(UI8 a, UI8 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(SI8 a, SI8 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(FP4 a, FP4 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}

BOL Test(FP8 a, FP8 b) {
  if (a == b) return true;
  Print(kStrandErrorExpecting);
  PrintHex(a);
  Print(':');
  Print(a);
  Print(kStrandFound);
  PrintHex(b);
  Print(':');
  Print(b);
  return false;
}
#endif

BOL Test(const void* value) {
  if (value) return true;
  Print("\nERROR:Nil pointer!");
  return false;
}

BOL Test(UI1 value) {
  if (value) return true;
  Print(kStrandErrorNil);
  return false;
}

BOL Test(SI1 value) {
  if (value) return true;
  Print(kStrandErrorNil);
  return false;
}

BOL Test(UI2 value) {
  if (value) return true;
  Print(kStrandErrorNil);
  return false;
}

BOL Test(SI2 value) {
  if (value) return true;
  Print(kStrandErrorNil);
  return false;
}

BOL Test(UI4 value) {
  if (value) return true;
  Print(kStrandErrorNil);
  return false;
}

BOL Test(SI4 value) {
  if (value) return true;
  Print(kStrandErrorNil);
  return false;
}

BOL Test(UI8 value) {
  if (value) return true;
  Print(kStrandErrorNil);
  return false;
}

BOL Test(SI8 value) {
  if (value) return true;
  Print(kStrandErrorNil);
  return false;
}

BOL Test(FP4 value) {
  if (value) return true;
  Print(kStrandErrorNil);
  return false;
}

BOL Test(FP8 value) {
  if (value) return true;
  Print(kStrandErrorNil);
  return false;
}

}  // namespace _

#include "module_release.inl"
