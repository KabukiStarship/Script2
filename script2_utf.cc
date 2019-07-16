/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_strand.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#include "t_utf.h"

namespace _ {

CH1 HexNibbleToUpperCase(UI1 nibble) {
  nibble = nibble & 0xf;
  if (nibble > 9) return nibble + ('A' - 10);
  return nibble + '0';
}

const CH1* STRPrintCharsHeader() {
  return "\n|0       8       16      24      32      40      48      56      |";
}

const CH1* STRPrintCharsBorder() {
  return "\n|+-------+-------+-------+-------+-------+-------+-------+-------|"
         " 0x";
}

const CH1* STRPrintHexHeader() {
  return "\n|0               8               16              24              |";
}

const CH1* STRPrintHexBorder() {
  return "\n|+---------------+---------------+---------------+---------------|"
         " 0x";
}

CH1 ToLower(CH1 value) { return TToLower<CH1>(value); }
CH2 ToLower(CH2 value) { return TToLower<CH2>(value); }
CH4 ToLower(CH4 value) { return TToLower<CH4>(value); }

SI1 ToSigned(CH1 value) { return (SI1)value; }
SI2 ToSigned(CH2 value) { return (SI2)value; }
SI4 ToSigned(CH4 value) { return (SI4)value; }
SIN ToSigned(CHN value) { return (SIN)value; }
SI1 ToSigned(UI1 value) { return (SI1)value; }
SI2 ToSigned(UI2 value) { return (SI2)value; }
SI4 ToSigned(UI4 value) { return (SI4)value; }
SI8 ToSigned(UI8 value) { return (SI8)value; }
SI1 ToSigned(SI1 value) { return (SI1)value; }
SI2 ToSigned(SI2 value) { return (SI2)value; }
SI4 ToSigned(SI4 value) { return (SI4)value; }
SI8 ToSigned(SI8 value) { return (SI8)value; }
SIW ToSigned(const void* value) { return reinterpret_cast<SIW>(value); }
#if USING_FP4 == YES
SI4 ToSigned(FP4 value) { return *reinterpret_cast<SI4*>(&value); }
#endif
#if USING_FP8 == YES
SI8 ToSigned(FP8 value) { return *reinterpret_cast<SI8*>(&value); }
#endif

CH1 HexNibbleToLowerCase(UI1 b) {
  b = b & 0xf;
  if (b > 9) return b + ('a' - 10);
  return b + '0';
}

UI2 HexByteToLowerCase(UI1 b) {
  UI2 value = HexNibbleToLowerCase(b & 0xf);
  value = value << 8;
  value |= HexNibbleToLowerCase(b >> 4);
  return value;
}

UI2 HexByteToUpperCase(UI1 b) {
  UI2 value = (UI2)HexNibbleToUpperCase(b & 0xf);
  value = value << 8;
  UI2 second_nibble = HexNibbleToUpperCase(b >> 4);
  value |= second_nibble;
  return value;
}

SI4 HexToByte(CH1 c) {
  if (c < '0') {
    return -1;
  }
  if (c >= 'a') {
    if (c > 'f') return -1;
    return c - ('a' - 10);
  }
  if (c >= 'A') {
    if (c > 'F') return -1;
    return c - ('A' - 10);
  }
  if (c > '9') return -1;
  return c - '0';
}

SI4 HexToByte(UI2 h) {
  SI4 lowerValue = HexToByte((CH1)(h >> 8));

  if (lowerValue < 0) return -1;

  SI4 upper_value = HexToByte((CH1)h);
  if (upper_value < 0) return -1;

  return lowerValue | (upper_value << 4);
}

CH1* Print(CH1* start, CH1* stop, CH1 c) {
  if (!start || start + 1 >= stop) return nullptr;
  *start++ = c;
  *start = 0;
  return start;
}
}  // namespace _

