/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /t_loom.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough
<<calemccollough.github.io>>; All right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_LOOM

#ifndef SCRIPT2_LOOM_TEMPLATES
#define SCRIPT2_LOOM_TEMPLATES

#include "t_stack.h"

#if SEAM == SCRIPT2_LOOM
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* An array of Strings.
 */
template <typename SIZ>
struct TLoom {
  SIZ size,             //< Size of the Loom in bytes.
      top;              //< Offset to the top of the string stack.
  TStack<SIZ> offsets;  //< A Stack of offsets to strands.
};

template <typename Char, typename SIZ>
constexpr SIZ TLoomCountMin() {
  return 8 / sizeof(SIZ);
}

template <typename Char, typename SIZ>
constexpr SIZ TLoomSizeMin() {
  enum {
    kCountMin = TLoomCountMin(),
    kSizeMin = sizeof(TLoom<SIZ>) + kCountMin * (sizeof(SIZ) + 2),
  };
  return kSizeMin;
}

template <typename Char, typename SIZ>
constexpr SIZ TLoomCountDefault() {
  return 32;
}

template <typename Char, typename SIZ>
constexpr SIZ TLoomSizeDefault() {
  return (32 * TLoomCountDefault<Char, SIZ>() * sizeof(Char)) &
         (sizeof(SIW) - 1);
}

template <typename Char, typename SIZ>
inline Char* TLoomStart(TLoom<SIZ>* loom, SIZ count_max) {
  SIZ* top = &TStackStart<SIZ, SIZ>(&loom->offsets)[count_max];
  return reinterpret_cast<Char*>(top);
}

template <typename Char, typename SIZ>
inline Char* TLoomStart(TLoom<SIZ>* loom) {
  return TLoomStart<Char, SIZ>(loom, loom->offsets.count_max);
}

template <typename Char, typename SIZ>
inline TLoom<SIZ>* TLoomInit(TLoom<SIZ>* loom, SIZ count_max) {
  A_ASSERT(loom);
  A_ASSERT((count_max >= TLoomCountMin<Char, SIZ>()));

  D_ARRAY_WIPE(&loom->top, loom->size - sizeof(SIZ));

  // count_max -= count_max & 3; // @todo Ensure the values are word-aligned.
  loom->top = TDelta<SIZ>(loom, TLoomStart<Char, SIZ>(loom, count_max));
  loom->offsets.count_max = count_max;
  loom->offsets.count = 0;
  return loom;
}

template <typename Char, typename SIZ>
Char* TLoomEnd(TLoom<SIZ>* loom) {
  SIW address = reinterpret_cast<SIW>(loom) + loom->size;
  return reinterpret_cast<Char*>(address);
}

template <typename Char, typename SIZ>
Char* TLoomStop(TLoom<SIZ>* loom) {
  SIW address = reinterpret_cast<SIW>(loom) + loom->top;
  return reinterpret_cast<Char*>(address);
}

/* Gets the element at the given index. */
template <typename Char, typename SIZ>
Char* TLoomGet(TLoom<SIZ>* loom, SIZ index) {
  D_ASSERT(loom);
  if (index < 0 || index >= loom->offsets.count) return nullptr;
  return TPtr<Char>(loom, TStackStart<SIZ, SIZ>(&loom->offsets)[index]);
}

