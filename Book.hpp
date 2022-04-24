/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Book.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
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

#undef  TPARAMS
#define TPARAMS CHT, ISZ, ISY, DT
#undef  TARGS
#define TARGS \
  typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM, typename DT = DT2

/* @ingroup Book
@brief A contiguous memory Associative List composed of a Loom and list.
The Loom datatype stores the size_bytes, which includes the size of the 
Keys Loom and the Values List. The Keys Loom is an array of strings that 
stores the Book Keys. The Values List is a list of type-value tupes that 
correspond to the key indexes.

The first element of every List ist a Loom (Array of Strings) that stores
the keys.

@code
+==============================+
|_______   Buffer              |
|_______ ^ Value N-1           |
|        | Value 0             |
|        |  Keys Loom          | 
|------------------------------|
|_______   Buffer              |
|_______ ^ Type of Value N-1   |
|        | Type of Value 0     |
|        |  ASCII Loom Type    |
|------------------------------|
|_______   Buffer              |
|_______ ^ Offset to Value N-1 |
|        | Offset to Value 0   |
|        |    Keys Loom        |
+==============================+  ^ Up in
|         TList Struct         |  |
+==============================+  + 0xN
@endcode */
template <TARGS>
struct TBook {
  TList<ISZ> values;  //< The type-value list that corresponsd to the key indexes.
};

/* The minimum count a good with the given template parameters can have. */
template <TARGS>
constexpr ISZ CBookCountMin() {
  return 8 / sizeof(ISZ);
}

/* The minimum size of a Book based on the CCountMin. */
template <TARGS>
constexpr ISZ CBookSizeMin(ISY count_max) {
  return sizeof(TBook<TPARAMS>) + count_max * (sizeof(ISZ) + 2);
}

/* The minimum size of a Book based on the CCountMin. */
template <TARGS>
constexpr ISZ CBookSizeMin() {
  return CBookSizeMin<TPARAMS>(CBookCountMin<TPARAMS>());
}

/* Calculates the minimum size of a Book with */
template<TARGS>
ISZ TBookSizeMin(TBook<TPARAMS>* book) {
  return 0;
}

/* Gets the default average string length.
@note Pulled number out of a hat. */
template <TARGS>
constexpr ISZ TBookDefaultAverageStringLength() {
  return 15;
}

/* Gets the default count of a good with the given template parameters. */
template <TARGS>
constexpr ISZ CBookDefaultCount() {
  return 32;
}

/* Gets the default size of a Book with the CBookDefaultCount. */
template <TARGS>
constexpr ISZ CBookDefaultSize(ISY count_max = CBookDefaultCount<TPARAMS>()) {
  if (count_max < 1) return -1;
  ISZ foo_baby_yeah_isms = count_max * TBookDefaultAverageStringLength<TPARAMS>() 
        * sizeof(CHT);
  return foo_baby_yeah_isms;
  //return foo_baby_yeah_isms + (-foo_baby_yeah_isms) & (sizeof(ISW) - 1);
  //auto foo_baby_yeah_isms = count_max * CBookDefaultCount<TPARAMS>() * sizeof(CHT);
  //return foo_baby_yeah_isms +
  //  (foo_baby_yeah_isms) & (sizeof(ISW) - 1);
}

/* Gets the start of the book as a templated-defined character. */
template <TARGS>
inline CHT* TBookStart(TBook<TPARAMS>* book, ISZ count_max) {
  ISZ* top = &TStackStart<ISZ, ISZ>(&book->offsets)[count_max];
  return reinterpret_cast<CHT*>(top);
}

/* Gets the start byte of the book. */
template <TARGS>
inline CHT* TBookStart(TBook<TPARAMS>* book) {
  return TBookStart<TPARAMS>(book, book->offsets.count_max);
}

/* Gets the byte after the end of the book's contiguous memory block. */
template <TARGS>
inline CHT* TBookEnd(TBook<TPARAMS>* book) {
  CHT* list = TLoomEnd<CHT, ISZ, ISY>(&book->keys);
  return TPtr<CHT>(TListEnd<ISZ>(reinterpret_cast<TList<ISZ>*>(list)));
}

