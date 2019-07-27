#include "module_footer.inl"
//
#include "t_test.h"

#define D_THIS 1
#define A_TEST_BEGIN \
  _::CPrint().Star() << Headingf("Testing ", nullptr, 80, __FUNCTION__)
#define D_COUT(item) _::CPrint().Star() << item
#define D_COUT_NL _::CPrint().Star().NL()
#define D_PAUSE(message) _::Pausef(message)
#define D_COUT_ERROR(message)                           \
  _::CPrint().Star() << "\nERROR: " << message << '.'); \
  _::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define D_COUT_BSQ(bsq) _::COut(header) << kLF << Bsq(bsq)
#define D_COUT_OBJ(obj) obj.CPrint()
#define D_COUT_FUNCTION _::COut("\n", __FUNCTION__)
#define D_COUT_FUNCTION_LINE \
  _::COut().NL();            \
  _::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__)
#define D_SOCKET_SAVE(cursor, end_a) SBuf socket_to_print(cursor, end_a)
#define D_SOCKET_FILL(begin, end_or_size, c) \
  _::SocketFill(cursor, end_or_size, c)
#define D_SOCKET_WIPE(begin, end_or_size) _::SocketWipe(begin, end_or_size)
#define A_CHECK(condition) \
  if (!_::Test(condition)) _::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define A_COMPARE(a, b)                            \
  if (!_::Test(a, b)) {                            \
    _::TestWarn(__LINE__, __FUNCTION__, __FILE__); \
  }
#define D_ASSERT_INDEX(condition, index)                       \
  if (!_::Test(condition)) {                                   \
    _::COut("\nError at index:0x").Hex(index) << ':' << index; \
    _::TestFail(__LINE__, __FUNCTION__, __FILE__);             \
  }
#define A_ASSERT(condition) \
  if (!_::Test(condition)) _::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define D_ASSERT(condition) \
  if (!_::Test(condition)) _::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define R_ASSERT(condition)
#define A_AVOW(a, b)                               \
  if (!_::Test(a, b)) {                            \
    _::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define D_AVOW(a, b)                               \
  if (!_::Test(a, b)) {                            \
    _::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define R_AVOW(a, b)
#define R_AVOW_INDEX(a, b, index)
#define D_AVOW_INDEX(a, b, index)                  \
  if (!_::Test(a, b)) {                            \
    _::COut(kSTRIndex).Print(index);               \
    _::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define A_AVOW_INDEX(a, b, index)                  \
  if (!_::Test(a, b)) {                            \
    _::COut("\n           Index:").Print(index);   \
    _::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define A_WARN(condition) \
  if (!condition) _::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define D_WARN(condition) \
  if (!condition) _::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define R_WARN(condition)
#define A_RETURN \
  { _::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return; }
#define D_RETURN \
  { _::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return; }
#define R_RETURN(value)
#define A_RETURN_VALUE(value) \
  { _::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return value; }
#define D_RETURN_VALUE(value) \
  { _::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return value; }
#define R_RETURN_VALUE(value)
