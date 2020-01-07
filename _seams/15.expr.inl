/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/15.expr.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_EXPR
#include "../room.h"
using namespace _;
#if SEAM == SCRIPT2_EXPR
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

namespace script2 {
static const CHA* Expr(const CHA* args) {
#if SEAM == SCRIPT2_EXPR
  A_TEST_BEGIN;

  enum {
    cBufferSize = 2048,
    cBufferWords = cBufferSize / sizeof(UIW),
    cStackHeight = 8,
  };
  UIW buffer[cBufferWords], unpacked_expr[cBufferWords];
  D_COUT("\n|  - Running OperationTests in address ranges: [0x"
         << Hexf(&buffer[0]) << ":0x" << Hexf(&buffer[cBufferWords - 1]));

  This a;

  Expression* expr = ExpressionInit(buffer, cBufferSize, cStackHeight, &a,
                                    unpacked_expr, cBufferSize);
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
      BoutWrite(bout, Params<4, ADR, IUA, CHA*, Parent::kTextBufferSize, ADR>(),
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
