// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_BIN_TEMPLATES
#define SCRIPT2_BIN_TEMPLATES
#include "BIn.h"
#if SEAM >= SCRIPT2_CRABS
namespace _ {

#if USING_SCRIPT2_TEXT == YES_0

/* Print the BIn to the printer. */
template<typename Printer>
Printer& TBInPrint(Printer& printer, BIn* bin) {
  ISN size = bin->size;
  return printer << Linef('_', 80) << " size:" << bin->size
                 << " start:" << bin->origin << " stop:" << bin->stop
                 << " read:" << bin->read;
  printer << Hexf(BInBegin(bin), size + sizeof(BIn));
}

template<typename CHT=CHR>
const CHT* TBInStates() {
  static const CHT StateStrings[BInStateInvalid + 1][16] = {
    /*00*/{'A','d','d','r','e','s','s'},
    /*01*/{'P','a','c','k','e','d',' ','A','r','g','s'},
    /*02*/{'P','a','c','k','e','d',' ','U','T','F','8'},
    /*03*/{'P','a','c','k','e','d',' ','U','T','F','1','6'},
    /*04*/{'P','a','c','k','e','d',' ','U','T','F','3','2'},
    /*05*/{'P','a','c','k','e','d',' ','V','a','r','i','n','t'},
    /*06*/{'P','a','c','k','e','d',' ',' ','O','b','j'},
    /*07*/{'V','e','r','i','f','y','i','n','g',' ','H','a','s','h'},
    /*08*/{'H','a','n','d','l','i','n','g',' ','E','r','r','o','r'},
    /*09*/{'D','i','s','c','o','n','n','e','c','t','e','d'},
    /*10*/{'A','c','k'},
    /*11*/{'L','o','c','k','e','d'},
    /*12*/{'P','a','c','k','e','d',' ','P','O','D'},
    /*13*/{'I','n','v','a','l','i','d' }
  };
  return &StateStrings[0][0];
}
template<typename CHT=CHR, typename IS=ISW>
inline const CHT* TBInStates(IS state) {
  if (state < 0 || state >= BInStateInvalid) state = BInStateInvalid;
  return &TBInStates<CHT>()[BInStateInvalid * 32];
}
#endif

inline IUA* BInBegin(BIn* bin) { return TPtr<IUA>(bin, sizeof(BIn)); }

}  //< namespace _

#endif
#endif
