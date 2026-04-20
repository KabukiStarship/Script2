// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_OP_DECL
#define CRABS_OP_DECL
#include <_Config.h>
#if SEAM >= CRABS_OP
namespace _ {

struct BOut;

//enum {
//  CROpPush          = 0, //< Operation Type 0: Stack push .
//  CROpOperation     = 1, //< Operation Type 1: Abstract Operation.
//  CROpOperationPush = 2, //< Operation Type 2: Operation with stack push.
//};

/* An expression Operation with name key, multiple input params,
result, and optional description of a data set.
@code
static const Op This = { "Key",
    Params<1, 2>::Header, Params<1, 2>::Header,
    "Description", '}', ';', ' ', NILP, "-", NILP };

static const Op OpExample =   { "Key2",
    NumOps (0), FirstOp ('A'),
    "Description", '}', ';', ' ', NILP, "-", NILP };
@endcode */
struct Op {
  const CHR * name;           //< Op name.
  const DTB * in,             //< Input _BSQ params or OpFirst.
            * out;            //< Output _BSQ params or OpLast.
  const CHR * description;    //< Op description.
  CHR         pop,            //< Index of the Pop Operation.
              close,          //< Index of the Close Operation.
              default_op;     //< Index of the Default Operation.
  const BOut* evaluation;     //< Evaluated expression Slot.
};

const Op* OpError(ERC error);

}  //< namespace _

#endif
#endif
