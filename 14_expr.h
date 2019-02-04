/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/14_expr.h
@author  Cale McCollough <cale@astartup.net>
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

#if SEAM == SCRIPT2_14
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

#include "c_room.h"

using namespace _;

namespace script2 {
static const CH1* _14_Expr(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM == SCRIPT2_14
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
} //< namespace script2
