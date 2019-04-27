/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_test.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_CTEST
#define SCRIPT2_CTEST 1

/* Function pointer prototype for a test case with command line argument
.
@return Pointer to a  to utf to the stdout.
@param seam_log Beginning of the seam log socket.
@param seam_end End of the seam log socket.
@param args     Command line argument . */
typedef const CH1* (*TestCase)(CH1* seam_log, CH1* seam_end, const CH1* args);

namespace _ {

/* Handles an DASSERT.
@return True upon failure.
@param  line    The line the program failed at.
@param  file    The file the error occurred at.
@param  message An optional message to utf. */
SDK void TestFunctionLine(SI4 line, const CH1* funciton, const CH1* file);

/* Handles an DASSERT.
@return True upon failure.
@param  line    The line the program failed at.
@param  file    The file the error occurred at.
@param  message An optional message to utf. */
SDK BOL TestWarn(SI4 line, const CH1* funciton, const CH1* file,
                 const CH1* header = "Assertion failed at ");

/* Handles an DASSERT.
@return True upon failure.
@param  line    The line the program failed at.
@param  file    The file the error occurred at.
@param  message An optional message to utf. */
SDK BOL TestFail(SI4 line, const CH1* funciton, const CH1* file);

/* Tests an array of TestCase(s).
@return 0 upon success or an app exit code upon failure. */
SDK SI4 SeamTreeTest(SI4 arg_count, CH1** args, CH1* seam_log,
                     SI4 seam_log_size, TestCase* tests, SI4 test_count);

/* Tests an array of TestCase(s).
@return Nil upon success or an error  upon failure. */
SDK const CH1* TestTree(CH1* seam_log, CH1* seam_end, const CH1* args,
                        TestCase* seams, SI4 node_count);

/* Prints a message when a TestCase completes without failure. */
SDK BOL TestBegin(CH1* seam_log, CH1* seam_end, const CH1* args);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param condition The condition to check. */
SDK BOL Test(BOL condition);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
SDK BOL Test(SI1 value);
SDK BOL Test(UI1 value);
SDK BOL Test(SI2 value);
SDK BOL Test(UI2 value);
SDK BOL Test(SI4 value);
SDK BOL Test(UI4 value);
SDK BOL Test(SI8 value);
SDK BOL Test(UI8 value);
SDK BOL Test(FP4 value);
SDK BOL Test(FP8 value);

/* Tests if the pointer is nil.
@return false if the condition is false.
@param  value The value to test.  */
SDK BOL Test(const void* value);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(const CH1* a, const CH1* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(CH1 a, CH1 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(CH2 a, CH2 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(CH4 a, CH4 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(const CH2* a, const CH2* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(const CH4* a, const CH4* b);

/* Tests if the two pointers are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(const void* a, const void* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(UI1 a, UI1 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(SI1 a, SI1 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(UI1 a, UI1 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(SI2 a, SI2 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(UI2 a, UI2 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(SI4 a, SI4 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(UI4 a, UI4 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(SI8 a, SI8 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(UI8 a, UI8 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(FP4 a, FP4 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
SDK BOL Test(FP8 a, FP8 b);

}  // namespace _

#endif