/* Initializes the book to the given count_max using the CBookDefaultSize.
@param loom_size_count If this number is positive then the value is size of the
                       keys Loom in bytes. If the value is negative then it is 
                       the default length of a key. */
template <TARGS>
inline TBook<TPARAMS>* TBookInit(TBook<TPARAMS>* book, ISZ size_bytes,
                                 ISY count_max, ISZ size_keys = 
                                  -CLoomDefaultLengthString<CHT, ISZ, ISY>()) {
  D_COUT("\n\nTBookInit\nsize_bytes: " << size_bytes << " count_max:" <<
    count_max << "\n\n");
  D_ASSERT(book);
  D_ASSERT(size_keys < size_bytes);
  if (size_keys < 0)
    size_keys = TLoomSize<CHT, ISZ, ISY>(count_max, size_keys);
  ISZ size_list = size_bytes - size_keys;
  if (size_keys - size_list > size_bytes || 
      count_max < CBookCountMin<TPARAMS>()) return nullptr;
  // Good to go.
  TList<ISZ>* list = &book->values;
  TListInit<ISZ, DT>(list, size_list, count_max);
  
  // Allocate memory for the Keys.
  TArray<ISZ>* buffer = TListAllocate(list, size_keys);
  TLoomInit<CHT, ISZ, ISY>(TPtr<TLoom<ISZ, ISY>>(buffer),
    count_max);
  D_COUT("\n\nTBookInit Init Post\nsize_bytes: " << size_bytes << 
         " count_max:" << count_max << "\n\n");
  return book;
}

/* Gets the keys Loom (Array of Strings). */
template <TARGS>
inline TLoom<ISZ, ISY>* TBookKeys(TBook<TPARAMS>* book) {
  ISZ count_max = book->values.offsets.count_max;
  D_ASSERT(count_max > 0);
  ISA* keys = TPtr<ISA>(book, sizeof(TBook<TPARAMS>)) +
    count_max * (sizeof(ISZ) + sizeof(DT));
  return TPtr<TLoom<ISZ, ISY>>(keys);
}

/* Gets the element at the given index. */
template <TARGS>
inline ISA* TBookGetPtr(TBook<TPARAMS>* book, ISY index) {
  return TListGetPtr<ISZ, T>(book->values, index);
}

/* Gets the TypeValue tuple the given index.
@param tuple Reference to the return type passed in by reference. */
template <TARGS>
inline TTypeValue<DT> TBookGet(TBook<TPARAMS>* book, ISY index) {
  return TListGet<ISZ, DT>(book->values, index);
}

/* Gets the size of the Book in bytes. */
template <TARGS>
inline ISZ TBookCountMax(TBook<TPARAMS>* book) {
  return book->values.offsets.count_max;
}

/* Prints the book to the printer. */
template <typename Printer, TARGS>
Printer& TBookPrint(Printer& printer, TBook<TPARAMS>* book) {
  ISZ count = book->values.offsets.count;
  printer << "\nBook<CH" << CSizef<CHT>() << ",IS" << CSizef<ISZ>() << ",IS"
          << CSizef<ISY>() << "> size:" << book->values.size_bytes
          << " stack_size:" << book->values.offsets.count_max << " count:" 
          << count;
  auto types = TListTypes<ISZ, DT2>(&book->values);
  for (ISY i = 0; i < count; ++i) {
    printer << '\n' << i << ".) \"" << TListGet<ISZ, DT>(book->values, i) 
            << "\" type:";
    auto type = *types++;
    TPrintType<Printer, DT2>(printer, type);
    D_COUT(" type:" << type << " 0b'" << Binaryf(type));
  }
  D_COUT(Linef('-') << ' ' << Charsf(book, TBookCountMax<TPARAMS>(book)));
  return printer << '\n';
}

