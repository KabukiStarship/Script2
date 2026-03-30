// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_ITERATOR_DECL
#define CRABS_ITERATOR_DECL
#include <_Config.h>
#if SEAM >= CRABS_DIC
// Dependencies:
// End dependencies.
namespace _ {

/* Interface for a generic iterator. */
struct Iterator {
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
