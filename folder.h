/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /folder.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-9 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_FILECABINET
#ifndef SCRIPT2_FOLDER_DEFINITIONS
#define SCRIPT2_FOLDER_DEFINITIONS
namespace _ {

struct CFolder {
  const CHR* uri_;  // Uniform Resource Identifier.
};

/* A file in a filesystem. */
class AFolder {
 public:
  Folder(const CHR* uri);

  const CHR* URI();
  const CHR* URISet(const CHR* uri);
  BOL Exists();
};
}  // namespace _
#endif
#endif
