/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Loom.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_LOOM_TEMPLATES
#define SCRIPT2_LOOM_TEMPLATES
#include <_Config.h>
#if SEAM >= SCRIPT2_LOOM
#include "Array.h"
#include "Stack.hpp"
#include "Types.hpp"
#if SEAM == SCRIPT2_LOOM
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
#define LOM_A typename CHT = CHR, typename ISZ = ISR, typename ISY = ISQ
#define LOM_P CHT, ISZ, ISY
namespace _ {
/* @ingroup Loom
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/MapTypes/Loom.md

# Memory Layout

+============================+
|_______ Boofer              | <-- start
|_______ String N            |
|_______ String 0            |
+----------------------------+
|_______ Boofer              |
|_______ String offset N     |
|        String offset 0     |
+============================+  ^ Up in
|       Loom Header          |  |
+============================+  + 0xN

@todo Look into adding variable for average UTF-8 and UTF-16 character length.
@todo Change keys_offset delta from table to keys_map.
*/

/* An array of Strings. */
template<LOM_A>
struct TLoom {
  ISZ bytes,          //< Size of the Loom in bytes.
      start;          //< Offset to the start of the string stack.
  TStack<SCK_P> map;  //< A Stack of offset mappings to strings.
};

#define LOM TLoom<LOM_P>

template<LOM_A>
constexpr ISY TLoomCountMin() {
  return 8 / sizeof(ISZ);
}

template<LOM_A>
constexpr ISZ TLoomSizeMin() {
  enum {
    CountMin = TLoomCountMin(),
    SizeMin = sizeof(TLoom<LOM_P>) + CountMin * (sizeof(ISZ) + 2),
  };
  return SizeMin;
}

/* Calculates the minimum size of a Loom of empty strings with the given 
total. */
template<LOM_A>
ISZ TLoomSizeMin(ISZ total, ISZ average_string_length = 0) {
  return sizeof(TLoom<LOM_P>) + 
    total * (sizeof(ISY) + (average_string_length + 1) * sizeof(CHT));
}

/* The default length of a key. */
template<LOM_A>
constexpr ISZ TLoomKeyLengthDefault() {
  return 32;
}

/* Default number of strings in a Loom. */
template<LOM_A>
constexpr ISY TLoomCountDefault() {
  return 32;
}

/* The default size of a Loom when no paramters are specified. */
template<LOM_A>
constexpr ISZ TLoomSizeDefault() {
  return (TLoomKeyLengthDefault<LOM_P>() *
    TLoomCountDefault<LOM_P>() * sizeof(CHT)) & (sizeof(ISW) - 1);
}

/* The default size of a Loom when no paramters are specified. */
template<LOM_A>
constexpr ISZ TLoomSize(ISY total, ISZ string_length_average = 
                         TLoomKeyLengthDefault<LOM_P>()) {
  return total * ((string_length_average + 1) * sizeof(CHT) +
          sizeof(ISY)) + sizeof(TLoom<LOM_P>);
}

/* Gets the default number of characters in a loom string. */
template<LOM_A>
constexpr ISZ TLoomDefaultLengthString() {
  return 32;
}

/* Calculates the default size of a Loom with the given average string
length. */
template<LOM_A>
inline ISZ TLoomKeysSize(ISY total, ISZ average_length_string =
  TLoomDefaultLengthString<LOM_P>()) {
  return total * sizeof(CHT) * (average_length_string + 1) +
          total * sizeof(ISY) + sizeof(TLoom<LOM_P>);
}

/* Returns the pointer to the first character in the loom string boofer. */
template<LOM_A>
inline CHT* TLoomKeysBegin(TLoom<LOM_P>* loom, ISY total) {
  return TPtr<CHT>(&TStackStart<ISZ, ISZ>(&loom->map)[total]);
}
template<LOM_A>
inline const CHT* TLoomKeysBegin(const TLoom<LOM_P>* loom, ISY total) {
  return CPtr<CHT>(
    TLoomKeysBegin<LOM_P>(CPtr<TLoom<LOM_P>>(loom), total));
}
template<LOM_A>
inline CHT* TLoomKeysBegin(TLoom<LOM_P>* loom) {
  return TLoomKeysBegin<LOM_P>(loom, loom->map.total);
}
template<LOM_A>
inline const CHT* TLoomKeysBegin(const TLoom<LOM_P>* loom) {
  return TLoomKeysBegin<LOM_P>(loom, loom->map.total);
}

/* Returns the offset to the begin of the strings. */
template<LOM_A>
inline ISZ TLoomKeysBegin(ISY total) {
  return sizeof(ISZ) * total + sizeof(TLoom<LOM_P>);
}

template<LOM_A>
CHT* TLoomStop(TLoom<LOM_P>* loom, ISZ bytes) {
  return TPtr<CHT>(TPtrDown<ISW, CHT>(loom, bytes));
}
template<LOM_A>
inline const CHT* TLoomStop(const TLoom<LOM_P>* loom, ISZ bytes) {
  return CPtr<CHT>(TLoomStop<LOM_P>(CPtr<TLoom<LOM_P>>(loom), bytes));
}

template<LOM_A>
CHT* TLoomStop(TLoom<LOM_P>* loom) {
  return TLoomStop<LOM_P>(loom, loom->bytes);
}
template<LOM_A>
inline const CHT* TLoomStop(const TLoom<LOM_P>* loom) {
  return TLoomStop<LOM_P>(loom, loom->bytes);
}

/* Returns the byte after the last byte in the Loom data structure. */
template<LOM_A, typename T = IUA>
inline const T* TLoomEnd(const TLoom<LOM_P>* loom) {
  return TPtr<T>(loom, loom->bytes);
}
template<LOM_A, typename T = IUA>
inline T* TLoomEnd(TLoom<LOM_P>* loom) {
  return CPtr<T>(
    TLoomEnd<LOM_P>(CPtr<TLoom<LOM_P>>(loom)));
}

/* Returns the byte after the last byte in the Loom data structure. */
template<LOM_A, typename T = IUA>
inline const T* TLoomTop(const TLoom<LOM_P>* loom) {
  return TPtr<T>(loom, loom->bytes);
}
template<LOM_A, typename T = IUA>
inline T * TLoomTop(const TLoom<LOM_P>*loom) {
  return CPtr<T>(
    TLoomTop<LOM_P>(CPtr<TLoom<LOM_P>>(loom), loom->bytes));
}

/* Free space left in the keys boofer */
template<LOM_A>
inline ISZ TLoomFreeSpace(const TLoom<LOM_P>* loom) {
  D_COUT("\n\nTLoomFreeSpace::loom->bytes:" << loom->bytes << "\n\n");
  return loom->bytes - loom->start;
}

/* Points to the string offsets array. */
template <LOM_A>
ISZ* TLoomKeysMap(TLoom<LOM_P>* loom) {
  return TPtr<ISZ>(loom, sizeof(TLoom<LOM_P>));
}
template <LOM_A>
const ISZ* TLoomKeysMap(const TLoom<LOM_P>* loom) {
  return CPtr<ISZ>(TLoomKeysMap<LOM_P>(CPtr<TLoom<LOM_P>>(loom)));
}

/* Gets the element at the given index. */
template <LOM_A>
CHT* TLoomGet(TLoom<LOM_P>* loom, ISY index) {
  D_ASSERT(loom);
  if (index < 0 || index >= loom->map.count) return nullptr;
  return TPtr<CHT>(loom, TStackStart<ISZ, ISZ>(&loom->map)[index]);
}
template <LOM_A>
const CHT* TLoomGet(const TLoom<LOM_P>* loom, ISY index) {
  return CPtr<CHT>(TLoomGet<LOM_P>(CPtr<TLoom<LOM_P>>(loom), index));
}

/* Gets the element at the given index. */
template <LOM_A>
const CHT* TLoomGet_NC(const TLoom<LOM_P>* loom, ISY index) {
  return TPtr<CHT>(loom, TLoomKeysMap<LOM_P>(loom)[index]);
}
template <LOM_A>
CHT* TLoomGet_NC(TLoom<LOM_P>* loom, ISY index) {
  return CPtr<CHT>(TLoomGet_NC<LOM_P>(CPtr<TLoom<LOM_P>>(loom), index));
}

/* Prints the Loom to the stream. */
template <typename Printer, LOM_A>
Printer& TLoomPrint(Printer& o, const TLoom<LOM_P>* loom) {
  ISY count = ISY(loom->map.count);
  // CHT, ISZ, ISY
  o << "\nLoom<CH" << CSizeCodef<CHA>() << ", IS" << CSizeCodef<ISZ>() << ", IS"
    << CSizeCodef<ISY>() << "> size:" << loom->bytes
    << " start:" << loom->start << " total:" << loom->map.total
    << " count:" << count;
  const ISZ* offsets = TStackStart<ISZ, ISZ>(&loom->map);
  for (ISY i = 0; i < count; ++i)
    o << '\n'
      << i << ".) \"" << TLoomGet<LOM_P>(loom, i) << "\":" << offsets[i];
  return o << '\n';
}

/* Initializes the loom with the given total.
@pre The size in bytes must be the first ISZ of the data. */
template<LOM_A>
inline TLoom<LOM_P>* TLoomInit(TLoom<LOM_P>* loom, ISY total) {
  D_ASSERT(loom);
  A_ASSERT(total >= TLoomCountMin<LOM_P>());
  D_ARRAY_WIPE(&loom->start, loom->bytes - sizeof(ISZ));

  // total -= total & 3; // @todo Ensure the values are word-aligned?
  auto start = TLoomKeysBegin<LOM_P>(loom, total); // @todo Why???
  ISZ bytes = loom->bytes;
  loom->start = TDelta<ISZ>(loom, start);
  loom->map.total = total;
  loom->map.count = 0;
  D_COUT("\n\nTLoomInit" << "" <<" bytes: "
         << loom->bytes << " count:" << loom->map.count
         << "/" << total << " start:" << loom->start
         << " space_atop:" << (loom->start - loom->bytes));
  return loom;
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template<LOM_A, typename CH = CHT>
ISY TLoomInsert(TLoom<LOM_P>* loom, const CH* string, ISY index = PSH) {
  D_ASSERT(loom);
  if (!string || loom->map.count >= loom->map.total) 
    return -ErrorInvalidIndex;
  ISY count = ISY(loom->map.count);
  D_ASSERT(count >= 0);
  CHT* cursor = nullptr;
  if (index < 0) {
    if (index == ANY) {
      D_COUT("\n\nindex == _ANY\n\n");
      if (count <= 1) {
        index = count;
      } else {
        auto length = TSTRLength<CH>(string);
        for (ISN i = 0; i < count; ++i) {
          if (i == count) {
            index = count;
            break;
          }
          cursor = TSTREnd<CHT>(TLoomGet<LOM_P>(loom, i)) + 1;
          CHT* start_next_string = (CHT*)(TLoomGet<LOM_P>(loom, i + 1));
          if (start_next_string - cursor > length) {
            index = i;
            break;
          }
          cursor = start_next_string;
        }
      }
      if (index != count) {
        index = TStackInsert<ISZ, ISZ, ISY>(&loom->map, TDelta<ISZ>(loom, cursor), 
                                       index);
        TSPrintString<CHT>(cursor, (CHT*)TLoomEnd<LOM_P>(loom), string);
        return index;
      }
    }
  }
  cursor = TPtr<CHT>(loom, loom->start);
  cursor = TSPrintString<CHT>(cursor, (CHT*)TLoomEnd<LOM_P>(loom), string);
  if (!cursor) return -1;

  auto i = TStackInsert<ISZ, ISZ, ISY>(&loom->map, loom->start, ISZ(index));
  index = ISY(i);
  loom->start = TDelta<ISZ>(loom, cursor + 1);
  return index;
}

template<LOM_A>
ISZ TLoomCharCount(TLoom<LOM_P>* loom) {
  return (ISZ)(TLoomEnd<LOM_P>(loom) - TLoomKeysBegin<LOM_P>(loom));
}
template<LOM_A>
BOL TLoomWrite(TLoom<LOM_P>* destination, TLoom<LOM_P>* soure) {
  return true;
}

/* Clones the loom to the pre-allocated destination Socket. */
template<LOM_A>
BOL TLoomClone(const TLoom<LOM_P>* loom, TLoom<LOM_P>* destination,
               ISY total = loom->total, ISY total_additional = 0,
               ISY bytes = loom->bytes, ISY bytes_additional = 0) {
  if (!loom || !destination) return false;
  ISZ start              = loom->start;
  ISY count              = loom->map.count;
  destination->bytes     = bytes + bytes_additional;
  destination->start     = loom->start + (total_additional * sizeof(ISY));
  destination->map.total = total + total_additional;
  destination->map.count = count;
  const ISZ* loom_offsets      = TStackStart<ISZ, ISZ>(&loom->map),
           * loom_offsets_end  = loom_offsets + total + total_additional;
  ISZ* clone_offsets     = TStackStart<ISZ, ISZ>(&destination->map);

  if (!total_additional) {
    while (loom_offsets <= loom_offsets_end)
      *clone_offsets++ = (*loom_offsets++);
  } else {
    while (loom_offsets <= loom_offsets_end)
      *clone_offsets++ = (*loom_offsets++) + total_additional * sizeof(ISY);
  }

  // Copy the Strings.
  ISZ keys_bytes = start - TLoomKeysBegin<LOM_P>(total);
  RAMCopy(TLoomKeysBegin<LOM_P>(destination), keys_bytes,
          TLoomKeysBegin<LOM_P>(loom       ), keys_bytes);
  return true;
}

/* Doubles the size and total of the loom.
@return Returns nil if the size is greater than the amount of memory that
can fit in type ISW, the unaltered socket pointer if the Stack has grown to
the size upper bounds, or a new dynamically allocated socket upon failure. */
template<LOM_A>
BOL TLoomGrow(Autoject& obj) {
  D_COUT("\n\nGrowing Loom...");
  auto loom = TPtr<TLoom<LOM_P>>(obj.origin);
  A_ASSERT(loom);
  ISZ size = loom->bytes,
      new_size = ATypeGrow(size);
  if (!ATypeCanGrow(size, new_size)) return false;
  ISY total = loom->map.total;

  //  D_COUT(" size:" << size " new_size:");<< new_size << " total : " <<
         //total);

#if D_THIS
  D_COUT("\n\nBefore:\n");
  TLoomPrint<COut, LOM_P>(StdOut(), loom);
  D_COUT('\n' << Charsf(loom, loom->bytes));
#endif

  // @see RAMFactory for documentation on how to create a new block of memory.
  auto size_double = size << 1;
  IUW* growth = obj.ram(nullptr, size_double);
  D_ARRAY_WIPE(growth, size);
  auto destination = TPtr<TLoom<LOM_P>>(growth);

  TLoomClone<LOM_P>(loom, destination, total, total, size, size);
#if D_THIS
  D_COUT("\n\nAfter:\n");
  TLoomPrint<COut, LOM_P>(StdOut(), destination);
  D_COUT('\n');
  D_COUT(Charsf(destination, destination->bytes));
#endif

  Delete(obj);
  obj.origin = growth;
  return true;
}

/* Adds a string to the end of the Loom, auto-growing if neccissary.
@return The index upon success or -1 if the obj can't grow anymore. */
template<LOM_A, typename CH=CHT>
ISY TLoomInsert(Autoject& obj, const CH* item, ISY index = PSH) {
  if (!item) return -1;
  D_COUT("\nAdding:\"" << item << '\"');
  ISY result =
      TLoomInsert<LOM_P, CH>(TPtr<LOM>(obj.origin), item, index);
  while (result < 0) {
    if (!TLoomGrow<LOM_P>(obj)) {
      D_COUT("\n\nFailed to grow.\n\n");
      return -1;
    }
    result = TLoomInsert<LOM_P, CH>(TPtr<LOM>(obj.origin), item, index);
  }
  return result;
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template<LOM_A>
CHT* TLoomPop(TLoom<LOM_P>* loom) {
  if (loom->map.count == 0) return nullptr;
  ISZ offset = TStackPop<ISZ, ISZ>(&loom->map), start = loom->start;
  loom->start = offset;
  return TPtr<CHT>(ISW(loom) + offset);
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template<LOM_A>
ISY TLoomRemove(TLoom<LOM_P>* loom, ISY index) {
  ISY count = ISY(loom->map.count);
  if (index == count) {
    if (!TLoomPop<LOM_P>(loom)) return -1;
    return count;
  }
  if (index < 0 || index > count) return -1;

  ISZ* offsets = TStackStart<ISZ, ISZ>(&loom->map);
  ISZ offset   = offsets[index],        //
      offset_b = offsets[index + 1],  //
      delta    = offset_b - offset;      //

  TStackRemove<ISZ, ISZ>(&loom->map, ISZ(index));

  // RAMShiftDown(TPtr<CHA>(loom) + offset, delta);
  return index;
}

/* Searches for the given string in the loom.
@return -1 if the loom doesn't contain the string or the index if it does. */
template<LOM_A>
ISY TLoomFind(TLoom<LOM_P>* loom, const CHT* string) {
  D_ASSERT(loom);
  D_ASSERT(string);
  ISZ* offsets = TStackStart<ISZ, ISZ>(&loom->map);
  for (ISZ i = 0; i < loom->map.count; ++i) {
    ISZ offset = offsets[i];
    CHT* other = TPtr<CHT>(IUW(loom) + offset);
    if (!TSTRCompare<CHT>(string, other)) return i;
  }
  return -1;
}

/* An ASCII Loom Autoject. */
template<LOM_A, ISZ Size_ = 512,
          typename BUF = TBUF<Size_, CHT, ISZ, TLoom<LOM_P>>>
class ALoom {
  AArray<IUA, ISZ, BUF> obj_;  //< An Auto-Array object.
 public:
  enum { CountDefault = Size_ / 16 };
  /* Constructs a Loom. */
  ALoom(ISY total = CountDefault) {
    TLoomInit<LOM_P>(This(), total);
  }

  /* Constructs a Loom subclass.
  @param factory RAMFactory to call when the String overflows. */
  ALoom(RAMFactory ram, ISY count = CountDefault)
      : obj_(ram) {
    TLoomInit<LOM_P>(This(), count);
  }

  /* Constructs a Loom subclass.
  @param factory RAMFactory to call when the String overflows. */
  ALoom(RAMFactory ram, ISZ bytes = TLoomSizeDefault<LOM_P>(),
        ISZ count = TLoomCountDefault<LOM_P>())
      : obj_(ram) {
    TLoomInit<LOM_P>(This(), count);
  }

  inline ISZ Size() { return obj_.Size(); }

  /* Deep copies the given string into the Loom.
  @return The index of the string in the Loom. */
  template<typename CH=CHT>
  inline ISZ Insert(const CH* string, ISY index = PSH) {
    return TLoomInsert<LOM_P, CH>(AJT(), string, index);
  }

  /* Removes the string at the given index from the Loom. */
  inline ISZ Remove(ISY index) { return TLoomRemove<LOM_P>(This(), index); }

  /* Gets the string at the given index. */
  inline CHT* Get(ISY index) { return TLoomGet<LOM_P>(This(), index); }

  /* Searches for the given string.
  @return -1 if the Loom doesn't contain the string or the index if it does.
*/
  inline ISZ Find(const CHT* string) {
    return TLoomFind<LOM_P>(This(), string);
  }

  /* Gets the ASCII Object. */
  inline TLoom<LOM_P>* This() { return obj_.OriginAs<TLoom<LOM_P>*>(); }

  /* Gets the Auto-Array. */
  inline Autoject& AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array.
  inline AArray<IUA, ISZ, BUF>& AJT_ARY() { return obj_; } */

  template<typename Printer>
  inline Printer& PrintTo(Printer& o) {
    TLoomPrint<Printer, LOM_P>(o, This());
    return o;
  }

  inline void COut() { PrintTo<_::COut>(_::StdOut()); }
};
}  //< namespace _
#endif
#endif
