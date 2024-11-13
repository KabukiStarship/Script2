// Copyright Kabuki Starship� <kabukistarship.com>.
#include "_Undef.hxx"
//
#include "Test.hpp"
//
#define D_THIS 0
#define A_TEST_BEGIN
#define D_PAUSE(message)
#define D_COUT(item)
#define D_COUT_NL
#define D_LINEF(item)
#define D_COUT_ERROR(message)
#define D_COUT_OBJ(stack)
#define D_COUT_FUNCTION
#define D_COUT_FUNCTION_LINE
#define D_COUT_ARRAY(item)
#define D_COUT_STACK(item)
#define D_COUT_LIST(item)
#define D_COUT_LOOM(item)
#define D_COUT_MAP(item)
#define D_COUT_BOOK(item)
#define D_COUT_DIC(item)
#define D_COUT_TABLE(item)
#define D_COUT_MATRIX(item)
#define D_ARRAY_SAVE(origin, stop)
#define D_ARRAY_FILL(origin, end_or_size, c)
#define D_ARRAY_WIPE(origin, end_or_size)
#define D_OBJ_WIPE(origin) 
#define D_ASSERT_INDEX(condition, index)
#define A_ASSERT(condition) \
  if (!::_::Test(condition)) ::_::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define D_ASSERT(condition)
#define A_ASSERT_PTR(ptr)                            \
  if (IUW(ptr) < CrabsErrorCount)  \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define D_ASSERT_PTR(ptr)
#define R_ASSERT_PTR(ptr)                            \
  if (IUW(ptr) < CrabsErrorCount)  \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define A_FAIL() ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define R_FAIL() ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define D_FAIL()
#define A_CHECK(condition)
#define D_CHECK(condition)
#define R_CHECK(condition) \
  if (!::_::Test(condition)) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define A_COMPARE(a, b)
#define D_COMPARE(a, b)
#define R_COMPARE(a, b)                           \
  if (!::_::Test(a, b)) {                           \
    ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__) \
  }
#define A_AVOW(a, b)                               \
  if (!::_::Test(a, b)) {                            \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define D_AVOW(a, b)
#define R_AVOW(a, b)                              \
  if (!::_::Test(a, b)) {                           \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__) \
  }
#define R_AVOW(a, b)                              \
  if (!::_::Test(a, b)) {                           \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__) \
  }
#define A_AVOW_INDEX(a, b, index)                  \
  if (!::_::Test(a, b)) {                            \
    ::_::COut("\n           Index:").Print(index);   \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define R_AVOW_INDEX(a, b, index)                  \
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
#define D_RETURNT(type, error) return type(error)
#define D_RETURN_CPTR_ERROR(type, error) return const_cast<type*>(IUW(error))
#define D_RETURN_TPTR_ERROR(type, error) return reinterpret_cast<type*>(IUW(error))
#define A_RETURN_VALUE(value) return value;
#define D_RETURN_VALUE(value)
#define R_RETURN_VALUE(value) \
  { ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return; }
#define D_CHECK_PTR_RETURN_CODE(ptr, error_code)\
  if (IUW(ptr) < IUW(CrabsErrorCount))\
    return error_code;
#define D_CHECK_PTR_RETURN(ptr)\
  if (IUW(ptr) < IUW(CrabsErrorCount))\
    return ptr;
#define D_CHECK_CPTR_RETURN(type, ptr)\
  if (IUW(ptr) < IUW(CrabsErrorCount))\
    return const_cast<type*>(ptr);
#define D_CHECK_TPTR_RETURN(type, ptr)\
  if (IUW(ptr) < IUW(CrabsErrorCount))\
    return reinterpret_cast<type*>(ptr);
#define D_CHECK_PTR_TRETURN(type, ptr)\
  if (IUW(ptr) < IUW(CrabsErrorCount))\
    return type(IUW(ptr));
#define D_CHECK_PTR_TRETURN2(type, ptr1, ptr2)\
  if (IUW(ptr1) < IUW(CrabsErrorCount))\
    return type(IUW(ptr1));\
  if (IUW(ptr2) < IUW(CrabsErrorCount))\
    return type(IUW(ptr2));
#define D_CHECK_PTR_RETURN_NIL(ptr)\
  if (IUW(ptr) < IUW(CrabsErrorCount)) return;
