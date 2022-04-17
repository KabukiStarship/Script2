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
#include "Book.hpp"
#include "List.hpp"
#if SEAM == SCRIPT2_BOOK
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
namespace _ {
/* @ingroup Book
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/MapTypes/Book.md

Please see the ASCII List documentation for information about
*/

#define TPARAMS CHT, ISZ, ISY, DT
#define TARGS \
  typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM, typename DT = DT2

/* @ingroup Book
@brief A contiguous memory Associative List created from a List and a Loom.
@code
+-----------------+
|      List       |
|-----------------|
|      Loom       |
|-----------------|  ^ Up in addresses
|  TBook Struct   |  |
+-----------------+ 0xN
@endcode */
template <TARGS>
struct TBook {
  TLoom<ISZ, ISY> keys;  //< The Loom of keys for the Associative List.
};

/* The minimum count a good with the given template parameters can have. */
template <TARGS>
constexpr ISZ CBookCountMin() {
  return 8 / sizeof(ISZ);
}

/* The minimum size of a Book based on the CCountMin. */
template <TARGS>
constexpr ISZ CBookSizeMin() {
  enum {
    cCountMin = CBookCountMin(),
    cSizeMin = sizeof(TBook<TPARAMS>) + cCountMin * (sizeof(ISZ) + 2),
  };
  return cSizeMin;
}

/* Gets the default count of a good with the given template parameters. */
template <TARGS>
constexpr ISZ CBookCountDefault() {
  return 32;
}

/* Gets the default size of a Book with the CBookCountDefault. */
template <TARGS>
constexpr ISZ CBookSizeDefault(ISY count_max = CBookCountDefault<TPARAMS>()) {
  return (count_max * CBookCountDefault<TPARAMS>() * sizeof(CHT)) &
         (sizeof(ISW) - 1);
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

template <TARGS>
inline TList<ISZ>* TBookList(TBook<TPARAMS>* book, ISZ size_bytes) {
  return TPtr<TList<ISZ>>(book, size_bytes);
}

template <TARGS>
inline TList<ISZ>* TBookList(TBook<TPARAMS>* book) {
  return TBookList<TPARAMS>(book, book->keys.size);
}

/* Gets the byte after the end of the book's contiguous memory block. */
template <TARGS>
inline CHT* TBookEnd(TBook<TPARAMS>* book) {
  CHT* list = TLoomEnd<CHT, ISZ, ISY>(&book->keys);
  return TPtr<CHT>(TListEnd<ISZ>(reinterpret_cast<TList<ISZ>*>(list)));
}

/* Initializes the book to the given count_max using the CBookSizeDefault. */
template <TARGS>
inline TBook<TPARAMS>* TBookInit(TBook<TPARAMS>* book, ISZ size_bytes,
                                 ISY count_max) {
  D_ASSERT(book);
  if (count_max < CBookCountMin<TPARAMS>()) return nullptr;

  TLoomInit<CHT, ISZ, ISY>(&book->keys, count_max);
  D_COUT("\n\nssize_bytes: " << size_bytes << " book->keys.size:" <<
         book->keys.size << "\n\n");
  TListInit<ISZ, DT>(TBookList<TPARAMS>(book), size_bytes - book->keys.size,
                     count_max);
  return book;
}

/* Gets the element at the given index. */
template <TARGS>
inline CHT* TBookGet(TBook<TPARAMS>* book, ISY index) {
  D_ASSERT(book);
  return TLoomGet<CHT, ISZ, ISY>(&book->keys, index);
}

template <TARGS>
inline ISZ TBookSize(TBook<TPARAMS>* book) {
  TList<ISZ>* list = TBookList<TPARAMS>(book);
  return book->keys.size + list->size_bytes;
}

/* Prints the book to the printer. */
template <typename Printer, TARGS>
Printer& TBookPrint(Printer& printer, TBook<TPARAMS>* book) {
  ISY count = book->keys.map.count;
  printer << "\nBook<CH" << CSizef<CHT>() << ",IS" << CSizef<ISZ>() << ",IS"
          << CSizef<ISY>() << "> size:" << book->keys.size
          << " top:" << book->keys.top 
          << " stack_size:" << book->keys.map.count_max << " count:" << count;
  auto types = TListTypes<ISZ, DT2>(TBookList<TPARAMS>(book));
  for (ISY i = 0; i < count; ++i) {
    printer << '\n' << i << ".) \"" << TBookGet<TPARAMS>(book, i) << "\" type:";
    auto type = *types++;
    TPrintType<Printer, DT2>(printer, type);
    D_COUT(" type:" << type << " 0b'" << Binaryf(type));
  }
  D_COUT(Linef('-') << ' ' << Charsf(book, TBookSize<TPARAMS>(book)));
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
  ISZ size = TBookSize<TPARAMS>(book);
  if (!TCanGrow<ISZ>(size)) return false;
  ISY count_max = book->keys.map.count_max;
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
  TList<ISZ>* list = TBookList<TPARAMS>(book);
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
  return TBookRemove<TPARAMS>(book, book->keys.map->count - 1);
}

/* Adds a key-value tuple to the end of the Book.
@return The index upon success or -1 upon failure. */
template <typename T, TARGS>
inline ISY TBookInsert(TBook<TPARAMS>* book, const CHT* key, T item,
                       ISY index = cPush) {
  A_ASSERT(book);
  if (!key) return cErrorInputNil;
  D_COUT("\nAdding key:\"" << key << "\" item:" << item << " into index:" << 
         index);
  ISY result = TLoomInsert<CHT, ISZ, ISY>(&book->keys, key, index);
  D_COUT(" result:" << result);
  if (result < 0) return index;
  auto list = TBookList<TPARAMS>(book);
  TListPrint<COut, ISZ, DT>(COut().Star(), list);

  result = ISY(TListInsert<ISZ, DT>(list, item, result));
  if (result < 0) {
    D_COUT("\nFailed to insert into List with error " << result << ':' <<
           STRError(result));
    TLoomRemove<CHT, ISZ, ISY>(&book->keys, index);
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
    cSizeDefault = CBookSizeDefault<TPARAMS>(),
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
  ABook(SocketFactory socket_factory, ISZ size = CBookSizeDefault<TPARAMS>(),
        ISY count = CBookCountDefault<TPARAMS>())
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

  /* */
  inline TList<ISZ>* List() { return TBookList<TPARAMS>(This()); }
};

}  //< namespace _
#undef TARGS
#undef TPARAMS
#endif
#endif
