/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/event.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_14
#ifndef SCRIPT2_EVENT
#define SCRIPT2_EVENT
// Dependencies:
#include "operand.h"
// End dependencies.

namespace _ {

/* Interface for a temporal event in a Bayesian net.
@code
#include <script/Event.h>
struct SDK Example: public Event {
virtual void Trigger () {
    // ...
}
};
@endcode
*/
struct SDK Event : public Operand {
  /* Virtual destructor. */
  virtual ~Event() = 0;

  /* Triggers the event. */
  virtual void Trigger() = 0;

  virtual DBL GetProbability() = 0;

  /* Script operations. */
  virtual const Op* Star(CHW index, CCrabs* crabs) = 0;
};

}  //< namespace _
#endif  //< SCRIPT2_EVENT
#endif  //< #if SEAM >= SCRIPT2_14
