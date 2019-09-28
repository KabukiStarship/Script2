/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /room.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_ROOM
#ifndef SCRIPT2_ROOM
#define SCRIPT2_ROOM
#include "interrupts.h"
#include "wall.h"

namespace _ {

/* A list of Requests that can be sent from Slot<SI4, TSizeBytes> to
    Slot<SI4, TSizeBytes>.  */
typedef enum Requests {
  kOpenDoorRequest = 0,
  kCloseDoorRequest,
  kConnectionRequest,
  kDisconnectRequest,
  kInvalidRequest,
} Request;

/* Returns an array of pointers to Strings that describe the program states.
 */
LIB_MEMBER const CH1** RoomStateTexts();

/* Returns a pointer to an array of pointers to the Request Strings. */
LIB_MEMBER const CH1** RequestTexts();

/* Gets the response CH1 corresponding to the given request. */
LIB_MEMBER const CH1* RequestText(Request r);

/* A Chinese Room.
An Chinese Room works the same way as in the Chinese Room thought
experiment. An Room receives a message through a slot in the door, the man
in the room reads does manual optical character recognition with a pen and
paper stack, some filing cabinets, and a library of multimaps.
  The size of the Crabs Stack is defined by the Script Protocol to be a
a maximum of 2^15-1 expressions tall.
# Memory Layout
Some systems have the stack grow up from the bottom and heap grow up and
vice versa.
@code
    +-----------------------+
    |         Heap          |
    |         Wall 1        |
    |         Wall 2        |
    |          ...          |
    |         Wall N        |
    |vvvvvvvvvvvvvvvvvvvvvvv|
    |     Unused Memory     |
    |^^^^^^^^^^^^^^^^^^^^^^^|
    |     Program Stack     |
+/- |-----------------------|
 |  | Floor (Static Memory) |
0xN +-----------------------+
@endcode

# ASCII Mappings

The mapping of the layout of the Chinese Room can be seen in the following
super cute ASCII houses:

@code
 _________
/_________\
[_#_]@[_#_]
@endcode


# Room Connections

There are multiple doors in a Chinese Room that lead to other Chinese Rooms.
Each door has multiple slots in lead to the same room. These slots are the
various IO ports of the system.

# Doors

There are two ways to access Doors in the CR. in the Root Scope, there are:

@code
Use Case Scenario:
Actors: Jo  - The app developer.
        Sam - The stop-user.
1.  Jo is creating an App and needs to make a Chinese Room so Jo downloads
    Script, starts his app, and makes a Room. Jo defines a Floor
    statically but is does not define any walls.
    2.  Host creates a memory stack without any heap space.
2.  Jo needs to add a UART port out to his App so he adds a BOut with a
    slot_size of 2KB.
    3.  Host adds the Slot to the Program Stack.
4.  Jo needs to add a SPI IO device so he initializes a Slot with 256
    bytes.
    5.  Host adds the new Slot on top of the Slot.
6.  Jo is out of memory in the Floor so he creates a Ceiling of size 2KB.
    7.  Host creates a Heap Block for the Ceiling.
7.  Jo needs Interprocess communication to three threads: one SlotIn,
    one SlotOut, and a Slot of size 2KB.
    8.  Host adds the SlotIn, MirroOut, and Slot to the Ceiling.
9.  Jo wants to add a Server so Jo creates Wall_1 with 1MB space.
    10. Host creates a Wall_1 with 1MB memory.
11. Jo wants needs to distribute information to the stop-users so Jo
    creates Dictionary in Wall_1 with some keys and values.
    12. Host creates dictionary and adds keys and values.
13. Jo complies the program and launches the server.
    14. Host loads.
15. Sam launches Jo's app and connections to the Host.
    16. Host receives login attempt from Sam and opens a Door for him.
17. Sam needs to get the values Jo stored in step 11 so Same sends a
    Dictionary GET request.
    @endcode
*/
class Room : public Operand {
  // NONCOPYABLE (Room) //< Not sure why this isn't working?