/* Doubles the size and count_max of the book.
@return Returns nil if the size is greater than the amount of memory that
can fit in type ISW, the unaltered socket pointer if the Stack has grown to the
size upper bounds, or a new dynamically allocated socket upon failure. */
template <TARGS>
BOL TBookGrow(Autoject& obj) {
  D_COUT("\n\nGrowing Book...");
  /* Grow Algoirhm.
  1. Check if we can grow and if so, create a new block of memory.
  2. Copy the Loom.
  3. Copy the List. */
  auto book = TPtr<TBook<TPARAMS>>(obj.origin);
  A_ASSERT(book);
  ISZ size = TBookCountMax<TPARAMS>(book);
  if (!TCanGrow<ISZ>(size)) return false;
  ISZ count_max = book->values.offsets.count_max;
  if (!TCanGrow<ISZ>(count_max)) return false;

  size = size << 1;
  count_max = count_max << 1;

  D_COUT(" new size:" << size << " count_max:" << count_max);

#if D_THIS
  D_COUT("\n\nBefore:\n");
  TBookPrint<COut, TPARAMS>(COut().Star(), book);
  D_COUT(Charsf(book, TBookEnd<TPARAMS>(book)));
#endif

  IUW* new_begin = obj.socket_factory(nullptr, size);
  D_ARRAY_WIPE(new_begin, size);
  TLoom<ISZ, ISY>* other = reinterpret_cast<TLoom<ISZ, ISY>*>(new_begin);

  return true;
}

/* Removes the given index from the Book.
@return The index upon success or -1 upon failure. */
template <TARGS>
void* TBookListRemove(TBook<TPARAMS>* book, ISY index) {
  TList<ISZ>* list = &book->values;
  ISY count = ISY(list->offsets.count);
  ISZ* offsets = TListOffsets<ISZ>(list);
  TStackRemove<ISZ, ISZ>(offsets, count, index);
  TStackRemove<DT2, ISZ>(TListTypes<ISZ, DT2>(list), count, index);
  return offsets + index;
}

/* Removes the given index from the Book.
@return The index upon success or -1 upon failure. */
template <TARGS>
void* TBookRemove(TBook<TPARAMS>* book, ISY index) {
  ISY result = TLoomRemove<TPARAMS>(&book->keys, index);
  if (!result) return nullptr;
  return TBookListRemove<TPARAMS>(book, index);
}

/* Removes the given key from the Book.
@return Nil upon failure or a pointer to the item removed upon success. */
template <TARGS>
void* TBookRemove(TBook<TPARAMS>* book, const CHT* key) {
  ISY index = TLoomFind<TPARAMS>(book->keys, key);
  if (index < 0) return index;
  TLoomRemove<TPARAMS>(book->keys, index);
  return TBookListRemove<TPARAMS>(book, index);
}

/* Adds a string to the end of the Book.
@return The index upon success or -1 upon failure. */
template <TARGS>
ISZ TBookPop(TBook<TPARAMS>* book) {
  return TBookRemove<TPARAMS>(book, book->values.offsets.count - 1);
}

/* Adds a key-value tuple to the end of the Book.
@return The index upon success or -1 upon failure. */
template <typename T, TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, T item,
                       ISY index = cPush) {
  ++index;
  A_ASSERT(book);
  if (!key) return cErrorInputNil;
  D_COUT("\nAdding key:\"" << key << "\" item:" << item << " into index:" << 
         index);
  auto keys = TBookKeys<TPARAMS>(book);
  ISY result = TLoomInsert<CHT, ISZ, ISY>(keys, key, index);
  D_COUT(" result:" << result);
  if (result < 0) return index;
  auto list = &book->values;
  TListPrint<COut, ISZ, DT>(COut().Star(), list);

  result = ISY(TListInsert<ISZ, DT>(list, item, result));
  if (result < 0) {
    D_COUT("\nFailed to insert into List with error " << result << ':' <<
           STRError(result));
    TLoomRemove<CHT, ISZ, ISY>(keys, index);
  }
  return result;
}
template <TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, ISA item) {
  return TBookInsert<ISA, TPARAMS>(book, key, item);
}
template <TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, IUA item) {
  return TBookInsert<ISA, TPARAMS>(book, key, item);
}
template <TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, ISB item) {
  return TBookInsert<ISB, TPARAMS>(book, key, item);
}
template <TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, IUB item) {
  return TBookInsert<ISB, TPARAMS>(book, key, item);
}
template <TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, ISC item) {
  return TBookInsert<ISC, TPARAMS>(book, key, item);
}
template <TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, IUC item) {
  return TBookInsert<ISC, TPARAMS>(book, key, item);
}
template <TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, ISD item) {
  return TBookInsert<ISD, TPARAMS>(book, key, item);
}
template <TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, IUD item) {
  return TBookInsert<IUD, TPARAMS>(book, key, item);
}
#if USING_FPC == YES_0
template <TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, FPC item) {
  return TBookInsert<FPC, TPARAMS>(book, key, item);
}
#endif
#if USING_FPD == YES_0
template <TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, FPD item) {
  return TBookInsert<FPD, TPARAMS>(book, key, item);
}
#endif

