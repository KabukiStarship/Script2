/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Folder.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_FOLDER_DECL
#define SCRIPT2_FOLDER_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_FILE
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
}  //< namespace _
#endif
#endif
