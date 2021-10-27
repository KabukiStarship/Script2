/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Language.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
#ifndef SCRIPT2_LANGUAGE
#define SCRIPT2_LANGUAGE 1
namespace _ {
namespace langauge {

enum {
  cEnUppercaseBegin = 'A',
  cEnUppercaseEnd   = 'Z',
  cEnLowercaseBegin = 'a',
  cEnLowercaseEnd   = 'z',
};
}  //< namespace langauge

/* A spoken language Unicode character range.

*/
struct Language {
  CHC uppercase_begin,  //< First uppercase Unicode CHA index.
      uppercase_end,    //< Last uppercase Unicode CHA index.
      lowercase_begin,  //< First lowercase Unicode CHA index.
      lowercase_end;    //< Last lowercase Unicode CHA index.
};

}  //< namespace _
#endif
#endif
