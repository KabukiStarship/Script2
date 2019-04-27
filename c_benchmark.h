/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_benchmark.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_13
#ifndef SCRIPT2_BENCHMARK
#define SCRIPT2_BENCHMARK 1

#include "c_test.h"

namespace _ {

/* Class for storing information about a failed assertion.
struct SDK TestResult {
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

#endif
#endif
