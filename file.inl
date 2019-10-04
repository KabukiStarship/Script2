/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /folder.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#include "file.h"
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

SIN File::Open() { return 0; }

void File::Close() {}
