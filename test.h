/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /test.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2015-9 Cale McCollough <calemccollough.github.io>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#ifndef SCRIPT2_C_TEST
#define SCRIPT2_C_TEST 1

/* Function pointer prototype for a test case with command line argument
.
@return Pointer to a  to utf to the stdout.
@param seam_log Beginning of the seam log socket.
@param seam_end End of the seam log socket.
@param args     Command line argument . */
typedef const CHA* (*TestCase)(const CHA* args);

namespace _ {

/* Handles an D_ASSERT.
@return True upon failure.
@param line    The line the program failed at.
@param file    The file the error occurred at.
@param message An optional message to utf. */
LIB_MEMBER void TestFunctionLine(ISN line, const CHA* funciton,
                                 const CHA* file);

/* Handles an D_ASSERT.
@return True upon failure.
@param line    The line the program failed at.
@param file    The file the error occurred at.
@param message An optional message to utf. */
LIB_MEMBER BOL TestWarn(ISN line, const CHA* funciton, const CHA* file);

/* Handles an D_ASSERT.
@return True upon failure.
@param line    The line the program failed at.
@param file    The file the error occurred at.
@param message An optional message to utf. */
LIB_MEMBER BOL TestFail(ISN line, const CHA* funciton, const CHA* file);

/* Converts ISC main(ISC,CHA**) arguments back into a string.
@return nil if there are no arguments or the args string upon success.
@param arg_count The number_ of arguments.
@param args      The arguments. */
LIB_MEMBER const CHA* ArgsToString(ISN arg_count, CHA** args);

/* Converts the result not being null into the proper OS return value for int
main (). */
LIB_MEMBER ISN SeamResult(const CHA* result);

/* Tests an array of TestCase(s).
@return 0 upon success or an app exit code upon failure. */
LIB_MEMBER ISN SeamTreeTest(ISN arg_count, CHA** args, TestCase* tests,
                            ISN test_count);

/* Tests an array of TestCase(s).
@return Nil upon success or an error  upon failure. */
LIB_MEMBER const CHA* TestTree(const CHA* args, TestCase* seams,
                               ISN node_count);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param condition The condition to check. */
LIB_MEMBER BOL Test(BOL condition);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param value The value to test. */
LIB_MEMBER BOL Test(ISA value);
LIB_MEMBER BOL Test(IUA value);
LIB_MEMBER BOL Test(ISB value);
LIB_MEMBER BOL Test(IUB value);
LIB_MEMBER BOL Test(ISC value);
LIB_MEMBER BOL Test(IUC value);
LIB_MEMBER BOL Test(ISD value);
LIB_MEMBER BOL Test(IUD value);
LIB_MEMBER BOL Test(FPC value);
LIB_MEMBER BOL Test(FPD value);

/* Tests if the pointer is nil.
@return false if the condition is false.
@param value The value to test.  */
LIB_MEMBER BOL Test(const void* value);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(const CHA* a, const CHA* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(CHA a, CHA b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(CHB a, CHB b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(CHC a, CHC b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(const CHB* a, const CHB* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(const CHC* a, const CHC* b);

/* Tests if the two pointers are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(const void* a, const void* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(IUA a, IUA b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(ISA a, ISA b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(IUA a, IUA b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(ISB a, ISB b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(IUB a, IUB b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(ISC a, ISC b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(IUC a, IUC b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(ISD a, ISD b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(IUD a, IUD b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(FPC a, FPC b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param a Parameter a.
@param b Parameter b. */
LIB_MEMBER BOL Test(FPD a, FPD b);

}  // namespace _

#endif
