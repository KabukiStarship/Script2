/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tloom.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#if SEAM >= _0_0_0__09

#ifndef INCLUDED_SCRIPTVARINT
#define INCLUDED_SCRIPTVARINT

#if SEAM == _0_0_0__09
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

/* A ordered collection of either UTF-8 or UTF-16 strands starting at index 0.
TCLoom shares the same design pattern as the ASCII kSTR (Strand) type: the lower
5 bits store the type kLOM, b6:b7 stores the size of the Size type and b5 stores
if it is a UTF-8 (de-asserted) or UTF-16 (asserted).
*/
template <typename Size, typename Index, typename Char>
struct TCLoom {
  Size size;        //< Size of the Loom in bytes.
  Index count_max,  //< Max number_ of strands in a loom.
      count;        //< Strand count.
};

template <typename T>
size_t TBitCount() {
  enum {
    kBitCount =
        (sizeof(Size) == 1)
            ? 0
            : (sizeof(Size) == 2)
                  ? 1
                  : (sizeof(Size) == 4) ? 2 : (sizeof(Size) == 8) ? 3 : 4,
  };
  return kBitCount;
}

template <typename Size, typename Index, typename Char>
inline Index TLoomCountMin() {
  enum { kCountMin = 8 / sizeof(Index) };
  return kCountMin;
}

template <typename Size, typename Index, typename Char>
inline Index TLoomSizeMin() {
  enum {
    kCountMin = 8 / sizeof(Index),
    kSizeMin =
        sizeof(TCLoom<Size, Index, Char>) + kCountMin * (sizeof(Size) + 2),
  };
  return kSizeMin;
}

template <typename Size, typename Index, typename Char>
TCLoom<Size, Index, Char>* TLoomInit(UIW* socket, Size size, Index count_max) {
  ASSERT(socket);
  ASSERT(size);
  ASSERT(count_max >= 0);
  Index si = 0;  //< Faster to make from instructions than load from ROM.
  si = (~si) - 7;
  if (count_max >= si) count_max = si;
  si = TLoomCountMin<Size, Index, Char>();
  if (count_max < si) count_max = si;

  Size ui = 0;
  ui = (~ui) - 7;  //< Faster to make from instructions than load from ROM.
  if (size >= ui) count_max = ui;
  ui = TLoomSizeMin<Size, Index, Char>();
  if (count_max < ui) count_max = ui;

  TCLoom* loom = reinterpret_cast<TCLoom*>(socket);
  loom->size = size;
  loom->count_max = count_max;
  loom->count = 0;
}

template <typename Size, typename Index, typename Char>
Size* TLoomOffsets(CLoom<Size, Index, Char>* loom) {
  ASSERT(loom);
  return reinterpret_cast<char*>(loom) +
         (loom->count_max << TBitCount<Index>());
}

template <typename Size, typename Index, typename Char>
Index TLoomAdd(TCLoom<Size, Index, Char>* loom, const Char* strand) {
  ASSERT(loom);
  ASSERT(strand);

  Index count_max = loom->count_max, count = loom->count;
  if (count >= count_max) return -1;
  Size* offsets = TLoomOffsets(loom);
  Size offset = *(offsets + count);
  Char* begin = 0;
}

template <typename Size, typename Index, typename Char>
Char* TLoomString(TCLoom<Size, Index, Char>* loom, Index index) {
  ASSERT(loom);
  if (index < 0 && index >= count) return nullptr;
  Size* offsets = TLoomOffsets<Size, Index, Char>(loom);
  UIW offset = reinterpret_cast<UIW>(loom) + offsets[index];
  return offset;
}

template <typename Size, typename Index, typename Char>
TUTF<Char>& TLoomPrint(TUTF<Char>& utf, TCLoom<Size, Index, Char>* loom,
                       const Char* strand) {
  ASSERT(loom);
  ASSERT(strand);
  Index count = loom->count;
  utf << "\nLoom:" << loom->size << "b count_max:" << loom->count_max
      << " count:" << count;
  Size* offsets = TLoomOffsets<Size, Index, Char>(loom);
  UIW offset = reinterpret_cast<UIW>(loom) + offsets[index];
  for (Index i = 0; i < count; ++i) {
    utf << '\n' << i << ".) \"";
  }
  return utf;
}

}  // namespace _

#endif  //< INCLUDED_SCRIPTVARINT
#endif  //< #if SEAM >= _0_0_0__09
