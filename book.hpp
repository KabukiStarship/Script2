/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /book.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_BOOK
#ifndef SCRIPT2_BOOK_CODE
#define SCRIPT2_BOOK_CODE
#include "book.hpp"
#include "list.hpp"
#if SEAM == SCRIPT2_BOOK
#include "_debug.inl"
#else
#include "_release.inl"
#endif
namespace _ {
/* @ingroup Book
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./spec/data/map_types/book.md */

#define TPARAMS SIZ, UIZ, SIY, CHT
#define TARGS \
  typename SIZ = SIN, typename UIZ = UIN, typename SIY = SIG, typename CHT = CHR

/* A contiguous memory Associative List created from a List and a Loom.
@ingroup Book
@code
+-----------------+
|      List       |
|-----------------|
|      Loom       |
|-----------------|  ^ Up in addresses
|  TBook Struct   |  |
+-----------------+ 0xN
@endcode
*/
template <TARGS>
struct TBook {
  TLoom<SIZ>* keys;
};

template <TARGS>
constexpr SIZ cBookCountMin() {
  return 8 / sizeof(SIZ);
}

template <TARGS>
constexpr SIZ cBookSizeMin() {
  enum {
    cCountMin = TBookCountMin(),
    cSizeMin = sizeof(TBook<TPARAMS>) + cCountMin * (sizeof(SIZ) + 2),
  };
  return cSizeMin;
}

template <TARGS>
constexpr SIZ cBookCountDefault() {
  return 32;
}

template <TARGS>
constexpr SIZ cBookSizeDefault() {
  return (32 * cBookCountDefault<TPARAMS>() * sizeof(CHT)) & (sizeof(SIW) - 1);
}

template <TARGS>
inline CHT* TBookStart(TBook<TPARAMS>* book, SIZ count_max) {
  SIZ* top = &TStackStart<SIZ, SIZ>(&book->offsets)[count_max];
  return reinterpret_cast<CHT*>(top);
}

template <TARGS>
inline CHT* TBookStart(TBook<TPARAMS>* book) {
  return TBookStart<TPARAMS>(book, book->offsets.count_max);
}

template <TARGS>
inline TBook<TPARAMS>* TBookInit(TBook<TPARAMS>* book, SIZ count_max) {
  D_ASSERT(book);
  A_ASSERT((count_max >= cBookCountMin<TPARAMS>()));

  TLoomInit(book->keys, count_max);

  return book;
}

template <TARGS>
inline CHT* TBookEnd(TBook<TPARAMS>* book) {
  CHT* list = TLoomEnd(book->keys);
  return TListEnd<SIZ>(reinterpret_cast<TList<SIZ>*>(list));
}

template <TARGS>
inline TList<SIZ>* TBookList(TBook<TPARAMS>* book, SIZ size_bytes) {
  return TPtr<TList<SIZ>>(book, size_bytes);
}

template <TARGS>
inline TList<SIZ>* TBookList(TBook<TPARAMS>* book) {
  return TBookList<TPARAMS>(book, book->keys->size);
}

/* Gets the element at the given index. */
template <TARGS>
inline CHT* TBookGet(TBook<TPARAMS>* book, SIY index) {
  D_ASSERT(book);
  auto count = book->keys->map.count;
  if (index < 0 || count) return nullptr;
  return TPtr<CHT>(book, TStackStart<SIZ, SIZ>(&book->keys->map)[index]);
}

template <TARGS>
inline SIZ TBookSize(TBook<TPARAMS>* book) {
  TList<SIZ>* list = TBookList<TPARAMS>(book);
  return book->keys->size + list->size_bytes;
}

template <TARGS, typename Printer>
Printer& TBookPrint(Printer& o, TBook<TPARAMS>* book) {
  SIZ count = book->keys->map.count;
  o << "\nBook<SI" << CH1('0' + sizeof(SIZ)) << ",UI" << CH1('0' + sizeof(UIZ))
    << ",SI" << CH1('A' + sizeof(SIY)) << CH1('0' + sizeof(CHT))
    << "> size:" << book->keys->size << " top:" << book->keys->top
    << " stack_size:" << book->keys->map.count_max << " count:" << count;
  auto types = TListTypes<SIZ, DT2>(TBookList<TPARAMS>(book));
  for (SIY i = 0; i < count; ++i)
    o << '\n'
      << i << ".) \"" << TBookGet<TPARAMS>(book, i)
      << "\" type:" << TPrintType<Printer, DT2>(o, *types++);
  D_COUT(Linef('-') << Charsf(book, TBookSize<TPARAMS>(book)));
  return o << '\n';
}

/* Doubles the size and count_max of the book.
@return Returns nil if the size is greater than the amount of memory that
can fit in type SIW, the unaltered socket pointer if the Stack has grown to the
size upper bounds, or a new dynamically allocated socket upon failure. */
template <TARGS>
BOL TBookGrow(Autoject& obj) {
  D_COUT("\n\nGrowing Book...");
  /* Grow Algoirhm.
  1. Check if we can grow and if so, create a new block of memory.
  2. Copy the Loom.
  3. Copy the List.
  */
  auto book = reinterpret_cast<TBook<TPARAMS>*>(obj.origin);
  A_ASSERT(book);
  SIZ size = TBookSize<TPARAMS>(book);
  if (!TCanGrow<SIZ>(size)) return false;
  SIZ count_max = book->keys.offsets.count_max;
  if (!TCanGrow<SIZ>(count_max)) return false;

  size = size << 1;
  count_max = count_max << 1;

  D_COUT(" new size:" << size << " count_max:" << count_max);

#if D_THIS
  D_COUT("\n\nBefore:\n");
  TBookPrint<TPARAMS, COut>(COut().Star(), book);
  D_COUT(Charsf(book, TBookEnd<TPARAMS>(book)));
#endif

  UIW* new_begin = obj.socket_factory(nullptr, size);
  D_ARRAY_WIPE(new_begin, size);
  TLoom<SIZ>* other = reinterpret_cast<TLoom<SIZ>*>(new_begin);

  return true;
}

/* Removes the given index from the Book.
@return The index upon success or -1 upon failure. */
template <TARGS>
void* TBookListRemove(TBook<TPARAMS>* book, SIY index) {
  TList<SIZ>* list = TBookList<TPARAMS>(book);
  SIZ count = list->offsets.count;
  SIZ* offsets = TListOffsets<SIZ>(list);
  TStackRemove<SIZ, SIZ>(offsets, count, index);
  TStackRemove<DT2, SIZ>(TListTypes<SIZ, DT2>(list), count, index);
  return offsets + index;
}

/* Removes the given index from the Book.
@return The index upon success or -1 upon failure. */
template <TARGS>
void* TBookRemove(TBook<TPARAMS>* book, SIY index) {
  SIY index = TLoomRemove<CHT, SIZ>(book->keys, index);
  return TBookListRemove<TPARAMS>(book, index);
}

/* Removes the given key from the Book.
@return Nil upon failure or a pointer to the item removed upon success. */
template <TARGS>
void* TBookRemove(TBook<TPARAMS>* book, const CHT* key) {
  SIY index = TLoomFind<TPARAMS>(book->keys, key);
  if (index < 0) return index;
  TLoomRemove<TPARAMS>(book->keys, index);
  return TBookListRemove<TPARAMS>(book, index);
}

/* Adds a string to the end of the Book.
@return The index upon success or -1 upon failure. */
template <TARGS>
SIZ TBookPop(TBook<TPARAMS>* book) {
  return TBookRemove<TPARAMS>(book, book->keys->map->count - 1);
}

/* Adds a key-value tuple to the end of the Book.
@return The index upon success or -1 upon failure. */
template <typename T, TARGS>
inline SIY TBookInsert(TBook<TPARAMS>* book, const CHT* key, T item,
                       SIY index = cPush) {
  A_ASSERT(book);
  if (!key) return cErrorNilInput;
  if (index == cAnywhere) {
    index = TLoomInsert<CHT, SIY>(book->keys, key, index);
  } else {
    if (index == cPush) index = book->keys.map.count - 1;
  }
  if (index < 0) return index;
  SIY result = SIY(TListInsert<SIZ, DT2>(TBookList<TPARAMS>(book), item));
  if (result) TBookRemove<TPARAMS>(book, index, item);
  return result;
}
template <TARGS>
inline SIY TBookInsert(TBook<TPARAMS>* book, const CHT* key, SI1 item) {
  return TBookInsert<SI1, TPARAMS>(book, key, item);
}
template <TARGS>
inline SIY TBookInsert(TBook<TPARAMS>* book, const CHT* key, UI1 item) {
  return TBookInsert<SI1, TPARAMS>(book, key, item);
}
template <TARGS>
inline SIY TBookInsert(TBook<TPARAMS>* book, const CHT* key, SI2 item) {
  return TBookInsert<SI2, TPARAMS>(book, key, item);
}
template <TARGS>
inline SIY TBookInsert(TBook<TPARAMS>* book, const CHT* key, UI2 item) {
  return TBookInsert<SI2, TPARAMS>(book, key, item);
}
template <TARGS>
inline SIY TBookInsert(TBook<TPARAMS>* book, const CHT* key, SI4 item) {
  return TBookInsert<SI4, TPARAMS>(book, key, item);
}
template <TARGS>
inline SIY TBookInsert(TBook<TPARAMS>* book, const CHT* key, UI4 item) {
  return TBookInsert<SI4, TPARAMS>(book, key, item);
}
template <TARGS>
inline SIY TBookInsert(TBook<TPARAMS>* book, const CHT* key, SI8 item) {
  return TBookInsert<SI8, TPARAMS>(book, key, item);
}
template <TARGS>
inline SIY TBookInsert(TBook<TPARAMS>* book, const CHT* key, UI8 item) {
  return TBookInsert<UI8, TPARAMS>(book, key, item);
}
#if USING_FP4 == YES_0
template <TARGS>
inline SIY TBookInsert(TBook<TPARAMS>* book, const CHT* key, FP4 item) {
  return TBookInsert<FP4, TPARAMS>(book, key, item);
}
#endif
#if USING_FP8 == YES_0
template <TARGS>
inline SIY TBookInsert(TBook<TPARAMS>* book, const CHT* key, FP8 item) {
  return TBookInsert<FP8, TPARAMS>(book, key, item);
}
#endif

/* Adds a string to the end of the Book, auto-growing if neccissary.
@return The index upon success or -1 if the obj can't grow anymore. */
template <typename T, typename BUF, TARGS>
SIY TBookInsert(AArray<UI1, SIZ, BUF>& obj, const CHT* key, T item,
                SIY index = cPush) {
  if (!key) return -cErrorNilInput;
  auto book = obj.OriginAs<TBook<TPARAMS>*>();
  D_COUT("\nAdding:\"" << item << '\"');
  SIY result = TBookInsert<T, TPARAMS>(book, key, item, index);
  while (result < 0) {
    if (!TBookGrow<TPARAMS>(obj.AJT())) {
      D_COUT("\n\nFailed to grow.\n\n");
      return -cErrorBufferOverflow;
    }
    result = TBookInsert<T, TPARAMS>(book, key, item, index);
  }
  return result;
}
template <typename BUF, TARGS>
inline SIY TBookInsert(AArray<UI1, SIZ, BUF>& obj, const CHT* key, SI1 item,
                       SIY index) {
  return TBookInsert<SI1, BUF, TPARAMS>(obj, key, item, index);
}
template <typename BUF, TARGS>
inline SIY TBookInsert(AArray<UI1, SIZ, BUF>& obj, const CHT* key, UI1 item,
                       SIY index) {
  return TBookInsert<SI1, BUF, TPARAMS>(obj, key, item, index);
}
template <typename BUF, TARGS>
inline SIY TBookInsert(AArray<UI1, SIZ, BUF>& obj, const CHT* key, SI2 item,
                       SIY index) {
  return TBookInsert<SI2, BUF, TPARAMS>(obj, key, item, index);
}
template <typename BUF, TARGS>
inline SIY TBookInsert(AArray<UI1, SIZ, BUF>& obj, const CHT* key, UI2 item,
                       SIY index) {
  return TBookInsert<SI2, BUF, TPARAMS>(obj, key, item, index);
}
template <typename BUF, TARGS>
inline SIY TBookInsert(AArray<UI1, SIZ, BUF>& obj, const CHT* key, SI4 item,
                       SIY index = cPush) {
  return TBookInsert<SI4, BUF, TPARAMS>(obj, key, item, index);
}
template <typename BUF, TARGS>
inline SIY TBookInsert(AArray<UI1, SIZ, BUF>& obj, const CHT* key, UI4 item,
                       SIY index = cPush) {
  return TBookInsert<SI4, BUF, TPARAMS>(obj, key, item, index);
}
template <typename BUF, TARGS>
inline SIY TBookInsert(AArray<UI1, SIZ, BUF>& obj, const CHT* key, SI8 item,
                       SIY index = cPush) {
  return TBookInsert<SI8, BUF, TPARAMS>(obj, key, item, index);
}
template <typename BUF, TARGS>
inline SIY TBookInsert(AArray<UI1, SIZ, BUF>& obj, const CHT* key, UI8 item,
                       SIY index = cPush) {
  return TBookInsert<UI8, BUF, TPARAMS>(obj, key, item, index);
}
#if USING_FP4 == YES_0
template <typename BUF, TARGS>
inline SIY TBookInsert(AArray<UI1, SIZ, BUF>& obj, const CHT* key, FP4 item,
                       SIY index = cPush) {
  return TBookInsert<FP4, BUF, TPARAMS>(obj, key, item, index);
}
#endif
#if USING_FP8 == YES_0
template <typename BUF, TARGS>
inline SIY TBookInsert(AArray<UI1, SIZ, BUF>& obj, const CHT* key, FP8 item,
                       SIY index = cPush) {
  return TBookInsert<FP8, BUF, TPARAMS>(obj, key, item, index);
}
#endif

template <TARGS, typename BUF>
SIZ TBookCharCount(TBook<TPARAMS>* book) {
  return (SIZ)(TBookEnd<TPARAMS>(book) - TBookStart<TPARAMS>(book));
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
  SIZ offset = TStackPop<SIZ, SIZ>(book->offsets), top = book->top;
  book->top = offset;
  return reinterpret_cast<CHT*>(reinterpret_cast<SIW>(book) + offset);
}

/* Searches for the given string in the book.
@return -1 if the book doesn't contain the string or the index if it does. */
template <TARGS>
SIZ TBookFind(TBook<TPARAMS>* book, const CHT* string) {
  D_ASSERT(book);
  D_ASSERT(string);
  return TLoomFind<CHT, SIZ>(book->keys, string);
}

/* An ASCII Book Autoject. */
template <TARGS, SIZ cSize_ = 512,
          typename BUF = TUIB<cSize_, CHT, TStrand<SIN>>>
class ABook {
  AArray<UI1, SIZ, BUF> obj_;  //< An Auto-Array object.
 public:
  enum { cCountDefault = cSize_ / 16 };
  /* Constructs a Book. */
  ABook(SIZ count_max = cCountDefault) {
    TBookInit<TPARAMS>(This(), count_max);
  }

