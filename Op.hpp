/* Script2�
@link    https://github.com/KabukiStarship/Script2.git
@file    /Op.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship� <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "Op.h"
//
#include "String.hpp"
namespace _ {

template<typename Printer>
Printer& TOpPrint(Printer& printer, const Op* op) {
  if (!op) {
    return printer << "\nOp: nil";
  }
  return printer << "\nOp      :" << op->name << "\nBSQ     :" << BSeq(op->in)
                 << "\nResult: :" << BSeq(op->out)
                 << "\nMetadata:" << op->description;
}

/* Converts the given value to a pointer. */
inline ISW OpCount(const Op& op) { return op.out - op.in; }

/* Converts the given value to a pointer. */
inline const ISC* OpFirst(CHC index) { return TPtr<const ISC>(index); }

/* Converts the given value to a pointer. */
inline CHC OpFirst(const Op* op) {
  return (CHC) IUW(op->in);
}

/* Converts the given value to a pointer. */
inline const ISC* OpLast(CHC index) { return TPtr<const ISC>(index); }

/* Converts the given value to a pointer. */
inline CHC OpLast(const Op* op) {
  return CHC(IUW(op->out));
}

}  //< namespace _

template<typename CHT>
inline _::TSPrinter<CHT, ISZ>& operator<<(_::TSPrinter<CHT, ISZ>& utf,
                                      const _::Op* op) {
  return _::Print(utf, op);
}

#endif
