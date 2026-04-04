// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_OP_HPP
#define CRABS_OP_HPP
#include "Op.h"
#include "BSeq.hpp"
#if SEAM >= CRABS_OP
#include "String.hpp"
namespace _ {

template<typename Printer>
Printer& TOpPrint(Printer& o, const Op* op) {
  if (IsError(op)) {
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

template<typename CHS, typename CHT, typename ISZ>
inline ::_::TSPrinter<CHS, CHT, ISZ>& operator<<(::_::TSPrinter<CHS, CHT, ISZ>& utf,
                                            const ::_::Op* op) {
  return ::_::TOpPrint<::_::TSPrinter<CHS, CHT, ISZ>>(utf, op);
}
#endif
#endif
