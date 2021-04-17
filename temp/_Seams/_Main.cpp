/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/_Main.cpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#include "_Tests.inl"
using namespace _;

ISN main(ISN arg_count, CHA** args) {
  CHA* argss = ArgsToString(arg_count, args);
#if SEAM == SEAM_N
  return SeamResult(Release(argss));
#else
  return TTestTree<Script2Tests>(arg_count, args);
#endif
}