/* Adds a string to the end of the Book, auto-growing if neccissary.
@return The index upon success or -1 if the obj can't grow anymore. */
template <typename T, TARGS, typename BUF>
ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, T item,
                ISY index = cPush) {
  if (!key) return cErrorInputNil;
  auto book = obj.OriginAs<TBook<TPARAMS>*>();
  D_COUT("\nAdding:\"" << item << '\"');
  ISY result = TBookInsert<T, TPARAMS>(book, key, item, index);
  while (result < 0) {
    if (!TBookGrow<TPARAMS>(obj.AJT())) {
      D_COUT("\n\nFailed to grow.\n\n");
      return cErrorBufferOverflow;
    } else {
      D_COUT("\nSuccesseded in growing.");
    }
    result = TBookInsert<T, TPARAMS>(book, key, item, index);
  }
  return result;
}
template <TARGS, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISA item,
                       ISY index) {
  return TBookInsert<ISA, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUA item,
                       ISY index) {
  return TBookInsert<ISA, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISB item,
                       ISY index) {
  return TBookInsert<ISB, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUB item,
                       ISY index) {
  return TBookInsert<ISB, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISC item,
                       ISY index = cPush) {
  return TBookInsert<ISC, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUC item,
                       ISY index = cPush) {
  return TBookInsert<ISC, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISD item,
                       ISY index = cPush) {
  return TBookInsert<ISD, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUD item,
                       ISY index = cPush) {
  return TBookInsert<IUD, TPARAMS, BUF>(obj, key, item, index);
}
#if USING_FPC == YES_0
template <TARGS, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, FPC item,
                       ISY index = cPush) {
  return TBookInsert<FPC, TPARAMS, BUF>(obj, key, item, index);
}
#endif
#if USING_FPD == YES_0
template <TARGS, typename BUF>
inline ISY TBookInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, FPD item,
                       ISY index = cPush) {
  return TBookInsert<FPD, TPARAMS, BUF>(obj, key, item, index);
}
#endif

template <TARGS, typename BUF>
ISZ TBookCharCount(TBook<TPARAMS>* book) {
  return (ISZ)(TBookEnd<TPARAMS>(book) - TBookStart<TPARAMS>(book));
}
template <TARGS, typename BUF>
BOL TBookWrite(TBook<TPARAMS>* destination, TBook<TPARAMS>* soure) {
  return true;
}

/* Adds a string to the end of the Book.
@return The index upon success or -1 upon failure. */
template <TARGS>
CHT* TBookPop(TBook<TPARAMS>* book) {
  if (book->offsets.count == 0) return nullptr;
  ISZ offset = TStackPop<ISZ, ISZ>(book->offsets), top = book->top;
  book->top = offset;
  return reinterpret_cast<CHT*>(reinterpret_cast<ISW>(book) + offset);
}

/* Searches for the given string in the book.
@return -1 if the book doesn't contain the string or the index if it does. */
template <TARGS>
ISZ TBookFind(TBook<TPARAMS>* book, const CHT* string) {
  D_ASSERT(book);
  D_ASSERT(string);
  return TLoomFind<CHT, ISZ>(book->keys, string);
}

/* An ASCII Book Autoject. */
template <TARGS, ISZ cSize = 512,
          typename BUF = TBUF<cSize, CHT, ISZ, TString<ISN>>>
