/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/15_expr.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM == SCRIPT2_SEAM_EXPR
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

#include "c_room.h"

using namespace _;

namespace script2 {
static const CH1* _15_Expr(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM == SCRIPT2_SEAM_EXPR
  TEST_BEGIN;

  enum {
    kBufferSize = 2048,
    kBufferWords = kBufferSize / sizeof(UIW),
    kStackHeight = 8,
  };
  UIW buffer[kBufferWords], unpacked_expr[kBufferWords];
  PRINTF("\n|  - Running OperationTests in address ranges: [0x%p:0x%p]\n",
         &buffer[0], &buffer[kBufferWords - 1]);

  This a;

  Expression* expr = ExpressionInit(buffer, kBufferSize, kStackHeight, &a,
                                    unpacked_expr, kBufferSize);
  ExpressionPrint(expr);

  std::cout << "\n|    Testing Root (@see \"a.h\")...\n";

  void* args[4];
  uint8_t io_number_ = 98;  //< ASCII:'b'
  Bin* bin = ExpressionBin(expr);
  Bout* bout = ExpressionBout(expr);

  const Operation* result;
  ExpressionRingBell(expr);
  ExpressionAckBack(expr);
  result =
      BoutWrite(bout, Params<4, ADR, UI1, CH1*, Parent::kTextBufferSize, ADR>(),
                Args(args, Address<'A', 'A', 'A'>(), &io_number_, Const("Test"),
                     Address<BS, CR>()));
  BoutPrint(bout);
  ASSERT(!result);

  ExprPrint(expr);

  // Mirror mirror (bin, bout);
  // Bypass handshake for testing purposes.
  ExpressionScan(expr);  //, &mirror);
  ExpressionPrint(expr);
  std::cout << "\n| Done with Operation tests.";
#endif
  return nullptr;
}
}  // namespace script2
