/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_strand.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#ifndef SCRIPT2_T_STRAND
#define SCRIPT2_T_STRAND 1

#if SEAM >= SCRIPT2_SEAM_STRAND
#include "c_ascii.h"
#include "c_strand.h"
#include "t_array.h"
#include "t_utf.h"

#if SEAM == SCRIPT2_SEAM_STRAND
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* An ASCII Object composed of a UTF-8/ASCII, UTF-16, or UTF-32 cursor. */
template <typename SIZ>
struct TStrand {
  SIZ size;  //< Size of the ASCII Object.
};

/* Utility class for printing blocks of Unicode characters. */
template <typename Char = CH1>
struct TChars {
  Char *start,  //< Start character adddress.
      *stop;    //< Stop character address.

  /* Foo: Masters of Bar. */
  TChars(Char* start, Char*) : start(start), stop(stop) {}
};

template <typename Char, typename T>
void TStrandPrint(Autoject& obj, TUTF<Char>& utf, T item,
                  AsciiFactory factory_heap) {
  Char *start = utf.start,  //
      *stop = utf.stop;
  auto cursor = ::_::Print(start, stop, item);
  if (!cursor) {
    *utf.start = 0;  //< Replace the delimiter so we can copy the string.
    SIW count = stop - start;
    do {
      AsciiFactory factory = obj.factory;
      DASSERT(factory);
      PRINTF("\nPrint failed, attempting to auto-grow from %s",
             (factory != factory_heap) ? "stack-to-heap." : "heap-to-heap.");

      SIW result = factory(obj, kFactoryGrow, reinterpret_cast<SIW>(&utf));
      if (result) {
        PRINTF("\nFactory exited with Error:%i:\"%s\".\n", (SIN)result,
               AsciiFactoryError(result));
        return;
      }
      if (factory != factory_heap) {
        factory = factory_heap;
        obj.factory = factory;
      }

      cursor = ::_::Print(utf.start, utf.stop, item);
      PRINT("\nRe-printed:\"");
      PRINT(utf.start);
      PRINT("\"");
      DWARN(cursor);
    } while (!cursor);
  } else {
    PRINT("\nPrinted:\"");
    PRINT(utf.start);
    PRINT("\"");
  }
  utf.start = cursor;
}

template <typename Char>
SIW TStrandFactory(Autoject& obj, SIW function, SIW arg, BOL using_heap) {
  SI4 size;
  UIW *begin = obj.begin, *new_begin;
  if (!begin) return kFactoryNilOBJ;
  switch (function) {
    case kFactoryDelete: {
      PRINTF("\nEntering Strand.Factory.%s.Delete:",
             using_heap ? "Heap" : "Stack");
      Delete(obj.begin, using_heap);
      PRINT(" Success.");
      return 0;
    }
    case kFactoryNew: {
      PRINTF("\nEntering Strand.Factory.%s.New: size:%i",
             using_heap ? "Heap" : "Stack", (SIN)arg);
      return reinterpret_cast<SIW>(New(arg));
    }
    case kFactoryGrow: {
      PRINTF("\nEntering Strand.Factory.%s.Grow:",
             using_heap ? "Heap" : "Stack");
      if (!arg) return kFactoryNilArg;
      UIW* new_begin = TArrayGrowDouble<SI4>(begin);
      if (!new_begin) return kFactoryCantGrow;
      PRINTF(" new size:%i", TSize<SI4>(new_begin));

      TUTF<Char> new_utf(new_begin);
      Char* start = TSTRStart<Char>(begin);
      new_utf << start;
      reinterpret_cast<TUTF<Char>*>(arg)->Set(new_utf);
      Char* new_start = TSTRStart<Char>(new_begin);
      PRINTF("\nCopying \"%s\" with result:\"%s\"", start, new_start);

      if (using_heap) delete[] begin;
      obj.begin = new_begin;
      return 0;
    }
    case kFactoryClone: {
      PRINTF("\nEntering Strand.Factory.%s.Clone:",
             using_heap ? "Heap" : "Stack");
      if (!arg) return kFactoryNilArg;
      Autoject* other = reinterpret_cast<Autoject*>(arg);
      begin = obj.begin;
      size = *reinterpret_cast<SI4*>(begin);
      new_begin = TArrayClone<SI4>(begin, size);
      if (!new_begin) return kFactoryCantGrow;
      other->begin = new_begin;
      other->factory = other->factory;
      return reinterpret_cast<SIW>(new_begin);
    }
    case kFactoryInfo: {
      return reinterpret_cast<SIW>("Strand");
    }
  }
  return kFactoryErrorCount;
}

