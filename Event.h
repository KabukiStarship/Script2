// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_EVENT_DECL
#define CRABS_EVENT_DECL
#include <_Config.h>
#if SEAM >= CRABS_DIC
namespace _ {

/* Interface for an abstract event.
 */
struct Event {
  /* Virtual destructor. */
  virtual ~Event() = 0;

  /* Triggers the event. */
  virtual void Trigger() = 0;
};

}  //< namespace _
#endif
#endif
