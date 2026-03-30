// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_PUFF_DECL
#define CRABS_PUFF_DECL
#include <_Config.h>
#if SEAM >= CRABS_ITOS
namespace _ {

/* Lookup table of ASCII CHS pairs for 00, 01, ..., 99. */
const IUB* BinaryLUTDecimals();

enum {
  UI2DigitTotal = 5,
  UI4DigitTotal = 9,
  UI8DigitTotal = 20,
};

const IUD* Pow10_UI8();
IUD Pow10(IUD index);

const IUC* Pow10_UI4();
IUC Pow10(IUC index);

const IUB* Pow10_UI2();
IUB Pow10(IUB index);

/* Finds the string length of the given value. */
ISC STRLength(IUB value);
ISC STRLength(ISB value);
ISC STRLength(IUC value);
ISC STRLength(ISC value);
ISC STRLength(IUD value);
ISC STRLength(ISD value);

#if SEAM >= CRABS_FTOS

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
ISC FloatDigitsMax();

/* Checks if the given value is not NaN or +/- Infinity. */
BOL IsFinite(FPC value);

/* Checks if the given value is not NaN or +/- Infinity. */
BOL IsInfinite(FPC value);

/* Returns the ceiling of the given value to the next highest up integer. */
FPC Ceiling(FPC value);
#endif

#if USING_FPD == YES_0
/* Gets the maximum number_ of digits required to represent a FPD as in
ASCII. */
ISC DoubleDigitsMax();

/* Checks if the given value is not NaN or +/- Infinity. */
BOL IsFinite(FPD value);

/* Returns the ceiling of the given value to the next highest up integer. */
BOL IsInfinite(FPD value);

/* Returns the ceiling of the given value to the next highest up integer. */
FPD Ceiling(FPD value);
#endif

#endif
}  //< namespace _
#endif
#endif