#if SEAM == SEAM_SCRIPT2_UTF
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif
namespace _ {
CH1* Print(CH1* start, CH1* stop, CH4 c) {
  if (!start || start >= stop) return nullptr;

  // | Byte 1   | Byte 2   | Byte 3   | Byte 4   | UTF-32 Result         |
  // |:--------:|:--------:|:--------:|:--------:|:---------------------:|
  // | 0aaaaaaa |          |          |          | 00000000000000aaaaaaa |
  // | 110aaaaa | 10bbbbbb |          |          | 0000000000aaaaabbbbbb |
  // | 1110aaaa | 10bbbbbb | 10cccccc |          | 00000aaaabbbbbbcccccc |
  // | 11110aaa | 10bbbbbb | 10cccccc | 10dddddd | aaabbbbbbccccccdddddd |
  if (!(c >> 7)) {  // 1 ASCII CH1.
    if (start + 1 >= stop) return nullptr;
    *start++ = (CH1)c;
  }
  CH2 lsb_mask = 0x3f, msb_mask = 0x80;
  if ((c >> 11) == 0) {  // 2 bytes.
    if (start + 2 >= stop) return nullptr;
    CH1 byte = (CH1)(0xC0 | (c >> 6));
    // PRINT ("\nPrinting 2:");
    // PRINT_HEX (c);
    // PRINT (" UTF8:");
    // PRINT_HEX (byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | (c & lsb_mask));
    // PRINT_HEX (byte);
    *start++ = byte;
  } else if ((c >> 16) == 0) {  // 3 bytes.
    if (start + 3 >= stop) return nullptr;
    CH1 byte = (CH1)(0xE0 | (c >> 12));
    // PRINT ("\nPrinting 3:");
    // PRINT_HEX (c);
    // PRINT (" UTF8:");
    // PRINT_HEX (byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | ((c >> 6) & lsb_mask));
    // PRINT_HEX (byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | (c & lsb_mask));
    // PRINT_HEX (byte);
    *start++ = byte;
  } else if ((c >> 21) == 0) {  // 4 bytes.
    if (start + 4 >= stop) return nullptr;
    CH1 byte = (CH1)(0xF0 | (c >> 18));
    // PRINT ("\nPrinting 4:");
    // PRINT_HEX (c);
    // PRINT (" UTF8:");
    // PRINT_HEX (byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | ((c >> 12) & lsb_mask));
    // PRINT_HEX (byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | ((c >> 6) & lsb_mask));
    // PRINT_HEX (byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | (c & lsb_mask));
    // PRINT_HEX (byte);
    *start++ = byte;
  } else {
    // PRINT ("\nUTF8 print Error:CH4 is out of range:");
    // PRINT_HEX (c);
    // PRINT (':');
    // PRINT ((UI4)c);
    return nullptr;
  }
  *start = 0;
  return start;
}

CH1* Print(CH1* start, SIW size, CH4 c) {
  return Print(start, start + size - 1, c);
}

CH4 ToCH4(CH1 c) {
#if CHAR_MIN == 0
  return (CH4)c;
#else
  return (CH4)(UI1)c;
#endif
}

const CH1* Scan(const CH1* string, CH4& result) {
  if (!string) return nullptr;
  CH4 c = ToCH4(*string++), lsb_mask = 0x3f, msb = 0x80;
  CH4 r = 0;

  if (!(c >> 7)) {
    r = (CH4)c;
  } else if ((c >> 5) == 0x6) {
    // PRINT ("  Scanning 2:");
    // PRINT_HEX ((CH1)c);
    r = (c & 31) << 6;
    c = ToCH4(*string++);
    // PRINT_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= c & (CH4)63;
    // PRINT ("  Result:");
    // PRINT_HEX (r);
  } else if ((c >> 4) == 0xE) {
    // PRINT ("  Scanning 3:");
    // PRINT_HEX ((CH1)c);
    r = ((CH4)(c & 15)) << 12;
    c = ToCH4(*string++);
    // PRINT_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= (c & 63) << 6;
    c = ToCH4(*string++);
    // PRINT_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= c & lsb_mask;
    // PRINT ("  Result:");
    // PRINT_HEX (r);
  } else if ((c >> 3) == 0x1E) {
    // PRINT ("  Scanning 4:");
    // PRINT_HEX ((CH1)c);
    r = ((CH4)(c & 7)) << 18;
    c = ToCH4(*string++);
    // PRINT_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= (c & lsb_mask) << 12;
    c = ToCH4(*string++);
    // PRINT_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= (c & lsb_mask) << 6;
    c = ToCH4(*string++);
    // PRINT_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= c & lsb_mask;
    // PRINT ("  Result:");
    // PRINT_HEX (r);
  } else {
    // PRINT ("\nUTF8 scan error:");
    // PRINT_HEX ((CH1)c);
    // PRINT ((SI4)c);
    return nullptr;
  }
  result = r;
  return string;
}

#if USING_UTF16 == YES

CH1* Print(CH1* start, CH1* stop, CH2 c) {
#if USING_UTF32 == YES
  return Print(start, stop, (CH4)c);
#else
  enum { k2ByteMSbMask = 0xC0, k3ByteMSbMask = 0xE0, k4ByteMSbMask = 0xF0 };
  if (!start) return nullptr;
  if (!(c >> 7)) {  // 1 byte.
    if (start + 1 >= stop) return nullptr;
    *start++ = (CH1)c;
    *start = 0;
    return start;
  }
  CH2 lsb_mask = 0x3f, msb_mask = 0x80;
  if (!(c >> 12)) {  // 2 bytes.
    if (start + 2 >= stop) return nullptr;
    *start++ = (CH1)(0xC0 | c >> 6);
    *start++ = (CH1)(msb_mask | ((c >> 6) & lsb_mask));
    *start = 0;
    return start;
  }  // else 3 bytes.
  if (start + 3 >= stop) return nullptr;
  *start++ = (CH1)(0xE0 | c >> 12);
  *start++ = (CH1)(msb_mask | ((c >> 6) & lsb_mask));
  *start++ = (CH1)(msb_mask | ((c >> 12) & lsb_mask));
  *start = 0;
  return start;
#endif
}

CH2* Print(CH2* start, CH2* stop, CH2 c) {
  if (!start || start + 1 >= stop) return nullptr;
  *start++ = c;
  *start = 0;
  return start;
}

CH2* Print(CH2* start, CH2* stop, CH1 c) { return Print(start, stop, (CH2)c); }

CH2* Print(CH2* start, CH2* stop, CH4 c) {
  // | Bytes {4N, 4N+ 1} | Bytes {4N + 2, 4N+ 3} | UTF-32 Result        |
  // |:-----------------:|:---------------------:|:--------------------:|
  // | 000000aaaaaaaaaa  |                       | 0000000000aaaaaaaaaa |
  // | 110110aaaaaaaaaa  | 110111bbbbbbbbbb      | aaaaaaaaaabbbbbbbbbb |
  if (!start || start + 1 >= stop) return nullptr;
  CH4 lsb_mask = 0x3f, lsb = c & lsb_mask, msb = c >> 10;
  if (!msb) {
    if (start + 1 >= stop) return nullptr;
    *start++ = (CH2)c;
    // PRINT ("\nPrinting 1:");
    // PRINT_HEX ((CH2)c);
    *start = 0;
    return start;
  } else {
    CH4 msb_mask = 0xDC00;
    if (msb >> 10) return nullptr;  // Non-Unicode value.
    if (start + 2 >= stop) return nullptr;
    CH2 nibble = (CH2)(lsb & msb_mask);
    // PRINT ("\nPrinting 2:");
    // PRINT_HEX ((CH2)nibble);
    *start++ = nibble;
    nibble = (CH2)(msb & msb_mask);
    // PRINT_HEX ((CH2)nibble);
    *start++ = nibble;
    *start = 0;
    return start;
  }
}

CH2* Print(CH2* start, SIW size, CH4 c) {
  return Print(start, start + size - 1, c);
}

const CH2* Scan(const CH2* string, CH4& result) {
  if (!string) return nullptr;
  // | Bytes {4N, 4N+ 1} | Bytes {4N + 2, 4N+ 3} | UTF-32 Result        |
  // |:-----------------:|:---------------------:|:--------------------:|
  // | 000000aaaaaaaaaa  |                       | 0000000000aaaaaaaaaa |
  // | 110110aaaaaaaaaa  | 110111bbbbbbbbbb      | aaaaaaaaaabbbbbbbbbb |
  CH2 c = *string++;
  CH2 lsb_mask = (1 << 10) - 1;
  if (c <= lsb_mask) {
    // PRINT (" Scanning 1:");
    // PRINT_HEX (c);
    result = (CH4)c;
  } else if ((c >> 10) == 30) {
    // PRINT (" Scanning 1:");
    // PRINT_HEX (c);
    CH4 r = ((CH4)c) & lsb_mask;
    c = *string++;
    if (c >> 10 != 55) return nullptr;
    r |= ((CH4)(c & lsb_mask)) << 10;
  } else {
    // PRINT (" Scan error:");
    // PRINT_HEX (c);
    return nullptr;
  }
  return string;
}

const CH4* Scan(const CH4* string, CH4& result) {
  if (!string) return string;
  result = *string++;
  return string;
}

#endif
#if USING_UTF32 == YES
CH4* Print(CH4* start, CH4* stop, CH1 c) {
  if (!start || start + 1 >= stop) return nullptr;
  *start++ = (CH4)c;
  *start = 0;
  return start;
}

CH4* Print(CH4* start, CH4* stop, CH2 c) {
  if (!start || start + 1 >= stop) return nullptr;
  *start++ = (CH4)c;
  *start = 0;
  return start;
}

CH4* Print(CH4* start, CH4* stop, CH4 c) {
  if (!start || start + 1 >= stop) return nullptr;
  *start++ = c;
  *start = 0;
  return start;
}

#endif

}  // namespace _

