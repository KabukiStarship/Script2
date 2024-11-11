// Copyright Kabuki Starship� <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_BSEQ_DELC
#define SCRIPT2_BSEQ_DELC
#include "Types.h"
#if SEAM >= SCRIPT2_CRABS
namespace _ {

/* Utility class for printing B-Sequences. */
template<typename ISY = ISN, typename DT = DTB>
struct TBSeq {
  const DT* params;  //< BSeq params.

  TBSeq(const DT* params) : params(params) {
    // Nothing to do here! (:-)-+=<
  }
};

enum {
  BSQMax = 420   //< Max number of elements in a BSQ.
};

#if CPU_SIZE == CPU_2_BYTE
inline ISB UnpackSVI(ISB value) {
  if (value < 0) {
    IUB result = 0x8000 return result | ~(value - 1);
  }
  return value;
}

inline ISB PackSVI(ISB value) {
  if (value < 0) {
    IUB result = 1 << 15;
    return result | ((~value + 1) << 1);
  }
  return value;
}
#endif

constexpr ISC CBSeqSize(const ISC* params) {
  if (!params) {
    return 0;
  }
  ISC bytes = sizeof(ISC), 
      count = *params++;

  if (count > BSQMax) {
    return 0;
  }

  for (; count > 0; --count) {
    ISC param = *params++;

    if (param == _NIL) {  // This is illegal.
      return 0;
    }
    //if (param <= _TKN) {
    //  bytes += sizeof(ISC);
    //  ++params;
    //}
    if (param == _ISE) {
      bytes += sizeof(ISC);
      ++params;
    }
    if (param == _IUE) {
      bytes += sizeof(ISC);
      ++params;
    }
    //if (param >= _LST && param <= _MAP) {  // This is illegal.
    //  return 0;
    //}
    //if (param > _MAP) {
    //  if (param >> 8) {  // This is an error.
    //    return 0;
    //  }
    //  if (param & 0x20) {     // It's a multi-dimensional array so
    //    param = *params;      // add the number_ of dimensions + 1;
    //    params += param + 1;  // for the dimension count.
    //  }
    //}
    bytes += sizeof(ISC);
  }
  return bytes;
}

/* Creates a immutable Script B-Sequence.
C++11 variadic template to ensure only one copy in ROM
and to eliminate some redundant typing. */
template<const ISC... N>
inline const ISC* TParams() {
  static const ISC Size = 0,  // BsqSize ({ N... })
      cList[sizeof...(N)] = {N...};
  return &Size;
}

/*< Returns the requested parameter number_. */
LIB_MEMBER ISC BSeqParamNumber(const ISN* bsq, ISN param_number);

}  //< namespace _

#endif
#endif