/* */
template <typename Char>
static SIW TStrandFactoryStack(Autoject& obj, SIW function, SIW arg) {
  return TStrandFactory<Char>(obj, function, arg, kStack);
}

/* */
template <typename Char>
static SIW TStrandFactoryHeap(Autoject& obj, SIW function, SIW arg) {
  return TStrandFactory<Char>(obj, function, arg, kHeap);
}

/* An ASCII Strand that can auto-grow from stack to heap.

The count of the string is defined as the maximimum chars that can fit in the
buffer, including the nil-term CH1.

This class is designed to take advantage of the behavior of the C++ operator
overloads. When you have a string of overloads, the objects get destructed
in the opposite order then where called.

# Initialization

A Strand may be initialed to print to the socket or to a dynamically allocated
string. This behavior is configured with the constructors. The AsciiFactory can
either be configured using the class template argument kFactory1_. If the
obj_.Factory () is nil then it will get replaced with the foo.

#

@code
TStrand<> (TSocket<64>).Star ("Hello ") << "world!";
@endcode

# Dynamic Allocated Strands

Strands that use dynamic memory use the TC:

@code
TStrand<UI4, TSocket<64>> () << "Hello world!";
@endcode
*/
template <typename Char = CH1, SIN kCount_ = kSTRCount,
          typename BUF = TSocket<kCount_, Char, TStrand<SIN>>>
class AStrand {
 public:
  /* Constructs a Strand that auto-grows from stack to heap.
  @param factory ASCII Factory to call when the Strand overflows. */
  AStrand() : obj_(kCount_, FactoryInit()) { Reset(); }