template <typename Char, typename SIZ, typename Printer>
Printer& TLoomPrint(Printer& o, TLoom<SIZ>* loom) {
  SIZ count = loom->offsets.count;
  o << "\nLoom<SI" << (CH1)('0' + sizeof(SIZ)) << "> size:" << loom->size
    << " top:" << loom->top << " stack_size:" << loom->offsets.count_max
    << " count:" << count;
  SIZ* offsets = TStackStart<SIZ, SIZ>(&loom->offsets);
  for (SIZ i = 0; i < count; ++i)
    o << '\n'
      << i << ".) \"" << TLoomGet<Char, SIZ>(loom, i) << "\":" << offsets[i];
  D_COUT(Linef('-') << Charsf(loom, loom->size));
  return o << '\n';
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template <typename Char, typename SIZ>
SIZ TLoomAdd(TLoom<SIZ>* loom, const Char* string) {
  A_ASSERT(loom);
  A_ASSERT(string);

  if (loom->offsets.count >= loom->offsets.count_max) return -1;
  Char* cursor = TPtr<Char>(loom, loom->top);
  cursor = TSPrintString<Char>(cursor, TLoomEnd<Char, SIZ>(loom), string);
  if (!cursor) return -1;
  SIZ index = TStackPush<SIZ, SIZ>(&loom->offsets, loom->top);
  loom->top = TDelta<SIZ>(loom, cursor + 1);
  return index;
}

template <typename Char, typename SIZ>
SIZ TLoomCharCount(TLoom<SIZ>* loom) {
  return (SIZ)(TLoomEnd<Char, SIZ>(loom) - TLoomStart<Char, SIZ>(loom));
}
template <typename Char = SI4, typename SIZ = SIN>
BOL TLoomWrite(TLoom<SIZ>* destination, TLoom<SIZ>* soure) {
  return true;
}

/* Doubles the size and count_max of the loom.
@return Returns nil if the size is greater than the amount of memory that
can fit in type SIW, the unaltered socket pointer if the Stack has grown to the
size upper bounds, or a new dynamically allocated socket upon failure. */
template <typename Char = SI4, typename SIZ = SIN>
BOL TLoomGrow(Autoject& obj) {
  D_COUT("\n\nGrowing Loom...");
  TLoom<SIZ>* loom = reinterpret_cast<TLoom<SIZ>*>(obj.origin);
  A_ASSERT(loom);
  SIZ size = loom->size;
  if (!TCanGrow<SIZ>(size)) return false;
  SIZ count_max = loom->offsets.count_max;
  if (!TCanGrow<SIZ>(count_max)) return false;

  size = size << 1;
  count_max = count_max << 1;

  D_COUT(" new size:" << size << " count_max:" << count_max);

#if D_THIS
  CPrint("\n\nBefore:\n");
  TLoomPrint<Char, SIZ, COut>(COut().Star(), loom);
  D_COUT(Charsf(loom, loom->size));
#endif

  UIW* new_begin = obj.socket_factory(nullptr, size);
  D_ARRAY_WIPE(new_begin, size);
  TLoom<SIZ>* other = reinterpret_cast<TLoom<SIZ>*>(new_begin);

  // Copy the offsets and offset them and the loom->top.
  SIZ extra_header_space = (count_max >> 1) * sizeof(SIZ);
  SIZ count = loom->offsets.count,  //
      top = loom->top;
  other->size = size;
  other->top = top + extra_header_space;
  other->offsets.count_max = count_max;
  other->offsets.count = count;
  SIZ *loom_offsets = TStackStart<SIZ, SIZ>(&loom->offsets),
      *other_offsets = TStackStart<SIZ, SIZ>(&other->offsets);
  for (SIZ i = 0; i < count; ++i)
    other_offsets[i] = loom_offsets[i] + extra_header_space;

  // Copy the Strings.
  Char* start = TLoomStart<Char, SIZ>(loom);
  SIZ Strings_size_bytes = TDelta<SIZ>(start, TPtr<>(loom, top));
  Char* other_start = TLoomStart<Char, SIZ>(other);
  if (Strings_size_bytes)
    ArrayCopy(other_start, Strings_size_bytes, start, Strings_size_bytes);
#if D_THIS
  CPrint("\n\nAfter:\n");
  TLoomPrint<Char, SIZ, COut>(COut().Star(), other);
  D_COUT(Charsf(other, other->size));
#endif

  Delete(obj);
  obj.origin = new_begin;
  return true;
}

/* Adds a string to the end of the Loom, auto-growing if neccissary.
@return The index upon success or -1 if the obj can't grow anymore. */
template <typename Char, typename SIZ, typename BUF>
SIZ TLoomAdd(AArray<Char, SIZ, BUF>& obj, const Char* item) {
  if (!item) return -1;
  D_COUT("\nAdding:\"" << item << '\"');
  SIZ result = TLoomAdd<Char, SIZ>(obj.BeginAs<TLoom<SIZ>>(), item);
  while (result < 0) {
    if (!TLoomGrow<Char, SIZ>(obj.AJT())) {
      D_COUT("\n\nFailed to grow.\n\n");
      return -1;
    }
    result = TLoomAdd<Char, SIZ>(obj.BeginAs<TLoom<SIZ>>(), item);
  }
  return result;
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template <typename Char, typename SIZ>
Char* TLoomPop(TLoom<SIZ>* loom) {
  if (loom->offsets.count == 0) return nullptr;
  SIZ offset = TStackPop<SIZ, SIZ>(loom->offsets), top = loom->top;
  loom->top = offset;
  return reinterpret_cast<Char*>(reinterpret_cast<SIW>(loom) + offset);
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template <typename Char, typename SIZ>
SIZ TLoomRemove(TLoom<SIZ>* loom, SIZ index) {
  SIZ count = loom->offsets.count;
  if (index == count) return TLoomPop<Char, SIZ>(loom);
  if (index < 0 || index > count) return -1;

  SIZ* offsets = TStackStart<SIZ, SIZ>(loom->offsets);
  SIZ offset = offsets[index],        //
      offset_b = offsets[index + 1],  //
      delta = offset_b - offset;      //

  TStackRemove<SIZ, SIZ>(loom->offsets, index);

  // ArrayShiftDown(reinterpret_cast<CH1*>(loom) + offset, delta);
  return index;
}

/* Searches for the given string in the loom.
@return -1 if the loom doesn't contain the string or the index if it does. */
template <typename Char, typename SIZ>
SIZ TLoomFind(TLoom<SIZ>* loom, const Char* string) {
  D_ASSERT(loom);
  D_ASSERT(string);
  SIZ* offsets = TStackStart<SIZ, SIZ>(&loom->offsets);
  for (SIZ i = 0; i < loom->offsets.count; ++i) {
    SIZ offset = offsets[i];
    Char* other = reinterpret_cast<Char*>(reinterpret_cast<UIW>(loom) + offset);
    if (!TSTRCompare<Char>(string, other)) return i;
  }
  return -1;
}

/* An ASCII Loom Autoject. */
template <typename Char = CHR, typename SIZ = SIN, SIZ kSize_ = 512,
          typename BUF = TUIB<kSize_, Char, TStrand<SIN>>>
class ALoom {
  AArray<Char, SIZ, BUF> obj_;  //< An Auto-Array object.
 public:
  enum { kCountDefault = kSize_ / 16 };
  /* Constructs a Loom. */
  ALoom(SIZ count_max = kCountDefault) {
    TLoomInit<Char, SIZ>(OBJ(), count_max);
  }

  /* Constructs a Loom subclass.
  @param factory SocketFactory to call when the Strand overflows. */
  ALoom(SocketFactory socket_factory, SIZ count = kCountDefault)
      : obj_(socket_factory) {
    TLoomInit<Char, SIZ>(OBJ(), count);
  }

  /* Constructs a Loom subclass.
  @param factory SocketFactory to call when the Strand overflows. */
  ALoom(SocketFactory socket_factory, SIZ size = TLoomSizeDefault<Char, SIZ>(),
        SIZ count = TLoomCountDefault<Char, SIZ>())
      : obj_(socket_factory) {
    TLoomInit<Char, SIZ>(OBJ(), count);
  }

  inline SIZ Size() { return obj_.Size(); }

  /* Deep copies the given string into the Loom.
  @return The index of the string in the Loom. */
  inline SIZ Add(const Char* string) {
    return TLoomAdd<Char, SIZ, BUF>(AJT(), string);
  }

  /* Removes the string at the given index from the Loom. */
  inline SIZ Remove(SIZ index) { return TLoomRemove<Char, SIZ>(OBJ(), index); }

  /* Gets the string at the given index. */
  inline Char* Get(SIZ index) { return TLoomGet<Char, SIZ>(OBJ(), index); }

  /* Searches for the given string.
  @return -1 if the Loom doesn't contain the string or the index if it does.
*/
  inline SIZ Find(const Char* string) {
    return TLoomFind<Char, SIZ>(OBJ(), string);
  }

  /* Gets the ASCII Object. */
  inline TLoom<SIZ>* OBJ() { return obj_.BeginAs<TLoom<SIZ>>(); }

  /* Gets the Auto-Array. */
  inline AArray<Char, SIZ, BUF>& AJT() { return obj_; }

  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    TLoomPrint<Char, SIZ, Printer>(o, OBJ());
    return o;
  }

  inline void COut() { PrintTo<_::COut>(_::COut().Star()); }
};
}  // namespace _

#endif
#endif
