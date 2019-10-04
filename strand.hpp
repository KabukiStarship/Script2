/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /strand.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

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
  TStrandPrint<COut, CHT, SIZ>(COut().Star(), strand)
#else
#include "_release.inl"
#define D_COUT_STRAND(strand)
#endif

namespace _ {

/* An ASCII Object composed of a UTF-8/ASCII, UTF-16, or UTF-32 cursor. */
template <typename SIZ>
struct TStrand {
  SIZ size;  //< Size of the ASCII Object.
};

template <typename T, typename SIZ>
inline SIZ TSizeBytes(TStrand<SIZ>* strand) {
  return TSizeBytes<T, SIZ, TStrand<SIZ>*>(reinterpret_cast<UIW*>(strand));
}
template <typename T, typename SIZ>
inline SIZ TSizeWords(TStrand<SIZ>* strand) {
  return TSizeWords<T, SIZ, TStrand<SIZ>*>(reinterpret_cast<UIW*>(strand));
}

/* Gets the first character in the strand. */
template <typename CHT = CHR, typename SIZ = SIN>
inline CHT* TSTRStart(TStrand<SIZ>* strand) {
  return TPtr<CHT>(strand, sizeof(TStrand<SIZ>));
}
template <typename CHT = CHR, typename SIZ = SIN>
inline CHT* TSTRStart(UIW* origin) {
  return TSTRStart<CHT, SIZ>(reinterpret_cast<TStrand<SIZ>*>(origin));
}

/* Searches for the stop of the strand. */
template <typename CHT = CHR, typename SIZ = SIN>
inline CHT* TSTRStop(void* origin) {
  SIZ size = reinterpret_cast<TStrand<SIZ>*>(origin)->size;
  CHT* start = TSTRStart<CHT, SIZ>(reinterpret_cast<TStrand<SIZ>*>(origin));
  return start + size - 1;
}

/* Gets the stop char of the strand. */
template <typename CHT = CHR, typename SIZ = SIN>
inline CHT* TSTRStop(void* origin, SIW size) {
  CHT* ptr = reinterpret_cast<CHT*>(TSTRStart<CHT, SIZ>(origin));
  return ptr + size - 1;
}

template <typename CHT = CHR, typename SIZ = SIN>
inline CHT* TStrandReset(TStrand<SIZ>* strand) {
  CHT* start = TSTRStart<CHT, SIN>(strand);
  *start = 0;
  return start;
}

/* Initializes an ASCII Strand. */
template <typename SIZ = SIN, typename CHT = CHR>
inline TStrand<SIZ>* TStrandInit(TStrand<SIZ>* strand, SIZ size) {
  if (!strand || size < 1) return strand;
  strand->size = size;
  TStrandReset<CHT, SIZ>(strand);
  return strand;
}

/* Initializes an ASCII Strand. */
template <typename CHT = CHR, typename SIZ = SIN>
inline CHT* TStrandInit(UIW* obj, SIZ size) {
  return TStrandInit<SIZ, CHT>(reinterpret_cast<TStrand<SIZ>*>(obj), size);
}

/* Prints this object to the given printer. */
template <typename Printer, typename CHT = CHR, typename SIZ = SIN>
Printer& TStrandPrint(Printer& o, TStrand<SIZ>* strand) {
  if (!strand) return o;
  CHT* start = TSTRStart<CHT, SIZ>(strand);
  SIZ size = strand->size;
  o << Linef("\n+---\n| TStrand<CH") << CHT('0' + sizeof(CHT)) << ",SI"
    << CHT('0' + sizeof(SIZ)) << "> size:" << size << Linef("\n+---\n| \"");
  SIW column_count = cConsoleWidth;
  SIZ length = 0;
  CHA c;
  const CHT* cursor = SScan(start, c);
  while (c) {
    SIW column = 2;
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

template <typename Printer, typename CHT = CHR, typename SIZ = SIN>
inline Printer& TStrandPrint(Printer& o, Autoject autoject) {
  return TStrandPrint<Printer, CHT, SIZ>(
      o, reinterpret_cast<TStrand<SIZ>*>(autoject.origin));
}

template <typename CHT = CHR, typename SIZ = SIN>
UIW* TStrandClone(Autoject& obj) {
  UIW* origin = obj.origin;  //
  SIZ size = TSize<SIZ>(origin);
  UIW* new_begin = TArrayNew<CHT, SIZ, TStrand<SIZ>>(size);
  D_COUT(" new size:" << TSize<SIZ>(new_begin));
  TSPrinter<CHT> new_utf(new_begin);
  CHT* start = TSTRStart<CHT>(origin);
  new_utf << start;
  D_COUT("\nCopying \"" << start << "\" with result:\""
                        << TSTRStart<CHT>(new_begin) << '\"');
  return new_begin;
}

/* Gets the size from the strand at the given origin address. */
template <typename SIZ = SIN>
inline SIZ TStrandSize(UIW* origin) {
  return reinterpret_cast<TStrand<SIZ>*>(origin)->size;
}

template <typename CHT = CHR, typename SIZ = SIN>
BOL TStrandGrow(Autoject& obj, TSPrinter<CHT, SIZ>& utf) {
  UIW* origin = obj.origin;
  SIZ size = TStrandSize<SIZ>(origin), new_size = size << 1,
      new_size_bytes = TSizeBytes<CHT, SIZ, TStrand<SIZ>>(new_size);
  if (!TCanGrow<SIZ>(new_size_bytes)) return false;
  size = new_size;
  D_COUT(" new_size:" << new_size << " new_size_bytes:" << new_size_bytes);

  UIW* new_begin = TArrayNew<CHT, SIZ, TStrand<SIZ>>(obj.socket_factory, size);
  if (!new_begin) return false;
  D_COUT(" new size:" << new_size_bytes);

  TSPrinter<CHT, SIZ> new_sprinter(TSTRStart<CHT, SIZ>(new_begin), size);
  CHT* start = TSTRStart<CHT>(origin);
  new_sprinter << start;
  utf.Set(new_sprinter);
  D_COUT("\nCopying \"" << start << "\" with result:\""
                        << TSTRStart<CHT>(new_begin) << '\"');

  Delete(obj);
  obj.origin = new_begin;
  return true;
}

template <typename T, typename CHT = CHR, typename SIZ = SIN>
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

      if (!TStrandGrow<CHT, SIZ>(obj, sprinter)) return;

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
buffer, including the nil-term CH1.

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
AStrand<> (TUIB<64>).Star ("Hello ") << "world!";
@endcode

# Dynamic Allocated Strands

Strands that use dynamic memory use the TC:

@code
AStrand<UI4, TUIB<64>> () << "Hello world!";
@endcode
*/
template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_ = cSTRCount,
          typename BUF = TUIB<cSize_, CHT, SIZ, TStrand<SIZ>>>
class AStrand {
  AArray<CHT, SIZ, BUF> obj_;  //< AutoArray of CHT(s).
  TSPrinter<CHT> sprinter_;    //< UTF for the strand.

 public:
  static constexpr DT2 Type() {
    return cTypeVector(cTypeChar<CHT>(), cARY, cTypeSize<SIZ>());
  }

  /* Constructs a Strand that auto-grows from stack to heap.
  @param factory SocketFactory to call when the Strand overflows. */
  AStrand() : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(CH1 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(const CH1* item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

#if USING_UTF16 == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(const CH2* item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }
#endif

#if USING_UTF32 == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(CH4 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }
#endif
  /* Constructs a Strand and prints the given item. */
  AStrand(const CH4* item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI1 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI1 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI2 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI2 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI4 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI4 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI8 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI8 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

#if USING_FP4 == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(FP4 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }
#endif
#if USING_FP8 == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(FP8 item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }
#endif

  /* Constructs a Strand and prints the given item. */
  AStrand(Hexf item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(Binaryf item) : obj_(cSize_, TRamFactory<Type()>().Init<BUF>()) {
    sprinter_.stop = TSTRStop<CHT, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Resets the sprinter_ to the given word-aligned buffer. */
  inline void Reset() { sprinter_.Set(TStrandReset<CHT, SIZ>(This())); }

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
  inline AStrand& Print(CH1 item) { return Print<CH1>(item); }
  inline AStrand& Print(const CH1* item) { return Print<const CH1*>(item); }
#if USING_UTF16 == YES_0
  inline AStrand& Print(CH2 item) { return Print<CH2>(item); }
  inline AStrand& Print(const CH2* item) { return Print<const CH2*>(item); }
#endif
#if USING_UTF32 == YES_0
  inline AStrand& Print(CH4 item) { return Print<CH4>(item); }
  inline AStrand& Print(const CH4* item) { return Print<const CH4*>(item); }
#endif
  inline AStrand& Print(SI4 item) { return Print<SI4>(item); }
  inline AStrand& Print(UI4 item) { return Print<UI4>(item); }
  inline AStrand& Print(SI8 item) { return Print<SI8>(item); }
  inline AStrand& Print(UI8 item) { return Print<UI8>(item); }
#if USING_FP4 == YES_0
  inline AStrand& Print(FP4 item) { return Print<FP4>(item); }
#endif
#if USING_FP8 == YES_0
  inline AStrand& Print(FP8 item) { return Print<FP8>(item); }
#endif

  /* Gets the size in elements. */
  inline SIZ Size() { return obj_.Size(); }

  /* Gets the total ASCII Object size in bytes. */
  inline SIZ SizeBytes() { return obj_.SizeBytes<TStrand<SIZ>>(AJT()); }

  /* Gets the total ASCII Object size in words. */
  inline SIZ SizeWords() { return obj_.SizeWords<TStrand<SIZ>>(AJT()); }

  /* Returns the origin of the obj. */
  inline CHT* Start() { return TSTRStart<CHT, SIZ>(obj_.Origin()); }

  /* Returns the stop of the obj. */
  inline CHT* Stop() { return TSTRStop<CHT, SIZ>(obj_.Origin()); }

  /* Returns the stop of the obj. */
  inline CH1* End() { return TArrayEnd<SIZ>(obj_); }

  /* Calculates the space left in the buffer based on the sprinter_ pointers. */
  inline SIZ SpaceLeft() { return sprinter_.SpaceLeft(); }

  /* Searches for the given querry, returning the end CHT of the qeurry in this
  string. */
  inline CHT* Find(const CHT* querry) { return TSTRFind(Start(), querry); }

  /* Checks if this Strand to the other string are equivalent.
  @return Nil if they Strings are not equivalent and a pointer to the next CH1
  after the end of the equivalent part of this strand upon success. */
  inline CHT Equals(const CHT* other) { return TSTRFind(Start(), other); }

  /* Checks to see if the sprinter_ is using static memory. */
  inline BOL IsStatic() { return obj_.Socket().Contains(sprinter_.cursor); }

  /* Gets the obj of the Console obj. */
  inline AArray<CHT, SIZ, BUF>& Array() { return obj_; }

  /* Gets the obj of the Console obj. */
  inline Autoject& AJT() { return obj_.OBJ(); }

  /* Gets the obj.origin as a TStrand<SI4>. */
  inline TStrand<SIZ>* This() { return obj_.OriginAs<TStrand<SIZ>*>(); }

  template <typename T>
  inline AStrand& Print(T item) {
    TStrandSPrint<T, CHT>(obj_.AJT(), sprinter_, item);
    return *this;
  }

  /* Prints this object to the given printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TStrandPrint<Printer, CHT, SIZ>(o, This());
  }

  inline void CPrint() { PrintTo<COut>(COut().Star()); }
};

/*
#if USING_UTF1 == YES_0
using Strand1 = TStrand<CH1>;
#endif
#if USING_UTF2 == YES_0
using Strand2 = TStrand<CH2>;
#endif
#if USING_UTF4 == YES_0
using Strand4 = TStrand<CH4>;
#endif*/

}  // namespace _

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj,
    _::AStrand<CHT, SIZ, cSize_, BUF>& item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, const CH1* item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

#if USING_UTF16 == YES_0
template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, const CH2* item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

#if USING_UTF32 == YES_0
template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, const CH4* item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, CH4 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, CH1 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
/*
template <typename CHT = CHR, SIN kCount_, typename BUF>
inline _::AStrand<CHT, kCount_, BUF>& operator<<(
    _::AStrand<CHT, kCount_, BUF>& obj, CH2 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print (item);
  D_COUT_OBJ (obj);
  return obj;
}*/

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, UI1 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, SI2 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, UI2 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, SI4 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, UI4 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, SI8 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, UI8 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

#if USING_FP4 == YES_0
template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, FP4 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif
#if USING_FP8 == YES_0
template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, FP8 item) {
  _::AStrand<CHT, SIZ, cSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, _::Hexf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, _::Binaryf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, _::Centerf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, _::Rightf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, _::Linef item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, _::Headingf item) {
  return obj.Print(item);
}

template <typename CHT = CHR, typename SIZ = SIN, SIZ cSize_, typename BUF>
inline _::AStrand<CHT, SIZ, cSize_, BUF>& operator<<(
    _::AStrand<CHT, SIZ, cSize_, BUF>& obj, _::Charsf item) {
  return obj.Print(item);
}

#endif
#endif
