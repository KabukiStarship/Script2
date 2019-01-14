/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_operand.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>
#if SEAM >= _0_0_0__14
#include "cop.h"
#include "coperand.h"
#include "cstr1.h"

#if SEAM == _0_0_0__14
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

const CH1* OperandName(Operand* operand) {
  ASSERT(operand);
  const Op* op = operand->Star('?', nullptr);
  ASSERT(op);

  return op->name;
}

UIW OperandCount(Operand* operand) {
  ASSERT(operand);
  const Op* op = operand->Star(0, nullptr);
  return (op == nullptr) ? 0 : reinterpret_cast<UIW>(op->in);
}

CHW OperandIndex(Operand* operand, CH1* begin, CH1* stop) {
  ASSERT(operand);
  const Op* op = operand->Star('?', nullptr);
  ASSERT(op);
  CHW index = OpFirst(op), last = OpLast(op);
  ASSERT(index);
  for (; index <= last; ++index) {
    if (StringEquals(begin, stop, operand->Star(index, nullptr)->name)) {
      return index;
    }
  }
  return 0;
}

#if USING_CRABS_TEXT
/*
Utf& Print (Utf& utf, const Operand* op) {
    utf << "\n Op:\n" << op->name << "\nparams_in:"
          << Bsq (op->in)
          << "\nparams_out:" << op->out
          << "\npop:" << op->pop  << " close:" << op->close
          << " default_op:"       << op->default_op
          << "\nignore_chars :"   << op->ignore_chars
          << "\nallowed_chars:"   << op->allowed_chars
          << "\n description :\"" << op->description;
    return utf;
}*/

UTF1& PrintOperand(UTF1& utf, Operand* operand) {
  ASSERT(operand);

  const Op* op = operand->Star('?', nullptr);

  ASSERT(op);

  UIW num_ops = reinterpret_cast<UIW>(op->in),
      op_num = reinterpret_cast<UIW>(op->out), last_op = op_num + num_ops - 1;
  if (num_ops > kParamsMax) {
    return utf << "\nError: Too many parameters!";
  }
  utf << "\nOperand         :" << op->name << Line('-', 80);
  for (; op_num <= last_op; ++op_num) {
    op = operand->Star((CHW)op_num, nullptr);
    utf << "\nOp \'" << op_num << "\':" << op_num << ' ' << op << Line('-', 80);
  }
  return utf;
}

Slot& OperandQuery(Operand* root, const CH1* address, Slot& slot) {
  ASSERT(address);
  ASSERT(root);

  SI4 index = *address++;
  const Op* op = root->Star(index, nullptr);
  CH1 socket[1024];
  PRINTF("%s", op->name)
  index = *address++;
  while (index) {
    op = root->Star(index, nullptr);
    ASSERT(op);
    PRINTF(".%s", op->name)
    index = *address++;
  }
  slot.Write(socket);
  return slot;
}
#endif
}  // namespace _

#endif  //> #if SEAM >= _0_0_0__14
