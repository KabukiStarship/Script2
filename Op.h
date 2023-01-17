/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Op.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef INCLUDED_SCRIPT2_OP_DECL
#define INCLUDED_SCRIPT2_OP_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "String.hpp"
namespace _ {
// enum {
//    cOpPush          = 0, //< Operation Type 0: Stack push .
//    cOpOperation     = 1, //< Operation Type 1: Abstract Operation.
//    cOpOperationPush = 2, //< Operation Type 2: Operation with stack push.
//};
struct BOut;
/* An expression Operation with name key, multiple input params,
result, and optional description of a data set.
@code
static const Op cThis = { "Key",
    Params<1, 2>::Header, Params<1, 2>::Header,
    "Description", '}', ';', ' ', nullptr, "-", nullptr };

static const Op kOpExample =   { "Key2",
    NumOps (0), FirstOp ('A'),
    "Description", '}', ';', ' ', true, nullptr, "-", nullptr };
@endcode */
struct LIB_MEMBER Op {
  const CHA* name;          //< Op name.
  const ISC* in,            //< Input cBSQ params or OpFirst.
      * out;                //< Output cBSQ params or OpLast.
  const CHA* description;   //< Op description.
  CHC pop,                  //< Index of the Pop Operation.
      close,                //< Index of the Close Operation.
      default_op;           //< Index of the Default Operation.
  BOL using_numbers;        //< Flag for if tokens may use numbers.
  const CHA* ignore_chars,  //< String of chars to ignore.
    * allowed_chars;        //< String of allowed symbols.
  const BOut* evaluation;   //< Evaluated expression Slot.
};

inline const Op* OpError(Error error) { return reinterpret_cast<const Op*>(error); }


}  //< namespace _

#endif
#endif
