/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /puff.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-9 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#if SEAM >= SCRIPT2_ITOS

#ifndef SCRIPT2_PUFF_HEADER_WITH_TEMPLATES
#define SCRIPT2_PUFF_HEADER_WITH_TEMPLATES 1

#include "binary.hpp"
#include "puff.h"
#if SEAM == SCRIPT2_ITOS
#include <iostream>
#define D_COUT(item) std::cout << item
namespace _ {
template <typename CHT = CHR>
CHT* TPrintPrinted(CHT* start = nullptr) {
  static CHT* buffer_begin = 0;
  if (start) {
    buffer_begin = start;
    return start;
  }
  std::cout << "\n    Printed \"";
  CHT* string = buffer_begin;
  CHT c = *string++;
  while (c) {
    std::cout << c;
    c = *string++;
  }
  std::cout << '\"';
}

}  // namespace _

#define BEGIN_ITOS_ALGORITHM                               \
  auto String_length = STRLength(value);                   \
  TPrintPrinted<CHT>(cursor);                              \
  for (ISN i = 0; i < String_length; ++i) cursor[i] = 'x'; \
  cursor[String_length] = 0;                               \
  std::cout << "Expecting:" << value << " length:" << String_length
#define D_PRINT_PRINTED TPrintPrinted<CHT>()

#else
#define D_COUT(item)
#define BEGIN_ITOS_ALGORITHM
#define D_PRINT_PRINTED
#endif

