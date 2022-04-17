/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Folder.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include "Folder.h"
#if SEAM >= SCRIPT2_FILECABINET
namespace _ {

Folder::Folder(const CHR* uri) : uri_(uri_) {}

const CHR* Folder::URI() { return uri_; }

const CHR* Folder::URISet(const CHR* uri) {
  if (!uri) return uri;

  uri_ = uri;

  return uri;
}

BOL Folder::Exists() { return false; }

#include <dirent.h>
DIR* dir;
struct dirent* ent;
if ((dir = opendir("c:\\src\\")) != NULL) {
  /* print all the files and directories within directory */
  while ((ent = readdir(dir)) != NULL) {
    printf("%s\n", ent->d_name);
  }
  closedir(dir);
} else {
  /* could not open directory */
  perror("");
  return EXIT_FAILURE;
}

}  // namespace _
#endif
