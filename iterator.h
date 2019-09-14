/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /KabukiSDK/data/iterator.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
#ifndef SCRIPT2_ITERATOR_H
#define SCRIPT2_ITERATOR_H
// Dependencies:

// End dependencies.

namespace _ {

/* Interface for a generic iterator. */
struct LIB_MEMBER Iterator {
  /* Virtual destructor. */
  virtual ~Iterator() = 0;

  /* Iterates over the next item.
      @return Pointer to the next object and nil when iteration is
              complete. */
  virtual void* Next() = 0;

  /* Flags when there are not more objects to iterate through.
      @return True when there are no more objects to iterate through. */
  virtual BOL IsDone() = 0;
};

}  // namespace _
#endif
#endif