namespace _ {
/* Prints two chars to the console.
@warning This function DOES NOT do any error checking! */
template <typename CHT = CHR>
inline CHT* TPrintNil(CHT* start) {
  *start = 0;
  return start;
}

/* Prints a single decimal to the socket.
@warning This function DOES NOT do any error checking!  */
template <typename CHT = CHR>
inline CHT* TSPrintDecimal(CHT* cursor, CHT value) {
  *reinterpret_cast<CHT*>(cursor) = '0' + value;
  D_PRINT_PRINTED;
  return cursor;
}

/* Prints a single decimal to the socket.
@warning This function DOES NOT do any error checking! */
template <typename CHT = CHR>
inline CHT* TWriteChar(CHT* cursor, CHT value) {
  *cursor++ = value;
  D_PRINT_PRINTED;
  return cursor;
}

/* Utility function for printing a char with any Unicode conversion. */
inline CHA* Write(CHA* cursor, CHA c) { return TWriteChar<CHA>(cursor, c); }

inline CHB* Write(CHB* cursor, CHB c) { return TWriteChar<CHB>(cursor, c); }

inline CHC* Write(CHC* cursor, CHC c) { return TWriteChar<CHC>(cursor, c); }

/* Prints a two decimals to the socket.
If the SEAM == _0_0_0 (1), then this function will utf debug data.
@warning This function DOES NOT do any error checking! */
template <typename CHT = CHR>
inline CHT* TPrint2Decimals(CHT* socket, IUB decimal_pair) {
  enum { cSizeBits = sizeof(CHT) * 8 };
  socket[0] = (CHT)(decimal_pair >> 8);
  CHA c = (CHA)decimal_pair;
  socket[1] = (CHT)(c);
  D_PRINT_PRINTED;
  return socket;
}

inline void PrintCharPair(CHA* socket, IUB value) {
#if ALIGN_MEMORY
  socket[0] = (CHA)(value >> 8);
  socket[1] = (CHA)(value);
#else
  *((IUB*)socket) = value;
#endif
  using CHT = CHR;
  D_PRINT_PRINTED;
}

inline void PrintCharPair(CHB* cursor, IUB decimal_pair) {
  TPrint2Decimals<CHB>(cursor, decimal_pair);
}

inline void PrintCharPair(CHC* cursor, IUB decimal_pair) {
  TPrint2Decimals<CHC>(cursor, decimal_pair);
}

/* Prints 8 decimals to the given socket with given LUT.*/
template <typename CHT = CHR>
CHT* TPrint8Decimals(CHT* cursor, IUC value, const IUB* lut) {
  D_COUT("\n    Printing 8 decimals:" << value);
  IUB pow_10_ui2 = 10000, digits6and5 = (IUB)(value / pow_10_ui2),
      digits2and1 = value - pow_10_ui2 * digits6and5;
  pow_10_ui2 = 100;
  IUB digits8and7 = digits6and5 / pow_10_ui2,
      digits4and3 = digits2and1 / pow_10_ui2;
  digits6and5 -= pow_10_ui2 * digits8and7;
  digits2and1 -= pow_10_ui2 * digits4and3;
  PrintCharPair(cursor, lut[digits8and7]);
  PrintCharPair(cursor + 2, lut[digits6and5]);
  PrintCharPair(cursor + 4, lut[digits4and3]);
  PrintCharPair(cursor + 6, lut[digits2and1]);
  D_PRINT_PRINTED;
  return cursor + 8;
}

template <typename CHT = CHR>
inline void TPrint8or16Decimals(CHT* cursor, IUC lsd, const IUB* lut,
                                IUC middle_sd, IUC delta) {
  if (delta == 8) {
    D_COUT("\n    Printing less than 17 decimals:");
    TPrint8Decimals<CHT>(cursor, lsd, lut);
  } else {
    D_COUT("\n    Printing more than 16 decimals:");
    TPrint8Decimals<CHT>(cursor, middle_sd, lut);
    TPrint8Decimals<CHT>(cursor + 8, lsd, lut);
  }
}

inline IUC ToUI4(IUC value) { return value; }
inline IUC ToUI4(IUD value) { return (IUC)value; }

/* Prints the give value to the given socket as a Unicode string.
@return Nil upon socket overflow and a pointer to the nil-term CHT upon
success.
@param cursor The beginning of the socket.
@param stop    The stop address of the socket. */
template <typename UI = UIW, typename CHT = CHR>
CHT* TSPrintUnsigned(CHT* cursor, CHT* stop, UI value) {
  BEGIN_ITOS_ALGORITHM;

  if (!cursor || cursor >= stop) return nullptr;

  CHT* nil_ptr;
  IUB pow_10_ui2, delta = 0;
  IUC pow_10_ui4;
  const IUB* lut = BinaryLUTDecimals();

  // The best way to understand how the numbers are getting converted is that
  // numbers get broken up into up to 8 pairs of 100, in each pair of 10000
  // there will be a Most Significant Decimal (MSD) pair and a Least
  // Significant Decimal (LSD) pair. The digits2and1 and digits6and5 will
  // always be the LSD and digits4and3 and digits8and7 will always be the MSD.

  if (value < 10) {
    D_COUT("\n    Range:[0, 9] length:1 ");
  Print1:
    nil_ptr = cursor + delta + 1;
    if (nil_ptr >= stop) return nullptr;
    TSPrintDecimal<CHT>(cursor, (CHT)value);
    return TPrintNil<CHT>(cursor + delta + 1);
  } else if (value < 100) {
  Print2:
    D_COUT("\n    Range:[10, 99] length:2 ");
    nil_ptr = cursor + delta + 2;
    if (cursor + delta + 2 >= stop) return nullptr;
    PrintCharPair(cursor, lut[value]);
    return TPrintNil<CHT>(cursor + delta + 2);
  } else {
    if ((value >> 10) == 0) {
      pow_10_ui2 = 1000;
      if (value >= pow_10_ui2) {
      Print4B:
        D_COUT("\n    Range:[1000, 1023] length:4");
        nil_ptr = cursor + delta + 4;
        if (nil_ptr >= stop) return nullptr;
        IUB digits2and1 = (IUB)(value - pow_10_ui2);
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
        cursor[0] = '1';
        cursor[1] = '0';
#else
        cursor[0] = '0';
        cursor[1] = '1';
#endif
        PrintCharPair(cursor + 2, lut[digits2and1]);
        return TPrintNil<CHT>(nil_ptr);
      }
    Print3:
      D_COUT("\n    Range:[100, 999] length:3");
      nil_ptr = cursor + delta + 3;
      if (nil_ptr >= stop) return nullptr;
      IUB digits2and1 = (IUB)value, pow_10_ui2 = 100;
      CHT digit = (CHT)(digits2and1 / pow_10_ui2);
      digits2and1 -= ((IUB)digit) * pow_10_ui2;
      TSPrintDecimal<CHT>(cursor, digit);
      PrintCharPair(cursor + 1, lut[digits2and1]);
      return TPrintNil<CHT>(nil_ptr);
    } else if ((value >> 14) == 0) {
      pow_10_ui2 = 10000;
      if (value >= pow_10_ui2) {
      Print5B:
        D_COUT("\n    Range:[10000, 16383] length:5");
        nil_ptr = cursor + delta + 5;
        if (nil_ptr >= stop) return nullptr;
        cursor = TWriteChar<CHT>(cursor, '1');
        value -= pow_10_ui2;
      } else {
      Print4:
        D_COUT("\n    Range:[1024, 9999] length:4");
        nil_ptr = cursor + delta + 4;
        if (nil_ptr >= stop) return nullptr;
        TPrintNil<CHT>(nil_ptr);
      }
      pow_10_ui2 = 100;
      IUB digits2and1 = (IUB)value, digits4and3 = digits2and1 / pow_10_ui2;
      digits2and1 -= digits4and3 * pow_10_ui2;
      PrintCharPair(cursor, lut[digits4and3]);
      PrintCharPair(cursor + 2, lut[digits2and1]);
      return TPrintNil<CHT>(nil_ptr);
    } else if ((value >> 17) == 0) {
      if (value >= 100000) {
      Print6B:
        D_COUT("\n    Range:[65536, 131071] length:6");
        goto Print6;
      }
    Print5:
      D_COUT("\n    Range:[10000, 65535] length:5");
      nil_ptr = cursor + delta + 5;
      if (nil_ptr >= stop) return nullptr;
      IUC value_ui4 = ToUI4(value);
      pow_10_ui2 = 10000;
      CHT digit6 = (IUA)(value_ui4 / pow_10_ui2);
      value_ui4 -= pow_10_ui2 * digit6;
      cursor = TWriteChar<CHT>(cursor, '0' + digit6);
      pow_10_ui2 = 100;
      IUB digits4and3 = ((IUB)value_ui4) / pow_10_ui2,
          digits2and1 = (IUB)(value_ui4 - digits4and3 * pow_10_ui2);
      PrintCharPair(cursor, lut[digits4and3]);
      PrintCharPair(cursor + 2, lut[digits2and1]);
      return TPrintNil<CHT>(nil_ptr);
    } else if ((value >> 20) == 0) {
      pow_10_ui4 = 1000000;
      if (value >= pow_10_ui4) {
      Print7B:
        D_COUT("\n    Range:[100000, 1048575] length:7");
        nil_ptr = cursor + delta + 7;
        if (nil_ptr >= stop) return nullptr;
        cursor = TWriteChar<CHT>(cursor, '1');
        value -= pow_10_ui4;
      } else {
      Print6:
        D_COUT("\n    Range:[131072, 999999] length:6");
        nil_ptr = cursor + delta + 6;
        if (nil_ptr >= stop) return nullptr;
        TPrintNil<CHT>(nil_ptr);
      }
      IUC value_ui4 = (IUC)value;
      pow_10_ui2 = 10000;
      IUB digits6and5 = (IUB)(value_ui4 / pow_10_ui2),
          digits2and1 = value_ui4 - pow_10_ui2 * digits6and5;
      pow_10_ui2 = 100;
      IUB digits8and7 = digits6and5 / pow_10_ui2,
          digits4and3 = digits2and1 / pow_10_ui2;
      digits6and5 -= pow_10_ui2 * digits8and7;
      digits2and1 -= pow_10_ui2 * digits4and3;
      PrintCharPair(cursor, lut[digits6and5]);
      PrintCharPair(cursor + 2, lut[digits4and3]);
      PrintCharPair(cursor + 4, lut[digits2and1]);
      return nil_ptr;
    } else if ((value >> 24) == 0) {
      pow_10_ui4 = 10000000;  //< 10^7
      if (value >= pow_10_ui4) {
        D_COUT("\n    Range:[10000000, 16777216] length:8");
        return TPrint8Decimals<CHT>(cursor, ToUI4(value), lut);
      }
    Print7:
      D_COUT("\n    Range:[1048576, 9999999] length:7");
      nil_ptr = cursor + delta + 7;
      if (nil_ptr >= stop) return nullptr;
      IUB pow_10_ui2 = 10000;
      IUC value_ui4 = ToUI4(value);
      IUB digits6and5 = value_ui4 / pow_10_ui2,
          digits2and1 = value_ui4 - pow_10_ui2 * digits6and5;
      pow_10_ui2 = 100;
      IUB digit7 = digits6and5 / pow_10_ui2,
          digits4and3 = digits2and1 / pow_10_ui2;
      digits6and5 -= pow_10_ui2 * digit7;
      digits2and1 -= pow_10_ui2 * digits4and3;
      TSPrintDecimal(cursor, (CHT)(digit7));
      PrintCharPair(cursor + 1, lut[digits6and5]);
      PrintCharPair(cursor + 3, lut[digits4and3]);
      PrintCharPair(cursor + 5, lut[digits2and1]);
      return TPrintNil<CHT>(nil_ptr);
    } else {
      IUC comparator = 100000000;  // 10^8
      UI msd =
          (value >= (~(IUC)0)) ? value / comparator : ToUI4(value) / comparator;
      IUC lsd = (IUC)(value - comparator * msd), middle_sd;
      if (msd >= comparator) {
        delta = 16;
        value = msd / comparator;
        middle_sd = ToUI4(msd - value * comparator);
        D_COUT("\n    Printing " << value << '_' << middle_sd << '_' << lsd);
      } else {
        value = msd;
        middle_sd = 0;
        delta = 8;
        D_COUT("\n    Printing " << value << '_' << lsd);
      }
      if (value == 0) {
        D_COUT("\n    Length:8");
        TPrint8or16Decimals<CHT>(cursor, lsd, lut, middle_sd, delta);
        return TPrintNil<CHT>(cursor + 8);
      } else if (value < 10) {
        D_COUT("\n    Length:9");
        TPrint8or16Decimals<CHT>(cursor + 1, lsd, lut, middle_sd, delta);
        goto Print1;
      } else if (value < 100) {
        D_COUT("\n    Length:10");
        TPrint8or16Decimals<CHT>(cursor + 2, lsd, lut, middle_sd, delta);
        goto Print2;
      } else if ((value >> 10) == 0) {
        pow_10_ui2 = 1000;
        if (value >= pow_10_ui2) {
          D_COUT("\n    Length:12B");
          TPrint8or16Decimals<CHT>(cursor + 4, lsd, lut, middle_sd, delta);
          goto Print4B;
        }
        D_COUT("\n    Length:11");
        TPrint8or16Decimals<CHT>(cursor + 3, lsd, lut, middle_sd, delta);
        goto Print3;
      } else if ((value >> 14) == 0) {
        pow_10_ui2 = 10000;
        if (value >= pow_10_ui2) {
          D_COUT("\n    Length:13B");
          TPrint8or16Decimals<CHT>(cursor + 5, lsd, lut, middle_sd, delta);
          goto Print5B;
        }
        D_COUT("\n    Length:12");
        TPrint8or16Decimals<CHT>(cursor + 4, lsd, lut, middle_sd, delta);
        goto Print4;
      } else if ((value >> 17) == 0) {
        pow_10_ui4 = 100000;
        if (value >= pow_10_ui4) {
          D_COUT("\n    Length:14B");
          TPrint8or16Decimals<CHT>(cursor + 6, lsd, lut, middle_sd, delta);
          goto Print6B;
        }
        D_COUT("\n    Length:13");
        TPrint8or16Decimals<CHT>(cursor + 5, lsd, lut, middle_sd, delta);
        goto Print5;
      } else if ((value >> 20) == 0) {
        pow_10_ui4 = 1000000;
        if (value >= pow_10_ui4) {
          D_COUT("\n    Length:15B");
          TPrint8or16Decimals<CHT>(cursor + 7, lsd, lut, middle_sd, delta);
          goto Print7B;
        }
        D_COUT("\n    Length:14");
        TPrint8or16Decimals<CHT>(cursor + 6, lsd, lut, middle_sd, delta);
        goto Print6;
      } else {
        comparator = 10000000;
        if (value >= comparator) {
          D_COUT("\n    Length:16");
          TPrint8Decimals<CHT>(cursor, ToUI4(value), lut);
          TPrint8Decimals<CHT>(cursor + 8, lsd, lut);
          return TPrintNil<CHT>(cursor + 16);
        }
        D_COUT("\n    Length:15");
        TPrint8or16Decimals<CHT>(cursor + 7, lsd, lut, middle_sd, delta);
        goto Print7;
      }
    }
  }
  return nullptr;  //< Unreachable.
}

template <typename UI = IUD, typename CHT = CHR>
inline CHT* TSPrintUnsigned(CHT* socket, ISW size, UI value) {
  return TSPrintUnsigned<UI, CHT>(socket, socket + size - 1, value);
}

template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, CHT* stop, IUD value) {
  return TSPrintUnsigned<IUD, CHT>(start, stop, value);
}

