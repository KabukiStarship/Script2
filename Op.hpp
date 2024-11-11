// Copyright Kabuki Starship� <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_OP_INLINE_CODE
#define SCRIPT2_OP_INLINE_CODE
#include "Op.h"
#if SEAM >= SCRIPT2_CRABS
#include "String.hpp"
namespace _ {

template<typename Printer>
Printer& TOpPrint(Printer& o, const Op* op) {
  if (!op) {
    return o << "\nOp: nil";
  }
  return o << "\nOp      :" << op->name 
           << "\nBSQ     :" << TBSeq<ISC, DTB>(op->in)
           << "\nResult: :" << TBSeq<ISC, DTB>(op->out)
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

template<typename CHT, typename ISZ>
inline ::_::TSPrinter<CHT, ISZ>& operator<<(::_::TSPrinter<CHT, ISZ>& utf,
                                            const ::_::Op* op) {
  return ::_::TOpPrint<::_::TSPrinter<CHT, ISZ>>(utf, op);
}
#endif
#endif
