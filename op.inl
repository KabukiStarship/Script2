/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /op.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>
#if SEAM >= SCRIPT2_DIC
#include "bsq.h"
#include "op.h"
#include "slot.h"
#include "test.h"

#if SEAM == SCRIPT2_DIC
#include "_debug.inl"
#else
#include "_release.inl"
#endif

namespace _ {

#if USING_SCRIPT2_TEXT
UTF1& Print(UTF1& utf, const Op* op) {
  if (!op) {
    return utf << "\nOp: nil";
  }
  return utf << "\nOp      :" << op->name << "\nBSQ     :" << Bsq(op->in)
             << "\nResult: :" << Bsq(op->out)
             << "\nMetadata:" << op->description;
}
#endif
/*
#if USING_SCRIPT2_TEXT
Op OpInit (UIW* socket, ISC buffer_size) {
    BOut* bout = BOutInit (socket, buffer_size);
    Op log;
    log.bout = bout;
    return log;
}

void Print (Op& log) {
    BIn    * bin = reinterpret_cast<BIn*> (log.bout);
    void   * args[1];
    IUA     type = 0,
    ui1;
    IUB ui2;
    IUC ui4;
    IUD ui8;
    //ISA   reserved,
    ISA   si1;
    IUB si2;
    IUC si4;
    IUD si8;
    FPC    flt;
    FPD   dbl;
    CHA   index;
    //if (BinReadChar (reinterpret_cast<BIn*> (log.bout), index))
    //    return;
    CHA socket[DBL_MAX_10_EXP + 2];
    while (index ) {
        switch (type) {
            case kSTR: {
                if (BinRead (bin, Params<2, kADR, kSTR> (), Args (args, &ui1,
                             socket)))
                    return;
                Write (socket);
            }
            case cISA: {
                if (BinRead (bin, Params<2, kADR, cISA> (), Args (args, &si1)))
                    return;
                Write (si1);
            }
            case cIUA: {
                if (BinRead (bin, Params<2, kADR, cIUA> (), Args (args, &ui1)))
                    return;
                Write (si1);
            }
            case cBOL: {
                if (BinRead (bin, Params<2, kADR, cISA> (), Args (args, &si1)))
                    return;
                Write (si1);
            }
            case cISB: {
                if (BinRead (bin, Params<2, kADR, cISB> (), Args (args, &si2)))
                    return;
                Write (si1);
            }
            case cIUB: {
                if (BinRead (bin, Params<2, kADR, cIUB> (),
                             Args (args, &ui2, socket)))
                    return;
                Write (si1);
            }
            case cISC: {
                if (BinRead (bin, Params<2, kADR, cISC> (),
                             Args (args, &si4, socket)))
                    return;
                Write (si1;
            }
            case cIUC: {
                if (BinRead (bin, Params<2, kADR, cIUC> (), Args (args, &ui4)))
                    return;
                Write (si1;
            }
            case cISD: {
                if (BinRead (bin, Params<2, kADR, cISD> (), Args (args, &si8)))
                    return;
                Write (si8;
            }
            case cIUD: {
                if (BinRead (bin, Params<2, kADR, cIUD> (), Args (args, &ui8)))
                 return;
                Write (ui8;
            }
            case kTM4: {
                if (BinRead (bin, Params<2, kADR, kTM4> (), Args (args, &ui4)))
                    return;
                ClockPrintTime (ui4);
            }
            case kTM8: {
                if (BinRead (bin, Params<2, kADR, kTM8> (), Args (args, &ui8)))
                    return;
                ClockPrintTimestamp (ui8);
            }
            case cFPC: {
                if (BinRead (bin, Params<2, kADR, cFPC> (), Args (args, &flt)))
                    return;
                Write (si1;
            }
            case cFPD: {
                if (BinRead (bin, Params<2, kADR, kSTR> (), Args (args, &dbl)))
                    return;
                Write (si1;
            }
        }
    }
}
#endif */

}  // namespace _

#endif  //> #if SEAM >= SCRIPT2_DIC
