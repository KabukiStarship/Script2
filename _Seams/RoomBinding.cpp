// Copyright AStarship <https://astarship.net>.
// Focused regression: direct header use and native Room instantiation.
#include "_Config.h"
#include "../AType.hpp"
#include "../_Package.hxx"
#include "../Room.hpp"

namespace _ {
static ISW ContextEcho(void*, void*, DTW, IUW value, IUW) {
  return value;
}
template<typename Room>
static BOL FloorContract(Room& room) {
  if constexpr (requires { room.Floor(); room.ClearFloor(); }) {
    auto* floor = room.Floor();
    if (floor == NILP || floor->map.count != 0 || floor->bytes != Room::FloorSize)
      return false;
    if (TListInsert(floor, ISC(23)) != 0) return false;
    if (TListInsert(floor, FPD(-0.125)) != 1) return false;
    const auto* view = floor;
    if (TListType(view, ISC(0)) != _ISC) return false;
    if (TListType(view, ISC(1)) != _FPD) return false;
    if (*TPtr<const ISC>(TListValue(view, ISC(0))) != 23) return false;
    if (*TPtr<const FPD>(TListValue(view, ISC(1))) != -0.125) return false;
    if (TListType(view, ISC(-1)) != _NIL) return false;
    if (TListType(view, ISC(2)) != _NIL) return false;
    room.ClearFloor();
    if (floor->map.count != 0) return false;
    if (TListInsert(floor, FPC(-0.25)) != 0) return false;
    if (*TPtr<const FPC>(TListValue(view, ISC(0))) != -0.25f) return false;
    // Byte-capacity failure must leave count/top unchanged.
    const auto bytes = floor->bytes;
    const auto top = floor->top;
    const auto count = floor->map.count;
    floor->bytes = top + 1;
    const auto result = TListInsert(floor, FPD(2.5));
    const BOL unchanged = floor->top == top && floor->map.count == count;
    floor->bytes = bytes;
    room.ClearFloor();
    return result < 0 && unchanged && floor->map.count == 0;
  } else {
    return false;
  }
}
}

ISN main() {
  using namespace _;
  if (TCTXHandle<IUW>(NILP, NILP, NILP, 0, 23, 0) != 0) return 1;
  if (TCTXHandle<IUW>(ContextEcho, NILP, NILP, 0, 23, 0) != 23) return 2;
  TRoom<CHA, CHC, ISC, ISC, DTB, IUC> room("vehicle_room", 2);
  if (room.WallCount() != 0) return 3;
  if (room.GetWall(-1) != NILP || room.GetWall(0) != NILP) return 4;
  const Op* query = room.Star('?', NILP);
  if (query == NILP) return 5;
  if (room.Star(0x10ffff, NILP) == NILP) return 6;
  if (!FloorContract(room)) return 7;
  static const Op bounds = {"Bounds", OpFirst('a'), OpLast('z'),
      "Operation marker types match Op.in/out.", ';', '}', 0, NILP};
  if (OpFirst(&bounds) != 'a' || OpLast(&bounds) != 'z') return 8;
  StdOut() << "ROOM_BINDING passed\n";
  return 0;
}
