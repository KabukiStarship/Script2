/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_puff.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_ITOS

#ifndef SCRIPT2_PUFF_HEADER_WITH_TEMPLATES
#define SCRIPT2_PUFF_HEADER_WITH_TEMPLATES 1

#include "c_puff.h"
#include "t_binary.h"
#if SEAM == SCRIPT2_ITOS
#include <iostream>
#define D_COUT(item) std::cout << item
namespace _ {
template <typename Char = CHR>
Char* TPrintPrinted(Char* start = nullptr) {
  static Char* buffer_begin = 0;
  if (start) {
    buffer_begin = start;
    return start;
  }
  std::cout << "\n    Printed \"";
  Char* string = buffer_begin;
  Char c = *string++;
  while (c) {
    std::cout << c;
    c = *string++;
  }
  std::cout << '\"';
}

}  // namespace _

#define BEGIN_ITOS_ALGORITHM                               \
  auto string_length = STRLength(value);                   \
  TPrintPrinted<Char>(cursor);                             \
  for (SIN i = 0; i < string_length; ++i) cursor[i] = 'x'; \
  cursor[string_length] = 0;                               \
  std::cout << "Expecting:" << value << " length:" << string_length
#define D_PRINT_PRINTED TPrintPrinted<Char>()

#else
#define D_COUT(item)
#define BEGIN_ITOS_ALGORITHM
#define D_PRINT_PRINTED
#endif

