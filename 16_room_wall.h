/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/16_room.h
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

#if SEAM == SCRIPT2_15
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

#include "c_room.h"

using namespace _;

namespace script2 {
static const CH1* _16_Room_Wall(CH1* seam_log, CH1* seam_end,
                                const CH1* args) {
#if SEAM == SCRIPT2_16
  TEST_BEGIN;
  Room room_a, room_b;
#endif
  return nullptr;
}
} //< namespace script2
