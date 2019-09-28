/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /language.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_DICTIONARY
#ifndef SCRIPT2_LANGUAGE
#define SCRIPT2_LANGUAGE 1

namespace _ {

namespace langauge {

enum {
  kEnUppercaseBegin = 'A',
  kEnUppercaseEnd = 'Z',
  kEnLowercaseBegin = 'a',
  kEnLowercaseEnd = 'z',
};
}  // namespace langauge

/* A spoken language Unicode character range.

*/
struct Language {
  CH4 uppercase_begin,  //< First uppercase Unicode CH1 index.
      uppercase_end,    //< Last uppercase Unicode CH1 index.
      lowercase_begin,  //< First lowercase Unicode CH1 index.
      lowercase_end;    //< Last lowercase Unicode CH1 index.
};

}  // namespace _
#endif
#endif
