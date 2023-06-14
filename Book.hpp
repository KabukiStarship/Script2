/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Book.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
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
+===================================+
|_______   Buffer                   |
|_______ ^ Book Value N-1           |
|_______ | Book Value 1             |
|        | List Value 0             |
|        |  ASCII Loom Keys         |
|-----------------------------------|
|_______   Buffer                   |
|_______ ^ Book element 1 Value N-1 |
|_______ | Book element 1 Value 1   |
|        | Type of List Value 0     |
|        |  ASCII Loom Type         |
|-----------------------------------|
|_______   Buffer                   |
|_______ ^ Offset to Value N-1      |
|        | Offset to Value 0        |
|        |   ASCII Loom Keys offset |
+===================================+  ^ Up in
|         TList Struct              |  |
+===================================+  + 0xN
@endcode */
template <TARGS>
struct TBook {
  // The type-value list that corresponds to the key indexes.
  TList<ISZ> values;
};

enum {
  // The number of bits to shift a Book's size_bytes right by to calculate the 
  // size_keys (Example: size_keys = size_bytes >> 2).
  cBookDefaultKeysFractionShift = 2,
  // The number of bits to shift a Book's size_bytes right by to calculate the 
  // count_max (Example: count_max = size_bytes >> 5).
  cBookDefaultCountMaxFractionShift = 5,
  cBookDefaultLengthKey = 15,
  cBookDefaultSizeBytes = 512,
  cBookDefaultCount = cBookDefaultSizeBytes >> cBookDefaultKeysFractionShift,
};

/* The minimum count a good with the given template parameters can have. */
template <TARGS>
constexpr ISY CBookCountMin() {
  return 8 / sizeof(ISZ);
}

/* The minimum size of a Book based on the CCountMin. */
template <TARGS>
constexpr ISZ TBookSizeMin(ISY count_max) {
  return sizeof(TBook<TPARAMS>) + count_max * (sizeof(ISZ) + 2); //< @todo ???
}

/* Gets the default count of a good with the given template parameters. */
template <TARGS>
constexpr ISZ CBookDefaultCount() {
  return 32;
}

/* Gets the default count of a good with the given template parameters. */
template <TARGS>
ISZ TBookDefaultCount(ISZ size_bytes) {
  return size_bytes >> 5; // >> 5 to / by 32
}

/* Gets the default size of a Book with the CBookDefaultCount. */
template <TARGS>
constexpr ISZ CBookDefaultSize(ISY count_max = CBookDefaultCount<TPARAMS>()) {
  if (count_max < 1) return -1;
  if (count_max < CBookCountMin<TPARAMS>()) 
    count_max = CBookCountMin<TPARAMS>();
  ISZ foo_baby_yeah_isms = count_max * cBookDefaultLengthKey * sizeof(CHT);
  return foo_baby_yeah_isms;
}

/* Gets the start of the book as a templated-defined character. */
template <TARGS>
inline CHT* TBookStart(TBook<TPARAMS>* book, ISZ count_max) {
  ISZ* top = &TStackStart<ISZ, ISZ>(&book->offsets)[count_max];
  return TPtr<CHT>(top);
}