template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, ISW size, IUD value) {
  return TSPrintUnsigned<IUD, CHT>(start, size, value);
}

#if ALU_SIZE < 64
template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, CHT* stop, IUC value) {
  return TSPrintUnsigned<IUC, CHT>(start, stop, value);
}

template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, ISW size, IUC value) {
  return TSPrintUnsigned<IUC, CHT>(start, size, value);
}
#else
template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, CHT* stop, IUC value) {
  return TSPrint<CHT>(start, stop, (IUD)value);
}

template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, ISW size, IUC value) {
  return TSPrint<CHT>(start, size, (IUD)value);
}
#endif

/* Writes the give value to the given socket as an ASCII string.
@return Nil upon socket overflow and a pointer to the nil-term CHT upon
success.
@param utf The text formatter to utf to.
@param value The value to write. */
template <typename SI = ISD, typename UI = IUD, typename CHT = CHR>
inline CHT* TSPrintSigned(CHT* start, CHT* stop, SI value) {
  if (value >= 0) {
    return TSPrintUnsigned<UI, CHT>(start, stop, (UI)value);
  }
  *start++ = '-';
  return TSPrintUnsigned<UI, CHT>(start, stop, (UI)(-(SI)value));
}

/* Writes the give value to the given socket as an ASCII string.
@return Nil upon socket overflow and a pointer to the nil-term CHT upon
success.
@param utf The text formatter to utf to.
@param value The value to write. */
template <typename SI = ISD, typename UI = IUD, typename CHT = CHR>
inline CHT* TSPrintSigned(CHT* start, ISW size, SI value) {
  return TSPrintSigned<SI, UI, CHT>(start, start + size - 1, value);
}

