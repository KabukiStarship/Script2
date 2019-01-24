#include "ctest.h"
#include "global_footer.inl"
#define TEST_BEGIN \
  if (!::_::TestBegin(seam_log, seam_end, args)) return __FUNCTION__
#define TEST_END Print("\n\nDone testing ", __FUNCTION__)
#define PRINT(item)
#define PRINTF(format, ...)
#define PAUSE(message)
#define PAUSEF(format, ...)
#define PRINT_HEADING(message)
#define PRINT_LINE(c)
#define PRINT_TIME(date)
#define PRINT_TYPE(type, value)
#define PRINT_BYTES(begin, end_or_size)
#define PRINT_HEX(item) 
#define PRINT_HEXS(begin, end_or_size)
#define PRINT_SOCKET_TOBJ(obj)
#define PRINT_BSQ(bsq)
#define PRINT_OBJ(stack)
#define PRINT_TOBJ(stack)
#define PRINT_FUNCTION
#define PRINTLN
#define PRINT_FUNCTION_LINE
#define SOCKET_SAVE(begin, stop)
#define ASSERT_INDEX(condition, index)
#define ASSERT(condition) \
  if (!::_::Test(condition)) ::_::TestAssert(__LINE__, __FUNCTION__, __FILE__)
#define DASSERT(condition)
#define CHECK(condition)
#define DCHECK(condition)
#define RCHECK(condition) \
  if (!_::Test(condition)) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define COMPARE(a, b)
#define DCOMPARE(a, b)
#define RCOMPARE(a, b)                                 \
  if (!::_::Test(a, b)) {                             \
    ::_::Print("\n\nExpecting:");                     \
    ::_::PrintHex(a);                                 \
    ::_::Print(':');                                  \
    ::_::Print(a);                                    \
    ::_::Print("\nFound    :");                       \
    ::_::PrintHex(b);                                 \
    ::_::Print(':');                                  \
    ::_::Print(b);                                    \
    ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__) \
  }
#define AVOW(a, b)
#define DAVOW(a, b)
#define RAVOW(a, b)                                     \
  if (!::_::Test(a, b)) {                             \
    ::_::Print("\n\nExpecting:");                     \
    ::_::PrintHex(a);                                 \
    ::_::Print(':');                                  \
    ::_::Print(a);                                    \
    ::_::Print("\nFound    :");                       \
    ::_::PrintHex(b);                                 \
    ::_::Print(':');                                  \
    ::_::Print(b);                                    \
    ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__) \
  }
#define RAVOW(a, b)                                    \
  if (!::_::Test(a, b)) {                              \
    ::_::Print("\n\nExpecting:");                     \
    ::_::PrintHex(a);                                 \
    ::_::Print(':');                                  \
    ::_::Print(a);                                    \
    ::_::Print("\nFound    :");                       \
    ::_::PrintHex(b);                                 \
    ::_::Print(':');                                  \
    ::_::Print(b);                                    \
    ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__) \
  }
#define AVOW_INDEX(a, b, index)
#define RETURN(value) return;
#define DRETURN(value)
#define RRETURN(value) {\
  ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) \
return; \
}
#define RETURN_VALUE(value) return value;
#define DRETURN_VALUE(value)
#define RRETURN_VALUE(value) {\
  ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) \
return; \
}
