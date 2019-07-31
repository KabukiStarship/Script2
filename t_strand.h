/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_strand.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>

#ifndef SCRIPT2_T_STRAND
#define SCRIPT2_T_STRAND 1

#include "t_array.h"

#if SEAM >= SCRIPT2_STRAND
#include "c_avalue.h"
#include "t_string.h"

#if SEAM == SCRIPT2_STRAND
#include "module_debug.inl"
#define D_COUT_STRAND(strand) \
  TStrandPrint<COut, Char, SIZ>(COut().Star(), strand)
#else
#include "module_release.inl"
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
template <typename Char = CHR, typename SIZ = SIN>
inline Char* TSTRStart(TStrand<SIZ>* strand) {
  return TPtr<Char>(strand, sizeof(TStrand<SIZ>));
}
template <typename Char = CHR, typename SIZ = SIN>
inline Char* TSTRStart(UIW* begin) {
  return TSTRStart<Char, SIZ>(reinterpret_cast<TStrand<SIZ>*>(begin));
}

/* Searches for the stop of the strand. */
template <typename Char = CHR, typename SIZ = SIN>
inline Char* TSTRStop(void* begin) {
  SIZ size = reinterpret_cast<TStrand<SIZ>*>(begin)->size;
  Char* start = TSTRStart<Char, SIZ>(reinterpret_cast<TStrand<SIZ>*>(begin));
  return start + size - 1;
}

/* Gets the stop char of the strand. */
template <typename Char = CHR, typename SIZ = SIN>
inline Char* TSTRStop(void* begin, SIW size) {
  Char* ptr = reinterpret_cast<Char*>(TSTRStart<Char, SIZ>(begin));
  return ptr + size - 1;
}

template <typename Char = CHR, typename SIZ = SIN>
inline Char* TStrandReset(TStrand<SIZ>* strand) {
  Char* start = TSTRStart<Char, SIN>(strand);
  *start = 0;
  return start;
}

/* Initializes an ASCII Strand. */
template <typename SIZ = SIN, typename Char = CHR>
inline TStrand<SIZ>* TStrandInit(TStrand<SIZ>* strand, SIZ size) {
  if (!strand || size < 1) return strand;
  strand->size = size;
  TStrandReset<Char, SIZ>(strand);
  return strand;
}

/* Initializes an ASCII Strand. */
template <typename Char = CHR, typename SIZ = SIN>
inline Char* TStrandInit(UIW* obj, SIZ size) {
  return TStrandInit<SIZ, Char>(reinterpret_cast<TStrand<SIZ>*>(obj), size);
}

/* Prints this object to the given printer. */
template <typename Printer, typename Char = CHR, typename SIZ = SIN>
Printer& TStrandPrint(Printer& o, TStrand<SIZ>* strand) {
  if (!strand) return o;
  Char* start = TSTRStart<Char, SIZ>(strand);
  SIZ size = strand->size;
  o << Linef("\n+---\n| TStrand<CH") << Char('0' + sizeof(Char)) << ",SI"
    << Char('0' + sizeof(SIZ)) << "> size:" << size << Linef("\n+---\n| \"");
  SIW column_count = kConsoleWidth;
  SIZ length = 0;
  CHA c;
  const Char* cursor = SScan(start, c);
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
  return o << "\"\n| length:" << TSTRLength<Char>(start) << Linef("\n+---");
}

template <typename Printer, typename Char = CHR, typename SIZ = SIN>
inline Printer& TStrandPrint(Printer& o, Autoject autoject) {
  return TStrandPrint<Printer, Char, SIZ>(
      o, reinterpret_cast<TStrand<SIZ>*>(autoject.begin));
}

template <typename Char = CHR, typename SIZ = SIN>
UIW* TStrandClone(Autoject& obj) {
  UIW* begin = obj.begin;  //
  SIZ size = TSize<SIZ>(begin);
  UIW* new_begin = TArrayNew<Char, SIZ, TStrand<SIZ>>(size);
  D_COUT(" new size:" << TSize<SIZ>(new_begin));
  TSPrinter<Char> new_utf(new_begin);
  Char* start = TSTRStart<Char>(begin);
  new_utf << start;
  D_COUT("\nCopying \"" << start << "\" with result:\""
                        << TSTRStart<Char>(new_begin) << '\"');
  return new_begin;
}

