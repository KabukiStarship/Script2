// Copyright Kabuki Starship <kabukistarship.com>.
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
