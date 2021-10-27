/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /String.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#ifndef SCRIPT2_STRING_DECIMPL
#define SCRIPT2_STRING_DECIMPL
#include "Array.hpp"
#if SEAM >= SCRIPT2_STRING
#include "Stringf.hpp"
#include "TypeValue.h"
#if SEAM == SCRIPT2_STRING
#include "_Debug.inl"
#define D_COUT_STRING(string) \
  TStringPrint<COut, CHT, ISZ>(COut().Star(), string)
#else
#include "_Release.inl"
#define D_COUT_STRING(string)
#endif
namespace _ {

/* An ASCII Object composed of a UTF-8/ASCII, UTF-16, or UTF-32 cursor. */
template <typename ISZ>
struct TString {
  ISZ size;  //< Size of the ASCII Object.
};

template <typename T, typename ISZ>
inline ISZ TSizeBytes(TString<ISZ>* string) {
  return TSizeBytes<T, ISZ, TString<ISZ>*>(reinterpret_cast<IUW*>(string));
}
template <typename T, typename ISZ>
inline ISZ TSizeWords(TString<ISZ>* string) {
  return TSizeWords<T, ISZ, TString<ISZ>*>(reinterpret_cast<IUW*>(string));
}

/* Gets the first character in the string. */
template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TSTRStart(TString<ISZ>* string) {
  return TPtr<CHT>(string, sizeof(TString<ISZ>));
}
template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TSTRStart(IUW* origin) {
  return TSTRStart<CHT, ISZ>(reinterpret_cast<TString<ISZ>*>(origin));
}

/* Searches for the stop of the string. */
template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TSTRStop(void* origin) {
  ISZ size = reinterpret_cast<TString<ISZ>*>(origin)->size;
  CHT* start = TSTRStart<CHT, ISZ>(reinterpret_cast<TString<ISZ>*>(origin));
  return start + size - 1;
}

/* Gets the stop char of the string. */
template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TSTRStop(void* origin, ISW size) {
  CHT* ptr = reinterpret_cast<CHT*>(TSTRStart<CHT, ISZ>(origin));
  return ptr + size - 1;
}

template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TStringReset(TString<ISZ>* string) {
  CHT* start = TSTRStart<CHT, ISN>(string);
  *start = 0;
  return start;
}

/* Initializes an ASCII String. */
template <typename ISZ = ISN, typename CHT = CHR>
inline TString<ISZ>* TStringInit(TString<ISZ>* string, ISZ size) {
  if (!string || size < 1) return string;
  string->size = size;
  TStringReset<CHT, ISZ>(string);
  return string;
}

/* Initializes an ASCII String. */
template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TStringInit(IUW* obj, ISZ size) {
  return TStringInit<ISZ, CHT>(reinterpret_cast<TString<ISZ>*>(obj), size);
}

/* Prints this object to the given printer. */
template <typename Printer, typename CHT = CHR, typename ISZ = ISN>
Printer& TStringPrint(Printer& o, TString<ISZ>* string) {
  if (!string) return o;
  CHT* start = TSTRStart<CHT, ISZ>(string);
  ISZ size = string->size;
  o << Linef("\n+---\n| TString<CH") << CHT('0' + sizeof(CHT)) << ",IS"
    << CHT('0' + sizeof(ISZ)) << "> size:" << size << Linef("\n+---\n| \"");
  ISW column_count = cConsoleWidth;
  ISZ length = 0;
  CHL c;
  const CHT* cursor = SScan(start, c);
  while (c) {
    ISW column = 2;
    while (++column < column_count) {
      ++length;
      o << c;
      cursor = SScan(cursor, c);
      if (!c) goto PrintBottomLine;
    }
    o << "\n| ";
  }
PrintBottomLine:
  return o << "\"\n| length:" << TSTRLength<CHT>(start) << Linef("\n+---");
}

template <typename Printer, typename CHT = CHR, typename ISZ = ISN>
inline Printer& TStringPrint(Printer& o, Autoject autoject) {
  return TStringPrint<Printer, CHT, ISZ>(
      o, reinterpret_cast<TString<ISZ>*>(autoject.origin));
}

template <typename CHT = CHR, typename ISZ = ISN>
IUW* TStringClone(Autoject& obj) {
  IUW* origin = obj.origin;  //
  ISZ size = TSize<ISZ>(origin);
  IUW* new_begin = TArrayNew<CHT, ISZ, TString<ISZ>>(size);
  D_COUT(" new size:" << TSize<ISZ>(new_begin));
  TSPrinter<CHT> new_utf(new_begin);
  CHT* start = TSTRStart<CHT>(origin);
  new_utf << start;
  D_COUT("\nCopying \"" << start << "\" with result:\""
                        << TSTRStart<CHT>(new_begin) << '\"');
  return new_begin;
}

/* Gets the size from the string at the given origin address. */
template <typename ISZ = ISN>
inline ISZ TStringSize(IUW* origin) {
  return reinterpret_cast<TString<ISZ>*>(origin)->size;
}

template <typename CHT = CHR, typename ISZ = ISN>
BOL TStringGrow(Autoject& obj, TSPrinter<CHT, ISZ>& utf) {
  IUW* origin = obj.origin;
  ISZ size = TStringSize<ISZ>(origin), new_size = size << 1,
      new_size_bytes = TSizeBytes<CHT, ISZ, TString<ISZ>>(new_size);
  if (!TCanGrow<ISZ>(new_size_bytes)) return false;
  size = new_size;
  D_COUT(" new_size:" << new_size << " new_size_bytes:" << new_size_bytes);

  IUW* new_begin = TArrayNew<CHT, ISZ, TString<ISZ>>(obj.socket_factory, size);
  if (!new_begin) return false;
  D_COUT(" new size:" << new_size_bytes);

  TSPrinter<CHT, ISZ> new_sprinter(TSTRStart<CHT, ISZ>(new_begin), size);
  CHT* start = TSTRStart<CHT>(origin);
  new_sprinter << start;
  utf.Set(new_sprinter);
  D_COUT("\nCopying \"" << start << "\" with result:\""
                        << TSTRStart<CHT>(new_begin) << '\"');

  Delete(obj);
  obj.origin = new_begin;
  return true;
}

template <typename T, typename CHT = CHR, typename ISZ = ISN>
void TStringSPrint(Autoject& obj, TSPrinter<CHT>& sprinter, T item) {
  CHT *start = sprinter.start,  //
      *stop = sprinter.stop;
  D_COUT("\ncount:" << stop - start << " start:0x" << Hexf(start) << " stop:0x"
                    << Hexf(stop));
  auto cursor = _::TSPrint<CHT>(start, stop, item);
  if (!cursor) {
    *start = 0;  //< Replace the delimiter so we can copy the string.
    do {
      SocketFactory factory = obj.socket_factory,  //
          factory_heap = (SocketFactory)factory(nullptr, 0);
      D_ASSERT(factory);
      D_COUT(
          "\nPrint failed, attempting to auto-grow from "
          << ((factory != factory_heap) ? "stack-to-heap." : "heap-to-heap."));

      if (!TStringGrow<CHT, ISZ>(obj, sprinter)) return;

      if (factory != factory_heap) {
        factory = factory_heap;
        obj.socket_factory = factory;
      }

      cursor = _::TSPrint<CHT>(sprinter.start, sprinter.stop, item);
      D_COUT("\nRe-printed:\"" << sprinter.start << "\"");
      D_WARN(cursor);
    } while (!cursor);
  } else {
    D_COUT("\nPrinted:\"" << sprinter.start << "\"");
  }
  sprinter.start = cursor;
  // D_COUT_STRING(obj);
}

/* An ASCII String that can auto-grow from stack to heap.

The count of the string is defined as the maximimum chars that can fit in the
buffer, including the nil-term CHA.

This class is designed to take advantage of the behavior of the C++ operator
overloads. When you have a string of overloads, the objects get destructed
in the opposite order then where called.

# Initialization

A String may be initialed to print to the socket or to a dynamically allocated
string. This behavior is configured with the constructors. The SocketFactory can
either be configured using the class template argument cFactory1_. If the
obj_.Factory () is nil then it will get replaced with the foo.

#

@code
AString<> (TBUF<64>).Star ("Hello ") << "world!";
@endcode

# Dynamic Allocated Strings

Strings that use dynamic memory use the TC:

@code
AString<IUC, TBUF<64>> () << "Hello world!";
@endcode
*/
template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_ = cSTRCount,
          typename BUF = TBUF<cSize_, CHT, ISZ, TString<ISZ>>>
class AString {
  AArray<CHT, ISZ, BUF> obj_;  //< AutoArray of CHT(s).
  TSPrinter<CHT> sprinter_;    //< UTF for the string.

