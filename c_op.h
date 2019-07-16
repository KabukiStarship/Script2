/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_op.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_ROOM
#ifndef INCLUDED_SCRIPT2_OP
#define INCLUDED_SCRIPT2_OP 1

#include "t_strand.h"

namespace _ {

// enum {
//    kOpPush          = 0, //< Operation Type 0: Stack push .
//    kOpOperation     = 1, //< Operation Type 1: Abstract Operation.
//    KOpOperationPush = 2, //< Operation Type 2: Operation with stack push.
//};

struct BOut;

/* An expression Operation with name key, multiple input params,
    result, and optional description of a data set.
    @code
    static const Op kThis = { "Key",
        Params<1, 2>::Header, Params<1, 2>::Header,
        "Description", '}', ';', ' ', nullptr, "-", nullptr };

    static const Op kOpExample =   { "Key2",
        NumOps (0), FirstOp ('A'),
        "Description", '}', ';', ' ', true, nullptr, "-", nullptr };
    @endcode */
struct LIB_MEMBER Op {
  const CH1* name;          //< Op name.
  const SI4 *in,            //< Input kBSQ params or OpFirst.
      *out;                 //< Output kBSQ params or OpLast.
  const CH1* description;   //< Op description.
  CH4 pop,                  //< Index of the Pop Operation.
      close,                //< Index of the Close Operation.
      default_op;           //< Index of the Default Operation.
  BOL using_numbers;        //< Flag for if tokens may use numbers.
  const CH1 *ignore_chars,  //< Strand of chars to ignore.
      *allowed_chars;       //< Strand of allowed symbols.
  const BOut* evaluation;   //< Evaluated expression Slot.
};

/* Converts the given value to a pointer. */
inline SIW OpCount(const Op& op) { return op.out - op.in; }

/* Converts the given value to a pointer. */
inline const SI4* OpFirst(CH4 index) {
  return reinterpret_cast<const SI4*>(index);
}

/* Converts the given value to a pointer. */
inline CH4 OpFirst(const Op* op) {
  A_ASSERT(op);
  return (CH4) reinterpret_cast<UIW>(op->in);
}

/* Converts the given value to a pointer. */
inline const SI4* OpLast(CH4 index) {
  return reinterpret_cast<const SI4*>(index);
}

/* Converts the given value to a pointer. */
inline CH4 OpLast(const Op* op) {
  A_ASSERT(op);
  return (CH4) reinterpret_cast<UIW>(op->out);
}

#if USING_SCRIPT2_TEXT == YES
template <typename Char>
TUTF<Char>& Print(TUTF<Char>& utf, const Op* op) {}
#endif

}  // namespace _

template <typename Char>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, const ::_::Op* op) {
  return ::_::Print(utf, op);
}

#endif  //< #if INCLUDED_SCRIPT2_OP 1
#endif  //< #if SEAM >= SEAM_SCRIPT2_DIC
