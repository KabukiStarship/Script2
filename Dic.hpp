/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Dic.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_DIC_TEMPLATES
#define SCRIPT2_DIC_TEMPLATES
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
#include "Binary.hpp"
#include "TypeValue.h"
#if SEAM == SCRIPT2_DIC
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
namespace _ {
/* @ingroup Dic
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/MapTypes/Dictionary.md */
#undef  TPARAMS
#define TPARAMS CHT, ISZ, ISY, HSH
#undef  TARGS
#define TARGS \
  typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM, typename HSH = IUN

/* @ingroup Dic
@brief A contiguous memory Associative List created from a List and a Table.
@code
+-----------------+
|      List       |
|-----------------|
|      Table      |
|-----------------|  ^ Up in addresses
|  TDic Struct    |  |
+-----------------+ 0xN
@endcode */
template <TARGS>
struct TDic {
  TTable<ISZ, ISY> keys;   //< The Table of keys for the Associative List.
};

/* The minimum count a good with the given template parameters can have. */
template <TARGS>
constexpr ISY CDicCountMin() {
  return 8 / sizeof(ISZ);
}

/* The minimum size of a Dic based on the CCountMin. */
template <TARGS>
constexpr ISZ CDicSizeMin() {
  enum {
    cCountMin = CDicCountMin<TPARAMS>(),
    cSizeMin = sizeof(TDic<TPARAMS>) + cCountMin * (sizeof(ISZ) + 2),
  };
  return cSizeMin;
}

/* Gets the default count of a good with the given template parameters. */
template <TARGS>
constexpr ISY CDicCountDefault() {
  return 32;
}

/* Gets the default size of a Dic with the CDicCountDefault. */
template <TARGS>
constexpr ISZ CDicSizeDefault() {
  return (32 * CDicCountDefault<TPARAMS>() * sizeof(CHT)) & (sizeof(ISW) - 1);
}

/* Gets the start of the dic as a templated-defined character. */
template <TARGS>
inline CHT* TDicStart(TDic<TPARAMS>* dic, ISZ count_max) {
  ISZ* top = &TStackStart<ISZ, ISZ>(&dic->offsets)[count_max];
  return reinterpret_cast<CHT*>(top);
}

/* Gets the start byte of the dic. */
template <TARGS>
inline CHT* TDicStart(TDic<TPARAMS>* dic) {
  return TDicStart<TPARAMS>(dic, dic->offsets.count_max);
}

/* Initializes the dic to the given count_max using the CDicSizeDefault. */
template <TARGS>
inline TDic<TPARAMS>* TDicInit(TDic<TPARAMS>* dic, ISY count_max) {
  D_ASSERT(dic);
  if (count_max < CDicCountMin<TPARAMS>()) return nullptr;

  TTableInit<TPARAMS>(&dic->keys, count_max, CDicSizeDefault<TPARAMS>());

  return dic;
}

/* Gets the byte after the end of the dic's contiguous memory block. */
template <TARGS>
inline CHT* TDicEnd(TDic<TPARAMS>* dic) {
  CHT* list = TPtr<CHT>(TTableEnd<TPARAMS>(&dic->keys));
  return TPtr<CHT>(TListEnd<ISZ>(TPtr<TList<ISZ>>(list)));
}
template <TARGS>
inline TList<ISZ>* TDicList(TDic<TPARAMS>* dic, ISZ size_bytes) {
  return TPtr<TList<ISZ>>(dic, size_bytes);
}
template <TARGS>
inline TList<ISZ>* TDicList(TDic<TPARAMS>* dic) {
  return TDicList<TPARAMS>(dic, dic->keys.size_bytes);
}

/* The size of the dic. */
template <TARGS>
inline ISZ TDicSize(TDic<TPARAMS>* dic) {
  TList<ISZ>* list = TDicList<TPARAMS>(dic);
  return dic->keys.size_bytes + list->size_bytes;
}

/* Prints the dic to the printer. */
template <typename Printer, TARGS>
Printer& TDicPrint(Printer& printer, TDic<TPARAMS>* dic) {
  ISY count = dic->keys.count;
  printer << "\nDic<CH" << CSizef<CHT> () << ",IS" << CSizef<ISZ>() << ",IS"
          << CSizef<ISY>()
          << "> size_bytes:" << dic->keys.size_bytes
          << " count_max:" << dic->keys.count_max << " count:" << count;
  auto types = TListTypes<ISZ, DTB>(TDicList<TPARAMS>(dic));
  for (ISY i = 0; i < count; ++i) {
    auto foo = TTableGet<TPARAMS>(&dic->keys, i);
    printer << '\n'
            << i << ".) \""
            << "here"
            << "\" type:" << TPrintType<Printer, DTB>(printer, *types++);
  }
  D_COUT(Linef('-') << Charsf(dic, TDicSize<TPARAMS>(dic)));
  return printer << '\n';
}

/* Doubles the size and count_max of the dic.
@return Returns nil if the size is greater than the amount of memory that
can fit in type ISW, the unaltered socket pointer if the Stack has grown to the
size upper bounds, or a new dynamically allocated socket upon failure. */
template <TARGS>
BOL TDicGrow(Autoject& obj) {
  D_COUT("\n\nGrowing Dic...");
  /* Grow Algoirhm.
  1. Check if we can grow and if so, create a new block of memory.
  2. Copy the Table.
  3. Copy the List. */
  auto dic = TPtr<TDic<TPARAMS>>(obj.origin);
  A_ASSERT(dic);
  ISZ size = TDicSize<TPARAMS>(dic);
  if (!TCanGrow<ISZ>(size)) return false;
  ISZ count_max = dic->keys.count_max;
  if (!TCanGrow<ISZ>(count_max)) return false;

  size = size << 1;
  count_max = count_max << 1;

  D_COUT(" new size:" << size << " count_max:" << count_max);

#if D_THIS
  D_COUT("\n\nBefore:\n");
  TDicPrint<COut, TPARAMS>(COut().Star(), dic);
  D_COUT(Charsf(dic, TDicEnd<TPARAMS>(dic)));
#endif

  IUW* new_begin = obj.socket_factory(nullptr, size);
  D_ARRAY_WIPE(new_begin, size);
  TTable<ISZ, ISY>* other = reinterpret_cast<TTable<ISZ, ISY>*>(new_begin);

  return true;
}

/* Removes the given index from the Dic.
@return The index upon success or -1 upon failure. */
template <TARGS>
void* TDicListRemove(TDic<TPARAMS>* dic, ISY index) {
  TList<ISZ>* list = TDicList<TPARAMS>(dic);
  ISY count = ISY(list->offsets.count);
  ISZ* offsets = TListOffsets<ISZ>(list);
  TStackRemove<ISZ, ISZ>(offsets, count, index);
  TStackRemove<DTB, ISZ>(TListTypes<ISZ, DTB>(list), count, index);
  return offsets + index;
}

/* Removes the given index from the Dic.
@return The index upon success or -1 upon failure. */
template <TARGS>
void* TDicRemove(TDic<TPARAMS>* dic, ISY index) {
  ISY result = TTableRemove<TPARAMS>(&dic->keys, index);
  if (!result) return nullptr;
  return TDicListRemove<TPARAMS>(dic, index);
}

/* Removes the given key from the Dic.
@return Nil upon failure or a pointer to the item removed upon success. */
template <TARGS>
void* TDicRemove(TDic<TPARAMS>* dic, const CHT* key) {
  ISY index = TTableFind<TPARAMS>(dic->keys, key);
  if (index < 0) return index;
  TTableRemove<TPARAMS>(dic->keys, index);
  return TDicListRemove<TPARAMS>(dic, index);
}

/* Adds a string to the end of the Dic.
@return The index upon success or -1 upon failure. */
template <TARGS>
ISZ TDicPop(TDic<TPARAMS>* dic) {
  return TDicRemove<TPARAMS>(dic, dic->keys.map->count - 1);
}

/* Adds a key-value tuple to the end of the Dic.
@return The index upon success or -1 upon failure. */
template <typename T, TARGS>
inline ISY TDicInsert(TDic<TPARAMS>* dic, const CHT* key, T item,
                      ISY index = cPush) {
  A_ASSERT(dic);
  if (!key) return cErrorInputNil;

  if (index == cAnywhere)
    index = TTableAdd<TPARAMS>(&dic->keys, key);
  else if (index == cPush)
    index = (index <= 0) ? 0 : dic->keys.count - 1;
  //D_COUT("\nAdding key:\"" << key << "\" item:" << item << 
  //       " into index:" << index);
  if (index < 0) return index;
  auto list = TDicList<TPARAMS>(dic);
#if DEBUG_THIS
  TListPrint<COut, ISY>(list);
#endif
  ISY result = ISY(TListInsert<ISZ, DTB>(list, item));
  if (result < 0) {
    D_COUT("\nFailed to insert with error " << result << ':'
                                            << STRError(result));
    TDicRemove<TPARAMS>(dic, index);
  }
  return result;
}
template <TARGS>
inline ISY TDicInsert(TDic<TPARAMS>* dic, const CHT* key, ISA item) {
  return TDicInsert<ISA, TPARAMS>(dic, key, item);
}
template <TARGS>
inline ISY TDicInsert(TDic<TPARAMS>* dic, const CHT* key, IUA item) {
  return TDicInsert<ISA, TPARAMS>(dic, key, item);
}
template <TARGS>
inline ISY TDicInsert(TDic<TPARAMS>* dic, const CHT* key, ISB item) {
  return TDicInsert<ISB, TPARAMS>(dic, key, item);
}
template <TARGS>
inline ISY TDicInsert(TDic<TPARAMS>* dic, const CHT* key, IUB item) {
  return TDicInsert<ISB, TPARAMS>(dic, key, item);
}
template <TARGS>
inline ISY TDicInsert(TDic<TPARAMS>* dic, const CHT* key, ISC item) {
  return TDicInsert<ISC, TPARAMS>(dic, key, item);
}
template <TARGS>
inline ISY TDicInsert(TDic<TPARAMS>* dic, const CHT* key, IUC item) {
  return TDicInsert<ISC, TPARAMS>(dic, key, item);
}
template <TARGS>
inline ISY TDicInsert(TDic<TPARAMS>* dic, const CHT* key, ISD item) {
  return TDicInsert<ISD, TPARAMS>(dic, key, item);
}
template <TARGS>
inline ISY TDicInsert(TDic<TPARAMS>* dic, const CHT* key, IUD item) {
  return TDicInsert<IUD, TPARAMS>(dic, key, item);
}
#if USING_FPC == YES_0
template <TARGS>
inline ISY TDicInsert(TDic<TPARAMS>* dic, const CHT* key, FPC item) {
  return TDicInsert<FPC, TPARAMS>(dic, key, item);
}
#endif
#if USING_FPD == YES_0
template <TARGS>
inline ISY TDicInsert(TDic<TPARAMS>* dic, const CHT* key, FPD item) {
  return TDicInsert<FPD, TPARAMS>(dic, key, item);
}
#endif

/* Adds a string to the end of the Dic, auto-growing if neccissary.
@return The index upon success or -1 if the obj can't grow anymore. */
template <typename T, TARGS, typename BUF>
ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, T item,
               ISY index = cPush) {
  if (!key) return cErrorInputNil;
  auto dic = obj.OriginAs<TDic<TPARAMS>*>();
  D_COUT("\nAdding:\"" << item << '\"');
  ISY result = TDicInsert<T, TPARAMS>(dic, key, item, index);
  while (result < 0) {
    if (!TDicGrow<TPARAMS>(obj.AJT())) {
      D_COUT("\n\nFailed to grow.\n\n");
      return cErrorBufferOverflow;
    } else {
      D_COUT("\nSuccesseded in growing.");
    }
    result = TDicInsert<T, TPARAMS>(dic, key, item, index);
  }
  return result;
}
template <TARGS, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISA item,
                      ISY index) {
  return TDicInsert<ISA, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUA item,
                      ISY index) {
  return TDicInsert<ISA, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISB item,
                      ISY index) {
  return TDicInsert<ISB, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUB item,
                      ISY index) {
  return TDicInsert<ISB, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISC item,
                      ISY index = cPush) {
  return TDicInsert<ISC, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUC item,
                      ISY index = cPush) {
  return TDicInsert<ISC, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISD item,
                      ISY index = cPush) {
  return TDicInsert<ISD, TPARAMS, BUF>(obj, key, item, index);
}
template <TARGS, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUD item,
                      ISY index = cPush) {
  return TDicInsert<IUD, TPARAMS, BUF>(obj, key, item, index);
}
#if USING_FPC == YES_0
template <TARGS, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, FPC item,
                      ISY index = cPush) {
  return TDicInsert<FPC, TPARAMS, BUF>(obj, key, item, index);
}
#endif
#if USING_FPD == YES_0
template <TARGS, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, FPD item,
                      ISY index = cPush) {
  return TDicInsert<FPD, TPARAMS, BUF>(obj, key, item, index);
}
#endif

