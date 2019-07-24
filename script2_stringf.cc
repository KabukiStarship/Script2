/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_lock.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>
//
#include "t_stringf.h"

namespace _ {

const CH1* STRPrintCharsHeader() {
  return "\n|0       8       16      24      32      40      48      56      |"
         " Begin address:";
}

const CH1* STRPrintCharsBorder() {
  return "\n|+-------+-------+-------+-------+-------+-------+-------+-------|"
         " ";
}

const CH1* STRPrintHexHeader() {
  return "\n|0               8               16              24              "
         "|  Begin address:";
}

const CH1* STRPrintHexBorder() {
  return "\n|+---------------+---------------+---------------+---------------|"
         " ";
}

CH1* Print(CH1* start, CH1* stop, CH1 c) {
  if (!start || start >= stop) return nullptr;
  *start++ = c;
  *start = 0;
  return start;
}

}  // namespace _

#if SEAM >= SEAM_SCRIPT2_UTF
#if SEAM == SEAM_SCRIPT2_UTF
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

CH1* Print(CH1* start, CH1* stop, CH4 c) {
  // | Byte 1   | Byte 2   | Byte 3   | Byte 4   | UTF-32 Result         |
  // |:--------:|:--------:|:--------:|:--------:|:---------------------:|
  // | 0aaaaaaa |          |          |          | 00000000000000aaaaaaa |
  // | 110aaaaa | 10bbbbbb |          |          | 0000000000aaaaabbbbbb |
  // | 1110aaaa | 10bbbbbb | 10cccccc |          | 00000aaaabbbbbbcccccc |
  // | 11110aaa | 10bbbbbb | 10cccccc | 10dddddd | aaabbbbbbccccccdddddd |

  if (!start || start >= stop) return nullptr;

  if (!(c >> 7)) {  // 1 ASCII CH1.
    if (start + 1 > stop) return nullptr;
    *start++ = (CH1)c;
  }
  CH2 lsb_mask = 0x3f, msb_mask = 0x80;
  if ((c >> 11) == 0) {  // 2 bytes.
    if (start + 2 >= stop) return nullptr;
    CH1 byte = (CH1)(0xC0 | (c >> 6));
    // D_PRINTF ("\nPrinting 2:%x  string_type:%x", c, byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | (c & lsb_mask));
    // D_PRINTF_HEX (byte);
    *start++ = byte;
  } else if ((c >> 16) == 0) {  // 3 bytes.
    if (start + 3 >= stop) return nullptr;
    CH1 byte = (CH1)(0xE0 | (c >> 12));
    // D_PRINTF ("\nPrinting 3:%x  string_type:%x", c, byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | ((c >> 6) & lsb_mask));
    // D_PRINTF_HEX (byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | (c & lsb_mask));
    // D_PRINTF_HEX (byte);
    *start++ = byte;
  } else if ((c >> 21) == 0) {  // 4 bytes.
    if (start + 4 >= stop) return nullptr;
    CH1 byte = (CH1)(0xF0 | (c >> 18));
    // D_PRINTF ("\nPrinting 4:%x  string_type:%x", c, byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | ((c >> 12) & lsb_mask));
    // D_PRINTF_HEX (byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | ((c >> 6) & lsb_mask));
    // D_PRINTF_HEX (byte);
    *start++ = byte;
    byte = (CH1)(msb_mask | (c & lsb_mask));
    // D_PRINTF_HEX (byte);
    *start++ = byte;
  } else {
    // D_PRINTFF ("\nUTF8 print Error: CH4 is out of range:%x:%u", c, (UI4)c);
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
    // D_PRINTF ("  Scanning 2:");
    // D_PRINTF_HEX ((CH1)c);
    r = (c & 31) << 6;
    c = ToCH4(*string++);
    // D_PRINTF_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= c & (CH4)63;
    // D_PRINTF ("  Result:");
    // D_PRINTF_HEX (r);
  } else if ((c >> 4) == 0xE) {
    // D_PRINTF ("  Scanning 3:");
    // D_PRINTF_HEX ((CH1)c);
    r = ((CH4)(c & 15)) << 12;
    c = ToCH4(*string++);
    // D_PRINTF_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= (c & 63) << 6;
    c = ToCH4(*string++);
    // D_PRINTF_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= c & lsb_mask;
    // D_PRINTF ("  Result:");
    // D_PRINTF_HEX (r);
  } else if ((c >> 3) == 0x1E) {
    // D_PRINTF ("  Scanning 4:");
    // D_PRINTF_HEX ((CH1)c);
    r = ((CH4)(c & 7)) << 18;
    c = ToCH4(*string++);
    // D_PRINTF_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= (c & lsb_mask) << 12;
    c = ToCH4(*string++);
    // D_PRINTF_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= (c & lsb_mask) << 6;
    c = ToCH4(*string++);
    // D_PRINTF_HEX ((CH1)c);
    if (!(c & msb)) return nullptr;
    r |= c & lsb_mask;
    // D_PRINTF ("  Result:");
    // D_PRINTF_HEX (r);
  } else {
    // D_PRINTF ("\nUTF8 scan error:");
    // D_PRINTF_HEX ((CH1)c);
    // D_PRINTF ((SI4)c);
    return nullptr;
  }
  result = r;
  return string;
}

