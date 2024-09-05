/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Book.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_BOOK_CODE
#define SCRIPT2_BOOK_CODE
#include <_Config.h>
#if SEAM >= SCRIPT2_BOOK
#include "List.hpp"
#if SEAM == SCRIPT2_BOOK
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
namespace _ {
/* @ingroup Book
Please see the ASCII Data Specification for DRY documentation.
@link ./Spec/Data/MapTypes/Book.md

Please see the ASCII List documentation for information about
*/

#undef  BOK_P
#define BOK_P CHT, ISZ, ISY, DT
#undef  BOK_A
#define BOK_A \
  typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM, typename DT = DTB

/* @ingroup Book
@brief A contiguous memory Associative List composed of a Loom and list.
The Loom datatype stores the size_bytes, which includes the size of the 
Keys Loom and the Values List. The Keys Loom is an array of strings that 
stores the Book Keys. The Values List is a list of type-value tupes that 
correspond to the key indexes.

The first element of every List ist a Loom (Array of Strings) that stores
the keys.

@code
+====================================+
|_______   Buffer                    |
|_______ ^ List Value N              |
|_______ | List Value 1              |
|        | Keys Loom (Value 0)       |
|------------------------------------|
|_______   Buffer                    |
|_______ ^ List Value N Type         |
|_______ | List Value 1 Type         |
|        | Loom Type (Type 0)        |
|------------------------------------|
|_______   Buffer                    |
|_______   Offset to Value N         |
|_______ ^ Offset to Value 1         |
|        | Offset to Keys (Offset 0) |
+====================================+  ^ Up in
|          TList Struct              |  |
+====================================+  + 0xN
@endcode */
template<BOK_A>
struct TBook {
  TList<LST_P> values;  //< A list of values with a Loom of keys in index 0.
};

enum {
  // The number of bits to shift a Book's size_bytes right by to calculate the 
  // size_keys (Example: size_keys = size_bytes >> 2).
  BookDefaultKeysFractionShift = -1,
  // The number of bits to shift a Book's size_bytes right by to calculate the 
  // count_max (Example: count_max = size_bytes >> 5).
  BookDefaultCountMaxFractionShift = -6,
  BookDefaultLengthKey = 15,
  BookDefaultSizeBytes = 512,
  BookDefaultCount = BookDefaultSizeBytes >> -(BookDefaultKeysFractionShift),
};

/* The minimum count a good with the given template parameters can have. */
template<BOK_A>
constexpr ISY CBookCountMin() {
  return 8 / sizeof(ISZ);
}

/* The minimum size of a Book based on the CCountMin. */
template<BOK_A>
constexpr ISZ CBookSizeMin(ISY count_max) {
  return sizeof(TBook<BOK_P>) + count_max * (sizeof(ISZ) + 2); //< @todo ???
}

/* Gets the default count of a good with the given template parameters. */
template<BOK_A>
constexpr ISZ CBookDefaultCount() {
  return 32;
}

/* Gets the default count of a good with the given template parameters. */
template<BOK_A>
ISY TBookCount(const TBook<BOK_P>* book) {
  return book->values.map.count - 1;
}

/* Gets the default count of a good with the given template parameters. */
template<BOK_A>
ISY TBookCountMax(const TBook<BOK_P>* book) {
  return book->values.map.count_max - 1;
}

/* Gets the default count of a good with the given template parameters. */
template<BOK_A>
ISY TBookCountDefault(ISY size_bytes) {
  return size_bytes >> 5; // >> 5 to / by 32
}

/* Gets the default size of a Book with the CBookDefaultCount. */
template<BOK_A>
constexpr ISZ CBookDefaultSize(ISY count_max = CBookDefaultCount<BOK_P>()) {
  if (count_max < 1) return -1;
  if (count_max < CBookCountMin<BOK_P>()) 
    count_max = CBookCountMin<BOK_P>();
  return count_max * BookDefaultLengthKey * sizeof(CHT);
}

/* Points to the base of the value offsets array. */
template<BOK_A>
inline ISZ* TBookValuesMap(TBook<BOK_P>* book) {
  return TPtr<ISZ>(book, sizeof(TBook<BOK_P>));
}

/* Points to the base of the value offsets array. */
template<BOK_A>
inline const ISZ* TBookValuesMap(const TBook<BOK_P>* book) {
  return CPtr<ISZ>(TBookValuesMap<BOK_P>(CPtr<TBook<BOK_P>>(book)));
}

/* Gets the keys Loom (index 0 of the ASCII List). */
template<BOK_A>
inline TLoom<LOM_P>* TBookKeys(TBook<BOK_P>* book) {
  return TPtr<TLoom<LOM_P>>(book, *TBookValuesMap<BOK_P>(book));
}
template<BOK_A>
inline const TLoom<LOM_P>* TBookKeys(const TBook<BOK_P>* book) {
  return CPtr<TLoom<LOM_P>>(TBookKeys<BOK_P>(CPtr<TBook<BOK_P>>(book)));
}

/* Gets the values List. */
template<BOK_A>
inline ISZ* TBookKeysMap(TBook<BOK_P>* book) {
  return TLoomOffsets<LOM_P>(TBookKeys<BOK_P>(book));
}
template<BOK_A>
inline const ISZ* TBookKeysMap(const TBook<BOK_P>* book) {
  return CPtr<ISZ>(TBookKeysMap<BOK_P>(CPtr<TBook<BOK_P>>(book)));
}

/* Gets the start of the book as a templated-defined character. */
template<BOK_A>
inline CHT* TBookStart(TBook<BOK_P>* book, ISZ count_max) {
  ISZ* top = &TStackStart<ISZ, ISZ>(TBookKeys<BOK_P>(book))[count_max];
  return TPtr<CHT>(top);
}

/* Gets the start byte of the book. */
template<BOK_A>
inline CHT* TBookStart(TBook<BOK_P>* book) {
  return TBookStart<BOK_P>(book, TBookKeys<BOK_P>(book).count_max);
}

/* Points to the byte after the last byte of the book's contiguous memory block. */
template<BOK_A>
inline CHA* TBookEnd(TBook<BOK_P>* book) {
  return TListEnd<ISZ>(&book->values);
}

/* Gets the byte after the end of the book's contiguous memory block. */
template<BOK_A>
inline CHA* TBookKeysEnd(TBook<BOK_P>* book) {
  return TLoomEnd<LOM_P>(TBookKeys<BOK_P>(book));
}

/* Gets the size of the Book in bytes. */
template<BOK_A>
inline ISZ TBookCountMax(TBook<BOK_P>* book) {
  return TBookKeys<BOK_P>(book)->map.count_max;
}

/* Checks if the book size values result are valid.
You must have enough room in the size_bytes with given count_max. */
template<BOK_A>
inline BOL TBookSizesAreValid(ISZ size_bytes, ISZ size_keys, ISY count_max) {
  return size_keys <= TListSizeFreeMax<LST_P>(size_bytes, count_max);
}

// Freespace left in bytes for the given book's keys Loom and values List.
// @return Returns -1 upon failure.
template<BOK_A>
inline ISZ TBookFreespace(TBook<BOK_P>* book) {
  auto keys = TBookKeys<BOK_P>(book);
  if (!keys) return -1;
  return TListFreeSpace<ISZ>(&book->values) + 
         TLoomFreeSpace<CHT, ISZ, ISY>(keys);
}

/* Prints the book to the Printer. */
template<typename Printer, BOK_A>
Printer& TBookPrint(Printer& o, const TBook<BOK_P>* book) {
  auto count_max    = book->values.map.count_max;
  auto count        = book->values.map.count;
  auto voffsets     = TPtr<ISZ>(book, sizeof(TBook<BOK_P>));
  auto types        = TPtr<DT>(voffsets + count_max);
  auto keys_offset  = *voffsets++;
  auto keys         = TPtr<TLoom<LOM_P>>(book, keys_offset);
  auto keys_size    = keys->size_bytes;
  auto keys_top     = keys->top;
  D_COUT("\ncount_max:" << count_max << " count:" << count << 
         " keys_size:" << keys_size << " keys_top : " << keys_top);
  D_AVOW(count_max, keys->map.count_max);
  D_AVOW(count    , keys->map.count);
  D_COUT_LOOM(keys);
  o << "\nBook<CH" << CATypeSWCH<CHT>() << ",IS" << CATypeSWCH<ISZ>() << ",IS"
    << CATypeSWCH<ISY>() << "> size_bytes:" << book->values.size_bytes
    << " count_max:" << count_max << " count:" << count << '\n'
    << " list_top:" << book->values.top << " keys_offset:" << keys_offset
    << " keys_free_space:" << TLoomFreeSpace<LOM_P>(keys)
    << " values_free_space:" << TListFreeSpace<ISZ>(&book->values)
    << " keys.size_bytes:" << keys_size << " keys.top:" << keys_top
    << " TypeOf(keys):" << ATypef(types[0]) << ' ';
  for (ISY i = 1; i < count; ++i) {
    o << '\n' << i << ".) \"" << TLoomGet<LOM_P>(keys, i) << "\" type:";
    auto type    = *(++types);
    auto voffset = *(++voffsets);
    o << ATypef(type) << " voffset:" << voffset << " value:";
  }
  D_COUT(Linef('-') << ' ' << Charsf(book, book->values.size_bytes));
  return o << '\n';
}

/* ASCII Data Type for the given templated BOK.
We are mapping an offset to a CH type, and thus the VT bits are 0.
@todo Look into if VT bits should be 0 and not 
| b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
|:-------:|:------:|:-----:|:-----:|:-----:|
|   MOD   |   MT   |  SW   |  VT   |  POD  |
1. POD: Plain Old Data bits.
2. VT : Vector Type bits.
3. SW : Size Width bits.
4. MT : Map Type bits.
5. MOD: Modifier bits. */
template<BOK_A>
constexpr DTB CBookKeysType() {
  enum {
    PODBits = CATypeCH<CHR, DT>(),
    VTBits  = 1 << ATypeVTBit0,
    SWBits  = CBitCount<ISZ>() << ATypeSWBit0,
    MTBits  = CATypeIS<ISY>() << ATypeMTBit0
  };
  return MTBits | SWBits | VTBits | PODBits;
}

/* Initializes the book to the given count_max using the CBookDefaultSize.
@param size_bytes The size of the book in bytes.
@param count_max The maximum number of entries in the book -1 for the keys.
@param size_keys If this number is positive then the value is size of the keys 
Loom in bytes. If the value is negative then it is the number of bits to shift 
the size_bytes to get the size_keys. */
template<BOK_A>
TBook<BOK_P>* TBookInit(TBook<BOK_P>* book,
                        ISY count_max = BookDefaultCountMaxFractionShift, 
                        ISZ size_keys = BookDefaultKeysFractionShift) {
  D_ASSERT(book);
  TList<LST_P>* values = &book->values;
  ISZ size_bytes = values->size_bytes;

  D_COUT("\n\nTBookInit size_bytes: " << size_bytes << " count_max:" <<
         count_max << " size_keys:" << size_keys);
  D_ARRAY_WIPE(&values->top, size_bytes - sizeof(ISZ));
  if (size_keys < 0) {
    size_keys *= -1;
    if (size_keys >= TBitCount<ISZ>()) {
      D_COUT("\nInvalid count_max bit shift value.");
      return nullptr;
    }
    size_keys = size_bytes >> size_keys;
    D_COUT("\nnew size_keys:" << size_keys);
  }
  if (count_max < 0) {
    count_max *= -1;
    if (count_max >= TBitCount<ISZ>()) {
      D_COUT("\nInvalid count_max bit shift value.");
      return nullptr;
    }
    count_max = ISY(size_bytes >> ISZ(count_max));
    D_COUT("\nnew count_max:" << count_max);
  }
  if (!TBookSizesAreValid<BOK_P>(size_bytes, size_keys, count_max)) {
    D_COUT("\nInvalid book sizes!");
    return nullptr;
  }
  TListInit<LST_P>(values, size_bytes, count_max);
  DTB KeysType = CBookKeysType<BOK_P>();
  ISY keys_index = TListAlloc<LST_P>(values, KeysType, size_keys);
  D_AVOW(ISY(0), keys_index);
  D_COUT("\nkeys_index  :" << keys_index);
  TLoom<LOM_P>* keys = TListValue<LST_P, TLoom<LOM_P>>(values, keys_index);
  D_COUT("\nkeys offset : " << TDelta<>(book, keys) << 
         "\nKeysType:0b" << Binaryf(KeysType) << ' ');
  // Expected Keys offset with ABook<ISB,IUB,ISA,CHA> with SizeBytes:512
  //   sizeof(TBook<ISB,IUB,ISA,CHA>) + 8*sizeof(IUB+DTB)
  // = 8 + 8*sizeof(IUB+DTB) = 8 + 32 = 40
  D_COUT(TPrintAType<COut>(StdOut(), KeysType));
  D_COUT("\nvalue_offsets_delta:" << TDelta<>(book, TBookValuesMap<BOK_P>(book)));
  D_COUT("\nkeys_delta:" << TDelta<>(book, keys));
  if (!keys) {
    D_COUT("\nBook Keys too large to fit in list! size_keys:" << size_keys);
    return nullptr;
  }
  auto result = TLoomInit<LOM_P>(keys, count_max);
  TLoomInsert<LOM_P>(result, "");
  D_COUT("\nkeys->top:" << keys->top);
  D_COUT("\nTDelta<>(book, TBookKeys<BOK_P>(book)):" << 
         TDelta<>(book, TBookKeys<BOK_P>(book)));
  if (!result) return nullptr;
  D_COUT("\n\nTListInit Post size_bytes: " << size_bytes << 
         " count_max:" << count_max << 
         "\nBook End  :" << TDelta<>(book, TBookEnd<BOK_P>(book)) <<
         "\nKeys End  :" << TDelta<>(book, TLoomEnd<LOM_P>(keys)) <<
         "\nKeys Start:" << TDelta<>(book, keys) << "\n\nResult:\n");
  D_COUT_BOOK(book);
  return book;
}

/* Copies an ASCII Book from the origin to the destination.
template<BOK_A>
TBook<BOK_P>* TBookCopy(TBook<BOK_P>* destination, TBook<BOK_P>* origin) {
  return TPtr<TBook<BOK_P>>(TMapCopy<ISZ>(destination, origin));
} */

/* Gets the element at the given index. */
template<BOK_A>
inline void* TBookValue(TBook<BOK_P>* book, ISY index) {
  return TListValue<void, LST_P>(TBookKeys<BOK_P>(book), index);
}

/* Gets the TypeValue tuple the given index.
@param tuple Reference to the return type passed in by reference. */
template<BOK_A>
inline ATypeValue TBookATypeValue(const TBook<BOK_P>* book, ISY index) {
  return TListTypeValuePtr<ISZ, DT>(&book->values, index);
}

template<BOK_A>
inline DT* TBookTypes(TBook<BOK_P>* book, ISY count_max) {
  return TListTypes<LST_P>(&book->values, count_max);
}
template<BOK_A>
inline const DT* TBookTypes(const TBook<BOK_P>* book, ISY count_max) {
  return CPtr<DT>(TBookTypes<BOK_P>(CPtr<TBook<BOK_P>>(book), count_max));
}

/* Gets the key at the given index without doing any error checking. */
template<BOK_A>
inline CHT* TBookKey_NC(TBook<BOK_P>* book, ISY index) {
  return TLoomGet_NC<LOM_P>(TBookKeys<BOK_P>(book), index);
}

/* Gets the key at the given index without doing any error checking. */
template<BOK_A>
inline const CHT* TBookKey_NC(const TBook<BOK_P>* book, ISY index) {
  return CPtr<CHT>(TBookKey_NC<LOM_P>(CPtr<TBook<BOK_P>>(book), index));
}

/* Gets the keys offsets array. */
template<BOK_A>
inline CHT* TBookKeys_NC(TBook<BOK_P>* book, ISY index) {
  return TPtr<CHT>(book, *TPtr<ISZ>(book, sizeof(TBook<BOK_P>)));
}
template<BOK_A>
inline const CHT* TBookKeys_NC(const TBook<BOK_P>* book) {
  auto bok = CPtr<TBook<BOK_P>>(TBookKeys<BOK_P>(book));
  return CPtr<CHT>(TBookKeys_NC<LOM_P>(bok));
}

/* Gets the type at the given index without doing any error checking. */
template<BOK_A>
inline DT TBookType_NC(const TBook<BOK_P>* book, ISY count_max, ISY index) {
  return TListType_NC<LST_P>(&book->values, count_max, index);
}

/* Gets the keys offsets array. */
template<BOK_A>
inline DT* TBookTypes_NC(TBook<BOK_P>* book, ISY count_max) {
  return TPtr<DT>(book, TBookKeys_NC<BOK_P>(book) + count_max);
}
template<BOK_A>
inline const CHT* TBookTypes_NC(const TBook<BOK_P>* book) {
  auto bok = CPtr<TBook<BOK_P>>(TBookValuesMap<BOK_P>(book));
  return CPtr<CHT>(TBookTypes_NC<LOM_P>(bok));
}

/* Gets the type at the given index without doing any error checking. */
template<BOK_A>
inline void* TBookValue_NC(TBook<BOK_P>* book, ISY index) {
  return TListValue_NC<LST_P>(&book->values, index);
}
template<BOK_A>
inline const void* TBookValue_NC(const TBook<BOK_P>* book, ISY index) {
  return CPtr<void>(TBookValue_NC<BOK_P>(CPtr<TBook<BOK_P>>(book), index));
}

/* Gets the type at the given index without doing any error checking. */
template<BOK_A>
inline ISZ TBookValueOffset_NC(const TBook<BOK_P>* book, ISY index) {
  //return TListValueOffset_NC<LST_P>(&book->values, index);
  return TPtr<ISZ>(book, sizeof(TBook<BOK_P>))[index];
}

/* Gets the TypeValue tuple the given index.
@param tuple Reference to the return type passed in by reference. */
template<BOK_A>
inline TATypeKV<ISZ, DT, CHT> TBookTypeKV(const TBook<BOK_P>* book, ISY index) {
  auto count = book->values.map.count;
  if (index < 0 || index >= count) 
    return { nullptr, _NIL, 0 };
  return { TBookKey_NC<BOK_P>(book, index), 
           TBookType_NC<BOK_P>(book, book->values.map.count_max, index),
           TBookValueOffset_NC<BOK_P>(book, index) };
}

/* Adds a key-value tuple to the end of the Book.
@todo Delete this function and replace with void* value.
@return The index upon success or -1 upon failure. */
template<typename T, BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, 
    T item, ISY index = PSH) {
  D_ASSERT(book);
  if (!key) return -ErrorInputNil;
  D_COUT("\nAdding key:\"" << key << "\" item:" << item << " into index:" <<
    index);
  if (index == 0) return -ErrorInputInvalid;
  D_COUT("\nKeys offset:" << TDelta<>(book, keys));
  D_COUT("\nValues offsets:" << TDelta<>(book, 
         TBookValuesMap<BOK_P>(book)));
  ISY result = TLoomInsert<LOM_P>(keys, key, index);
  if (result < 0) {
    D_COUT("\n\n\nFailed to insert into loom:" << result << ' ' << 
           CrabsErrorSTR(result));
    D_COUT_LOOM(keys);
    D_COUT_BOOK(book);
    return -ErrorKeysBufferOverflow;
  }
  //D_COUT_LOOM(keys);
  //D_COUT("\n\nBefore:\n" << Charsf(book, book->values.size_bytes));
  result = TListInsert<LST_P>(&book->values, item, result);
  if (result < 0) {
    #if SEAM == SCRIPT2_BOOK
    D_COUT("\nFailed to insert into List with error " << result << ':' <<
      CrabsErrorSTR(result));
    D_COUT_LIST(&book->values);
    D_COUT("\n\nList memory: &book->values.size_bytes:" << *&book->values.size_bytes << '\n');
    D_COUT(Charsf(&book->values, &book->values.size_bytes));
    //D_COUT("After:\n" << Charsf(book, book->values.size_bytes));
    #endif
    D_ASSERT(result > 0);
    TLoomPop<LOM_P>(keys);
  }
  //D_COUT("After:\n" << Charsf(book, book->values.size_bytes));
  return result;
}
template<typename T, BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, const CHT* key, T item,
    ISY index = PSH) {
  return TBookInsert<T, BOK_P>(book, TBookKeys<BOK_P>(book), key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, 
    ISA item) {
  return TBookInsert<ISA, BOK_P>(book, keys, key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, const CHT* key, ISA item) {
  return TBookInsert<ISA, BOK_P>(book, TBookKeys<BOK_P>(book), key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, 
    IUA item) {
  return TBookInsert<ISA, BOK_P>(book, keys, key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, const CHT* key, IUA item) {
  return TBookInsert<ISA, BOK_P>(book, TBookKeys<BOK_P>(book), key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, 
    ISB item) {
  return TBookInsert<ISB, BOK_P>(book, keys, key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, const CHT* key, ISB item) {
  return TBookInsert<ISB, BOK_P>(book, TBookKeys<BOK_P>(book), key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, 
    IUB item) {
  return TBookInsert<ISB, BOK_P>(book, keys, key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, const CHT* key, IUB item) {
  return TBookInsert<ISB, BOK_P>(book, TBookKeys<BOK_P>(book), key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, 
    ISC item) {
  return TBookInsert<ISC, BOK_P>(book, keys, key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, const CHT* key, ISC item) {
  return TBookInsert<ISC, BOK_P>(book, TBookKeys<BOK_P>(book), key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, 
    IUC item) {
  return TBookInsert<ISC, BOK_P>(book, keys, key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, const CHT* key, IUC item) {
  return TBookInsert<ISC, BOK_P>(book, TBookKeys<BOK_P>(book), key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, 
    ISD item) {
  return TBookInsert<ISD, BOK_P>(book, keys, key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, const CHT* key, ISD item) {
  return TBookInsert<ISD, BOK_P>(book, TBookKeys<BOK_P>(book), key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, IUD item) {
  return TBookInsert<IUD, BOK_P>(book, keys, key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, const CHT* key, IUD item) {
  return TBookInsert<IUD, BOK_P>(book, TBookKeys<BOK_P>(book), key, item);
}
#if USING_FPC == YES_0
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, 
    FPC item) {
  return TBookInsert<FPC, BOK_P>(book, keys, key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, const CHT* key, FPC item) {
  return TBookInsert<FPC, BOK_P>(book, TBookKeys<BOK_P>(book), key, item);
}
#endif
#if USING_FPD == YES_0
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, 
    FPD item) {
  return TBookInsert<FPD, BOK_P>(book, keys, key, item);
}
template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, const CHT* key, FPD item) {
  return TBookInsert<FPD, BOK_P>(book, TBookKeys<BOK_P>(book), key, item);
}
#endif

/* Adds a key-value tuple to the end of the Book.
@return The index upon success or -1 upon failure. */
template<BOK_A>
inline ISY TBookInsertFrom(TBook<BOK_P>* book, TLoom<LOM_P>* keys, const CHT* key, 
                       DT type, const void* value, ISY index = PSH) {
  D_COUT("\nAdding \"" << key << "\" type:" << ATypef(type) << ":0d" << type <<
         ":0x" << Hexf(type) << ":\'" << CHA(type) << "\' value(offset):" <<
         TDelta<>(book, value));
  //D_COUT("\n\nList memory before:\n" <<
  //  Charsf(&book->values, *&book->values.size_bytes));
  auto result = TListInsert<LST_P>(&book->values, type, value, index);
  D_COUT_LIST(&book->values);
  if (result < 0)
    return result;
  auto key_index = TLoomInsert<LOM_P>(keys, key, index);
  if (key_index < 0) 
    TListRemove<LST_P>(&book->values, index);
  return key_index;
}
template<BOK_A>
inline ISY TBookInsertFrom(TBook<BOK_P>* book, TLoom<LOM_P>* keys, 
    const CHT* key, DT type, ISZ value_offset, ISY index = PSH) {
  return TBookInsert<BOK_P>(book, keys, key, type, 
    TPtr<>(&book->values, value_offset), index);
}
template<BOK_A>
inline ISY TBookInsertFrom(TBook<BOK_P>* book, const CHT* key, DT type,
    const void* value, ISY index = PSH) {
  return TBookInsert<BOK_P>(book, TBookKeys<BOK_P>(book), key, type, 
                            value, index);
}
template<BOK_A>
inline ISY TBookInsertFrom(TBook<BOK_P>* book, const CHT* key, DT type,
    ISZ value_offset, ISY index = PSH) {
  return TBookInsert<BOK_P>(book, TBookKeys<BOK_P>(book), key, type, 
                            value_offset, index);
}

template<BOK_A>
inline ISY TBookInsert(TBook<BOK_P>* book, TATypeKV<ISZ, DT, CHT> item, 
                       ISY index = PSH) {
  return TBookInsert<BOK_P>(book, item.key, item.tv.type, 
                            TPtr<>(book, item.tv.value));
}

/* Adds all of the items from the source to the book. */
template<BOK_A>
TBook<BOK_P>* TBookAdd(TBook<BOK_P>* book, const TBook<BOK_P>* source) {
  auto src_values = &source->values;
  auto src_size = src_values->size_bytes;
  auto src_top = src_values->top;
  ISY src_count_max = ISY(src_values->map.count_max),
      src_count     = ISY(src_values->map.count);
  D_COUT("\nAdding " << src_count << " of " << src_count_max << 
    " max items...\nsource:\n");
  D_COUT_BOOK(source);
  D_ASSERT(src_count >= 0 && src_count <= src_count_max && src_top > 0);
  TLoom<LOM_P>* keys     = TBookKeys<BOK_P>(book);
  const TLoom<LOM_P>* src_keys = TBookKeys<BOK_P>(source);
  const ISZ* src_keys_map      = TBookKeysMap<BOK_P>(source) + 1;
  const ISZ* src_values_map    = TBookValuesMap<BOK_P>(source) + 1;
  const DT * src_types         = TBookTypes<BOK_P>(source, src_count_max) + 1;
  for (ISY i = 1; i < src_count; ++i) {
    D_COUT("\n\ni:" << i);
    const CHT* key    = TPtr<CHT>(src_keys, *src_keys_map++);
    ISZ value_offset  = *src_values_map++;
    DT  type          = *src_types++;
    ISY result        = TBookInsertFrom<BOK_P>(book, keys, key, type,
      TPtr<>(&book->values, value_offset));
    const CHA* dez_nutz = TErrorST<CHA, ISY>(result);
    D_COUT("\nResult:" << result << ' ' << (result < 0 ? dez_nutz : " "));
    D_ASSERT(result >= 0);
  }
  return book;
}

/* Doubles the size and count_max of the book.
@return Returns nil if the size is greater than the amount of memory that
can fit in type ISW, the unaltered socket pointer if the Stack has grown to the
size upper bounds, or a new dynamically allocated socket upon failure. */
template<BOK_A>
BOL TBookGrow(Autoject& obj) {
  D_COUT("\n\nGrowing Book...");
  /* Grow Algoirhm.
  1. Check if we can grow and if so, create a new block of memory.
  2. Copy the Loom.
  3. Copy the List. */
  auto origin = obj.origin;
  D_ASSERT(origin);
  auto source    = TPtr<TBook<BOK_P>>(origin);
  auto size      = source->values.size_bytes;
  auto top       = source->values.top;
  ISY  count_max = ISY(source->values.map.count_max),
       count     = ISY(source->values.map.count);
  D_COUT("\nsize:" << size << " top:" << top << " count_max:" << count_max << 
         " count:" << count);
  auto size_new = ATypeGrow(size);
  if (!ATypeCanGrow(size, size_new)) {
    D_COUT("\n\nError: keys_size cannot grow! keys_size:" << size <<
      " keys_size_new:" << size_new);
    return false;
  }
  auto count_max_new = ATypeGrow(count_max);
  if (!ATypeCanGrow(count_max, count_max_new)) {
    D_COUT("\n\nError: count_max cannot grow! count:" << count_max << 
           " count_max_new:" << count_max_new);
    return false;
  }
  auto keys_size = TBookKeys<BOK_P>(source)->size_bytes;
  auto keys_size_new = ATypeGrow(keys_size);
  if (!ATypeCanGrow(keys_size, keys_size_new)) {
    D_COUT("\n\nError: keys_size cannot grow! keys_size:" << keys_size << 
           " keys_size_new:" << keys_size_new);
    return false;
  }
  /*
#if D_THIS
  D_COUT("\n\n\n*******\nsize_new:" << size_new << 
         " count_max:" << count_max_new << " keys_size_new:" << keys_size_new);
  D_COUT("\n\nBefore:\n");
  D_COUT_BOOK(source);
  D_COUT(Charsf(source, source->values.size_bytes));
#endif*/
  IUW* origin_new = obj.ram(nullptr, size_new);
  D_COUT("\n\n*TPtr<ISZ>(origin_new):" << *TPtr<ISZ>(origin_new) << 
         " size_new:" << size_new);
  auto destination = TPtr<TBook<BOK_P>>(origin_new);
  //D_OBJ_ORIGIN_WIPE(TPtr<ISZ>(origin_new));
  TBookInit<BOK_P>(destination, count_max_new, keys_size_new);
  TBookAdd<BOK_P>(destination, source);
  obj.origin = origin_new;
  D_COUT("\n\nFinished growing. :-)\n\n");
  D_COUT_BOOK(TPtr<TBook<BOK_P>>(obj.origin));
  return true;
}

/* Adds a string to the end of the Book, auto-growing if neccissary.
@return The index upon success or -1 if the obj can't grow anymore.
@todo Verify copmile size of this function isolated and in the AArray class. */
template<typename T, BOK_A, typename BUF>
ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, T item,
                ISY index = PSH) {
  if (!key) return -ErrorInputNil;
  auto book = obj.OriginAs<TBook<BOK_P>*>();
  //D_COUT("\nAdding:\"" << item << "book->values.size_bytes:" << 
  //       book->values.size_bytes << 
  //       "\nBefore: obj.OriginAs<TBook<BOK_P>*>()->values.size_bytes:" << 
  //       obj.OriginAs<TBook<BOK_P>*>()->values.size_bytes);
  ISY result = TBookInsert<T, BOK_P>(book, key, item, index);
  //D_COUT("\n\nAfter: obj.OriginAs<TBook<BOK_P>*>()->values.size_bytes:" << 
  //  obj.OriginAs<TBook<BOK_P>*>()->values.size_bytes);
  //D_COUT("\n\nTBookInsert::CrabsErrorSTR(result):" << CrabsErrorSTR(result) << ':' << 
  //       result << '\n');
  while (result < 0) {
    if (!TBookGrow<BOK_P>(obj.AJT())) {
      //D_COUT("\n\nFailed to grow, personally.\n\n");
      //D_COUT("\n\n\n!!!obj.OriginAs<TBook<BOK_P>*>()->values.size_bytes:" <<    
      //       obj.OriginAs<TBook<BOK_P>*>()->values.size_bytes << 
      //       "\n!!!book->values.size-bytes:" << book->values.size_bytes);
      return -ErrorBufferOverflow;
    }
    book = obj.OriginAs<TBook<BOK_P>*>();
    result = TBookInsert<T, BOK_P>(book, key, item, index);
    if (result < 0) {
      D_COUT("\n\n\nFailed to insert into book:" << result << ' ' <<
             CrabsErrorSTR(result));
      auto keys = TBookKeys<BOK_P>(TPtr<TBook<BOK_P>>(obj.This()));
      D_COUT_LOOM(keys);
    }
    D_COUT("\ndez nutz baby!!!");
    D_COUT('\n');
  }
  return result;
}
template<BOK_A, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISA item,
  ISY index) {
  return TBookInsert<ISA, BOK_P, BUF>(obj, key, item, index);
}
template<BOK_A, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUA item,
  ISY index) {
  return TBookInsert<IUA, BOK_P, BUF>(obj, key, item, index);
}
template<BOK_A, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISB item,
  ISY index) {
  return TBookInsert<ISB, BOK_P, BUF>(obj, key, item, index);
}
template<BOK_A, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUB item,
  ISY index) {
  return TBookInsert<IUB, BOK_P, BUF>(obj, key, item, index);
}
template<BOK_A, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISC item,
  ISY index = PSH) {
  return TBookInsert<ISC, BOK_P, BUF>(obj, key, item, index);
}
template<BOK_A, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUC item,
  ISY index = PSH) {
  return TBookInsert<IUC, BOK_P, BUF>(obj, key, item, index);
}
template<BOK_A, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISD item,
  ISY index = PSH) {
  return TBookInsert<ISD, BOK_P, BUF>(obj, key, item, index);
}
template<BOK_A, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUD item,
  ISY index = PSH) {
  return TBookInsert<IUD, BOK_P, BUF>(obj, key, item, index);
}
#if USING_FPC == YES_0
template<BOK_A, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, FPC item,
  ISY index = PSH) {
  return TBookInsert<FPC, BOK_P, BUF>(obj, key, item, index);
}
#endif
#if USING_FPD == YES_0
template<BOK_A, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, FPD item,
  ISY index = PSH) {
  return TBookInsert<FPD, BOK_P, BUF>(obj, key, item, index);
}
#endif

/* Removes the given index from the Book.
@return The index upon success or -1 upon failure. */
template<BOK_A>
void* TBookListRemove(TBook<BOK_P>* book, ISY index) {
  if (index < 1) return nullptr;
  TList<LST_P>* list = &book->values;
  ISY count = ISY(list->map.count);
  ISZ* offsets = TListValuesMap<ISZ>(list);
  TStackRemove<ISZ, ISZ>(offsets, count, index);
  TStackRemove<DTB, ISZ>(TListTypes<ISZ, DTB>(list), count, index);
  return offsets + index;
}

/* Removes the given index from the Book.
@return The index upon success or -1 upon failure. */
template<BOK_A>
void* TBookRemove(TBook<BOK_P>* book, ISY index) {
  ISY result = TLoomRemove<BOK_P>(TBookKeys<BOK_P>(book), index);
  if (!result) return nullptr;
  return TBookListRemove<BOK_P>(book, index);
}

/* Removes the given key from the Book.
@return Nil upon failure or a pointer to the item removed upon success. */
template<BOK_A>
void* TBookRemove(TBook<BOK_P>* book, const CHT* key) {
  ISY index = TLoomFind<BOK_P>(TBookKeys<BOK_P>(book), key);
  if (index < 0) return index;
  TLoomRemove<BOK_P>(TBookKeys<BOK_P>(book), index);
  return TBookListRemove<BOK_P>(book, index);
}

/* Adds a string to the end of the Book.
@return The index upon success or -1 upon failure. */
template<BOK_A>
ISZ TBookPop(TBook<BOK_P>* book) {
  return TBookRemove<BOK_P>(book, TBookKeys<BOK_P>(book).map.count - 1);
}

template<BOK_A, typename BUF>
ISZ TBookCharCount(TBook<BOK_P>* book) {
  return (ISZ)(TBookEnd<BOK_P>(book) - TBookStart<BOK_P>(book));
}
template<BOK_A, typename BUF>
BOL TBookWrite(TBook<BOK_P>* destination, TBook<BOK_P>* soure) {
  return true;
}

/* Adds a string to the end of the Book.
@return The index upon success or -1 upon failure. */
template<BOK_A>
CHT* TBookPop(TBook<BOK_P>* book) {
  if (TBookKeys<BOK_P>(book).count == 0) return nullptr;
  ISZ offset = TStackPop<ISZ, ISZ>(TBookKeys<BOK_P>(book)), top = book->top;
  book->top = offset;
  return TPtr<CHT>(ISW(book) + offset);
}

/* Searches for the given string in the book.
@return -1 if the book doesn't contain the string or the index if it does. */
template<BOK_A>
ISZ TBookFind(TBook<BOK_P>* book, const CHT* string) {
  D_ASSERT(book);
  D_ASSERT(string);
  return TLoomFind<CHT, ISZ>(TBookKeys<BOK_P>(book), string);
}

/* An ASCII Book Autoject.
@code
ABook<BOK_A, 1024, TBuf<>>
@endcode */
template<BOK_A, ISZ SizeInit = 512, 
          typename BUF = TBUF<SizeInit, CHT, ISZ, TString<ISN>>>
class ABook {
  AArray<IUA, ISZ, BUF> obj_;  //< An Auto-Array object.
 public:

  static constexpr DTB Type() {
    enum {
      //PODBits = _NIL,
      VTBits = 1 << ATypeVTBit0,
      SWBits = CBitCount<ISZ>() << ATypeSWBit0,
      MTBits = CATypeCH<ISY>() << ATypeMTBit0
    };
    return MTBits | SWBits | VTBits; // | PODBits;
  }
  enum {
    SizeBytesDefault = CBookDefaultSize<BOK_P>(),
    CountMaxDefault = SizeBytesDefault >> -BookDefaultCountMaxFractionShift,
    BitchWhat_DEZ_NUTZ_BABY = Type()
  };

  ABook(ISY count_max = BookDefaultCountMaxFractionShift,
        ISZ size_keys = BookDefaultKeysFractionShift)
    : obj_(SizeInit, TRAMFactory<Type(), ISZ>().Init<BUF>()) {
    TBookInit<BOK_P>(This(), count_max, size_keys);
  }

  /* Constructs a Book on the Heap.
  @param factory RAMFactory to call when the String overflows. */
  ABook(RAMFactory ram, 
        ISY count_max = BookDefaultCountMaxFractionShift,
        ISZ size_keys = BookDefaultKeysFractionShift)
      : obj_(ram) {
    TBookInit<BOK_P>(This(), count_max);
  }

  /* Returns the size in elements. */
  inline ISZ Size() { return obj_.Size(); }

  /* Shorthand way to get the TBook->keys List. */
  inline TList<LST_P>* Values() { return &This()->values; }

  /* Gets the Keys struct. */
  inline TLoom<LOM_P>* Keys() { return TBookKeys<BOK_P>(This()); }

  /* Returns the size in bytes. */
  inline ISZ SizeBytes() { return Values()->size_bytes; }

  /* Returns the size in words. */
  inline ISZ SizeWords() { return obj_.SizeWords() >> ALUSizeLog2; }

  /* Returns the number of keys. */
  inline ISZ Count() { return Values()->map.count; }

  /* Returns the maximum number of keys. */
  inline ISZ CountMax() { return Values()->map.count_max; }

  /* Inserts the key and item on into the Loom and List at the given index.
  @return The index of the string in the Book. */
  inline ISY Insert(const CHT* key, ISA item, ISY index = PSH) {
    return TBookInsert<BOK_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUA item, ISY index = PSH) {
    return TBookInsert<BOK_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISB item, ISY index = PSH) {
    return TBookInsert<BOK_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUB item, ISY index = PSH) {
    return TBookInsert<BOK_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISC item, ISY index = PSH) {
    return TBookInsert<BOK_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUC item, ISY index = PSH) {
    return TBookInsert<BOK_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISD item, ISY index = PSH) {
    return TBookInsert<BOK_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUD item, ISY index = PSH) {
    return TBookInsert<BOK_P, BUF>(AJT_ARY(), key, item, index);
  }
#if USING_FPC == YES_0
  inline ISY Insert(const CHT* key, FPC item, ISY index = PSH) {
    return TBookInsert<BOK_P, BUF>(AJT_ARY(), key, item, index);
  }
#endif
#if USING_FPD == YES_0
  inline ISY Insert(const CHT* key, FPD item, ISY index = PSH) {
    return TBookInsert<BOK_P, BUF>(AJT_ARY(), key, item, index);
  }
#endif
  inline ISY Insert(const CHT* key, const CHT* item, ISY index = PSH) {
    return TBookInsert<BOK_P, BUF>(AJT_ARY(), key, item, index);
  }

  /* Removes the string at the given index from the Book. */
  inline void* Remove(ISY index) { return TBookRemove<BOK_P>(This(), index); }

  /* Removes the string at the given index from the Book. */
  inline void* Remove(const CHT* key) {
    return TBookRemove<BOK_P>(This(), key);
  }

  /* Removes the string at the given index from the Book. */
  inline ISZ Pop() { return TBookRemove<BOK_P>(This()); }

  /* Gets the string at the given index. */
  inline CHT* Get(ISY index) { return TBookATypeValue<BOK_P>(This(), index); }

  /* Searches for the given string.
  @return -1 if the Book doesn't contain the string or the index if it does. */
  inline ISZ Find(const CHT* string) {
    return TBookFind<BOK_P>(This(), string);
  }

  /* Gets the Autoject. */
  inline Autoject AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array. */
  inline AArray<IUA, ISZ, BUF>& AJT_ARY() { return obj_; }

  /* Gets the ASCII Object. */
  inline TBook<BOK_P>* This() { return obj_.OriginAs<TBook<BOK_P>*>(); }

  /* Prints this object to the Printer. */
  template<typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TBookPrint<Printer, BOK_P>(o, This());
  }

  /* Prints this object to the stdout. */
  inline void COut() { PrintTo<_::COut>(_::StdOut()); }
};

}  //< namespace _
#endif
#endif