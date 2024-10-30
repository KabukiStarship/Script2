/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Undef.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */

#undef D_THIS
#undef A_TEST_BEGIN
#undef D_PAUSE
#undef D_COUT
#undef D_COUT_NL
#undef D_LINEF
#undef D_COUT_ERROR
#undef D_COUT_OBJ
#undef D_COUT_FUNCTION
#undef D_COUT_FUNCTION_LINE
#undef D_COUT_ARRAY
#undef D_COUT_STACK
#undef D_COUT_MATRIX
#undef D_COUT_LIST
#undef D_COUT_LOOM
#undef D_COUT_TABLE
#undef D_COUT_MAP
#undef D_COUT_BOOK
#undef D_COUT_DIC
#undef D_ARRAY_SAVE
#undef D_ARRAY_FILL
#undef D_ARRAY_WIPE
#undef D_OBJ_WIPE
#undef A_CHECK
#undef D_CHECK
#undef R_CHECK
#undef A_COMPARE
#undef D_COMPARE
#undef R_COMPARE
#undef D_ASSERT_INDEX
#undef A_ASSERT
#undef D_ASSERT
#undef R_ASSERT
#undef A_ASSERT_PTR
#undef D_ASSERT_PTR
#undef R_ASSERT_PTR
#undef A_AVOW
#undef D_AVOW
#undef R_AVOW
#undef A_AVOW_INDEX
#undef R_AVOW_INDEX
#undef D_AVOW_INDEX
#undef A_FAIL
#undef D_FAIL
#undef A_WARN
#undef D_WARN
#undef R_WARN
#undef A_RETURN
#undef D_RETURN
#undef R_RETURN
#undef D_RETURNT
#undef D_RETURN_PTR_ERROR
#undef D_RETURN_CPTR_ERROR
#undef D_RETURN_TPTR_ERROR
#undef A_RETURN_VALUE
#undef D_RETURN_VALUE
#undef R_RETURN_VALUE
#undef D_CHECK_PTR_RETURN_CODE
#undef D_CHECK_PTR_TRETURN
#undef D_CHECK_PTR_TRETURN2
#undef D_CHECK_CPTR_RETURN
#undef D_CHECK_TPTR_RETURN
#undef D_CHECK_PTR_RETURN_NIL

//@todo Delete me!
//enum
//{
//  plain = 0,
//  bold = 1,
//  italic = 2
//};
//
//void PrintString(const char* message, int size, int style)
//{
//}
//
//#define PRINT_STRING_1_ARGS(message)              PrintString(message, 0, 0)
//#define PRINT_STRING_2_ARGS(message, size)        PrintString(message, size, 0)
//#define PRINT_STRING_3_ARGS(message, size, style) PrintString(message, size, style)
//
//#define GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4
//#define PRINT_STRING_MACRO_CHOOSER(...) \
//    GET_4TH_ARG(__VA_ARGS__, PRINT_STRING_3_ARGS, \
//                PRINT_STRING_2_ARGS, PRINT_STRING_1_ARGS, )
//
//#define PRINT_STRING(...) PRINT_STRING_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
//
//int main(int argc, char* const argv[])
//{
//  PRINT_STRING("Hello, World!");
//  PRINT_STRING("Hello, World!", 18);
//  PRINT_STRING("Hello, World!", 18, bold);
//
//  return 0;
//}
