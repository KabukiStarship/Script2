/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_lock.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#include "c_valuef.h"

namespace _ {

// Valuef::Valuef() {}
Valuef::Valuef(void* item, SIW count) : count(count), item(item) {}
Valuef::Valuef(const void* item, SIW count) : count(count), item(item) {}
#if USING_UTF8 == YES
Valuef::Valuef(CH1 item, SIW count) : count(count), item(item) {}
Valuef::Valuef(const CH1* item, SIW count) : count(count), item(item) {}
#endif
#if USING_UTF16 == YES
Valuef::Valuef(CH2 item, SIW count) : count(count), item(item) {}
Valuef::Valuef(const CH2* item, SIW count) : count(count), item(item) {}
#endif
#if USING_UTF32 == YES
Valuef::Valuef(CH4 item, SIW count) : count(count), item(item) {}
Valuef::Valuef(const CH4* item, SIW count) : count(count), item(item) {}
#endif
Valuef::Valuef(SI1 item, SIW count) : count(count), item(item) {}
Valuef::Valuef(UI1 item, SIW count) : count(count), item(item) {}
Valuef::Valuef(SI2 item, SIW count) : count(count), item(item) {}
Valuef::Valuef(UI2 item, SIW count) : count(count), item(item) {}
Valuef::Valuef(SI4 item, SIW count) : count(count), item(item) {}
Valuef::Valuef(UI4 item, SIW count) : count(count), item(item) {}
Valuef::Valuef(SI8 item, SIW count) : count(count), item(item) {}
Valuef::Valuef(UI8 item, SIW count) : count(count), item(item) {}
#if USING_FP4 == YES
Valuef::Valuef(FP4 item, SIW count) : count(count), item(item) {}
#endif
#if USING_FP8 == YES
Valuef::Valuef(FP8 item, SIW count) : count(count), item(item) {}
#endif

void* Valuef::Value() { return item.Value(); }

void* Valuef::Ptr() { return item.Ptr(); }

#if USING_UTF8 == YES
Centerf::Centerf(CH1 item, SIW count) : valuef(item, count) {}
Centerf::Centerf(const CH1* item, SIW count) : valuef(item, count) {}
#endif
#if USING_UTF16 == YES
Centerf::Centerf(CH2 item, SIW count) : valuef(item, count) {}
Centerf::Centerf(const CH2* item, SIW count) : valuef(item, count) {}
#endif
#if USING_UTF32 == YES
Centerf::Centerf(CH4 item, SIW count) : valuef(item, count) {}
Centerf::Centerf(const CH4* item, SIW count) : valuef(item, count) {}
#endif
Centerf::Centerf(SI4 item, SIW count) : valuef(item, count) {}
Centerf::Centerf(UI4 item, SIW count) : valuef(item, count) {}
Centerf::Centerf(SI8 item, SIW count) : valuef(item, count) {}
#if USING_FP4 == YES
Centerf::Centerf(FP4 item, SIW count) : valuef(item, count) {}
#endif
#if USING_FP8 == YES
Centerf::Centerf(FP8 item, SIW count) : valuef(item, count) {}
#endif
Centerf::Centerf(UI8 item, SIW count) : valuef(item, count) {}

Rightf::Rightf(CH1 item, SIW count) : valuef(item, count) {}
Rightf::Rightf(const CH1* item, SIW count) : valuef(item, count) {}
#if USING_UTF16 == YES
Rightf::Rightf(CH2 item, SIW count) : valuef(item, count) {}
Rightf::Rightf(const CH2* item, SIW count) : valuef(item, count) {}
#endif
#if USING_UTF32 == YES
Rightf::Rightf(CH4 item, SIW count) : valuef(item, count) {}
Rightf::Rightf(const CH4* item, SIW count) : valuef(item, count) {}
#endif
Rightf::Rightf(SI4 item, SIW count) : valuef(item, count) {}
Rightf::Rightf(UI4 item, SIW count) : valuef(item, count) {}
Rightf::Rightf(SI8 item, SIW count) : valuef(item, count) {}
Rightf::Rightf(UI8 item, SIW count) : valuef(item, count) {}
#if USING_FP4 == YES
Rightf::Rightf(FP4 item, SIW count) : valuef(item, count) {}
#endif
#if USING_FP8 == YES
Rightf::Rightf(FP8 item, SIW count) : valuef(item, count) {}
#endif

Linef::Linef(CH1 item, SIW count) : valuef(item, count) {}
Linef::Linef(const CH1* item, SIW count) : valuef(item, count) {}

Headingf::Headingf(const CH1* caption1, const CH1* style, SIW count,
                   const CH1* caption2, const CH1* caption3)
    : caption(caption1, count),
      style(style),
      caption2(caption2),
      caption3(caption3) {}

Charsf::Charsf(const void* start, const void* stop)
    : valuef(start, reinterpret_cast<const CH1*>(stop) -
                        reinterpret_cast<const CH1*>(start)) {}
Charsf::Charsf(const void* start, SIW count) : valuef(start, count) {}

#if USING_UTF16
Charsf::Charsf(const CH2* start, const CH2* stop)
    : valuef(start, stop - start) {}
Charsf::Charsf(const CH2* start, SIW count) : valuef(start, count) {}
#endif
#if USING_UTF32
Charsf::Charsf(const CH4* start, const CH4* stop)
    : valuef(start, stop - start) {}
Charsf::Charsf(const CH4* start, SIW count) : valuef(start, count) {}
#endif

Hexf::Hexf(const void* begin) : valuef(begin, -sizeof(const void*)) {}
Hexf::Hexf(const void* begin, SIW size) : valuef(begin, size) {}
Hexf::Hexf(SI1 item) : valuef(item, -sizeof(SI1)) {}
Hexf::Hexf(UI1 item) : valuef(item, -sizeof(UI1)) {}
Hexf::Hexf(SI2 item) : valuef(item, -sizeof(SI2)) {}
Hexf::Hexf(UI2 item) : valuef(item, -sizeof(UI2)) {}
Hexf::Hexf(SI4 item) : valuef(item, -sizeof(SI4)) {}
Hexf::Hexf(UI4 item) : valuef(item, -sizeof(UI4)) {}
Hexf::Hexf(SI8 item) : valuef(item, -sizeof(SI8)) {}
Hexf::Hexf(UI8 item) : valuef(item, -sizeof(UI8)) {}
#if USING_FP8 == YES
Hexf::Hexf(FP4 item) : valuef(item, -sizeof(FP4)) {}
#endif
#if USING_FP8 == YES
Hexf::Hexf(FP8 item) : valuef(item, -sizeof(FP8)) {}
#endif

Binaryf::Binaryf(const void* begin) : valuef(begin, -sizeof(const void*)) {}
Binaryf::Binaryf(const void* begin, SIW size) : valuef(begin, size) {}
Binaryf::Binaryf(SI1 item) : valuef(item, -sizeof(SI1)) {}
Binaryf::Binaryf(UI1 item) : valuef(item, -sizeof(UI1)) {}
Binaryf::Binaryf(SI2 item) : valuef(item, -sizeof(SI2)) {}
Binaryf::Binaryf(UI2 item) : valuef(item, -sizeof(UI2)) {}
Binaryf::Binaryf(SI4 item) : valuef(item, -sizeof(SI4)) {}
Binaryf::Binaryf(UI4 item) : valuef(item, -sizeof(UI4)) {}
Binaryf::Binaryf(SI8 item) : valuef(item, -sizeof(SI8)) {}
Binaryf::Binaryf(UI8 item) : valuef(item, -sizeof(UI8)) {}
#if USING_FP8 == YES
Binaryf::Binaryf(FP4 item) : valuef(item, -sizeof(FP4)) {}
#endif
#if USING_FP8 == YES
Binaryf::Binaryf(FP8 item) : valuef(item, -sizeof(FP8)) {}
#endif

Indentf::Indentf(SIW indent_count) : indent_count(indent_count) {}

}  // namespace _
