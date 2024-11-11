// Copyright Kabuki Starship� <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_BOOK_CODE
#define SCRIPT2_BOOK_CODE
#include "List.hpp"
#if SEAM >= SCRIPT2_BOOK
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
The Loom datatype stores the bytes, which includes the size of the 
Keys Loom and the Values List. The Keys Loom is an array of strings that 
stores the Book Keys. The Values List is a list of type-value tupes that 
correspond to the key indexes.

The first element of every List ist a Loom (Array of Strings) that stores
the keys.

@code
+====================================+
|_______   Boofer                    |
|_______ ^ List Value N              |
|_______ | List Value 1              |
|        | Keys Loom (Value 0)       |
|------------------------------------|
|_______   Boofer                    |
|_______ ^ List Value N Type         |
|_______ | List Value 1 Type         |
|        | Loom Type (Type 0)        |
|------------------------------------|
|_______   Boofer                    |
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

#define BOK TBook<CHT, ISZ, ISY, DT>

enum {
  // The number of bits to shift a Book's bytes right by to calculate the 
  // size_keys (Example: size_keys = bytes >> 2).
  BookDefaultKeysFractionShift = -1,
  // The number of bits to shift a Book's bytes right by to calculate the 
  // total (Example: total = bytes >> 5).
  BookDefaultTotalFractionShift = -6,
  BookDefaultLengthKey = 15,
  BookDefaultSizeBytes = 512,
  BookDefaultCount = BookDefaultSizeBytes >> -(BookDefaultKeysFractionShift),
};

/* The minimum count a good with the given template parameters can have. */
template<BOK_A>
constexpr ISY CBookMinCount() {
  return 8 / sizeof(ISZ);
}

/* The minimum size of a Book based on the CCountMin. */
template<BOK_A>
constexpr ISZ CBookMinSize(ISY total) {
  return sizeof(BOK) + total * (sizeof(ISZ) + 2); //< @todo ???
}

/* Gets the default count of a good with the given template parameters. */
template<BOK_A>
constexpr ISZ CBookDefaultCount() {
  return 32;
}

/* Gets the default count of a good with the given template parameters. */
template<BOK_A>
ISY TBookCount(const BOK* book) {
  return book->values.map.count - 1;
}

/* Gets the default count of a good with the given template parameters. */
template<BOK_A>
ISY TBookTotal(const BOK* book) {
  return book->values.map.total - 1;
}

/* Gets the default count of a good with the given template parameters. */
template<BOK_A>
ISY TBookDefaultCount(ISY bytes) {
  return bytes >> 5; // >> 5 to / by 32
}

/* Gets the default size of a Book with the CBookDefaultCount. */
template<BOK_A>
constexpr ISZ CBookDefaultSize(ISY total = CBookDefaultCount<BOK_P>()) {
  if (total < 1) return -1;
  if (total < CBookMinCount<BOK_P>()) 
    total = CBookMinCount<BOK_P>();
  return total * BookDefaultLengthKey * sizeof(CHT);
}

/* Points to the base of the value offsets array. */
template<BOK_A>
inline ISZ* TBookValuesMap(BOK* book) {
  return TListValuesMap<LST_P>(&book->values);
}
template<BOK_A>
inline const ISZ* TBookValuesMap(const BOK* book) {
  return CPtr<ISZ>(TBookValuesMap<BOK_P>(CPtr<BOK>(book)));
}

/* Gets the keys Loom (index 0 of the ASCII List). */
template<BOK_A>
inline TLoom<LOM_P>* TBookKeys(BOK* book) {
  return TPtr<TLoom<LOM_P>>(book, *TBookValuesMap<BOK_P>(book));
}
template<BOK_A>
inline const TLoom<LOM_P>* TBookKeys(const BOK* book) {
  return CPtr<TLoom<LOM_P>>(TBookKeys<BOK_P>(CPtr<BOK>(book)));
}

/* Gets the values List. */
template<BOK_A>
inline ISZ* TBookKeysMap(BOK* book) {
  return TLoomKeysMap<LOM_P>(TBookKeys<BOK_P>(book));
}
template<BOK_A>
inline const ISZ* TBookKeysMap(const BOK* book) {
  return CPtr<ISZ>(TBookKeysMap<BOK_P>(CPtr<BOK>(book)));
}

