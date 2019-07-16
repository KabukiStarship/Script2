#include "c_test.h"
//
#include "module_footer.inl"

#define DEBUG_THIS 1
#define A_TEST_BEGIN \
  if (!args) return __FUNCTION__
#define A_TEST_END Print("\n\nDone testing ", __FUNCTION__)
#define DECLARE_COUT COut CPrint()
#define COUT(item) ::_::CPrint() << item
#define COUT_2(a, b) ::_::CPrint() << a << b
#define COUT_3(a, b, c) ::_::CPrint() << a << b << c
#define COUT_4(a, b, c, d) ::_::CPrint() << a << b << c << d
#define D_COUT_NL ::_::CPrint().NL()
#define D_COUT(item) ::_::CPrint() << item
#define D_COUT_2(a, b) ::_::CPrint() << a << b
#define D_COUT_3(a, b, c) ::_::CPrint() << a << b << c
#define D_COUT_4(a, b, c, d) ::_::CPrint() << a << b << c << d
#define D_COUT_5(a, b, c, d, e) ::_::CPrint() << a << b << c << d << e
#define D_COUT_6(a, b, c, d, e, f) ::_::CPrint() << a << b << c << d << e << f
#define D_COUT_7(a, b, c, d, e, f, g) \
  ::_::CPrint() << a << b << c << d << e << f << g
#define D_COUT_8(a, b, c, d, e, f, g, h) \
  ::_::CPrint() << a << b << c << d << e << f << g << h
#define D_PRINTF(format, ...) ::_::Printf(format, __VA_ARGS__)
#define D_PAUSE(message) ::_::Pausef(message)
#define D_PAUSEF(format, ...) ::_::Pausef(format, __VA_ARGS__)
#define D_COUT_ERROR(message)           \
  ::_::Printf("\nERROR: %s.", message); \
  ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define D_COUT_LINE ::_::PrintLinef()
#define D_COUT_LINEF(style) ::_::CPrint() << Linef(style)
#define D_COUT_LINEF_COUNT(style, count) ::_::CPrint() << Linef(style, count)
#define D_COUT_HEADING(caption) ::_::COut() << Headingf(caption)
#define D_COUT_HEADINGF(caption, style) ::_::COut(Headingf(caption, style))
#define D_COUT_HEADINGF_COUNT(caption, style, column_count) \
  ::_::COut(Headingf(caption, style, column_count))
#define D_COUT_HEADINGF_2(caption, style, column_count, caption2) \
  ::_::COut(Headingf(caption, style, column_count, caption2))
#define D_COUT_HEADINGF_3(caption, style, column_count, caption2, caption3) \
  ::_::COut(Headingf(caption, style, column_count, caption2, caption3))
#define D_COUT_TYPE(type, value) ::_::CPrint() << AValue(type, value)
#define D_COUT_CHARS(begin, end_or_size) \
  ::_::CPrint() << Charsf(begin, end_or_size)
#define D_COUT_HEX(item) ::_::COut().Hex(item)
#define D_COUT_HEXF(begin, end_or_size) ::_::COut().Hex(begin, end_or_size)
#define D_COUT_SOCKET_OBJ(obj) \
  ::_::CPrint() << Charsf(obj.Auto().Begin(), obj.Size())
#define D_COUT_BSQ(bsq) ::_::COut(header) << kLF << Bsq(bsq)
#define D_COUT_OBJ(obj) obj.COut()
#define D_COUT_FUNCTION ::_::COut("\n", __FUNCTION__)
#define D_COUT_FUNCTION_LINE \
  ::_::COut().NL();          \
  ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__)
#define D_COUT_FACTORY_FUNCTION(obj, function, using_heap)                     \
  if (function >= 0 && function < kFactoryName)                                \
    Printf("\nEntering %s.Factory.%s.%s:", obj, using_heap ? "Heap" : "Stack", \
           AsciiFactoryFunction(function));
#define D_SOCKET_SAVE(cursor, end_a) Socket socket_to_print(cursor, end_a)
#define D_SOCKET_FILL(begin, end_or_size, c) \
  ::_::SocketFill(cursor, end_or_size, c)
#define D_SOCKET_WIPE(begin, end_or_size) ::_::SocketWipe(begin, end_or_size)
#define A_CHECK(condition) \
  if (!::_::Test(condition)) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define A_COMPARE(a, b)                              \
  if (!::_::Test(a, b)) {                            \
    ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__); \
  }
#define D_ASSERT_INDEX(condition, index)                              \
  if (!::_::Test(condition)) {                                        \
    ::_::Printf("\nError at index:0x%x:%i!", (SI4)index, (SI4)index); \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__);                  \
  }
#define A_ASSERT(condition) \
  if (!::_::Test(condition)) ::_::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define D_ASSERT(condition) \
  if (!::_::Test(condition)) ::_::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define R_ASSERT(condition)
#define A_AVOW(a, b)                                 \
  if (!::_::Test(a, b)) {                            \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define D_AVOW(a, b)                                 \
  if (!::_::Test(a, b)) {                            \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define R_AVOW(a, b)
#define R_AVOW_INDEX(a, b, index)
#define D_AVOW_INDEX(a, b, index)                    \
  if (!::_::Test(a, b)) {                            \
    ::_::COut(kSTRIndex).Print(index);               \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define A_AVOW_INDEX(a, b, index)                    \
  if (!::_::Test(a, b)) {                            \
    ::_::COut("\n           Index:").Print(index);   \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define A_WARN(condition) \
  if (!condition) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define D_WARN(condition) \
  if (!condition) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define R_WARN(condition)
#define A_RETURN \
  { ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return; }
#define D_RETURN \
  { ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return; }
#define R_RETURN(value)
#define A_RETURN_VALUE(value) \
  { ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return value; }
#define D_RETURN_VALUE(value) \
  { ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return value; }
#define R_RETURN_VALUE(value)
