/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cop.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#if SEAM >= _0_0_01__13
#ifndef INCLUDED_CRABS_OP
#define INCLUDED_CRABS_OP 1

#include "tstr.h"

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
struct API Op {
  const CH1* name;          //< Op name.
  const UIT *in,             //< Input kBSQ params or OpFirst.
      *out;                  //< Output kBSQ params or OpLast.
  const CH1* description;   //< Op description.
  CHW pop,                   //< Index of the Pop Operation.
      close,                 //< Index of the Close Operation.
      default_op;            //< Index of the Default Operation.
  BOL using_numbers;         //< Flag for if tokens may use numbers.
  const CH1 *ignore_chars,  //< String of chars to ignore.
      *allowed_chars;        //< String of allowed symbols.
  const BOut* evaluation;    //< Evaluated expression Slot.
};

/* Converts the given value to a pointer. */
inline SIW OpCount(const Op& op) { return op.out - op.in; }

/* Converts the given value to a pointer. */
inline const UIT* OpFirst(CHW index) {
  return reinterpret_cast<const UIT*>(index);
}

/* Converts the given value to a pointer. */
inline CHW OpFirst(const Op* op) {
  ASSERT(op);
  return (CHW) reinterpret_cast<UIW>(op->in);
}

/* Converts the given value to a pointer. */
inline const UIT* OpLast(CHW index) {
  return reinterpret_cast<const UIT*>(index);
}

/* Converts the given value to a pointer. */
inline CHW OpLast(const Op* op) {
  ASSERT(op);
  return (CHW) reinterpret_cast<UIW>(op->out);
}

#if USING_CRABS_TEXT == YES
template <typename Char>
TUTF<Char>& Print(TUTF<Char>& utf, const Op* op) {}
#endif

}  // namespace _

template <typename Char>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, const _::Op* op) {
  return _::Print(utf, op);
}

#endif  //< #if INCLUDED_CRABS_OP 1
#endif  //< #if SEAM >= _0_0_0__14
