/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /test.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>

#include "test.h"
//
#include "cout.h"
#include "stringf.hpp"

namespace _ {

void TestFunctionLine(SIN line, const CH1* function, const CH1* file) {
  static const CH1 kStrandIndex[] = "\0";
  COut("\n        Function:").Print(function)
      << "\n            Line:" << line << " in \"" << file << '\"';
}

BOL TestWarn(SIN line, const CH1* function, const CH1* file) {
  TestFunctionLine(line, function, file);
  return true;
}

BOL TestFail(SIN line, const CH1* function, const CH1* file) {
  BOL result = TestWarn(line, function, file);
  return result;
}

const CH1* ArgsToString(SIN arg_count, CH1** args) {
  if (!args || arg_count <= 1) return "";
  if (arg_count == 2) return args[1];
  CH1 *origin = args[1], *stop = args[arg_count - 1] - 1;
  while (stop > origin) {
    CH1 c = *stop;
    if (!c) *stop = ' ';
    --stop;
  }
  return origin;
}

const CH1* TestTree(const CH1* args, TestCase* tests, SIN count) {
  if (!tests) return nullptr;
  for (SIN i = 0; i < count; ++i) {
    TestCase test = tests[i];
    if (!test) {
      COut("\nError: seam node ").Print(i) << " is missing!";
      return "";
    }
    const CH1* error = test(args);
    if (error) return error;
  }
  return nullptr;
}

SIN SeamResult(const CH1* result) {
  if (result) {
    COut("\n\nError in seam ").Print(result);
    return APP_EXIT_FAILURE;
  }
  COut("\n\nUnit tests completed successfully! (:-)+==<\n");
  return APP_EXIT_SUCCESS;
}

SIN SeamTreeTest(SIN arg_count, CH1** args, TestCase* tests, SIN test_count) {
  return SeamResult(TestTree(ArgsToString(arg_count, args), tests, test_count));
}

BOL Test(BOL condition) { return condition; }

static const CH1 kSTRErrorExpecting[] = "\n\nERROR: Expecting:0x\0";
static const CH1 kSTRFound[] = "\n           Found:0x\0";
static const CH1 kSTRErrorNil[] = "\nERROR: value was nil!\0";

BOL Test(const CH1* a, const CH1* b) {
  SIN difference = TSTRCompare<CH1>(a, b);
  if (!difference) return true;
  COut("\n\nERROR: Expecting:\"").Print(a)
      << "\"\n           Found:\"" << b << "\"\n      Difference:\0"
      << difference;
  return false;
}

#if USING_UTF16 == YES_0
BOL Test(const CH2* a, const CH2* b) {
  SIN difference = TSTRCompare<CH2>(a, b);
  if (!difference) return true;
  COut("\n\nERROR: Expecting:\"").Print(a)
      << "\"\n           Found:\"" << b << "\"\n      Difference:\0"
      << difference;
  return false;
}
#endif
#if USING_UTF32 == YES_0
BOL Test(const CH4* a, const CH4* b) {
  SIN difference = TSTRCompare<CH4>(a, b);
  if (!difference) return true;
  COut("\n\nERROR: Expecting:\"").Print(a)
      << "\"\n           Found:\"" << b << "\"\n      Difference:\0"
      << difference;
  return false;
}
#endif
BOL Test(CH1 a, CH1 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}

BOL Test(CH2 a, CH2 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}

BOL Test(CH4 a, CH4 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}

BOL Test(const void* a, const void* b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a) << kSTRFound << Hexf(b);
  return false;
}

BOL Test(UI1 a, UI1 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}

BOL Test(SI1 a, SI1 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}

BOL Test(UI2 a, UI2 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}

BOL Test(SI2 a, SI2 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}

BOL Test(UI4 a, UI4 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}

BOL Test(SI4 a, SI4 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}

BOL Test(UI8 a, UI8 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}

BOL Test(SI8 a, SI8 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}

#if USING_FP4 == YES_0
BOL Test(FP4 a, FP4 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}
#endif
#if USING_FP8 == YES_0
BOL Test(FP8 a, FP8 b) {
  if (a == b) return true;
  COut(kSTRErrorExpecting).Hex(a)
      << ':' << a << kSTRFound << Hexf(b) << ':' << b;
  return false;
}
#endif

BOL Test(const void* value) { return value != nullptr; }

BOL Test(UI1 value) { return value != 0; }

BOL Test(SI1 value) { return value != 0; }

BOL Test(UI2 value) { return value != 0; }

BOL Test(SI2 value) { return value != 0; }

BOL Test(UI4 value) { return value != 0; }

BOL Test(SI4 value) { return value != 0; }

BOL Test(UI8 value) { return value != 0; }

BOL Test(SI8 value) { return value != 0; }

BOL Test(FP4 value) { return value != 0; }

BOL Test(FP8 value) { return value != 0; }

}  // namespace _
