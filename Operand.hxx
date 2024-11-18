// Copyright Kabuki Starship <kabukistarship.com>.
#include "Operand.h"
#if SEAM >= SCRIPT2_CRABS
#include "Op.hpp"
#if SEAM == SCRIPT2_CRABS
#include "_Debug.hxx"
#else
#include "_Release.hxx"
#endif
namespace _ {

const CHA* OperandName(Operand* operand) {
  A_ASSERT(operand);
  const Op* op = operand->Star('?', nullptr);
  A_ASSERT(op);

  return op->name;
}

IUW OperandCount(Operand* operand) {
  A_ASSERT(operand);
  const Op* op = operand->Star(0, nullptr);
  return (op == nullptr) ? 0 : IUW(op->in);
}

CHC OperandIndex(Operand* operand, CHA* origin, CHA* stop) {
  A_ASSERT(operand);
  const Op* op = operand->Star('?', nullptr);
  A_ASSERT(op);
  CHC index = OpFirst(op),
      last  = OpLast (op);
  A_ASSERT(index);
  for (; index <= last; ++index) {
    if (TSTREquals<CHA>(origin, stop, operand->Star(index, nullptr)->name)) {
      return index;
    }
  }
  return 0;
}

#if USING_SCRIPT2_TEXT
/*
UTF& Print (UTF& utf, const Operand* op) {
    utf << "\n Op:\n" << op->name << "\nparams_in:"
          << BSeq (op->in)
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

  IUW num_ops = IUW(op->in),
      op_num = IUW(op->out), last_op = op_num + num_ops - 1;
  if (num_ops > ParamsTotal) {
    return utf << "\nError: Too many parameters!";
  }
  utf << "\nOperand         :" << op->name << Line('-', 80);
  for (; op_num <= last_op; ++op_num) {
    op = operand->Star((CHC)op_num, nullptr);
    utf << "\nOp \'" << op_num << "\':" << op_num << ' ' << op << Line('-', 80);
  }
  return utf;
}

Slot& OperandQuery(Operand* root, const CHA* address, Slot& slot) {
  A_ASSERT(address);
  A_ASSERT(root);

  ISC index = *address++;
  const Op* op = root->Star(index, nullptr);
  CHA socket[1024];
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
}  //< namespace _
#endif
