/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Address.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
#ifndef SCRIPT2_ADDRESS
#define SCRIPT2_ADDRESS 1

namespace _ {

/* C++11 constexpr function for creating Script addresses headers with less
typing as well as ensuring there is only a single copy in ROM.
Template solves the problem of not being able using array constructors to
create data structures in ROM.

@code
Address<'A', 'B', 'C'> ()
@endcode
*/
template <const CHA... N>
LIB_MEMBER const CHA* Address() {
  static const CHA path[sizeof...(N)] = {N...};
  static const CHA term_char = 0;
  return path;
}

/* Returns a pointer to static variable for writing the address { a, \0 } to.
 */
inline IUB PackAddress(IUA a) { return ((1 << 8) | a); }

/* Returns a pointer to static variable for writing the address 
{ a, b, \0, \0 } to. */
inline IUC PackAddress(IUC a, IUC b) { return ((1 << 16) | a | (b << 8)); }

/* Returns a pointer to static variable for writing the address { a, b, c, \0 }
to. */
inline IUC PackAddress(IUC a, IUC b, IUC c) {
  return ((1 << 24) | a | (b << 8) | (c << 16));
}

/* Returns a pointer to static variable for writing the address { a, b, c, d,
e, f, g, \0 } to. */
inline IUD PackAddress(IUD a, IUD b, IUD c, IUD d) {
  IUD one = 1;
  return (one << 32 | a | (b << 8) | (c << 16) | (d << 24));
}

/* Returns a pointer to static variable for writing the address { a, b, c, d,
e, f, g, \0 } to. */
inline IUD PackAddress(IUD a, IUD b, IUD c, IUD d, IUD e) {
  IUD one = 1;
  return (one << 40 | a | (b << 8) | (c << 16) | (d << 24) | (e << 32));
}

/* Returns a pointer to static variable for writing the address
{ a, b, c, d, e, f, g, \0 } to. */
inline IUD PackAddress(IUD a, IUD b, IUD c, IUD d, IUD e, IUD f) {
  IUD one = 1;
  return (one << 48 | a | (b << 8) | (c << 16) | (d << 24) | (e << 32) |
          (f << 40));
}

/* Returns a pointer to static variable for writing the address
{ a, b, c, d, e, f, g, \0 } to. */
inline IUD PackAddress(IUD a, IUD b, IUD c, IUD d, IUD e, IUD f, IUD g) {
  IUD one = 1;
  return (one << 56 | a | (b << 8) | (c << 16) | (d << 24) | (e << 32) |
          (f << 40) | (g << 48));
}

}  // namespace _
#endif
#endif
