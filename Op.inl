/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Op.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
#include "BSeq.h"
#include "Op.h"
#include "Slot.h"
#include "Test.h"
#if SEAM == SCRIPT2_DIC
#include "_Debug.inl"
#else
#include "_Release.inl"
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
                if (BinRead (bin, Params<2, cADR, STR_> (), Args (args, &iua,
                             socket)))
                    return;
                Write (socket);
            }
            case cISA: {
                if (BinRead (bin, Params<2, cADR, cISA> (), Args (args, &si1)))
                    return;
                Write (si1);
            }
            case cIUA: {
                if (BinRead (bin, Params<2, cADR, cIUA> (), Args (args, &iua)))
                    return;
                Write (si1);
            }
            case cBOL: {
                if (BinRead (bin, Params<2, cADR, cISA> (), Args (args, &si1)))
                    return;
                Write (si1);
            }
            case cISB: {
                if (BinRead (bin, Params<2, cADR, cISB> (), Args (args, &si2)))
                    return;
                Write (si1);
            }
            case cIUB: {
                if (BinRead (bin, Params<2, cADR, cIUB> (),
                             Args (args, &iub, socket)))
                    return;
                Write (si1);
            }
            case cISC: {
                if (BinRead (bin, Params<2, cADR, cISC> (),
                             Args (args, &si4, socket)))
                    return;
                Write (si1;
            }
            case cIUC: {
                if (BinRead (bin, Params<2, cADR, cIUC> (), Args (args, &iuc)))
                    return;
                Write (si1;
            }
            case cISD: {
                if (BinRead (bin, Params<2, cADR, cISD> (), Args (args, &si8)))
                    return;
                Write (si8;
            }
            case cIUD: {
                if (BinRead (bin, Params<2, cADR, cIUD> (), Args (args, &iud)))
                 return;
                Write (iud;
            }
            case kTMC: {
                if (BinRead (bin, Params<2, cADR, kTMC> (), Args (args, &iuc)))
                    return;
                ClockPrintTime (iuc);
            }
            case kTMD: {
                if (BinRead (bin, Params<2, cADR, kTMD> (), Args (args, &iud)))
                    return;
                ClockPrintTimestamp (iud);
            }
            case cFPC: {
                if (BinRead (bin, Params<2, cADR, cFPC> (), Args (args, &flt)))
                    return;
                Write (si1;
            }
            case cFPD: {
                if (BinRead (bin, Params<2, cADR, STR_> (), Args (args, &dbl)))
                    return;
                Write (si1;
            }
        }
    }
}
#endif */

}  //< namespace _

#endif  //> #if SEAM >= SCRIPT2_DIC
