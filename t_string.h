/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_string.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

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