/* Gets the size from the strand at the given begin address. */
template <typename SIZ = SIN>
inline SIZ TStrandSize(UIW* begin) {
  return reinterpret_cast<TStrand<SIZ>*>(begin)->size;
}

template <typename Char = CHR, typename SIZ = SIN>
BOL TStrandGrow(Autoject& obj, TSPrinter<Char, SIZ>& utf) {
  UIW* begin = obj.begin;
  SIZ size = TStrandSize<SIZ>(begin), new_size = size << 1,
      new_size_bytes = TSizeBytes<Char, SIZ, TStrand<SIZ>>(new_size);
  if (!TCanGrow<SIZ>(new_size_bytes)) return false;
  size = new_size;
  D_COUT("new_size:" << new_size << " new_size_bytes:" << new_size_bytes);

  UIW* new_begin = TArrayNew<Char, SIZ, TStrand<SIZ>>(obj.ram_factory, size);
  if (!new_begin) return false;
  D_COUT(" new size:" << new_size_bytes);

  TSPrinter<Char, SIZ> new_sprinter(TSTRStart<Char, SIZ>(new_begin), size);
  Char* start = TSTRStart<Char>(begin);
  new_sprinter << start;
  utf.Set(new_sprinter);
  D_COUT("\nCopying \"" << start << "\" with result:\""
                        << TSTRStart<Char>(new_begin) << '\"');

  Delete(obj);
  obj.begin = new_begin;
  return true;
}

