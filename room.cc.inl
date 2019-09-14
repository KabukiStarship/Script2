/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /room.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>
#if SEAM >= SCRIPT2_ROOM
#include "bsq.h"
#include "door.h"
#include "room.h"
#include "stack.h"
#include "strand.hpp"

#if SEAM == SCRIPT2_ROOM
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

const CH1** RoomStateTexts() {
  static const CH1* states[] = {"Initializing", "Waking up", "Running",
                                "Going to sleep", "Exiting"};
  return states;
}

const CH1** RequestTexts() {
  static const CH1* RequestTexts[] = {"Open door", "Close door",
                                      "Invalid request"};

  return RequestTexts;
}

const CH1* RequestText(Request r) {
  // if (r < 0 || r >= InvalidRequest)
  if (r >= InvalidRequest) return RequestTexts()[InvalidRequest];
  return RequestTexts()[r];
}

Room::Room(const CH1* room_name, SI4 state_count)
    : state_(1),
      state_count_(state_count < 1 ? 1 : state_count),
      name_(!room_name ? "Unnamed" : room_name),
      this_(nullptr),
      xoff_(nullptr),
      device_(nullptr),
      devices_(nullptr) {}

Room::~Room() {}

SI4 Room::GetState() { return state_; }

SI4 Room::GetStateCount() { return state_count_; }

BOL Room::SetState(SI4 new_state) {
  if (new_state < 0) {
    return false;
  }
  if (new_state >= state_count_) {
    return false;
  }
  state_ = new_state;
  return true;
}

const CH1* Room::GetRoomName() { return name_; }

BOL Room::SetRoomName(const CH1* name) {
  if (!name) {
    return false;
  }
  delete name_;
  name_ = StrandClone(name);
  return true;
}

Request Room::HandleNextRequest(Request r) { return InvalidRequest; }

void Room::ClearLog() {}

void Room::ProcessLog() {}

void Room::PrintErrors(BOut* bout) {
  // SI4 errorHeader[] = { 0 };
  // return a.prints (errorHeader);
}

void Room::DiagnoseProblems() {
  // Check for remote crash request.
  // throw RoomCrashException ();
}

const Op* Room::Init(Crabs* crabs) {
  if (crabs != nullptr) {
    // @todo We need to load a stored Room state.
    return nullptr;
  }
  return nullptr;
}

void Room::ShutDown() { D_COUT("\nShutting down..."); }

void Room::Sleep() { D_COUT("\nGoing to sleep..."); }

void Room::Wake() { D_COUT("\nWaking up..."); }

void Room::Crash() { D_COUT("\nRoom crash!"); }

const Op* Room::Loop() { return 0; }

BOL Room::IsOn() { return true; }

SI4 Room::Main(const CH1** args, SI4 args_count) {
  const Op* result = nullptr;
  D_COUT("\nInitializing Chinese Room with " << args_count << " args:");
#if D_THIS
  for (SI4 i = 0; i < args_count; ++i) {
    D_COUT('\n' << i << ":\"" << args[i] << '\"');
  }
#endif
  D_COUT('\n')
  while (IsOn()) {
    try {
      result = Init(nullptr);
      if (result) return 1;
      do {
        this_->ExecAll();
        result = Loop();
      } while (!result);
      ShutDown();
    } catch (...) {
      D_COUT("\nRoom crashed!")
      return 3;
    }
  }
  return 1;
}

CH1 Room::CommandNext() { return 0; }

const Op* Room::Star(CH4 index, Crabs* crabs) {
  static const Op kThis = {
      "Room", OpFirst('A'), OpLast('A'), "A Chinese Room.", ';', '}', 0};

  switch (index) {
    case '?': {
      return ExprQuery(crabs, kThis);
    }
  }
  return 0;
}

int_t Room::WallCount() { return walls_->count; }

Wall* Room::GetWall(int_t wall_number) {
  if (wall_number < 0) return nullptr;
  if (wall_number >= walls_->count) return nullptr;
  return TStackGet<Wall*, SI4, int_t>(walls_, wall_number);
}

Wall* Room::AddWall(Wall* new_wall) {
  if (new_wall == nullptr) return nullptr;
  if (walls_->count >= walls_->count_max) return nullptr;
  TStackPush<Wall*>(walls_, new_wall);
  return new_wall;
}

BOL Room::RemoveWall(int_t wall_number) {
  return TStackRemove<Wall*, SI4, int_t>(walls_, wall_number);
}

UIW Room::GetSizeBytes() {
  UIW count = kRoomFloorSize;
  for (int_t i = 0; i < walls_->count; ++i) {
    count += TStackGet<Wall*, SI4, int_t>(walls_, i)->GetSizeBytes();
  }
  // @todo Add all memory we used in bytes here.
  return count;
}

#if USING_SCRIPT2_TEXT
UTF1& Room::Print(UTF1& utf) { return utf << "\nRoom: "; }
#endif

}  // namespace _

#endif
