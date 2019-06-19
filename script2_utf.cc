/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_strand.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#if SEAM >= SCRIPT2_SEAM_UTF
#if SEAM == SCRIPT2_SEAM_UTF
#include "module_release.inl"
#else
#include "module_release.inl"
#endif

#include "t_utf.h"

#if USING_UTF8 == YES

namespace _ {
CH1 HexNibbleToUpperCase(UI1 b) {
  b = b & 0xf;
  if (b > 9) return b + ('A' - 10);
  return b + '0';
}

const CH1* STRSocketHeader() {
  return "\n|0       8       16      24      32      40      48      56      |";
}

const CH1* STRSocketBorder() {
  return "\n|+-------+-------+-------+-------+-------+-------+-------+-------|"
         " ";
}

const CH1* STRSocketHexHeader() {
  return "\n|0               8               16              24              |";
}

const CH1* STRSocketHexBorder() {
  return "\n|+---------------+---------------+---------------+---------------|"
         " ";
}

UI1 ToUnsigned(CH1 value) { return (UI1)value; }
UI2 ToUnsigned(CH2 value) { return (UI2)value; }
UI4 ToUnsigned(CH4 value) { return (UI4)value; }
UIN ToUnsigned(CHN value) { return (UIN)value; }
UI1 ToUnsigned(SI1 value) { return (UI1)value; }
UI2 ToUnsigned(SI2 value) { return (UI2)value; }
UI4 ToUnsigned(SI4 value) { return (UI4)value; }
UI8 ToUnsigned(SI8 value) { return (UI4)value; }
UI1 ToUnsigned(UI1 value) { return (UI1)value; }
UI2 ToUnsigned(UI2 value) { return (UI2)value; }
UI4 ToUnsigned(UI4 value) { return (UI4)value; }
UI8 ToUnsigned(UI8 value) { return (UI8)value; }
UIW ToUnsigned(const void* value) { return reinterpret_cast<UIW>(value); }
#if USING_FP4 == YES
UI4 ToUnsigned(FP4 value) { return *reinterpret_cast<UI4*>(&value); }
#endif
#if USING_FP8 == YES
UI8 ToUnsigned(FP8 value) { return *reinterpret_cast<UI8*>(&value); }
#endif

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

Hex::Hex(const void* begin) : size_(sizeof(UIW)) {
  *buffer_ = reinterpret_cast<UIW>(begin);
}
Hex::Hex(const void* begin, SIW size) : size_(-size) {
  buffer_[0] = reinterpret_cast<UIW>(begin);
}
Hex::Hex(SI1 item) : size_(1) { *reinterpret_cast<SI1*>(buffer_) = item; }
Hex::Hex(UI1 item) : size_(1) { *reinterpret_cast<UI1*>(buffer_) = item; }
Hex::Hex(SI2 item) : size_(2) { *reinterpret_cast<SI2*>(buffer_) = item; }
Hex::Hex(UI2 item) : size_(2) { *reinterpret_cast<UI2*>(buffer_) = item; }
Hex::Hex(SI4 item) : size_(4) { *reinterpret_cast<SI4*>(buffer_) = item; }
Hex::Hex(UI4 item) : size_(4) { *reinterpret_cast<UI4*>(buffer_) = item; }
Hex::Hex(SI8 item) : size_(8) { *reinterpret_cast<SI8*>(buffer_) = item; }
Hex::Hex(UI8 item) : size_(8) { *reinterpret_cast<UI8*>(buffer_) = item; }
#if USING_FP8 == YES
Hex::Hex(FP4 item) : size_(4) { *reinterpret_cast<FP4*>(buffer_) = item; }
#endif
#if USING_FP8 == YES
Hex::Hex(FP8 item) : size_(8) { *reinterpret_cast<FP8*>(buffer_) = item; }
#endif

const CH1* Hex::Begin() {
  if (size_ < 0) return reinterpret_cast<const CH1*>(buffer_[0]);
  return reinterpret_cast<const CH1*>(&buffer_[0]);
}

SIW Hex::Size() {
  SIW l_size = size_;
  return l_size < 0 ? -l_size : l_size;
}

Binary::Binary(const void* begin) : size_(sizeof(UIW)) {
  *buffer_ = reinterpret_cast<UIW>(begin);
}
Binary::Binary(const void* begin, SIW size) : size_(-size) {
  *buffer_ = reinterpret_cast<UIW>(begin);
}
Binary::Binary(SI1 item) : size_(1) { *reinterpret_cast<SI1*>(buffer_) = item; }
Binary::Binary(UI1 item) : size_(1) { *reinterpret_cast<UI1*>(buffer_) = item; }
Binary::Binary(SI2 item) : size_(2) { *reinterpret_cast<SI2*>(buffer_) = item; }
Binary::Binary(UI2 item) : size_(2) { *reinterpret_cast<UI2*>(buffer_) = item; }
Binary::Binary(SI4 item) : size_(4) { *reinterpret_cast<SI4*>(buffer_) = item; }
Binary::Binary(UI4 item) : size_(4) { *reinterpret_cast<UI4*>(buffer_) = item; }
Binary::Binary(SI8 item) : size_(8) { *reinterpret_cast<SI8*>(buffer_) = item; }
Binary::Binary(UI8 item) : size_(8) { *reinterpret_cast<UI8*>(buffer_) = item; }

#if USING_FP8 == YES
Binary::Binary(FP4 item) : size_(4) { *reinterpret_cast<FP4*>(buffer_) = item; }
#endif
#if USING_FP8 == YES
Binary::Binary(FP8 item) : size_(8) { *reinterpret_cast<FP8*>(buffer_) = item; }
#endif

const CH1* Binary::Begin() {
  if (size_ < 0) return reinterpret_cast<const CH1*>(buffer_[0]);
  return reinterpret_cast<const CH1*>(&buffer_[0]);
}

SIW Binary::Size() {
  SIW l_size = size_;
  return l_size < 0 ? -l_size : l_size;
}

}  // namespace _