template <typename T, typename Char = CHR, typename SIZ = SIN>
void TStrandSPrint(Autoject& obj, TSPrinter<Char>& sprinter, T item) {
  Char *start = sprinter.start,  //
      *stop = sprinter.stop;
  D_COUT("\ncount:" << stop - start << "start:0x" << Hexf(start) << " stop:0x"
                    << Hexf(stop));
  auto cursor = _::TSPrint<Char>(start, stop, item);
  if (!cursor) {
    *start = 0;  //< Replace the delimiter so we can copy the string.
    do {
      RamFactory factory = obj.ram_factory,  //
          factory_heap = RamFactoryHeap;
      D_ASSERT(factory);
      D_COUT(
          "\nPrint failed, attempting to auto-grow from "
          << ((factory != factory_heap) ? "stack-to-heap." : "heap-to-heap."));

      if (!TStrandGrow<Char, SIZ>(obj, sprinter)) return;

      if (factory != factory_heap) {
        factory = factory_heap;
        obj.ram_factory = factory;
      }

      cursor = _::TSPrint<Char>(sprinter.start, sprinter.stop, item);
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
string. This behavior is configured with the constructors. The RamFactory can
either be configured using the class template argument kFactory1_. If the
obj_.Factory () is nil then it will get replaced with the foo.

#

@code
AStrand<> (TBuf<64>).Star ("Hello ") << "world!";
@endcode

# Dynamic Allocated Strands

Strands that use dynamic memory use the TC:

@code
AStrand<UI4, TBuf<64>> () << "Hello world!";
@endcode
*/
template <typename Char = CHR, typename SIZ = SIN, SIZ kSize_ = kSTRCount,
          typename BUF = TBuf<kSize_, Char, SIZ, TStrand<SIZ>>>
class AStrand {
  AArray<Char, SIZ, BUF> obj_;  //< AutoArray of Char(s).
  TSPrinter<Char> sprinter_;    //< UTF for the strand.

 public:
  /* Constructs a Strand that auto-grows from stack to heap.
  @param factory RamFactory to call when the Strand overflows. */
  AStrand() : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(CH1 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(const CH1* item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

#if USING_UTF16 == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(const CH2* item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }
#endif

#if USING_UTF32 == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(CH4 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }
#endif
  /* Constructs a Strand and prints the given item. */
  AStrand(const CH4* item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI1 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI1 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI2 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI2 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI4 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI4 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI8 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI8 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

#if USING_FP4 == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(FP4 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }
#endif
#if USING_FP8 == YES_0
  /* Constructs a Strand and prints the given item. */
  AStrand(FP8 item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }
#endif

  /* Constructs a Strand and prints the given item. */
  AStrand(Hexf item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(Binaryf item) : obj_(kSize_) {
    sprinter_.stop = TSTRStop<Char, SIZ>(This());
    Reset();
    Print(item);
  }

  /* Resets the sprinter_ to the given word-aligned buffer. */
  inline void Reset() { sprinter_.Set(TStrandReset<Char, SIZ>(This())); }

  /* Wipes the given */
  inline void WipeFreeSpace() { sprinter_.Wipe(); }

  /* Wipes the given */
  inline void Wipe() {
    Reset();
    WipeFreeSpace();
  }

  /* Gets the UTF. */
  inline TSPrinter<Char>& Star() { return sprinter_; }

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

  /* Returns the begin of the obj. */
  inline Char* Start() { return TSTRStart<Char, SIZ>(obj_.Begin()); }

  /* Returns the stop of the obj. */
  inline Char* Stop() { return TSTRStop<Char, SIZ>(obj_.Begin()); }

  /* Returns the stop of the obj. */
  inline CH1* End() { return TArrayEnd<SIZ>(obj_); }

  /* Calculates the space left in the buffer based on the sprinter_ pointers. */
  inline SIZ SpaceLeft() { return sprinter_.SpaceLeft(); }

  /* Searches for the given querry, returning the end Char of the qeurry in this
  string. */
  inline Char* Find(const Char* querry) { return TSTRFind(Start(), querry); }

  /* Checks if this Strand to the other string are equivalent.
  @return Nil if they strings are not equivalent and a pointer to the next CH1
  after the end of the equivalent part of this strand upon success. */
  inline Char Equals(const Char* other) { return TSTRFind(Start(), other); }

  /* Checks to see if the sprinter_ is using static memory. */
  inline BOL IsStatic() { return obj_.Socket().Contains(sprinter_.cursor); }

  /* Gets the obj of the Console obj. */
  inline AArray<Char, SIZ, BUF>& Array() { return obj_; }

  /* Gets the obj of the Console obj. */
  inline Autoject& AJT() { return obj_.OBJ(); }

  /* Gets the obj.begin as a TStrand<SI4>. */
  inline TStrand<SIZ>* This() { return obj_.BeginAs<TStrand<SIZ>>(); }

  template <typename T>
  inline AStrand& Print(T item) {
    TStrandSPrint<T, Char>(obj_.AJT(), sprinter_, item);
    return *this;
  }

  /* Prints this object to the given printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TStrandPrint<Printer, Char, SIZ>(o, This());
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

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj,
    _::AStrand<Char, SIZ, kSize_, BUF>& item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, const CH1* item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

#if USING_UTF16 == YES_0
template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, const CH2* item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

#if USING_UTF32 == YES_0
template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, const CH4* item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, CH4 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, CH1 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
/*
template <typename Char = CHR, SIN kCount_, typename BUF>
inline _::AStrand<Char, kCount_, BUF>& operator<<(
    _::AStrand<Char, kCount_, BUF>& obj, CH2 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print (item);
  D_COUT_OBJ (obj);
  return obj;
}*/

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, UI1 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, SI2 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, UI2 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, SI4 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, UI4 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, SI8 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, UI8 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}

#if USING_FP4 == YES_0
template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, FP4 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif
#if USING_FP8 == YES_0
template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, FP8 item) {
  _::AStrand<Char, SIZ, kSize_, BUF>& result = obj.Print(item);
  D_COUT_OBJ(obj);
  return obj;
}
#endif

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, _::Hexf item) {
  return obj.Print(item);
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, _::Binaryf item) {
  return obj.Print(item);
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, _::Centerf item) {
  return obj.Print(item);
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, _::Rightf item) {
  return obj.Print(item);
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, _::Linef item) {
  return obj.Print(item);
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, _::Headingf item) {
  return obj.Print(item);
}

template <typename Char, typename SIZ, SIZ kSize_, typename BUF>
inline _::AStrand<Char, SIZ, kSize_, BUF>& operator<<(
    _::AStrand<Char, SIZ, kSize_, BUF>& obj, _::Charsf item) {
  return obj.Print(item);
}

#endif
#endif
