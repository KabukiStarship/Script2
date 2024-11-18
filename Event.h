// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_EVENT_DECL
#define SCRIPT2_EVENT_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
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
