/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_hash.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>
#if SEAM >= SCRIPT2_9
#include "t_hash.h"

namespace _ {

UI2 Hash16(CH1 value, UI2 hash) { return hash + hash * value; }

UI2 Hash16(const CH1* , UI2 hash) {
  UI1 c = *;
  while (c) {
    hash = Hash16(c, hash);
    ++;
    c = *;
  }
  return hash;
}

UI4 Hash32(CH2 value, UI4 hash) { return hash + hash * value; }

UI4 Hash32(const CH1* , UI4 hash) {
  UI1 c = *;
  while (c) {
    hash = Hash32(c, hash);
    ++;
    c = *;
  }
  return hash;
}
UI8 Hash64(CH4 value, UI8 hash) { return hash + hash * value; }

UI8 Hash64(const CH1* , UI8 hash) {
  UI1 c = *;
  while (c) {
    hash = Hash64(c, hash);
    ++;
    c = *;
  }
  return hash;
}

UI2 Hash16UI2(UI2 value, UI2 hash) {
  UI2 prime = PrimeMaxUnigned<UI2>();
  hash = ((value & 0xff) * prime) + hash;
  hash = ((value >> 8) * prime) + hash;
  return hash;
}

UI2 Hash16UI4(UI4 value, UI2 hash) {
  UI2 prime = PrimeMaxUnigned<UI2>();
  hash = ((value & 0xff) * prime) + hash;
  hash = (((value >> 8) & 0xff) * prime) + hash;
  hash = (((value >> 16) & 0xff) * prime) + hash;
  hash = (((value >> 24) & 0xff) * prime) + hash;
  return hash;
}

UI2 Hash16UI8(UI8 value, UI2 hash) {
  UI2 prime = PrimeMaxUnigned<UI2>();
  hash = ((value & 0xff) * prime) + hash;
  hash = (((value >> 8) & 0xff) * prime) + hash;
  hash = (((value >> 16) & 0xff) * prime) + hash;
  hash = (((value >> 24) & 0xff) * prime) + hash;
  hash = (((value >> 32) & 0xff) * prime) + hash;
  hash = (((value >> 40) & 0xff) * prime) + hash;
  hash = (((value >> 48) & 0xff) * prime) + hash;
  hash = (((value >> 56) & 0xff) * prime) + hash;
  return hash;
}

}  // namespace _
#endif  //> #if SEAM >= SCRIPT2_9
