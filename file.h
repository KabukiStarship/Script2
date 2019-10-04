/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /file.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_FILE
#ifndef SCRIPT2_FILE_DEFINITIONS
#define SCRIPT2_FILE_DEFINITIONS
namespace _ {
/* A file in a filesystem. */
class File {
  const CHR* uri_;  // Uniform Resource Identifier.
  File(const CHR* uri);

  const CHR* URI();
  const CHR* URISet(const CHR* uri);
  BOL Exists();
  BOL IsOpen();
  SIN Open();
  void Close();
};

}  // namespace _
#endif
#endif
