// Copyright Kabuki Starship� <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_LANGUAGE_DECL
#define SCRIPT2_LANGUAGE_DECL 1
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
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
