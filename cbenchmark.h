/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cbenchmark.h
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

#if SEAM >= _0_0_0__13
#ifndef SCRIPT2_BENCHMARK
#define SCRIPT2_BENCHMARK 1

#include "ctest.h"

namespace _ {

/* Class for storing information about a failed assertion.
struct API TestResult {
  const CH1 *name,  //< The file the assertion occurred at.
      *description;  //< An optional description to utf.
  SI4 line,          //< The line the assertion failed at.
      code;          //< The test result code.
}; */

class BenchmarkCase {
 public:
  /* Constructs an object from the given values. */
  BenchmarkCase(const CH1* name, TestCase* cases, SI4 count);

  /* Runs the benchmark. */
  const CH1* Run(CH1* cursor, CH1* stop, const CH1* args);

  /* Gets the number_ of cases in this benchmark. */
  SI4 GetCount();

 private:
  const CH1* name;  //< Name of this benchmark case.
  TestCase* cases;   //< Array of pointers of BenchmarkCase(s).
  SI4 count;         //< Number of test cases.
};

/* A Benchmark composed of one or more BenchmarkCase(s). */
class Benchmark {
 public:
  /* Constructs an object from the given values. */
  Benchmark(const CH1* name, const CH1* filename, BenchmarkCase* groups,
            SI4 count);

  /* Runs the benchmark.
  @return If args is nil, result will contain the name as */
  const CH1* Run(CH1* cursor, CH1* stop, const CH1* args);

 private:
  const CH1 *name,       //< Name of the benchmark.
      *filename;          //< Filename including .csv file extention.
  BenchmarkCase* groups;  //< Array of pointers of BenchmarkCase(s).
  SI4 count,              //< Number of test cases.
      columns_max;        //< Max test cases in any BenchmarkCase(s).
};

}  // namespace _

#endif  //< SCRIPT2_BENCHMARK
#endif  //< #if SEAM >= _0_0_0__13
