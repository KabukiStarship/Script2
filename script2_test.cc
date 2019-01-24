/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_test.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#include "ctest.h"

#include "cconsole.h"

#include "tbinary.h"

#include "global_debug.inl"

namespace _ {

void TestFunctionLine(SI4 line, const CH1* function, const CH1* file) {
  Printf("line %d in %s in \"%s\"", line, function, file);
}

BOL TestWarn(SI4 line, const CH1* function, const CH1* file,
             const CH1* header) {
  Print('\n');
  Print(header);
  TestFunctionLine(line, function, file);
  return true;
}

BOL TestAssert(SI4 line, const CH1* function, const CH1* file) {
  BOL result = TestWarn(line, function, file);
  return result;
}

SI4 SeamTreeTest(SI4 arg_count, CH1** args, CH1* seam_log, SI4 seam_log_size,
                 TestCase* tests, SI4 test_count) {
  if (seam_log_size < 0) return APP_EXIT_FAILURE;
  const CH1* result =
      TestTree(seam_log, seam_log + seam_log_size - 1,
               ArgsToString(arg_count, args), tests, test_count);
  if (result) {
    Print("\nERROR: ", result);
    return APP_EXIT_FAILURE;
  }
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
    PrintHeading("Testing ", seam, 1);
    const CH1* error = test(seam_log, seam_end, args);
    if (error) return error;
    Print("\nDone testing ", seam);
  }
  Print("\n\nUnit test finished successfully! (:-)+==<\n");
  return nullptr;
}

BOL TestBegin(CH1* seam_log, CH1* seam_end, const CH1* args) {
  return !(!seam_log || !seam_end || !args);
}

BOL Test(BOL condition) { return condition; }

static const CH1 kStringErrorExpecting[] = "\nERROR: Expecting:\0";
static const CH1 kStringFound[] = "\n           Found:\0";
static const CH1 kStringDifference[] = "\n      Difference:\0";
static const CH1 kStringErrorNil[] = "\nERROR: value was nil!\0";

BOL Test(const CH1* a, const CH1* b) {
  SI4 result = ::_::TStringCompare<const CH1>(a, b);
  if (!result) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  Print(kStringDifference);
  Print(result);
  return false;
}

BOL Test(const CH2* a, const CH2* b) {
  SI4 result = ::_::TStringCompare<const CH2>(a, b);
  if (!result) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print(kStringFound);
  Print(b);
  Print(kStringDifference);
  Print(result);
  return false;
}

BOL Test(const CH4* a, const CH4* b) {
  SI4 result = ::_::TStringCompare<const CH4>(a, b);
  if (!result) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print ("   ");
  PrintHex (a);
  Print(kStringFound);
  Print(b);
  Print(kStringDifference);
  Print(result);
  return false;
}

BOL Test (CH1 a, CH1 b) {
  if (a == b) return true;
  Print (kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print (kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test (CH2 a, CH2 b) {
  if (a == b) return true;
  Print (kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print (kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test (CH4 a, CH4 b) {
  if (a == b) return true;
  Print (kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print (kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test(const void* a, const void* b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  PrintHex (a);
  Print(kStringFound);
  PrintHex (b);
  return false;
}

BOL Test(UI1 a, UI1 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print(kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test(SI1 a, SI1 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print(kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test(UI2 a, UI2 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  Print(a);
  Print ("   ");
  PrintHex (a);
  Print(kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test(SI2 a, SI2 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print(kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test(UI4 a, UI4 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print(kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test(SI4 a, SI4 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print(kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test(UI8 a, UI8 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print(kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test(SI8 a, SI8 b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print(kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test(FLT a, FLT b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print(kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
  return false;
}

BOL Test(DBL a, DBL b) {
  if (a == b) return true;
  Print(kStringErrorExpecting);
  PrintHex (a);
  Print (':');
  Print (a);
  Print(kStringFound);
  PrintHex (b);
  Print (':');
  Print (b);
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

#include "global_release.inl"
