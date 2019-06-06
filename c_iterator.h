/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/KabukiSDK/data/iterator.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_SEAM_DIC
#ifndef SCRIPT2_ITERATOR_H
#define SCRIPT2_ITERATOR_H
// Dependencies:
#include "c_onfig.h"
// End dependencies.

namespace _ {

/* Interface for a generic iterator. */
struct SDK Iterator {
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
#endif  //< SCRIPT2_ITERATOR_H
#endif  //< #if SEAM >= SCRIPT2_SEAM_DIC
