// Copyright Kabuki Starship <kabukistarship.com>.
#include "Test.h"
#include "COut.h"
#include "Stringf.hpp"
namespace _ {

void TestFunctionLine(ISN line, const CHA* function, const CHA* file) {
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut("\n        Function:").Print(function) <<
       "\n            Line:" << line << " in \"" << file << '\"';
#endif
}

BOL TestWarn(ISN line, const CHA* function, const CHA* file) {
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut("\n\nWARNING Function:").Print(function) << " at line:" << line <<
       "\n       " << " in \"" << file << '\"';
#endif
  return true;
}

BOL TestWarnFail(ISN line, const CHA* function, const CHA* file) {
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut("\n\nFAILURE Function:").Print(function) << " at line:" << line <<
    "\n       " << " in \"" << file << '\"';
#endif
  return true;
}

BOL TestFail(ISN line, const CHA* function, const CHA* file) {
  BOL result = TestWarnFail(line, function, file);
  // Insert break-point here.
  return result;
}

const CHA* ArgsToString(ISN arg_count, CHA** args) {
  if (!args || arg_count <= 1) return "";
  if (arg_count == 2) return args[1];
  CHA *origin = args[1], *stop = args[arg_count - 1] - 1;
  while (stop > origin) {
    CHA c = *stop;
    if (!c) *stop = ' ';
    --stop;
  }
  return origin;
}

const CHA* TestTree(const CHA* args, TestCase* tests, ISN count) {
  if (!tests) return nullptr;
  for (ISN i = 0; i < count; ++i) {
    TestCase test = tests[i];
    if (!test) {
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
      COut("\nError: seam node ").Print(i) << " is missing!";
#endif
      return "";
    }
    const CHA* error = test(args);
    if (error) return error;
  }
  return nullptr;
}

ISN SeamResult(const CHA* result) {
  if (result) {
    #if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
    COut("\n\nError in seam ").Print(result);
    #endif
    return APP_EXIT_FAILURE;
  }
  #if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut("\n\nUnit tests completed successfully! (:-)+==<\n");
  #endif
  return APP_EXIT_SUCCESS;
}

ISN SeamTreeTest(ISN arg_count, CHA** args, TestCase* tests, ISN test_count) {
  return SeamResult(TestTree(ArgsToString(arg_count, args), tests, test_count));
}

BOL Test(BOL condition) { return condition; }

static const CHA STRErrorExpecting[] = "\n\nERROR: Expecting:0x\0";
static const CHA STRFound[] = "\n           Found:0x\0";
//static const CHA STRErrorNil[] = "\nERROR: value was nil!\0";

BOL Test(const CHA* a, const CHA* b) {
  ISN difference = TSTRCompare<CHA>(a, b);
  if (!difference) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut("\n\nERROR: Expecting:\"").Print(a)
      << "\"\n           Found:\"" << b << "\"\n      Difference:\0"
      << difference;
#endif
  return false;
}

#if USING_UTF16 == YES_0
BOL Test(const CHB* a, const CHB* b) {
  ISN difference = TSTRCompare<CHB>(a, b);
  if (!difference) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut("\n\nERROR: Expecting:\"").Print(a)
      << "\"\n           Found:\"" << b << "\"\n      Difference:\0"
      << difference;
#endif
  return false;
}
#endif
#if USING_UTF32 == YES_0
BOL Test(const CHC* a, const CHC* b) {
  ISN difference = TSTRCompare<CHC>(a, b);
  if (!difference) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut("\n\nERROR: Expecting:\"").Print(a)
      << "\"\n           Found:\"" << b << "\"\n      Difference:\0"
      << difference;
#endif
  return false;
}
#endif
BOL Test(CHA a, CHA b) {
  if (a == b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL Test(CHB a, CHB b) {
  if (a == b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL Test(CHC a, CHC b) {
  if (a == b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL Test(const void* a, const void* b) {
  if (a == b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a) << STRFound << Hexf(b);
#endif
  return false;
}

BOL Test(IUA a, IUA b) {
  if (a == b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL Test(ISA a, ISA b) {
  if (a == b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL Test(IUB a, IUB b) {
  if (a == b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL Test(ISB a, ISB b) {
  if (a == b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL Test(IUC a, IUC b) {
  if (a == b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL Test(ISC a, ISC b) {
  if (a == b) return true;

#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL Test(IUD a, IUD b) {
  if (a == b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL Test(ISD a, ISD b) {
  if (a == b) return true;

#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

#if USING_FPC == YES_0
BOL Test(FPC a, FPC b) {
  if (a == b) return true;
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
  return false;
}
#endif
#if USING_FPD == YES_0
BOL Test(FPD a, FPD b) {
  if (a == b) return true;
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
  return false;
}
#endif



BOL TestNot(const CHA* a, const CHA* b) {
  ISN difference = !TSTRCompare<CHA>(a, b);
  if (!difference) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut("\n\nERROR: Expecting:\"").Print(a)
      << "\"\n           Found:\"" << b << "\"\n      Difference:\0"
      << difference;
#endif
  return false;
}

#if USING_UTF16 == YES_0
BOL TestNot(const CHB* a, const CHB* b) {
  ISN difference = !TSTRCompare<CHB>(a, b);
  if (!difference) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut("\n\nERROR: Expecting:\"").Print(a)
      << "\"\n           Found:\"" << b << "\"\n      Difference:\0"
      << difference;
#endif
  return false;
}
#endif
#if USING_UTF32 == YES_0
BOL TestNot(const CHC* a, const CHC* b) {
  ISN difference = TSTRCompare<CHC>(a, b);
  if (!difference) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut("\n\nERROR: Expecting:\"").Print(a)
      << "\"\n           Found:\"" << b << "\"\n      Difference:\0"
      << difference;
#endif
  return false;
}
#endif
BOL TestNot(CHA a, CHA b) {
  if (a != b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL TestNot(CHB a, CHB b) {
  if (a != b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL TestNot(CHC a, CHC b) {
  if (a != b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL TestNot(const void* a, const void* b) {
  if (a != b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a) << STRFound << Hexf(b);
#endif
  return false;
}

BOL TestNot(IUA a, IUA b) {
  if (a != b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL TestNot(ISA a, ISA b) {
  if (a != b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL TestNot(IUB a, IUB b) {
  if (a != b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL TestNot(ISB a, ISB b) {
  if (a != b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL TestNot(IUC a, IUC b) {
  if (a != b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL TestNot(ISC a, ISC b) {
  if (a != b) return true;

#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL TestNot(IUD a, IUD b) {
  if (a != b) return true;
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

BOL TestNot(ISD a, ISD b) {
  if (a != b) return true;

#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
#endif
  return false;
}

#if USING_FPC == YES_0
BOL TestNot(FPC a, FPC b) {
  if (a != b) return true;
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
  return false;
}
#endif
#if USING_FPD == YES_0
BOL TestNot(FPD a, FPD b) {
  if (a != b) return true;
  COut(STRErrorExpecting).Hex(a)
      << ':' << a << STRFound << Hexf(b) << ':' << b;
  return false;
}
#endif

BOL Test(const void* value) { return value != nullptr; }

BOL Test(IUA value) { return value != 0; }

BOL Test(ISA value) { return value != 0; }

BOL Test(IUB value) { return value != 0; }

BOL Test(ISB value) { return value != 0; }

BOL Test(IUC value) { return value != 0; }

BOL Test(ISC value) { return value != 0; }

BOL Test(IUD value) { return value != 0; }

BOL Test(ISD value) { return value != 0; }

BOL Test(FPC value) { return value != 0; }

BOL Test(FPD value) { return value != 0; }

}  //< namespace _
