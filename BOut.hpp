/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /BOut.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "BOut.h"
namespace _ {

inline CHA* BOutBegin(BOut* bout) { return TPtr<CHA>(bout) + sizeof(BOut); }

template <typename Printer>
Printer& TBOutPrint(Printer& printer, BOut* bout) {
  A_ASSERT(bout);
  ISC size = bout->size;
  printer << Line('_', 80) << "\nBOut:" << Hex<>(bout) << " size:" << size
          << " start:" << bout->origin << " stop:" << bout->stop
          << " read:" << bout->read << Socket(BOutBuffer(bout), size - 1);
  return printer;
}

}  //< namespace _

#endif
