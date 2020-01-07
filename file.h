/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /file.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_FILECABINET
#ifndef SCRIPT2_FILE_DEFINITIONS
#define SCRIPT2_FILE_DEFINITIONS
#include "stringf.hpp"
namespace _ {

/* A file in a filesystem. */
class File {
  const CHR* uri_;  // Uniform Resource Identifier.
  File(const CHR* uri);

  const CHR* URI();
  const CHR* URISet(const CHR* uri);
  BOL Exists();
  BOL IsOpen();
  ISN Open();
  void Close();
};

}  // namespace _
/* Prints the given item to the File. */
_::File& operator<<(_::File& o, CHA item);
_::File& operator<<(_::File& o, const CHA* item);

#if USING_UTF16 == YES_0
_::File& operator<<(_::File& o, CHB item);
_::File& operator<<(_::File& o, const CHB* item);
#endif
#if USING_UTF32 == YES_0
_::File& operator<<(_::File& o, CHC item);
_::File& operator<<(_::File& o, const CHC* item);
#endif
_::File& operator<<(_::File& o, ISC item);
_::File& operator<<(_::File& o, IUC item);
_::File& operator<<(_::File& o, ISD item);
_::File& operator<<(_::File& o, IUD item);
#if USING_FPC == YES_0
_::File& operator<<(_::File& o, FPC item);
#endif
#if USING_FPD == YES_0
_::File& operator<<(_::File& o, FPD item);
#endif
_::File& operator<<(_::File& o, _::Hexf item);
_::File& operator<<(_::File& o, _::Binaryf item);
_::File& operator<<(_::File& o, _::Centerf item);
_::File& operator<<(_::File& o, _::Rightf item);
_::File& operator<<(_::File& o, _::Linef item);
_::File& operator<<(_::File& o, _::Headingf item);
_::File& operator<<(_::File& o, _::Indentf item);
_::File& operator<<(_::File& o, _::Charsf item);
_::File& operator<<(_::File& o, _::File item);
#endif
#endif
