/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \ctest.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_CTEST
#define SCRIPT2_CTEST 1

/* Function pointer prototype for a test case with command line argument
string_.
@return Pointer to a string_ to utf to the stdout.
@param seam_log Beginning of the seam log socket.
@param seam_end End of the seam log socket.
@param args     Command line argument string_. */
typedef const CH1* (*TestCase)(CH1* seam_log, CH1* seam_end,
                                const CH1* args);
namespace _ {

/* Tests an array of TestCase(s).
@return 0 upon success or an app exit code upon failure. */
int SeamTreeTest(int arg_count, CH1** args, CH1* seam_log, int seam_log_size,
                 TestCase* tests, int test_count);

/* Tests an array of TestCase(s).
@return Nil upon success or an error string_ upon failure. */
const CH1* TestTree(CH1* seam_log, CH1* seam_end, const CH1* args,
                     TestCase* seams, int node_count);

/* Prints a message when a TestCase completes without failure. */
BOL TestBegin(CH1* seam_log, CH1* seam_end, const CH1* args);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param condition The condition to check. */
API BOL Test(BOL condition);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API BOL Test(SI1 value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API BOL Test(UI1 value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API BOL Test(SI2 value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API BOL Test(UI2 value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API BOL Test(SI4 value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API BOL Test(UI4 value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API BOL Test(SI8 value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API BOL Test(UI8 value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API BOL Test(FLT value);

/* Test function to assist in casting boolean types.
@return false if the condition is false.
@param  value The value to test. */
API BOL Test(DBL value);

/* Tests if the pointer is nil.
@return false if the condition is false.
@param  value The value to test.  */
API BOL Test(const void* value);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(const CH1* a, const CH1* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(const CH2* a, const CH2* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(const CH4* a, const CH4* b);

/* Tests if the two pointers are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(const void* a, const void* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(UI1 a, UI1 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(SI1 a, SI1 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(UI1 a, UI1 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(SI2 a, SI2 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(UI2 a, UI2 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(SI4 a, SI4 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(UI4 a, UI4 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(SI8 a, SI8 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(UI8 a, UI8 b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(FLT a, FLT b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(DBL a, DBL b);

/* Handles an assert.
@return True upon failure.
@param  line    The line the program failed at.
@param  file    The file the error occurred at.
@param  message An optional message to utf. */
API BOL TestWarn(const CH1* funciton, const CH1* file, int line);

/* Handles an assert.
@return True upon failure.
@param  line    The line the program failed at.
@param  file    The file the error occurred at.
@param  message An optional message to utf. */
API BOL TestAssert(const CH1* funciton, const CH1* file, int line);

}  // namespace _

#endif  //< #ifndef SCRIPT2_CTEST