/* Gets the start of the book as a templated-defined character. */
template<BOK_A>
inline CHT* TBookStart(BOK* book, ISY total) {
  ISZ* top = &TStackStart<ISZ, ISZ>(TBookKeys<BOK_P>(book))[total];
  return TPtr<CHT>(top);
}
template<BOK_A>
inline const CHT* TBookStart(const BOK* book, ISY total) {
  return CPtr<ISZ>(TBookStart<BOK_P>(CPtr<BOK>(book), total));
}

/* Gets the start byte of the book. */
template<BOK_A>
inline CHT* TBookStart(BOK* book) {
  return TBookStart<BOK_P>(book, TBookKeys<BOK_P>(book).total);
}

/* Points to the byte after the last byte of the book's contiguous memory block. */
template<BOK_A>
inline CHA* TBookEnd(BOK* book) {
  return TListEnd<ISZ>(&book->values);
}
template<BOK_A>
inline const ISZ* TBookEnd(const BOK* book) {
  return CPtr<ISZ>(TBookEnd<BOK_P>(CPtr<BOK>(book)));
}

/* Gets the byte after the end of the book's contiguous memory block. */
template<BOK_A>
inline CHA* TBookKeysEnd(BOK* book) {
  return TLoomEnd<LOM_P>(TBookKeys<BOK_P>(book));
}

/* Gets the size of the Book in bytes. */
template<BOK_A>
inline ISZ TBookTotal(BOK* book) {
  return TBookKeys<BOK_P>(book)->map.total;
}
template<BOK_A>
inline const ISZ* TBookTotal(const BOK* book) {
  return CPtr<ISZ>(TBookTotal<BOK_P>(CPtr<BOK>(book)));
}

/* Checks if the book size values result are valid.
You must have enough room in the bytes with given total. */
template<BOK_A>
inline BOL TBookSizesAreValid(ISZ bytes, ISZ size_keys, ISY total) {
  return size_keys <= TListSizeFreeMax<LST_P>(bytes, total);
}

// Freespace left in bytes for the given book's keys Loom and values List.
// @return Returns -1 upon failure.
template<BOK_A>
inline ISZ TBookFreeSpace(BOK* book) {
  D_CHECK_TPTR_RETURN(ISZ, book);
  auto keys = TBookKeys<BOK_P>(book);
  D_CHECK_TPTR_RETURN(ISZ, keys);
  return TListFreeSpace<LST_P>(&book->values) + 
         TLoomFreeSpace<LOM_P>(keys);
}

/* Prints the book to the Printer. */
template<typename Printer, BOK_A>
Printer& TBookPrint(Printer& o, const BOK* book) {
  D_ASSERT_PTR(book);
  if (!PtrIsValid(book))
    return o << "book ptr invalid";
  auto total        = book->values.map.total;
  auto count        = book->values.map.count;
  auto voffsets     = TPtr<ISZ>(book, sizeof(BOK));
  auto types        = TPtr<DT>(voffsets + total);
  auto keys_offset  = *voffsets++;
  auto keys         = TPtr<TLoom<LOM_P>>(book, keys_offset);
  auto keys_size    = keys->bytes;
  auto keys_start   = keys->start;
  D_COUT("\ntotal:" << total << " count:" << count << 
         " keys_size:" << keys_size << " keys_top : " << keys_start);
  D_AVOW(total, keys->map.total);
  D_AVOW(count    , keys->map.count);
  D_COUT_LOOM(keys);
  o << "\nBook<CH" << CSizeCodef<CHT>() << ",IS" << CSizeCodef<ISZ>() << ",IS"
    << CSizeCodef<ISY>() << "> bytes:" << book->values.bytes
    << " total:" << total << " count:" << count << '\n'
    << " list_top:" << book->values.top << " keys_offset:" << keys_offset
    << " keys_free_space:" << TLoomFreeSpace<LOM_P>(keys)
    << " values_free_space:" << TListFreeSpace<ISZ>(&book->values)
    << " keys.bytes:" << keys_size << " keys.top:" << keys_start
    << " TypeOf(keys):" << ATypef(types[0]) << ' ';
  for (ISY i = 1; i < count; ++i) {
    o << '\n' << i << ".) \"" << TLoomGet<LOM_P>(keys, i) << "\" type:";
    auto type    = *(++types);
    auto voffset = *(++voffsets);
    o << ATypef(type) << " voffset:" << voffset << " value:";
  }
  D_COUT(Linef('-') << ' ' << Charsf(book, book->values.bytes));
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
    PODBits = CATypeCH<CHR>(),
    VTBits  = 1 << ATypeVTBit0,
    SWBits  = CBitCount<ISZ>() << ATypeSWBit0,
    MTBits  = CATypeIS<ISY>() << ATypeMTBit0
  };
  return MTBits | SWBits | VTBits | PODBits;
}

