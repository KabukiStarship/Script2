/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tutf.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#if SEAM >= _0_0_0__02
#ifndef INCLUDED_SCRIPT_TSTRAND
#define INCLUDED_SCRIPT_TSTRAND 1

#include "tutf.h"

#include "casciidata.h"

#if SEAM == _0_0_0__02
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

template <typename SIN, typename Char>
Char* TStrandInit(UIW* obj, SIN size) {
  ASSERT(obj);
  ASSERT(size > 0);
  ASSERT((size | ~kWordBitsMask) == 0);
  *reinterpret_cast<UIW*>(obj) = size;
  return reinterpret_cast<Char*>(reinterpret_cast<UIW>(obj) + sizeof(SIN));
}

/* An ASCII String that can auto-grow from stack to heap.

This class is designed to take advantage of the behavior of the C++ operator
overloads. When you have a string_ of overloads, the objects get destructed
in the opposite order then where called, which is a obj push pop operation.

# Statically Allocated Strings

If it is null then the factory is treated as statically allocated factory.

@code
TStrand<> (TCOut<>) << "Hello world!";
@endcode

# Dynamic Allocated Strings

Strings that use dynamic memory use the DCOutAuto factory:

@code
TStrand<UI4> (TCOutAuto<>) << "Hello world!";
@endcode
*/
template <typename Char = char, AsciiFactory kFactory_ = TCOutAuto<Char>,
          SIN kLengthMax_ = 64>
class TStrand {
 public:
  enum {
    kSizeMax = (~(SIN)0) - sizeof(SIN) + 1,        //< Max size in bytes
    kCountMax = kSizeMax / sizeof(Char),           //< Max element of chars.
    kCountMin = (sizeof(SIN) / sizeof(Char)) + 1,  // Min element count.
    // kLengthMax bounded to the min max range.
    kLengthMax = (int)((kLengthMax_ < kCountMin)
                           ? kCountMin
                           : (kLengthMax_ > kCountMax - 1) ? kCountMax - 1
                                                           : kLengthMax_),
    kSize = (int)sizeof(SIN) + (kLengthMax + 1) * (int)sizeof(Char),
  };

  /* Constructs a Strand that auto-grows from stack to heap.
  @param factory ASCII Factory to call when the Strand overflows. */
  TStrand(AsciiFactory factory = nullptr)
      : obj_(socket_.Words(), factory),
        utf_(TStrandInit<SIN, Char>(socket_.Words(), socket_.SizeBytes()),
             kLengthMax) {
    // static_assert((kSize & (sizeof(Char)) == 0, "!(kSize & (sizeof (Char))");
    // static_assert(sizeof(SIN) >= sizeof(Char),
    //              "!(sizeof (SIN) >= sizeof (Char))");
    _::Printf(
        "\nTStrand(AsciiFactory factory)"
        "\nsocket_.Begin():0x%p socket_.End():0x%p"
        "\nTUTF:start:0x%p TUTF::stop:0x%p"
        "\nsizeof(SIN):%i Char count max:%i end space:%i\n",
        socket_.Begin(), socket_.End(), utf_.start, utf_.stop,
        (SIN)(reinterpret_cast<UIW>(utf_.start) -
              reinterpret_cast<UIW>(socket_.Begin())),
        (SIN)(utf_.stop - utf_.start),
        (SIN)(reinterpret_cast<UIW>(socket_.End()) -
              reinterpret_cast<UIW>(utf_.stop)));
    Terminate();
  }

  /* Constructs a strand from dynamic memory.
  @param size    Object size IN BYTES.
  @param factory Non-nil ASCII Factory. */
  TStrand(SIN size, AsciiFactory factory = TCOutAuto<Char>) {
    ASSERT(factory);
    static_assert(factory != nullptr, "factory != nullptr");
    UIW* socket = factory(nullptr, size, nullptr);
    obj_.Set(socket, factory);
    obj_.SetBegin(socket);
    utf_.Set(socket, size);
    Terminate();
  }

  /* Constructs the pointers to the buffer_.
  @param begin   Buffer begin address.
  @param size    Object size IN BYTES.
  @param factory ASCII Factory.  */
  TStrand(UIW* begin, SIN size, AsciiFactory factory = nullptr)
      : obj_(size, begin, factory), utf_(begin, size) {
    ASSERT(begin);
    Terminate();
  }

  /* Gets the UTF. */
  TUTF<Char> Print() {
    SIN size = TObjSize<SIN>(obj_);
    Char* start_ptr = reinterpret_cast<Char*>(
        reinterpret_cast<UIW>(obj_.start) + sizeof(SIN));
    return TUTF<Char>(start_ptr, start_ptr + (size >> TBitShiftCount<SIN>()));
  }

