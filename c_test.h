/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_test.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_C_TEST
#define SCRIPT2_C_TEST 1

#include "c_cin.h"

/* Function pointer prototype for a test case with command line argument
.
@return Pointer to a  to utf to the stdout.
@param seam_log Beginning of the seam log socket.
@param seam_end End of the seam log socket.
@param args     Command line argument . */
typedef const CH1* (*TestCase)(const CH1* args);

namespace _ {

/* Handles an D_ASSERT.
@return True upon failure.
@param  line    The line the program failed at.
@param  file    The file the error occurred at.
@param  message An optional message to utf. */
LIB_MEMBER void TestFunctionLine(SI4 line, const CH1* funciton,
                                 const CH1* file);

/* Handles an D_ASSERT.
@return True upon failure.
@param  line    The line the program failed at.
@param  file    The file the error occurred at.
@param  message An optional message to utf. */
LIB_MEMBER BOL TestWarn(SI4 line, const CH1* funciton, const CH1* file);

/* Handles an D_ASSERT.
@return True upon failure.
@param  line    The line the program failed at.
@param  file    The file the error occurred at.
@param  message An optional message to utf. */
LIB_MEMBER BOL TestFail(SI4 line, const CH1* funciton, const CH1* file);

/* Tests an array of TestCase(s).
@return 0 upon success or an app exit code upon failure. */
LIB_MEMBER SIN SeamTreeTest(SI4 arg_count, CH1** args, TestCase* tests,
                            SIN test_count);

/* Tests an array of TestCase(s).
@return Nil upon success or an error  upon failure. */
LIB_MEMBER const CH1* TestTree(const CH1* args, TestCase* seams,
                               SIN node_count);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param condition The condition to check. */
LIB_MEMBER BOL Test(BOL condition);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
LIB_MEMBER BOL Test(SI1 value);
LIB_MEMBER BOL Test(UI1 value);
LIB_MEMBER BOL Test(SI2 value);
LIB_MEMBER BOL Test(UI2 value);
LIB_MEMBER BOL Test(SI4 value);
LIB_MEMBER BOL Test(UI4 value);
LIB_MEMBER BOL Test(SI8 value);
LIB_MEMBER BOL Test(UI8 value);
LIB_MEMBER BOL Test(FP4 value);
LIB_MEMBER BOL Test(FP8 value);

/* Tests if the pointer is nil.
@return false if the condition is false.
@param  value The value to test.  */
LIB_MEMBER BOL Test(const void* value);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(const CH1* a, const CH1* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(CH1 a, CH1 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(CH2 a, CH2 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(CH4 a, CH4 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(const CH2* a, const CH2* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(const CH4* a, const CH4* b);

/* Tests if the two pointers are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(const void* a, const void* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(UI1 a, UI1 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(SI1 a, SI1 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(UI1 a, UI1 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(SI2 a, SI2 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(UI2 a, UI2 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(SI4 a, SI4 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(UI4 a, UI4 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(SI8 a, SI8 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(UI8 a, UI8 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(FP4 a, FP4 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
LIB_MEMBER BOL Test(FP8 a, FP8 b);

}  // namespace _

#endif
