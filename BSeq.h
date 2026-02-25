// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_BSEQ_DECL
#define CRABS_BSEQ_DECL
#include "AType.h"
#if SEAM >= CRABS_OPERATION
namespace _ {

/*< Returns the requested parameter number_. */
LIB_MEMBER ISC BSeqParamNumber(const DTB* params, ISN param_number);

}  //< namespace _

#endif
#endif
