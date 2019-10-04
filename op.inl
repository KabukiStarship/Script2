/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /op.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

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
Op OpInit (UIW* socket, SI4 buffer_size) {
    BOut* bout = BOutInit (socket, buffer_size);
    Op log;
    log.bout = bout;
    return log;
}

void Print (Op& log) {
    BIn    * bin = reinterpret_cast<BIn*> (log.bout);
    void   * args[1];
    UI1     type = 0,
    ui1;
    UI2 ui2;
    UI4 ui4;
    UI8 ui8;
    //SI1   reserved,
    SI1   si1;
    UI2 si2;
    UI4 si4;
    UI8 si8;
    FP4    flt;
    FP8   dbl;
    CH1   index;
    //if (BinReadChar (reinterpret_cast<BIn*> (log.bout), index))
    //    return;
    CH1 socket[DBL_MAX_10_EXP + 2];
    while (index ) {
        switch (type) {
            case kSTR: {
                if (BinRead (bin, Params<2, kADR, kSTR> (), Args (args, &ui1,
                             socket)))
                    return;
                Write (socket);
            }
            case cSI1: {
                if (BinRead (bin, Params<2, kADR, cSI1> (), Args (args, &si1)))
                    return;
                Write (si1);
            }
            case cUI1: {
                if (BinRead (bin, Params<2, kADR, cUI1> (), Args (args, &ui1)))
                    return;
                Write (si1);
            }
            case cBOL: {
                if (BinRead (bin, Params<2, kADR, cSI1> (), Args (args, &si1)))
                    return;
                Write (si1);
            }
            case cSI2: {
                if (BinRead (bin, Params<2, kADR, cSI2> (), Args (args, &si2)))
                    return;
                Write (si1);
            }
            case cUI2: {
                if (BinRead (bin, Params<2, kADR, cUI2> (),
                             Args (args, &ui2, socket)))
                    return;
                Write (si1);
            }
            case cSI4: {
                if (BinRead (bin, Params<2, kADR, cSI4> (),
                             Args (args, &si4, socket)))
                    return;
                Write (si1;
            }
            case cUI4: {
                if (BinRead (bin, Params<2, kADR, cUI4> (), Args (args, &ui4)))
                    return;
                Write (si1;
            }
            case cSI8: {
                if (BinRead (bin, Params<2, kADR, cSI8> (), Args (args, &si8)))
                    return;
                Write (si8;
            }
            case cUI8: {
                if (BinRead (bin, Params<2, kADR, cUI8> (), Args (args, &ui8)))
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
            case cFP4: {
                if (BinRead (bin, Params<2, kADR, cFP4> (), Args (args, &flt)))
                    return;
                Write (si1;
            }
            case cFP8: {
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
