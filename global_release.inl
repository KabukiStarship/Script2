#include "global_footer.inl"
//
#include "c_test.h"

#define DEBUG_SEAM 0
#define TEST_BEGIN \
  if (!::_::TestBegin(seam_log, seam_end, args)) return __FUNCTION__
#define PRINT(item)
#define PRINTF(format, ...)
#define PAUSE(message)
#define PAUSEF(format, ...)
#define PRINTNL
#define PRINT_ERROR(message)
#define PRINT_LINEF(style)
#define PRINT_LINEF_COUNT(style, count)
#define PRINT_HEADING(message)
#define PRINT_HEADING_COUNT(message)
#define PRINT_HEADINGF(caption, style, column_count)
#define PRINT_HEADINGF_COUNT(caption, style, column_count)
#define PRINT_HEADINGF_2(caption, style, column_count, caption2)
#define PRINT_HEADINGF_3(caption, style, column_count, caption2, caption3)
#define PRINT_TIME(date)
#define PRINT_TYPE(type, value)
#define PRINT_CHARS(begin, end_or_size)
#define PRINT_HEX(item)
#define PRINT_HEXS(begin, end_or_size)
#define PRINT_SOCKET_OBJ(obj)
#define PRINT_BSQ(bsq)
#define PRINT_OBJ(stack)
#define PRINT_FUNCTION
#define PRINTLN
#define PRINT_FUNCTION_LINE
#define SOCKET_SAVE(begin, stop)
#define SOCKET_FILL(begin, end_or_size, c)
#define SOCKET_WIPE(begin, end_or_size)
#define ASSERT_INDEX(condition, index)
#define ASSERT(condition) \
  if (!::_::Test(condition)) ::_::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define DASSERT(condition)
#define CHECK(condition)
#define DCHECK(condition)
#define RCHECK(condition) \
  if (!::_::Test(condition)) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define COMPARE(a, b)
#define DCOMPARE(a, b)
#define RCOMPARE(a, b)                              \
  if (!::_::Test(a, b)) {                           \
    ::_::Print("\n\nExpecting:");                   \
    ::_::PrintHex(a);                               \
    ::_::Print(':');                                \
    ::_::Print(a);                                  \
    ::_::Print("\nFound    :");                     \
    ::_::PrintHex(b);                               \
    ::_::Print(':');                                \
    ::_::Print(b);                                  \
    ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__) \
  }
#define AVOW(a, b)
#define DAVOW(a, b)
#define RAVOW(a, b)                                 \
  if (!::_::Test(a, b)) {                           \
    ::_::Print("\n\nExpecting:");                   \
    ::_::PrintHex(a);                               \
    ::_::Print(':');                                \
    ::_::Print(a);                                  \
    ::_::Print("\nFound    :");                     \
    ::_::PrintHex(b);                               \
    ::_::Print(':');                                \
    ::_::Print(b);                                  \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__) \
  }
#define RAVOW(a, b)                                 \
  if (!::_::Test(a, b)) {                           \
    ::_::Print("\n\nExpecting:");                   \
    ::_::PrintHex(a);                               \
    ::_::Print(':');                                \
    ::_::Print(a);                                  \
    ::_::Print("\nFound    :");                     \
    ::_::PrintHex(b);                               \
    ::_::Print(':');                                \
    ::_::Print(b);                                  \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__) \
  }
#define AVOW_INDEX(a, b, index)
#define WARN(condition) \
  if (!condition) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define DWARN(condition)
#define RWARN(condition) \
  if (!condition) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define RETURN(value) return;
#define DRETURN(value)
#define RRETURN(value) \
  { ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return; }
#define RETURN_VALUE(value) return value;
#define DRETURN_VALUE(value)
#define RRETURN_VALUE(value) \
  { ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return; }
