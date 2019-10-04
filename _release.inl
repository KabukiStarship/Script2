/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_release.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include "_undef.inl"
//
#include "test.hpp"

#define D_THIS 0
#define A_TEST_BEGIN
#define D_PAUSE(message)
#define D_COUT(item)
#define D_COUT_NL
#define D_COUT_ERROR(message)
#define D_COUT_OBJ(stack)
#define D_COUT_FUNCTION
#define D_COUT_FUNCTION_LINE
#define D_COUT_ARRAY(item)
#define D_COUT_STACK(item)
#define D_COUT_MATRIX(item)
#define D_COUT_TABLE(item)
#define D_COUT_MAP(item)
#define D_COUT_BOOK(item)
#define D_COUT_DICTIONARY(item)
#define D_ARRAY_SAVE(origin, stop)
#define D_ARRAY_FILL(origin, end_or_size, c)
#define D_ARRAY_WIPE(origin, end_or_size)
#define D_ASSERT_INDEX(condition, index)
#define A_ASSERT(condition) \
  if (!_::Test(condition)) _::TestFail(__LINE__, __FUNCTION__, __FILE__)
#define D_ASSERT(condition)
#define A_CHECK(condition)
#define D_CHECK(condition)
#define R_CHECK(condition) \
  if (!_::Test(condition)) _::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define A_COMPARE(a, b)
#define D_COMPARE(a, b)
#define R_COMPARE(a, b)                           \
  if (!_::Test(a, b)) {                           \
    _::TestWarn(__LINE__, __FUNCTION__, __FILE__) \
  }
#define A_AVOW(a, b)                               \
  if (!_::Test(a, b)) {                            \
    _::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define D_AVOW(a, b)
#define R_AVOW(a, b)                              \
  if (!_::Test(a, b)) {                           \
    _::TestFail(__LINE__, __FUNCTION__, __FILE__) \
  }
#define R_AVOW(a, b)                              \
  if (!_::Test(a, b)) {                           \
    _::TestFail(__LINE__, __FUNCTION__, __FILE__) \
  }
#define A_AVOW_INDEX(a, b, index)                  \
  if (!_::Test(a, b)) {                            \
    _::COut("\n           Index:").Print(index);   \
    _::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define R_AVOW_INDEX(a, b, index)                  \
  if (!_::Test(a, b)) {                            \
    _::COut("\n           Index:").Print(index);   \
    _::TestFail(__LINE__, __FUNCTION__, __FILE__); \
  }
#define D_AVOW_INDEX(a, b, index)
#define A_WARN(condition) \
  if (!condition) _::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define D_WARN(condition)
#define R_WARN(condition) \
  if (!condition) _::TestWarn(__LINE__, __FUNCTION__, __FILE__)
#define A_RETURN(value) return;
#define D_RETURN(value)
#define R_RETURN(value) \
  { _::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return; }
#define A_RETURN_VALUE(value) return value;
#define D_RETURN_VALUE(value)
#define R_RETURN_VALUE(value) \
  { _::TestFunctionLine(__LINE__, __FUNCTION__, __FILE__) return; }
