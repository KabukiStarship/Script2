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
#include "Stack.hpp"
#include "Types.hpp"
#if SEAM == SCRIPT2_LOOM
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
#define LOM_A typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM
#define LOM_P CHT, ISZ, ISY
namespace _ {
/* @ingroup Loom
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/MapTypes/Loom.md

# Memory Layout

+============================+
|_______ Buffer              |
|_______ ...                 | <-- top
|_______ String N            |
|_______ ...                 |
|_______ String 0            |
+----------------------------+
|_______ count_max           |
|_______ ...                 |
|_______ String offset N     |
|_______ ...                 |
|        String offset 0     |
+============================+  ^ Up in
|       Loom Header          |  |
+============================+  + 0xN

@todo Look into adding variable for average UTF-8 and UTF-16 character length.
*/

/* An array of Strings. */
template<typename ISZ = ISN, typename ISY = ISM>
struct TLoom {
  ISZ size_bytes,   //< Size of the Loom in bytes.
      top;          //< Offset to the top of the string stack.
  TStack<ISY> map;  //< A Stack of offset mappings to strings.
};

template<LOM_A>
constexpr ISZ TLoomCountMin() {
  return 8 / sizeof(ISZ);
}

template<LOM_A>
constexpr ISZ TLoomSizeMin() {
  enum {
    CountMin = TLoomCountMin(),
    SizeMin = sizeof(TLoom<ISZ, ISY>) + CountMin * (sizeof(ISZ) + 2),
  };
  return SizeMin;
}

/* Calculates the minimum size of a Loom of empty strings with the given 
count_max. */
template<LOM_A>
ISZ TLoomSizeMin(ISZ count_max, ISZ average_string_length = 0) {
  return sizeof(TLoom<ISZ, ISY>) + 
    count_max * (sizeof(ISY) + (average_string_length + 1) * sizeof(CHT));
}

/* The default average length of a key. */
template<LOM_A>
constexpr ISZ TLoomLengthDefault() {
  return 32;
}

/* Default number of strings in a Loom. */
template<LOM_A>
constexpr ISZ TLoomCountDefault() {
  return 32;
}

/* The default size of a Loom when no paramters are specified. */
template<LOM_A>
constexpr ISZ TLoomSizeDefault() {
  return (TLoomLengthDefault<LOM_P>() *
    TLoomCountDefault<LOM_P>() * sizeof(CHT)) & (sizeof(ISW) - 1);
}

/* The default size of a Loom when no paramters are specified. */
template<LOM_A>
constexpr ISZ TLoomSize(ISY count_max, ISZ string_length_average = 
                         TLoomLengthDefault<LOM_P>()) {
  return count_max * ((string_length_average + 1) * sizeof(CHT) +
          sizeof(ISY)) + sizeof(TLoom<ISZ, ISY>);
}

/* Gets the default number of characters in a loom string. */
template<LOM_A>
constexpr ISZ TLoomDefaultLengthString() {
  return 32;
}

/* Calculates the default size of a Loom with the given average string
length. */
template<LOM_A>
inline ISZ TLoomKeysSize(ISY count_max, ISZ average_length_string =
  TLoomDefaultLengthString<LOM_P>()) {
  return count_max * sizeof(CHT) * (average_length_string + 1) +
          count_max * sizeof(ISY) + sizeof(TLoom<LOM_P>);
}

/* Returns the pointer to the first character in the loom string buffer. */
template<LOM_A>
inline CHT* TLoomStart(TLoom<ISZ, ISY>* loom, ISY count_max) {
  ISZ* top = &TStackStart<ISZ, ISY>(&loom->map)[count_max];
  return TPtr<CHT>(top);
}
template<LOM_A>
inline CHT* TLoomStart(TLoom<ISZ, ISY>* loom) {
  return TLoomStart<LOM_P>(loom, loom->map.count_max);
}

/* Returns the byte after the last byte in the Loom data structure. */
template<LOM_A>
constexpr IUA* TLoomEnd(TLoom<ISZ, ISY>* loom) {
  return TPtr<IUA>(loom, loom->size_bytes);
}

/* Returns the byte after the last byte in the Loom data structure. */
template<LOM_A>
constexpr IUA* TLoomTop(TLoom<ISZ, ISY>* loom) {
  return TPtr<IUA>(loom, loom->size_bytes);
}

/* Calculates the amount of free space left in the buffer */
template<LOM_A>
inline ISZ TLoomFreeSpace(TLoom<ISZ, ISY>* loom) {
  D_COUT("\n\nTLoomFreeSpace::loom->size_bytes:" << loom->size_bytes << "\n\n");
  return loom->size_bytes - loom->top;
}

/* Gets the element at the given index. */
template <LOM_A>
CHT* TLoomGet(TLoom<ISZ, ISY>* loom, ISY index) {
  D_ASSERT(loom);
  if (index < 0 || index >= loom->map.count) return nullptr;
  return TPtr<CHT>(loom, TStackStart<ISZ, ISY>(&loom->map)[index]);
}

/* Prints the Loom to the stream. */
template <typename Printer, LOM_A>
Printer& TLoomPrint(Printer& o, TLoom<ISZ, ISY>* loom) {
  ISY count = loom->map.count;
  // CHT, ISZ, ISY
  o << "\nLoom<CH" << TSizef<CHA>() << ", IS" << TSizef<ISZ>() << ", IS"
    << TSizef<ISY>() << "> size:" << loom->size_bytes
    << " top:" << loom->top << " count_max:" << loom->map.count_max
    << " count:" << count;
  ISZ* offsets = TStackStart<ISZ, ISY>(&loom->map);
  for (ISY i = 0; i < count; ++i)
    o << '\n'
      << i << ".) \"" << TLoomGet<LOM_P>(loom, i) << "\":" << offsets[i];
  return o << '\n';
}

/* Initializes the loom with the given count_max.
@pre The size in bytes must be the first ISZ of the data. */
template<LOM_A>
inline TLoom<ISZ, ISY>* TLoomInit(TLoom<ISZ, ISY>* loom, ISY count_max) {
  D_ASSERT(loom);
  A_ASSERT(count_max >= TLoomCountMin<LOM_P>());
  D_ARRAY_WIPE(&loom->top, loom->size_bytes - sizeof(ISZ));

  // count_max -= count_max & 3; // @todo Ensure the values are word-aligned?
  auto top = TLoomStart<LOM_P>(loom, count_max);
  loom->top = TDelta<ISZ>(loom, top);
  loom->map.count_max = count_max;
  loom->map.count = 0;
  D_COUT("\n\nTLoomInit" << "" <<" size_bytes: "
         << size_bytes << " count:" << loom->map.count
         << "/" << count_max << " top:" << loom->top 
         << " space_left:" << TDelta<>(TPtr<>(loom, top)));
  return loom;
}

template<LOM_A>
CHT* TLoomStop(TLoom<ISZ, ISY>* loom) {
  ISW address = ISW(loom) + loom->top;
  return TPtr<CHT>(address);
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template<LOM_A>
ISY TLoomInsert(TLoom<ISZ, ISY>* loom, const CHT* string, ISY index = STKPush) {
  D_ASSERT(loom);
  if (!string || loom->map.count >= loom->map.count_max) return -2;
  ISY count = loom->map.count;
  D_ASSERT(count >= 0);
  CHT* cursor = nullptr;
  if (index < 0) {
    if (index == Any) {
      D_COUT("\n\nindex == _ANY\n\n");
      if (count <= 1) {
        index = count;
      } else {
        auto length = TSTRLength<CHT>(string);
        for (ISN i = 0; i < count; ++i) {
          if (i == count) {
            index = count;
            break;
          }
          cursor = TSTREnd<CHT>(TLoomGet<LOM_P>(loom, i)) + 1;
          CHT* start_next_string = TLoomGet<LOM_P>(loom, i + i);
          if (start_next_string - cursor > length) {
            index = i;
            break;
          }
          cursor = start_next_string;
        }
      }
      if (index != count) {
        index = TStackInsert<ISZ, ISY>(&loom->map, TDelta<ISZ>(loom, cursor), 
                                       index);
        cursor = TSPrintString<CHT>(cursor, (CHT*)TLoomEnd<LOM_P>(loom),
                                    string);
        return index;
      }
    }
  }
  cursor = TPtr<CHT>(loom, loom->top);
  cursor = TSPrintString<CHT>(cursor, (CHT*)TLoomEnd<LOM_P>(loom), string);
  if (!cursor) return -1;

  index = TStackInsert<ISZ, ISY>(&loom->map, loom->top, index);
  loom->top = TDelta<ISZ>(loom, cursor + 1);
  return index;
}

template<LOM_A>
ISZ TLoomCharCount(TLoom<ISZ, ISY>* loom) {
  return (ISZ)(TLoomEnd<LOM_P>(loom) - TLoomStart<LOM_P>(loom));
}
template<LOM_A>
BOL TLoomWrite(TLoom<ISZ, ISY>* destination, TLoom<ISZ, ISY>* soure) {
  return true;
}

/* Clones the loom to the pre-allocated destination Socket. */
template<LOM_A>
BOL TLoomClone(TLoom<ISZ, ISY>* loom, TLoom<ISZ, ISY>* destination,
               ISY count_max = loom->count_max, ISY count_additional = 0,
               ISY size = loom->size, ISY size_additional = 0) {
  if (!loom || !destination) return false;
  ISZ top = loom->top;
  ISY count = loom->map.count;
  destination->size_bytes = size + size_additional;
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
  CHT* start = TLoomStart<LOM_P>(loom);
  ISZ strings_size = TDelta<ISZ>(start, TPtr<>(loom, top));
  CHT* clone_start = TLoomStart<LOM_P>(destination);
  if (strings_size) ArrayCopy(clone_start, strings_size, start, strings_size);
  return true;
}

/* Doubles the size and count_max of the loom.
@return Returns nil if the size is greater than the amount of memory that
can fit in type ISW, the unaltered socket pointer if the Stack has grown to
the size upper bounds, or a new dynamically allocated socket upon failure. */
template<LOM_A>
BOL TLoomGrow(Autoject& obj) {
  D_COUT("\n\nGrowing Loom...");
  auto loom = TPtr<TLoom<ISZ, ISY>>(obj.origin);
  A_ASSERT(loom);
  ISZ size_bytes = loom->size_bytes;
  if (!TCanGrow<ISZ>(size_bytes)) return false;
  ISY count_max = loom->map.count_max;

  D_COUT(" new size:" << size_bytes << " count_max:" << count_max);

#if D_THIS
  D_COUT("\n\nBefore:\n");
  TLoomPrint<COut, LOM_P>(COut().Star(), loom);
  D_COUT('\n' << Charsf(loom, loom->size_bytes));
#endif

  // @see RAMFactory for documentation on how to create a new block of memory.
  auto size_double = size_bytes << 1;
  IUW* growth = obj.ram(nullptr, size_double);
  D_ARRAY_WIPE(growth, size_bytes);
  auto destination = TPtr<TLoom<ISZ, ISY>>(growth);

  TLoomClone<LOM_P>(loom, destination, count_max, count_max, size_bytes, size_bytes);
#if D_THIS
  D_COUT("\n\nAfter:\n");
  TLoomPrint<COut, LOM_P>(COut().Star(), destination);
  D_COUT('\n');
  D_COUT(Charsf(destination, destination->size_bytes));
#endif

  Delete(obj);
  obj.origin = growth;
  return true;
}

/* Adds a string to the end of the Loom, auto-growing if neccissary.
@return The index upon success or -1 if the obj can't grow anymore. */
template<LOM_A, typename BUF>
ISY TLoomInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* item,
                ISY index = STKPush) {
  if (!item) return -1;
  D_COUT("\nAdding:\"" << item << '\"');
  ISY result =
      TLoomInsert<LOM_P>(obj.OriginAs<TLoom<ISZ, ISY>*>(), item, index);
  while (result < 0) {
    if (!TLoomGrow<LOM_P>(obj.AJT())) {
      D_COUT("\n\nFailed to grow.\n\n");
      return -1;
    }
    result =
        TLoomInsert<LOM_P>(obj.OriginAs<TLoom<ISZ, ISY>*>(), item, index);
  }
  return result;
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template<LOM_A>
CHT* TLoomPop(TLoom<ISZ, ISY>* loom) {
  if (loom->map.count == 0) return nullptr;
  ISZ offset = TStackPop<ISZ, ISY>(&loom->map), top = loom->top;
  loom->top = offset;
  return TPtr<CHT>(ISW(loom) + offset);
}

/* Adds a string to the end of the Loom.
@return The index upon success or -1 upon failure. */
template<LOM_A>
ISY TLoomRemove(TLoom<ISZ, ISY>* loom, ISY index) {
  ISY count = ISY(loom->map.count);
  if (index == count) {
    if (!TLoomPop<LOM_P>(loom)) return -1;
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
template<LOM_A>
ISZ TLoomFind(TLoom<ISZ, ISY>* loom, const CHT* string) {
  D_ASSERT(loom);
  D_ASSERT(string);
  ISZ* offsets = TStackStart<ISZ, ISY>(&loom->map);
  for (ISZ i = 0; i < loom->map.count; ++i) {
    ISZ offset = offsets[i];
    CHT* other = TPtr<CHT>(IUW(loom) + offset);
    if (!TSTRCompare<CHT>(string, other)) return i;
  }
  return -1;
}

/* An ASCII Loom Autoject. */
template<typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM,
          ISZ cSize_ = 512,
          typename BUF = TBUF<cSize_, CHT, ISZ, TLoom<ISZ, ISY>>>
class ALoom {
  AArray<IUA, ISZ, BUF> obj_;  //< An Auto-Array object.
 public:
  enum { cCountDefault = cSize_ / 16 };
  /* Constructs a Loom. */
  ALoom(ISY count_max = cCountDefault) {
    TLoomInit<LOM_P>(This(), count_max);
  }

  /* Constructs a Loom subclass.
  @param factory RAMFactory to call when the String overflows. */
  ALoom(RAMFactory ram, ISY count = cCountDefault)
      : obj_(ram) {
    TLoomInit<LOM_P>(This(), count);
  }

  /* Constructs a Loom subclass.
  @param factory RAMFactory to call when the String overflows. */
  ALoom(RAMFactory ram, ISZ size_bytes = TLoomSizeDefault<LOM_P>(),
        ISZ count = TLoomCountDefault<LOM_P>())
      : obj_(ram) {
    TLoomInit<LOM_P>(This(), count);
  }

  inline ISZ Size() { return obj_.Size(); }

  /* Deep copies the given string into the Loom.
  @return The index of the string in the Loom. */
  inline ISZ Insert(const CHT* string, ISY index = STKPush) {
    return TLoomInsert<LOM_P, BUF>(AJT_ARY(), string, index);
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
  inline TLoom<ISZ, ISY>* This() { return obj_.OriginAs<TLoom<ISZ, ISY>*>(); }

  /* Gets the Auto-Array. */
  inline Autoject AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array. */
  inline AArray<IUA, ISZ, BUF>& AJT_ARY() { return obj_; }

  template<typename Printer>
  inline Printer& PrintTo(Printer& o) {
    TLoomPrint<Printer, LOM_P>(o, This());
    return o;
  }

  inline void COut() { PrintTo<_::COut>(_::COut().Star()); }
};
}  //< namespace _
#endif
#endif