template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, CHT* stop, ISD value) {
  return TSPrintSigned<ISD, IUD, CHT>(start, stop, value);
}
template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, ISW size, ISD value) {
  return TSPrintSigned<ISD, IUD, CHT>(start, size, value);
}

#if ALU_SIZE < 64
template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, CHT* stop, ISC value) {
  return TSPrintSigned<ISC, IUC, CHT>(start, stop, value);
}
template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, ISW size, ISC value) {
  return TSPrintSigned<ISC, IUC, CHT>(start, size, value);
}
#else
template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, CHT* stop, ISC value) {
  return TSPrint<CHT>(start, stop, (ISD)value);
}
template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, ISW size, ISC value) {
  return TSPrint<CHT>(start, size, (ISD)value);
}
#endif
}  // namespace _
#endif

#if SEAM >= SCRIPT2_FTOS
#if SEAM == SCRIPT2_FTOS
#include "_debug.inl"
#define D_COUT_FLOAT_BINARY(integer, decimals, decimal_count) \
  Print("\nBinary:\"");                                       \
  TPrintBinary(value);                                        \
  PrintNL()
#else
#include "_release.inl"
#define D_COUT_FLOAT_BINARY(integer, decimals, decimal_count)
#endif

namespace _ {

inline void FloatBytes(FPC value, CHA& byte_0, CHA& byte_1, CHA& byte_2,
                       CHA& byte_3) {
  IUC ui_value = *reinterpret_cast<IUC*>(&value);
  byte_0 = (CHA)(ui_value);
  byte_1 = (CHA)(ui_value >> 8);
  byte_2 = (CHA)(ui_value >> 16);
  byte_3 = (CHA)(ui_value >> 24);
}

inline void FloatBytes(FPD value, CHA& byte_0, CHA& byte_1, CHA& byte_2,
                       CHA& byte_3, CHA& byte_4, CHA& byte_5, CHA& byte_6,
                       CHA& byte_7) {
  IUD ui_value = *reinterpret_cast<IUD*>(&value);
  byte_0 = (CHA)(ui_value);
  byte_1 = (CHA)(ui_value >> 8);
  byte_2 = (CHA)(ui_value >> 16);
  byte_3 = (CHA)(ui_value >> 24);
  byte_4 = (CHA)(ui_value >> 32);
  byte_5 = (CHA)(ui_value >> 40);
  byte_6 = (CHA)(ui_value >> 48);
  byte_7 = (CHA)(ui_value >> 56);
}

template <typename CHT = CHR>
CHT* TPrint3(CHT* string, CHT* stop, CHT a, CHT b, CHT c) {
  if (!string || string + 3 >= stop) return nullptr;
  *string++ = a;
  *string++ = b;
  *string++ = c;
  return string;
}

/* Masks off the given bits starting at b0. */
template <typename ISZ, ISN cMSb_, ISN cLSb_>
ISZ TMiddleBits(ISZ value) {
  // The goal is to not allow for undefined shifting behavior and not pay for
  // the error checking.
  //                              b15 ---vv--- b8
  // Example: TMiddleBits<ISC, 15, 7> (0xff00)
  //          Expecting 0xff
  // right_shift_count = 32 - 16 = 16
  enum {
    cSize = sizeof(ISZ) * 8,
    cMSbNatural = (cMSb_ < 0) ? 0 : cMSb_,
    cLSbLNatural = (cLSb_ < 0) ? 0 : cLSb_,
    cRightShiftTemp1 = cSize - cMSbNatural + 1,
    cRightShiftTemp2 = (cRightShiftTemp1 >= cSize) ? 0 : cRightShiftTemp1,
    cLeftShift = (cRightShiftTemp2 < cLSb_) ? 0 : cRightShiftTemp2,
    cRightShift = (cRightShiftTemp2 < cLSb_) ? 0 : cRightShiftTemp2,
  };
  return (value << cRightShift) >> cLeftShift;
}

/* Searches for the highest MSb asserted.
@return -1 */
template <typename UI>
ISC TMSbAssertedReverse(UI value) {
  for (ISC i = sizeof(UI) * 8 - 1; i > 0; --i)
    if ((value >> i) != 0) return i;
  return -1;
}

/* A decimal number in floating-point format.
To use this class the sizeof (Float) must equal the sizeof (UI) and sizeof
(SI).
*/
template <typename Float = FPW, typename SI = ISC, typename UI = UIW>
class TBinary {
  UI f;
  SI e;

