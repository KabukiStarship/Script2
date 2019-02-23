/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_hash.cc
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
