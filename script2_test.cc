/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_test.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#include "ttest.h"

#include "cconsole.h"

#include "test_debug.inl"

namespace _ {

BOL TestWarn(const char* function, const char* file, int line) {
  Printf("\nAssertion failed in function %s at line %d in \"%s\"", function,
         line, file);
  return true;
}

BOL TestAssert(const char* function, const char* file, int line) {
  TestWarn(function, file, line);
  Pause();
  return true;
}

int SeamTreeTest(int arg_count, char** args, char* seam_log, int seam_log_size,
                 TestCase* tests, int test_count) {
  if (seam_log_size < 0) return APP_EXIT_FAILURE;
  const char* result =
      TestTree(seam_log, seam_log + seam_log_size - 1,
               ArgsToString(arg_count, args), tests, test_count);
  if (result) {
    Print("\nERROR: ", result);
    return APP_EXIT_FAILURE;
  }
  return APP_EXIT_SUCCESS;
}

const char* TestTree(char* seam_log, char* seam_end, const char* args,
                     TestCase* tests, int count) {
  ASSERT(seam_log || seam_end || args || tests);
  for (int i = 0; i < count; ++i) {
    TestCase test = tests[i];
    if (!test) {
      Print("\nERROR: Test ");
      Print(i);
      Print(" missing!");
      return "";
    }
    const char* seam = test(nullptr, nullptr, nullptr);
    if (!seam) {
      Print("\nERROR: SEAM ");
      Print(i + 1);
      Print(" missing!");
      return "";
    }
    PrintHeading("Testing ", seam, 1);
    const char* error = test(seam_log, seam_end, args);
    if (error) return error;
    Print("\nDone testing ", seam);
  }
  Print("\n\nUnit test finished successfully! (:-)+==<\n");
  return nullptr;
}

BOL TestBegin(char* seam_log, char* seam_end, const char* args) {
  return !(!seam_log || !seam_end || !args);
}

BOL Test(BOL condition) { return condition; }

static const char kStringErrorExpecting[] = "\nERROR: Expecting:";
static const char kStringFound[] = "\n           Found:";
static const char kStringDifference[] = "\n      Difference:";
static const char kStringErrorNil[] = "\nERROR: value was nil!";

BOL Test(const char* a, const char* b) {
  int result = ::_::TStringCompare<char>(a, b);
  if (!result) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  Print(kStringDifference);
  Print(result);
  return false;
}

BOL Test(const char16_t* a, const char16_t* b) {
  int result = ::_::TStringCompare<char16_t>(a, b);
  if (!result) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  Print(kStringDifference);
  Print(result);
  return false;
}

BOL Test(const char32_t* a, const char32_t* b) {
  int result = ::_::TStringCompare<char32_t>(a, b);
  if (!result) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  Print(kStringDifference);
  Print(result);
  return false;
}

BOL Test(const void* a, const void* b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  PrintHex(a);
  Print(kStringFound);
  PrintHex(b);
  return false;
}

BOL Test(UI1 a, UI1 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  return false;
}

BOL Test(SI1 a, SI1 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  return false;
}

BOL Test(UI2 a, UI2 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  return false;
}

BOL Test(SI2 a, SI2 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  return false;
}

BOL Test(UI4 a, UI4 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  return false;
}

BOL Test(SI4 a, SI4 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  return false;
}

BOL Test(UI8 a, UI8 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  return false;
}

BOL Test(SI8 a, SI8 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  return false;
}

BOL Test(FLT a, FLT b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  return false;
}

BOL Test(DBL a, DBL b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  return false;
}

BOL Test(const void* value) {
  if (value) return true;
  Print("\nERROR:Nil pointer!");
  return false;
}

BOL Test(UI1 value) {
  if (value) return true;
  Print(kStringErrorNil);
  return false;
}

BOL Test(SI1 value) {
  if (value) return true;
  Print(kStringErrorNil);
  return false;
}

BOL Test(UI2 value) {
  if (value) return true;
  Print(kStringErrorNil);
  return false;
}

BOL Test(SI2 value) {
  if (value) return true;
  Print(kStringErrorNil);
  return false;
}

BOL Test(UI4 value) {
  if (value) return true;
  Print(kStringErrorNil);
  return false;
}

BOL Test(SI4 value) {
  if (value) return true;
  Print(kStringErrorNil);
  return false;
}

BOL Test(UI8 value) {
  if (value) return true;
  Print(kStringErrorNil);
  return false;
}

BOL Test(SI8 value) {
  if (value) return true;
  Print(kStringErrorNil);
  return false;
}

BOL Test(FLT value) {
  if (value) return true;
  Print(kStringErrorNil);
  return false;
}

BOL Test(DBL value) {
  if (value) return true;
  Print(kStringErrorNil);
  return false;
}

}  // namespace _

#include "test_release.inl"