 public:
  enum {
    cSizeMax = 8,
    cSize = sizeof(Float) >= cSizeMax ? 0 : sizeof(Float),
    cSizeBits = cSize * 8,
    cMSb = cSizeBits - 1,
    cStrandLengthMax = 24,
    cExponentSizeBits =
        (sizeof(Float) == 2)
            ? 5
            : (sizeof(Float) == 4) ? 8 : (sizeof(Float) == 8) ? 11 : 15,
    cCoefficientSize = cSizeBits - cExponentSizeBits - 1,
    cMantissaSize = cSizeBits - cExponentSizeBits - 1,
    cExponentMaskUnshifted =
        (sizeof(cSize) == 2)
            ? 0xf
            : (sizeof(cSize) == 4) ? 0x7f : (sizeof(cSize) == 8) ? 0x3FF : 0,
    cExponentBias = cExponentMaskUnshifted + cCoefficientSize,
    cExponentMin = -cExponentBias,
  };

  // Constructs an uninitialized floating-point number_.
  TBinary() : f(0), e(0) {}

  inline static UI Coefficient(UI decimal) {
    return (decimal << (cExponentSizeBits + 1)) >> (cExponentSizeBits + 1);
  }

  // Converts a Float to a TBinary
  TBinary(Float value) {
    UI ui = *reinterpret_cast<UI*>(&value);

    UI biased_e = TMiddleBits<UI, cMSb - 1, cMantissaSize - 1>(ui);
    UI coefficient = Coefficient(ui);
    if (biased_e != 0) {
      f = coefficient + (((UI)1) << cExponentSizeBits);
      e = biased_e - cExponentBias;
    } else {
      f = coefficient;
      e = cExponentMin + 1;
    }
  }

  TBinary(UI f, SI e) : f(f), e(e) {}

  inline static UI Exponent(UI decimal) {
    return (decimal << (cExponentSizeBits + 1)) >> (cExponentSizeBits + 1);
  }

  template <typename CHT = CHR>
  static CHT* Print(CHT* socket, CHT* stop, Float value) {
    // Not handling NaN and inf

    if (IsNaN(value)) {
      if (stop - socket < 4) return nullptr;
      socket[0] = 'N';
      socket[1] = 'a';
      socket[2] = 'N';
      socket[3] = 0;
      return socket + 4;
    }
    if (IsInfinite(value)) {
      if (stop - socket < 4) return nullptr;
      UI f = *reinterpret_cast<UI*>(&value);
      socket[0] = (f >> (sizeof(UI) * 8 - 1)) ? '-' : '+';
      socket[1] = 'i';
      socket[2] = 'n';
      socket[3] = 'f';
      socket[4] = 0;
      return socket + 5;
    }

    if (value == 0) {
      return TPrint3<CHT>(socket, stop, (CHT)'0', (CHT)'.', (CHT)'0');
    }
    if (value < 0) {
      *socket++ = '-';
      value = -value;
    }
    SI k;
    CHT* cursor = Print<CHT>(socket, stop, value, k);
    if (!cursor) return cursor;
    return Standardize<CHT>(socket, stop, cursor - socket, k);
  }

  static TBinary IEEE754Pow10(SI e, SI& k) {
    // SI k = static_cast<SI>(ceil((-61 - e) *
    // 0.30102999566398114))

    // + 374; dk must be positive to perform ceiling function on positive
    // values.
    Float scalar = sizeof(Float) == 8 ? 0.30102999566398114 : 0.301029995f,
          dk = (-61 - e) * scalar + 347;
    k = static_cast<SI>(dk);
    if (k != dk) ++k;

    SI index = (k >> 3) + 1;

    k = -(-((SI)348) + (index << 3));
    // decimal exponent no need lookup table.

    D_ASSERT(index < 87);

    const UI* f_lut = Pow10IntegralLUT();
    const ISB* e_lut = reinterpret_cast<const ISB*>(BinaryPow10Exponents());
    return TBinary(f_lut[index], e_lut[index]);
  }

