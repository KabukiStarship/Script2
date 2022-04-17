/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Stringf.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#include "Stringf.hpp"
namespace _ {
const CHA* STRPrintCharsHeader() {
  return "\n|0       8       16      24      32      40      48      56      |"
         " Begin address:";
}

const CHA* STRPrintCharsBorder() {
  return "\n|+-------+-------+-------+-------+-------+-------+-------+-------|"
         " ";
}

const CHA* STRPrintHexHeader() {
  return "\n|0               8               16              24              "
         "|  Begin address:";
}

const CHA* STRPrintHexBorder() {
  return "\n|+---------------+---------------+---------------+---------------|"
         " ";
}

}  //< namespace _

#if SEAM >= SCRIPT2_CORE
#if SEAM == SCRIPT2_CORE
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif

namespace _ {

CHA* SPrint(CHA* string, CHA* stop, CHC item) {
  // | Byte 1   | Byte 2   | Byte 3   | Byte 4   | UTF-32 Result         |
  // |:--------:|:--------:|:--------:|:--------:|:---------------------:|
  // | 0aaaaaaa |          |          |          | 00000000000000aaaaaaa |
  // | 110aaaaa | 10bbbbbb |          |          | 0000000000aaaaabbbbbb |
  // | 1110aaaa | 10bbbbbb | 10cccccc |          | 00000aaaabbbbbbcccccc |
  // | 11110aaa | 10bbbbbb | 10cccccc | 10dddddd | aaabbbbbbccccccdddddd |

  if (!string) return nullptr;

  D_COUT("\n\n" << IUC(item) << ".) Printed:0x");
  if (!(item >> 7)) {  // 1 ASCII CHA.
    if (string + 1 > stop) return nullptr;
    *string++ = CHA(item);
    D_COUT(Hexf(*(string - 1)) << "   ");
  } else {
    CHB lsb_mask = 0x3f, msb_mask = 0x80;
    if ((item >> 11) == 0) {
      if (string + 2 >= stop) return nullptr;
      *string++ = CHA(0xC0 | (item >> 6));
      *string++ = CHA(msb_mask | (item & lsb_mask));
      D_COUT(Hexf(*(string - 2)) << '_' << Hexf(*(string - 1)) << "   ");
    } else if ((item >> 16) == 0) {
      if (string + 3 >= stop) return nullptr;

      *string++ = CHA(0xE0 | (item >> 12));
      *string++ = CHA(msb_mask | ((item >> 6) & lsb_mask));
      *string++ = CHA(msb_mask | (item & lsb_mask));
      D_COUT(Hexf(*(string - 3)) << '_' << Hexf(*(string - 2)) << '_'
                                 << Hexf(*(string - 1)) << "   ");
    } else if ((item >> 21) == 0) {
      if (string + 4 >= stop) return nullptr;
      *string++ = CHA(0xF0 | (item >> 18));
      *string++ = CHA(msb_mask | ((item >> 12) & lsb_mask));
      *string++ = CHA(msb_mask | ((item >> 6) & lsb_mask));
      *string++ = CHA(msb_mask | (item & lsb_mask));
      D_COUT(Hexf(*(string - 4))
             << '_' << Hexf(*(string - 3)) << '_' << Hexf(*(string - 2)) << '_'
             << Hexf(*(string - 1)) << "   ");
    } else {
      D_COUT("\n\nUTF8 print Error: CHC is out of range!");
      return nullptr;
    }
  }
  *string = 0;
  return string;
}

const CHA* SScan(const CHA* string, CHC& item) {
  if (!string) return nullptr;
  CHA c = CHC(*string++);
  CHC lsb_mask = 0x3f, msb = 0x80, result = 0;
  D_COUT("SScan:" << Hexf(c));
  if (!(c >> 7)) {
    result = CHC(c);
  } else if ((IUA(c) >> 5) == 6) {
    result = (c & 31) << 6;
    c = CHC(*string++);
    D_COUT(Hexf(c));
    if (!(c & msb)) return nullptr;
    result |= c & CHC(63);
    D_COUT(Hexf(*(string - 1)));
  } else if ((IUA(c) >> 4) == 0xE) {
    result = CHC(c & 15) << 12;
    c = CHC(*string++);
    if (!(c & msb)) return nullptr;
    result |= (c & 63) << 6;
    c = CHC(*string++);
    if (!(c & msb)) return nullptr;
    result |= c & lsb_mask;
    D_COUT('_' << Hexf(*(string - 2)) << '_' << Hexf(*(string - 1)));
  } else if ((IUA(c) >> 3) == 0x1E) {
    result = CHC(c & 7) << 18;
    c = CHC(*string++);
    if (!(c & msb)) return nullptr;
    result |= (c & lsb_mask) << 12;
    c = CHC(*string++);
    if (!(c & msb)) return nullptr;
    result |= (c & lsb_mask) << 6;
    c = CHC(*string++);
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

CHA* SPrint(CHA* start, CHA* stop, CHB item) {
  // | Byte 1   | Byte 2   | Byte 3   |  UTF-32 Result   |
  // |:--------:|:--------:|:--------:|:----------------:|
  // | 0aaaaaaa |          |          | 000000000aaaaaaa |
  // | 110aaaaa | 10bbbbbb |          | 00000aaaaabbbbbb |
  // | 1110aaaa | 10bbbbbb | 10cccccc | aaaabbbbbbcccccc |
#if USING_UTF32 == YES_0
  return SPrint(start, stop, CHC(item));
#else
  enum { c2ByteMSbMask = 0xC0, c3ByteMSbMask = 0xE0, c4ByteMSbMask = 0xF0 };
  if (!start || start >= stop) return nullptr;
  if (!(item >> 7)) {  // 1 byte.
    if (start + 1 > stop) return nullptr;
    *start++ = CHA(item);
    *start = 0;
    return start;
  }
  CHB lsb_mask = 0x3f, msb_mask = 0x80;
  if (!(item >> 12)) {  // 2 bytes.
    if (start + 2 >= stop) return nullptr;
    *start++ = (CHA)(0xC0 | item >> 6);
    *start++ = (CHA)(msb_mask | ((item >> 6) & lsb_mask));
    *start = 0;
    return start;
  }  // else 3 bytes.
  if (start + 3 >= stop) return nullptr;
  *start++ = (CHA)(0xE0 | item >> 12);
  *start++ = (CHA)(msb_mask | ((item >> 6) & lsb_mask));
  *start++ = (CHA)(msb_mask | ((item >> 12) & lsb_mask));
  *start = 0;
  return start;
#endif
}
#if USING_UTF16 == YES_0
CHB* SPrint(CHB* start, CHB* stop, CHC item) {
  // | Bytes {4N, 4N+ 1} | Bytes {4N + 2, 4N+ 3} |    UTF-32 Result     |
  // |:-----------------:|:---------------------:|:--------------------:|
  // | 000000aaaaaaaaaa  |                       | 0000000000aaaaaaaaaa |
  // | 110110yyyyyyyyyy  |   110111xxxxxxxxxx    | yyyyyyyyyyxxxxxxxxxx |
  // |      0xD800       |         0xDC00        |                      |
  if (!start || start + 1 >= stop) return nullptr;
  CHC lsb_mask = 0x3f, lsb = item & lsb_mask, msb = item >> 10;
  if (!msb) {
    if (start + 1 > stop) return nullptr;
    *start++ = CHB(item);
    D_COUT("\nPrinting 1:" << (Hexf(CHB(item))));
    *start = 0;
    return start;
  } else {
    CHC msb_mask = 0xDC00;
    if (msb >> 10) return nullptr;  // Non-Unicode value.
    if (start + 2 >= stop) return nullptr;
    CHB nibble = (CHB)(lsb & msb_mask);
    D_COUT("\nPrinting 2:" << Hexf(CHB(nibble)));
    *start++ = nibble;
    nibble = (CHB)(msb & msb_mask);
    D_COUT(Hexf(CHB(nibble)));
    *start++ = nibble;
    *start = 0;
    return start;
  }
}

const CHB* SScan(const CHB* string, CHC& item) {
  // | Bytes {4N, 4N+ 1} | Bytes {4N + 2, 4N+ 3} | UTF-32 Result        |
  // |:-----------------:|:---------------------:|:--------------------:|
  // | 000000aaaaaaaaaa  |                       | 0000000000aaaaaaaaaa |
  // | 110110aaaaaaaaaa  | 110111bbbbbbbbbb      | aaaaaaaaaabbbbbbbbbb |
  CHB c = *string++;
  CHB lsb_mask = (1 << 10) - 1;
  if (c <= lsb_mask) {
    D_COUT(" Scanning 1:" << Hexf(c));
    item = CHC(c);
  } else if ((c >> 10) == 30) {
    D_COUT(" Scanning 1:" << Hexf(c));
    CHC r = (CHC(c)) & lsb_mask;
    c = *string++;
    if (c >> 10 != 55) return nullptr;
    r |= ((CHC)(c & lsb_mask)) << 10;
  } else {
    D_COUT(" SScan error:" << Hexf(c));
    return nullptr;
  }
  return string;
}
#endif

}  //< namespace _
#endif

namespace _ {

Valuef::Valuef() : count(0), value() {}

Valuef::Valuef(void* item, ISW count) : count(count), value(item) {}
Valuef::Valuef(const void* item, ISW count) : count(count), value(item) {}
#if USING_UTF8 == YES_0
Valuef::Valuef(CHA item, ISW count) : count(count), value(item) {}
Valuef::Valuef(const CHA* item, ISW count) : count(count), value(item) {}
#endif
#if USING_UTF16 == YES_0
Valuef::Valuef(CHB item, ISW count) : count(count), value(item) {}
Valuef::Valuef(const CHB* item, ISW count) : count(count), value(item) {}
#endif
#if USING_UTF32 == YES_0
Valuef::Valuef(CHC item, ISW count) : count(count), value(item) {}
Valuef::Valuef(const CHC* item, ISW count) : count(count), value(item) {}
#endif
Valuef::Valuef(ISA item, ISW count) : count(count), value(item) {}
Valuef::Valuef(IUA item, ISW count) : count(count), value(item) {}
Valuef::Valuef(ISB item, ISW count) : count(count), value(item) {}
Valuef::Valuef(IUB item, ISW count) : count(count), value(item) {}
Valuef::Valuef(ISC item, ISW count) : count(count), value(item) {}
Valuef::Valuef(IUC item, ISW count) : count(count), value(item) {}
Valuef::Valuef(ISD item, ISW count) : count(count), value(item) {}
Valuef::Valuef(IUD item, ISW count) : count(count), value(item) {}
#if USING_FPC == YES_0
Valuef::Valuef(FPC item, ISW count) : count(count), value(item) {}
#endif
#if USING_FPD == YES_0
Valuef::Valuef(FPD item, ISW count) : count(count), value(item) {}
#endif

ISW Valuef::Type() { return value.Type(); }

ISW Valuef::Count() { return count; }

void* Valuef::Value() { return value.WordPTR(); }

void* Valuef::ToPtr() { return value.ToPTR(); }

CHA* Valuef::ToSTA() { return value.ToSTA(); }
CHB* Valuef::ToSTB() { return value.ToSTB(); }
CHC* Valuef::ToSTC() { return value.ToSTC(); }

IUW Valuef::ToWord() { return value.Word(); }

Hexf::Hexf(const void* origin, ISW size) : element(origin, size) {}
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
Hexf::Hexf(const void* item) : element(IUW(item), -ISW(sizeof(const void*))) {}
Hexf::Hexf(CHA item) : element(item, -ISW(sizeof(ISA))) {}
Hexf::Hexf(ISA item) : element(item, -ISW(sizeof(ISA))) {}
Hexf::Hexf(IUA item) : element(item, -ISW(sizeof(IUA))) {}
Hexf::Hexf(CHB item) : element(item, -ISW(sizeof(CHB))) {}
Hexf::Hexf(ISB item) : element(item, -ISW(sizeof(ISB))) {}
Hexf::Hexf(IUB item) : element(item, -ISW(sizeof(IUB))) {}
Hexf::Hexf(CHC item) : element(item, -ISW(sizeof(CHC))) {}
Hexf::Hexf(ISC item) : element(item, -ISW(sizeof(ISC))) {}
Hexf::Hexf(IUC item) : element(item, -ISW(sizeof(IUC))) {}
Hexf::Hexf(ISD item) : element(item, -ISW(sizeof(ISD))) {}
Hexf::Hexf(IUD item) : element(item, -ISW(sizeof(IUD))) {}
#if USING_FPC == YES_0
Hexf::Hexf(FPC item) : element(item, -ISW(sizeof(FPC))) {}
#endif
#if USING_FPD == YES_0
Hexf::Hexf(FPD item) : element(item, -ISW(sizeof(FPD))) {}
#endif

Binaryf::Binaryf(const void* origin, ISW size) : element(origin, size) {}
Binaryf::Binaryf(const void* item)
    : element(IUW(item), -ISW(sizeof(const void*))) {}
Binaryf::Binaryf(ISA item) : element(item, -ISW(sizeof(ISA))) {}
Binaryf::Binaryf(IUA item) : element(item, -ISW(sizeof(IUA))) {}
Binaryf::Binaryf(ISB item) : element(item, -ISW(sizeof(ISB))) {}
Binaryf::Binaryf(IUB item) : element(item, -ISW(sizeof(IUB))) {}
Binaryf::Binaryf(ISC item) : element(item, -ISW(sizeof(ISC))) {}
Binaryf::Binaryf(IUC item) : element(item, -ISW(sizeof(IUC))) {}
Binaryf::Binaryf(ISD item) : element(item, -ISW(sizeof(ISD))) {}
Binaryf::Binaryf(IUD item) : element(item, -ISW(sizeof(IUD))) {}
#if USING_FPC == YES_0
Binaryf::Binaryf(FPC item) : element(item, -ISW(sizeof(FPC))) {}
#endif
#if USING_FPD == YES_0
Binaryf::Binaryf(FPD item) : element(item, -ISW(sizeof(FPD))) {}
#endif
#else
Hexf::Hexf(const void* item) : valuef(item, sizeof(const void*)) {}
Hexf::Hexf(ISA item) : valuef(item, sizeof(ISA)) {}
Hexf::Hexf(IUA item) : valuef(item, sizeof(IUA)) {}
Hexf::Hexf(ISB item) : valuef(item, sizeof(ISB)) {}
Hexf::Hexf(IUB item) : valuef(item, sizeof(IUB)) {}
Hexf::Hexf(ISC item) : valuef(item, sizeof(ISC)) {}
Hexf::Hexf(IUC item) : valuef(item, sizeof(IUC)) {}
Hexf::Hexf(ISD item) : valuef(item, sizeof(ISD)) {}
Hexf::Hexf(IUD item) : valuef(item, sizeof(IUD)) {}
#if USING_FPD == YES_0
Hexf::Hexf(FPC item) : valuef(item, sizeof(FPC)) {}
#endif
#if USING_FPD == YES_0
Hexf::Hexf(FPD item) : valuef(item, sizeof(FPD)) {}
#endif

Binaryf::Binaryf(const void* origin, ISW size) : valuef(origin, size) {}
Binaryf::Binaryf(const void* origin) : valuef(origin, sizeof(const void*)) {}
Binaryf::Binaryf(ISA item) : valuef(item, sizeof(ISA)) {}
Binaryf::Binaryf(IUA item) : valuef(item, sizeof(IUA)) {}
Binaryf::Binaryf(ISB item) : valuef(item, sizeof(ISB)) {}
Binaryf::Binaryf(IUB item) : valuef(item, sizeof(IUB)) {}
Binaryf::Binaryf(ISC item) : valuef(item, sizeof(ISC)) {}
Binaryf::Binaryf(IUC item) : valuef(item, sizeof(IUC)) {}
Binaryf::Binaryf(ISD item) : valuef(item, sizeof(ISD)) {}
Binaryf::Binaryf(IUD item) : valuef(item, sizeof(IUD)) {}
#if USING_FPD == YES_0
Binaryf::Binaryf(FPC item) : valuef(item, sizeof(FPC)) {}
#endif
#if USING_FPD == YES_0
Binaryf::Binaryf(FPD item) : valuef(item, sizeof(FPD)) {}
#endif
#endif

// Stringf::Stringf () {}
Stringf::Stringf() : type_(cNIL), count_(0), buffer_() {
  String_ = &buffer_[0];
  *buffer_ = 0;
}
//< Visual C++ is complaining about unitialized members. I think it's a bug.

Stringf::Stringf(const CHA* item) : String_(item), count_(0) { Print(item); }
#if USING_UTF16 == YES_0
Stringf::Stringf(const CHB* item) : String_(item), count_(0) { Print(item); }
#endif
#if USING_UTF32 == YES_0
Stringf::Stringf(const CHC* item) : String_(item), count_(0) { Print(item); }
#endif
Stringf::Stringf(CHA item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(CHB item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(CHC item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(ISC item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(IUC item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(ISD item) : String_(buffer_), count_(0) { Print(item); }
Stringf::Stringf(IUD item) : String_(buffer_), count_(0) { Print(item); }
#if USING_FPC == YES_0
Stringf::Stringf(FPC item) : String_(buffer_), count_(0) { Print(item); }
#endif
#if USING_FPD == YES_0
Stringf::Stringf(FPD item) : String_(buffer_), count_(0) { Print(item); }
#endif
Stringf::Stringf(const CHA* item, ISW count) : String_(item), count_(count) {
  Print(item);
}
#if USING_UTF16 == YES_0
Stringf::Stringf(const CHB* item, ISW count) : String_(item), count_(count) {
  Print(item);
}
#endif
#if USING_UTF32 == YES_0
Stringf::Stringf(const CHC* item, ISW count) : String_(item), count_(count) {
  Print(item);
}
#endif
Stringf::Stringf(CHA item, ISW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(CHB item, ISW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(CHC item, ISW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(ISC item, ISW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(IUC item, ISW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(ISD item, ISW count) : String_(buffer_), count_(count) {
  Print(item);
}
Stringf::Stringf(IUD item, ISW count) : String_(buffer_), count_(count) {
  Print(item);
}
#if USING_FPC == YES_0
Stringf::Stringf(FPC item, ISW count) : String_(buffer_), count_(count) {
  Print(item);
}
#endif
#if USING_FPD == YES_0
Stringf::Stringf(FPD item, ISW count) : String_(buffer_), count_(count) {
  Print(item);
}
#endif
Stringf::Stringf(TypeValue item, ISW count) : String_(buffer_), count_(count) {
  Print(item);
}

IUW Stringf::Word() { return buffer_[0]; }

void* Stringf::Value() { return buffer_; }

void* Stringf::Ptr() { return reinterpret_cast<void*>(buffer_[0]); }

const CHA* Stringf::STA() { return reinterpret_cast<const CHA*>(String_); }
const CHB* Stringf::STB() { return reinterpret_cast<const CHB*>(String_); }
const CHC* Stringf::STC() { return reinterpret_cast<const CHC*>(String_); }

ISW Stringf::Type() const { return type_; }

ISW Stringf::Count() const { return count_; }

void Stringf::Print(const CHA* item) {
  type_ = cSTA;
  String_ = item;
}
#if USING_UTF16 == YES_0
void Stringf::Print(const CHB* item) {
  type_ = cSTB;
  String_ = item;
}
#endif
#if USING_UTF32 == YES_0
void Stringf::Print(const CHC* item) {
  type_ = cSTC;
  String_ = item;
}
#endif

void Stringf::Print(CHA item) {
  CHA* buffer = TPtr<CHA>(buffer_);
  _::SPrint(buffer, buffer + cLengthMax, item);
  type_ = cSTA;
  String_ = buffer_;
}

#if USING_UTF16 == YES_0
void Stringf::Print(CHB item) {
  CHA* buffer = TPtr<CHA>(buffer_);
  _::SPrint(buffer, buffer + cLengthMax, item);
  type_ = cSTA;
  String_ = buffer_;
}
#endif
#if USING_UTF32 == YES_0
void Stringf::Print(CHC item) {
  CHA* buffer = TPtr<CHA>(buffer_);
  _::SPrint(buffer, buffer + cLengthMax, item);
  type_ = cSTA;
  String_ = buffer;
}
#endif
void Stringf::Print(ISC item) {
  CHA* buffer = TPtr<CHA>(buffer_);
#if SEAM >= SCRIPT2_ITOS
  _::TSPrint<CHA>(buffer, buffer + cLengthMax, item);
#endif
  type_ = cSTA;
  String_ = buffer;
}

void Stringf::Print(IUC item) {
  CHA* buffer = TPtr<CHA>(buffer_);
#if SEAM >= SCRIPT2_ITOS
  _::TSPrint<CHA>(buffer, buffer + cLengthMax, item);
#endif
  type_ = cSTA;
  String_ = buffer;
}

void Stringf::Print(ISD item) {
  CHA* buffer = TPtr<CHA>(buffer_);
#if SEAM >= SCRIPT2_ITOS
  _::TSPrint<CHA>(buffer, buffer + cLengthMax, item);
#endif
  type_ = cSTA;
  String_ = buffer;
}

void Stringf::Print(IUD item) {
  CHA* buffer = TPtr<CHA>(buffer_);
#if SEAM >= SCRIPT2_ITOS
  _::TSPrint<CHA>(buffer, buffer + cLengthMax, item);
#endif
  type_ = cSTA;
  String_ = buffer;
}

#if USING_FPC == YES_0
void Stringf::Print(FPC item) {
  CHA* buffer = TPtr<CHA>(buffer_);
  _::TSPrint<CHA>(buffer, buffer + cLengthMax, item);
  type_ = cSTA;
  String_ = buffer;
}
#endif
#if USING_FPD == YES_0
void Stringf::Print(FPD item) {
  CHA* buffer = TPtr<CHA>(buffer_);
  _::TSPrint<CHA>(buffer, buffer + cLengthMax, item);
  type_ = cSTA;
  String_ = buffer;
}
#endif

void Stringf::PrintTMC(TMC item) {}

void Stringf::PrintTME(TMC item, IUC subsecond_tick) {}

void Stringf::PrintTMD(TMD item) {}

void Stringf::Print(TypeValue item) {
  DTW type = item.Type();
  type_ = type;
  static const CHA kNotSupported[] = "Not supported\0";
  DTW pod_type = type & cTypePODMask;
  if (type != pod_type) {  // It's not a POD type.
  }
  switch (type) {
    case cNIL:
      // CHC c = 2205; // Empty-set Unicode character.
      return;
    case cCHA:
      Print(CHA(item.ToIUA()));
      return;
    case cISA:
      Print(ISA(item.ToIUA()));
      return;
    case cIUA:
      Print((item.ToIUA()));
      return;
    case cCHB:
      Print(CHB(item.ToIUB()));
      return;
    case cISB:
      Print(ISB(item.ToIUB()));
      return;
    case cIUB:
      Print(item.ToIUB());
      return;
    case cFPB:
      Print(item.ToIUB());
      return;
    case cCHC:
      Print(CHC(item.ToIUC()));
      return;
    case cISC:
      Print(ISC(item.ToIUC()));
      return;
    case cIUC:
      Print(IUC(item.ToIUC()));
      return;
    case cFPC:
#if USING_FPC == YES_0
      Print(ToFloat(item.ToIUC()));
#endif
      return;
    case cTME:
      PrintTME(ISC(item.Word()), IUC(item.Word2()));
    case cISD:
      Print(ISD(item.ToUID()));
      return;
    case cIUD:
      Print(item.ToUID());
      return;
    case cFPD:
#if USING_FPD == YES_0
      Print(ToFloat(item.ToUID()));
#endif
      return;
  }
  String_ = kNotSupported;
}

void Stringf::Hex(CHA item, ISW count) {
  *TPtr<CHA>(buffer_) = item;
  type_ = cCHA;
  count_ = -count;
}
#if USING_UTF16 == YES_0
void Stringf::Hex(CHB item, ISW count) {
  *reinterpret_cast<CHB*>(buffer_) = item;
  type_ = cCHB;
  count_ = -count;
}
#endif
#if USING_UTF32 == YES_0
void Stringf::Hex(CHC item, ISW count) {
  *reinterpret_cast<CHC*>(buffer_) = item;
  type_ = cCHC;
  count_ = -count;
}
#endif
void Stringf::Hex(ISA item, ISW count) {
  *reinterpret_cast<ISA*>(buffer_) = item;
  type_ = cISA;
  count_ = -count;
}
void Stringf::Hex(IUA item, ISW count) {
  *reinterpret_cast<IUA*>(buffer_) = item;
  type_ = cIUA;
  count_ = -count;
}

void Stringf::Hex(ISB item, ISW count) {
  *reinterpret_cast<ISB*>(buffer_) = item;
  type_ = cISB;
  count_ = -count;
}

void Stringf::Hex(IUB item, ISW count) {
  *TPtr<IUB>(buffer_) = item;
  type_ = cIUB;
  count_ = -count;
}

void Stringf::Hex(ISC item, ISW count) {
  *reinterpret_cast<ISC*>(buffer_) = item;
  type_ = cISC;
  count_ = -count;
}

void Stringf::Hex(IUC item, ISW count) {
  *TPtr<IUC>(buffer_) = item;
  type_ = cIUC;
}

void Stringf::Hex(ISD item, ISW count) {
  *reinterpret_cast<ISD*>(buffer_) = item;
  type_ = cISD;
  count_ = -count;
}

void Stringf::Hex(IUD item, ISW count) {
  *TPtr<IUD>(buffer_) = item;
  type_ = cIUD;
  count_ = -count;
}

#if USING_FPC == YES_0
void Stringf::Hex(FPC item, ISW count) {
  *reinterpret_cast<FPC*>(buffer_) = item;
  type_ = cFPC;
  count_ = -count;
}
#endif

#if USING_FPD == YES_0
void Stringf::Hex(FPD item, ISW count) {
  *reinterpret_cast<FPD*>(buffer_) = item;
  type_ = cFPD;
  count_ = -count;
}
#endif

Centerf::Centerf() {}

#if USING_UTF8 == YES_0
Centerf::Centerf(CHA item, ISW count) : element(item, count) {}
Centerf::Centerf(const CHA* item, ISW count) : element(item, count) {}
#endif
#if USING_UTF16 == YES_0
Centerf::Centerf(CHB item, ISW count) : element(item, count) {}
Centerf::Centerf(const CHB* item, ISW count) : element(item, count) {}
#endif
#if USING_UTF32 == YES_0
Centerf::Centerf(CHC item, ISW count) : element(item, count) {}
Centerf::Centerf(const CHC* item, ISW count) : element(item, count) {}
#endif
Centerf::Centerf(ISC item, ISW count) : element(item, count) {}
Centerf::Centerf(IUC item, ISW count) : element(item, count) {}
Centerf::Centerf(ISD item, ISW count) : element(item, count) {}
#if USING_FPC == YES_0
Centerf::Centerf(FPC item, ISW count) : element(item, count) {}
#endif
#if USING_FPD == YES_0
Centerf::Centerf(FPD item, ISW count) : element(item, count) {}
#endif
Centerf::Centerf(IUD item, ISW count) : element(item, count) {}

Centerf& Centerf::Hex(CHA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_UTF16 == YES_0
Centerf& Centerf::Hex(CHB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_UTF32 == YES_0
Centerf& Centerf::Hex(CHC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
Centerf& Centerf::Hex(ISA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(IUA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(ISB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(IUB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(ISC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(IUC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(ISD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(IUD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_FPC == YES_0
Centerf& Centerf::Hex(FPC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_FPD == YES_0
Centerf& Centerf::Hex(FPD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif

Rightf::Rightf() {}
Rightf::Rightf(CHA item, ISW count) : element(item, count) {}
Rightf::Rightf(const CHA* item, ISW count) : element(item, count) {}
#if USING_UTF16 == YES_0
Rightf::Rightf(CHB item, ISW count) : element(item, count) {}
Rightf::Rightf(const CHB* item, ISW count) : element(item, count) {}
#endif
#if USING_UTF32 == YES_0
Rightf::Rightf(CHC item, ISW count) : element(item, count) {}
Rightf::Rightf(const CHC* item, ISW count) : element(item, count) {}
#endif
Rightf::Rightf(ISC item, ISW count) : element(item, count) {}
Rightf::Rightf(IUC item, ISW count) : element(item, count) {}
Rightf::Rightf(ISD item, ISW count) : element(item, count) {}
Rightf::Rightf(IUD item, ISW count) : element(item, count) {}
#if USING_FPC == YES_0
Rightf::Rightf(FPC item, ISW count) : element(item, count) {}
#endif
#if USING_FPD == YES_0
Rightf::Rightf(FPD item, ISW count) : element(item, count) {}
#endif

Rightf& Rightf::Hex(CHA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_UTF16 == YES_0
Rightf& Rightf::Hex(CHB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_UTF32 == YES_0
Rightf& Rightf::Hex(CHC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
Rightf& Rightf::Hex(ISA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(IUA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(ISB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(IUB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(ISC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(IUC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(ISD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(IUD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_FPC == YES_0
Rightf& Rightf::Hex(FPC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_FPD == YES_0
Rightf& Rightf::Hex(FPD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif

Linef::Linef(CHA item, ISW count) : element(string, count) {
  CHA* cursor = string;
  *cursor++ = '\n';
  *cursor++ = item;
  *cursor++ = item;
  *cursor++ = item;
  *cursor = 0;
}
Linef::Linef(const CHA* item, ISW count) : element(item, count) {}

Headingf::Headingf(const CHA* caption1)
    : element(caption1, cConsoleWidth),
      style(nullptr),
      caption2(nullptr),
      caption3(nullptr) {}

Headingf::Headingf(const CHA* caption1, const CHA* caption2)
    : element(caption1, cConsoleWidth),
      style(nullptr),
      caption2(caption2),
      caption3(nullptr) {}

Headingf::Headingf(const CHA* caption1, const CHA* caption2,
                   const CHA* caption3, const CHA* style, ISW count)
    : element(caption1, count),
      style(style),
      caption2(caption2),
      caption3(caption3) {}

Charsf::Charsf(const void* start, const void* stop)
    : element(reinterpret_cast<const CHA*>(start),
              reinterpret_cast<const CHA*>(stop) -
                  reinterpret_cast<const CHA*>(start)) {}
Charsf::Charsf(const void* start, ISW count)
    : element(reinterpret_cast<const CHA*>(start), count) {}

#if USING_UTF16 == YES_0
Charsf::Charsf(const CHB* start, const CHB* stop)
    : element(start, stop - start) {}
Charsf::Charsf(const CHB* start, ISW count) : element(start, count) {}
#endif
#if USING_UTF32 == YES_0
Charsf::Charsf(const CHC* start, const CHC* stop)
    : element(start, stop - start) {}
Charsf::Charsf(const CHC* start, ISW count) : element(start, count) {}
#endif

Indentf::Indentf(ISW indent_count) : indent_count(indent_count) {}

}  //< namespace _

#if SEAM >= SCRIPT2_FTOS
#if SEAM == SCRIPT2_FTOS
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif

#include <cstdio>  // For sprintf_s

namespace _ {

CHA* SPrint(CHA* string, CHA* stop, FPC value) {
  if (!string || string >= stop) return nullptr;
  ISW size = stop - string;
  D_COUT("\nString:" << Hexf(string) << " end:" << Hexf(stop)
                     << " size:" << size << "\nExpecting:" << value);
  ISC count = sprintf_s(string, stop - string, "%f", value);
  if (count <= 0) return nullptr;
  return string + count;
}

#if USING_FPD == YES_0
CHA* SPrint(CHA* start, CHA* stop, FPD value) {
  if (!start || start >= stop) return nullptr;
  ISW size = stop - start;
  ISC count = sprintf_s(start, size, "%lf", value);
  if (count <= 0) return nullptr;
  return start + count;
}
#endif
#if USING_FPC == YES_0
const CHA* SScan(const CHA* start, FPC& value) {
  ISC count = sscanf_s(start, "%f", &value);
  return TSTRFloatStop<CHA>(start);
}
#endif
const CHA* SScan(const CHA* start, FPD& value) {
  ISC count = sscanf_s(start, "%lf", &value);
  return TSTRFloatStop<CHA>(start);
}
}  //< namespace _
#endif
