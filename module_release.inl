#include "module_footer.inl"
//
#include "t_test.h"

#define DEBUG_THIS 0
#define A_TEST_BEGIN
#define COUT_COUT
#define COUT(item)
#define D_COUT(item)
#define D_COUT_2(a, b)
#define D_COUT_3(a, b, c)
#define D_COUT_4(a, b, c, d)
#define D_COUT_5(a, b, c, d, e)
#define D_COUT_6(a, b, c, d, e, f)
#define D_COUT_7(a, b, c, d, e, f, g)
#define D_COUT_8(a, b, c, d, e, f, g, h)
#define D_PRINTF(format, ...)
#define D_PAUSE(message)
#define D_PAUSEF(format, ...)
#define D_COUT_NL
#define D_COUT_ERROR(message)
#define D_COUT_LINE
#define D_COUT_LINEF(style)
#define D_COUT_LINEF_COUNT(style, count)
#define D_COUT_HEADING(message)
#define D_COUT_HEADING_COUNT(message)
#define D_COUT_HEADINGF(caption, style, column_count)
#define D_COUT_HEADINGF_COUNT(caption, style, column_count)
#define D_COUT_HEADINGF_2(caption, style, column_count, caption2)
#define D_COUT_HEADINGF_3(caption, style, column_count, caption2, caption3)
#define D_COUT_TIME(date)
#define D_COUT_TYPE(type, value)
#define D_COUT_CHARS(begin, end_or_size)
#define D_COUT_HEX(item)
#define D_COUT_HEXF(begin, end_or_size)
#define D_COUT_SOCKET_OBJ(obj)
#define D_COUT_BSQ(bsq)
#define D_COUT_OBJ(stack)
#define D_COUT_FUNCTION
#define D_COUT_FUNCTION_LINE
#define D_SOCKET_SAVE(begin, stop)
#define D_SOCKET_FILL(begin, end_or_size, c)
#define D_SOCKET_WIPE(begin, end_or_size)
#define D_ASSERT_INDEX(condition, index)
#define A_ASSERT(condition) \
  if (!::_::Test(condition)) ::_::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define D_ASSERT(condition)
#define A_CHECK(condition)
#define DCHECK(condition)
#define RCHECK(condition) \
  if (!::_::Test(condition)) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define A_COMPARE(a, b)
#define D_COMPARE(a, b)
#define R_COMPARE(a, b)                             \
  if (!::_::Test(a, b)) {                           \
    ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__) \
  }
#define A_AVOW(a, b)                                 \
  if (!::_::Test(a, b)) {                            \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define D_AVOW(a, b)
#define R_AVOW(a, b)                                \
  if (!::_::Test(a, b)) {                           \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__) \
  }
#define R_AVOW(a, b)                                \
  if (!::_::Test(a, b)) {                           \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__) \
  }
#define A_AVOW_INDEX(a, b, index)                    \
  if (!::_::Test(a, b)) {                            \
    ::_::COut("\n           Index:").Print(index);   \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define R_AVOW_INDEX(a, b, index)                    \
  if (!::_::Test(a, b)) {                            \
    ::_::COut("\n           Index:").Print(index);   \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define D_AVOW_INDEX(a, b, index)
#define A_WARN(condition) \
  if (!condition) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define D_WARN(condition)
#define R_WARN(condition) \
  if (!condition) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define A_RETURN(value) return;
#define D_RETURN(value)
#define R_RETURN(value) \
  { ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return; }
#define A_RETURN_VALUE(value) return value;
#define D_RETURN_VALUE(value)
#define R_RETURN_VALUE(value) \
  { ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return; }
#define D_COUT_FACTORY_FUNCTION(obj, function, using_heap)