template <TARGS, typename BUF>
ISZ TDicCharCount(TDic<TPARAMS>* dic) {
  return (ISZ)(TDicEnd<TPARAMS>(dic) - TDicStart<TPARAMS>(dic));
}
template <TARGS, typename BUF>
BOL TDicWrite(TDic<TPARAMS>* destination, TDic<TPARAMS>* soure) {
  return true;
}

/* Adds a string to the end of the Dic.
@return The index upon success or -1 upon failure. */
template <TARGS>
CHT* TDicPop(TDic<TPARAMS>* dic) {
  if (dic->offsets.count == 0) return nullptr;
  ISZ offset = TStackPop<ISZ, ISZ>(dic->offsets), top = dic->top;
  dic->top = offset;
  return reinterpret_cast<CHT*>(reinterpret_cast<ISW>(dic) + offset);
}

/* Searches for the given string in the dic.
@return -1 if the dic doesn't contain the string or the index if it does. */
template <TARGS>
ISZ TDicFind(TDic<TPARAMS>* dic, const CHT* string) {
  D_ASSERT(dic);
  D_ASSERT(string);
  return TTableFind<CHT, ISZ>(dic->keys, string);
}

/* An ASCII Dic Autoject. */
template <TARGS, ISZ cSize = 512,
          typename BUF = TBUF<cSize, CHT, ISZ, TString<ISN>>>