 public:
  static constexpr DT2 Type() {
    return CTypeVector(CTypeChar<CHT>(), cARY, CTypeSize<ISZ>());
  }

  /* Constructs a String that auto-grows from stack to heap.
  @param factory SocketFactory to call when the String overflows. */
  AString() : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
  }

  /* Constructs a String and prints the given item. */
  AString(CHA item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a String and prints the given item. */
  AString(const CHA* item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

#if USING_UTF16 == YES_0
  /* Constructs a String and prints the given item. */
  AString(const CHB* item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }
#endif

#if USING_UTF32 == YES_0
  /* Constructs a String and prints the given item. */
  AString(CHC item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }
#endif
  /* Constructs a String and prints the given item. */
  AString(const CHC* item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a String and prints the given item. */
  AString(ISA item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a String and prints the given item. */
  AString(IUA item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a String and prints the given item. */
  AString(ISB item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a String and prints the given item. */
  AString(IUB item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a String and prints the given item. */
  AString(ISC item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a String and prints the given item. */
  AString(IUC item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a String and prints the given item. */
  AString(ISD item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a String and prints the given item. */
  AString(IUD item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

#if USING_FPC == YES_0
  /* Constructs a String and prints the given item. */
  AString(FPC item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }
#endif
#if USING_FPD == YES_0
  /* Constructs a String and prints the given item. */
  AString(FPD item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }
#endif

  /* Constructs a String and prints the given item. */
  AString(Hexf item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a String and prints the given item. */
  AString(Binaryf item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Resets the sprinter_ to the given word-aligned buffer. */
  inline void Reset() { sprinter_.Set(TStringReset<CHT, ISZ>(This())); }

  /* Wipes the given */
  inline void WipeFreeSpace() { sprinter_.Wipe(); }

  /* Wipes the given */
  inline void Wipe() {
    Reset();
    WipeFreeSpace();
  }

  /* Gets the UTF. */
  inline TSPrinter<CHT>& Star() { return sprinter_; }

  /* @todo I had the auto-grow code in a template but I could not figure out
  which function wasn't working so I had to copy paste. This needs to get
  changed back to a template as soon as it's fixed thanks. */

  /* Prints a item to the string.
  @return A reference to this. */
  inline AString& Print(CHA item) { return Print<CHA>(item); }
  inline AString& Print(const CHA* item) { return Print<const CHA*>(item); }
#if USING_UTF16 == YES_0
  inline AString& Print(CHB item) { return Print<CHB>(item); }
  inline AString& Print(const CHB* item) { return Print<const CHB*>(item); }
#endif
#if USING_UTF32 == YES_0
  inline AString& Print(CHC item) { return Print<CHC>(item); }
  inline AString& Print(const CHC* item) { return Print<const CHC*>(item); }
#endif
  inline AString& Print(ISC item) { return Print<ISC>(item); }
  inline AString& Print(IUC item) { return Print<IUC>(item); }
  inline AString& Print(ISD item) { return Print<ISD>(item); }
  inline AString& Print(IUD item) { return Print<IUD>(item); }
#if USING_FPC == YES_0
  inline AString& Print(FPC item) { return Print<FPC>(item); }
#endif
#if USING_FPD == YES_0
  inline AString& Print(FPD item) { return Print<FPD>(item); }
#endif

  /* Gets the size in elements. */
  inline ISZ Size() { return obj_.Size(); }

  /* Gets the total ASCII Object size in bytes. */
  inline ISZ SizeBytes() { return obj_.SizeBytes<TString<ISZ>>(AJT()); }

  /* Gets the total ASCII Object size in words. */
  inline ISZ SizeWords() { return obj_.SizeWords<TString<ISZ>>(AJT()); }

  /* Returns the origin of the obj. */
  inline CHT* Start() { return TSTRStart<CHT, ISZ>(obj_.Origin()); }

  /* Returns the stop of the obj. */
  inline CHT* Stop() { return TSTRStop<CHT, ISZ>(obj_.Origin()); }

  /* Returns the stop of the obj. */
  inline CHA* End() { return TArrayEnd<ISZ>(obj_); }

  /* Calculates the space left in the buffer based on the sprinter_ pointers. */
  inline ISZ SpaceLeft() { return sprinter_.SpaceLeft(); }

  /* Searches for the given querry, returning the end CHT of the qeurry in this
  string. */
  inline CHT* Find(const CHT* querry) { return TSTRFind(Start(), querry); }

  /* Checks if this String to the other string are equivalent.
  @return Nil if they Strings are not equivalent and a pointer to the next CHA
  after the end of the equivalent part of this string upon success. */
  inline CHT Equals(const CHT* other) { return TSTRFind(Start(), other); }

  /* Checks to see if the sprinter_ is using static memory. */
  inline BOL IsStatic() { return obj_.Socket().Contains(sprinter_.cursor); }

  /* Gets the obj of the Console obj. */
  inline AArray<CHT, ISZ, BUF>& Array() { return obj_; }

  /* Gets the obj of the Console obj. */
  inline Autoject& AJT() { return obj_.OBJ(); }

  /* Gets the obj.origin as a TString<ISC>. */
  inline TString<ISZ>* This() { return obj_.OriginAs<TString<ISZ>*>(); }

  template <typename T>
  inline AString& Print(T item) {
    TStringSPrint<T, CHT>(obj_.AJT(), sprinter_, item);
    return *this;
  }

  /* Prints this object to the given printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TStringPrint<Printer, CHT, ISZ>(o, This());
  }

  inline void CPrint() { PrintTo<COut>(COut().Star()); }
};

/*
#if USING_UTF1 == YES_0
using String1 = TString<CHA>;
#endif
#if USING_UTF2 == YES_0
using String2 = TString<CHB>;
#endif
#if USING_UTF4 == YES_0
using String4 = TString<CHC>;
#endif*/

}  //< namespace _

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj,
    _::AString<CHT, ISZ, cSize_, BUF>& item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, const CHA* item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

#if USING_UTF16 == YES_0
template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, const CHB* item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

#if USING_UTF32 == YES_0
template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, const CHC* item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, CHC item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, CHA item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
/*
template <typename CHT = CHR, ISN kCount_, typename BUF>
inline _::AString<CHT, kCount_, BUF>& operator<<(
    _::AString<CHT, kCount_, BUF>& obj, CHB item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print (item);
  D_COUT_OBJ (obj);
  return obj;
}*/

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, IUA item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, ISB item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, IUB item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, ISC item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, IUC item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, ISD item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, IUD item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

#if USING_FPC == YES_0
template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, FPC item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif
#if USING_FPD == YES_0
template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, FPD item) {
  _::AString<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, _::Hexf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, _::Binaryf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, _::Centerf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, _::Rightf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, _::Linef item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, _::Headingf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AString<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AString<CHT, ISZ, cSize_, BUF>& obj, _::Charsf item) {
  return obj.Print(item);
}

#endif
#endif