/* Initializes the book to the given total using the CBookDefaultSize.
@param bytes The size of the book in bytes.
@param total The maximum number of entries in the book -1 for the keys.
@param size_keys If this number is positive then the value is size of the keys 
Loom in bytes. If the value is negative then it is the number of bits to shift 
the bytes to get the size_keys. */
template<BOK_A>
BOK* TBookInit(BOK* book,
                        ISY total = BookDefaultTotalFractionShift,
                        ISZ size_keys = BookDefaultKeysFractionShift) {
  D_ASSERT(book);
  TList<LST_P>* values = &book->values;
  ISZ bytes = values->bytes;
  D_COUT("\n\nTBookInit bytes: " << bytes << " total:" <<
         total << " size_keys:" << size_keys);
  D_ARRAY_WIPE(&values->top, bytes - sizeof(ISZ));
  if (size_keys < 0) {
    size_keys *= -1;
    if (size_keys >= TBitCount<ISZ>()) {
      D_COUT("\nInvalid total bit shift value.");
      return nullptr;
    }
    size_keys = bytes >> size_keys;
    D_COUT("\nnew size_keys:" << size_keys);
  }
  if (total < 0) {
    total *= -1;
    if (total >= TBitCount<ISZ>()) {
      D_COUT("\nInvalid total bit shift value.");
      return nullptr;
    }
    total = ISY(bytes >> ISZ(total));
    D_COUT("\nnew total:" << total);
  }
  if (!TBookSizesAreValid<BOK_P>(bytes, size_keys, total)) {
    D_COUT("\nInvalid book sizes!");
    return nullptr;
  }
  TListInit<LST_P>(values, bytes, total);
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
  auto result = TLoomInit<LOM_P>(keys, total);
  TLoomInsert<LOM_P>(result, "");
  D_COUT("\nkeys->top:" << keys->start);
  D_COUT("\nTDelta<>(book, TBookKeys<BOK_P>(book)):" << 
         TDelta<>(book, TBookKeys<BOK_P>(book)));
  if (!result) return nullptr;
  D_COUT("\n\nTListInit Post bytes: " << bytes << 
         " total:" << total << 
         "\nBook End  :" << TDelta<>(book, TBookEnd<BOK_P>(book)) <<
         "\nKeys End  :" << TDelta<>(book, TLoomEnd<LOM_P>(keys)) <<
         "\nKeys Start:" << TDelta<>(book, keys) << "\n\nResult:\n");
  D_COUT_BOOK(book);
  return book;
}

/* Gets the element at the given index. */
template<BOK_A>
inline void* TBookValue(BOK* book, ISY index) {
  return TListValue<void, LST_P>(TBookKeys<BOK_P>(book), index);
}
template<BOK_A>
inline const void* TBookValue(const BOK* book, ISY index) {
  return CPtr<DT>(TBookValue<BOK_P>(CPtr<BOK>(book), index));
}

/* Gets the TypeValue tuple the given index.
@param tuple Reference to the return type passed in by reference. */
template<BOK_A>
inline ATypeValue TBookATypeValue(const BOK* book, ISY index) {
  return TListTypeValuePtr<ISZ, DT>(&book->values, index);
}

template<BOK_A>
inline DT* TBookTypes(BOK* book, ISY total) {
  return TListTypes<LST_P>(&book->values, total);
}
template<BOK_A>
inline const DT* TBookTypes(const BOK* book, ISY total) {
  return CPtr<DT>(TBookTypes<BOK_P>(CPtr<BOK>(book), total));
}

/* Gets the key at the given index without doing any error checking. */
template<BOK_A>
inline CHT* TBookKey_NC(BOK* book, ISY index) {
  return TLoomGet_NC<LOM_P>(TBookKeys<BOK_P>(book), index);
}

/* Gets the key at the given index without doing any error checking. */
template<BOK_A>
inline const CHT* TBookKey_NC(const BOK* book, ISY index) {
  return CPtr<CHT>(TBookKey_NC<LOM_P>(CPtr<BOK>(book), index));
}