#if USING_UTF16 == YES_0

CH1* Print(CH1* start, CH1* stop, CH2 c) {
  // | Byte 1   | Byte 2   | Byte 3   |  UTF-32 Result   |
  // |:--------:|:--------:|:--------:|:----------------:|
  // | 0aaaaaaa |          |          | 000000000aaaaaaa |
  // | 110aaaaa | 10bbbbbb |          | 00000aaaaabbbbbb |
  // | 1110aaaa | 10bbbbbb | 10cccccc | aaaabbbbbbcccccc |
#if USING_UTF32 == YES_0
  return Print(start, stop, (CH4)c);
#else
  enum { k2ByteMSbMask = 0xC0, k3ByteMSbMask = 0xE0, k4ByteMSbMask = 0xF0 };
  if (!start) return nullptr;
  if (!(c >> 7)) {  // 1 byte.
    if (start + 1 > stop) return nullptr;
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
  if (!start || start + 1 > stop) return nullptr;
  *start++ = c;
  *start = 0;
  return start;
}

CH2* Print(CH2* start, CH2* stop, CH1 c) { return Print(start, stop, (CH2)c); }

CH2* Print(CH2* start, CH2* stop, CH4 c) {
  // | Bytes {4N, 4N+ 1} | Bytes {4N + 2, 4N+ 3} |    UTF-32 Result     |
  // |:-----------------:|:---------------------:|:--------------------:|
  // | 000000aaaaaaaaaa  |                       | 0000000000aaaaaaaaaa |
  // | 110110yyyyyyyyyy  |   110111xxxxxxxxxx    | yyyyyyyyyyxxxxxxxxxx |
  // |      0xD800       |         0xDC00        |                      |
  if (!start || start + 1 >= stop) return nullptr;
  CH4 lsb_mask = 0x3f, lsb = c & lsb_mask, msb = c >> 10;
  if (!msb) {
    if (start + 1 > stop) return nullptr;
    *start++ = (CH2)c;
    // D_PRINTF ("\nPrinting 1:");
    // D_PRINTF_HEX ((CH2)c);
    *start = 0;
    return start;
  } else {
    CH4 msb_mask = 0xDC00;
    if (msb >> 10) return nullptr;  // Non-Unicode value.
    if (start + 2 >= stop) return nullptr;
    CH2 nibble = (CH2)(lsb & msb_mask);
    // D_PRINTF ("\nPrinting 2:");
    // D_PRINTF_HEX ((CH2)nibble);
    *start++ = nibble;
    nibble = (CH2)(msb & msb_mask);
    // D_PRINTF_HEX ((CH2)nibble);
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
    // D_PRINTF (" Scanning 1:");
    // D_PRINTF_HEX (c);
    result = (CH4)c;
  } else if ((c >> 10) == 30) {
    // D_PRINTF (" Scanning 1:");
    // D_PRINTF_HEX (c);
    CH4 r = ((CH4)c) & lsb_mask;
    c = *string++;
    if (c >> 10 != 55) return nullptr;
    r |= ((CH4)(c & lsb_mask)) << 10;
  } else {
    // D_PRINTF (" Scan error:");
    // D_PRINTF_HEX (c);
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
#if USING_UTF32 == YES_0

CH4* Print(CH4* start, CH4* stop, CH4 c) {
  if (!start || start + 1 > stop) return nullptr;
  *start++ = c;
  *start = 0;
  return start;
}

CH4* Print(CH4* start, CH4* stop, CH2 c) { return Print(start, stop, CH4(c)); }

CH4* Print(CH4* start, CH4* stop, CH1 c) { return Print(start, stop, CH4(c)); }
#endif

#if USING_UTF16 == YES_0
CH2* Print(CH2* start, CH2* stop, FP4 value) {
  return TBinary<FP4, SI4, UI4>::template Print<CH2>(start, stop, value);
}

CH2* Print(CH2* start, CH2* stop, FP8 value) {
  return TBinary<FP8, SI8, UI8>::template Print<CH2>(start, stop, value);
}
#endif

#if USING_UTF32 == YES_0
CH4* Print(CH4* start, CH4* stop, FP4 value) {
  return TBinary<FP4, SI4, UI4>::template Print<CH4>(start, stop, value);
}

CH4* Print(CH4* start, CH4* stop, FP8 value) {
  return TBinary<FP8, SI8, UI8>::template Print<CH4>(start, stop, value);
}
#endif
}  // namespace _
#endif

namespace _ {

Valuef::Valuef() : count(0), value() {}

Valuef::Valuef(void* item, SIW count) : count(count), value(item) {}
Valuef::Valuef(const void* item, SIW count) : count(count), value(item) {}
#if USING_UTF8 == YES_0
Valuef::Valuef(CH1 item, SIW count) : count(count), value(item) {}
Valuef::Valuef(const CH1* item, SIW count) : count(count), value(item) {}
#endif
#if USING_UTF16 == YES_0
Valuef::Valuef(CH2 item, SIW count) : count(count), value(item) {}
Valuef::Valuef(const CH2* item, SIW count) : count(count), value(item) {}
#endif
#if USING_UTF32 == YES_0
Valuef::Valuef(CH4 item, SIW count) : count(count), value(item) {}
Valuef::Valuef(const CH4* item, SIW count) : count(count), value(item) {}
#endif
Valuef::Valuef(SI1 item, SIW count) : count(count), value(item) {}
Valuef::Valuef(UI1 item, SIW count) : count(count), value(item) {}
Valuef::Valuef(SI2 item, SIW count) : count(count), value(item) {}
Valuef::Valuef(UI2 item, SIW count) : count(count), value(item) {}
Valuef::Valuef(SI4 item, SIW count) : count(count), value(item) {}
Valuef::Valuef(UI4 item, SIW count) : count(count), value(item) {}
Valuef::Valuef(SI8 item, SIW count) : count(count), value(item) {}
Valuef::Valuef(UI8 item, SIW count) : count(count), value(item) {}
#if USING_FP4 == YES_0
Valuef::Valuef(FP4 item, SIW count) : count(count), value(item) {}
#endif
#if USING_FP8 == YES_0
Valuef::Valuef(FP8 item, SIW count) : count(count), value(item) {}
#endif

SIW Valuef::Type() { return value.Type(); }

SIW Valuef::Count() { return count; }

void* Valuef::Value() { return value.Value(); }

void* Valuef::Ptr() { return value.Ptr(); }

CH1* Valuef::ST1() { return value.ST1(); }
CH2* Valuef::ST2() { return value.ST2(); }
CH4* Valuef::ST3() { return value.ST3(); }

UIW Valuef::Word() { return value.Word(); }

Hexf::Hexf(const void* begin, SIW size) : element(begin, size) {}
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
Hexf::Hexf(const void* item) : element(UIW(item), -SIW(sizeof(const void*))) {}
Hexf::Hexf(SI1 item) : element(item, -SIW(sizeof(SI1))) {}
Hexf::Hexf(UI1 item) : element(item, -SIW(sizeof(UI1))) {}
Hexf::Hexf(SI2 item) : element(item, -SIW(sizeof(SI2))) {}
Hexf::Hexf(UI2 item) : element(item, -SIW(sizeof(UI2))) {}
Hexf::Hexf(SI4 item) : element(item, -SIW(sizeof(SI4))) {}
Hexf::Hexf(UI4 item) : element(item, -SIW(sizeof(UI4))) {}
Hexf::Hexf(SI8 item) : element(item, -SIW(sizeof(SI8))) {}
Hexf::Hexf(UI8 item) : element(item, -SIW(sizeof(UI8))) {}
#if USING_FP4 == YES_0
Hexf::Hexf(FP4 item) : element(item, -SIW(sizeof(FP4))) {}
#endif
#if USING_FP8 == YES_0
Hexf::Hexf(FP8 item) : element(item, -SIW(sizeof(FP8))) {}
#endif

Binaryf::Binaryf(const void* begin, SIW size) : element(begin, size) {}
Binaryf::Binaryf(const void* item)
    : element(UIW(item), -SIW(sizeof(const void*))) {}
Binaryf::Binaryf(SI1 item) : element(item, -SIW(sizeof(SI1))) {}
Binaryf::Binaryf(UI1 item) : element(item, -SIW(sizeof(UI1))) {}
Binaryf::Binaryf(SI2 item) : element(item, -SIW(sizeof(SI2))) {}
Binaryf::Binaryf(UI2 item) : element(item, -SIW(sizeof(UI2))) {}
Binaryf::Binaryf(SI4 item) : element(item, -SIW(sizeof(SI4))) {}
Binaryf::Binaryf(UI4 item) : element(item, -SIW(sizeof(UI4))) {}
Binaryf::Binaryf(SI8 item) : element(item, -SIW(sizeof(SI8))) {}
Binaryf::Binaryf(UI8 item) : element(item, -SIW(sizeof(UI8))) {}
#if USING_FP4 == YES_0
Binaryf::Binaryf(FP4 item) : element(item, -SIW(sizeof(FP4))) {}
#endif
#if USING_FP8 == YES_0
Binaryf::Binaryf(FP8 item) : element(item, -SIW(sizeof(FP8))) {}
#endif
#else
Hexf::Hexf(const void* item) : valuef(item, sizeof(const void*)) {}
Hexf::Hexf(SI1 item) : valuef(item, sizeof(SI1)) {}
Hexf::Hexf(UI1 item) : valuef(item, sizeof(UI1)) {}
Hexf::Hexf(SI2 item) : valuef(item, sizeof(SI2)) {}
Hexf::Hexf(UI2 item) : valuef(item, sizeof(UI2)) {}
Hexf::Hexf(SI4 item) : valuef(item, sizeof(SI4)) {}
Hexf::Hexf(UI4 item) : valuef(item, sizeof(UI4)) {}
Hexf::Hexf(SI8 item) : valuef(item, sizeof(SI8)) {}
Hexf::Hexf(UI8 item) : valuef(item, sizeof(UI8)) {}
#if USING_FP8 == YES_0
Hexf::Hexf(FP4 item) : valuef(item, sizeof(FP4)) {}
#endif
#if USING_FP8 == YES_0
Hexf::Hexf(FP8 item) : valuef(item, sizeof(FP8)) {}
#endif

Binaryf::Binaryf(const void* begin, SIW size) : valuef(begin, size) {}
Binaryf::Binaryf(const void* begin) : valuef(begin, sizeof(const void*)) {}
Binaryf::Binaryf(SI1 item) : valuef(item, sizeof(SI1)) {}
Binaryf::Binaryf(UI1 item) : valuef(item, sizeof(UI1)) {}
Binaryf::Binaryf(SI2 item) : valuef(item, sizeof(SI2)) {}
Binaryf::Binaryf(UI2 item) : valuef(item, sizeof(UI2)) {}
Binaryf::Binaryf(SI4 item) : valuef(item, sizeof(SI4)) {}
Binaryf::Binaryf(UI4 item) : valuef(item, sizeof(UI4)) {}
Binaryf::Binaryf(SI8 item) : valuef(item, sizeof(SI8)) {}
Binaryf::Binaryf(UI8 item) : valuef(item, sizeof(UI8)) {}
#if USING_FP8 == YES_0
Binaryf::Binaryf(FP4 item) : valuef(item, sizeof(FP4)) {}
#endif
#if USING_FP8 == YES_0
Binaryf::Binaryf(FP8 item) : valuef(item, sizeof(FP8)) {}
#endif
#endif

Stringf::Stringf() {}
Stringf::Stringf(const CH1* item) : string_(item) { Print(item); }
#if USING_UTF16 == YES_0
Stringf::Stringf(const CH2* item) : string_(item) { Print(item); }
#endif
#if USING_UTF32 == YES_0
Stringf::Stringf(const CH4* item) : string_(item) { Print(item); }
#endif
Stringf::Stringf(CH1 item) : string_(buffer_) { Print(item); }
Stringf::Stringf(CH2 item) : string_(buffer_) { Print(item); }
Stringf::Stringf(CH4 item) : string_(buffer_) { Print(item); }
Stringf::Stringf(SI4 item) : string_(buffer_) { Print(item); }
Stringf::Stringf(UI4 item) : string_(buffer_) { Print(item); }
Stringf::Stringf(SI8 item) : string_(buffer_) { Print(item); }
Stringf::Stringf(UI8 item) : string_(buffer_) { Print(item); }

#if USING_FP4 == YES_0
Stringf::Stringf(FP4 item) : string_(buffer_) { Print(item); }
#endif
#if USING_FP8 == YES_0
Stringf::Stringf(FP8 item) : string_(buffer_) { Print(item); }
#endif
Stringf::Stringf(const CH1* item, SIW count) : string_(item), count_(count) {
  Print(item);
}
#if USING_UTF16 == YES_0
Stringf::Stringf(const CH2* item, SIW count) : string_(item), count_(count) {
  Print(item);
}
#endif
#if USING_UTF32 == YES_0
Stringf::Stringf(const CH4* item, SIW count) : string_(item), count_(count) {
  Print(item);
}
#endif
Stringf::Stringf(CH1 item, SIW count) : string_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(CH2 item, SIW count) : string_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(CH4 item, SIW count) : string_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(SI4 item, SIW count) : string_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(UI4 item, SIW count) : string_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(SI8 item, SIW count) : string_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(UI8 item, SIW count) : string_(buffer_), count_(count) {
  Print(item);
}
#if USING_FP4 == YES_0
Stringf::Stringf(FP4 item, SIW count) : string_(buffer_), count_(count) {
  Print(item);
}
#endif
#if USING_FP8 == YES_0
Stringf::Stringf(FP8 item, SIW count) : string_(buffer_), count_(count) {
  Print(item);
}
#endif
UIW Stringf::Word() { return buffer_[0]; }
void* Stringf::Value() { return buffer_; }
void* Stringf::Ptr() { return reinterpret_cast<void*>(buffer_[0]); }
const CH1* Stringf::ST1() { return reinterpret_cast<const CH1*>(string_); }
const CH2* Stringf::ST2() { return reinterpret_cast<const CH2*>(string_); }
const CH4* Stringf::ST3() { return reinterpret_cast<const CH4*>(string_); }

SIW Stringf::Type() const { return type_; }

SIW Stringf::Count() const { return count_; }

void Stringf::Print(const CH1* item) {
  type_ = kST1;
  string_ = item;
}
#if USING_UTF16 == YES_0
void Stringf::Print(const CH2* item) {
  type_ = kST2;
  string_ = item;
}
#endif
#if USING_UTF32 == YES_0
void Stringf::Print(const CH4* item) {
  type_ = kST3;
  string_ = item;
}
#endif

void Stringf::Print(CH1 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
  _::Print(buffer, buffer + kLengthMax, item);
  type_ = kST1;
  string_ = buffer_;
}

#if USING_UTF16 == YES_0
void Stringf::Print(CH2 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
  _::Print(buffer, buffer + kLengthMax, item);
  type_ = kST1;
  string_ = buffer_;
}
#endif
#if USING_UTF32 == YES_0
void Stringf::Print(CH4 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
  _::Print(buffer, buffer + kLengthMax, item);
  type_ = kST1;
  string_ = buffer;
}
#endif
void Stringf::Print(SI4 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
#if SEAM >= SEAM_SCRIPT2_ITOS
  _::TPrint<CH1>(buffer, buffer + kLengthMax, item);
#endif
  type_ = kST1;
  string_ = buffer;
}

void Stringf::Print(UI4 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
#if SEAM >= SEAM_SCRIPT2_ITOS
  _::TPrint<CH1>(buffer, buffer + kLengthMax, item);
#endif
  type_ = kST1;
  string_ = buffer;
}

void Stringf::Print(SI8 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
#if SEAM >= SEAM_SCRIPT2_ITOS
  _::TPrint<CH1>(buffer, buffer + kLengthMax, item);
#endif
  type_ = kST1;
  string_ = buffer;
}

void Stringf::Print(UI8 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
#if SEAM >= SEAM_SCRIPT2_ITOS
  _::TPrint<CH1>(buffer, buffer + kLengthMax, item);
#endif
  type_ = kST1;
  string_ = buffer;
}

#if USING_FP4 == YES_0
void Stringf::Print(FP4 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
  _::TPrint<CH1>(buffer, buffer + kLengthMax, item);
  type_ = kST1;
  string_ = buffer;
}
#endif
#if USING_FP8 == YES_0
void Stringf::Print(FP8 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
  _::TPrint<CH1>(buffer, buffer + kLengthMax, item);
  type_ = kST1;
  string_ = buffer;
}
#endif

void Stringf::Hex(CH1 item, SIW count) {
  *buffer_ = UIW(item);
  type_ = kCH1;
  string_ = buffer_;
}
#if USING_UTF16 == YES_0
void Stringf::Hex(CH2 item, SIW count) {
  *buffer_ = UIW(item);
  type_ = kCH2;
  string_ = buffer_;
}
#endif
#if USING_UTF32 == YES_0
void Stringf::Hex(CH4 item, SIW count) {
  *buffer_ = UIW(item);
  type_ = kCH4;
  string_ = buffer_;
}
#endif
void Stringf::Hex(SI1 item, SIW count) {
  *buffer_ = UIW(item);
  type_ = kSI1;
  string_ = buffer_;
}
void Stringf::Hex(UI1 item, SIW count) {
  *buffer_ = UIW(item);
  type_ = kUI1;
  string_ = buffer_;
}

void Stringf::Hex(SI2 item, SIW count) {
  *buffer_ = UIW(item);
  type_ = kSI2;
  string_ = buffer_;
}

void Stringf::Hex(UI2 item, SIW count) {
  *buffer_ = UIW(item);
  type_ = kUI2;
  string_ = buffer_;
}

void Stringf::Hex(SI4 item, SIW count) {
  *buffer_ = UIW(item);
  type_ = kSI4;
  string_ = buffer_;
}

void Stringf::Hex(UI4 item, SIW count) {
  *buffer_ = UIW(item);
  type_ = kUI4;
  string_ = buffer_;
}

void Stringf::Hex(SI8 item, SIW count) {
  *buffer_ = UIW(item);
  type_ = kSI8;
  string_ = buffer_;
}

void Stringf::Hex(UI8 item, SIW count) {
  *buffer_ = UIW(item);
  type_ = kUI8;
  string_ = buffer_;
}

#if USING_FP4 == YES_0
void Stringf::Hex(FP4 item, SIW count) {
  UI4 value = *reinterpret_cast<UI4*>(&item);
  *buffer_ = UIW(value);
  type_ = kFP4;
  string_ = buffer_;
}
#endif

#if USING_FP8 == YES_0
void Stringf::Hex(FP8 item, SIW count) {
  UI8 value = *reinterpret_cast<UI8*>(&item);
  *buffer_ = UIW(value);
  type_ = kFP8;
  string_ = buffer_;
}
#endif

Centerf::Centerf() {}

#if USING_UTF8 == YES_0
Centerf::Centerf(CH1 item, SIW count) : element(item, count) {}
Centerf::Centerf(const CH1* item, SIW count) : element(item, count) {}
#endif
#if USING_UTF16 == YES_0
Centerf::Centerf(CH2 item, SIW count) : element(item, count) {}
Centerf::Centerf(const CH2* item, SIW count) : element(item, count) {}
#endif
#if USING_UTF32 == YES_0
Centerf::Centerf(CH4 item, SIW count) : element(item, count) {}
Centerf::Centerf(const CH4* item, SIW count) : element(item, count) {}
#endif
Centerf::Centerf(SI4 item, SIW count) : element(item, count) {}
Centerf::Centerf(UI4 item, SIW count) : element(item, count) {}
Centerf::Centerf(SI8 item, SIW count) : element(item, count) {}
#if USING_FP4 == YES_0
Centerf::Centerf(FP4 item, SIW count) : element(item, count) {}
#endif
#if USING_FP8 == YES_0
Centerf::Centerf(FP8 item, SIW count) : element(item, count) {}
#endif
Centerf::Centerf(UI8 item, SIW count) : element(item, count) {}

Centerf& Centerf::Hex(CH1 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_UTF16 == YES_0
Centerf& Centerf::Hex(CH2 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_UTF32 == YES_0
Centerf& Centerf::Hex(CH4 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#endif
Centerf& Centerf::Hex(SI1 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(UI1 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(SI2 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(UI2 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(SI4 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(UI4 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(SI8 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(UI8 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_FP4 == YES_0
Centerf& Centerf::Hex(FP4 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_FP8 == YES_0
Centerf& Centerf::Hex(FP8 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#endif

Rightf::Rightf() {}
Rightf::Rightf(CH1 item, SIW count) : element(item, count) {}
Rightf::Rightf(const CH1* item, SIW count) : element(item, count) {}
#if USING_UTF16 == YES_0
Rightf::Rightf(CH2 item, SIW count) : element(item, count) {}
Rightf::Rightf(const CH2* item, SIW count) : element(item, count) {}
#endif
#if USING_UTF32 == YES_0
Rightf::Rightf(CH4 item, SIW count) : element(item, count) {}
Rightf::Rightf(const CH4* item, SIW count) : element(item, count) {}
#endif
Rightf::Rightf(SI4 item, SIW count) : element(item, count) {}
Rightf::Rightf(UI4 item, SIW count) : element(item, count) {}
Rightf::Rightf(SI8 item, SIW count) : element(item, count) {}
Rightf::Rightf(UI8 item, SIW count) : element(item, count) {}
#if USING_FP4 == YES_0
Rightf::Rightf(FP4 item, SIW count) : element(item, count) {}
#endif
#if USING_FP8 == YES_0
Rightf::Rightf(FP8 item, SIW count) : element(item, count) {}
#endif

Rightf& Rightf::Hex(CH1 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_UTF16 == YES_0
Rightf& Rightf::Hex(CH2 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_UTF32 == YES_0
Rightf& Rightf::Hex(CH4 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#endif
Rightf& Rightf::Hex(SI1 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(UI1 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(SI2 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(UI2 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(SI4 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(UI4 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(SI8 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(UI8 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_FP4 == YES_0
Rightf& Rightf::Hex(FP4 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_FP8 == YES_0
Rightf& Rightf::Hex(FP8 item, SIW count) {
  element.Hex(item, count);
  return *this;
}
#endif

Linef::Linef(CH1 item, SIW count) : element(item, count) {}
Linef::Linef(const CH1* item, SIW count) : element(item, count) {}

Headingf::Headingf(const CH1* caption1, const CH1* style, SIW count,
                   const CH1* caption2, const CH1* caption3)
    : element(caption1, count),
      style(style),
      caption2(caption2),
      caption3(caption3) {}

Charsf::Charsf(const void* start, const void* stop)
    : element(reinterpret_cast<const CH1*>(start),
              reinterpret_cast<const CH1*>(stop) -
                  reinterpret_cast<const CH1*>(start)) {}
Charsf::Charsf(const void* start, SIW count)
    : element(reinterpret_cast<const CH1*>(start), count) {}

#if USING_UTF16 == YES_0
Charsf::Charsf(const CH2* start, const CH2* stop)
    : element(start, stop - start) {}
Charsf::Charsf(const CH2* start, SIW count) : element(start, count) {}
#endif
#if USING_UTF32 == YES_0
Charsf::Charsf(const CH4* start, const CH4* stop)
    : element(start, stop - start) {}
Charsf::Charsf(const CH4* start, SIW count) : element(start, count) {}
#endif

Indentf::Indentf(SIW indent_count) : indent_count(indent_count) {}

}  // namespace _

#if SEAM >= SEAM_SCRIPT2_FTOS
#if SEAM == SEAM_SCRIPT2_FTOS
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

#include <cstdio>  // For sprintf_s

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

const CH1* Scan(const CH1* start, FP4& value) {
  SI4 count = sscanf_s(start, "%f", &value);
  return TSTRFloatStop<CH1>(start);
}

const CH1* Scan(const CH1* start, FP8& value) {
  SI4 count = sscanf_s(start, "%lf", &value);
  return TSTRFloatStop<CH1>(start);
}
}  // namespace _
#endif