  TBinary Minus(const TBinary<Float, SI, UI>& value) const {
    D_ASSERT(e == value.e);
    D_ASSERT(f >= value.f);
    return TBinary(f - value.f, e);
  }

#if D_THIS
  static void PrintDebugInfo() {
    D_COUT("\nkSize:" << cSize << " cSizeBits:" << cSizeBits << " cMSbIndex:"
                      << cMSb << " cStrandLengthMax:" << cStrandLengthMax
                      << "\nkExponentSizeBits:" << cExponentSizeBits
                      << " cCoefficientSize:" << cCoefficientSize
                      << " cMantissaSize:" << cMantissaSize
                      << "\nkExponentMaskUnshifted:" << cExponentMaskUnshifted
                      << " cExponentBias:" << cExponentBias
                      << " ExponentMin ():" << cExponentMin << "\n\n");
  }
#endif

  inline TBinary Multiply(IUB rhs_f, ISB rhs_e) const {
    IUC p = IUC(f) * IUC(rhs_f);
    IUB h = p >> 16;
    IUB l = IUB(p);
    if (l & (IUB(1) << 15))  // rounding
      h++;
    return TBinary(h, e + rhs_e + 16);
  }

  inline TBinary Multiply(IUC rhs_f, ISC rhs_e) const {
    IUD p = IUD(f) * IUD(rhs_f);
    IUC h = p >> 32;
    IUC l = IUC(p);
    if (l & (IUC(1) << 31))  // rounding
      h++;
    return TBinary(h, e + rhs_e + 32);
  }

  inline TBinary Multiply(IUD rhs_f, ISD rhs_e) const {
#if USING_VISUAL_CPP_X64
    IUD h;
    IUD l = _umul128(f, rhs_f, &h);
    if (l & (IUD(1) << 63))  // rounding
      h++;
    return TBinary(h, e + rhs_e + 64);
#elif USING_GCC
    IUE p = static_cast<IUE>(f) * static_cast<IUE>(rhs_f);
    IUD h = p >> 64;
    IUD l = static_cast<IUD>(p);
    if (l & (IUD(1) << 63))  // rounding
      h++;
    return TBinary(h, e + rhs_e + 64);
#else
    const IUD M32 = 0xFFFFFFFF;
    const IUD a = f >> 32;
    const IUD b = f & M32;
    const IUD c = rhs_f >> 32;
    const IUD d = rhs_f & M32;
    const IUD ac = a * c;
    const IUD bc = b * c;
    const IUD ad = a * d;
    const IUD bd = b * d;
    IUD tmp = (bd >> 32) + (ad & M32) + (bc & M32);
    tmp += 1U << 31;  /// mult_round
    return TBinary(ac + (ad >> 32) + (bc >> 32) + (tmp >> 32), e + rhs_e + 64);
#endif
  }

  TBinary operator*(const TBinary& rhs) const { return Multiply(rhs.f, rhs.e); }

  TBinary operator-(const TBinary& rhs) const {
    D_ASSERT(e == rhs.e);
    D_ASSERT(f >= rhs.f);
    return TBinary(f - rhs.f, e);
  }

 private:
  static inline void Multiply(TBinary& result, TBinary& a, TBinary& b) {}

  static constexpr ISW LUTCount() {
    // @todo Figure out the LUT sizes for Half and Single precision FP
    // numbers.
    return (sizeof(Float) == 4) ? 83 : (sizeof(Float) == 8) ? 83 : 0;
  }

  static const UI* Pow10IntegralLUT() {
    const void* ptr =
        (sizeof(UI) == 4)
            ? Binary32Pow10IntegralPortions()
            : (sizeof(UI) == 8) ? Binary64Pow10IntegralPortions() : nullptr;
    return reinterpret_cast<const UI*>(ptr);
  }

  static void AlignLUT(CHA* origin, ISW size) {
    D_ASSERT(size);
    ISW lut_count = LUTCount();
    if (size != ((100 + lut_count) * 2 + lut_count * 8)) return;
    IUB* ui2_ptr = reinterpret_cast<IUB*>(origin);

    for (CHA tens = '0'; tens <= '9'; ++tens)
      for (ISN ones = '0'; ones <= '9'; ++ones)
#if ENDIAN == LITTLE
        *ui2_ptr++ = (tens << 8) | ones;
#else
        *ui2_ptr++ = (ones << 8) | tens;
#endif
    const IUB* e_lut = BinaryPow10Exponents();
    for (ISC i = 0; i < 87; ++i) *ui2_ptr = e_lut[i];

    IUD* ui8_ptr = reinterpret_cast<IUD*>(ui2_ptr);
    const UI* f_lut = Pow10IntegralLUT();
    for (ISC i = 0; i < 87; ++i) *ui8_ptr = f_lut[i];
  }

  template <typename CHT = CHR>
  static CHT* Print(CHT* socket, CHT* stop, Float value, SI& k) {
    TBinary v(value);
    TBinary lower_estimate, upper_estimate;
    v.NormalizedBoundaries(lower_estimate, upper_estimate);

    TBinary cmk = IEEE754Pow10(upper_estimate.e, k);

    TBinary W = v.NormalizeBoundary() * cmk,  //
        w_plus = upper_estimate * cmk,        //
        w_minus = lower_estimate * cmk;
    w_minus.f++;
    w_plus.f--;
    return DigitGen<CHT>(socket, stop, W, w_plus, w_plus.f - w_minus.f, k);
  }

  TBinary NormalizeBoundary() const {
    // SI msba = MSbAsserted(0);
#if defined(_MSC_VER) && defined(_M_AMD64)
    unsigned long index;  //< This is Microsoft's fault.
    _BitScanReverse64(&index, f);
    unsigned long msb_minus_index = cMSb - index;
    return TBinary(f << (cMSb - index), e - msb_minus_index);
#else
    TBinary res = *this;
    UI cDpHiddenBit = ((UI)1) << cMantissaSize;  // 0x0010000000000000;
    while (!(res.f & (kDpHiddenBit << 1))) {
      res.f <<= 1;
      --res.e;
    }
    res.f <<= (kDiySignificandSize - cCoefficientSize - 2);
    res.e = res.e - (kDiySignificandSize - cCoefficientSize - 2);
    return res;
#endif
  }

