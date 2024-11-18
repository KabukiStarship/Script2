// Copyright Kabuki Starship <kabukistarship.com>.
#include "Op.h"
#if SEAM >= SCRIPT2_DIC
#include "BSeq.hpp"
#include "Slot.h"
#include "Test.h"
#if SEAM == SCRIPT2_DIC
#include "_Debug.hxx"
#else
#include "_Release.hxx"
#endif
namespace _ {

/*
#if USING_SCRIPT2_TEXT
Op OpInit (IUW* socket, ISC boofer_size) {
    BOut* bout = BOutInit (socket, boofer_size);
    Op log;
    log.bout = bout;
    return log;
}

void Print (Op& log) {
  BIn    * bin = TPtr<BIn> (log.bout);
  void   * args[1];
  IUA     type = 0,
  iua;
  IUB iub;
  IUC iuc;
  IUD iud;
  //ISA   reserved,
  ISA   si1;
  IUB si2;
  IUC si4;
  IUD si8;
  FPC    flt;
  FPD   dbl;
  CHA   index;
  //if (BinReadChar (TPtr<BIn> (log.bout), index))
  //    return;
  CHA socket[DBL_MAX_10_EXP + 2];
  while (index ) {
    switch (type) {
      case STR_: {
        if (BinRead (bin, Params<2, _ADR, STR_> (), Args (args, &iua,
                     socket)))
          return;
        Write (socket);
      }
      case _ISA: {
        if (BinRead (bin, Params<2, _ADR, _ISA> (), Args (args, &si1)))
          return;
        Write (si1);
      }
      case _IUA: {
        if (BinRead (bin, Params<2, _ADR, _IUA> (), Args (args, &iua)))
          return;
        Write (si1);
      }
      case _BOL: {
        if (BinRead (bin, Params<2, _ADR, _ISA> (), Args (args, &si1)))
          return;
        Write (si1);
      }
      case _ISB: {
        if (BinRead (bin, Params<2, _ADR, _ISB> (), Args (args, &si2)))
          return;
        Write (si1);
      }
      case _IUB: {
        if (BinRead (bin, Params<2, _ADR, _IUB> (),
                      Args (args, &iub, socket)))
          return;
        Write (si1);
      }
      case _ISC: {
        if (BinRead (bin, Params<2, _ADR, _ISC> (),
                      Args (args, &si4, socket)))
          return;
        Write (si1;
      }
      case _IUC: {
        if (BinRead (bin, Params<2, _ADR, _IUC> (), Args (args, &iuc)))
            return;
        Write (si1;
      }
      case _ISD: {
        if (BinRead (bin, Params<2, _ADR, _ISD> (), Args (args, &si8)))
            return;
        Write (si8;
      }
      case _IUD: {
        if (BinRead (bin, Params<2, _ADR, _IUD> (), Args (args, &iud)))
          return;
        Write (iud;
      }
      case kTMC: {
        if (BinRead (bin, Params<2, _ADR, kTMC> (), Args (args, &iuc)))
          return;
        ClockPrintTime (iuc);
      }
      case kTMD: {
        if (BinRead (bin, Params<2, _ADR, kTMD> (), Args (args, &iud)))
          return;
        ClockPrintTimestamp (iud);
      }
      case _FPC: {
        if (BinRead (bin, Params<2, _ADR, _FPC> (), Args (args, &flt)))
          return;
        Write (si1;
      }
      case _FPD: {
        if (BinRead (bin, Params<2, _ADR, STR_> (), Args (args, &dbl)))
          return;
        Write (si1;
      }
    }
  }
}
#endif */

}  //< namespace _

#endif  //> #if SEAM >= SCRIPT2_DIC
