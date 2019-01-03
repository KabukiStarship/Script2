/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /interrupts.h
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
#if SEAM >= _0_0_0__14
#ifndef INCLUDED_CRABS_EXCEPTIONS
#define INCLUDED_CRABS_EXCEPTIONS YES
// Dependencies:
#include "config.h"
// End dependencies.
#if USING_CRABS_INTERRUPTS == YES

namespace _ {

#if USING_TEXT_SCRIPT == YES
/* Exception thrown to interrupt and crash the program. */
struct API RoomCrashException : public std::exception {
  const CH1* what() const throw();
};
#endif
}  // namespace _
#endif  //< #if USING_CRABS_INTERRUPTS == YES
#endif  //< #if INCLUDED_CRABS_EXCEPTIONS == YES
#endif  //< #if SEAM >= _0_0_0__14
