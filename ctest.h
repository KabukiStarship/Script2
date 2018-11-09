/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script.git
@file    \kabuki\f2\ctest.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#ifndef INCLUDED_SCRIPT_COMPARE
#define INCLUDED_SCRIPT_COMPARE 1

/* Function pointer prototype for a test case with command line argument
string.
@return Pointer to a string to print to the stdout.
@param seam_log Beginning of the seam log buffer.
@param seam_end End of the seam log buffer.
@param args     Command line argument string. */
typedef const char* (*TestCase)(char* seam_log, char* seam_end,
                                const char* args);
namespace _ {

/* Tests an array of TestCase(s).
@return 0 upon success or an app exit code upon failure. */
int SeamTreeTest(int arg_count, char** args, char* seam_log, int seam_log_size,
                 TestCase* tests, int test_count);

/* Tests an array of TestCase(s).
@return Nil upon success or an error string upon failure. */
const char* TestTree(char* seam_log, char* seam_end, const char* args,
                     TestCase* seams, int node_count);

/* Prints a message when a TestCase completes without failure. */
BOL TestBegin(char* seam_log, char* seam_end, const char* args);

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
API BOL Test(const char* a, const char* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(const char16_t* a, const char16_t* b);

/* Tests if the given arguments are equal.
@return false if the condition is false.
@param  a Parameter a.
@param  b Parameter b. */
API BOL Test(const char32_t* a, const char32_t* b);

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
@param  message An optional message to print. */
API BOL TestWarn(const char* funciton, const char* file, int line);

/* Handles an assert.
@return True upon failure.
@param  line    The line the program failed at.
@param  file    The file the error occurred at.
@param  message An optional message to print. */
API BOL ErrorFreeze(const char* funciton, const char* file, int line);
}  // namespace _

#endif  //< #ifndef INCLUDED_SCRIPT_COMPARE