/* Gets the start byte of the book. */
template <TARGS>
inline CHT* TBookStart(TBook<TPARAMS>* book) {
  return TBookStart<TPARAMS>(book, book->offsets.count_max);
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

/* Gets the byte after the end of the book's contiguous memory block. */
template <TARGS>
inline CHA* TBookEnd(TBook<TPARAMS>* book) {
  return TListEnd<ISZ>(&book->values);
}

/* Gets the byte after the end of the book's contiguous memory block. */
template <TARGS>
inline CHA* TBookKeysEnd(TBook<TPARAMS>* book) {
  return TLoomEnd<CHT, ISZ, ISY>(TBookKeys<TPARAMS>(book));
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
    << CSizef<ISY>() << "> size_bytes:" << book->values.size_bytes
    << " stack_size:" << book->values.offsets.count_max << " count:"
    << count;
  auto types = TListTypes<ISZ, DTB>(&book->values);
  for (ISY i = 0; i < count; ++i) {
    printer << '\n' << i << ".) \"" << TListGet<ISZ, DT>(&book->values, i)
      << "\" type:";
    auto type = *types++;
    TPrintType<Printer, DTB>(printer, type);
    D_COUT(" type:" << type << " 0b'" << Binaryf(type));
  }
  D_COUT(Linef('-') << ' ' << Charsf(book, TBookCountMax<TPARAMS>(book)));
  return printer << '\n';
}

/* Initializes the book to the given count_max using the CBookDefaultSize.
@param size_bytes The size of the book in bytes.
@param count_max The maximum number of entries in the book -1 for the keys.
@param size_keys If this number is positive then the value is size of the keys 
                 Loom in bytes. If the value is negative then it is the number
                 of bits to shift the size_bytes to get the size_keys. */
template <TARGS>
TBook<TPARAMS>* TBookInit(TBook<TPARAMS>* book, ISY count_max, 
                          ISZ size_keys = -cBookDefaultKeysFractionShift) {
  ISZ size_bytes = book->values.size_bytes;
  D_COUT("\n\nTBookInit size_bytes: " << size_bytes << " count_max:" <<
         count_max << " size_keys:" << size_keys << "\n\n");
  D_ASSERT(book);
  if (size_keys < 0) size_keys = ISY(size_bytes >> (-size_keys));
  if (count_max < 0) count_max = ISY(size_bytes >> (-count_max));
  TList<ISZ>* list = &book->values;
  TListInit<ISZ, DT>(list, size_bytes, count_max);
  if (!list) {
    D_COUT("\nBook List size_bytes not large enough!");
    return nullptr;
  }
  // Allocate memory for the Keys.
  TArray<ISZ>* buffer = TListPush<ISZ, DT>(list, size_keys);
  if (!buffer) {
    D_COUT("\nBook Keys too large to fit in list! size_keys:" << size_keys);
    return nullptr;
  }
  auto keys = TPtr<TLoom<ISZ, ISY>>(buffer);
  D_COUT("TListPush Begin:" << Hexf(buffer) << " End:" << buffer->size);
  auto result = TLoomInit<CHT, ISZ, ISY>(TBookKeys<TPARAMS>(book), count_max);
  D_COUT("\n\nTBookInit Post size_bytes: " << size_bytes << 
         " count_max  :" << count_max << "\nTBook\n");
  D_COUT("\nMemory layout:" << 
    "\nBook End : " << TDelta<>(book, TBookEnd<TPARAMS>(book)) <<
    "\nKeys End  :" << TDelta<>(book, TLoomEnd<CHT, ISZ, ISY>(keys)) <<
    "\nKeys Start:" << TDelta<>(book, keys) <<
    "\nBook      :" << Hexf(book));
  auto foo = TBookPrint<COut, CHT, ISZ, ISY, DT>(COut().Star(), book);
  D_COUT(foo);
  if (!result) return nullptr;
  return book;
}



/* Copies an ASCII Book from the origin to the destination. */
template<TARGS>
CHA* TBookCopy(TStack<ISZ>* origin, TStack<ISZ>* destination) {
  return ArrayCopy(&origin->count, sizeof(ISZ) + origin->count * sizeof(T),
                   &destination->count, 
                   sizeof(ISZ) + destination->count_max * sizeof(T));
}

IUW* BookFactoryStack(IUW* buffer, ISW size_bytes) {
  if (size_bytes < 0) return nullptr;
  size_bytes += (-size_bytes) & cWordLSbMask; //< Word align up.
  ISW size_words = size_bytes >> cWordBitCount;
  IUW* socket = new IUW[size_words];
  // @todo Check if the memory was created successfully.
  return socket;
}

IUW* BookFactoryHeap(IUW* buffer, ISW size_bytes) {
  if (buffer) {
    delete[] buffer;
    return nullptr;
  }
  return BookFactoryStack(buffer, size_bytes);
}

/* Gets the element at the given index. */
template <TARGS>
inline ISA* TBookGetPtr(TBook<TPARAMS>* book, ISY index) {
  return TListGetPtr<ISZ, T>(book->values, index);
}

/* Gets the TypeValue tuple the given index.
@param tuple Reference to the return type passed in by reference. */
template <TARGS>
inline TypeWordValue TBookGet(TBook<TPARAMS>* book, ISY index) {
  return TListGet<ISZ, DT>(book->values, index);
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
  TLoom<ISZ, ISY>* other = TPtr<TLoom<ISZ, ISY>>(new_begin);

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
  TStackRemove<DTB, ISZ>(TListTypes<ISZ, DTB>(list), count, index);
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
  return TPtr<CHT>(ISW(book) + offset);
}

/* Searches for the given string in the book.
@return -1 if the book doesn't contain the string or the index if it does. */
template <TARGS>
ISZ TBookFind(TBook<TPARAMS>* book, const CHT* string) {
  D_ASSERT(book);
  D_ASSERT(string);
  return TLoomFind<CHT, ISZ>(book->keys, string);
}

/* An ASCII Book Autoject.
@code
ABook<TARGS, 1024, TBuf<>>
@endcode
*/
template <TARGS, ISZ cSize = 512,
          typename BUF = TBUF<cSize, CHT, ISZ, TString<ISN>>>
class ABook {
  AArray<IUA, ISZ, BUF> obj_;  //< An Auto-Array object.
 public:
  enum { 
    cSizeBytesDefault = CBookDefaultSize<TPARAMS>(),

    cCountMaxDefault = cSizeBytesDefault >> cBookDefaultCountMaxFractionShift,
  };

  /* Constructs a Book. 
  inline TBook<TPARAMS>* TBookInit(TBook<TPARAMS>* book, ISZ size_bytes,
                                 ISY count_max, ISZ size_keys = 
                                  -CLoomDefaultLengthString<CHT, ISZ, ISY>())
                                  */
  ABook(ISY count_max = -cBookDefaultCountMaxFractionShift,
        ISZ size_keys = -cBookDefaultKeysFractionShift) {
    TBookInit<TPARAMS>(This(), count_max, size_keys);
  }

  /* Constructs a Book on the Heap.
  @param factory SocketFactory to call when the String overflows. */
  ABook(SocketFactory socket_factory, 
        ISY count_max = -cBookDefaultCountMaxFractionShift,
        ISZ size_keys = -cBookDefaultKeysFractionShift)
      : obj_(socket_factory) {
    TBookInit<TPARAMS>(This(), count_max);
  }

  /* Returns the size in elements. */
  inline ISZ Size() { return obj_.Size(); }

  /* Returns the size in bytes. */
  inline ISZ SizeBytes() { return This()->values.size_bytes; }

  /* Returns the size in words. */
  inline ISZ SizeWords() { return obj_.SizeWords() >> cWordBitCount; }

  /* Returns the number of keys. */
  inline ISZ Count() { return This()->values.offsets.count; }

  /* Returns the maximum number of keys. */
  inline ISZ CountMax() { return This()->values.offsets.count_max; }

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