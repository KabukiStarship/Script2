/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /dic.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#if SEAM >= SCRIPT2_DIC

#ifndef SCRIPT2_DIC_CODE
#define SCRIPT2_DIC_CODE 1

#include "binary.h"
#include "typevalue.h"

#if SEAM >= SCRIPT2_BOOK
#include "_debug.inl"
#else
#include "_release.inl"
#endif

namespace _ {

/* A one-to-one map of Key-{Type-Value} tuples. */
template <typename Size, typename Offset, typename Index>
struct Dictionary {
  TTable<SIZ>* keys;
};

template <typename Size, typename Offset, typename Index>
constexpr Size cDicOverheadPerIndex() {
  return sizeof(2 * sizeof(Index) + sizeof(Offset) + sizeof(Size) + 3);
};

template <typename Size, typename Offset, typename Index>
constexpr Size cMinSizeDic(Index item_count) {
  return item_count *
         sizeof(2 * sizeof(Index) + sizeof(Offset) + sizeof(Size) + 3);
};

enum {
  cMaxNumMappingsDic2 = 255,                //< The number_ of pages in a Dic2.
  cMaxNumMappingsDic4 = 8 * 1024,           //< The number_ of pages in a Dic4.
  cMaxNumMappingsDic8 = 256 * 1024 * 1024,  //< The number_ of pages in a Dic8.
  cOverheadPerDic2Index = TDicOverheadPerIndex<UI1, UI2, UI2>(),
  cOverheadPerDic4Index = TDicOverheadPerIndex<UI2, UI2, UI4>(),
  cOverheadPerDic8Index = TDicOverheadPerIndex<UI4, UI4, UI8>(),
};

}  // namespace _

#endif
#endif
