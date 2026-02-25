// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_BOUT_HPP
#define CRABS_BOUT_HPP
#include "BOut.h"
#if SEAM >= CRABS_OPERATION
#if SEAM == CRABS_OPERATION
#include "_Debug.h"
#else
#include "_Release.h"
#endif
namespace _ {

template<typename Printer>
Printer& TBOutPrint(Printer& o, const BOut* bout) {
  A_ASSERT(bout);
  ISN size = bout->bytes;
  o << Linef("\n___") << "\nBOut: size:" << size
    << " origin:" << bout->origin << " stop:" << bout->stop
    << " read:" << bout->read << Charsf(BOutBegin(bout), size - 1);
  return o;
}

template<typename Printer>
Printer& TBOutPrintVars(Printer& printer, BOut* bout) {
  A_ASSERT(bout);
  ISN size = bout->bytes;
  return printer << Linef('_', 80) << "\nBOut: size:" << size
    << " start:" << bout->origin << " stop:" << bout->stop
    << " read:" << bout->read;
}

template<typename Printer>
Printer& TBOutPrint(Printer& printer, BOut* bout) {
  A_ASSERT(bout);
  ISN size = bout->bytes;
  return printer << Linef('_', 80) << "\nBOut: size:" << size
          << " start:" << bout->origin << " stop:" << bout->stop
          << " read:" << bout->read << Charsf(BOutBoofer(bout), size - 1);
}
}  //< namespace _
#endif
#endif