/* Gets the keys offsets array. */
template<BOK_A>
inline CHT* TBookKeys_NC(BOK* book, ISY index) {
  return TPtr<CHT>(book, *TPtr<ISZ>(book, sizeof(BOK)));
}
template<BOK_A>
inline const CHT* TBookKeys_NC(const BOK* book) {
  auto bok = CPtr<BOK>(TBookKeys<BOK_P>(book));
  return CPtr<CHT>(TBookKeys_NC<LOM_P>(bok));
}

/* Gets the type at the given index without doing any error checking. */
template<BOK_A>
inline DT TBookType_NC(const BOK* book, ISY total, ISY index) {
  return TListType_NC<LST_P>(&book->values, total, index);
}

/* Gets the keys offsets array. */
template<BOK_A>
inline DT* TBookTypes_NC(BOK* book, ISY total) {
  return TPtr<DT>(book, TBookKeys_NC<BOK_P>(book) + total);
}
template<BOK_A>
inline const CHT* TBookTypes_NC(const BOK* book) {
  auto bok = CPtr<BOK>(TBookValuesMap<BOK_P>(book));
  return CPtr<CHT>(TBookTypes_NC<LOM_P>(bok));
}

/* Gets the type at the given index without doing any error checking. */
template<BOK_A>
inline void* TBookValue_NC(BOK* book, ISY index) {
  return TListValue_NC<LST_P>(&book->values, index);
}
template<BOK_A>
inline const void* TBookValue_NC(const BOK* book, ISY index) {
  return CPtr<void>(TBookValue_NC<BOK_P>(CPtr<BOK>(book), index));
}

/* Gets the type at the given index without doing any error checking. */
template<BOK_A>
inline ISZ TBookValueOffset_NC(const BOK* book, ISY index) {
  //return TListValueOffset_NC<LST_P>(&book->values, index);
  return TPtr<ISZ>(book, sizeof(BOK))[index];
}

/* Gets the TypeValue tuple the given index.
@param tuple Reference to the return type passed in by reference. */
template<BOK_A>
inline TATypeKV<ISZ, DT, CHT> TBookTypeKV(const BOK* book, ISY index) {
  auto count = book->values.map.count;
  if (index < 0 || index >= count) 
    return { nullptr, _NIL, 0 };
  return { TBookKey_NC<BOK_P>(book, index), 
           TBookType_NC<BOK_P>(book, book->values.map.total, index),
           TBookValueOffset_NC<BOK_P>(book, index) };
}

