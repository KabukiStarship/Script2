/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /strand.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-9 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>

#ifndef SCRIPT2_T_STRAND
#define SCRIPT2_T_STRAND 1

#include "array.hpp"

#if SEAM >= SCRIPT2_STRAND
#include "stringf.hpp"
#include "typevalue.h"

#if SEAM == SCRIPT2_STRAND
#include "_debug.inl"
#define D_COUT_STRAND(strand) \
  TStrandPrint<COut, CHT, ISZ>(COut().Star(), strand)
#else
#include "_release.inl"
#define D_COUT_STRAND(strand)
#endif

namespace _ {

/* An ASCII Object composed of a UTF-8/ASCII, UTF-16, or UTF-32 cursor. */
template <typename ISZ>
struct TStrand {
  ISZ size;  //< Size of the ASCII Object.
};

template <typename T, typename ISZ>
inline ISZ TSizeBytes(TStrand<ISZ>* strand) {
  return TSizeBytes<T, ISZ, TStrand<ISZ>*>(reinterpret_cast<UIW*>(strand));
}
template <typename T, typename ISZ>
inline ISZ TSizeWords(TStrand<ISZ>* strand) {
  return TSizeWords<T, ISZ, TStrand<ISZ>*>(reinterpret_cast<UIW*>(strand));
}

/* Gets the first character in the strand. */
template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TSTRStart(TStrand<ISZ>* strand) {
  return TPtr<CHT>(strand, sizeof(TStrand<ISZ>));
}
template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TSTRStart(UIW* origin) {
  return TSTRStart<CHT, ISZ>(reinterpret_cast<TStrand<ISZ>*>(origin));
}

/* Searches for the stop of the strand. */
template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TSTRStop(void* origin) {
  ISZ size = reinterpret_cast<TStrand<ISZ>*>(origin)->size;
  CHT* start = TSTRStart<CHT, ISZ>(reinterpret_cast<TStrand<ISZ>*>(origin));
  return start + size - 1;
}

/* Gets the stop char of the strand. */
template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TSTRStop(void* origin, ISW size) {
  CHT* ptr = reinterpret_cast<CHT*>(TSTRStart<CHT, ISZ>(origin));
  return ptr + size - 1;
}

template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TStrandReset(TStrand<ISZ>* strand) {
  CHT* start = TSTRStart<CHT, ISN>(strand);
  *start = 0;
  return start;
}

/* Initializes an ASCII Strand. */
template <typename ISZ = ISN, typename CHT = CHR>
inline TStrand<ISZ>* TStrandInit(TStrand<ISZ>* strand, ISZ size) {
  if (!strand || size < 1) return strand;
  strand->size = size;
  TStrandReset<CHT, ISZ>(strand);
  return strand;
}

/* Initializes an ASCII Strand. */
template <typename CHT = CHR, typename ISZ = ISN>
inline CHT* TStrandInit(UIW* obj, ISZ size) {
  return TStrandInit<ISZ, CHT>(reinterpret_cast<TStrand<ISZ>*>(obj), size);
}

/* Prints this object to the given printer. */
template <typename Printer, typename CHT = CHR, typename ISZ = ISN>
Printer& TStrandPrint(Printer& o, TStrand<ISZ>* strand) {
  if (!strand) return o;
  CHT* start = TSTRStart<CHT, ISZ>(strand);
  ISZ size = strand->size;
  o << Linef("\n+---\n| TStrand<CH") << CHT('0' + sizeof(CHT)) << ",SI"
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
inline Printer& TStrandPrint(Printer& o, Autoject autoject) {
  return TStrandPrint<Printer, CHT, ISZ>(
      o, reinterpret_cast<TStrand<ISZ>*>(autoject.origin));
}

template <typename CHT = CHR, typename ISZ = ISN>
UIW* TStrandClone(Autoject& obj) {
  UIW* origin = obj.origin;  //
  ISZ size = TSize<ISZ>(origin);
  UIW* new_begin = TArrayNew<CHT, ISZ, TStrand<ISZ>>(size);
  D_COUT(" new size:" << TSize<ISZ>(new_begin));
  TSPrinter<CHT> new_utf(new_begin);
  CHT* start = TSTRStart<CHT>(origin);
  new_utf << start;
  D_COUT("\nCopying \"" << start << "\" with result:\""
                        << TSTRStart<CHT>(new_begin) << '\"');
  return new_begin;
}

/* Gets the size from the strand at the given origin address. */
template <typename ISZ = ISN>
inline ISZ TStrandSize(UIW* origin) {
  return reinterpret_cast<TStrand<ISZ>*>(origin)->size;
}

template <typename CHT = CHR, typename ISZ = ISN>
BOL TStrandGrow(Autoject& obj, TSPrinter<CHT, ISZ>& utf) {
  UIW* origin = obj.origin;
  ISZ size = TStrandSize<ISZ>(origin), new_size = size << 1,
      new_size_bytes = TSizeBytes<CHT, ISZ, TStrand<ISZ>>(new_size);
  if (!TCanGrow<ISZ>(new_size_bytes)) return false;
  size = new_size;
  D_COUT(" new_size:" << new_size << " new_size_bytes:" << new_size_bytes);

  UIW* new_begin = TArrayNew<CHT, ISZ, TStrand<ISZ>>(obj.socket_factory, size);
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
void TStrandSPrint(Autoject& obj, TSPrinter<CHT>& sprinter, T item) {
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

      if (!TStrandGrow<CHT, ISZ>(obj, sprinter)) return;

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
  // D_COUT_STRAND(obj);
}

/* An ASCII Strand that can auto-grow from stack to heap.

The count of the string is defined as the maximimum chars that can fit in the
buffer, including the nil-term CHA.

This class is designed to take advantage of the behavior of the C++ operator
overloads. When you have a string of overloads, the objects get destructed
in the opposite order then where called.

# Initialization

A Strand may be initialed to print to the socket or to a dynamically allocated
string. This behavior is configured with the constructors. The SocketFactory can
either be configured using the class template argument cFactory1_. If the
obj_.Factory () is nil then it will get replaced with the foo.

#

@code
AStrand<> (TBUF<64>).Star ("Hello ") << "world!";
@endcode

# Dynamic Allocated Strands

Strands that use dynamic memory use the TC:

@code
AStrand<IUC, TBUF<64>> () << "Hello world!";
@endcode
*/
template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_ = cSTRCount,
          typename BUF = TBUF<cSize_, CHT, ISZ, TStrand<ISZ>>>
class AStrand {
  AArray<CHT, ISZ, BUF> obj_;  //< AutoArray of CHT(s).
  TSPrinter<CHT> sprinter_;    //< UTF for the strand.

 public:
  static constexpr DT2 Type() {
    return CTypeVector(CTypeChar<CHT>(), cARY, CTypeSize<ISZ>());
  }

  /* Constructs a Strand that auto-grows from stack to heap.
  @param factory SocketFactory to call when the Strand overflows. */
  AStrand() : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(CHA item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(const CHA* item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

#if USING_UTF16 == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(const CHB* item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }
#endif

#if USING_UTF32 == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(CHC item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }
#endif
  /* Constructs a Strand and prints the given item. */
  AStrand(const CHC* item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(ISA item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(IUA item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(ISB item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(IUB item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(ISC item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(IUC item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(ISD item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(IUD item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

#if USING_FPC == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(FPC item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }
#endif
#if USING_FPD == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(FPD item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }
#endif

  /* Constructs a Strand and prints the given item. */
  AStrand(Hexf item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(Binaryf item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, ISZ>(This());
    Reset();
    Print(item);
  }

  /* Resets the sprinter_ to the given word-aligned buffer. */
  inline void Reset() { sprinter_.Set(TStrandReset<CHT, ISZ>(This())); }

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

  /* Prints a item to the strand.
  @return A reference to this. */
  inline AStrand& Print(CHA item) { return Print<CHA>(item); }
  inline AStrand& Print(const CHA* item) { return Print<const CHA*>(item); }
#if USING_UTF16 == YES_0
  inline AStrand& Print(CHB item) { return Print<CHB>(item); }
  inline AStrand& Print(const CHB* item) { return Print<const CHB*>(item); }
#endif
#if USING_UTF32 == YES_0
  inline AStrand& Print(CHC item) { return Print<CHC>(item); }
  inline AStrand& Print(const CHC* item) { return Print<const CHC*>(item); }
#endif
  inline AStrand& Print(ISC item) { return Print<ISC>(item); }
  inline AStrand& Print(IUC item) { return Print<IUC>(item); }
  inline AStrand& Print(ISD item) { return Print<ISD>(item); }
  inline AStrand& Print(IUD item) { return Print<IUD>(item); }
#if USING_FPC == YES_0
  inline AStrand& Print(FPC item) { return Print<FPC>(item); }
#endif
#if USING_FPD == YES_0
  inline AStrand& Print(FPD item) { return Print<FPD>(item); }
#endif

  /* Gets the size in elements. */
  inline ISZ Size() { return obj_.Size(); }

  /* Gets the total ASCII Object size in bytes. */
  inline ISZ SizeBytes() { return obj_.SizeBytes<TStrand<ISZ>>(AJT()); }

  /* Gets the total ASCII Object size in words. */
  inline ISZ SizeWords() { return obj_.SizeWords<TStrand<ISZ>>(AJT()); }

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

  /* Checks if this Strand to the other string are equivalent.
  @return Nil if they Strings are not equivalent and a pointer to the next CHA
  after the end of the equivalent part of this strand upon success. */
  inline CHT Equals(const CHT* other) { return TSTRFind(Start(), other); }

  /* Checks to see if the sprinter_ is using static memory. */
  inline BOL IsStatic() { return obj_.Socket().Contains(sprinter_.cursor); }

  /* Gets the obj of the Console obj. */
  inline AArray<CHT, ISZ, BUF>& Array() { return obj_; }

  /* Gets the obj of the Console obj. */
  inline Autoject& AJT() { return obj_.OBJ(); }

  /* Gets the obj.origin as a TStrand<ISC>. */
  inline TStrand<ISZ>* This() { return obj_.OriginAs<TStrand<ISZ>*>(); }

  template <typename T>
  inline AStrand& Print(T item) {
    TStrandSPrint<T, CHT>(obj_.AJT(), sprinter_, item);
    return *this;
  }

  /* Prints this object to the given printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TStrandPrint<Printer, CHT, ISZ>(o, This());
  }

  inline void CPrint() { PrintTo<COut>(COut().Star()); }
};

/*
#if USING_UTF1 == YES_0
using Strand1 = TStrand<CHA>;
#endif
#if USING_UTF2 == YES_0
using Strand2 = TStrand<CHB>;
#endif
#if USING_UTF4 == YES_0
using Strand4 = TStrand<CHC>;
#endif*/

}  // namespace _

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj,
    _::AStrand<CHT, ISZ, cSize_, BUF>& item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, const CHA* item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

#if USING_UTF16 == YES_0
template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, const CHB* item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

#if USING_UTF32 == YES_0
template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, const CHC* item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, CHC item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, CHA item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
/*
template <typename CHT = CHR, ISN kCount_, typename BUF>
inline _::AStrand<CHT, kCount_, BUF>& operator<<(
    _::AStrand<CHT, kCount_, BUF>& obj, CHB item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print (item);
  D_COUT_OBJ (obj);
  return obj;
}*/

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, IUA item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, ISB item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, IUB item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, ISC item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, IUC item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, ISD item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, IUD item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

#if USING_FPC == YES_0
template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, FPC item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif
#if USING_FPD == YES_0
template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, FPD item) {
  _::AStrand<CHT, ISZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, _::Hexf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, _::Binaryf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, _::Centerf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, _::Rightf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, _::Linef item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, _::Headingf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename ISZ = ISN, ISZ cSize_, typename BUF>
inline _::AStrand<CHT, ISZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, ISZ, cSize_, BUF>& obj, _::Charsf item) {
  return obj.Print(item);
}

#endif
#endif