  /* Constructs a Book subclass.
  @param factory SocketFactory to call when the Strand overflows. */
  ABook(SocketFactory socket_factory, SIZ count = cCountDefault)
      : obj_(socket_factory) {
    TBookInit<TPARAMS>(This(), count);
  }

  /* Constructs a Book subclass.
  @param factory SocketFactory to call when the Strand overflows. */
  ABook(SocketFactory socket_factory, SIZ size = cBookSizeDefault<TPARAMS>(),
        SIZ count = cBookCountDefault<TPARAMS>())
      : obj_(socket_factory) {
    TBookInit<TPARAMS>(This(), count);
  }

  inline SIZ Size() { return obj_.Size(); }

  inline SIZ SizeBytes() { return obj_.SizeBytes(); }

  inline SIZ SizeWords() { return obj_.SizeWords(); }

  inline SIY Count() { return This()->keys->map->count; }

  /* Inserts the key and item on into the Loom and List at the given index.
  @return The index of the string in the Book. */
  inline SIY Insert(const CHT* key, SI1 item, SIY index = cPush) {
    return TBookInsert<BUF, TPARAMS>(AJT_ARY(), key, item, index);
  }
  inline SIY Insert(const CHT* key, UI1 item, SIY index = cPush) {
    return TBookInsert<BUF, TPARAMS>(AJT_ARY(), key, item, index);
  }
  inline SIY Insert(const CHT* key, SI2 item, SIY index = cPush) {
    return TBookInsert<BUF, TPARAMS>(AJT_ARY(), key, item, index);
  }
  inline SIY Insert(const CHT* key, UI2 item, SIY index = cPush) {
    return TBookInsert<BUF, TPARAMS>(AJT_ARY(), key, item, index);
  }
  inline SIY Insert(const CHT* key, SI4 item, SIY index = cPush) {
    return TBookInsert<BUF, TPARAMS>(AJT_ARY(), key, item, index);
  }
  inline SIY Insert(const CHT* key, UI4 item, SIY index = cPush) {
    return TBookInsert<BUF, TPARAMS>(AJT_ARY(), key, item, index);
  }
  inline SIY Insert(const CHT* key, SI8 item, SIY index = cPush) {
    return TBookInsert<BUF, TPARAMS>(AJT_ARY(), key, item, index);
  }
  inline SIY Insert(const CHT* key, UI8 item, SIY index = cPush) {
    return TBookInsert<BUF, TPARAMS>(AJT_ARY(), key, item, index);
  }
#if USING_FP4 == YES_0
  inline SIY Insert(const CHT* key, FP4 item, SIY index = cPush) {
    return TBookInsert<BUF, TPARAMS>(AJT_ARY(), key, item, index);
  }
#endif
#if USING_FP8 == YES_0
  inline SIY Insert(const CHT* key, FP8 item, SIY index = cPush) {
    return TBookInsert<BUF, TPARAMS>(AJT_ARY(), key, item, index);
  }
#endif
  inline SIY Insert(const CHT* key, const CHT* item, SIY index = cPush) {
    return TBookInsert<BUF, TPARAMS>(AJT_ARY(), key, item, index);
  }