class ABook {
  AArray<IUA, ISZ, BUF> obj_;  //< An Auto-Array object.
 public:
  enum { cCountDefault = cSize / 16,
    // 
    cSizeDefault = CBookDefaultSize<TPARAMS>(),
  };

  /* Constructs a Book. */
  ABook(ISY count_max = cCountDefault, ISZ size = cSizeDefault) {
    TBookInit<TPARAMS>(This(), size, count_max);
  }

  /* Constructs a Book subclass.
  @param factory SocketFactory to call when the String overflows. */
  ABook(SocketFactory socket_factory, ISY count = cCountDefault)
      : obj_(socket_factory) {
    TBookInit<TPARAMS>(This(), count);
  }

  /* Constructs a Book subclass.
  @param factory SocketFactory to call when the String overflows. */
  ABook(SocketFactory socket_factory, ISZ size = CBookDefaultSize<TPARAMS>(),
        ISY count = CBookDefaultCount<TPARAMS>())
      : obj_(socket_factory) {
    TBookInit<TPARAMS>(This(), count);
  }

  /* Returns the size in elements. */
  inline ISZ Size() { return obj_.Size(); }

  /* Returns the size in bytes. */
  inline ISZ SizeBytes() { return obj_.SizeBytes(); }

  /* Returns the size in words. */
  inline ISZ SizeWords() { return obj_.SizeWords(); }

  /* Returns the number of keys. */
  inline ISY Count() { return This()->keys->map->count; }

  /* Inserts the key and item on into the Loom and List at the given index.
  @return The index of the string in the Book. */
  inline ISY Insert(const CHT* key, ISA item, ISY index = cPush) {
    return TBookInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUA item, ISY index = cPush) {
    return TBookInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISB item, ISY index = cPush) {
    return TBookInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUB item, ISY index = cPush) {
    return TBookInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISC item, ISY index = cPush) {
    return TBookInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUC item, ISY index = cPush) {
    return TBookInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISD item, ISY index = cPush) {
    return TBookInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUD item, ISY index = cPush) {
    return TBookInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
#if USING_FPC == YES_0
  inline ISY Insert(const CHT* key, FPC item, ISY index = cPush) {
    return TBookInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
#endif
#if USING_FPD == YES_0
  inline ISY Insert(const CHT* key, FPD item, ISY index = cPush) {
    return TBookInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
#endif
  inline ISY Insert(const CHT* key, const CHT* item, ISY index = cPush) {
    return TBookInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }

  /* Removes the string at the given index from the Book. */
  inline void* Remove(ISY index) { return TBookRemove<TPARAMS>(This(), index); }

  /* Removes the string at the given index from the Book. */
  inline void* Remove(const CHT* key) {
    return TBookRemove<TPARAMS>(This(), key);
  }

  /* Removes the string at the given index from the Book. */
  inline ISZ Pop() { return TBookRemove<TPARAMS>(This()); }

  /* Gets the string at the given index. */
  inline CHT* Get(ISY index) { return TBookGet<TPARAMS>(This(), index); }

  /* Searches for the given string.
  @return -1 if the Book doesn't contain the string or the index if it does. */
  inline ISZ Find(const CHT* string) {
    return TBookFind<TPARAMS>(This(), string);
  }

  /* Gets the Autoject. */
  inline Autoject AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array. */
  inline AArray<IUA, ISZ, BUF>& AJT_ARY() { return obj_; }

  /* Gets the ASCII Object. */
  inline TBook<TPARAMS>* This() { return obj_.OriginAs<TBook<TPARAMS>*>(); }

  /* Prints this object to the Printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TBookPrint<Printer, TPARAMS>(o, This());
  }

  /* Prints this object to the stdout. */
  inline void COut() { PrintTo<_::COut>(_::COut().Star()); }

  /* Shorthand way to get the TBook->values List. */
  inline TList<ISZ>* List() { return &This()->values; }

  /* Gets the Keys struct. */
  inline TBook<ISZ>* Keys() { return TBookKeys<TPARAMS>(This()); }
};

}  //< namespace _
#endif
#endif