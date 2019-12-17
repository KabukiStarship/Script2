/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /folder.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-9 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_config.h>
#include "file.h"
#if SEAM >= SCRIPT2_FILECABINET
using namespace _;

File::File(const CHR* uri) : uri_(uri_) {}

const CHR* File::URI() { return uri_; }

const CHR* File::URISet(const CHR* uri) {
  if (!uri) return uri;

  uri_ = uri;

  return uri;
}

BOL File::Exists() { return false; }

BOL File::IsOpen() { return false; }

ISN File::Open() { return 0; }

void File::Close() {}

_::File& operator<<(_::File& o, CHA item) { return o.Print(item); }
_::File& operator<<(_::File& o, const CHA* item) { return o.Print(item); }
#if USING_UTF16 == YES_0
_::File& operator<<(_::File& o, CHB item) { return o.Print(item); }
_::File& operator<<(_::File& o, const CHB* item) { return o.Print(item); }
#endif
#if USING_UTF32 == YES_0
_::File& operator<<(_::File& o, CHC item) { return o.Print(item); }
_::File& operator<<(_::File& o, const CHC* item) { return o.Print(item); }
#endif
_::File& operator<<(_::File& o, ISC item) { return o.Print(item); }
_::File& operator<<(_::File& o, IUC item) { return o.Print(item); }
_::File& operator<<(_::File& o, ISD item) { return o.Print(item); }
_::File& operator<<(_::File& o, IUD item) { return o.Print(item); }
#if USING_FPC == YES_0
_::File& operator<<(_::File& o, FPC item) { return o.Print(item); }
#endif
#if USING_FPD == YES_0
_::File& operator<<(_::File& o, FPD item) { return o.Print(item); }
#endif
_::File& operator<<(_::File& o, _::Hexf item) { return o.Print(item); }
_::File& operator<<(_::File& o, _::Binaryf item) { return o.Print(item); }
_::File& operator<<(_::File& o, _::Centerf item) { return o.Print(item); }
_::File& operator<<(_::File& o, _::Rightf item) { return o.Print(item); }
_::File& operator<<(_::File& o, _::Linef item) { return o.Print(item); }
_::File& operator<<(_::File& o, _::Headingf item) { return o.Print(item); }
_::File& operator<<(_::File& o, _::Indentf item) { return o.Print(item); }
_::File& operator<<(_::File& o, _::Charsf item) { return o.Print(item); }
_::File& operator<<(_::File& o, _::File item) { return o; }
#endif
#endif