  // static const UI  cDpExponentMask = 0x7FF0000000000000,
  //   cDpSignificandMask = 0x000FFFFFFFFFFFFF,

  // Normalizes the boundaries.
  void NormalizedBoundaries(TBinary& m_minus, TBinary& m_plus) const {
    UI l_f = f,   //< Local copy of f.
        l_e = e;  //< Local copy of e.
    TBinary pl = TBinary((l_f << 1) + 1, ((SI)l_e) - 1).NormalizeBoundary();
    ISC cShiftCount = (cMantissaSize >= 8) ? 0 : cMantissaSize;
    const UI cHiddenBit = ((UI)1) << cShiftCount;
    TBinary mi = (f == cHiddenBit) ? TBinary((l_f << 2) - 1, e - 2)
                                   : TBinary((l_f << 1) - 1, e - 1);
    mi.f <<= mi.e - pl.e;
    mi.e = pl.e;
    m_plus = pl;
    m_minus = mi;
  }

  // Rounds the Grisu estimation closer to the inside of the squeeze.
  static IUC Round(IUC lsd, UI delta, UI rest, UI ten_kappa, UI wp_w) {
    while (rest < wp_w && (delta - rest) >= ten_kappa &&
           (rest + ten_kappa < wp_w ||  /// closer
            (wp_w - rest) > (rest + ten_kappa - wp_w))) {
      --lsd;
      rest += ten_kappa;
    }
    return lsd;
  }

  static inline IUC Pow10(IUC p_1, ISC& kappa) {
    IUC pow_10 = 10;
    if (p_1 < pow_10) {
      kappa = 1;
      return pow_10;
    } else if (p_1 < (pow_10 = 100)) {
      kappa = 2;
      return pow_10;
    } else if ((p_1 >> 10) == 0) {
      pow_10 = 1000;
      if (p_1 >= pow_10) goto Kappa4;
      kappa = 3;
      return pow_10;
    } else if (!(p_1 >> 13)) {
    Kappa4:
      pow_10 = 10000;
      if (p_1 >= pow_10) goto Kappa5;
      kappa = 4;
      return pow_10;
    } else if (!(p_1 >> 17)) {
    Kappa5:
      pow_10 = 100000;
      if (p_1 >= pow_10) goto Kappa6;
      kappa = 5;
      return pow_10;
    } else if (!(p_1 >> 20)) {
    Kappa6:
      pow_10 = 1000000;
      if (p_1 >= pow_10) goto Kappa7;
      kappa = 6;
      return pow_10;
    } else if (!(p_1 >> 24)) {
    Kappa7:
      pow_10 = 10000000;
      if (p_1 >= pow_10) goto Kappa8;
      kappa = 7;
      return pow_10;
    } else if (!(p_1 >> 27)) {
    Kappa8:
      pow_10 = 100000000;
      if (p_1 >= pow_10) goto Kappa9;
      kappa = 8;
      pow_10 = pow_10;
    } else {  // if (!(p_1 >> 30)) {
    Kappa9:
      pow_10 = 1000000000;
      kappa = 9;
      return pow_10;
    }
    return 0;
  }

  static inline IUC Pow10(IUC p_1, ISD& kappa) {
    IUC pow_10 = 10;
    if (p_1 < pow_10) {
      kappa = 1;
      return pow_10;
    } else if (p_1 < (pow_10 = 100)) {
      kappa = 2;
      return pow_10;
    } else if ((p_1 >> 10) == 0) {
      pow_10 = 1000;
      if (p_1 >= pow_10) goto Kappa4;
      kappa = 3;
      return pow_10;
    } else if (!(p_1 >> 13)) {
    Kappa4:
      pow_10 = 10000;
      if (p_1 >= pow_10) goto Kappa5;
      kappa = 4;
      return pow_10;
    } else if (!(p_1 >> 17)) {
    Kappa5:
      pow_10 = 100000;
      if (p_1 >= pow_10) goto Kappa6;
      kappa = 5;
      return pow_10;
    } else if (!(p_1 >> 20)) {
    Kappa6:
      pow_10 = 1000000;
      if (p_1 >= pow_10) goto Kappa7;
      kappa = 6;
      return pow_10;
    } else if (!(p_1 >> 24)) {
    Kappa7:
      pow_10 = 10000000;
      if (p_1 >= pow_10) goto Kappa8;
      kappa = 7;
      return pow_10;
    } else {  // if (!(p_1 >> 27)) {
    Kappa8:
      pow_10 = 100000000;
      kappa = 8;
      pow_10 = pow_10;
    }
    return 0;
  }

