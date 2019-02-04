/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_benchmark.cc
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#if SEAM >= SCRIPT2_13
#include "t_benchmark.h"

#include "rng.h"
#include "t_binary.h"
#include "t_test.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

using namespace std;
using namespace std::chrono;

#if SEAM == SCRIPT2_13
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

BenchmarkCase::BenchmarkCase(const CH1* name, TestCase* cases, SI4 count)
    : name(name), cases(cases), count(count) {}

const CH1* BenchmarkCase::Run(CH1* cursor, CH1* stop, const CH1* args) {
  /*
  FP8 nil_reading;
  SI4 i;
  SI4 columns_max;
  ASSERT(TScan<>(args, columns_max));

  for (i = 0; i < count; ++i) {
    const CH1* result = (*cases[i])(nullptr, nullptr, nullptr);
    Print(result);
    if (i < count) Print(',', ' ');
  }
  for (; i < columns_max; ++i) Print(',');
  PrintNL();
  for (i = 0; i < count; ++i) {
    const CH1* result = (*cases[i])(nullptr, nullptr, nullptr);
    if (i < count) Print(',', ' ');
  }
  PrintNL();
  */
  return nullptr;
}

SI4 BenchmarkCase::GetCount() { return count; }

Benchmark::Benchmark(const CH1* name, const CH1* filename,
                     BenchmarkCase* groups, SI4 count)
    : name(name), filename(filename), groups(groups), count(count) {
  ASSERT(count > 0);
  SI4 l_test_count_max = 0;
  for (SIW i = 0; i < count; ++i) {
  }
}

const CH1* Benchmark::Run(CH1* cursor, CH1* stop, const CH1* args) {
  /*
  std::ofstream out(filename);

  auto* coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());

  for (SIW i = 0; i < count; ++i) {
    BenchmarkCase group = groups[i];
    const CH1* result = group.Run(cursor, stop, args);
    ASSERT(result);
    Print(result);
  }
  BenchmarkCase *benchmark_case = groups, *stop = groups + count - 1;
  for (SI4 i = 0; i <  {
    groups[i]->Run(cursor, stop, args);
  }
  std::cout.rdbuf(coutbuf);*/
  return nullptr;
}

}  // namespace _

#endif
