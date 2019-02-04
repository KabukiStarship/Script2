/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_string.h
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
#pragma once
#ifndef SCRIPT2_STRINGUTILS_T
#define SCRIPT2_STRINGUTILS_T

namespace _ {

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CH1>
inline const Char* TSTREnd(const Char* start, CH1 delimiter = 0) {
  while (*start++ != delimiter)
    ;
  return start - 1;
}

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CH1>
inline Char* TSTREnd(Char* start, Char delimiter = 0) {
  return const_cast<Char*>(
      TSTREnd(reinterpret_cast<const Char*>(start), delimiter));
}

/* Checks if the given character is whitespace. */
template <typename Char = CH1>
inline BOL TIsWhitespace(Char character) {
  return character <= ' ';
}

}  // namespace _

#endif
