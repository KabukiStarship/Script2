/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /stringf.inl
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>
//
#include "stringf.hpp"

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

}  // namespace _

#if SEAM >= SCRIPT2_UNIPRINTER
#if SEAM == SCRIPT2_UNIPRINTER
#include "_debug.inl"
#else
#include "_release.inl"
#endif

namespace _ {

CH1* SPrint(CH1* string, CH1* stop, CH4 item) {
  // | Byte 1   | Byte 2   | Byte 3   | Byte 4   | UTF-32 Result         |
  // |:--------:|:--------:|:--------:|:--------:|:---------------------:|
  // | 0aaaaaaa |          |          |          | 00000000000000aaaaaaa |
  // | 110aaaaa | 10bbbbbb |          |          | 0000000000aaaaabbbbbb |
  // | 1110aaaa | 10bbbbbb | 10cccccc |          | 00000aaaabbbbbbcccccc |
  // | 11110aaa | 10bbbbbb | 10cccccc | 10dddddd | aaabbbbbbccccccdddddd |

  if (!string) return nullptr;

  D_COUT("\n\n" << UI4(item) << ".) Printed:0x");
  if (!(item >> 7)) {  // 1 ASCII CH1.
    if (string + 1 > stop) return nullptr;
    *string++ = CH1(item);
    D_COUT(Hexf(*(string - 1)) << "   ");
  } else {
    CH2 lsb_mask = 0x3f, msb_mask = 0x80;
    if ((item >> 11) == 0) {
      if (string + 2 >= stop) return nullptr;
      *string++ = CH1(0xC0 | (item >> 6));
      *string++ = CH1(msb_mask | (item & lsb_mask));
      D_COUT(Hexf(*(string - 2)) << '_' << Hexf(*(string - 1)) << "   ");
    } else if ((item >> 16) == 0) {
      if (string + 3 >= stop) return nullptr;

      *string++ = CH1(0xE0 | (item >> 12));
      *string++ = CH1(msb_mask | ((item >> 6) & lsb_mask));
      *string++ = CH1(msb_mask | (item & lsb_mask));
      D_COUT(Hexf(*(string - 3)) << '_' << Hexf(*(string - 2)) << '_'
                                 << Hexf(*(string - 1)) << "   ");
    } else if ((item >> 21) == 0) {
      if (string + 4 >= stop) return nullptr;
      *string++ = CH1(0xF0 | (item >> 18));
      *string++ = CH1(msb_mask | ((item >> 12) & lsb_mask));
      *string++ = CH1(msb_mask | ((item >> 6) & lsb_mask));
      *string++ = CH1(msb_mask | (item & lsb_mask));
      D_COUT(Hexf(*(string - 4))
             << '_' << Hexf(*(string - 3)) << '_' << Hexf(*(string - 2)) << '_'
             << Hexf(*(string - 1)) << "   ");
    } else {
      D_COUT("\n\nUTF8 print Error: CH4 is out of range!");
      return nullptr;
    }
  }
  *string = 0;
  return string;
}

const CH1* SScan(const CH1* string, CH4& item) {
  if (!string) return nullptr;
  CH1 c = CH4(*string++);
  CH4 lsb_mask = 0x3f, msb = 0x80, result = 0;
  D_COUT("SScan:" << Hexf(c));
  if (!(c >> 7)) {
    result = CH4(c);
  } else if ((UI1(c) >> 5) == 6) {
    result = (c & 31) << 6;
    c = CH4(*string++);
    D_COUT(Hexf(c));
    if (!(c & msb)) return nullptr;
    result |= c & CH4(63);
    D_COUT(Hexf(*(string - 1)));
  } else if ((UI1(c) >> 4) == 0xE) {
    result = CH4(c & 15) << 12;
    c = CH4(*string++);
    if (!(c & msb)) return nullptr;
    result |= (c & 63) << 6;
    c = CH4(*string++);
    if (!(c & msb)) return nullptr;
    result |= c & lsb_mask;
    D_COUT('_' << Hexf(*(string - 2)) << '_' << Hexf(*(string - 1)));
  } else if ((UI1(c) >> 3) == 0x1E) {
    result = CH4(c & 7) << 18;
    c = CH4(*string++);
    if (!(c & msb)) return nullptr;
    result |= (c & lsb_mask) << 12;
    c = CH4(*string++);
    if (!(c & msb)) return nullptr;
    result |= (c & lsb_mask) << 6;
    c = CH4(*string++);
    if (!(c & msb)) return nullptr;
    result |= c & lsb_mask;
    D_COUT('_' << Hexf(*(string - 3)) << '_' << Hexf(*(string - 2)) << '_'
               << Hexf(*(string - 1)));
  } else {
    D_COUT(" error:0x" << Hexf(c) << '_' << Hexf(*string++) << '_'
                       << Hexf(*string++) << '_' << Hexf(*string++) << '\n');
    return nullptr;
  }
  item = result;
  return string;
}

CH1* SPrint(CH1* start, CH1* stop, CH2 item) {
  // | Byte 1   | Byte 2   | Byte 3   |  UTF-32 Result   |
  // |:--------:|:--------:|:--------:|:----------------:|
  // | 0aaaaaaa |          |          | 000000000aaaaaaa |
  // | 110aaaaa | 10bbbbbb |          | 00000aaaaabbbbbb |
  // | 1110aaaa | 10bbbbbb | 10cccccc | aaaabbbbbbcccccc |
#if USING_UTF32 == YES_0
  return SPrint(start, stop, CH4(item));
#else
  enum { k2ByteMSbMask = 0xC0, k3ByteMSbMask = 0xE0, k4ByteMSbMask = 0xF0 };
  if (!start || start >= stop) return nullptr;
  if (!(item >> 7)) {  // 1 byte.
    if (start + 1 > stop) return nullptr;
    *start++ = CH1(item);
    *start = 0;
    return start;
  }
  CH2 lsb_mask = 0x3f, msb_mask = 0x80;
  if (!(item >> 12)) {  // 2 bytes.
    if (start + 2 >= stop) return nullptr;
    *start++ = (CH1)(0xC0 | item >> 6);
    *start++ = (CH1)(msb_mask | ((item >> 6) & lsb_mask));
    *start = 0;
    return start;
  }  // else 3 bytes.
  if (start + 3 >= stop) return nullptr;
  *start++ = (CH1)(0xE0 | item >> 12);
  *start++ = (CH1)(msb_mask | ((item >> 6) & lsb_mask));
  *start++ = (CH1)(msb_mask | ((item >> 12) & lsb_mask));
  *start = 0;
  return start;
#endif
}
#if USING_UTF16 == YES_0
CH2* SPrint(CH2* start, CH2* stop, CH4 item) {
  // | Bytes {4N, 4N+ 1} | Bytes {4N + 2, 4N+ 3} |    UTF-32 Result     |
  // |:-----------------:|:---------------------:|:--------------------:|
  // | 000000aaaaaaaaaa  |                       | 0000000000aaaaaaaaaa |
  // | 110110yyyyyyyyyy  |   110111xxxxxxxxxx    | yyyyyyyyyyxxxxxxxxxx |
  // |      0xD800       |         0xDC00        |                      |
  if (!start || start + 1 >= stop) return nullptr;
  CH4 lsb_mask = 0x3f, lsb = item & lsb_mask, msb = item >> 10;
  if (!msb) {
    if (start + 1 > stop) return nullptr;
    *start++ = CH2(item);
    D_COUT("\nPrinting 1:" << (Hexf(CH2(item))));
    *start = 0;
    return start;
  } else {
    CH4 msb_mask = 0xDC00;
    if (msb >> 10) return nullptr;  // Non-Unicode value.
    if (start + 2 >= stop) return nullptr;
    CH2 nibble = (CH2)(lsb & msb_mask);
    D_COUT("\nPrinting 2:" << Hexf(CH2(nibble)));
    *start++ = nibble;
    nibble = (CH2)(msb & msb_mask);
    D_COUT(Hexf(CH2(nibble)));
    *start++ = nibble;
    *start = 0;
    return start;
  }
}

const CH2* SScan(const CH2* string, CH4& item) {
  // | Bytes {4N, 4N+ 1} | Bytes {4N + 2, 4N+ 3} | UTF-32 Result        |
  // |:-----------------:|:---------------------:|:--------------------:|
  // | 000000aaaaaaaaaa  |                       | 0000000000aaaaaaaaaa |
  // | 110110aaaaaaaaaa  | 110111bbbbbbbbbb      | aaaaaaaaaabbbbbbbbbb |
  CH2 c = *string++;
  CH2 lsb_mask = (1 << 10) - 1;
  if (c <= lsb_mask) {
    D_COUT(" Scanning 1:" << Hexf(c));
    item = CH4(c);
  } else if ((c >> 10) == 30) {
    D_COUT(" Scanning 1:" << Hexf(c));
    CH4 r = (CH4(c)) & lsb_mask;
    c = *string++;
    if (c >> 10 != 55) return nullptr;
    r |= ((CH4)(c & lsb_mask)) << 10;
  } else {
    D_COUT(" SScan error:" << Hexf(c));
    return nullptr;
  }
  return string;
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

void* Valuef::Value() { return value.WordPTR(); }

void* Valuef::ToPtr() { return value.ToPTR(); }

CH1* Valuef::ToST1() { return value.ToST1(); }
CH2* Valuef::ToST2() { return value.ToST2(); }
CH4* Valuef::ToST3() { return value.ToST3(); }

UIW Valuef::ToWord() { return value.Word(); }

Hexf::Hexf(const void* origin, SIW size) : element(origin, size) {}
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
Hexf::Hexf(const void* item) : element(UIW(item), -SIW(sizeof(const void*))) {}
Hexf::Hexf(CH1 item) : element(item, -SIW(sizeof(SI1))) {}
Hexf::Hexf(SI1 item) : element(item, -SIW(sizeof(SI1))) {}
Hexf::Hexf(UI1 item) : element(item, -SIW(sizeof(UI1))) {}
Hexf::Hexf(CH2 item) : element(item, -SIW(sizeof(CH2))) {}
Hexf::Hexf(SI2 item) : element(item, -SIW(sizeof(SI2))) {}
Hexf::Hexf(UI2 item) : element(item, -SIW(sizeof(UI2))) {}
Hexf::Hexf(CH4 item) : element(item, -SIW(sizeof(CH4))) {}
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

Binaryf::Binaryf(const void* origin, SIW size) : element(origin, size) {}
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

Binaryf::Binaryf(const void* origin, SIW size) : valuef(origin, size) {}
Binaryf::Binaryf(const void* origin) : valuef(origin, sizeof(const void*)) {}
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

// Stringf::Stringf () {}
Stringf::Stringf() : type_(kNIL), count_(0), buffer_() {
  String_ = &buffer_[0];
  *buffer_ = 0;
}
//< Visual C++ is complaining about unitialized members. I think it's a bug.

Stringf::Stringf(const CH1* item) : String_(item), count_(0) { Print(item); }
#if USING_UTF16 == YES_0
Stringf::Stringf(const CH2* item) : String_(item), count_(0) { Print(item); }
#endif
#if USING_UTF32 == YES_0
Stringf::Stringf(const CH4* item) : String_(item), count_(0) { Print(item); }
#endif
Stringf::Stringf(CH1 item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(CH2 item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(CH4 item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(SI4 item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(UI4 item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(SI8 item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(UI8 item) : String_(buffer_), count_(0) { Print(item); }
#if USING_FP4 == YES_0
Stringf::Stringf(FP4 item) : String_(buffer_), count_(0) { Print(item); }
#endif
#if USING_FP8 == YES_0
Stringf::Stringf(FP8 item) : String_(buffer_), count_(0) { Print(item); }
#endif
Stringf::Stringf(const CH1* item, SIW count) : String_(item), count_(count) {
  Print(item);
}
#if USING_UTF16 == YES_0
Stringf::Stringf(const CH2* item, SIW count) : String_(item), count_(count) {
  Print(item);
}
#endif
#if USING_UTF32 == YES_0
Stringf::Stringf(const CH4* item, SIW count) : String_(item), count_(count) {
  Print(item);
}
#endif
Stringf::Stringf(CH1 item, SIW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(CH2 item, SIW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(CH4 item, SIW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(SI4 item, SIW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(UI4 item, SIW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(SI8 item, SIW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(UI8 item, SIW count) : String_(buffer_), count_(count) {
  Print(item);
}
#if USING_FP4 == YES_0
Stringf::Stringf(FP4 item, SIW count) : String_(buffer_), count_(count) {
  Print(item);
}
#endif
#if USING_FP8 == YES_0
Stringf::Stringf(FP8 item, SIW count) : String_(buffer_), count_(count) {
  Print(item);
}
#endif
Stringf::Stringf(TypeValue item, SIW count) : String_(buffer_), count_(count) {
  Print(item);
}

UIW Stringf::Word() { return buffer_[0]; }

void* Stringf::Value() { return buffer_; }

void* Stringf::Ptr() { return reinterpret_cast<void*>(buffer_[0]); }

const CH1* Stringf::ST1() { return reinterpret_cast<const CH1*>(String_); }
const CH2* Stringf::ST2() { return reinterpret_cast<const CH2*>(String_); }
const CH4* Stringf::ST3() { return reinterpret_cast<const CH4*>(String_); }

SIW Stringf::Type() const { return type_; }

SIW Stringf::Count() const { return count_; }

void Stringf::Print(const CH1* item) {
  type_ = kST1;
  String_ = item;
}
#if USING_UTF16 == YES_0
void Stringf::Print(const CH2* item) {
  type_ = kST2;
  String_ = item;
}
#endif
#if USING_UTF32 == YES_0
void Stringf::Print(const CH4* item) {
  type_ = kST3;
  String_ = item;
}
#endif

void Stringf::Print(CH1 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
  _::SPrint(buffer, buffer + kLengthMax, item);
  type_ = kST1;
  String_ = buffer_;
}

#if USING_UTF16 == YES_0
void Stringf::Print(CH2 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
  _::SPrint(buffer, buffer + kLengthMax, item);
  type_ = kST1;
  String_ = buffer_;
}
#endif
#if USING_UTF32 == YES_0
void Stringf::Print(CH4 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
  _::SPrint(buffer, buffer + kLengthMax, item);
  type_ = kST1;
  String_ = buffer;
}
#endif
void Stringf::Print(SI4 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
#if SEAM >= SCRIPT2_ITOS
  _::TSPrint<CH1>(buffer, buffer + kLengthMax, item);
#endif
  type_ = kST1;
  String_ = buffer;
}

void Stringf::Print(UI4 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
#if SEAM >= SCRIPT2_ITOS
  _::TSPrint<CH1>(buffer, buffer + kLengthMax, item);
#endif
  type_ = kST1;
  String_ = buffer;
}

void Stringf::Print(SI8 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
#if SEAM >= SCRIPT2_ITOS
  _::TSPrint<CH1>(buffer, buffer + kLengthMax, item);
#endif
  type_ = kST1;
  String_ = buffer;
}

void Stringf::Print(UI8 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
#if SEAM >= SCRIPT2_ITOS
  _::TSPrint<CH1>(buffer, buffer + kLengthMax, item);
#endif
  type_ = kST1;
  String_ = buffer;
}

#if USING_FP4 == YES_0
void Stringf::Print(FP4 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
  _::TSPrint<CH1>(buffer, buffer + kLengthMax, item);
  type_ = kST1;
  String_ = buffer;
}
#endif
#if USING_FP8 == YES_0
void Stringf::Print(FP8 item) {
  CH1* buffer = reinterpret_cast<CH1*>(buffer_);
  _::TSPrint<CH1>(buffer, buffer + kLengthMax, item);
  type_ = kST1;
  String_ = buffer;
}
#endif

void Stringf::PrintTM4(TM4 item) {}

void Stringf::PrintTME(TM4 item, UI4 subsecond_tick) {}

void Stringf::PrintTM8(TM8 item) {}

void Stringf::Print(TypeValue item) {
  DTW type = item.Type();
  type_ = type;
  static const CH1 kNotSupported[] = "Not supported\0";
  DTW pod_type = type & kTypePODMask;
  if (type != pod_type) {  // It's not a POD type.
  }
  switch (type) {
    case kNIL:
      // CH4 c = 2205; // Empty-set Unicode character.
      return;
    case kCH1:
      Print(CH1(item.ToUI1()));
      return;
    case kSI1:
      Print(SI1(item.ToUI1()));
      return;
    case kUI1:
      Print((item.ToUI1()));
      return;
    case kCH2:
      Print(CH2(item.ToUI2()));
      return;
    case kSI2:
      Print(SI2(item.ToUI2()));
      return;
    case kUI2:
      Print(item.ToUI2());
      return;
    case kFP2:
      Print(item.ToUI2());
      return;
    case kCH4:
      Print(CH4(item.ToUI4()));
      return;
    case kSI4:
      Print(SI4(item.ToUI4()));
      return;
    case kUI4:
      Print(UI4(item.ToUI4()));
      return;
    case kFP4:
#if USING_FP4 == YES_0
      Print(ToFloat(item.ToUI4()));
#endif
      return;
    case kTME:
      PrintTME(SI4(item.Word()), UI4(item.Word2()));
    case kSI8:
      Print(SI8(item.ToUI8()));
      return;
    case kUI8:
      Print(item.ToUI8());
      return;
    case kFP8:
#if USING_FP8 == YES_0
      Print(ToFloat(item.ToUI8()));
#endif
      return;
  }
  String_ = kNotSupported;
}

void Stringf::Hex(CH1 item, SIW count) {
  *reinterpret_cast<CH1*>(buffer_) = item;
  type_ = kCH1;
  count_ = -count;
}
#if USING_UTF16 == YES_0
void Stringf::Hex(CH2 item, SIW count) {
  *reinterpret_cast<CH2*>(buffer_) = item;
  type_ = kCH2;
  count_ = -count;
}
#endif
#if USING_UTF32 == YES_0
void Stringf::Hex(CH4 item, SIW count) {
  *reinterpret_cast<CH4*>(buffer_) = item;
  type_ = kCH4;
  count_ = -count;
}
#endif
void Stringf::Hex(SI1 item, SIW count) {
  *reinterpret_cast<SI1*>(buffer_) = item;
  type_ = kSI1;
  count_ = -count;
}
void Stringf::Hex(UI1 item, SIW count) {
  *reinterpret_cast<UI1*>(buffer_) = item;
  type_ = kUI1;
  count_ = -count;
}

void Stringf::Hex(SI2 item, SIW count) {
  *reinterpret_cast<SI2*>(buffer_) = item;
  type_ = kSI2;
  count_ = -count;
}

void Stringf::Hex(UI2 item, SIW count) {
  *reinterpret_cast<UI2*>(buffer_) = item;
  type_ = kUI2;
  count_ = -count;
}

void Stringf::Hex(SI4 item, SIW count) {
  *reinterpret_cast<SI4*>(buffer_) = item;
  type_ = kSI4;
  count_ = -count;
}

void Stringf::Hex(UI4 item, SIW count) {
  *reinterpret_cast<UI4*>(buffer_) = item;
  type_ = kUI4;
}

void Stringf::Hex(SI8 item, SIW count) {
  *reinterpret_cast<SI8*>(buffer_) = item;
  type_ = kSI8;
  count_ = -count;
}

void Stringf::Hex(UI8 item, SIW count) {
  *reinterpret_cast<UI8*>(buffer_) = item;
  type_ = kUI8;
  count_ = -count;
}

#if USING_FP4 == YES_0
void Stringf::Hex(FP4 item, SIW count) {
  *reinterpret_cast<FP4*>(buffer_) = item;
  type_ = kFP4;
  count_ = -count;
}
#endif

#if USING_FP8 == YES_0
void Stringf::Hex(FP8 item, SIW count) {
  *reinterpret_cast<FP8*>(buffer_) = item;
  type_ = kFP8;
  count_ = -count;
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

Linef::Linef(CH1 item, SIW count) : element(string, count) {
  CH1* cursor = string;
  *cursor++ = item;
  *cursor++ = item;
  *cursor++ = item;
  *cursor = 0;
}
Linef::Linef(const CH1* item, SIW count) : element(item, count) {}

Headingf::Headingf(const CH1* caption1)
    : element(caption1, kConsoleWidth),
      style(nullptr),
      caption2(nullptr),
      caption3(nullptr) {}

Headingf::Headingf(const CH1* caption1, const CH1* caption2)
    : element(caption1, kConsoleWidth),
      style(nullptr),
      caption2(caption2),
      caption3(nullptr) {}

Headingf::Headingf(const CH1* caption1, const CH1* caption2,
                   const CH1* caption3, const CH1* style, SIW count)
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

#if SEAM >= SCRIPT2_FTOS
#if SEAM == SCRIPT2_FTOS
#include "_debug.inl"
#else
#include "_release.inl"
#endif

#include <cstdio>  // For sprintf_s

namespace _ {

CH1* SPrint(CH1* string, CH1* stop, FP4 value) {
  if (!string || string >= stop) return nullptr;
  SIW size = stop - string;
  D_COUT("\nString:" << Hexf(string) << " end:" << Hexf(stop)
                     << " size:" << size << "\nExpecting:" << value);
  SI4 count = sprintf_s(string, stop - string, "%f", value);
  if (count <= 0) return nullptr;
  return string + count;
}

#if USING_FP8 == YES_0
CH1* SPrint(CH1* start, CH1* stop, FP8 value) {
  if (!start || start >= stop) return nullptr;
  SIW size = stop - start;
  SI4 count = sprintf_s(start, size, "%lf", value);
  if (count <= 0) return nullptr;
  return start + count;
}
#endif
#if USING_FP4 == YES_0
const CH1* SScan(const CH1* start, FP4& value) {
  SI4 count = sscanf_s(start, "%f", &value);
  return TSTRFloatStop<CH1>(start);
}
#endif
const CH1* SScan(const CH1* start, FP8& value) {
  SI4 count = sscanf_s(start, "%lf", &value);
  return TSTRFloatStop<CH1>(start);
}
}  // namespace _
#endif