class ADic {
  AArray<IUA, ISZ, BUF> obj_;  //< An Auto-Array object.
 public:
  enum { cCountDefault = cSize / 16 };
  /* Constructs a Dic. */
  ADic(ISY count_max = cCountDefault) { TDicInit<TPARAMS>(This(), count_max); }

  /* Constructs a Dic subclass.
  @param factory SocketFactory to call when the String overflows. */
  ADic(SocketFactory socket_factory, ISY count = cCountDefault)
      : obj_(socket_factory) {
    TDicInit<TPARAMS>(This(), count);
  }

  /* Constructs a Dic subclass.
  @param factory SocketFactory to call when the String overflows. */
  ADic(SocketFactory socket_factory, ISZ size = CDicSizeDefault<TPARAMS>(),
       ISY count = CDicCountDefault<TPARAMS>())
      : obj_(socket_factory) {
    TDicInit<TPARAMS>(This(), count);
  }

  /* Gets the max number of associative array elements. */
  inline ISZ Size() { return obj_.Size(); }

  /* Gets the size of the Dictionary in bytes. */
  inline ISZ SizeBytes() { return obj_.SizeBytes(); }

  /* Gets the size of the Dictionary in words. */
  inline ISZ SizeWords() { return obj_.SizeWords(); }

  /* Gets the number of elements in the dictionary. */
  inline ISY Count() { return This()->keys->map->count; }