#if SEAM >= SCRIPT2_SEAM_ITOS
namespace _ {

/*
SI4 TSTRLength(UI8 value) {
  if (value < 10) return 1;
  if (value < 100) return 2;
  if (value < 1000) return 3;
  if (value < 10000) return 4;
  if (value < 100000) return 5;
  if (value < 1000000) return 6;
  if (value < 10000000) return 7;
  if (value < 100000000) return 8;
  if (value < 1000000000) return 9;
  if (value < 10000000000) return 10;
  if (value < 100000000000) return 11;
  if (value < 1000000000000) return 12;
  if (value < 10000000000000) return 13;
  if (value < 100000000000000) return 14;
  if (value < 1000000000000000) return 15;
  if (value < 10000000000000000) return 16;
  if (value < 100000000000000000) return 17;
  if (value < 1000000000000000000) return 18;
  if (value < 10000000000000000000) return 19;
  return 20;
}

template <typename Char>
Char* PrintMod10(Char* start, Char* stop, UI4 value) {
  if (!start || start >= stop) return nullptr;

  UI4 length;
  if (value < 10) {
    if (start + 1 >= stop) return nullptr;
    *start = '0' + value;
    *(start + 1) = 0;
    return start + 1;
  } else if (value < 100) {
    UI4 ten = 10;
    length = value / 10;

  } else if (value < 1000)
    length = 3;
  else if (value < 10000)
    length = 4;
  else if (value < 100000)
    length = 5;
  else if (value < 1000000)
    length = 6;
  else if (value < 10000000)
    length = 7;
  else if (value < 100000000)
    length = 8;
  else if (value < 1000000000)
    length = 9;
  else if (value < 10000000000)
    length = 10;
  else if (value < 100000000000)
    length = 11;
  else
    length = 12;
  Char* stop = start + length - 1;
  if (stop >= stop) return nullptr;
  UI4 ten = 10;
  while (length > 0) {
    UI4 scalar = value / ten;
  }
}
*/

// CH1* PrintMod10(CH1* start, CH1* stop, UI8 value);

UI1 Unsigned(SI1 value) { return (UI1)(value); }

UI2 Unsigned(SI2 value) { return (UI2)(value); }

UI4 Unsigned(SI4 value) { return (UI4)(value); }

UI8 Unsigned(SI8 value) { return (UI8)(value); }

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
  UI2 value = HexNibbleToUpperCase(b & 0xf);
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

#if SEAM == SCRIPT2_SEAM_UTF
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

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
#endif
#if USING_UTF16 == YES

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
#endif

#if SEAM >= SCRIPT2_SEAM_FTOS
//#include <cmath>

#if SEAM == SCRIPT2_SEAM_FTOS
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

#include <cstdio>

namespace _ {

CH1* Print(CH1* start, CH1* stop, FP4 value) {
  if (!start || start >= stop) return nullptr;
  SIW size = stop - start;
  PRINTF("\ncursor:%p end:%p size:%i\nExpecting:%f", start, stop, (SI4)size,
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

/* Masks the lower bits using faster bit shifting.
@brief The algorithm has you enter the highest bit rather than bit count because
it would introduce an extra instruction and you should do that manually if you
wish to do so.
@param value The value to mask.
@param left_bits Number of bits to shift left.
@param right_bits Number of bits to shift right. */
template <typename UI>
inline UI ShiftLeftRight(UI value, SI4 left_bits, SI4 right_bits) {
  value = value << left_bits;
  return value >> right_bits;
}

/* Creates a mask with the given number_ of zeros in the MSb(s).
@param msb_zero_count The number_ of zeros in the Most Significant bits. */
template <typename UI>
inline UI CreateMaskLSb(UI msb_zero_count) {
  UI mask = 0;
  return (~mask) >> msb_zero_count;
}

/* Masks off the lower bits. */
template <typename UI>
inline UI MaskLSb(UI value, UI msb_zero_count) {
  return value & CreateMaskLSb<UI>(msb_zero_count);
}

/* Returns 2^n. */
template <typename I>
inline I PowerOf2(I n) {
  I value = 1;
  return value << n;
}

UI8 ComputePow10(SI4 e, SI4 alpha, SI4 gamma) {
  FP8 pow_10 = 0.30102999566398114,  //< 1/lg(10)
      alpha_minus_e_plus_63 = static_cast<FP8>(alpha - e + 63),
      ceiling = Ceiling(alpha_minus_e_plus_63 * pow_10);
  return *reinterpret_cast<UI8*>(&pow_10);
}

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

//-----------------------------------------------------------------------------
// UTF implmementations.
//-----------------------------------------------------------------------------

/*
SI4 COutHeap1(Autoject& obj, SIW function, void* arg) {
  return TCOutHeap<CH1>(obj, function, arg);
}*/

const CH1* StringEmpty() { return TSTREmpty<CH1>(); }

const CH1* StringNL() { return TSTRNL<CH1>(); }

const CH1* StringError() { return TSTRError<CH1>(); }

BOL IsWhitespace(CH1 item) { return TIsWhitespace<CH1>(item); }

CH1 PrintableChar(CH1 item) { return TCharPrintable<CH1>(item); }

const CH1* STREnd(const CH1* start) { return TSTREnd<CH1>(start); }

SI4 StrandLength(const CH1* start) { return TSTRLength<CH1, SI4>(start); }

const CH1* StrandLineEnd(const CH1* start, SI4 count) {
  return TSTRLineEnd<CH1>(start, count);
}

const CH1* StrandLineEnd(const CH1* start, const CH1* stop, SI4 count) {
  return TSTRLineEnd<CH1>(start, stop, count);
}

const CH1* StrandDecimalStop(const CH1* start, const CH1* stop) {
  return TSTRDecimalEnd<CH1>(start);
}

const CH1* StrandDecimalStop(const CH1* start) {
  return TSTRDecimalEnd<CH1>(start);
}

const CH1* STRSkipChar(const CH1* start, CH1 skip_char) {
  return TSTRSkipChar<CH1>(start, skip_char);
}

const CH1* STRSkipSpaces(const CH1* start) {
  return TSTRSkipSpaces<CH1>(start);
}

const CH1* STRSkipSpaces(const CH1* start, const CH1* stop) {
  return TSTRSkipSpaces<CH1>(start, stop);
}

const CH1* STREquals(const CH1* text_a, const CH1* text_b) {
  return TSTREquals<CH1>(text_a, text_b);
}

const CH1* STREquals(const CH1* start, const CH1* stop, const CH1* query) {
  return TSTREquals<CH1>(start, stop, query);
}

SI4 STRCompare(const CH1* text_a, const CH1* text_b) {
  return TSTRCompare<CH1>(text_a, text_b);
}
/*
SI4 STRCompare(const CH1* text_a, const CH1* stop,
                  const CH1* text_b) {
  return TSTRCompare<CH1>(text_a, stop, text_b);
}*/

const CH1* STRFind(const CH1* start, const CH1* query) {
  return TSTRFind<CH1>(start, query);
}

CH1* Print(CH1* start, CH1* stop, const CH1* item) {
  return TPrint<CH1>(start, stop, item);
}

#if USING_UTF16 == YES
CH1* Print(CH1* start, CH1* stop, const CH2* item) {
  return TPrint<CH1>(start, stop, item);
}
#endif

#if USING_UTF32 == YES
CH1* Print(CH1* start, CH1* stop, const CH4* item) {
  return TPrint<CH1>(start, stop, item);
}
#endif

CH1* Print(CH1* start, CH1* stop, UI8 item) {
  return TPrintUnsigned<UI8, CH1>(start, stop, item);
}

CH1* Print(CH1* start, CH1* stop, SI8 item) {
  return TPrintSigned<SI8, UI8, CH1>(start, stop, item);
}

#if ALU_SIZE != 32
CH1* Print(CH1* start, CH1* stop, UI4 item) {
  return Print(start, stop, (UI8)item);
}

CH1* Print(CH1* start, CH1* stop, SI4 item) {
  return Print(start, stop, (SI8)item);
}
#else
CH1* Print(CH1* start, CH1* stop, UI4 item) {
  return TPrintUnsigned<UI8, CH1>(start, stop, (UI8)item);
}

CH1* Print(CH1* start, CH1* stop, SI4 item) {
  return TPrintSigned<SI8, UI8, CH1>(start, stop, (SI8)item);
}
#endif

#if USING_FP4 == YES
CH1* PrintCenter(CH1* start, CH1* stop, FP4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, FP4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}
#endif
#if USING_FP8 == YES
CH1* PrintCenter(CH1* start, CH1* stop, FP8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, FP8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

#endif

CH1* PrintCenter(CH1* start, CH1* stop, const CH1* begin, SI4 count) {
  return TPrintCenter<CH1>(start, stop, begin, count);
}

CH1* PrintCenter(CH1* start, CH1* stop, CH1 item, SI4 count) {
  return TPrintCenter<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, SI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, UI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, UI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, SI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, const CH1* item, SI4 count) {
  return TPrintRight<CH1>(start, stop, item, count);
}

CH1* PrintRight(CH1* start, CH1* stop, CH1 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, UI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, SI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, UI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, SI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintHex(CH1* start, CH1* stop, const void* ptr) {
  return TPrintHex<CH1>(start, stop, ptr);
}

CH1* PrintHex(CH1* start, CH1* stop, UI1 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, SI1 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, UI2 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, SI2 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, UI4 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, SI4 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, UI8 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, SI8 item) {
  return TPrintHex<CH1>(start, stop, item);
}

#if USING_FP4 == YES
CH1* PrintHex(CH1* start, CH1* stop, FP4 item) {
  return TPrintHex<CH1>(start, stop, item);
}
#endif
#if USING_FP8 == YES
CH1* PrintHex(CH1* start, CH1* stop, FP8 item) {
  return TPrintHex<CH1>(start, stop, item);
}
#endif

CH1* PrintBinary(CH1* start, CH1* stop, const void* ptr) {
  return TPrintBinary<CH1>(start, stop, ptr);
}

CH1* PrintBinary(CH1* start, CH1* stop, UI1 item) {
  return TPrintBinary<CH1, UI1>(start, stop, item);
}

CH1* PrintBinary(CH1* start, CH1* stop, SI1 item) {
  return TPrintBinary<CH1, UI1>(start, stop, (UI1)item);
}

CH1* PrintBinary(CH1* start, CH1* stop, UI2 item) {
  return TPrintBinary<CH1, UI2>(start, stop, item);
}

CH1* PrintBinary(CH1* start, CH1* stop, SI2 item) {
  return TPrintBinary<CH1, UI2>(start, stop, (UI2)item);
}

CH1* PrintBinary(CH1* start, CH1* stop, UI4 item) {
  return TPrintBinary<CH1, UI4>(start, stop, item);
}

CH1* PrintBinary(CH1* start, CH1* stop, SI4 item) {
  return TPrintBinary<CH1, UI4>(start, stop, item);
}

CH1* PrintBinary(CH1* start, CH1* stop, UI8 item) {
  return TPrintBinary<CH1, UI8>(start, stop, item);
}

CH1* PrintBinary(CH1* start, CH1* stop, SI8 item) {
  return TPrintBinary<CH1, UI8>(start, stop, item);
}

#if USING_FP4 == YES
CH1* PrintBinary(CH1* start, CH1* stop, FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return TPrintBinary<CH1, UI4>(start, stop, ui);
}
#endif
#if USING_FP8 == YES
CH1* PrintBinary(CH1* start, CH1* stop, FP8 item) {
  UI8 ui = *reinterpret_cast<UI8*>(&item);
  return TPrintBinary<CH1, UI8>(start, stop, ui);
}
#endif
CH1* PrintChars(CH1* start, CH1* stop, const void* begin, const void* end) {
  return TPrintSocket<CH1>(start, stop, begin, end);
}

CH1* PrintChars(CH1* start, CH1* stop, const void* begin, SIW size) {
  const CH1* ptr = reinterpret_cast<const CH1*>(begin);
  return PrintChars(start, stop, begin, ptr + size - 1);
}

CH1* PrintLinef(CH1* start, CH1* stop, CH1 token, SI4 count) {
  return TPrintLinef<CH1>(start, stop, token, count);
}

CH1* PrintLinef(CH1* start, CH1* stop, const CH1* item, SI4 count) {
  return TPrintLinef<CH1>(start, stop, item, count);
}

CH1* PrintRepeat(CH1* start, CH1* stop, CH1 token, SI4 count) {
  return TPrintHeadingf<CH1>(start, stop, token, count);
}

CH1* PrintRepeat(CH1* start, CH1* stop, const CH1* item, SI4 count) {
  return TPrintHeadingf<CH1>(start, stop, item, count);
}

const CH1* Scan(const CH1* start, SI1& result) {
  return TScanSigned<SI1, UI1, CH1>(start, result);
}

const CH1* Scan(const CH1* start, UI1& result) {
  return TScanUnsigned<UI1, CH1>(start, result);
}

const CH1* Scan(const CH1* start, SI2& result) {
  return TScanSigned<SI2, UI2, CH1>(start, result);
}

const CH1* Scan(const CH1* start, UI2& result) {
  return TScanUnsigned<UI2, CH1>(start, result);
}

const CH1* Scan(const CH1* start, SI4& result) {
  return TScanSigned<SI4, UI4, CH1>(start, result);
}

const CH1* Scan(const CH1* start, UI4& result) {
  return TScanUnsigned<UI4, CH1>(start, result);
}

const CH1* Scan(const CH1* start, SI8& result) {
  return TScanSigned<SI8, UI8, CH1>(start, result);
}

const CH1* Scan(const CH1* start, UI8& result) {
  return TScanUnsigned<UI8, CH1>(start, result);
}

Token1::Token1(const CH1* item, SI4 count) : string_(item), count_(count) {
  Print(item);
}

#if USING_UTF16 == YES
Token1::Token1(CH2 item, SI4 count) : string_(strand_), count_(count) {
  Print(item);
}

Token1::Token1(const CH2* item, SI4 count) : string_(strand_), count_(count) {}
#endif

#if USING_UTF32 == YES
Token1::Token1(CH4 item, SI4 count) : string_(strand_), count_(count) {
  Print(item);
}

Token1::Token1(const CH4* item, SI4 count) : count_(count) { Print(item); }
#endif

Token1::Token1(SI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token1::Token1(UI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token1::Token1(SI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token1::Token1(UI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

#if USING_FP4 == YES
Token1::Token1(FP4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif
#if USING_FP8 == YES
Token1::Token1(FP8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif

const CH1* Token1::String() { return string_; }

CH1* Token1::Strand() { return strand_; }

const CH1* Token1::Set(const CH1* string) {
  if (!string) return string;
  string_ = string;
  return string;
}

const CH1* Token1::Get() {
  const CH1* string = string_;
  return string ? string : strand_;
}

SI4 Token1::Count() { return count_; }

CH1* Token1::Print(CH1 item) {
  return ::_::Print(strand_, strand_ + kTokenLongest, item);
}

CH1* Token1::Print(const CH1* item) {
  CH1* cursor = ::_::TPrint<CH1>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#if USING_UTF16 == YES
CH1* Token1::Print(CH2 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH1* Token1::Print(const CH2* item) {
  CH1* cursor = ::_::TPrint<CH1>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_UTF32 == YES
CH1* Token1::Print(CH4 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH1* Token1::Print(const CH4* item) {
  CH1* cursor = ::_::TPrint<CH1>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

CH1* Token1::Print(SI4 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH1* Token1::Print(UI4 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH1* Token1::Print(SI8 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH1* Token1::Print(UI8 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#if USING_FP4 == YES
CH1* Token1::Print(FP4 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_FP8 == YES
CH1* Token1::Print(FP8 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

Center1::Center1(CH1 item, SI4 count) : token(item, count) {}

Center1::Center1(const CH1* item, SI4 count) : token(item, count) {}

#if USING_UTF16 == YES
Center1::Center1(CH2 item, SI4 count) : token(item, count) {}

Center1::Center1(const CH2* item, SI4 count) : token(item, count) {}
#endif

#if USING_UTF32 == YES
Center1::Center1(CH4 item, SI4 count) : token(item, count) {}

Center1::Center1(const CH4* item, SI4 count) : token(item, count) {}
#endif

Center1::Center1(SI4 item, SI4 count) : token(item, count) {}

Center1::Center1(UI4 item, SI4 count) : token(item, count) {}

Center1::Center1(SI8 item, SI4 count) : token(item, count) {}

#if USING_FP4 == YES
Center1::Center1(FP4 item, SI4 count) : token(item, count) {}
#endif
#if USING_FP8 == YES
Center1::Center1(FP8 item, SI4 count) : token(item, count) {}
#endif

Center1::Center1(UI8 item, SI4 count) : token(item, count) {}

Right1::Right1(CH1 item, SI4 count) : token(item, count) {}

Right1::Right1(const CH1* item, SI4 count) : token(item, count) {}

#if USING_UTF16 == YES
Right1::Right1(CH2 item, SI4 count) : token(item, count) {}

Right1::Right1(const CH2* item, SI4 count) : token(item, count) {}
#endif
#if USING_UTF32 == YES
Right1::Right1(CH4 item, SI4 count) : token(item, count) {}

Right1::Right1(const CH4* item, SI4 count) : token(item, count) {}
#endif

Right1::Right1(SI4 item, SI4 count) : token(item, count) {}

Right1::Right1(UI4 item, SI4 count) : token(item, count) {}

Right1::Right1(SI8 item, SI4 count) : token(item, count) {}

Right1::Right1(UI8 item, SI4 count) : token(item, count) {}

#if USING_FP4 == YES
Right1::Right1(FP4 item, SI4 count) : token(item, count) {}
#endif
#if USING_FP8 == YES
Right1::Right1(FP8 item, SI4 count) : token(item, count) {}
#endif

Linef1::Linef1(CH1 item, SI4 count) : token(token.Strand(), count) {
  CH1* strand = token.Strand();
  TPrint<CH1>(strand, strand + kTokenLongest, item);
}

Linef1::Linef1(const CH1* item, SI4 count) : token(token.Strand(), count) {
  CH1* strand = token.Strand();
  TPrint<CH1>(strand, strand + kTokenLongest, item);
}

Headingf1::Headingf1(const CH1* caption1, const CH1* style, SI4 count,
                     const CH1* caption2, const CH1* caption3)
    : caption(caption1, count),
      style(style),
      caption2(caption2),
      caption3(caption3) {}

Chars1::Chars1(const CH1* start, const CH1* stop) : start(start), stop(stop) {}

UTF1::UTF1(CH1* start, SIW buffer_size)
    : start(start), stop(start + buffer_size - 1) {
  DASSERT(start);
  DASSERT(buffer_size);
}

UTF1::UTF1(CH1* begin, CH1* stop) : start(start), stop(stop) {
  DASSERT(begin);
  DASSERT(begin < stop);
}

UTF1::UTF1(const UTF1& other) : start(other.start), stop(other.stop) {
  DASSERT(start);
  DASSERT(stop);
}

UTF1& UTF1::Set(CH1* new_cursor) {
  start = new_cursor;
  return *this;
}

UTF1& UTF1::Print(CH1 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(CH2 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(CH4 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(const CH1* item) {
  return Set(::_::Print(start, stop, item));
}

UTF1& UTF1::Print(const CH2* item) {
  return Set(::_::Print(start, stop, item));
}

UTF1& UTF1::Print(const CH4* item) {
  return Set(::_::Print(start, stop, item));
}

UTF1& UTF1::Print(SI4 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(UI4 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(SI8 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(UI8 item) { return Set(::_::Print(start, stop, item)); }

#if USING_FP4 == YES
UTF1& UTF1::Print(FP4 item) { return Set(::_::Print(start, stop, item)); }
#endif
#if USING_FP8 == YES
UTF1& UTF1::Print(FP8 item) { return Set(::_::Print(start, stop, item)); }
#endif

UTF1& UTF1::Print(Right1 item) {
  return Set(
      ::_::PrintRight(start, stop, item.token.Get(), item.token.Count()));
}

UTF1& UTF1::Print(Center1 item) {
  return Set(
      ::_::PrintCenter(start, stop, item.token.Get(), item.token.Count()));
}

UTF1& UTF1::Print(Linef1 item) {
  return Set(
      ::_::PrintLinef(start, stop, item.token.Get(), item.token.Count()));
}

UTF1& UTF1::Print(Headingf1 item) {
  return Set(
      ::_::PrintLinef(start, stop, item.caption.Get(), item.caption.Count()));
}

UTF1& UTF1::Hex(UI1 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI1 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(UI2 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI2 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(UI4 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI4 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(UI8 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI8 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

#if USING_FP4 == YES
UTF1& UTF1::Hex(FP4 item) { return Set(TPrintHex<CH1>(start, stop, item)); }
#endif
#if USING_FP8 == YES
UTF1& UTF1::Hex(FP8 item) { return Set(TPrintHex<CH1>(start, stop, item)); }
#endif

template <typename T, typename Char = CH1>
Char* TPrintHex(Char* start, Char* stop, const void* begin, SIW size_bytes) {
  Char* end = start + (size_bytes * 2);
  if (!start || size_bytes <= 0 || end < start) return nullptr;
  const UI1* cursor = reinterpret_cast<const UI1*>(begin);
  while (size_bytes-- > 0) {
    UI1 byte = *cursor++;
    *start++ = HexNibbleToUpperCase(byte >> 4);
    *start++ = HexNibbleToUpperCase(byte & 0xf);
  }
  *start = 0;
  return start;
}

UTF1& UTF1::Hex(const void* ptr) {
  return Set(TPrintHex<CH1>(start, stop, ptr));
}

UTF1& UTF1::Print(::_::Hex item) {
  return Set(TPrintHex<CH1>(start, stop, item.Begin(), item.Size()));
}

UTF1& UTF1::Binary(UI1 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(SI1 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(UI2 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(SI2 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(UI4 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(SI4 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(UI8 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(SI8 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

#if USING_FP4 == YES
UTF1& UTF1::Binary(FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH1>(start, stop, ui));
}
#endif
#if USING_FP8 == YES
UTF1& UTF1::Binary(FP8 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH1>(start, stop, ui));
}
#endif

UTF1& UTF1::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH1>(start, stop, ptr));
}

UTF1& UTF1::Print(Chars1 chars) {
  return Set(TPrintChars<CH1>(start, stop, chars.start, chars.stop));
}

Token1::Token1(CH1 item, SI4 count) : string_(strand_), count_(count) {
  TPrint1<CH1>(strand_, item);
}

}  // namespace _

::_::UTF1& operator<<(::_::UTF1& o, CH1 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, ::_::UTF1& p) { return o; }

::_::UTF1& operator<<(::_::UTF1& o, const CH1* item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, UI1 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, SI2 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, UI2 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, SI4 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, UI4 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, SI8 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, UI8 item) { return o.Print(item); }

#if USING_FP4 == YES
::_::UTF1& operator<<(::_::UTF1& o, FP4 item) { return o.Print(item); }
#endif
#if USING_FP8 == YES
::_::UTF1& operator<<(::_::UTF1& o, FP8 item) { return o.Print(item); }
#endif

::_::UTF1& operator<<(::_::UTF1& o, ::_::Hex item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, ::_::Center1 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, ::_::Right1 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, ::_::Linef1 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, ::_::Headingf1 item) {
  return o.Print(item);
}

::_::UTF1& operator<<(::_::UTF1& o, ::_::Chars1 item) { return o.Print(item); }

#if USING_UTF16 == YES
::_::UTF1& operator*(::_::UTF1& o, CH2 item) { return o.Print(item); }
::_::UTF1& operator*=(::_::UTF1& o, CH2 item) { return o.Print(item); }
::_::UTF1& operator*(::_::UTF1& o, const CH2* item) { return o.Print(item); }
#endif
#if USING_UTF32 == YES
::_::UTF1& operator<<(::_::UTF1& o, CH4 item) { return o.Print(item); }

::_::UTF1& operator*(::_::UTF1& o, const CH4* item) { return o.Print(item); }
#endif

#endif  //< #if USING_UTF8

#if USING_UTF16 == YES
namespace _ {

const CH2* Empty() { return TSTREmpty<CH2>(); }

const CH2* NewLine() { return TSTRNL<CH2>(); }

const CH2* ErrorHeader() { return TSTRError<CH2>(); }

BOL IsWhitespace(CH2 item) { return TIsWhitespace<CH2>(item); }

CH2 PrintableChar(CH2 item) { return TCharPrintable<CH2>(item); }

const CH2* STREnd(const CH2* start) { return TSTREnd<CH2>(start); }

SI4 StrandLength(const CH2* start) { return TSTRLength<CH2, SI4>(start); }

const CH2* StrandLineEnd(const CH2* start, SI4 count) {
  return TSTRLineEnd<CH2>(start, count);
}

const CH2* StrandLineEnd(const CH2* start, const CH2* stop, SI4 count) {
  return TSTRLineEnd<CH2>(start, stop, count);
}

const CH2* StrandDecimalEnd(const CH2* start, const CH2* stop) {
  return TSTRDecimalEnd<CH2>(start, stop);
}

const CH2* StrandDecimalEnd(const CH2* start) {
  return TSTRDecimalEnd<CH2>(start);
}

const CH2* STRSkipChar(const CH2* start, CH2 skip_char) {
  return TSTRSkipChar<CH2>(start, skip_char);
}

const CH2* STRSkipSpaces(const CH2* start) {
  return TSTRSkipSpaces<CH2>(start);
}

const CH2* STRSkipSpaces(const CH2* start, const CH2* stop) {
  return TSTRSkipSpaces<CH2>(start, stop);
}

const CH2* STREquals(const CH2* text_a, const CH2* text_b) {
  return TSTREquals<CH2>(text_a, text_b);
}

const CH2* STREquals(const CH2* start, const CH2* stop, const CH2* query) {
  return TSTREquals<CH2>(start, stop, query);
}

SI4 STRCompare(const CH2* text_a, const CH2* text_b) {
  return TSTRCompare<CH2>(text_a, text_b);
}

const CH2* STRFind(const CH2* start, const CH2* query) {
  return TSTRFind<CH2>(start, query);
}

#if USING_UTF8 == YES
CH2* Print(CH2* start, CH2* stop, const CH1* item) {
  return TPrint<CH2>(start, stop, item);
}
#endif

CH2* Print(CH2* start, CH2* stop, const CH2* item) {
  return TPrint<CH2>(start, stop, item);
}

#if USING_UTF32 == YES
CH2* Print(CH2* start, CH2* stop, const CH4* item) {
  return TPrint<CH2>(start, stop, item);
}
#endif

CH2* Print(CH2* start, CH2* stop, UI4 item) {
  return TPrintUnsigned<UI4, CH2>(start, stop, item);
}

CH2* Print(CH2* start, CH2* stop, SI4 item) {
  return TPrintSigned<SI4, UI4, CH2>(start, stop, item);
}

CH2* Print(CH2* start, CH2* stop, UI8 item) {
  return TPrintUnsigned<UI8, CH2>(start, stop, item);
}

CH2* Print(CH2* start, CH2* stop, SI8 item) {
  return TPrintSigned<SI8, UI8, CH2>(start, stop, item);
}

CH2* PrintCenter(CH2* start, CH2* stop, const CH2* item, SI4 count) {
  return TPrintCenter<CH2>(start, stop, item, count);
}

CH2* PrintCenter(CH2* start, CH2* stop, CH2 item, SI4 count) {
  return TPrintCenter<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintCenter(CH2* start, CH2* stop, SI4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintCenter(CH2* start, CH2* stop, UI4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintCenter(CH2* start, CH2* stop, UI8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintCenter(CH2* start, CH2* stop, SI8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

#if USING_FP4 == YES
CH2* PrintCenter(CH2* start, CH2* stop, FP4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}
CH2* PrintRight(CH2* start, CH2* stop, FP4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}
CH2* PrintHex(CH2* start, CH2* stop, FP4 item) {
  return TPrintHex<CH2>(start, stop, item);
}
CH2* PrintBinary(CH2* start, CH2* stop, FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Print(start, stop, ui);
}
const CH2* Scan(const CH2* start, FP4& result) {
  return TScan<CH2>(start, result);
}
#endif
#if USING_FP8 == YES
CH2* PrintCenter(CH2* start, CH2* stop, FP8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}
CH2* PrintRight(CH2* start, CH2* stop, FP8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}
CH2* PrintHex(CH2* start, CH2* stop, FP8 item) {
  return TPrintHex<CH2>(start, stop, item);
}
CH2* PrintBinary(CH2* start, CH2* stop, FP8 item) {
  UI8 ui = *reinterpret_cast<UI8*>(&item);
  return Print(start, stop, ui);
}
const CH2* Scan(const CH2* start, FP8& result) {
  return TScan<CH2>(start, result);
}
#endif

CH2* PrintRight(CH2* start, CH2* stop, const CH2* item, SI4 count) {
  return TPrintRight<CH2>(start, stop, item, count);
}

CH2* PrintRight(CH2* start, CH2* stop, CH2 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintRight(CH2* start, CH2* stop, UI4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintRight(CH2* start, CH2* stop, SI4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintRight(CH2* start, CH2* stop, UI8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintRight(CH2* start, CH2* stop, SI8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintHex(CH2* start, CH2* stop, const void* ptr) {
  return TPrintHex<CH2>(start, stop, ptr);
}

CH2* PrintHex(CH2* start, CH2* stop, UI1 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, SI1 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, UI2 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, SI2 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, UI4 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, SI4 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, UI8 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, SI8 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, const void* ptr) {
  return TPrintBinary<CH2>(start, stop, ptr);
}

CH2* PrintBinary(CH2* start, CH2* stop, UI1 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, SI1 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, UI2 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, SI2 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, UI4 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, SI4 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, UI8 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, SI8 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintChars(CH2* start, CH2* stop, const void* begin, const void* end) {
  return TPrintSocket<CH2>(start, stop, begin, end);
}

CH2* PrintChars(CH2* start, CH2* stop, const void* begin, SIW size) {
  const CH1* end = reinterpret_cast<const CH1*>(begin) + size - 1;
  return PrintChars(start, stop, begin, end);
}

CH2* PrintLinef(CH2* start, CH2* stop, CH2 token, SI4 count) {
  return TPrintLinef<CH2>(start, stop, token, count);
}

CH2* PrintLinef(CH2* start, CH2* stop, const CH2* token, SI4 count) {
  return TPrintLinef<CH2>(start, stop, token, count);
}

CH2* PrintRepeat(CH2* start, CH2* stop, CH2 token, SI4 count) {
  return TPrintHeadingf<CH2>(start, stop, token, count);
}

CH2* PrintRepeat(CH2* start, CH2* stop, const CH2* item, SI4 count) {
  return TPrintHeadingf<CH2>(start, stop, item, count);
}

CH2* PrintHeadingf(CH2* start, CH2* stop, CH2 token, SI4 count) {
  return TPrintHeadingf<CH2>(start, stop, token, count);
}

CH2* PrintHeadingf(CH2* start, CH2* stop, const CH2* token, SI4 count) {
  return TPrintHeadingf<CH2>(start, stop, token, count);
}

const CH2* Scan(const CH2* start, SI1& result) {
  return TScanSigned<SI1, UI1, CH2>(start, result);
}

const CH2* Scan(const CH2* start, UI1& result) {
  return TScanUnsigned<UI1, CH2>(start, result);
}

const CH2* Scan(const CH2* start, SI2& result) {
  return TScanSigned<SI2, UI2, CH2>(start, result);
}

const CH2* Scan(const CH2* start, UI2& result) {
  return TScanUnsigned<UI2, CH2>(start, result);
}

const CH2* Scan(const CH2* start, SI4& result) {
  return TScanSigned<SI4, UI4, CH2>(start, result);
}

const CH2* Scan(const CH2* start, UI4& result) {
  return TScanUnsigned<UI4, CH2>(start, result);
}

const CH2* Scan(const CH2* start, SI8& result) {
  return TScanSigned<SI8, UI8, CH2>(start, result);
}

const CH2* Scan(const CH2* start, UI8& result) {
  return TScanUnsigned<UI8, CH2>(start, result);
}

/*
void COut2(UIW* begin) { return TCOut<CH2>(begin); }

void COut2Auto(UIW* begin) { return TCOutAuto<CH2>(begin); }*/

UTF2::UTF2(CH2* start, SIW buffer_size)
    : start(start), stop(start + buffer_size - 1) {
  ASSERT(start);
  ASSERT(buffer_size);
}

UTF2::UTF2(CH2* start, CH2* stop) : start(start), stop(stop) {
  ASSERT(start);
  ASSERT(start < stop);
}

UTF2::UTF2(const UTF2& other) : start(other.start), stop(other.stop) {
  ASSERT(start);
  ASSERT(stop);
}

UTF2& UTF2::Set(CH2* new_cursor) {
  start = new_cursor;
  return *this;
}

UTF2& UTF2::Print(CH1 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(CH2 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(CH4 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(const CH1* item) {
  return Set(::_::Print(start, stop, item));
}

UTF2& UTF2::Print(const CH2* item) {
  return Set(::_::Print(start, stop, item));
}

UTF2& UTF2::Print(const CH4* item) {
  return Set(::_::Print(start, stop, item));
}

UTF2& UTF2::Print(SI4 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(UI4 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(SI8 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(UI8 item) { return Set(::_::Print(start, stop, item)); }

#if USING_FP4 == YES
UTF2& UTF2::Print(FP4 item) { return Set(::_::Print(start, stop, item)); }
UTF2& UTF2::Hex(FP4 item) { return Set(TPrintHex<CH2>(start, stop, item)); }
UTF2& UTF2::Binary(FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH2>(start, stop, ui));
}
#endif
#if USING_FP8 == YES
UTF2& UTF2::Print(FP8 item) { return Set(::_::Print(start, stop, item)); }
UTF2& UTF2::Hex(FP8 item) { return Set(TPrintHex<CH2>(start, stop, item)); }
UTF2& UTF2::Binary(FP8 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH2>(start, stop, ui));
}
#endif

UTF2& UTF2::Print(Right2 item) {
  return Set(
      ::_::PrintRight(start, stop, item.token.Get(), item.token.Count()));
}

UTF2& UTF2::Print(Center2 item) {
  return Set(
      ::_::PrintCenter(start, stop, item.token.Get(), item.token.Count()));
}

UTF2& UTF2::Print(Linef2 item) {
  return Set(
      ::_::PrintLinef(start, stop, item.token.Get(), item.token.Count()));
}

UTF2& UTF2::Print(Headingf2 item) {
  return Set(::_::PrintLinef(start, stop, item.caption.String(),
                             item.caption.Count()));
}

Chars2::Chars2(const CH2* start, const CH2* stop) : start(start), stop(stop) {}

UTF2& UTF2::Print(Chars2 item) {
  return Set(::_::PrintChars(start, stop, item.start, item.stop));
}

UTF2& UTF2::Print(::_::Hex item) {
  return Set(::_::TPrintHex<CH2>(start, stop, item.Begin(), item.Size()));
}

UTF2& UTF2::Hex(UI1 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI1 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(UI2 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI2 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(UI4 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI4 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(UI8 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI8 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(const void* item) {
  return Set(TPrintHex<CH2>(start, stop, item));
}

UTF2& UTF2::Hex(const void* item, SIW size_bytes) {
  return Set(TPrintHex<CH2>(start, stop, item, size_bytes));
}

UTF2& UTF2::Binary(UI1 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(SI1 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(UI2 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(SI2 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(UI4 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(SI4 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(UI8 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(SI8 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH2>(start, stop, ptr));
}

Token2::Token2(CH1 item, SI4 count) : string_(strand_), count_(count) {
  TPrint1<CH2>(strand_, item);
}

Token2::Token2(const CH1* item, SI4 count) : string_(strand_), count_(count) {
  if (!Print(item)) *strand_ = 0;
}

Token2::Token2(CH2 item, SI4 count) : string_(strand_), count_(count) {
  TPrint1<CH2>(strand_, item);
}

Token2::Token2(const CH2* item, SI4 count) : string_(item), count_(count) {
  if (!item) *strand_ = 0;
}

#if USING_UTF32
Token2::Token2(CH4 item, SI4 count) : string_(strand_), count_(count) {
  Print(item);
}

Token2::Token2(const CH4* item, SI4 count) : string_(item), count_(count) {
  if (!Print(item)) *strand_ = 0;
}
#endif

Token2::Token2(SI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token2::Token2(UI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token2::Token2(SI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token2::Token2(UI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

#if USING_FP4 == YES
Token2::Token2(FP4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif
#if USING_FP8 == YES
Token2::Token2(FP8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif

const CH2* Token2::String() { return string_; }

CH2* Token2::Strand() { return strand_; }

const CH2* Token2::Get() {
  const CH2* ptr = string_;
  return ptr ? ptr : strand_;
}

const CH2* Token2::Set(const CH2* string) {
  if (!string) return string;
  string_ = string;
  return string;
}

SI4 Token2::Count() { return count_; }

CH2* Token2::Print(CH1 item) {
  return ::_::Print(strand_, strand_ + kTokenLongest, item);
}

CH2* Token2::Print(const CH1* item) {
  CH2* cursor = ::_::TPrint<CH2>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#if USING_UTF16 == YES
CH2* Token2::Print(CH2 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH2* Token2::Print(const CH2* item) {
  CH2* cursor = ::_::TPrint<CH2>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_UTF32 == YES
CH2* Token2::Print(CH4 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH2* Token2::Print(const CH4* item) {
  CH2* cursor = ::_::TPrint<CH2>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

CH2* Token2::Print(SI4 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH2* Token2::Print(UI4 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH2* Token2::Print(SI8 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH2* Token2::Print(UI8 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#if USING_FP4 == YES
CH2* Token2::Print(FP4 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_FP8 == YES
CH2* Token2::Print(FP8 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

Center2::Center2(const CH1* item, SI4 count) : token(item, count) {}

Center2::Center2(CH1 item, SI4 count) : token(item, count) {}

Center2::Center2(const CH2* item, SI4 count) : token(item, count) {}

#if USING_UTF32
Center2::Center2(CH4 item, SI4 count) : token(item, count) {}
Center2::Center2(const CH4* item, SI4 count) : token(item, count) {}
#endif

Center2::Center2(CH2 item, SI4 count) : token(item, count) {}

Center2::Center2(SI4 item, SI4 count) : token(item, count) {}

Center2::Center2(UI4 item, SI4 count) : token(item, count) {}

Center2::Center2(SI8 item, SI4 count) : token(item, count) {}

Center2::Center2(UI8 item, SI4 count) : token(item, count) {}

#if USING_FP4 == YES
Center2::Center2(FP4 item, SI4 count) : token_(item, count) {}
#endif
#if USING_FP8 == YES
Center2::Center2(FP8 item, SI4 count) : token_(item, count) {}
#endif

Right2::Right2(CH1 item, SI4 count) : token(item, count) {}

Right2::Right2(const CH1* item, SI4 count) : token(item, count) {}

Right2::Right2(CH2 item, SI4 count) : token(item, count) {}

Right2::Right2(const CH2* item, SI4 count) : token(item, count) {}

#if USING_UTF32
Right2::Right2(CH4 item, SI4 count) : token(item, count) {}

Right2::Right2(const CH4* item, SI4 count) : token(item, count) {}
#endif

Right2::Right2(SI4 item, SI4 count) : token(item, count) {}

Right2::Right2(UI4 item, SI4 count) : token(item, count) {}

Right2::Right2(SI8 item, SI4 count) : token(item, count) {}

Right2::Right2(UI8 item, SI4 count) : token(item, count) {}

#if USING_FP4 == YES
Right2::Right2(FP4 item, SI4 count) : token(item, count) {}
#endif
#if USING_FP8 == YES
Right2::Right2(FP8 item, SI4 count) : token(item, count) {}
#endif

Linef2::Linef2(const CH1* item, SI4 count) : token(token.Strand(), count) {
  CH2* strand = token.Strand();
  ::_::Print(strand, strand + kTokenLongest, item);
}

Linef2::Linef2(CH1 item, SI4 count) : token(token.Strand(), count) {
  CH2* strand = token.Strand();
  ::_::Print(strand, strand + kTokenLongest, item);
}

Linef2::Linef2(CH2 item, SI4 count) : token(token.Strand(), count) {
  CH2* strand = token.Strand();
  ::_::Print(strand, strand + kTokenLongest, item);
}

Linef2::Linef2(const CH2* item, SI4 count) : token(item, count) {}

Headingf2::Headingf2(const CH2* caption, const CH2* style, SI4 count,
                     const CH2* caption2, const CH2* caption3)
    : caption(caption, count),
      style(style),
      caption2(caption2),
      caption3(caption3) {}

}  // namespace _

::_::UTF2& operator<<(::_::UTF2& o, CH4 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, ::_::UTF2& p) { return o; }

::_::UTF2& operator<<(::_::UTF2& o, const CH1* item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, const CH2* item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, const CH4* item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, UI1 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, SI2 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, UI2 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, SI4 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, UI4 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, SI8 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, UI8 item) { return o.Print(item); }

#if USING_FP4 == YES
::_::UTF2& operator<<(::_::UTF2& o, FP4 item) { return o.Print(item); }
#endif
#if USING_FP8 == YES
::_::UTF2& operator<<(::_::UTF2& o, FP8 item) { return o.Print(item); }
#endif

::_::UTF2& operator<<(::_::UTF2& o, ::_::Hex item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, ::_::Center2 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, ::_::Right2 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, ::_::Linef2 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, ::_::Headingf2 item) {
  return o.Print(item);
}

::_::UTF2& operator<<(::_::UTF2& o, ::_::Chars2 item) { return o.Print(item); }
#endif  //< #if USING_UTF16

#if USING_UTF32 == YES
namespace _ {
/*
SI4 COutHeap4 (Autoject& obj, SIW function, void* arg) {
  return TCOutHeap<CH4> (obj, function, arg);
}*/

const CH4* EmptyCH4() { return TSTREmpty<CH4>(); }

const CH4* NewLineCH4() { return TSTRNL<CH4>(); }

const CH4* ErrorHeaderCH4() { return TSTRError<CH4>(); }

BOL IsWhitespace(CH4 item) { return TIsWhitespace<CH4>(item); }

CH4 PrintableChar(CH4 item) { return TCharPrintable<CH4>(item); }

const CH4* STREnd(const CH4* start) { return TSTREnd<CH4>(start); }

SI4 StrandLength(const CH4* start) { return TSTRLength<CH4, SI4>(start); }

const CH4* StrandLineEnd(const CH4* start, SI4 count) {
  return TSTRLineEnd<CH4>(start, count);
}

const CH4* StrandLineEnd(const CH4* start, const CH4* stop, SI4 count) {
  return TSTRLineEnd<CH4>(start, stop, count);
}

const CH4* StrandDecimalEnd(const CH4* start, const CH4* stop) {
  return TSTRDecimalEnd<CH4>(start, stop);
}

const CH4* StrandDecimalEnd(const CH4* start) {
  return TSTRDecimalEnd<CH4>(start);
}

const CH4* STRSkipChar(const CH4* start, CH4 skip_char) {
  return TSTRSkipChar<CH4>(start, skip_char);
}

const CH4* STRSkipSpaces(const CH4* start) {
  return TSTRSkipSpaces<CH4>(start);
}

const CH4* STRSkipSpaces(const CH4* start, const CH4* stop) {
  return TSTRSkipSpaces<CH4>(start, stop);
}

const CH4* STREquals(const CH4* text_a, const CH4* text_b) {
  return TSTREquals<CH4>(text_a, text_b);
}

const CH4* STREquals(const CH4* start, const CH4* stop, const CH4* text_b) {
  return TSTREquals<CH4>(start, stop, text_b);
}

/*
BOL TTextQualifies(const CH4* start) { return TTextQualifies<CH4>(start); }

BOL TTextQualifies(const CH4* start, const CH4* stop) {
  return TTextQualifies<CH4>(start, stop);
}*/

SI4 STRCompare(const CH4* text_a, const CH4* text_b) {
  return TSTRCompare<CH4>(text_a, text_b);
}

const CH4* STRFind(const CH4* start, const CH4* item) {
  return TSTRFind<CH4>(start, item);
}

#if USING_UTF8 == YES
CH4* Print(CH4* start, CH4* stop, const CH1* item) {
  return TPrint<CH4>(start, stop, item);
}
#endif

#if USING_UTF16 == YES
CH4* Print(CH4* start, CH4* stop, const CH2* item) {
  return TPrint<CH4>(start, stop, item);
}
#endif

CH4* Print(CH4* start, CH4* stop, const CH4* item) {
  return TPrint<CH4>(start, stop, item);
}

CH4* Print(CH4* start, SIW count, const CH4* item) {
  return TPrint<CH4>(start, count, item);
}

CH4* Print(CH4* start, CH4* stop, UI4 item) {
  return TPrintUnsigned<UI4, CH4>(start, stop, item);
}

CH4* Print(CH4* start, CH4* stop, SI4 item) {
  return TPrintSigned<SI4, UI4, CH4>(start, stop, item);
}

CH4* Print(CH4* start, CH4* stop, UI8 item) {
  return TPrintUnsigned<UI8, CH4>(start, stop, item);
}

CH4* Print(CH4* start, CH4* stop, SI8 item) {
  return TPrintSigned<SI8, UI8, CH4>(start, stop, item);
}

CH4* PrintCenter(CH4* start, CH4* stop, const CH4* begin, SI4 count) {
  return TPrintCenter<CH4>(start, stop, begin, count);
}

CH4* PrintCenter(CH4* start, CH4* stop, CH4 item, SI4 count) {
  return TPrintCenter<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintCenter(CH4* start, CH4* stop, SI4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintCenter(CH4* start, CH4* stop, UI4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintCenter(CH4* start, CH4* stop, UI8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintCenter(CH4* start, CH4* stop, SI8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

#if USING_FP4 == YES
CH4* PrintCenter(CH4* start, CH4* stop, FP4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}
CH4* PrintRight(CH4* start, CH4* stop, FP4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}
CH4* PrintHex(CH4* start, CH4* stop, FP4 item) {
  return TPrintHex<CH4>(start, stop, item);
}
CH4* PrintBinary(CH4* start, CH4* stop, FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return TPrintBinary<CH4, UI8>(start, stop, ui);
}
const CH4* Scan(const CH4* start, FP4& result) {
  return TScan<CH4>(start, result);
}
#endif
#if USING_FP8 == YES
CH4* PrintCenter(CH4* start, CH4* stop, FP8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}
CH4* PrintRight(CH4* start, CH4* stop, FP8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}
CH4* PrintHex(CH4* start, CH4* stop, FP8 item) {
  return TPrintHex<CH4>(start, stop, item);
}
CH4* PrintBinary(CH4* start, CH4* stop, FP8 item) {
  UI8 ui = *reinterpret_cast<UI8*>(&item);
  return TPrintBinary<CH4, UI8>(start, stop, ui);
}
const CH4* Scan(const CH4* start, FP8& result) {
  return TScan<CH4>(start, result);
}
#endif

CH4* PrintRight(CH4* start, CH4* stop, const CH4* begin, SI4 count) {
  return TPrintRight<CH4>(start, stop, begin, count);
}

CH4* PrintRight(CH4* start, CH4* stop, CH4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintRight(CH4* start, CH4* stop, UI4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintRight(CH4* start, CH4* stop, SI4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintRight(CH4* start, CH4* stop, UI8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintRight(CH4* start, CH4* stop, SI8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintHex(CH4* start, CH4* stop, const void* ptr) {
  return TPrintHex<CH4>(start, stop, ptr);
}

CH4* PrintHex(CH4* start, CH4* stop, UI1 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, SI1 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, UI2 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, SI2 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, UI4 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, SI4 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, UI8 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, SI8 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, const void* ptr) {
  return TPrintBinary<CH4>(start, stop, ptr);
}

CH4* PrintBinary(CH4* start, CH4* stop, UI1 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, SI1 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, UI2 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, SI2 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, UI4 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, SI4 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, UI8 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, SI8 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintChars(CH4* start, CH4* stop, const void* begin, const void* end) {
  return TPrintSocket<CH4>(start, stop, begin, end);
}

CH4* PrintChars(CH4* start, CH4* stop, const void* begin, SIW size) {
  const CH4* ptr = reinterpret_cast<const CH4*>(begin);
  return PrintChars(start, stop, begin, ptr + size - 1);
}

CH4* PrintLinef(CH4* start, CH4* stop, CH4 item, SI4 count) {
  return TPrintLinef<CH4>(start, stop, item, count);
}

CH4* PrintLinef(CH4* start, CH4* stop, const CH4* item, SI4 count) {
  return TPrintLinef<CH4>(start, stop, item, count);
}

CH4* PrintRepeat(CH4* start, CH4* stop, CH4 item, SI4 count) {
  return TPrintHeadingf<CH4>(start, stop, item, count);
}

CH4* PrintRepeat(CH4* start, CH4* stop, const CH4* item, SI4 count) {
  return TPrintHeadingf<CH4>(start, stop, item, count);
}

const CH4* Scan(const CH4* start, SI1& result) {
  return TScanSigned<SI1, UI2, CH4>(start, result);
}

const CH4* Scan(const CH4* start, UI1& result) {
  return TScanUnsigned<UI1, CH4>(start, result);
}

const CH4* Scan(const CH4* start, SI2& result) {
  return TScanSigned<SI2, UI2, CH4>(start, result);
}

const CH4* Scan(const CH4* start, UI2& result) {
  return TScanUnsigned<UI2, CH4>(start, result);
}

const CH4* Scan(const CH4* start, SI4& result) {
  return TScanSigned<SI4, UI4, CH4>(start, result);
}

const CH4* Scan(const CH4* start, UI4& result) {
  return TScanUnsigned<UI4, CH4>(start, result);
}

const CH4* Scan(const CH4* start, SI8& result) {
  return TScanSigned<SI8, UI8, CH4>(start, result);
}

const CH4* Scan(const CH4* start, UI8& result) {
  return TScanUnsigned<UI8, CH4>(start, result);
}

/*
void COut4(UIW* begin) { return TCOut<CH4>(begin); }

void COutAuto4(UIW* begin) { return TCOutAuto<CH4>(begin); }*/

UTF4::UTF4(CH4* start, SIW buffer_size)
    : start(start), stop(start + buffer_size - 1) {
  ASSERT(start);
  ASSERT(buffer_size);
}

UTF4::UTF4(CH4* start, CH4* stop) : start(start), stop(stop) {
  ASSERT(start);
  ASSERT(start < stop);
}

UTF4::UTF4(const UTF4& other) : start(other.start), stop(other.stop) {
  ASSERT(start);
  ASSERT(stop);
}

UTF4& UTF4::Set(CH4* new_cursor) {
  start = new_cursor;
  return *this;
}

UTF4& UTF4::Print(CH1 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(CH2 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(CH4 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(const CH1* item) {
  return Set(::_::Print(start, stop, item));
}

UTF4& UTF4::Print(const CH2* item) {
  return Set(::_::Print(start, stop, item));
}

UTF4& UTF4::Print(const CH4* item) {
  return Set(::_::Print(start, stop, item));
}

UTF4& UTF4::Print(SI4 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(UI4 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(SI8 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(UI8 item) { return Set(::_::Print(start, stop, item)); }

#if USING_FP4 == YES
UTF4& UTF4::Print(FP4 item) { return Set(::_::Print(start, stop, item)); }
UTF4& UTF4::Hex(FP4 item) { return Set(TPrintHex<CH4>(start, stop, item)); }
UTF4& UTF4::Binary(FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH4>(start, stop, ui));
}
#endif
#if USING_FP4 == YES
UTF4& UTF4::Print(FP8 item) { return Set(::_::Print(start, stop, item)); }
UTF4& UTF4::Hex(FP8 item) { return Set(TPrintHex<CH4>(start, stop, item)); }
UTF4& UTF4::Binary(FP8 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH4>(start, stop, ui));
}
#endif

UTF4& UTF4::Print(Right4 item) {
  return Set(
      ::_::PrintRight(start, stop, item.token.Get(), item.token.Count()));
}

UTF4& UTF4::Print(Center4 item) {
  return Set(
      ::_::PrintCenter(start, stop, item.token.Get(), item.token.Count()));
}

UTF4& UTF4::Print(Linef4 item) {
  return Set(
      ::_::PrintLinef(start, stop, item.token.Get(), item.token.Count()));
}

UTF4& UTF4::Print(Headingf4 item) {
  return Set(::_::PrintLinef(start, stop, item.caption.String(),
                             item.caption.Count()));
}

UTF4& UTF4::Print(::_::Hex item) {
  return Set(::_::TPrintHex<CH4>(start, stop, item.Begin(), item.Size()));
}

UTF4& UTF4::Hex(UI1 item) { return Set(TPrintHex<CH4>(start, stop, item)); }

UTF4& UTF4::Hex(SI1 item) { return Set(TPrintHex<CH4>(start, stop, item)); }

UTF4& UTF4::Hex(UI2 item) { return Set(TPrintHex<CH4>(start, stop, item)); }

UTF4& UTF4::Hex(SI2 item) {
  return Set(TPrintHex<CH4>(start, stop, (UI2)item));
}

UTF4& UTF4::Hex(UI4 item) { return Set(TPrintHex<CH4>(start, stop, item)); }

UTF4& UTF4::Hex(SI4 item) {
  return Set(TPrintHex<CH4>(start, stop, (UI4)item));
}

UTF4& UTF4::Hex(UI8 item) { return Set(TPrintHex<CH4>(start, stop, item)); }

UTF4& UTF4::Hex(SI8 item) {
  return Set(TPrintHex<CH4>(start, stop, (UI8)item));
}

UTF4& UTF4::Hex(const void* ptr) {
  return Set(TPrintHex<CH4>(start, stop, ptr));
}

UTF4& UTF4::Binary(UI1 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(SI1 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(UI2 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(SI2 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(UI4 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(SI4 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(UI8 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(SI8 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH4>(start, stop, ptr));
}

Token4::Token4(CH4 item, SI4 count) : string_(strand_), count_(count) {
  TPrint1<CH4>(strand_, item);
}

Token4::Token4(const CH4* item, SI4 count) : string_(item), count_(count) {
  if (!item) *strand_ = 0;
}

Token4::Token4(SI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token4::Token4(UI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token4::Token4(SI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token4::Token4(UI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

#if USING_FP4 == YES
Token4::Token4(FP4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif
#if USING_FP8 == YES
Token4::Token4(FP8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif

const CH4* Token4::String() { return string_; }

CH4* Token4::Strand() { return strand_; }

const CH4* Token4::SetString(const CH4* ptr) {
  string_ = ptr;
  return ptr;
}

const CH4* Token4::Get() {
  const CH4* ptr = string_;
  return ptr ? ptr : strand_;
}

SI4 Token4::Count() { return count_; }

CH4* Token4::Print(CH1 item) {
  return ::_::TPrint<CH4>(strand_, strand_ + kTokenLongest, item);
}

CH4* Token4::Print(const CH1* item) {
  CH4* cursor = ::_::TPrint<CH4>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#if USING_UTF16 == YES
CH4* Token4::Print(CH2 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH4* Token4::Print(const CH2* item) {
  CH4* cursor = ::_::TPrint<CH4>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_UTF32 == YES
CH4* Token4::Print(CH4 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH4* Token4::Print(const CH4* item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

CH4* Token4::Print(SI4 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH4* Token4::Print(UI4 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH4* Token4::Print(SI8 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH4* Token4::Print(UI8 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#if USING_FP4 == YES
CH4* Token4::Print(FP4 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_FP8 == YES
CH4* Token4::Print(FP8 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

Center4::Center4(const CH4* item, SI4 count) : token(item, count) {}

Center4::Center4(SI4 item, SI4 count) : token(item, count) {}

Center4::Center4(UI4 item, SI4 count) : token(item, count) {}

Center4::Center4(SI8 item, SI4 count) : token(item, count) {}

Center4::Center4(UI8 item, SI4 count) : token(item, count) {}

#if USING_FP4 == YES
Center4::Center4(FP4 item, SI4 count) : token(item, count) {}
#endif
#if USING_FP8 == YES
Center4::Center4(FP8 item, SI4 count) : token(item, count) {}
#endif

Right4::Right4(const CH4* item, SI4 count) : token(item, count) {}

Right4::Right4(SI4 item, SI4 count) : token(item, count) {}

Right4::Right4(UI4 item, SI4 count) : token(item, count) {}

Right4::Right4(SI8 item, SI4 count) : token(item, count) {}

Right4::Right4(UI8 item, SI4 count) : token(item, count) {}

#if SEAM >= SCRIPT2_SEAM_FTOS
Right4::Right4(FP4 item, SI4 count) : token(item, count) {}

Right4::Right4(FP8 item, SI4 count) : token(item, count) {}
#endif

Linef4::Linef4(CH4 item, SI4 count) : token(token.Strand(), count) {
  CH4* strand = token.Strand();
  ::_::Print(strand, strand + kTokenLongest, item);
}

Linef4::Linef4(const CH4* item, SI4 count) : token(item, count) {}

Headingf4::Headingf4(const CH4* caption, const CH4* style, SI4 count,
                     const CH4* caption2, const CH4* caption3)
    : caption(caption, count),
      style(style),
      caption2(caption2),
      caption3(caption3) {}

Chars4::Chars4(const CH4* start, const CH4* stop) : start(start), stop(stop) {}

}  // namespace _

::_::UTF4& operator<<(::_::UTF4& o, CH4 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, ::_::UTF4& p) { return o; }

::_::UTF4& operator<<(::_::UTF4& o, const CH1* item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, const CH2* item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, const CH4* item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, UI1 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, SI2 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, UI2 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, SI4 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, UI4 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, SI8 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, UI8 item) { return o.Print(item); }

#if USING_FP4 == YES
::_::UTF4& operator<<(::_::UTF4& o, FP4 item) { return o.Print(item); }
#endif
#if USING_FP8 == YES
::_::UTF4& operator<<(::_::UTF4& o, FP8 item) { return o.Print(item); }
#endif

::_::UTF4& operator<<(::_::UTF4& o, ::_::Hex item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, ::_::Center4 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, ::_::Right4 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, ::_::Linef4 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, ::_::Headingf4 item) {
  return o.Print(item);
}

::_::UTF4& operator<<(::_::UTF4& o, ::_::Chars4 item) {
  return ::_::TPrintChars<::_::UTF4>(o, item.start, item.stop);
}

#endif
#endif
