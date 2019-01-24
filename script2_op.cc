/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_op.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>
#if SEAM >= SCRIPT2_14
#include "cop.h"

#include "cbsq.h"
#include "cslot.h"
#include "cstr1.h"
#include "ctest.h"

#if SEAM == SCRIPT2_14
#include "global_debug.inl"
#else
#include "global_release.inl"
#endif

namespace _ {

#if USING_CRABS_TEXT
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
#if USING_CRABS_TEXT
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
    FLT    flt;
    DBL   dbl;
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
            case kFLT: {
                if (BinRead (bin, Params<2, kADR, kFLT> (), Args (args, &flt)))
                    return;
                Write (si1;
            }
            case kDBL: {
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
