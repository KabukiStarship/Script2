/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Puff.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_Config.h>

#if SEAM >= SCRIPT2_ITOS
#ifndef SCRIPT2_PUFF
#define SCRIPT2_PUFF 1

namespace _ {

/* Lookup table of ASCII CHT pairs for 00, 01, ..., 99. */
const IUB* BinaryLUTDecimals();

enum {
  cUI2DigitCountMax = 5,
  cUI4DigitCountMax = 9,
  cUI8DigitCountMax = 20,
};

const IUD* Pow10_UI8();
IUD Pow10(IUD index);

const IUC* Pow10_UI4();
IUC Pow10(IUC index);

const IUB* Pow10_UI2();
IUB Pow10(IUB index);

/* Finds the string length of the given value. */
LIB_MEMBER ISC STRLength(IUB value);
LIB_MEMBER ISC STRLength(ISB value);
LIB_MEMBER ISC STRLength(IUC value);
LIB_MEMBER ISC STRLength(ISC value);
LIB_MEMBER ISC STRLength(IUD value);
LIB_MEMBER ISC STRLength(ISD value);

#if SEAM >= SCRIPT2_FTOS

/* IEEE754 Powers of 10 integral portions LUT. */
const void* Binary32Pow10IntegralPortions();

/* IEEE754 Powers of 10 integral portions LUT. */
const void* Binary64Pow10IntegralPortions();

/* Lookup table of the IEEE754 integral portion of pre-computed powers of 10.
 */
const void* BinaryPow10Exponents();

#if USING_FPC == YES_0
/* Gets the maximum number_ of digits required to represent a FPC as in
ASCII. */
LIB_MEMBER ISC FloatDigitsMax();

/* Checks if the given value is not NaN or +/- Infinity. */
LIB_MEMBER BOL IsFinite(FPC value);

/* Checks if the given value is not NaN or +/- Infinity. */
LIB_MEMBER BOL IsInfinite(FPC value);

/* Returns the ceiling of the given value to the next highest up integer. */
LIB_MEMBER FPC Ceiling(FPC value);
#endif

#if USING_FPD == YES_0
/* Gets the maximum number_ of digits required to represent a FPD as in
ASCII. */
LIB_MEMBER ISC DoubleDigitsMax();

/* Checks if the given value is not NaN or +/- Infinity. */
LIB_MEMBER BOL IsFinite(FPD value);

/* Returns the ceiling of the given value to the next highest up integer. */
LIB_MEMBER BOL IsInfinite(FPD value);

/* Returns the ceiling of the given value to the next highest up integer. */
LIB_MEMBER FPD Ceiling(FPD value);
#endif

#endif
}  // namespace _
#endif
#endif
