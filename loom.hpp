/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /loom.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_LOOM
#ifndef SCRIPT2_LOOM_TEMPLATES
#define SCRIPT2_LOOM_TEMPLATES
#include "stack.hpp"
#if SEAM == SCRIPT2_LOOM
#include "_debug.inl"
#else
#include "_release.inl"
#endif
namespace _ {
/* @ingroup Loom
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./spec/data/map_types/loom.md */

#define TPARAMS CHT, SIZ

/* An array of Strings.
 */
template <typename SIZ>
struct TLoom {
  SIZ size,         //< Size of the Loom in bytes.
      top;          //< Offset to the top of the string stack.
  TStack<SIZ> map;  //< A Stack of offsets to strands.
};

template <typename CHT = CHR, typename SIZ = SIN>
constexpr SIZ cLoomCountMin() {
  return 8 / sizeof(SIZ);
}

template <typename CHT = CHR, typename SIZ = SIN>
constexpr SIZ cLoomSizeMin() {
  enum {
    cCountMin = cLoomCountMin(),
    cSizeMin = sizeof(TLoom<SIZ>) + cCountMin * (sizeof(SIZ) + 2),
  };
  return cSizeMin;
}

template <typename CHT = CHR, typename SIZ = SIN>
constexpr SIZ cLoomCountDefault() {
  return 32;
}

template <typename CHT = CHR, typename SIZ = SIN>
constexpr SIZ cLoomSizeDefault() {
  return (32 * cLoomCountDefault<TPARAMS>() * sizeof(CHT)) & (sizeof(SIW) - 1);
}

template <typename CHT = CHR, typename SIZ = SIN>
inline CHT* TLoomStart(TLoom<SIZ>* loom, SIZ count_max) {
  SIZ* top = &TStackStart<SIZ, SIZ>(&loom->map)[count_max];
  return reinterpret_cast<CHT*>(top);
}

template <typename CHT = CHR, typename SIZ = SIN>
inline CHT* TLoomStart(TLoom<SIZ>* loom) {
  return TLoomStart<TPARAMS>(loom, loom->map.count_max);
}

template <typename CHT = CHR, typename SIZ = SIN>
inline TLoom<SIZ>* TLoomInit(TLoom<SIZ>* loom, SIZ count_max) {
  A_ASSERT(loom);
  A_ASSERT((count_max >= cLoomCountMin<TPARAMS>()));

  D_ARRAY_WIPE(&loom->top, loom->size - sizeof(SIZ));

  // count_max -= count_max & 3; // @todo Ensure the values are word-aligned.
  loom->top = TDelta<SIZ>(loom, TLoomStart<TPARAMS>(loom, count_max));
  loom->map.count_max = count_max;
  loom->map.count = 0;
  return loom;
}

template <typename CHT = CHR, typename SIZ = SIN>
CHT* TLoomEnd(TLoom<SIZ>* loom) {
  SIW address = reinterpret_cast<SIW>(loom) + loom->size;
  return reinterpret_cast<CHT*>(address);
}

template <typename CHT = CHR, typename SIZ = SIN>
CHT* TLoomStop(TLoom<SIZ>* loom) {
  SIW address = reinterpret_cast<SIW>(loom) + loom->top;
  return reinterpret_cast<CHT*>(address);
}

/* Gets the element at the given index. */
template <typename CHT = CHR, typename SIZ = SIN>
CHT* TLoomGet(TLoom<SIZ>* loom, SIZ index) {
  D_ASSERT(loom);
  if (index < 0 || index >= loom->map.count) return nullptr;
  return TPtr<CHT>(loom, TStackStart<SIZ, SIZ>(&loom->map)[index]);
}

template <typename CHT = CHR, typename SIZ = SIN, typename Printer>
Printer& TLoomPrint(Printer& o, TLoom<SIZ>* loom) {
  SIZ count = loom->map.count;
  o << "\nLoom<SI" << CH1('0' + sizeof(SIZ)) << "> size:" << loom->size
    << " top:" << loom->top << " stack_size:" << loom->map.count_max
    << " count:" << count;
  SIZ* offsets = TStackStart<SIZ, SIZ>(&loom->map);
  for (SIZ i = 0; i < count; ++i)
    o << '\n'
      << i << ".) \"" << TLoomGet<TPARAMS>(loom, i) << "\":" << offsets[i];
  D_COUT(Linef('-') << Charsf(loom, loom->size));
  return o << '\n';
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template <typename CHT = CHR, typename SIZ = SIN>
SIZ TLoomInsert(TLoom<SIZ>* loom, const CHT* string, SIZ index = cPush) {
  A_ASSERT(loom);
  if (!string || loom->map.count >= loom->map.count_max) return -1;
  if (index < 0) {
    auto count = loom->map.count;
    index = count;
    if (index < 0) index = 0;
  }
  CHT* cursor = TPtr<CHT>(loom, loom->top);
  cursor = TSPrintString<CHT>(cursor, TLoomEnd<TPARAMS>(loom), string);
  if (!cursor) return -1;
  if (index < count - 1) {
    SIZ index = TStackInsert<SIZ, SIZ>(&loom->map, loom->top, index);
  }
  SIZ index = TStackPush<SIZ, SIZ>(&loom->map, loom->top);
  loom->top = TDelta<SIZ>(loom, cursor + 1);
  return index;
}

template <typename CHT = CHR, typename SIZ = SIN>
SIZ TLoomCharCount(TLoom<SIZ>* loom) {
  return (SIZ)(TLoomEnd<TPARAMS>(loom) - TLoomStart<TPARAMS>(loom));
}
template <typename CHT = CHR, typename SIZ = SIN>
BOL TLoomWrite(TLoom<SIZ>* destination, TLoom<SIZ>* soure) {
  return true;
}

/* Clones the loom to a pre-allocated Socket. */
template <typename CHT = CHR, typename SIZ = SIN>
BOL TLoomClone(TLoom<SIZ>* loom, TLoom<SIZ>* other, SIZ count_max) {
  SIZ extra_header_space = (count_max >> 1) * sizeof(SIZ);
  SIZ count = loom->map.count, top = loom->top;
  other->size = size;
  other->top = top + extra_header_space;
  other->map.count_max = count_max;
  other->map.count = count;
  SIZ *loom_offsets = TStackStart<SIZ, SIZ>(&loom->map),
      *other_offsets = TStackStart<SIZ, SIZ>(&other->map);
  for (SIZ i = 0; i < count; ++i)
    other_offsets[i] = loom_offsets[i] + extra_header_space;

  // Copy the Strings.
  CHT* start = TLoomStart<TPARAMS>(loom);
  SIZ Strings_size_bytes = TDelta<SIZ>(start, TPtr<>(loom, top));
  CHT* other_start = TLoomStart<TPARAMS>(other);
  if (Strings_size_bytes)
    ArrayCopy(other_start, Strings_size_bytes, start, Strings_size_bytes);
}

/* Doubles the size and count_max of the loom.
@return Returns nil if the size is greater than the amount of memory that
can fit in type SIW, the unaltered socket pointer if the Stack has grown to the
size upper bounds, or a new dynamically allocated socket upon failure. */
template <typename CHT = CHR, typename SIZ = SIN>
BOL TLoomGrow(Autoject& obj) {
  D_COUT("\n\nGrowing Loom...");
  auto loom = reinterpret_cast<TLoom<SIZ>*>(obj.origin);
  A_ASSERT(loom);
  SIZ size = loom->size;
  if (!TCanGrow<SIZ>(size)) return false;
  SIZ count_max = loom->map.count_max;
  if (!TCanGrow<SIZ>(count_max)) return false;

  size = size << 1;
  count_max = count_max << 1;

  D_COUT(" new size:" << size << " count_max:" << count_max);

#if D_THIS
  D_COUT("\n\nBefore:\n");
  TLoomPrint<TPARAMS, COut>(COut().Star(), loom);
  D_COUT(Charsf(loom, loom->size));
#endif

  UIW* new_begin = obj.socket_factory(nullptr, size);
  D_ARRAY_WIPE(new_begin, size);
  auto other = reinterpret_cast<TLoom<SIZ>*>(new_begin);

  TLoomClone<TPARAMS>(other, loom, count_max);
#if D_THIS
  D_COUT("\n\nAfter:\n");
  TLoomPrint<TPARAMS, COut>(COut().Star(), other);
  D_COUT(Charsf(other, other->size));
#endif

  Delete(obj);
  obj.origin = new_begin;
  return true;
}

/* Adds a string to the end of the Loom, auto-growing if neccissary.
@return The index upon success or -1 if the obj can't grow anymore. */
template <typename CHT = CHR, typename SIZ = SIN, typename BUF>
SIZ TLoomInsert(AArray<TPARAMS, BUF>& obj, const CHT* item, SIZ index = cPush) {
  if (!item) return -1;
  D_COUT("\nAdding:\"" << item << '\"');
  SIZ result = TLoomInsert<TPARAMS>(obj.OriginAs<TLoom<SIZ>*>(), item, index);
  while (result < 0) {
    if (!TLoomGrow<TPARAMS>(obj.AJT())) {
      D_COUT("\n\nFailed to grow.\n\n");
      return -1;
    }
    result = TLoomInsert<TPARAMS>(obj.OriginAs<TLoom<SIZ>*>(), item, index);
  }
  return result;
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template <typename CHT = CHR, typename SIZ = SIN>
CHT* TLoomPop(TLoom<SIZ>* loom) {
  if (loom->map.count == 0) return nullptr;
  SIZ offset = TStackPop<SIZ, SIZ>(loom->map), top = loom->top;
  loom->top = offset;
  return reinterpret_cast<CHT*>(reinterpret_cast<SIW>(loom) + offset);
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template <typename CHT = CHR, typename SIZ = SIN>
SIZ TLoomRemove(TLoom<SIZ>* loom, SIZ index) {
  SIZ count = loom->map.count;
  if (index == count) return TLoomPop<TPARAMS>(loom);
  if (index < 0 || index > count) return -1;

  SIZ* offsets = TStackStart<SIZ, SIZ>(loom->map);
  SIZ offset = offsets[index],        //
      offset_b = offsets[index + 1],  //
      delta = offset_b - offset;      //

  TStackRemove<SIZ, SIZ>(loom->map, index);

  // ArrayShiftDown(reinterpret_cast<CH1*>(loom) + offset, delta);
  return index;
}

/* Searches for the given string in the loom.
@return -1 if the loom doesn't contain the string or the index if it does. */
template <typename CHT = CHR, typename SIZ = SIN>
SIZ TLoomFind(TLoom<SIZ>* loom, const CHT* string) {
  D_ASSERT(loom);
  D_ASSERT(string);
  SIZ* offsets = TStackStart<SIZ, SIZ>(&loom->map);
  for (SIZ i = 0; i < loom->map.count; ++i) {
    SIZ offset = offsets[i];
    CHT* other = reinterpret_cast<CHT*>(reinterpret_cast<UIW>(loom) + offset);
    if (!TSTRCompare<CHT>(string, other)) return i;
  }
  return -1;
}

/* An ASCII Loom Autoject. */
template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_ = 512,
          typename BUF = TUIB<cSize_, CHT, TStrand<SIN>>>
class ALoom {
  AArray<TPARAMS, BUF> obj_;  //< An Auto-Array object.
 public:
  enum { cCountDefault = cSize_ / 16 };
  /* Constructs a Loom. */
  ALoom(SIZ count_max = cCountDefault) {
    TLoomInit<TPARAMS>(This(), count_max);
  }

  /* Constructs a Loom subclass.
  @param factory SocketFactory to call when the Strand overflows. */
  ALoom(SocketFactory socket_factory, SIZ count = cCountDefault)
      : obj_(socket_factory) {
    TLoomInit<TPARAMS>(This(), count);
  }

  /* Constructs a Loom subclass.
  @param factory SocketFactory to call when the Strand overflows. */
  ALoom(SocketFactory socket_factory, SIZ size = cLoomSizeDefault<TPARAMS>(),
        SIZ count = cLoomCountDefault<TPARAMS>())
      : obj_(socket_factory) {
    TLoomInit<TPARAMS>(This(), count);
  }

  inline SIZ Size() { return obj_.Size(); }

  /* Deep copies the given string into the Loom.
  @return The index of the string in the Loom. */
  inline SIZ Insert(const CHT* string, SIZ index = cPush) {
    return TLoomInsert<TPARAMS, BUF>(AJT_ARY(), string, index);
  }

  /* Removes the string at the given index from the Loom. */
  inline SIZ Remove(SIZ index) { return TLoomRemove<TPARAMS>(This(), index); }

  /* Gets the string at the given index. */
  inline CHT* Get(SIZ index) { return TLoomGet<TPARAMS>(This(), index); }

  /* Searches for the given string.
  @return -1 if the Loom doesn't contain the string or the index if it does.
*/
  inline SIZ Find(const CHT* string) {
    return TLoomFind<TPARAMS>(This(), string);
  }

  /* Gets the ASCII Object. */
  inline TLoom<SIZ>* This() { return obj_.OriginAs<TLoom<SIZ>*>(); }

  /* Gets the Auto-Array. */
  inline Autoject AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array. */
  inline AArray<TPARAMS, BUF>& AJT_ARY() { return obj_; }

  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    TLoomPrint<TPARAMS, Printer>(o, This());
    return o;
  }

  inline void COut() { PrintTo<_::COut>(_::COut().Star()); }
};
}  // namespace _
#undef TPARAMS
#endif
#endif
