#include "ttest.h"
#include "test_footer.inl"

#define TEST_BEGIN \
  if (!::_::TestBegin(seam_log, seam_end, args)) return __FUNCTION__
#define TEST_END Print("\n\nDone testing ", __FUNCTION__)
#define PRINT(item) ::_::Print(item)
#define PRINT_TIME(t) ::_::PrintTime(t)
#define PRINTF(format, ...) ::_::Printf(format, __VA_ARGS__)
#define PAUSE(message) ::_::Pause(message)
#define PAUSEF(format, ...) ::_::Pausef(format, __VA_ARGS__)
#define PRINT_HEADING(message) ::_::PrintHeading(message, 5)
#define PRINT_LINE(c) ::_::PrintLine(c)
#define PRINT_TYPE(type, value) Console<>().Out() << TypeValue(type, value)
#define PRINT_SOCKET(begin, end_or_size) PrintSocket(begin, end_or_size)
#define PRINT_SOCKET_OBJ(obj) PrintSocket(obj.Begin (), obj.SizeBytes ())
#define PRINT_BSQ(bsq) Console<>().Out() << header << '\n' << Bsq(bsq)
#define PRINT_OBJ(stack) stack->Print()
#define PRINT_TOBJ(stack) stack.Print()
#define PRINT_FUNCTION ::_::Print("\n", __FUNCTION__)
#define PRINTLN ::_::Print('\n')
#define PRINT_FUNCTION_LINE ::_::Print('\n'); \
  ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__)
#define SOCKET_SAVE(cursor, end_a) Socket socket_to_print(cursor, end_a)
#define CHECK(condition) \
  if (!_::Test(condition)) ::_::AssertWarn(__LINE__, __FUNCTION__, __FILE__)
#define COMPARE(a, b)                                 \
  if (!::_::Test(a, b)) {                             \
    ::_::Print("\n\nExpecting:");                     \
    ::_::Print(a);                                    \
    ::_::Print("\nFound    :");                       \
    ::_::Print(b);                                    \
    ::_::AssertWarn(__LINE__, __FUNCTION__, __FILE__) \
  }
#define ASSERT(condition) \
  if (!_::Test(condition)) ::_::TestAssert(__LINE__, __FUNCTION__, __FILE__)
#define DASSERT(condition) \
  if (!_::Test(condition)) ::_::TestAssert(__LINE__, __FUNCTION__, __FILE__)
#define RASSERT(condition)
#define AVOW(a, b)                                     \
  if (!::_::Test(a, b)) {                              \
    ::_::Print("\n\nExpecting:");                      \
    ::_::Print(a);                                     \
    ::_::Print("\nFound    :");                        \
    ::_::Print(b);                                     \
    ::_::TestAssert(__LINE__, __FUNCTION__, __FILE__); \
  }
#define DAVOW(a, b)                                    \
  if (!::_::Test(a, b)) {                              \
    ::_::Print("\n\nExpecting:");                      \
    ::_::Print(a);                                     \
    ::_::Print("\nFound    :");                        \
    ::_::Print(b);                                     \
    ::_::TestAssert(__LINE__, __FUNCTION__, __FILE__); \
  }
#define RAVOW(a, b) 
