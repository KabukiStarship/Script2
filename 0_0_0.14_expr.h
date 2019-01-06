/* Script^2 @version 0.x
@file    /script2/0_0_0.14_room.h
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

#if SEAM == _0_0_0__14
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

#include "croom.h"

using namespace _;

static const CH1* _0_0_0__14_Expr(CH1* seam_log, CH1* seam_end,
                                  const CH1* args) {
#if SEAM == _0_0_0__14
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
      BoutWrite(bout, Params<4, ADR, UI1, STR, Parent::kTextBufferSize, ADR>(),
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
