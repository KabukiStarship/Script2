/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Debug.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */

#include "_Undef.inl"
//
#include "Test.hpp"

#define D_THIS 1
#define A_TEST_BEGIN \
  ::_::COut cout;      \
  cout << Headingf("Testing ", __FUNCTION__, nullptr, nullptr, 80)
#define D_COUT(item) ::_::StdOut() << item
#define D_COUT_NL ::_::StdOut().NL()
#define D_LINEF(item) ::_::StdOut() << Linef(item)
#define D_PAUSE(message) ::_::Pausef(message)
#define D_COUT_ERROR(message)                           \
  ::_::StdOut() << "\nERROR: " << message << '.'); \
  ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define D_COUT_BSQ(item) ::_::TBSeqPrint<::_::COut>(StdOut(), item)
#define D_COUT_BIN(item) ::_::TBInPrint<::_::COut>(StdOut(), item)
#define D_COUT_BOut(item) ::_::TBOutPrint<::_::COut>(StdOut(), item)
#define D_COUT_OBJ(obj) obj.PrintTo<::_::COut>(StdOut())
#define D_COUT_FUNCTION ::_::COut("\n", __FUNCTION__)
#define D_COUT_FUNCTION_LINE \
  ::_::COut().NL();            \
  ::_::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__)
#define D_COUT_ARRAY(item) ::_::TArrayPrint<COut, ISZ>(StdOut(), item)
#define D_COUT_STACK(item) ::_::TStackPrint<COut, T, ISZ>(StdOut(), item)
#define D_COUT_MATRIX(item) ::_::TMatrixPrint<COut, T, ISZ>(StdOut(), item)
#define D_COUT_TABLE(item) \
  TTablePrint<::_::COut, CHT, ISZ, ISY, HSH>(StdOut(), item)
#define D_COUT_MAP(item) ::_::TMapPrint<COut, D, ISZ>(StdOut(), item)
#define D_COUT_BOOK(item) \
  ::_::TBookPrint<COut, CHT, ISZ, ISY>(StdOut(), item)
#define D_COUT_DICTIONARY(item) \
  ::_::TDicPrint<::_::COut, CHT, ISZ, ISY, HSH>(StdOut(), item)
#define D_ARRAY_SAVE(origin, end_or_size) \
  Socket socket_to_print(origin, end_or_size)
#define D_ARRAY_FILL(origin, end_or_size, c) \
  ::_::RAMFill(cursor, end_or_size, c)
#define D_ARRAY_WIPE(origin, end_or_size) ::_::RAMFill(origin, end_or_size)
#define A_CHECK(condition) \
  if (!::_::Test(condition)) ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define A_COMPARE(a, b)                            \
  if (!::_::Test(a, b)) {                            \
    ::_::TestWarn(__LINE__, __FUNCTION__, __FILE__); \
  }
#define D_ASSERT_INDEX(condition, index)                       \
  if (!::_::Test(condition)) {                                   \
    ::_::COut("\nError at index:0x").Hex(index) << ':' << index; \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__);             \
  }
#define A_ASSERT(condition) \
  if (!::_::Test(condition)) ::_::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define D_ASSERT(condition) \
  if (!::_::Test(condition)) ::_::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define R_ASSERT(condition)
#define A_AVOW(a, b)                               \
  if (!::_::Test(a, b)) {                            \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define D_AVOW(a, b)                               \
  if (!::_::Test(a, b)) {                            \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define R_AVOW(a, b)
#define R_AVOW_INDEX(a, b, index)
#define D_AVOW_INDEX(a, b, index)                  \
  if (!::_::Test(a, b)) {                            \
    ::_::COut(kSTRIndex).Print(index);               \
    ::_::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define A_AVOW_INDEX(a, b, index)                  \
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
