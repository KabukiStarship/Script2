/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_est_tree.cc
@author  Cale McCollough <cale@astartup.net>
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

#ifndef INCLUDED_SEAM_TREE
#define INCLUDED_SEAM_TREE 1
#include "test_tree.h"
 
SI4 main(SI4 arg_count, CH1** args) {
  enum { kSize = 1024 };
  CH1 seam_log[kSize];
  return _::TTestTree<script2::TestNode>(arg_count, args, seam_log, kSize);
}
#endif
