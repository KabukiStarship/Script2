/* Script2�
@link    https://github.com/KabukiStarship/Script2.git
@file    /Iterator.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship� <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_ITERATOR_DECL
#define SCRIPT2_ITERATOR_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
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

}  //< namespace _
#endif
#endif