  /* Inserts the key and item on into the Table and List at the given index.
  @return The index of the string in the Dic. */
  inline ISY Insert(const CHT* key, ISA item, ISY index = cPush) {
    return TDicInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUA item, ISY index = cPush) {
    return TDicInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISB item, ISY index = cPush) {
    return TDicInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUB item, ISY index = cPush) {
    return TDicInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISC item, ISY index = cPush) {
    return TDicInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUC item, ISY index = cPush) {
    return TDicInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISD item, ISY index = cPush) {
    return TDicInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUD item, ISY index = cPush) {
    return TDicInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
#if USING_FPC == YES_0
  inline ISY Insert(const CHT* key, FPC item, ISY index = cPush) {
    return TDicInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
#endif
#if USING_FPD == YES_0
  inline ISY Insert(const CHT* key, FPD item, ISY index = cPush) {
    return TDicInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }
#endif
  inline ISY Insert(const CHT* key, const CHT* item, ISY index = cPush) {
    return TDicInsert<TPARAMS, BUF>(AJT_ARY(), key, item, index);
  }

  /* Removes the string at the given index from the Dic. */
  inline void* Remove(ISY index) { return TDicRemove<TPARAMS>(This(), index); }

  /* Removes the string at the given index from the Dic. */
  inline void* Remove(const CHT* key) {
    return TDicRemove<TPARAMS>(This(), key);
  }

  /* Removes the string at the given index from the Dic. */
  inline ISZ Pop() { return TDicRemove<TPARAMS>(This()); }

  /* Gets the string at the given index. */
  inline CHT* Get(ISY index) { return TTableGet<TPARAMS>(This(), index); }

  /* Searches for the given string.
  @return -1 if the Dic doesn't contain the string or the index if it does.
*/
  inline ISZ Find(const CHT* string) {
    return TDicFind<TPARAMS>(This(), string);
  }

  /* Gets the Autoject. */
  inline Autoject AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array. */
  inline AArray<IUA, ISZ, BUF>& AJT_ARY() { return obj_; }

  /* Gets the ASCII Object. */
  inline TDic<TPARAMS>* This() { return obj_.OriginAs<TDic<TPARAMS>*>(); }

  /* Prints this object to the Printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    TDicPrint<Printer, TPARAMS>(o, This());
    return o;
  }

  /* Prints this object to the stdout. */
  inline void COut() { PrintTo<_::COut>(_::COut().Star()); }
};

}  //< namespace _
#endif
#endif
