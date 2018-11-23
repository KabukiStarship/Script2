/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /seam_tree.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#ifndef INCLUDED_SEAM_TREE
#define INCLUDED_SEAM_TREE 1
#include "0_0_0.script2.h"

using namespace _;
int main(int arg_count, char** args) {
  enum { kSize = 1024 };
  char seam_log[kSize];
  return TTestTree<_0_0_0_F2>(arg_count, args, seam_log, kSize);
}
#endif
