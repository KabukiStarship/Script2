/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_op.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>
#if SEAM >= SCRIPT2_14
#include "c_op.h"

#include "c_bsq.h"
#include "c_slot.h"
#include "c_utf1.h"
#include "c_test.h"

#if SEAM == SCRIPT2_14
#include "module_debug.inl"
#else
#include "module_release.inl"
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
            case kSI1: {
                if (BinRead (bin, Params<2, kADR, kSI1> (), Args (args, &si1)))
                    return;
                Write (si1);
            }
            case kUI1: {
                if (BinRead (bin, Params<2, kADR, kUI1> (), Args (args, &ui1)))
                    return;
                Write (si1);
            }
            case kBOL: {
                if (BinRead (bin, Params<2, kADR, kSI1> (), Args (args, &si1)))
                    return;
                Write (si1);
            }
            case kSI2: {
                if (BinRead (bin, Params<2, kADR, kSI2> (), Args (args, &si2)))
                    return;
                Write (si1);
            }
            case kUI2: {
                if (BinRead (bin, Params<2, kADR, kUI2> (),
                             Args (args, &ui2, socket)))
                    return;
                Write (si1);
            }
            case kSI4: {
                if (BinRead (bin, Params<2, kADR, kSI4> (),
                             Args (args, &si4, socket)))
                    return;
                Write (si1;
            }
            case kUI4: {
                if (BinRead (bin, Params<2, kADR, kUI4> (), Args (args, &ui4)))
                    return;
                Write (si1;
            }
            case kSI8: {
                if (BinRead (bin, Params<2, kADR, kSI8> (), Args (args, &si8)))
                    return;
                Write (si8;
            }
            case kUI8: {
                if (BinRead (bin, Params<2, kADR, kUI8> (), Args (args, &ui8)))
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
            case kFP4: {
                if (BinRead (bin, Params<2, kADR, kFP4> (), Args (args, &flt)))
                    return;
                Write (si1;
            }
            case kFP8: {
                if (BinRead (bin, Params<2, kADR, kSTR> (), Args (args, &dbl)))
                    return;
                Write (si1;
            }
        }
    }
}
#endif */

}  // namespace _

#endif  //> #if SEAM >= SCRIPT2_14
