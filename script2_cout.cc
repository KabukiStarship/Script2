/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_cout.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#if USING_CONSOLE == YES

#include <cstdio>
#include <iostream>

#include "c_avalue.h"
#include "c_cout.h"
#include "t_puff.h"
#include "t_stringcore.h"

#if SEAM == SEAM_SCRIPT2_CORE
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

#define STD_COUT std::cout

namespace _ {

void Printf(const CH1* format, ...) {
  if (!format) return;
  va_list arg;
  va_start(arg, format);
  vfprintf(stdout, format, arg);
  va_end(arg);
}

COut::COut() {}

COut::COut(CH1 item) { Print(item); }
COut::COut(const CH1* item) { Print(item); }

#if USING_UTF16 == YES
COut::COut(CH2 item) { Print(item); }
COut::COut(const CH2* item) { Print(item); }
#endif
#if USING_UTF32 == YES
COut::COut(CH4 item) { Print(item); }
COut::COut(const CH4* item) { Print(item); }
#endif

COut::COut(SI1 item) { Print(item); }

COut::COut(UI1 item) { Print(item); }

COut::COut(SI2 item) { Print(item); }

COut::COut(UI2 item) { Print(item); }

COut::COut(SI4 item) { Print(item); }

COut::COut(UI4 item) { Print(item); }

COut::COut(SI8 item) { Print(item); }

COut::COut(UI8 item) { Print(item); }

#if USING_FP4 == YES
COut::COut(FP4 item) { Print(item); }
#endif
#if USING_FP8 == YES

COut::COut(FP8 item) { Print(item); }
#endif

COut::COut(Hexf item) { Print(item); }

COut::COut(Binaryf item) { Print(item); }

COut::COut(Centerf item) { Print(item); }

COut::COut(Rightf item) { Print(item); }

COut::COut(Linef item) { Print(item); }

COut::COut(Headingf item) { Print(item); }

COut::COut(Indentf item) { Print(item); }

COut::COut(Charsf item) { Print(item); }

COut::COut(const CH1* item, CH1 second_item) {
  Print(item);
  Print(second_item);
}

COut::COut(const CH1* item, const CH1* second_item) {
  Print(item);
  Print(second_item);
}
COut::COut(CH1 item, CH1 second_item) {
  Print(item);
  Print(second_item);
}
COut::COut(CH1 item, const CH1* second_item) {
  Print(item);
  Print(second_item);
}
COut::COut(CH1 item, CH1 second_item, CH1 third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut::COut(CH1 item, CH1 second_item, const CH1* third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut::COut(const CH1* item, const CH1* second_item, CH1 third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut::COut(const CH1* item, const CH1* second_item, const CH1* third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut& COut::Star() { return *this; }

COut& COut::Print(CH1 item) {
  STD_COUT << item;
  return *this;
}

COut& COut::Print(const CH1* item) {
  return TPrintString<COut, CH1>(*this, item);
}

#if USING_UTF16 == YES
COut& COut::Print(CH2 item) {
  STD_COUT << (CHN)item;
  return *this;
}

COut& COut::Print(const CH2* item) {
  return TPrintString<COut, CH2>(*this, item);
}
#endif
#if USING_UTF32 == YES
COut& COut::Print(CH4 item) {
  STD_COUT << (CHN)item;
  return *this;
}
COut& COut::Print(const CH4* item) {
  return TPrintString<COut, CH4>(*this, item);
}
#endif

COut& COut::Print(SI4 item) {
#if SEAM <= SEAM_SCRIPT2_ITOS
  STD_COUT << item;
#else
#if CPU_SIZE == 64
  Print((SI8)item);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintSigned<SI8, UI8, CH1>(socket, kSize - 1, (SI8)value);
  Print(socket);
#endif
#endif
  return *this;
}

COut& COut::Print(UI4 item) {
#if SEAM <= SEAM_SCRIPT2_ITOS
  STD_COUT << item;
#else
#if CPU_SIZE == 64
  Print((UI8)item);
#else
  enum { kSize = 24 };
  CH1 buffer[kSize];
  TPrintUnsigned<UI4, CH1>(buffer, kSize - 1, item);
  Print(buffer);
#endif
#endif
  return *this;
}

COut& COut::Print(SI8 item) {
#if SEAM <= SEAM_SCRIPT2_ITOS
  STD_COUT << item;
#else
  enum { kSize = 24 };
  CH1 buffer[kSize];
  TPrintSigned<SI8, UI8, CH1>(buffer, kSize - 1, item);
  Print(buffer);
#endif
  return *this;
}

COut& COut::Print(UI8 item) {
#if SEAM <= SEAM_SCRIPT2_ITOS
  STD_COUT << item;
#else
  enum { kSize = 24 };
  CH1 buffer[kSize];
  TPrintUnsigned<UI8, CH1>(buffer, kSize - 1, item);
  Print(buffer);
#endif
  return *this;
}

#if USING_FP4 == YES
COut& COut::Print(FP4 item) {
#if SEAM <= SEAM_SCRIPT2_BOOK
  STD_COUT << item;
#else
  enum { kSize = 16 };
  CH1 buffer[kSize];
  TPrintFloat<FP4, UI4, CH1>(buffer, kSize, value);
  Print(buffer);
#endif
  return *this;
}
#endif
#if USING_FP8 == YES
COut& COut::Print(FP8 item) {
#if SEAM <= SEAM_SCRIPT2_BOOK
  STD_COUT << item;
#else
  enum { kSize = 24 };
  CH1 buffer[kSize];
  TPrintFloat<FP8, UI8, CH1>(buffer, kSize - 1, item);
  Print(buffer);
#endif
  return *this;
}
#endif

COut& COut::Print(Hexf item) {
  return TPrintHex<COut>(*this, item.valuef.Value(), item.valuef.count);
}

COut& COut::Print(Binaryf item) {
  return TPrintBinary<COut>(*this, item.valuef.Value(), item.valuef.count);
}

COut& COut::Print(Centerf item) {
  SIW utf_format = ::_::TypeTextFormat(item.valuef.item.Type());
#if USING_UTF8 == YES
  if (utf_format == 1) {
    const CH1* start = reinterpret_cast<const CH1*>(item.valuef.item.Ptr());
    return ::_::TPrintCenter<::_::COut, CH1>(*this, start, item.valuef.count);
  }
#endif
#if USING_UTF16 == YES
  if (utf_format == 2) {
    const CH2* start = reinterpret_cast<const CH2*>(item.valuef.item.Ptr());
    return ::_::TPrintCenter<::_::COut, CH2>(*this, start, item.valuef.count);
  }
#endif
#if USING_UTF32 == YES
  if (utf_format == 4) {
    const CH4* start = reinterpret_cast<const CH4*>(item.valuef.item.Ptr());
    return ::_::TPrintCenter<::_::COut, CH4>(*this, start, item.valuef.count);
  }
#endif
  return *this;
}

COut& COut::Print(Rightf item) {
  SIW utf_format = ::_::TypeTextFormat(item.valuef.item.Type());
#if USING_UTF8 == YES
  if (utf_format == 1) {
    const CH1* start = reinterpret_cast<const CH1*>(item.valuef.item.Ptr());
    return ::_::TPrintRight<::_::COut, CH1>(*this, start, item.valuef.count);
  }
#endif
#if USING_UTF16 == YES
  if (utf_format == 2) {
    const CH2* start = reinterpret_cast<const CH2*>(item.valuef.item.Ptr());
    return ::_::TPrintRight<::_::COut, CH2>(*this, start, item.valuef.count);
  }
#endif
#if USING_UTF32 == YES
  if (utf_format == 4) {
    const CH4* start = reinterpret_cast<const CH4*>(item.valuef.item.Ptr());
    return ::_::TPrintRight<::_::COut, CH4>(*this, start, item.valuef.count);
  }
#endif
  return *this;
}

COut& COut::Print(Linef item) {
  SIW utf_format = ::_::TypeTextFormat(item.valuef.item.Type());
#if USING_UTF8 == YES
  if (utf_format == 1) {
    const CH1* start = reinterpret_cast<const CH1*>(item.valuef.item.Ptr());
    ::_::TPrintLinef<::_::COut, CH1>(*this, start, item.valuef.count);
    return *this;
  }
#endif
#if USING_UTF16 == YES
  if (utf_format == 2) {
    const CH2* start = reinterpret_cast<const CH2*>(item.valuef.item.Ptr());
    ::_::TPrintLinef<::_::COut, CH2>(*this, start, item.valuef.count);
    return *this;
  }
#endif
#if USING_UTF32 == YES
  if (utf_format == 4) {
    const CH4* start = reinterpret_cast<const CH4*>(item.valuef.item.Ptr());
    ::_::TPrintLinef<::_::COut, CH4>(*this, start, item.valuef.count);
    return *this;
  }
#endif
  return *this;
}

COut& COut::Print(Headingf item) {
  SIW utf_format = ::_::TypeTextFormat(item.caption.item.Type());
#if USING_UTF8 == YES
  if (utf_format == 1) {
    const CH1* caption = reinterpret_cast<const CH1*>(item.caption.item.Ptr());
    return ::_::TPrintHeadingf<::_::COut, CH1>(*this, caption, item.style,
                                               item.caption.count,
                                               item.caption2, item.caption3);
  }
#endif
#if USING_UTF16 == YES
  if (utf_format == 2) {
    const CH2* caption = reinterpret_cast<const CH2*>(item.caption.item.Ptr());
    return ::_::TPrintHeadingf<::_::COut, CH2>(*this, caption, item.style,
                                               item.caption.count,
                                               item.caption2, item.caption3);
  }
#endif
#if USING_UTF32 == YES
  if (utf_format == 3) {
    const CH4* caption = reinterpret_cast<const CH4*>(item.caption.item.Ptr());
    return ::_::TPrintHeadingf<::_::COut, CH4>(*this, caption, item.style,
                                               item.caption.count,
                                               item.caption2, item.caption3);
  }
#endif
  return *this;
}

COut& COut::Print(Indentf item) {
  return ::_::TPrintIndent<::_::COut>(*this, item.indent_count);
}

COut& COut::Print(Charsf item) {
  SIW utf_format = ::_::TypeTextFormat(item.valuef.item.Type());
#if USING_UTF8 == YES
  if (utf_format == 1) {
    const CH1* start = reinterpret_cast<const CH1*>(item.valuef.item.Ptr());
    return ::_::TPrintChars<::_::COut, CH1>(*this, start, item.valuef.count);
  }
#endif
#if USING_UTF16 == YES
  if (utf_format == 2) {
    const CH2* start = reinterpret_cast<const CH2*>(item.valuef.item.Ptr());
    return ::_::TPrintChars<::_::COut, CH2>(*this, start, item.valuef.count);
  }
#endif
#if USING_UTF32 == YES
  if (utf_format == 4) {
    const CH4* start = reinterpret_cast<const CH4*>(item.valuef.item.Ptr());
    return ::_::TPrintChars<::_::COut, CH4>(*this, start, item.valuef.count);
  }
#endif
  return *this;
}

COut& COut::NL() { return Print('\n'); }
COut& COut::NL(CH1 item) {
  NL();
  return Print(item);
}
COut& COut::NL(const CH1* item) {
  NL();
  return Print(item);
}
#if USING_UTF16 == YES
COut& COut::NL(CH2 item) {
  NL();
  return Print(item);
}
COut& COut::NL(const CH2* item) {
  NL();
  return Print(item);
}
#endif
#if USING_UTF32 == YES
COut& COut::NL(CH4 item) {
  NL();
  return Print(item);
}
COut& COut::NL(const CH4* item) {
  NL();
  return Print(item);
}
#endif
COut& COut::NL(SI4 item) {
  NL();
  return Print(item);
}
COut& COut::NL(UI4 item) {
  NL();
  return Print(item);
}
COut& COut::NL(SI8 item) {
  NL();
  return Print(item);
}
COut& COut::NL(UI8 item) {
  NL();
  return Print(item);
}
#if USING_FP4 == YES
COut& COut::NL(FP4 item) {
  NL();
  return Print(item);
}
#endif
#if USING_FP8 == YES
COut& COut::NL(FP8 item) {
  NL();
  return Print(item);
}
#endif

COut& COut::Hex(const void* item) { return TPrintHex<COut>(*this, item); }
COut& COut::Hex(const void* item, SIW size) {
  return TPrintHex<COut>(*this, item, size);
}
COut& COut::Hex(const void* item, const void* item_stop) {
  return TPrintHex<COut>(*this, item, item_stop);
}
COut& COut::Hex(SI1 item) { return TPrintHex<COut, SI1, UI1>(*this, item); }
COut& COut::Hex(UI1 item) { return TPrintHex<COut, UI1>(*this, item); }
COut& COut::Hex(SI2 item) { return TPrintHex<COut, SI2, UI2>(*this, item); }
COut& COut::Hex(UI2 item) { return TPrintHex<COut, UI2>(*this, item); }
COut& COut::Hex(SI4 item) { return TPrintHex<COut, SI4, UI4>(*this, item); }
COut& COut::Hex(UI4 item) { return TPrintHex<COut, UI4>(*this, item); }
COut& COut::Hex(SI8 item) { return TPrintHex<COut, SI8, UI8>(*this, item); }
COut& COut::Hex(UI8 item) { return TPrintHex<COut, UI8>(*this, item); }
#if USING_FP4 == YES
COut& COut::Hex(FP4 item) { return TPrintHex<COut>(*this, item); }
#endif
#if USING_FP8 == YES
COut& COut::Hex(FP8 item) { return TPrintHex<COut>(*this, item); }
#endif

/* Stores the given item to the buffer and store the size. */
COut& COut::Binary(const void* item) { return TPrintBinary<COut>(*this, item); }
COut& COut::Binary(const void* item, SIW size) {
  return TPrintBinary<COut>(*this, item, size);
}
COut& COut::Binary(const void* start, const void* stop) {
  return TPrintBinary<COut>(
      *this, start,
      reinterpret_cast<const CH1*>(stop) - reinterpret_cast<const CH1*>(start));
}
COut& COut::Binary(SI1 item) {
  return TPrintBinary<COut, SI1, UI1>(*this, item);
}
COut& COut::Binary(UI1 item) { return TPrintBinary<COut, UI1>(*this, item); }
COut& COut::Binary(SI2 item) {
  return TPrintBinary<COut, SI2, UI2>(*this, item);
}
COut& COut::Binary(UI2 item) { return TPrintBinary<COut, UI2>(*this, item); }
COut& COut::Binary(SI4 item) {
  return TPrintBinary<COut, SI4, UI4>(*this, item);
}
COut& COut::Binary(UI4 item) { return TPrintBinary<COut, UI4>(*this, item); }
COut& COut::Binary(SI8 item) {
  return TPrintBinary<COut, SI8, UI8>(*this, item);
}
COut& COut::Binary(UI8 item) { return TPrintBinary<COut, UI8>(*this, item); }
#if USING_FP4 == YES
COut& COut::Binary(FP4 item) { return TPrintBinary<COut>(*this, item); }
#endif
#if USING_FP8 == YES
COut& COut::Binary(FP8 item) { return TPrintBinary<COut>(*this, item); }
#endif
SIN COut::PrintAndCount(const CH1* string) {
  return TPrintAndCount<COut, CH1>(*this, string);
}
#if USING_UTF16 == YES
SIN COut::PrintAndCount(const CH2* string) {
  return TPrintAndCount<COut, CH2>(*this, string);
}
#endif
#if USING_UTF32 == YES
SIN COut::PrintAndCount(const CH4* string) {
  return TPrintAndCount<COut, CH4>(*this, string);
}
#endif

COut CPrint() { return COut(); }

}  // namespace _

::_::COut& operator<<(::_::COut& o, CH1 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, const CH1* item) { return o.Print(item); }

#if USING_UTF16 == YES
::_::COut& operator<<(::_::COut& o, CH2 item) { return o.Print(item); }
::_::COut& operator<<(::_::COut& o, const CH2* item) { return o.Print(item); }
#endif
#if USING_UTF32 == YES
::_::COut& operator<<(::_::COut& o, CH4 item) { return o.Print(item); }
::_::COut& operator<<(::_::COut& o, const CH4* item) { return o.Print(item); }
#endif

::_::COut& operator<<(::_::COut& o, SI4 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, UI4 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, SI8 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, UI8 item) { return o.Print(item); }

#if USING_FP4 == YES
::_::COut& operator<<(::_::COut& o, FP4 item) { return o.Print(item); }
#endif

#if USING_FP8 == YES
::_::COut& operator<<(::_::COut& o, FP8 item) { return o.Print(item); }
#endif

::_::COut& operator<<(::_::COut& o, ::_::Hexf item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Binaryf item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Centerf item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Rightf item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Linef item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Headingf item) {
  return o.Print(item);
}

::_::COut& operator<<(::_::COut& o, ::_::Indentf item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Charsf item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::COut& item) { return o; }

#endif
