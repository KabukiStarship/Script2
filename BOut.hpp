// Copyright Kabuki Starship� <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_BOUT_INLINE_CODE
#define SCRIPT2_BOUT_INLINE_CODE
#include "BOut.h"
#if SEAM >= SCRIPT2_CRABS
namespace _ {

inline CHA* BOutBegin(BOut* bout) { return TPtr<CHA>(bout) + sizeof(BOut); }

template<typename Printer>
Printer& TBOutPrint(Printer& printer, BOut* bout) {
  A_ASSERT(bout);
  ISN size = bout->size;
  printer << Linef('_', 80) << "\nBOut: size:" << size
          << " start:" << bout->origin << " stop:" << bout->stop
          << " read:" << bout->read << Charsf(BOutBoofer(bout), size - 1);
  return printer;
}
}  //< namespace _
#endif
#endif
