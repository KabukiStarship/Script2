/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /15_expr.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM == SCRIPT2_EXPR
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

#include "c_room.h"

using namespace _;

namespace script2 {
static const CH1* Expr(const CH1* args) {
#if SEAM == SCRIPT2_EXPR
  A_TEST_BEGIN;

  enum {
    kBufferSize = 2048,
    kBufferWords = kBufferSize / sizeof(UIW),
    kStackHeight = 8,
  };
  UIW buffer[kBufferWords], unpacked_expr[kBufferWords];
  D_COUT("\n|  - Running OperationTests in address ranges: [0x"
         << Hexf(&buffer[0]) << ":0x" << Hexf(&buffer[kBufferWords - 1]));

  This a;

  Expression* expr = ExpressionInit(buffer, kBufferSize, kStackHeight, &a,
                                    unpacked_expr, kBufferSize);
  ExpressionPrint(expr);

  D_COUT("\n|    Testing Root (@see \"a.h\")...\n");

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
  A_ASSERT(!result);

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