  /* Prints a char to the strand.
  @param item The item to utf.
  @return A UTF. */
  template <typename T>
  TUTF<Char> Print(T item) {
    UIW start = reinterpret_cast<UIW>(obj_.Begin());
    SIN size = *reinterpret_cast<SIN*>(this);
    ASSERT((size & kAlignMask) == 0);
    Char *cursor = reinterpret_cast<Char*>(start + sizeof(SIN)),
         *stop = cursor + (size >> TBitShiftCount<SIN>()) - 1;
    cursor = TPrint<Char>(cursor, stop, item);
    if (!cursor) {
      // Attempt to grow.
      return TUTF<Char>(reinterpret_cast<Char*>(start), stop);
    }
    return TUTF<Char>(cursor, stop);
  }

  /* Prints a char to the strand.
  @return A UTF. */
  inline TUTF<Char> Print(Char c) { return TPrint<Char>(c); }

  /* Prints a char to the strand.
  @return A UTF. */
  inline TUTF<Char> Print(const Char* string_) {
    return Print<const Char*>(string_);
  }

  /* Prints the given value.
  @return A UTF. */
  // inline TUTF<Char> Print(SI4 value) { return Print<SI4>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(UI4 value) { return Print<UI4>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(SI8 value) { return Print<SI8>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(UI8 value) { return Print<UI8>(value); }

#if SEAM >= _0_0_0__03
  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(FLT value) { return Print<FLT>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(DBL value) { return TPrint<DBL>(value); }
#endif

  /* Returns the stop of the begin. */
  inline Char* Stop() { return TStringStop<Char, SIN>(obj_.Begin()); }

  /* Returns the stop of the begin. */
  inline char* End() { return TObjEnd<SIN>(obj_); }

  /* Writes a nil-term char at the stop of the strand. */
  inline void Terminate() { *Stop() = 0; }

  /* Gets the begin of the Console begin. */
  inline TObject<SIN>& Obj() { return obj_; }

 private:
  TObject<SIN> obj_;            //< ASCII Obj.
  TUTF<Char> utf_;              //< The UTF for the strand.
  TSocket<SIN, kSize> socket_;  //< A socket on the stack.
};

#if USING_UTF1 == YES
using Strand1 = TStrand<char>;
#endif
#if USING_UTF2 == YES
using Strand2 = TStrand<char16_t>;
#endif
#if USING_UTF4 == YES
using Strand4 = TStrand<char32_t>;
#endif

}  // namespace _

/* Writes a nil-terminated UTF-8 to the strand.
@return The strand.
@param  strand The strand.
@param  value   The value to strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, const Char* string_) {
  return strand.Print(string_);
}

/* Writes the given value to the strand.
@param  strand The strand.
@param  value   The value to strand.
@return The strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, Char c) {
  return strand.Print(c);
}

/* Writes the given value to the strand.
@param  strand The strand.
@param  value The value to write to the strand.
@return The strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, UI1 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@param  strand The strand.
@param  value The value to write to the strand.
@return The strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, SI2 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@param  strand The strand.
@param  value The value to write to the strand.
@return The strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, UI2 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, SI4 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, UI4 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, SI8 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, UI8 value) {
  return strand.Print(value);
}

#if SEAM >= _0_0_0__03
/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, FLT value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, AsciiFactory, kLengthMax_>& operator<<(
    _::TStrand<Char, AsciiFactory, kLengthMax_>& strand, DBL value) {
  return strand.Print(value);
}
#endif

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  item The item to write to strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, _::TCenter<Char> item) {
  return strand.Print(item);
}

/* Writes the given value to the strand justified right.
@return The strand.
@param  strand The strand.
@param  item The item to strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, _::TRight<Char> item) {
  return strand.Print(item);
}

/* Prints a line of the given column_count to the strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand, _::TLineChar<Char> item) {
  return strand.Print(item);
}

/* Prints a line strand of the given column_count to the strand. */
template <typename SIN, typename Char, AsciiFactory kFactory_, SIW kLengthMax_>
inline _::TStrand<Char, kFactory_, kLengthMax_>& operator<<(
    _::TStrand<Char, kFactory_, kLengthMax_>& strand,
    _::TLineString<Char> item) {
  return strand.Print(item);
}

#endif  //< #if INCLUDED_SCRIPT_TSTRAND
#endif  //< #if SEAM >= _0_0_0__02