  /* Removes the string at the given index from the Book. */
  inline void* Remove(SIY index) { return TBookRemove<TPARAMS>(This(), index); }

  /* Removes the string at the given index from the Book. */
  inline void* Remove(const CHT* key) {
    return TBookRemove<TPARAMS>(This(), key);
  }

  /* Removes the string at the given index from the Book. */
  inline SIZ Pop() { return TBookRemove<TPARAMS>(This()); }

  /* Gets the string at the given index. */
  inline CHT* Get(SIY index) { return TBookGet<TPARAMS>(This(), index); }

  /* Searches for the given string.
  @return -1 if the Book doesn't contain the string or the index if it does.
*/
  inline SIZ Find(const CHT* string) {
    return TBookFind<TPARAMS>(This(), string);
  }

  /* Gets the Autoject. */
  inline Autoject AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array. */
  inline AArray<UI1, SIZ, BUF>& AJT_ARY() { return obj_; }

  /* Gets the ASCII Object. */
  inline TBook<TPARAMS>* This() { return obj_.OriginAs<TBook<TPARAMS>*>(); }

  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    TBookPrint<TPARAMS, Printer>(o, This());
    return o;
  }

  inline void COut() { PrintTo<_::COut>(_::COut().Star()); }
};

}  // namespace _
#undef TARGS
#undef TPARAMS
#endif
#endif