  /* Constructs a Strand and prints the given item. */
  AStrand(CH1 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(const CH1* item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

#if USING_UTF16 == YES
  /* Constructs a Strand and prints the given item. */
  AStrand(const CH2* item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }
#endif

#if USING_UTF32 == YES
  /* Constructs a Strand and prints the given item. */
  AStrand(CH4 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }
#endif
  /* Constructs a Strand and prints the given item. */
  AStrand(const CH4* item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI1 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI1 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI2 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI2 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI4 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI4 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(SI8 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(UI8 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

#if USING_FP4 == YES
  /* Constructs a Strand and prints the given item. */
  AStrand(FP4 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }
#endif
#if USING_FP8 == YES
  /* Constructs a Strand and prints the given item. */
  AStrand(FP8 item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }
#endif

  /* Constructs a Strand and prints the given item. */
  AStrand(Hex item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  AStrand(Binary item) : obj_(kCount_, FactoryInit()) {
    Reset();
    Print(item);
  }

  /* Resets the utf_ to the given word-aligned buffer. */
  inline void Reset() { utf_.Set(obj_.BeginWord()); }

  /* Wipes the given */
  inline void WipeFreeSpace() { utf_.Wipe(); }

  /* Wipes the given */
  inline void Wipe() {
    Reset();
    WipeFreeSpace();
  }

  /* Gets the UTF. */
  inline TUTF<Char>& Star() { return utf_; }

  /* @todo I had the auto-grow code in a template but I could not figure out
  which function wasn't working so I had to copy paste. This needs to get
  changed back to a template as soon as it's fixed thanks. */

  /* Prints a CH1 to the strand.
  @return A UTF. */
  inline AStrand& Print(CH1 item) { return Print<CH1>(item); }

  inline AStrand& Print(const CH1* item) { return Print<const CH1*>(item); }

#if USING_UTF16 == YES
  inline AStrand& Print(CH2 item) { return Print<CH2>(item); }

  inline AStrand& Print(const CH2* item) { return Print<const CH2*>(item); }
#endif
#if USING_UTF32 == YES
  inline AStrand& Print(CH4 item) { return Print<CH4>(item); }

  inline AStrand& Print(const CH4* item) { return Print<const CH4*>(item); }
#endif
  inline AStrand& Print(SI4 item) { return Print<SI4>(item); }

  inline AStrand& Print(UI4 item) { return Print<UI4>(item); }

  inline AStrand& Print(SI8 item) { return Print<SI8>(item); }

  inline AStrand& Print(UI8 item) { return Print<UI8>(item); }

#if USING_FP4 == YES
  inline AStrand& Print(FP4 item) { return Print<FP4>(item); }
#endif
#if USING_FP8 == YES
  inline AStrand& Print(FP8 item) { return Print<FP8>(item); }
#endif

  /* Returns the begin of the obj. */
  inline Char* Start() { return TSTRStart<Char, SI4>(obj_.BeginWord()); }

  /* Returns the stop of the obj. */
  inline Char* Stop() { return TSTRStop<Char, SI4>(obj_.BeginWord()); }

  /* Returns the stop of the obj. */
  inline CH1* End() { return TArrayEnd<SI4>(obj_); }

  /* Calculates the space left in the buffer based on the utf_ pointers. */
  inline SIN SpaceLeft() { return utf_.SpaceLeft(); }

  /* Searches for the given querry, returning the end Char of the qeurry in this
  string. */
  inline Char* Find(const Char* querry) { return TSTRFind(Start(), querry); }

  /* Checks if this Strand to the other string are equivalent.
  @return Nil if they strings are not equivalent and a pointer to the next CH1
  after the end of the equivalent part of this strand upon success. */
  inline Char Equals(const Char* other) { return TSTRFind(Start(), other); }

  /* Checks to see if the utf_ is using static memory. */
  inline BOL IsStatic() { return obj_.Socket().Contains(utf_.cursor); }

  /* Gets the obj of the Console obj. */
  inline AArray<Char, SIN, BUF>& ARY() { return obj_; }

  /* Gets the obj of the Console obj. */
  inline Autoject& OBJ() { return obj_.OBJ(); }

  /* Prints this object to the given printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
#if DEBUG_SEAM
    o << "\nTStrand<CH" << (CH1)('0' + sizeof(Char))
      << "> size:" << (SIW)obj_.Size() << " space_left:" << (SIW)SpaceLeft()
      << " contents:\"" << Start() << '\"';
    return o;
#else
    return o << Start();
#endif
  }

  template <typename T>
  inline AStrand& Print(T item) {
    PRINTF("\nBefore:\"");
    PRINT(Start());
    PRINT("\"");
    TStrandPrint<Char, T>(obj_.AObj(), utf_, item, TStrandFactoryHeap<Char>);
    return *this;
  }

  /* Returns true if the buffer is a Socket and false if it's a Nil. */
  static constexpr BOL UsesStack() { return buffer_.Size() != 0; }

 private:
  TUTF<Char> utf_;  //< UTF for the strand.
  // AutoArray of Char(s).
  AArray<Char, SIN, BUF> obj_;

  /* Gets the AsciiFactory based on if the BUF is Nil or a TSocket. */
  constexpr AsciiFactory FactoryInit() {
    return obj_.UsesStack() ? TStrandFactoryStack<Char>
                            : TStrandFactoryHeap<Char>;
  }
};

/*
#if USING_UTF1 == YES
using Strand1 = TStrand<CH1>;
#endif
#if USING_UTF2 == YES
using Strand2 = TStrand<CH2>;
#endif
#if USING_UTF4 == YES
using Strand4 = TStrand<CH4>;
#endif*/

}  // namespace _

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj,
    ::_::AStrand<Char, kCount_, BUF>& item) {
  return obj;
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, const CH1* item) {
  return obj.Print(item);
}

#if USING_UTF16 == YES
template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, const CH2* item) {
  return obj.Print(item);
}
#endif

#if USING_UTF32 == YES
template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, const CH4* item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, CH4 item) {
  return obj.Print(item);
}
#endif

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, CH1 item) {
  return obj.Print(item);
}
/*
template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, CH2 item) {
  return obj.Print(item);
}*/

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, UI1 item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, SI2 item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, UI2 item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, SI4 item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, UI4 item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, SI8 item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, UI8 item) {
  return obj.Print(item);
}

#if USING_FP4 == YES
template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, FP4 item) {
  return obj.Print(item);
}
#endif
#if USING_FP8 == YES
template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, FP8 item) {
  return obj.Print(item);
}
#endif

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, ::_::Hex item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, ::_::TCenter<Char> item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, ::_::TRight<Char> item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, ::_::TLinef<Char> item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, ::_::THeadingf<Char> item) {
  return obj.Print(item);
}

template <typename Char, SIN kCount_, typename BUF>
inline ::_::AStrand<Char, kCount_, BUF>& operator<<(
    ::_::AStrand<Char, kCount_, BUF>& obj, ::_::TChars<Char> item) {
  return obj.Print(item);
}

#endif
#endif
