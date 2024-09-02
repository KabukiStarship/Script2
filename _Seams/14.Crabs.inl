/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/15.Crabs.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_CRABS
#include "../Crabs.h"
using namespace _;
#if SEAM == SCRIPT2_CRABS
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif

namespace Script2 {
static const CHA* Crabs(const CHA* args) {
#if SEAM == SCRIPT2_CRABS
  A_TEST_BEGIN;

  enum {
    BufferSize = 2048,
    BufferWords = BufferSize / sizeof(IUW),
    StackHeight = 8,
  };
  IUW boofer[BufferWords], unpacked_expr[BufferWords];
  D_COUT("\n|  - Running OperationTests in address ranges: [0x"
         << Hexf(&boofer[0]) << ":0x" << Hexf(&boofer[BufferWords - 1]));

  This a;

  Crabs* crabs = CrabsInit(boofer, BufferSize, StackHeight, &a,
                                    unpacked_expr, BufferSize);
  CrabsPrint(crabs);

  D_COUT("\n|    Testing Root (@see \"a.h\")...\n");

  void* args[4];
  uint8_t io_number_ = 98;  //< ASCII:'b'
  Bin* bin = CrabsBin(crabs);
  Bout* bout = CrabsBout(crabs);

  const Op* result;
  CrabsRingBell(crabs);
  CrabsAckBack(crabs);
  result =
      BoutWrite(bout, Params<4, ADR, IUA, CHA*, Parent::cTextBufferSize, ADR>(),
                Args(args, Address<'A', 'A', 'A'>(), &io_number_, Const("Test"),
                     Address<BS, CR>()));
  BoutPrint(bout);
  A_ASSERT(!result);

  CrabsPrint(crabs);

  // Mirror mirror (bin, bout);
  // Bypass handshake for testing purposes.
  CrabsScan(crabs);  //, &mirror);
  CrabsPrint(crabs);
  D_COUT("\n| Done with Operation tests.");
#endif
  return nullptr;
}
}  //< namespace Script2
