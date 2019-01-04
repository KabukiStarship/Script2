/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cdoor.h
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
#if SEAM >= _0_0_0__14
#ifndef SCRIPT2_DOOR
#define SCRIPT2_DOOR
#include "ccrabs.h"
#include "cslot.h"
#include "tstack.h"
#include "tstr.h"

namespace _ {

/* A door that connects two Chinese rooms.
A door can lead to one or more Rooms. A Door that can
be locked, in which case all of the Rooms behind this door are locked
out. When a door is locked, no messages are processed or sent to or
from the door and its subsidiary agents.

Rooms can be connected by one or more Portal. An example of a
system with one Door and multiple Portals is a WiFi plus USB/Serial
connection. This is a commonly used configuration for debugging the system.

Multiple doors also might share the same Portal. An example of this is a
connection to multiple systems over a WiFi connection.

@code

+=============+
|    slots    |
|=============|
| Door struct |
+=============+

@endcode
*/
class Door : public Operand {
 public:
  typedef enum Errors { kErrorInvalidOp = 0, kErrorImplementation } Error;

  enum {
    kMinDoorSize = 128,  //< The min and default size of the door socket.
  };

  /* A door in a Chinese room. */
  Door(const CH1* roomName = nullptr, UIW* socket = nullptr,
       UIW size_bytes = kMinDoorSize);

  /* AsciiFactory. */
  virtual ~Door();

  /* Gets the BOut at the given index. */
  slot_t GetSlot(slot_t index);

  /* Address the given crabs to the Door. */
  slot_t AddSlot(slot_t slot);

  /* Attempts to find a Slot or Door with the given address. */
  BOL Contains(void* address);

  /* Gets the Slot that contains the given address.
  @return Returns the doors_ stack count if the Door does not contain the given
  address. */
  slot_t FindSlot(void* address);

  /* Executes all of the queued escape sequences. */
  const Op* ExecAll();

  /* Script expressions. */
  virtual const Op* Star(CHW index, CCrabs* crabs);

 private:
  UIW* begin;                           //< Pointer to dynamic socket.
  TArray<slot_t, UIT, int_t>* slots_;  //< Slots in the door.
};

/* Returns a Static Error Op. */
API const Op* DoorResult(Door* door, Door::Error error);

API const CH1* DoorErrorText(Door::Error error);

/* Returns the main door of the room.
API Door& Doors (); */

/* Initializes a Door at the beginning of the given socket.
static Door* DoorInit (int* socket, UIT slot_size) {
  if (socket == nullptr) return nullptr;
  if (slot_size < kMinSlotSize) return nullptr;
  Wall* wall = reinterpret_cast<Door*>(socket);
  w->is_dynamic = 0;
  w->num_doors = 0;
  w->max_num_doors;
  w->door_one = nullptr;
}*/

}  // namespace _
#endif  //< #if SEAM >= _0_0_0__14
#endif  //< SCRIPT2_DOOR
