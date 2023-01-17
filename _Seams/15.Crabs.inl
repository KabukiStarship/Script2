/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/15.Crabs.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

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
    cBufferSize = 2048,
    cBufferWords = cBufferSize / sizeof(IUW),
    cStackHeight = 8,
  };
  IUW buffer[cBufferWords], unpacked_expr[cBufferWords];
  D_COUT("\n|  - Running OperationTests in address ranges: [0x"
         << Hexf(&buffer[0]) << ":0x" << Hexf(&buffer[cBufferWords - 1]));

  This a;

  Crabs* crabs = CrabsInit(buffer, cBufferSize, cStackHeight, &a,
                                    unpacked_expr, cBufferSize);
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
