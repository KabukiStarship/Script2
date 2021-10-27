/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Room.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "BSeq.h"
#include "Door.hpp"
#include "Room.h"
#include "Stack.hpp"
#include "String.hpp"
#if SEAM == SCRIPT2_CRABS
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
namespace _ {

const CHA** RoomStateTexts() {
  static const CHA* states[] = {"Initializing", "Waking up", "Running",
                                "Going to sleep", "Exiting"};
  return states;
}

const CHA** RequestTexts() {
  static const CHA* RequestTexts[] = {"Open door", "Close door",
                                      "Invalid request"};

  return RequestTexts;
}

const CHA* RequestText(Request r) {
  // if (r < 0 || r >= InvalidRequest)
  if (r >= InvalidRequest) return RequestTexts()[InvalidRequest];
  return RequestTexts()[r];
}

Room::Room(const CHA* room_name, ISC state_count)
    : state_(1),
      state_count_(state_count < 1 ? 1 : state_count),
      name_(!room_name ? "Unnamed" : room_name),
      this_(nullptr),
      xoff_(nullptr),
      device_(nullptr),
      devices_(nullptr) {}

Room::~Room() {}

ISC Room::GetState() { return state_; }

ISC Room::GetStateCount() { return state_count_; }

BOL Room::SetState(ISC new_state) {
  if (new_state < 0) {
    return false;
  }
  if (new_state >= state_count_) {
    return false;
  }
  state_ = new_state;
  return true;
}

const CHA* Room::GetRoomName() { return name_; }

BOL Room::SetRoomName(const CHA* name) {
  if (!name) {
    return false;
  }
  delete name_;
  name_ = StringClone(name);
  return true;
}

Request Room::HandleNextRequest(Request r) { return InvalidRequest; }

void Room::ClearLog() {}

void Room::ProcessLog() {}

void Room::PrintErrors(BOut* bout) {
  // ISC errorHeader[] = { 0 };
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

ISC Room::Main(const CHA** args, ISC args_count) {
  const Op* result = nullptr;
  D_COUT("\nInitializing Chinese Room with " << args_count << " args:");
#if D_THIS
  for (ISC i = 0; i < args_count; ++i) {
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

CHA Room::CommandNext() { return 0; }

const Op* Room::Star(CHC index, Crabs* crabs) {
  static const Op cThis = {
      "Room", OpFirst('A'), OpLast('A'), "A Chinese Room.", ';', '}', 0};

  switch (index) {
    case '?': {
      return ExprQuery(crabs, cThis);
      case 'a': {
        static const Op cThis = {
          "FuncionA",
          OpFirst('A'),
          OpLast('A'),
          "Description of function a.",
          ';',
          '}',
          0
        };
        return OpPush(this, crabs);
      }
    }
  }
  return 0;
}

int_t Room::WallCount() { return walls_->count; }

Wall* Room::GetWall(int_t wall_number) {
  if (wall_number < 0) return nullptr;
  if (wall_number >= walls_->count) return nullptr;
  return TStackGet<Wall*, ISC, int_t>(walls_, wall_number);
}

Wall* Room::AddWall(Wall* new_wall) {
  if (new_wall == nullptr) return nullptr;
  if (walls_->count >= walls_->count_max) return nullptr;
  TStackInsert<Wall*>(walls_, new_wall);
  return new_wall;
}

BOL Room::RemoveWall(int_t wall_number) {
  return TStackRemove<Wall*, ISC, int_t>(walls_, wall_number);
}

IUW Room::GetSizeBytes() {
  IUW count = cRoomFloorSize;
  for (int_t i = 0; i < walls_->count; ++i) {
    count += TStackGet<Wall*, ISC, int_t>(walls_, i)->GetSizeBytes();
  }
  // @todo Add all memory we used in bytes here.
  return count;
}

#if USING_SCRIPT2_TEXT
UTF1& Room::Print(UTF1& utf) { return utf << "\nRoom: "; }
#endif

}  //< namespace _

#endif