namespace _ {
/* Prints two chars to the console.
@warning This function DOES NOT do any error checking! */
template <typename Char = CHR>
inline Char* TPrintNil(Char* start) {
  *start = 0;
  return start;
}

/* Prints a single decimal to the socket.
@warning This function DOES NOT do any error checking!  */
template <typename Char = CHR>
inline Char* TSPrintDecimal(Char* cursor, Char value) {
  *reinterpret_cast<Char*>(cursor) = '0' + value;
  D_PRINT_PRINTED;
  return cursor;
}

/* Prints a single decimal to the socket.
@warning This function DOES NOT do any error checking! */
template <typename Char = CHR>
inline Char* TWriteChar(Char* cursor, Char value) {
  *cursor++ = value;
  D_PRINT_PRINTED;
  return cursor;
}

/* Utility function for printing a char with any Unicode conversion. */
inline CH1* Write(CH1* cursor, CH1 c) { return TWriteChar<CH1>(cursor, c); }

inline CH2* Write(CH2* cursor, CH2 c) { return TWriteChar<CH2>(cursor, c); }

inline CH4* Write(CH4* cursor, CH4 c) { return TWriteChar<CH4>(cursor, c); }

/* Prints a two decimals to the socket.
If the SEAM == _0_0_0 (1), then this function will utf debug data.
@warning This function DOES NOT do any error checking! */
template <typename Char = CHR>
inline Char* TPrint2Decimals(Char* socket, UI2 decimal_pair) {
  enum { kSizeBits = sizeof(Char) * 8 };
  socket[0] = (Char)(decimal_pair >> 8);
  CH1 c = (CH1)decimal_pair;
  socket[1] = (Char)(c);
  D_PRINT_PRINTED;
  return socket;
}

inline void PrintCharPair(CH1* socket, UI2 value) {
#if ALIGN_MEMORY
  socket[0] = (CH1)(value >> 8);
  socket[1] = (CH1)(value);
#else
  *((UI2*)socket) = value;
#endif
  using Char = CHR;
  D_PRINT_PRINTED;
}

inline void PrintCharPair(CH2* cursor, UI2 decimal_pair) {
  TPrint2Decimals<CH2>(cursor, decimal_pair);
}

inline void PrintCharPair(CH4* cursor, UI2 decimal_pair) {
  TPrint2Decimals<CH4>(cursor, decimal_pair);
}

/* Prints 8 decimals to the given socket with given LUT.*/
template <typename Char = CHR>
Char* TPrint8Decimals(Char* cursor, UI4 value, const UI2* lut) {
  D_COUT("\n    Printing 8 decimals:" << value);
  UI2 pow_10_ui2 = 10000, digits6and5 = (UI2)(value / pow_10_ui2),
      digits2and1 = value - pow_10_ui2 * digits6and5;
  pow_10_ui2 = 100;
  UI2 digits8and7 = digits6and5 / pow_10_ui2,
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

template <typename Char = CHR>
inline void TPrint8or16Decimals(Char* cursor, UI4 lsd, const UI2* lut,
                                UI4 middle_sd, UI4 delta) {
  if (delta == 8) {
    D_COUT("\n    Printing less than 17 decimals:");
    TPrint8Decimals<Char>(cursor, lsd, lut);
  } else {
    D_COUT("\n    Printing more than 16 decimals:");
    TPrint8Decimals<Char>(cursor, middle_sd, lut);
    TPrint8Decimals<Char>(cursor + 8, lsd, lut);
  }
}

inline UI4 ToUI4(UI4 value) { return value; }
inline UI4 ToUI4(UI8 value) { return (UI4)value; }

/* Prints the give value to the given socket as a Unicode string.
@return Nil upon socket overflow and a pointer to the nil-term Char upon
success.
@param  cursor The beginning of the socket.
@param  stop    The stop address of the socket. */
template <typename UI = UIW, typename Char = CHR>
Char* TSPrintUnsigned(Char* cursor, Char* stop, UI value) {
  BEGIN_ITOS_ALGORITHM;

  if (!cursor || cursor >= stop) return nullptr;

  Char* nil_ptr;
  UI2 pow_10_ui2, delta = 0;
  UI4 pow_10_ui4;
  const UI2* lut = BinaryLUTDecimals();

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
    TSPrintDecimal<Char>(cursor, (Char)value);
    return TPrintNil<Char>(cursor + delta + 1);
  } else if (value < 100) {
  Print2:
    D_COUT("\n    Range:[10, 99] length:2 ");
    nil_ptr = cursor + delta + 2;
    if (cursor + delta + 2 >= stop) return nullptr;
    PrintCharPair(cursor, lut[value]);
    return TPrintNil<Char>(cursor + delta + 2);
  } else {
    if ((value >> 10) == 0) {
      pow_10_ui2 = 1000;
      if (value >= pow_10_ui2) {
      Print4B:
        D_COUT("\n    Range:[1000, 1023] length:4");
        nil_ptr = cursor + delta + 4;
        if (nil_ptr >= stop) return nullptr;
        UI2 digits2and1 = (UI2)(value - pow_10_ui2);
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
        cursor[0] = '1';
        cursor[1] = '0';
#else
        cursor[0] = '0';
        cursor[1] = '1';
#endif
        PrintCharPair(cursor + 2, lut[digits2and1]);
        return TPrintNil<Char>(nil_ptr);
      }
    Print3:
      D_COUT("\n    Range:[100, 999] length:3");
      nil_ptr = cursor + delta + 3;
      if (nil_ptr >= stop) return nullptr;
      UI2 digits2and1 = (UI2)value, pow_10_ui2 = 100;
      Char digit = (Char)(digits2and1 / pow_10_ui2);
      digits2and1 -= ((UI2)digit) * pow_10_ui2;
      TSPrintDecimal<Char>(cursor, digit);
      PrintCharPair(cursor + 1, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
    } else if ((value >> 14) == 0) {
      pow_10_ui2 = 10000;
      if (value >= pow_10_ui2) {
      Print5B:
        D_COUT("\n    Range:[10000, 16383] length:5");
        nil_ptr = cursor + delta + 5;
        if (nil_ptr >= stop) return nullptr;
        cursor = TWriteChar<Char>(cursor, '1');
        value -= pow_10_ui2;
      } else {
      Print4:
        D_COUT("\n    Range:[1024, 9999] length:4");
        nil_ptr = cursor + delta + 4;
        if (nil_ptr >= stop) return nullptr;
        TPrintNil<Char>(nil_ptr);
      }
      pow_10_ui2 = 100;
      UI2 digits2and1 = (UI2)value, digits4and3 = digits2and1 / pow_10_ui2;
      digits2and1 -= digits4and3 * pow_10_ui2;
      PrintCharPair(cursor, lut[digits4and3]);
      PrintCharPair(cursor + 2, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
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
      UI4 value_ui4 = ToUI4(value);
      pow_10_ui2 = 10000;
      Char digit6 = (UI1)(value_ui4 / pow_10_ui2);
      value_ui4 -= pow_10_ui2 * digit6;
      cursor = TWriteChar<Char>(cursor, '0' + digit6);
      pow_10_ui2 = 100;
      UI2 digits4and3 = ((UI2)value_ui4) / pow_10_ui2,
          digits2and1 = (UI2)(value_ui4 - digits4and3 * pow_10_ui2);
      PrintCharPair(cursor, lut[digits4and3]);
      PrintCharPair(cursor + 2, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
    } else if ((value >> 20) == 0) {
      pow_10_ui4 = 1000000;
      if (value >= pow_10_ui4) {
      Print7B:
        D_COUT("\n    Range:[100000, 1048575] length:7");
        nil_ptr = cursor + delta + 7;
        if (nil_ptr >= stop) return nullptr;
        cursor = TWriteChar<Char>(cursor, '1');
        value -= pow_10_ui4;
      } else {
      Print6:
        D_COUT("\n    Range:[131072, 999999] length:6");
        nil_ptr = cursor + delta + 6;
        if (nil_ptr >= stop) return nullptr;
        TPrintNil<Char>(nil_ptr);
      }
      UI4 value_ui4 = (UI4)value;
      pow_10_ui2 = 10000;
      UI2 digits6and5 = (UI2)(value_ui4 / pow_10_ui2),
          digits2and1 = value_ui4 - pow_10_ui2 * digits6and5;
      pow_10_ui2 = 100;
      UI2 digits8and7 = digits6and5 / pow_10_ui2,
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
        return TPrint8Decimals<Char>(cursor, ToUI4(value), lut);
      }
    Print7:
      D_COUT("\n    Range:[1048576, 9999999] length:7");
      nil_ptr = cursor + delta + 7;
      if (nil_ptr >= stop) return nullptr;
      UI2 pow_10_ui2 = 10000;
      UI4 value_ui4 = ToUI4(value);
      UI2 digits6and5 = value_ui4 / pow_10_ui2,
          digits2and1 = value_ui4 - pow_10_ui2 * digits6and5;
      pow_10_ui2 = 100;
      UI2 digit7 = digits6and5 / pow_10_ui2,
          digits4and3 = digits2and1 / pow_10_ui2;
      digits6and5 -= pow_10_ui2 * digit7;
      digits2and1 -= pow_10_ui2 * digits4and3;
      TSPrintDecimal(cursor, (Char)(digit7));
      PrintCharPair(cursor + 1, lut[digits6and5]);
      PrintCharPair(cursor + 3, lut[digits4and3]);
      PrintCharPair(cursor + 5, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
    } else {
      UI4 comparator = 100000000;  // 10^8
      UI msd =
          (value >= (~(UI4)0)) ? value / comparator : ToUI4(value) / comparator;
      UI4 lsd = (UI4)(value - comparator * msd), middle_sd;
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
        TPrint8or16Decimals<Char>(cursor, lsd, lut, middle_sd, delta);
        return TPrintNil<Char>(cursor + 8);
      } else if (value < 10) {
        D_COUT("\n    Length:9");
        TPrint8or16Decimals<Char>(cursor + 1, lsd, lut, middle_sd, delta);
        goto Print1;
      } else if (value < 100) {
        D_COUT("\n    Length:10");
        TPrint8or16Decimals<Char>(cursor + 2, lsd, lut, middle_sd, delta);
        goto Print2;
      } else if ((value >> 10) == 0) {
        pow_10_ui2 = 1000;
        if (value >= pow_10_ui2) {
          D_COUT("\n    Length:12B");
          TPrint8or16Decimals<Char>(cursor + 4, lsd, lut, middle_sd, delta);
          goto Print4B;
        }
        D_COUT("\n    Length:11");
        TPrint8or16Decimals<Char>(cursor + 3, lsd, lut, middle_sd, delta);
        goto Print3;
      } else if ((value >> 14) == 0) {
        pow_10_ui2 = 10000;
        if (value >= pow_10_ui2) {
          D_COUT("\n    Length:13B");
          TPrint8or16Decimals<Char>(cursor + 5, lsd, lut, middle_sd, delta);
          goto Print5B;
        }
        D_COUT("\n    Length:12");
        TPrint8or16Decimals<Char>(cursor + 4, lsd, lut, middle_sd, delta);
        goto Print4;
      } else if ((value >> 17) == 0) {
        pow_10_ui4 = 100000;
        if (value >= pow_10_ui4) {
          D_COUT("\n    Length:14B");
          TPrint8or16Decimals<Char>(cursor + 6, lsd, lut, middle_sd, delta);
          goto Print6B;
        }
        D_COUT("\n    Length:13");
        TPrint8or16Decimals<Char>(cursor + 5, lsd, lut, middle_sd, delta);
        goto Print5;
      } else if ((value >> 20) == 0) {
        pow_10_ui4 = 1000000;
        if (value >= pow_10_ui4) {
          D_COUT("\n    Length:15B");
          TPrint8or16Decimals<Char>(cursor + 7, lsd, lut, middle_sd, delta);
          goto Print7B;
        }
        D_COUT("\n    Length:14");
        TPrint8or16Decimals<Char>(cursor + 6, lsd, lut, middle_sd, delta);
        goto Print6;
      } else {
        comparator = 10000000;
        if (value >= comparator) {
          D_COUT("\n    Length:16");
          TPrint8Decimals<Char>(cursor, ToUI4(value), lut);
          TPrint8Decimals<Char>(cursor + 8, lsd, lut);
          return TPrintNil<Char>(cursor + 16);
        }
        D_COUT("\n    Length:15");
        TPrint8or16Decimals<Char>(cursor + 7, lsd, lut, middle_sd, delta);
        goto Print7;
      }
    }
  }
  return nullptr;  //< Unreachable.
}

template <typename UI = UI8, typename Char = CHR>
inline Char* TSPrintUnsigned(Char* socket, SIW size, UI value) {
  return TSPrintUnsigned<UI, Char>(socket, socket + size - 1, value);
}

template <typename Char = CHR>
inline Char* TSPrint(Char* start, Char* stop, UI8 value) {
  return TSPrintUnsigned<UI8, Char>(start, stop, value);
}

template <typename Char = CHR>
inline Char* TSPrint(Char* start, SIW size, UI8 value) {
  return TSPrintUnsigned<UI8, Char>(start, size, value);
}

#if CPU_WORD_SIZE < 64
template <typename Char = CHR>
inline Char* TSPrint(Char* start, Char* stop, UI4 value) {
  return TSPrintUnsigned<UI4, Char>(start, stop, value);
}

template <typename Char = CHR>
inline Char* TSPrint(Char* start, SIW size, UI4 value) {
  return TSPrintUnsigned<UI4, Char>(start, size, value);
}
#else
template <typename Char = CHR>
inline Char* TSPrint(Char* start, Char* stop, UI4 value) {
  return TSPrint<Char>(start, stop, (UI8)value);
}

template <typename Char = CHR>
inline Char* TSPrint(Char* start, SIW size, UI4 value) {
  return TSPrint<Char>(start, size, (UI8)value);
}
#endif

/* Writes the give value to the given socket as an ASCII string.
@return Nil upon socket overflow and a pointer to the nil-term Char upon
success.
@param  utf The text formatter to utf to.
@param value The value to write. */
template <typename SI = SI8, typename UI = UI8, typename Char = CHR>
inline Char* TSPrintSigned(Char* start, Char* stop, SI value) {
  if (value >= 0) {
    return TSPrintUnsigned<UI, Char>(start, stop, (UI)value);
  }
  *start++ = '-';
  return TSPrintUnsigned<UI, Char>(start, stop, (UI)(-(SI)value));
}

/* Writes the give value to the given socket as an ASCII string.
@return Nil upon socket overflow and a pointer to the nil-term Char upon
success.
@param  utf The text formatter to utf to.
@param value The value to write. */
template <typename SI = SI8, typename UI = UI8, typename Char = CHR>
inline Char* TSPrintSigned(Char* start, SIW size, SI value) {
  return TSPrintSigned<SI, UI, Char>(start, start + size - 1, value);
}

template <typename Char = CHR>
inline Char* TSPrint(Char* start, Char* stop, SI8 value) {
  return TSPrintSigned<SI8, UI8, Char>(start, stop, value);
}
template <typename Char = CHR>
inline Char* TSPrint(Char* start, SIW size, SI8 value) {
  return TSPrintSigned<SI8, UI8, Char>(start, size, value);
}

#if CPU_WORD_SIZE < 64
template <typename Char = CHR>
inline Char* TSPrint(Char* start, Char* stop, SI4 value) {
  return TSPrintSigned<SI4, UI4, Char>(start, stop, value);
}
template <typename Char = CHR>
inline Char* TSPrint(Char* start, SIW size, SI4 value) {
  return TSPrintSigned<SI4, UI4, Char>(start, size, value);
}
#else
template <typename Char = CHR>
inline Char* TSPrint(Char* start, Char* stop, SI4 value) {
  return TSPrint<Char>(start, stop, (SI8)value);
}
template <typename Char = CHR>
inline Char* TSPrint(Char* start, SIW size, SI4 value) {
  return TSPrint<Char>(start, size, (SI8)value);
}
#endif
}  // namespace _
#endif

#if SEAM >= SCRIPT2_FTOS
#if SEAM == SCRIPT2_FTOS
#include "module_debug.inl"
#define D_COUT_FLOAT_BINARY(integer, decimals, decimal_count) \
  Print("\nBinary:\"");                                       \
  TPrintBinary(value);                                        \
  PrintNL()
#else
#include "module_release.inl"
#define D_COUT_FLOAT_BINARY(integer, decimals, decimal_count)
#endif

namespace _ {

inline void FloatBytes(FP4 value, CH1& byte_0, CH1& byte_1, CH1& byte_2,
                       CH1& byte_3) {
  UI4 ui_value = *reinterpret_cast<UI4*>(&value);
  byte_0 = (CH1)(ui_value);
  byte_1 = (CH1)(ui_value >> 8);
  byte_2 = (CH1)(ui_value >> 16);
  byte_3 = (CH1)(ui_value >> 24);
}

inline void FloatBytes(FP8 value, CH1& byte_0, CH1& byte_1, CH1& byte_2,
                       CH1& byte_3, CH1& byte_4, CH1& byte_5, CH1& byte_6,
                       CH1& byte_7) {
  UI8 ui_value = *reinterpret_cast<UI8*>(&value);
  byte_0 = (CH1)(ui_value);
  byte_1 = (CH1)(ui_value >> 8);
  byte_2 = (CH1)(ui_value >> 16);
  byte_3 = (CH1)(ui_value >> 24);
  byte_4 = (CH1)(ui_value >> 32);
  byte_5 = (CH1)(ui_value >> 40);
  byte_6 = (CH1)(ui_value >> 48);
  byte_7 = (CH1)(ui_value >> 56);
}

template <typename Char = CHR>
Char* TPrint3(Char* string, Char* stop, Char a, Char b, Char c) {
  if (!string || string + 3 >= stop) return nullptr;
  *string++ = a;
  *string++ = b;
  *string++ = c;
  return string;
}

/* Masks off the given bits starting at b0. */
template <typename SIZ, SIN kMSb_, SIN kLSb_>
SIZ TMiddleBits(SIZ value) {
  // The goal is to not allow for undefined shifting behavior and not pay for
  // the error checking.
  //                              b15 ---vv--- b8
  // Example: TMiddleBits<SI4, 15, 7> (0xff00)
  //          Expecting 0xff
  // right_shift_count = 32 - 16 = 16
  enum {
    kSize = sizeof(SIZ) * 8,
    kMSbNatural = (kMSb_ < 0) ? 0 : kMSb_,
    kLSbLNatural = (kLSb_ < 0) ? 0 : kLSb_,
    kRightShiftTemp1 = kSize - kMSbNatural + 1,
    kRightShiftTemp2 = (kRightShiftTemp1 >= kSize) ? 0 : kRightShiftTemp1,
    kLeftShift = (kRightShiftTemp2 < kLSb_) ? 0 : kRightShiftTemp2,
    kRightShift = (kRightShiftTemp2 < kLSb_) ? 0 : kRightShiftTemp2,
  };
  return (value << kRightShift) >> kLeftShift;
}

/* Searches for the highest MSb asserted.
@return -1 */
template <typename UI>
SI4 TMSbAssertedReverse(UI value) {
  for (SI4 i = sizeof(UI) * 8 - 1; i > 0; --i)
    if ((value >> i) != 0) return i;
  return -1;
}

/* A decimal number in floating-point format.
To use this class the sizeof (Float) must equal the sizeof (UI) and sizeof
(SI).
*/
template <typename Float = FPW, typename SI = SI4, typename UI = UIW>
class TBinary {
  UI f;
  SI e;

 public:
  enum {
    kSizeMax = 8,
    kSize = sizeof(Float) >= kSizeMax ? 0 : sizeof(Float),
    kSizeBits = kSize * 8,
    kMSb = kSizeBits - 1,
    kStrandLengthMax = 24,
    kExponentSizeBits =
        (sizeof(Float) == 2)
            ? 5
            : (sizeof(Float) == 4) ? 8 : (sizeof(Float) == 8) ? 11 : 15,
    kCoefficientSize = kSizeBits - kExponentSizeBits - 1,
    kMantissaSize = kSizeBits - kExponentSizeBits - 1,
    kExponentMaskUnshifted =
        (sizeof(kSize) == 2)
            ? 0xf
            : (sizeof(kSize) == 4) ? 0x7f : (sizeof(kSize) == 8) ? 0x3FF : 0,
    kExponentBias = kExponentMaskUnshifted + kCoefficientSize,
    kExponentMin = -kExponentBias,
  };

  // Constructs an uninitialized floating-point number_.
  TBinary() : f(0), e(0) {}

  inline static UI Coefficient(UI decimal) {
    return (decimal << (kExponentSizeBits + 1)) >> (kExponentSizeBits + 1);
  }

  // Converts a Float to a TBinary
  TBinary(Float value) {
    UI ui = *reinterpret_cast<UI*>(&value);

    UI biased_e = TMiddleBits<UI, kMSb - 1, kMantissaSize - 1>(ui);
    UI coefficient = Coefficient(ui);
    if (biased_e != 0) {
      f = coefficient + (((UI)1) << kExponentSizeBits);
      e = biased_e - kExponentBias;
    } else {
      f = coefficient;
      e = kExponentMin + 1;
    }
  }

  TBinary(UI f, SI e) : f(f), e(e) {}

  inline static UI Exponent(UI decimal) {
    return (decimal << (kExponentSizeBits + 1)) >> (kExponentSizeBits + 1);
  }

  template <typename Char = CHR>
  static Char* Print(Char* socket, Char* stop, Float value) {
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
      return TPrint3<Char>(socket, stop, (Char)'0', (Char)'.', (Char)'0');
    }
    if (value < 0) {
      *socket++ = '-';
      value = -value;
    }
    SI k;
    Char* cursor = Print<Char>(socket, stop, value, k);
    if (!cursor) return cursor;
    return Standardize<Char>(socket, stop, cursor - socket, k);
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
    const SI2* e_lut = reinterpret_cast<const SI2*>(BinaryPow10Exponents());
    return TBinary(f_lut[index], e_lut[index]);
  }

  TBinary Minus(const TBinary<Float, SI, UI>& value) const {
    D_ASSERT(e == value.e);
    D_ASSERT(f >= value.f);
    return TBinary(f - value.f, e);
  }

#if D_THIS
  static void PrintDebugInfo() {
    D_COUT("\nkSize:" << kSize << " kSizeBits:" << kSizeBits << " kMSbIndex:"
                      << kMSb << " kStrandLengthMax:" << kStrandLengthMax
                      << "\nkExponentSizeBits:" << kExponentSizeBits
                      << " kCoefficientSize:" << kCoefficientSize
                      << " kMantissaSize:" << kMantissaSize
                      << "\nkExponentMaskUnshifted:" << kExponentMaskUnshifted
                      << " kExponentBias:" << kExponentBias
                      << " ExponentMin ():" << kExponentMin << "\n\n");
  }
#endif

  inline TBinary Multiply(UI2 rhs_f, SI2 rhs_e) const {
    UI4 p = UI4(f) * UI4(rhs_f);
    UI2 h = p >> 16;
    UI2 l = UI2(p);
    if (l & (UI2(1) << 15))  // rounding
      h++;
    return TBinary(h, e + rhs_e + 16);
  }

  inline TBinary Multiply(UI4 rhs_f, SI4 rhs_e) const {
    UI8 p = UI8(f) * UI8(rhs_f);
    UI4 h = p >> 32;
    UI4 l = UI4(p);
    if (l & (UI4(1) << 31))  // rounding
      h++;
    return TBinary(h, e + rhs_e + 32);
  }

  inline TBinary Multiply(UI8 rhs_f, SI8 rhs_e) const {
#if USING_VISUAL_CPP_X64
    UI8 h;
    UI8 l = _umul128(f, rhs_f, &h);
    if (l & (UI8(1) << 63))  // rounding
      h++;
    return TBinary(h, e + rhs_e + 64);
#elif USING_GCC
    UIH p = static_cast<UIH>(f) * static_cast<UIH>(rhs_f);
    UI8 h = p >> 64;
    UI8 l = static_cast<UI8>(p);
    if (l & (UI8(1) << 63))  // rounding
      h++;
    return TBinary(h, e + rhs_e + 64);
#else
    const UI8 M32 = 0xFFFFFFFF;
    const UI8 a = f >> 32;
    const UI8 b = f & M32;
    const UI8 c = rhs_f >> 32;
    const UI8 d = rhs_f & M32;
    const UI8 ac = a * c;
    const UI8 bc = b * c;
    const UI8 ad = a * d;
    const UI8 bd = b * d;
    UI8 tmp = (bd >> 32) + (ad & M32) + (bc & M32);
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

  static constexpr SIW LUTCount() {
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

  static void AlignLUT(CH1* begin, SIW size) {
    D_ASSERT(size);
    SIW lut_count = LUTCount();
    if (size != ((100 + lut_count) * 2 + lut_count * 8)) return;
    UI2* ui2_ptr = reinterpret_cast<UI2*>(begin);

    for (CH1 tens = '0'; tens <= '9'; ++tens)
      for (SIN ones = '0'; ones <= '9'; ++ones)
#if ENDIAN == LITTLE
        *ui2_ptr++ = (tens << 8) | ones;
#else
        *ui2_ptr++ = (ones << 8) | tens;
#endif
    const UI2* e_lut = BinaryPow10Exponents();
    for (SI4 i = 0; i < 87; ++i) *ui2_ptr = e_lut[i];

    UI8* ui8_ptr = reinterpret_cast<UI8*>(ui2_ptr);
    const UI* f_lut = Pow10IntegralLUT();
    for (SI4 i = 0; i < 87; ++i) *ui8_ptr = f_lut[i];
  }

  template <typename Char = CHR>
  static Char* Print(Char* socket, Char* stop, Float value, SI& k) {
    TBinary v(value);
    TBinary lower_estimate, upper_estimate;
    v.NormalizedBoundaries(lower_estimate, upper_estimate);

    TBinary c_mk = IEEE754Pow10(upper_estimate.e, k);

    TBinary W = v.NormalizeBoundary() * c_mk,  //
        w_plus = upper_estimate * c_mk,        //
        w_minus = lower_estimate * c_mk;
    w_minus.f++;
    w_plus.f--;
    return DigitGen<Char>(socket, stop, W, w_plus, w_plus.f - w_minus.f, k);
  }

  TBinary NormalizeBoundary() const {
    // SI msba = MSbAsserted(0);
#if defined(_MSC_VER) && defined(_M_AMD64)
    unsigned long index;  //< This is Microsoft's fault.
    _BitScanReverse64(&index, f);
    unsigned long msb_minus_index = kMSb - index;
    return TBinary(f << (kMSb - index), e - msb_minus_index);
#else
    TBinary res = *this;
    UI kDpHiddenBit = ((UI)1) << kMantissaSize;  // 0x0010000000000000;
    while (!(res.f & (kDpHiddenBit << 1))) {
      res.f <<= 1;
      --res.e;
    }
    res.f <<= (kDiySignificandSize - kCoefficientSize - 2);
    res.e = res.e - (kDiySignificandSize - kCoefficientSize - 2);
    return res;
#endif
  }

  // static const UI  kDpExponentMask = 0x7FF0000000000000,
  //   kDpSignificandMask = 0x000FFFFFFFFFFFFF,

  // Normalizes the boundaries.
  void NormalizedBoundaries(TBinary& m_minus, TBinary& m_plus) const {
    UI l_f = f,   //< Local copy of f.
        l_e = e;  //< Local copy of e.
    TBinary pl = TBinary((l_f << 1) + 1, ((SI)l_e) - 1).NormalizeBoundary();
    SI4 kShiftCount = (kMantissaSize >= 8) ? 0 : kMantissaSize;
    const UI kHiddenBit = ((UI)1) << kShiftCount;
    TBinary mi = (f == kHiddenBit) ? TBinary((l_f << 2) - 1, e - 2)
                                   : TBinary((l_f << 1) - 1, e - 1);
    mi.f <<= mi.e - pl.e;
    mi.e = pl.e;
    m_plus = pl;
    m_minus = mi;
  }

  // Rounds the Grisu estimation closer to the inside of the squeeze.
  static UI4 Round(UI4 lsd, UI delta, UI rest, UI ten_kappa, UI wp_w) {
    while (rest < wp_w && (delta - rest) >= ten_kappa &&
           (rest + ten_kappa < wp_w ||  /// closer
            (wp_w - rest) > (rest + ten_kappa - wp_w))) {
      --lsd;
      rest += ten_kappa;
    }
    return lsd;
  }

  static inline UI4 Pow10(UI4 p_1, SI4& kappa) {
    UI4 pow_10 = 10;
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

  static inline UI4 Pow10(UI4 p_1, SI8& kappa) {
    UI4 pow_10 = 10;
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
  @return Nil upon failure or a pointer to the nil-term Char upon success. */
  template <typename Char = CHR>
  static Char* DigitGen(Char* start, Char* stop, const TBinary& w,
                        const TBinary& m_plus, UI delta, SI& k) {
    TBinary one(((UI)1) << (-m_plus.e), m_plus.e), wp_w = m_plus.Minus(w);
    UI4 d, pow_10, p_1 = static_cast<UI4>(m_plus.f >> -one.e);
    UI p_2 = m_plus.f & (one.f - 1);
    SI kappa;
    pow_10 = Pow10(p_1, kappa);
    const UI* f_lut = Pow10IntegralLUT();
    while (kappa > 0) {
      UI4 d;
      d = p_1 / pow_10;
      p_1 -= d * pow_10;

      if (start >= stop) return nullptr;

      if (d) start = TSPrintDecimal<Char>(start, d);

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
      d = static_cast<UI4>(p_2 >> -one.e);
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
  template <typename Char = CHR>
  static void ShiftUp(Char* start, SIW char_count) {
    Char* stop = start + char_count;
    while (char_count) *stop++ = *start++;
  }

  /* Converts the Grisu2 output to a standardized/easier-to-read format. */
  template <typename Char = CHR>
  static Char* Standardize(Char* start, Char* stop, SIW length, SI k) {
    const SIW kk = length + k;  // 10^(kk-1) <= v < 10^kk
    Char* nil_term_char;
    if (length <= kk && kk <= 21) {  // 1234e7 -> 12340000000
      for (SIW i = length; i < kk; i++) start[i] = '0';
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
      const SIW offset = 2 - kk;
      ShiftUp(&start[offset], length);
      start[0] = '0';
      start[1] = '.';
      for (SIW i = 2; i < offset; i++) start[i] = '0';
      nil_term_char = &start[length + offset];
      *nil_term_char = 0;
      return nil_term_char;
    } else if (length == 1) {
      // 1e30
      start[1] = 'e';
      return TSPrintSigned<SIW, UIW, Char>(start + 2, stop, kk - 1);
    }
    // else 1234e30 -> 1.234e33
    ShiftUp(&start[2], length - 1);

    *(++start)++ = '.';
    *start++ = 'e';
    return TSPrintSigned<SIW, UIW, Char>(start + length + 2, stop, kk - 1);
  }
};

using Binary32 = TBinary<FP4, SI4, UI4>;
using Binary64 = TBinary<FP8, SI4, UI8>;

template <typename Char = CHR>
Char* TSPrint(Char* start, Char* stop, FP4 value) {
  return TBinary<FP4, SI4, UI4>::template Print<Char>(start, stop, value);
}
template <typename Char = CHR>
Char* TSPrint(Char* start, SIW size, FP4 value) {
  return TSPrint<Char>(start, start + size - 1, value);
}

template <typename Char = CHR>
Char* TSPrint(Char* start, Char* stop, FP8 value) {
  return TBinary<FP8, SI8, UI8>::template Print<Char>(start, stop, value);
}
template <typename Char = CHR>
Char* TSPrint(Char* start, SIW size, FP8 value) {
  return TSPrint<Char>(start, start + size - 1, value);
}
#if USING_FP4 == YES_0
inline CH2* SPrint(CH2* string, CH2* stop, FP4 item) {
  return TBinary<FP4, SI4, UI4>::template Print<CH2>(string, stop, item);
}
#endif
#if USING_FP8 == YES_0
inline CH2* SPrint(CH2* string, CH2* stop, FP8 item) {
  return TBinary<FP8, SI8, UI8>::template Print<CH2>(string, stop, item);
}
#endif
#if USING_FP4 == YES_0
inline CH4* SPrint(CH4* string, CH4* stop, FP4 value) {
  return TBinary<FP4, SI4, UI4>::template Print<CH4>(string, stop, value);
}
#endif
#if USING_FP8 == YES_0
inline CH4* SPrint(CH4* string, CH4* stop, FP8 value) {
  return TBinary<FP8, SI8, UI8>::template Print<CH4>(string, stop, value);
}
#endif
}  // namespace _
#endif
#undef D_COUT
#endif
