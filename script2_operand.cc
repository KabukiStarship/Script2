/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_operand.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
#include "c_op.h"
#include "c_operand.h"

#if SEAM == SCRIPT2_DICTIONARY
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

const CH1* OperandName(Operand* operand) {
  A_ASSERT(operand);
  const Op* op = operand->Star('?', nullptr);
  A_ASSERT(op);

  return op->name;
}

UIW OperandCount(Operand* operand) {
  A_ASSERT(operand);
  const Op* op = operand->Star(0, nullptr);
  return (op == nullptr) ? 0 : reinterpret_cast<UIW>(op->in);
}

CH4 OperandIndex(Operand* operand, CH1* begin, CH1* stop) {
  A_ASSERT(operand);
  const Op* op = operand->Star('?', nullptr);
  A_ASSERT(op);
  CH4 index = OpFirst(op), last = OpLast(op);
  A_ASSERT(index);
  for (; index <= last; ++index) {
    if (STREquals(begin, stop, operand->Star(index, nullptr)->name)) {
      return index;
    }
  }
  return 0;
}

#if USING_SCRIPT2_TEXT
/*
UTF& Print (UTF& utf, const Operand* op) {
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
  A_ASSERT(operand);

  const Op* op = operand->Star('?', nullptr);

  A_ASSERT(op);

  UIW num_ops = reinterpret_cast<UIW>(op->in),
      op_num = reinterpret_cast<UIW>(op->out), last_op = op_num + num_ops - 1;
  if (num_ops > kParamsMax) {
    return utf << "\nError: Too many parameters!";
  }
  utf << "\nOperand         :" << op->name << Line('-', 80);
  for (; op_num <= last_op; ++op_num) {
    op = operand->Star((CH4)op_num, nullptr);
    utf << "\nOp \'" << op_num << "\':" << op_num << ' ' << op << Line('-', 80);
  }
  return utf;
}

Slot& OperandQuery(Operand* root, const CH1* address, Slot& slot) {
  A_ASSERT(address);
  A_ASSERT(root);

  SI4 index = *address++;
  const Op* op = root->Star(index, nullptr);
  CH1 socket[1024];
  D_COUT(op->name)
  index = *address++;
  while (index) {
    op = root->Star(index, nullptr);
    A_ASSERT(op);
    D_COUT('.' << op->name)
    index = *address++;
  }
  slot.Write(socket);
  return slot;
}
#endif
}  // namespace _

#endif  //> #if SEAM >= SCRIPT2_DICTIONARY
