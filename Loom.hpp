/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Loom.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_LOOM_TEMPLATES
#define SCRIPT2_LOOM_TEMPLATES
#include <_Config.h>
#if SEAM >= SCRIPT2_LOOM
#include "Stack.hpp"
#include "TypeValue.hpp"
#if SEAM == SCRIPT2_LOOM
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
#define TARGS typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM
#define TPARAMS CHT, ISZ, ISY
namespace _ {
/* @ingroup Loom
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./spec/data/map_types/loom.md */

/* An array of Strings. */
template <typename ISZ = ISN, typename ISY = ISM>
struct TLoom {
  ISZ size,         //< Size of the Loom in bytes.
      top;          //< Offset to the top of the string stack.
  TStack<ISY> map;  //< A Stack of offsets to strings.
};

template <TARGS>
constexpr ISZ CLoomCountMin() {
  return 8 / sizeof(ISZ);
}

template <TARGS>
constexpr ISZ CLoomSizeMin() {
  enum {
    cCountMin = CLoomCountMin(),
    cSizeMin = sizeof(TLoom<ISZ, ISY>) + cCountMin * (sizeof(ISZ) + 2),
  };
  return cSizeMin;
}

template <TARGS>
constexpr ISZ CLoomCountDefault() {
  return 32;
}

template <TARGS>
constexpr ISZ CLoomSizeDefault() {
  return (32 * CLoomCountDefault<TPARAMS>() * sizeof(CHT)) & (sizeof(ISW) - 1);
}

template <TARGS>
inline CHT* TLoomStart(TLoom<ISZ, ISY>* loom, ISY count_max) {
  ISZ* top = &TStackStart<ISZ, ISY>(&loom->map)[count_max];
  return reinterpret_cast<CHT*>(top);
}

template <TARGS>
inline CHT* TLoomStart(TLoom<ISZ, ISY>* loom) {
  return TLoomStart<TPARAMS>(loom, loom->map.count_max);
}

/* Initializes the loom with the given count_max. */
template <TARGS>
inline TLoom<ISZ, ISY>* TLoomInit(TLoom<ISZ, ISY>* loom, ISY count_max) {
  A_ASSERT(loom);
  A_ASSERT(count_max >= CLoomCountMin<TPARAMS>());
  D_ARRAY_WIPE(&loom->top, loom->size - sizeof(ISZ));

  // count_max -= count_max & 3; // @todo Ensure the values are word-aligned.
  loom->top = TDelta<ISZ>(loom, TLoomStart<TPARAMS>(loom, count_max));
  loom->map.count_max = count_max;
  loom->map.count = 0;
  return loom;
}

template <TARGS>
CHT* TLoomEnd(TLoom<ISZ, ISY>* loom) {
  ISW address = reinterpret_cast<ISW>(loom) + loom->size;
  return reinterpret_cast<CHT*>(address);
}

template <TARGS>
CHT* TLoomStop(TLoom<ISZ, ISY>* loom) {
  ISW address = reinterpret_cast<ISW>(loom) + loom->top;
  return reinterpret_cast<CHT*>(address);
}

/* Gets the element at the given index. */
template <TARGS>
CHT* TLoomGet(TLoom<ISZ, ISY>* loom, ISY index) {
  D_ASSERT(loom);
  if (index < 0 || index >= loom->map.count) return nullptr;
  return TPtr<CHT>(loom, TStackStart<ISZ, ISY>(&loom->map)[index]);
}

template <typename Printer, TARGS>
Printer& TLoomPrint(Printer& o, TLoom<ISZ, ISY>* loom) {
  ISY count = loom->map.count;
  o << "\nLoom<IS" << CSizef<ISZ>() << "> size:" << loom->size
    << " top:" << loom->top << " stack_size:" << loom->map.count_max
    << " count:" << count;
  ISZ* offsets = TStackStart<ISZ, ISY>(&loom->map);
  for (ISY i = 0; i < count; ++i)
    o << '\n'
      << i << ".) \"" << TLoomGet<TPARAMS>(loom, i) << "\":" << offsets[i];
  return o << '\n';
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template <TARGS>
ISY TLoomInsert(TLoom<ISZ, ISY>* loom, const CHT* string, ISY index = cPush) {
  A_ASSERT(loom);
  if (!string || loom->map.count >= loom->map.count_max) return -1;
  ISY count = loom->map.count;
  D_ASSERT(count >= 0);
  CHT* cursor = nullptr;
  if (index < 0) {
    if (index == cAnywhere) {
      D_COUT("\n\nindex == cAnywhere\n\n");
      if (count <= 1) {
        index = count;
      } else {
        auto length = TSTRLength<CHT>(string);
        for (ISN i = 0; i < count; ++i) {
          if (i == count) {
            index = count;
            break;
          }
          cursor = TSTREnd<CHT>(TLoomGet<TPARAMS>(loom, i)) + 1;
          CHT* start_next_string = TLoomGet<TPARAMS>(loom, i + i);
          if (start_next_string - cursor > length) {
            index = i;
            break;
          }
          cursor = start_next_string;
        }
      }
      if (index != count) {
        index = TStackInsert<ISZ, ISY>(&loom->map, TDelta<ISZ>(loom, cursor), index);
        cursor = TSPrintString<CHT>(cursor, TLoomEnd<TPARAMS>(loom), string);
        return index;
      }
    }
  }
  cursor = TPtr<CHT>(loom, loom->top);
  cursor = TSPrintString<CHT>(cursor, TLoomEnd<TPARAMS>(loom), string);
  if (!cursor) return -1;

  index = TStackInsert<ISZ, ISY>(&loom->map, loom->top, index);
  loom->top = TDelta<ISZ>(loom, cursor + 1);
  return index;
}

template <TARGS>
ISZ TLoomCharCount(TLoom<ISZ, ISY>* loom) {
  return (ISZ)(TLoomEnd<TPARAMS>(loom) - TLoomStart<TPARAMS>(loom));
}
template <TARGS>
BOL TLoomWrite(TLoom<ISZ, ISY>* destination, TLoom<ISZ, ISY>* soure) {
  return true;
}

/* Clones the loom to the pre-allocated destination Socket. */
template <TARGS>
BOL TLoomClone(TLoom<ISZ, ISY>* loom, TLoom<ISZ, ISY>* destination,
               ISY count_max = loom->count_max, ISY count_additional = 0,
               ISY size = loom->size, ISY size_additional = 0) {
  if (!loom || !destination) return false;
  ISZ top = loom->top;
  ISY count = loom->map.count;
  destination->size = size + size_additional;
  destination->top = loom->top + (count_additional * sizeof(ISY));
  destination->map.count_max = count_max + count_additional;
  destination->map.count = count;
  ISZ *loom_offsets = TStackStart<ISZ, ISY>(&loom->map),
      *loom_offsets_end = loom_offsets + count_max + count_additional,
      *clone_offsets = TStackStart<ISZ, ISY>(&destination->map);

  if (!count_additional) {
    while (loom_offsets <= loom_offsets_end)
      *clone_offsets++ = (*loom_offsets++);
  } else {
    while (loom_offsets <= loom_offsets_end)
      *clone_offsets++ = (*loom_offsets++) + count_additional * sizeof(ISY);
  }

  // Copy the Strings.
  CHT* start = TLoomStart<TPARAMS>(loom);
  ISZ strings_size = TDelta<ISZ>(start, TPtr<>(loom, top));
  CHT* clone_start = TLoomStart<TPARAMS>(destination);
  if (strings_size) ArrayCopy(clone_start, strings_size, start, strings_size);
  return true;
}

/* Doubles the size and count_max of the loom.
@return Returns nil if the size is greater than the amount of memory that
can fit in type ISW, the unaltered socket pointer if the Stack has grown to
the size upper bounds, or a new dynamically allocated socket upon failure. */
template <TARGS>
BOL TLoomGrow(Autoject& obj) {
  D_COUT("\n\nGrowing Loom...");
  auto loom = TPtr<TLoom<ISZ, ISY>>(obj.origin);
  A_ASSERT(loom);
  ISZ size = loom->size;
  if (!TCanGrow<ISZ>(size)) return false;
  ISY count_max = loom->map.count_max;

  D_COUT(" new size:" << size << " count_max:" << count_max);

#if D_THIS
  D_COUT("\n\nBefore:\n");
  TLoomPrint<COut, TPARAMS>(COut().Star(), loom);
  D_COUT('\n' << Charsf(loom, loom->size));
#endif

  // @see RamFactory for documentation on how to create a new block of memory.
  IUW* growth = obj.socket_factory(nullptr, size << 1);
  D_ARRAY_WIPE(growth, size);
  auto destination = TPtr<TLoom<ISZ, ISY>>(growth);

  TLoomClone<TPARAMS>(loom, destination, count_max, count_max, size, size);
#if D_THIS
  D_COUT("\n\nAfter:\n");
  TLoomPrint<COut, TPARAMS>(COut().Star(), destination);
  D_COUT('\n');
  D_COUT(Charsf(destination, destination->size));
#endif

  Delete(obj);
  obj.origin = growth;
  return true;
}

/* Adds a string to the end of the Loom, auto-growing if neccissary.
@return The index upon success or -1 if the obj can't grow anymore. */
template <TARGS, typename BUF>
ISY TLoomInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* item,
                ISY index = cPush) {
  if (!item) return -1;
  D_COUT("\nAdding:\"" << item << '\"');
  ISY result =
      TLoomInsert<TPARAMS>(obj.OriginAs<TLoom<ISZ, ISY>*>(), item, index);
  while (result < 0) {
    if (!TLoomGrow<TPARAMS>(obj.AJT())) {
      D_COUT("\n\nFailed to grow.\n\n");
      return -1;
    }
    result =
        TLoomInsert<TPARAMS>(obj.OriginAs<TLoom<ISZ, ISY>*>(), item, index);
  }
  return result;
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template <TARGS>
CHT* TLoomPop(TLoom<ISZ, ISY>* loom) {
  if (loom->map.count == 0) return nullptr;
  ISZ offset = TStackPop<ISZ, ISY>(&loom->map), top = loom->top;
  loom->top = offset;
  return reinterpret_cast<CHT*>(reinterpret_cast<ISW>(loom) + offset);
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template <TARGS>
ISY TLoomRemove(TLoom<ISZ, ISY>* loom, ISY index) {
  ISY count = ISY(loom->map.count);
  if (index == count) {
    if (!TLoomPop<TPARAMS>(loom)) return -1;
    return count;
  }
  if (index < 0 || index > count) return -1;

  ISZ* offsets = TStackStart<ISZ, ISY>(&loom->map);
  ISZ offset = offsets[index],        //
      offset_b = offsets[index + 1],  //
      delta = offset_b - offset;      //

  TStackRemove<ISZ, ISY>(&loom->map, ISZ(index));

  // ArrayShiftDown(TPtr<CHA>(loom) + offset, delta);
  return index;
}

/* Searches for the given string in the loom.
@return -1 if the loom doesn't contain the string or the index if it does. */
template <TARGS>
ISZ TLoomFind(TLoom<ISZ, ISY>* loom, const CHT* string) {
  D_ASSERT(loom);
  D_ASSERT(string);
  ISZ* offsets = TStackStart<ISZ, ISY>(&loom->map);
  for (ISZ i = 0; i < loom->map.count; ++i) {
    ISZ offset = offsets[i];
    CHT* other = reinterpret_cast<CHT*>(reinterpret_cast<IUW>(loom) + offset);
    if (!TSTRCompare<CHT>(string, other)) return i;
  }
  return -1;
}

/* An ASCII Loom Autoject. */
template <typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM,
          ISZ cSize_ = 512,
          typename BUF = TBUF<cSize_, CHT, ISZ, TLoom<ISZ, ISY>>>
class ALoom {
  AArray<IUA, ISZ, BUF> obj_;  //< An Auto-Array object.
 public:
  enum { cCountDefault = cSize_ / 16 };
  /* Constructs a Loom. */
  ALoom(ISY count_max = cCountDefault) {
    TLoomInit<TPARAMS>(This(), count_max);
  }

  /* Constructs a Loom subclass.
  @param factory SocketFactory to call when the String overflows. */
  ALoom(SocketFactory socket_factory, ISY count = cCountDefault)
      : obj_(socket_factory) {
    TLoomInit<TPARAMS>(This(), count);
  }

  /* Constructs a Loom subclass.
  @param factory SocketFactory to call when the String overflows. */
  ALoom(SocketFactory socket_factory, ISZ size = CLoomSizeDefault<TPARAMS>(),
        ISZ count = CLoomCountDefault<TPARAMS>())
      : obj_(socket_factory) {
    TLoomInit<TPARAMS>(This(), count);
  }

  inline ISZ Size() { return obj_.Size(); }

  /* Deep copies the given string into the Loom.
  @return The index of the string in the Loom. */
  inline ISZ Insert(const CHT* string, ISY index = cPush) {
    return TLoomInsert<TPARAMS, BUF>(AJT_ARY(), string, index);
  }

  /* Removes the string at the given index from the Loom. */
  inline ISZ Remove(ISY index) { return TLoomRemove<TPARAMS>(This(), index); }

  /* Gets the string at the given index. */
  inline CHT* Get(ISY index) { return TLoomGet<TPARAMS>(This(), index); }

  /* Searches for the given string.
  @return -1 if the Loom doesn't contain the string or the index if it does.
*/
  inline ISZ Find(const CHT* string) {
    return TLoomFind<TPARAMS>(This(), string);
  }

  /* Gets the ASCII Object. */
  inline TLoom<ISZ, ISY>* This() { return obj_.OriginAs<TLoom<ISZ, ISY>*>(); }

  /* Gets the Auto-Array. */
  inline Autoject AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array. */
  inline AArray<IUA, ISZ, BUF>& AJT_ARY() { return obj_; }

  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    TLoomPrint<Printer, TPARAMS>(o, This());
    return o;
  }

  inline void COut() { PrintTo<_::COut>(_::COut().Star()); }
};
}  //< namespace _
#undef TPARAMS
#undef TARGS
#endif
#endif