  /* Prints the integer portion of the floating-point number_.
  @return Nil upon failure or a pointer to the nil-term CHT upon success. */
  template <typename CHT = CHR>
  static CHT* DigitGen(CHT* start, CHT* stop, const TBinary& w,
                       const TBinary& m_plus, UI delta, SI& k) {
    TBinary one(((UI)1) << (-m_plus.e), m_plus.e), wp_w = m_plus.Minus(w);
    IUC d, pow_10, p_1 = static_cast<IUC>(m_plus.f >> -one.e);
    UI p_2 = m_plus.f & (one.f - 1);
    SI kappa;
    pow_10 = Pow10(p_1, kappa);
    const UI* f_lut = Pow10IntegralLUT();
    while (kappa > 0) {
      IUC d;
      d = p_1 / pow_10;
      p_1 -= d * pow_10;

      if (start >= stop) return nullptr;

      if (d) start = TSPrintDecimal<CHT>(start, d);

      --kappa;
      UI tmp = (static_cast<UI>(p_1) << -one.e) + p_2;

      if (tmp <= delta) {
        k += kappa;
        UI pow_10_f = f_lut[kappa];
        d = Round(d, delta, tmp, pow_10_f << -one.e, wp_w.f);
        return start;
      }
    }

    for (;;) {  // kappa = 0
      p_2 *= 10;
      delta *= 10;
      d = static_cast<IUC>(p_2 >> -one.e);
      if (start >= stop) return nullptr;
      if (d) *start++ = '0' + d;
      p_2 &= one.f - 1;
      --kappa;
      if (p_2 < delta) {
        k += kappa;
        UI pow_10_f = f_lut[-kappa];
        d = Round(d, delta, p_2, one.f, wp_w.f * pow_10_f);
        return start;
      }
    }

    switch (kappa) {  // Load integer pow_10 from the i-cache.
      case 1:
        d = p_1;
        p_1 = 0;
        return start;
      case 2:
        pow_10 = 10;
        return start;
      case 3:
        pow_10 = 100;
        return start;
      case 4:
        pow_10 = 1000;
        return start;
      case 5:
        pow_10 = 10000;
        return start;
      case 6:
        pow_10 = 100000;
        return start;
      case 7:
        pow_10 = 1000000;
        return start;
      case 8:
        pow_10 = 10000000;
        return start;
      case 9:
        pow_10 = 100000000;
        return start;
      case 10:
        pow_10 = 1000000000;
        return start;
    }
    return start;
  }

  /* Shifts the given string up by given char_count. */
  template <typename CHT = CHR>
  static void ShiftUp(CHT* start, ISW char_count) {
    CHT* stop = start + char_count;
    while (char_count) *stop++ = *start++;
  }

  /* Converts the Grisu2 output to a standardized/easier-to-read format. */
  template <typename CHT = CHR>
  static CHT* Standardize(CHT* start, CHT* stop, ISW length, SI k) {
    const ISW kk = length + k;  // 10^(kk-1) <= v < 10^kk
    CHT* nil_term_char;
    if (length <= kk && kk <= 21) {  // 1234e7 -> 12340000000
      for (ISW i = length; i < kk; i++) start[i] = '0';
      start[kk] = '.';
      start[kk + 1] = '0';
      nil_term_char = &start[kk + 2];
      *nil_term_char = NIL;
      return nil_term_char;
    } else if (0 < kk && kk <= 21) {  // 1234e-2 -> 12.34
      ShiftUp(&start[kk + 1], length - kk);
      start[kk] = '.';
      nil_term_char = &start[length + 1];
      *nil_term_char = NIL;
      return nil_term_char;
    } else if (-6 < kk && kk <= 0) {  // 1234e-6 -> 0.001234
      const ISW offset = 2 - kk;
      ShiftUp(&start[offset], length);
      start[0] = '0';
      start[1] = '.';
      for (ISW i = 2; i < offset; i++) start[i] = '0';
      nil_term_char = &start[length + offset];
      *nil_term_char = 0;
      return nil_term_char;
    } else if (length == 1) {
      // 1e30
      start[1] = 'e';
      return TSPrintSigned<ISW, UIW, CHT>(start + 2, stop, kk - 1);
    }
    // else 1234e30 -> 1.234e33
    ShiftUp(&start[2], length - 1);

    *(++start)++ = '.';
    *start++ = 'e';
    return TSPrintSigned<ISW, UIW, CHT>(start + length + 2, stop, kk - 1);
  }
};

using Binary32 = TBinary<FPC, ISC, IUC>;
using Binary64 = TBinary<FPD, ISC, IUD>;

template <typename CHT = CHR>
CHT* TSPrint(CHT* start, CHT* stop, FPC value) {
  return TBinary<FPC, ISC, IUC>::template Print<CHT>(start, stop, value);
}
template <typename CHT = CHR>
CHT* TSPrint(CHT* start, ISW size, FPC value) {
  return TSPrint<CHT>(start, start + size - 1, value);
}

template <typename CHT = CHR>
CHT* TSPrint(CHT* start, CHT* stop, FPD value) {
  return TBinary<FPD, ISD, IUD>::template Print<CHT>(start, stop, value);
}
template <typename CHT = CHR>
CHT* TSPrint(CHT* start, ISW size, FPD value) {
  return TSPrint<CHT>(start, start + size - 1, value);
}
#if USING_FPC == YES_0
inline CHB* SPrint(CHB* string, CHB* stop, FPC item) {
  return TBinary<FPC, ISC, IUC>::template Print<CHB>(string, stop, item);
}
#endif
#if USING_FPD == YES_0
inline CHB* SPrint(CHB* string, CHB* stop, FPD item) {
  return TBinary<FPD, ISD, IUD>::template Print<CHB>(string, stop, item);
}
#endif
#if USING_FPC == YES_0
inline CHC* SPrint(CHC* string, CHC* stop, FPC value) {
  return TBinary<FPC, ISC, IUC>::template Print<CHC>(string, stop, value);
}
#endif
#if USING_FPD == YES_0
inline CHC* SPrint(CHC* string, CHC* stop, FPD value) {
  return TBinary<FPD, ISD, IUD>::template Print<CHC>(string, stop, value);
}
#endif
}  // namespace _
#endif
#undef D_COUT
#endif