#if SEAM >= SEAM_SCRIPT2_FTOS
//#include <cmath>

#if SEAM == SEAM_SCRIPT2_FTOS
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

#include <cstdio>

namespace _ {

CH1* Print(CH1* start, CH1* stop, FP4 value) {
  if (!start || start >= stop) return nullptr;
  SIW size = stop - start;
  D_PRINTF("\ncursor:%p end:%p size:%i\nExpecting:%f", start, stop, (SI4)size,
           value);
  SI4 count = sprintf_s(start, stop - start, "%f", value);
  if (count <= 0) return nullptr;
  return start + count;
  // return TBinary<FP4, UI4>::TPrint<CH1>(start, stop, value);
}

CH1* Print(CH1* start, CH1* stop, FP8 value) {
  if (!start || start >= stop) return nullptr;
  SIW size = stop - start;
  SI4 count = sprintf_s(start, size, "%lf", value);
  if (count <= 0) return nullptr;
  return start + count;
  // return TBinary<FP8, UI8>::TPrint<CH1>(start, stop, value);
}

template <typename Char>
const Char* TStrandFloatStop(const Char* start) {
  const CH1* stop = TSTRDecimalEnd<CH1>(start);
  if (!stop) return stop;
  CH1 c = *stop++;
  if (c == '.') {
    stop = TSTRDecimalEnd<CH1>(start);
    c = *stop++;
  }
  if (c == 'e' || c != 'E') {
    if (c == '-') c = *stop++;
    return TSTRDecimalEnd<CH1>(start);
  }
  return stop;
}

const CH1* Scan(const CH1* start, FP4& value) {
  SI4 count = sscanf_s(start, "%f", &value);
  return TStrandFloatStop<CH1>(start);
}

const CH1* Scan(const CH1* start, FP8& value) {
  SI4 count = sscanf_s(start, "%lf", &value);
  return TStrandFloatStop<CH1>(start);
}

#if USING_FP4 == YES
SI4 FloatDigitsMax() { return 15; }
#endif
#if USING_FP8 == YES
SI4 DoubleDigitsMax() { return 31; }
#endif

SI4 MSbAsserted(UI1 value) { return TMSbAssertedReverse<UI1>(value); }

SI4 MSbAsserted(SI1 value) { return TMSbAssertedReverse<UI1>((UI8)value); }

SI4 MSbAsserted(UI2 value) { return TMSbAssertedReverse<UI2>(value); }

SI4 MSbAsserted(SI2 value) { return TMSbAssertedReverse<UI2>((UI8)value); }

SI4 MSbAsserted(UI4 value) { return TMSbAssertedReverse<UI4>(value); }

SI4 MSbAsserted(SI4 value) { return TMSbAssertedReverse<UI4>((UI8)value); }

SI4 MSbAsserted(UI8 value) { return TMSbAssertedReverse<UI8>(value); }

SI4 MSbAsserted(SI8 value) { return TMSbAssertedReverse<UI8>((UI8)value); }

void FloatBytes(FP4 value, CH1& byte_0, CH1& byte_1, CH1& byte_2, CH1& byte_3) {
  UI4 ui_value = *reinterpret_cast<UI4*>(&value);
  byte_0 = (CH1)(ui_value);
  byte_1 = (CH1)(ui_value >> 8);
  byte_2 = (CH1)(ui_value >> 16);
  byte_3 = (CH1)(ui_value >> 24);
}

CH1* Print(CH1* begin, UI2 chars) {
#if ALIGN_MEMORY
  *reinterpret_cast<UI2*>(chars);
  return begin + 2;
#else
  *reinterpret_cast<UI2*>(chars);
  return begin + 2;
#endif
}

CH1* Print(CH1* begin, CH1 byte_0, CH1 byte_1) {
#if ALIGN_MEMORY
  if (reinterpret_cast<UIW>(begin) & 1) {
    begin[0] = byte_1;
    begin[1] = NIL;
  }
  if (align == 0) begin[0] = byte_0;
  begin[0] = byte_0;
  begin[1] = NIL;
#else
  *reinterpret_cast<UI2*>(begin) = byte_0 | (((UI2)byte_1) << 8);
#endif
  return &begin[2];
}

CH1* Print(CH1* begin, CH1* stop, CH1 byte_0, CH1 byte_1, CH1 byte_2) {
#if ALIGN_MEMORY
  switch (reinterpret_cast<UIW>(begin) & 3) {
    case 0: {
      *reinterpret_cast<UI4*>(begin) = ((UI4)byte_0) | ((UI4)byte_1) << 8 |
                                       ((UI4)byte_1) << 16 |
                                       ((UI4)byte_1) << 24;
      return &begin[4];
    }
    case 1: {
      UI4* ptr = reinterpret_cast<UI4*>(begin) - 1;
      UI4 word = (*ptr) & ((UI4)0xff) << 24;  //< Mask off byte_0 UI1.
      *ptr = word;
      begin[3] = 0;
      return &begin[4];
    }
    case 2: {
      UI2 ptr = *reinterpret_cast<UI2*>(begin);
      *ptr++ = ((UI2)byte_0) | ((UI2)byte_1) << 8;
      *ptr++ = ((UI2)byte_2) | ((UI2)byte_3) << 8;
      return reinterpret_cast<CH1*>(ptr);
    }
    case 3: {
      *begin = byte_0;
      UI4* ptr = reinterpret_cast<UI4*>(begin) - 1;
      UI4 word = (*ptr) & ((UI4)0xff) << 24;  //< Mask off byte_0 UI1.
      word |= ((UI4)byte_0) | ((UI4)byte_0) << 8 |
              ((UI4)byte_0) << 16;  //< OR together three.
      begin[3] = 0
    }
  }
#else
  *reinterpret_cast<UI4*>(begin) = ((UI4)byte_0) | ((UI4)byte_1) << 8 |
                                   ((UI4)byte_1) << 16 | ((UI4)byte_1) << 24;
#endif
  return &begin[4];
}

// CH1 puff_lut[2 * 100 + (8 + 2) * 87]; //< Experiment for cache aligned LUT.

constexpr SIW IEEE754LutElementCount() { return 87; }

const UI2* DigitsLut(const CH1* puff_lut) {
  return reinterpret_cast<const UI2*>(puff_lut);
}

const UI2* PuffLutExponents(CH1* puff_lut) {
  return reinterpret_cast<const UI2*>(puff_lut + 200);
}

const UI8* PufLutPow10(CH1* puff_lut) {
  return reinterpret_cast<const UI8*>(puff_lut + 374);
}

UI4 Value(FP4 value) { return *reinterpret_cast<UI4*>(&value); }

UI8 Value(FP8 value) { return *reinterpret_cast<UI8*>(&value); }

BOL IsNaNPositive(SI1 value) { return value > TUnsignedNaN<SI1>(); }

BOL IsNaNNegative(SI1 value) { return value > TUnsignedNaN<SI1>(); }

BOL IsNaN(FP4 value) { return isnan(value); }

BOL IsNaN(FP8 value) { return isnan(value); }

BOL IsFinite(FP4 value) { return isfinite(value); }

BOL IsFinite(FP8 value) { return isfinite(value); }

BOL IsInfinite(FP4 value) { return isinf(value); }

BOL IsInfinite(FP8 value) { return isinf(value); }

FP8 Ceiling(FP8 value) { return ceil(value); }

FP4 Ceiling(FP4 value) { return ceil(value); }

CH1* LastByte(CH1* c) { return c; }

#if USING_UTF16 == YES
CH1* LastByte(CH2* c) { return reinterpret_cast<CH1*>(c) + 1; }

CH2* Print(CH2* start, CH2* stop, FP4 value) {
  return TBinary<FP4, SI4, UI4>::template Print<CH2>(start, stop, value);
}

CH2* Print(CH2* start, CH2* stop, FP8 value) {
  return TBinary<FP8, SI8, UI8>::template Print<CH2>(start, stop, value);
}
#endif

#if USING_UTF32 == YES
CH1* LastByte(CH4* c) { return reinterpret_cast<CH1*>(c) + 3; }

CH4* Print(CH4* start, CH4* stop, FP4 value) {
  return TBinary<FP4, SI4, UI4>::template Print<CH4>(start, stop, value);
}

CH4* Print(CH4* start, CH4* stop, FP8 value) {
  return TBinary<FP8, SI8, UI8>::template Print<CH4>(start, stop, value);
}
#endif

}  // namespace _

#endif