 public:
  typedef enum States {
    kStateBooting = 0,
    kStateGoingToSleep,
    kShutdown,
  } State;

  enum {
#ifndef SCRIPT2_MAX_WALLS
    kRoomFloorSize = 1024,
#else
    kRoomFloorSize = SCRIPT2_MAX_WALLS,
#undef ROOM_FLOOR_SIZE
#endif
    kFloorSizeWords = kRoomFloorSize / sizeof(UIW) + 2,  //< +2 socket.
  };

  /* Creates a Room with the given size.
      @param floor Buffer used to create the Wall Stack. Set to nullptr to
                   enable dynamic memory.
      @param size  The room size that is bounded between the kMinRoomSize and
                   kMaxRoomSize. */
  Room(const CH1* room_name = "chinese_room", SI4 num_states = 2);

  /* SocketFactory. */
  virtual ~Room();

  /* Gets the Room state_. */
  SI4 GetState();

  /* Gets the Room state_. */
  SI4 GetStateCount();

  const CH1* GetRoomName();

  /* Sets the Room state_. */
  virtual BOL SetRoomName(const CH1* name);

  /* Processes a request from another Room.
      @return Returns false upon success and true if there is an error. */
  Request HandleNextRequest(Request r);

  /* Clears the log. */
  void ClearLog();

  /* Processes all of the errors in the error log. */
  void ProcessLog();

  /* Prints the error log to a expression. */
  void PrintErrors(BOut* bout);

  /* Gets the wall_count_. */
  int_t WallCount();

  /* Gets the given wall by index.
  @return Nil if the index is invalid  */
  Wall* GetWall(int_t wall_number);

  /* Ads a wall to the room.
  @return The inputed new_wall pointer upon success or nil upon failre. */
  Wall* AddWall(Wall* new_wall);

  /* Removes the given Wall by index.
  @return False upon failure.  */
  BOL RemoveWall(int_t wall_number);

  /* Gets the entire Room size, including dynamic memory, in bytes. */
  UIW GetSizeBytes();

  /* Function run every main loop cycle to check the system status. */
  virtual void DiagnoseProblems();

  /* Sets up the Room. */
  virtual const Op* Init(Crabs* crabs);

  /* Handler for shut down event. */
  virtual void ShutDown();

  /* Handler go to sleep event. */
  virtual void Sleep();

  /* Handler for wake from sleep event. */
  virtual void Wake();

  /* Handler for recovering from an external crash message. */
  virtual void Crash();

  /* Main program loop. */
  virtual const Op* Loop();

  /* Returns true if the Room is on. */
  virtual BOL IsOn();

  /* The default main function.
      Please feel free to override this with your own main function. */
  virtual SI4 Main(const CH1** args, SI4 args_count);

  /* Handles Script Commands.
      @param text     Beginning of the Text socket.
      @param text_end End of the Text socket.
      @return Returns nil upon success and an error  upon failure. */
  virtual CH1 CommandNext();

  /* Script2 operations. */
  virtual const Op* Star(CH4 index, Crabs* crabs);

#if USING_SCRIPT2_TEXT
  /* Prints the Room to the stdout. */
  virtual UTF1& Print(UTF1& utf);
#endif

 protected:
  SI4 state_count_,                 //< Number of FSM states.
      state_;                       //< Room state.
  const CH1* name_;                 //< Room Name.
  TMap<Wall*, SI4, int_t>* walls_;  //< Walls in the Room.
  Crabs* expr_;                     //< Current Crabs being executed.
                                    //< DC1: this.
  Door* this_;                      //< DC2: The Door to this room.
  Operand *xoff_,                   //< DC3: XOFF - XOFF handling device.
      *device_,                     //< DC4: the current device control.
      *devices_;                    //< Pointer to the current device control.
  UIW origin[kFloorSizeWords];      //< Room Floor socket.

 private:
  /* Sets the Room state_. */
  BOL SetState(SI4 new_state);
};

/* Returns the Room-Level Script. */
// LIB_MEMBER Room* ChineseRoom (Room* room = nullptr);

}  // namespace _
#endif
#endif