/* Adds a key-value tuple to the end of the Book.
@todo Delete this function and replace with void* value.
@return The index upon success or -1 upon failure. */
template<typename T, BOK_A>
inline ISY TBookInsert(BOK* book, TLoom<LOM_P>* keys, const CHT* key, 
    T item, ISY index = PSH) {
  D_CHECK_PTR_TRETURN(ISY, book);
  D_COUT("\nAdding key:\"" << key << "\" item:" << item << " into index:" <<
    index);
  if (index == 0) D_RETURNT(ISY, -ErrorInvalidIndex);
  D_COUT("\nKeys offset:" << TDelta<>(book, keys) << 
         "\nValues offsets:" << TDelta<>(book, TBookValuesMap<BOK_P>(book)));
  ISY result = TLoomInsert<LOM_P>(keys, key, index);
  if (result < 0) {
    D_COUT("\n\n\nFailed to insert into loom:" << result << ' ' << 
           CrabsErrorSTR(result));
    D_COUT_LOOM(keys);
    D_COUT_BOOK(book);
    return -ErrorKeysBooferOverflow;
  }
  result = TListInsert<LST_P>(&book->values, item, result);
  if (result < 0) {
    #if SEAM == SCRIPT2_BOOK
    D_COUT("\nFailed to insert into List with error " << result << ':' <<
      CrabsErrorSTR(result));
    D_COUT_LIST(&book->values);
    D_COUT("\n\nList memory: &book->values.bytes:" << *&book->values.bytes << '\n');
    D_COUT(Charsf(&book->values, &book->values.bytes));
    //D_COUT("After:\n" << Charsf(book, book->values.bytes));
    #endif
    D_ASSERT(result > 0);
    TLoomPop<LOM_P>(keys);
  }
  //D_COUT("After:\n" << Charsf(book, book->values.bytes));
  return result;
}
template<typename T, BOK_A>
inline ISY TBookInsert(BOK* book, const CHT* key, T item,
    ISY index = PSH) {
  return TBookInsert<T, BOK_P>(book, TBookKeys<BOK_P>(book), key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, TLoom<LOM_P>* keys, const CHT* key, 
    ISA item, ISY index = PSH) {
  return TBookInsert<ISA, BOK_P>(book, keys, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, const CHT* key, ISA item, ISY index = PSH) {
  return TBookInsert<ISA, BOK_P>(book, TBookKeys<BOK_P>(book), key, item,
    index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, TLoom<LOM_P>* keys, const CHT* key, 
    IUA item, ISY index = PSH) {
  return TBookInsert<ISA, BOK_P>(book, keys, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, const CHT* key, IUA item, ISY index = PSH) {
  return TBookInsert<ISA, BOK_P>(book, TBookKeys<BOK_P>(book), key, item,
    index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, TLoom<LOM_P>* keys, const CHT* key, 
    ISB item, ISY index = PSH) {
  return TBookInsert<ISB, BOK_P>(book, keys, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, const CHT* key, ISB item, ISY index = PSH) {
  return TBookInsert<ISB, BOK_P>(book, TBookKeys<BOK_P>(book), key, item,
    index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, TLoom<LOM_P>* keys, const CHT* key, 
    IUB item, ISY index = PSH) {
  return TBookInsert<ISB, BOK_P>(book, keys, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, const CHT* key, IUB item, ISY index = PSH) {
  return TBookInsert<ISB, BOK_P>(book, TBookKeys<BOK_P>(book), key, item, 
    index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, TLoom<LOM_P>* keys, const CHT* key, 
    ISC item, ISY index = PSH) {
  return TBookInsert<ISC, BOK_P>(book, keys, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, const CHT* key, ISC item, ISY index = PSH) {
  return TBookInsert<ISC, BOK_P>(book, TBookKeys<BOK_P>(book), key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, TLoom<LOM_P>* keys, const CHT* key, 
    IUC item, ISY index = PSH) {
  return TBookInsert<ISC, BOK_P>(book, keys, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, const CHT* key, IUC item, ISY index = PSH) {
  return TBookInsert<ISC, BOK_P>(book, TBookKeys<BOK_P>(book), key, item,
    index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, TLoom<LOM_P>* keys, const CHT* key, 
    ISD item, ISY index = PSH) {
  return TBookInsert<ISD, BOK_P>(book, keys, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, const CHT* key, ISD item, ISY index = PSH) {
  return TBookInsert<ISD, BOK_P>(book, TBookKeys<BOK_P>(book), key, item, 
    index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, TLoom<LOM_P>* keys, const CHT* key, IUD item, 
  ISY index = PSH) {
  return TBookInsert<IUD, BOK_P>(book, keys, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, const CHT* key, IUD item, ISY index = PSH) {
  return TBookInsert<IUD, BOK_P>(book, TBookKeys<BOK_P>(book), key, item, index);
}
#if USING_FPC == YES_0
template<BOK_A>
inline ISY TBookInsert(BOK* book, TLoom<LOM_P>* keys, const CHT* key, 
    FPC item, ISY index = PSH) {
  return TBookInsert<FPC, BOK_P>(book, keys, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, const CHT* key, FPC item, ISY index = PSH) {
  return TBookInsert<FPC, BOK_P>(book, TBookKeys<BOK_P>(book), key, item, index);
}
#endif
#if USING_FPD == YES_0
template<BOK_A>
inline ISY TBookInsert(BOK* book, TLoom<LOM_P>* keys, const CHT* key, 
    FPD item, ISY index = PSH) {
  return TBookInsert<FPD, BOK_P>(book, keys, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(BOK* book, const CHT* key, FPD item, ISY index = PSH) {
  return TBookInsert<FPD, BOK_P>(book, TBookKeys<BOK_P>(book), key, item, 
    index);
}
#endif

/* Adds a key-value tuple to the end of the Book.
@return The index upon success or -1 upon failure. */
template<BOK_A>
inline ISY TBookInsertFrom(BOK* book, TLoom<LOM_P>* keys, const CHT* key, 
                       DT type, const void* value, ISY index = PSH) {
  D_COUT("\nAdding \"" << key << "\" type:" << ATypef(type) << ":0d" << type <<
         ":0x" << Hexf(type) << ":\'" << CHA(type) << "\' value(offset):" <<
         TDelta<>(book, value));
  //D_COUT("\n\nList memory before:\n" <<
  //  Charsf(&book->values, *&book->values.bytes));
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
inline ISY TBookInsertFrom(BOK* book, TLoom<LOM_P>* keys, 
    const CHT* key, DT type, ISZ value_offset, ISY index = PSH) {
  return TBookInsert<BOK_P>(book, keys, key, type, 
    TPtr<>(&book->values, value_offset), index);
}
template<BOK_A>
inline ISY TBookInsertFrom(BOK* book, const CHT* key, DT type,
    const void* value, ISY index = PSH) {
  return TBookInsert<BOK_P>(book, TBookKeys<BOK_P>(book), key, type, 
                            value, index);
}
template<BOK_A>
inline ISY TBookInsertFrom(BOK* book, const CHT* key, DT type,
    ISZ value_offset, ISY index = PSH) {
  return TBookInsert<BOK_P>(book, TBookKeys<BOK_P>(book), key, type, 
                            value_offset, index);
}

template<BOK_A>
inline ISY TBookInsert(BOK* book, TATypeKV<ISZ, DT, CHT> item, 
                       ISY index = PSH) {
  return TBookInsert<BOK_P>(book, item.key, item.tv.type, 
                            TPtr<>(book, item.tv.value));
}

/* Adds all of the items from the source to the book. */
template<BOK_A>
BOK* TBookAppend(BOK* book, const BOK* source) {
  D_CHECK_PTR_RETURN(book);
  D_CHECK_CPTR_RETURN(BOK, source);
  auto src_values = &source->values;
  auto src_size = src_values->bytes;
  auto src_top = src_values->top;
  ISY src_total = ISY(src_values->map.total),
      src_count     = ISY(src_values->map.count);
  D_COUT("\nAdding " << src_count << " of " << src_total << 
    " max items...\nsource:\n");
  D_COUT_BOOK(source);
  D_ASSERT(src_count >= 0 && src_count <= src_total && src_top > 0);
  TLoom<LOM_P>* keys     = TBookKeys<BOK_P>(book);
  const TLoom<LOM_P>* src_keys = TBookKeys<BOK_P>(source);
  const ISZ* src_keys_map      = TBookKeysMap<BOK_P>(source) + 1;
  const ISZ* src_values_map    = TBookValuesMap<BOK_P>(source) + 1;
  const DT * src_types         = TBookTypes<BOK_P>(source, src_total) + 1;
  for (ISY i = 1; i < src_count; ++i) {
    D_COUT("\n\ni:" << i);
    const CHT* key    = TPtr<CHT>(src_keys, *src_keys_map++);
    ISZ value_offset  = *src_values_map++;
    DT  type          = *src_types++;
    ISY result        = TBookInsertFrom<BOK_P>(book, keys, key, type,
      TPtr<>(&book->values, value_offset));
    const CHA* dez_nutz = TAErrors<CHA, ISY>(result);
    D_COUT("\nResult:" << result << ' ' << (result < 0 ? dez_nutz : " "));
    D_ASSERT(result >= 0);
  }
  return book;
}

/* Doubles the size and total of the book.
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
  auto source    = TPtr<BOK>(origin);
  auto size      = source->values.bytes;
  auto top       = source->values.top;
  ISY  total = ISY(source->values.map.total),
       count     = ISY(source->values.map.count);
  D_COUT("\nsize:" << size << " top:" << top << " total:" << total << 
         " count:" << count);
  auto size_new = ATypeGrow(size);
  if (!ATypeCanGrow(size, size_new)) {
    D_COUT("\n\nError: keys_size cannot grow! keys_size:" << size <<
      " keys_size_new:" << size_new);
    return false;
  }
  auto total_new = ATypeGrow(total);
  if (!ATypeCanGrow(total, total_new)) {
    D_COUT("\n\nError: total cannot grow! count:" << total << 
           " total_new:" << total_new);
    return false;
  }
  auto keys_size = TBookKeys<BOK_P>(source)->bytes;
  auto keys_size_new = ATypeGrow(keys_size);
  if (!ATypeCanGrow(keys_size, keys_size_new)) {
    D_COUT("\n\nError: keys_size cannot grow! keys_size:" << keys_size << 
           " keys_size_new:" << keys_size_new);
    return false;
  }
  IUW* origin_new = obj.ram(nullptr, size_new);
  D_COUT("\n\n*TPtr<ISZ>(origin_new):" << *TPtr<ISZ>(origin_new) << 
         " size_new:" << size_new);
  auto destination = TPtr<BOK>(origin_new);
  TBookInit<BOK_P>(destination, total_new, keys_size_new);
  TBookAppend<BOK_P>(destination, source);
  obj.origin = origin_new;
  D_COUT("\n\nFinished growing. :-)\n\n");
  D_COUT_BOOK(TPtr<BOK>(obj.origin));
  return true;
}

/* Adds a string to the end of the Book, auto-growing if neccissary.
@return The index upon success or -1 if the obj can't grow anymore.
@todo Verify copmile size of this function isolated and in the AArray class. */
template<typename T, BOK_A>
ISY TBookInsert(Autoject& obj, const CHT* key, T item, ISY index = PSH) {
  D_CHECK_PTR_TRETURN(ISY, key);
  ISY result = TBookInsert<T, BOK_P>(TPtr<BOK>(obj.origin), key, item, index);
  while (result < 0) {
    if (!TBookGrow<BOK_P>(obj)) {
      return -ErrorBooferOverflow;
    }
    BOK* book = TPtr<BOK>(obj.origin);
    result = TBookInsert<T, BOK_P>(book, key, item, index);
    if (result < 0) {
      D_COUT("\n\n\nFailed to insert into book:" << result << ' ' <<
             CrabsErrorSTR(result));
      D_COUT_LOOM(TBookKeys<BOK_P>(book));
      return result;
    }
    D_COUT("\ndez nutz baby!!!\n");
  }
  return result;
}
template<BOK_A>
inline ISY TBookInsert(Autoject& obj, const CHT* key, ISA item,
  ISY index = PSH) {
  return TBookInsert<ISA, BOK_P>(obj, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(Autoject& obj, const CHT* key, IUA item,
  ISY index = PSH) {
  return TBookInsert<IUA, BOK_P>(obj, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(Autoject& obj, const CHT* key, ISB item,
  ISY index = PSH) {
  return TBookInsert<ISB, BOK_P>(obj, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(Autoject& obj, const CHT* key, IUB item,
  ISY index = PSH) {
  return TBookInsert<IUB, BOK_P>(obj, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(Autoject& obj, const CHT* key, ISC item,
  ISY index = PSH) {
  return TBookInsert<ISC, BOK_P>(obj, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(Autoject& obj, const CHT* key, IUC item,
  ISY index = PSH) {
  return TBookInsert<IUC, BOK_P>(obj, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(Autoject& obj, const CHT* key, ISD item,
  ISY index = PSH) {
  return TBookInsert<ISD, BOK_P>(obj, key, item, index);
}
template<BOK_A>
inline ISY TBookInsert(Autoject& obj, const CHT* key, IUD item,
  ISY index = PSH) {
  return TBookInsert<IUD, BOK_P>(obj, key, item, index);
}
#if USING_FPC == YES_0
template<BOK_A>
inline ISY TBookInsert(Autoject& obj, const CHT* key, FPC item,
  ISY index = PSH) {
  return TBookInsert<FPC, BOK_P>(obj, key, item, index);
}
#endif
#if USING_FPD == YES_0
template<BOK_A>
inline ISY TBookInsert(Autoject& obj, const CHT* key, FPD item,
  ISY index = PSH) {
  return TBookInsert<FPD, BOK_P>(obj, key, item, index);
}
#endif

/* Removes the given index from the Book.
@return The index upon success or -1 upon failure. */
template<BOK_A>
void* TBookListRemove(BOK* book, ISY index) {
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
void* TBookRemove(BOK* book, ISY index) {
  ISY result = TLoomRemove<BOK_P>(TBookKeys<BOK_P>(book), index);
  if (!result) return nullptr;
  return TBookListRemove<BOK_P>(book, index);
}

/* Removes the given key from the Book.
@return Nil upon failure or a pointer to the item removed upon success. */
template<BOK_A>
void* TBookRemove(BOK* book, const CHT* key) {
  ISY index = TLoomFind<BOK_P>(TBookKeys<BOK_P>(book), key);
  if (index < 0) return index;
  TLoomRemove<BOK_P>(TBookKeys<BOK_P>(book), index);
  return TBookListRemove<BOK_P>(book, index);
}

/* Adds a string to the end of the Book.
@return The index upon success or -1 upon failure. */
template<BOK_A>
ISZ TBookPop(BOK* book) {
  return TBookRemove<BOK_P>(book, TBookKeys<BOK_P>(book).map.count - 1);
}

template<BOK_A>
ISZ TBookCharCount(BOK* book) {
  return (ISZ)(TBookEnd<BOK_P>(book) - TBookStart<BOK_P>(book));
}
template<BOK_A>
BOL TBookWrite(BOK* destination, BOK* soure) {
  return true;
}

/* Adds a string to the end of the Book.
@return The index upon success or -1 upon failure. */
template<BOK_A>
CHT* TBookPop(BOK* book) {
  if (TBookKeys<BOK_P>(book).count == 0) return nullptr;
  ISZ offset = TStackPop<ISZ, ISZ>(TBookKeys<BOK_P>(book)), top = book->top;
  book->top = offset;
  return TPtr<CHT>(ISW(book) + offset);
}

/* Searches for the given string in the book.
@return -1 if the book doesn't contain the string or the index if it does. */
template<BOK_A>
ISZ TBookFind(BOK* book, const CHT* string) {
  D_ASSERT(book);
  D_ASSERT(string);
  return TLoomFind<CHT, ISZ>(TBookKeys<BOK_P>(book), string);
}

/* An ASCII Book Autoject.
@code
ABook<BOK_A, 1024, TBuf<>>All
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
    TotalDefault = SizeBytesDefault >> -BookDefaultTotalFractionShift,
    BitchWhat_DEZ_NUTZ_BABY = Type()
  };

  ABook(ISY total = BookDefaultTotalFractionShift,
        ISZ size_keys = BookDefaultKeysFractionShift)
    : obj_(SizeInit, TRAMFactory<Type(), ISZ>().Init<BUF>()) {
    TBookInit<BOK_P>(This(), total, size_keys);
  }

  /* Constructs a Book on the Heap.
  @param factory RAMFactory to call when the String overflows. */
  ABook(RAMFactory ram, 
        ISY total = BookDefaultTotalFractionShift,
        ISZ size_keys = BookDefaultKeysFractionShift)
      : obj_(ram) {
    TBookInit<BOK_P>(This(), total);
  }

  /* Returns the size in elements. */
  inline ISZ Size() { return obj_.Size(); }

  /* Shorthand way to get the TBook->keys List. */
  inline TList<LST_P>* Values() { return &This()->values; }

  /* Gets the Keys struct. */
  inline TLoom<LOM_P>* Keys() { return TBookKeys<BOK_P>(This()); }

  /* Returns the size in bytes. */
  inline ISZ SizeBytes() { return Values()->bytes; }

  /* Returns the size in words. */
  inline ISZ SizeWords() { return obj_.SizeWords() >> WordSizeLog2; }

  /* Returns the number of keys. */
  inline ISZ Count() { return Values()->map.count; }

  /* Returns the maximum number of keys. */
  inline ISZ Total() { return Values()->map.total; }

  /* Inserts the key and item on into the Loom and List at the given index.
  @return The index of the string in the Book. */
  inline ISY Insert(const CHT* key, ISA item, ISY index = PSH) {
    return TBookInsert<ISA, BOK_P>(AJT(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUA item, ISY index = PSH) {
    return TBookInsert<IUA, BOK_P>(AJT(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISB item, ISY index = PSH) {
    return TBookInsert<ISB, BOK_P>(AJT(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUB item, ISY index = PSH) {
    return TBookInsert<IUB, BOK_P>(AJT(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISC item, ISY index = PSH) {
    return TBookInsert<ISC, BOK_P>(AJT(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUC item, ISY index = PSH) {
    return TBookInsert<IUC, BOK_P>(AJT(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISD item, ISY index = PSH) {
    return TBookInsert<ISD, BOK_P>(AJT(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUD item, ISY index = PSH) {
    return TBookInsert<IUD, BOK_P>(AJT(), key, item, index);
  }
#if USING_FPC == YES_0
  inline ISY Insert(const CHT* key, FPC item, ISY index = PSH) {
    return TBookInsert<FPC, BOK_P>(AJT(), key, item, index);
  }
#endif
#if USING_FPD == YES_0
  inline ISY Insert(const CHT* key, FPD item, ISY index = PSH) {
    return TBookInsert<FPD, BOK_P>(AJT(), key, item, index);
  }
#endif
  inline ISY Insert(const CHT* key, const CHT* item, ISY index = PSH) {
    return TBookInsert<BOK_P>(AJT(), key, item, index);
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
  inline Autoject& AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array.
  inline AArray<IUA, ISZ, BUF>& AJT() { return obj_; } */

  /* Gets the ASCII Object. */
  inline BOK* This() { return obj_.OriginAs<BOK*>(); }

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
