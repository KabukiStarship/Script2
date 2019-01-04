/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tstrand.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#if SEAM >= _0_0_0__03
#ifndef SCRIPT2_TSTRAND
#define SCRIPT2_TSTRAND 1

#include "tstr.h"

#include "casciidata.h"

#if SEAM == _0_0_0__03
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

/* Initializes an ASCII Strand. */
template <typename Char, SIN kSize_>
Char* TStrandInit(TSocket<SIN, kSize_>& socket) {
  return TStringInit<SIN, Char>(socket.Begin<>(), kSize_);
}

/* ASCII Strand Factory that can grow from stack-to-heap.
All you have to do to grow from stack-to-heap is set the kUsingHeap_ template
parameter to a non-zero value and you're good to go. */
template <typename Char, BOL kUsingHeap_ = kStack>
int TStrandFactory(CObject& obj, SIW function, void* arg);

/* An ASCII String that can auto-grow from stack to heap.

This class is designed to take advantage of the behavior of the C++ operator
overloads. When you have a string of overloads, the objects get destructed
in the opposite order then where called.

# Initialization

A Strand may be initialed to print to the socket_ or to a dynamically allocated
string. This behavior is configured with the constructors. The AsciiFactory can
either be configured using the class template argument kFactory1_. If the
obj_.Factory () is nil then it will get replaced with the

@code
TStrand<> (TCOut<>).Plus ("Hello ") << "world!";
@endcode

# Dynamic Allocated Strings

Strings that use dynamic memory use the DCOutAuto factory:

@code
TStrand<UI4> (TCOutHeap<>) << "Hello world!";
@endcode */
template <typename Char = CH1, SIN kLengthMax_ = 64,
          AsciiFactory kFactory_ = TStrandFactory<Char>>
class TStrand {
 public:
  enum {
    kSizeMax = (~(SIN)0) - (sizeof(SIN) - 1),      //< Max size in bytes.
    kCountMax = kSizeMax / sizeof(Char) - 1,       //< Max element of chars.
    kCountMin = (sizeof(SIN) / sizeof(Char)) + 1,  //< Min element count.
    // kLengthMax bounded to the min max range.
    kLengthMax = (int)((kLengthMax_ < kCountMin)
                           ? kCountMin
                           : (kLengthMax_ > kCountMax - 1) ? kCountMax - 1
                                                           : kLengthMax_),
    // The size in bytes.
    kSize = (int)sizeof(SIN) + (kLengthMax + 1) * (int)sizeof(Char),
  };

  /* Constructs a Strand that auto-grows from stack to heap.
  @param factory ASCII Factory to call when the Strand overflows. */
  TStrand()
      : obj_(socket_.Words(), nullptr),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    Terminate();
  }

  /* Constructs the utf_ pointers to point to the obj begin and stop.
  The utf_ pointers will only point to the begin and stop of the obj if
  the obj is an address and the size is in bounds. If the size is out of
  bounds then the utf_ will point to the begin and stop of the socket_.
  If the obj is nil than a dynamic ASCII OBJ will be created using the
  kFactory_; if the size is less than the minimum size or greater than the
  maximum size then the socket_ will be used.
  @param obj  Buffer obj address.
  @param size Object size IN BYTES. */
  TStrand(UIW* obj, SIN size)
      : obj_(size, obj, kFactory_), utf_(obj, utf_.begin + kLengthMax) {
    Terminate();
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(const CH1* item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    PRINTF("\n\nsocket_.Words():0x%p socket_.SizeBytes():%i\n\n",
           socket_.Words(), (int)socket_.SizeBytes());
    utf_ << item;
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(const CH2* item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(const CH4* item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(SI1 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(UI1 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(SI2 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(UI2 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(SI4 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(UI4 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(SI8 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(UI8 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }

#if SEAM >= _0_0_0__03
  /* Constructs a Strand and prints the given item. */
  TStrand(FLT item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(DBL item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SIN, Char>(), utf_.begin + kLengthMax) {
    utf_ << item;
  }
#endif

  /* Gets the UTF. */
  TUTF<Char>& Star() { return utf_; }

  /* Prints a CH1 to the strand.
  @param item The item to utf.
  @return A UTF. */
  template <typename T>
  TUTF<Char>& Print(T item) {
    UIW begin = reinterpret_cast<UIW>(obj_.Begin());
    SIN size = *reinterpret_cast<SIN*>(this);
    ASSERT((size & kAlignMask) == 0);
    Char *cursor = reinterpret_cast<Char*>(begin + sizeof(SIN)),
         *stop = cursor + (size >> TBitShiftCount<SIN>()) - 1;
    do {
      cursor = TPrint<Char>(cursor, stop, item);
      if (!obj_.Grow()) return utf_;
    } while (!cursor);
    cursor = TPrint<Char>(cursor, stop, item);
    return utf_;
  }

  /* Prints a CH1 to the strand.
  @return A UTF. */
  inline TUTF<Char>& Print(Char c) { return TPrint<Char>(c); }

  /* Prints a CH1 to the strand.
  @return A UTF. */
  inline TUTF<Char>& Print(const Char* string) {
    return Print<const Char*>(string);
  }

  /* Prints the given value.
  @return A UTF. */
  // inline TUTF<Char>& Print(SI4 value) { return Print<SI4>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char>& Print(UI4 value) { return Print<UI4>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char>& Print(SI8 value) { return Print<SI8>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char>& Print(UI8 value) { return Print<UI8>(value); }

#if SEAM >= _0_0_0__03
  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(FLT value) { return Print<FLT>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(DBL value) { return TPrint<DBL>(value); }
#endif

  /* Returns the begin of the obj. */
  inline Char* Start() { return TStringStart<Char, SIN>(obj_.Begin()); }

  /* Returns the stop of the obj. */
  inline Char* Stop() { return TStringStop<Char, SIN>(obj_.Begin()); }

  /* Returns the stop of the obj. */
  inline CH1* End() { return TObjEnd<SIN>(obj_); }

  /* Writes a nil-term CH1 at the stop of the strand. */
  inline void Terminate() { *Stop() = 0; }

  /*  */
  inline Char* Find(const Char* querry) { return TStringFind(Start(), querry); }

  /* Checks if this Strand to the other string are equivalent.
  @return Nil if they strings are not equivalent and a pointer to the next CH1
  after the end of the equivalent part of this strand upon success. */
  inline Char Equals(const Char* other) { return TStringFind(Start(), other); }

  /* Checks to see if the utf_ is using static memory. */
  inline BOL IsStatic() { return socket_.Contains(utf_.cursor); }

  /* Gets the obj of the Console obj. */
  inline TObject<SIN>& Obj() { return obj_; }

  /* Prints to the given  */
  void Print() {
    _::Print("\nTStrand<CH");
    _::Print('0' + sizeof(Char));
    _::Print('>');
    obj_.Print();
    utf_.Print();
    socket_.Print();
  }

 private:
  TObject<SIN> obj_;            //< ASCII CObject.
  TUTF<Char> utf_;              //< The UTF for the strand.
  TSocket<SIN, kSize> socket_;  //< A socket on the stack.
};

#if USING_UTF1 == YES
using Strand1 = TStrand<CH1>;
#endif
#if USING_UTF2 == YES
using Strand2 = TStrand<CH2>;
#endif
#if USING_UTF4 == YES
using Strand4 = TStrand<CH4>;
#endif

template <typename Size>
int TStrandFactory(CObject& obj, SIW function, void* arg, BOL using_heap);

template <typename Size, typename Char, BOL kUsingHeap_ = false>
int TStrandFactory(CObject& obj, SIW function, void* arg) {
  return TStrandFactory<Size>(obj, function, arg, kUsingHeap_);
}

/* Strand factory.
 */
template <typename Size>
int TStrandFactory(CObject& obj, SIW function, void* arg, BOL using_heap) {
  Size size;
  UIW *begin, *temp;
  switch (function) {
    case kFactoryDelete: {
      begin = obj.begin;
      if (!begin) return kFactoryNilOBJ;
      if (using_heap)
        delete[] begin;
      else
        obj.factory = TStrandFactory<Size, kHeap>;
      return 0;
    }
    case kFactoryNew: {
      size = TAlignUpSigned<Size>(*reinterpret_cast<Size*>(arg));
      if ((~size) == 0) return kFactorySizeInvalid;
      begin = new UIW[size >> kWordBitCount];
      obj.begin = begin;
      *reinterpret_cast<Size*>(begin) = size;
      return 0;
    }
    case kFactoryGrow: {
      size = *reinterpret_cast<Size*>(obj.begin);
      if (!TObjCanGrow<Size>(size)) return kFactoryCantGrow;
      size = size << 1;  // << 1 to * 2
      temp = obj.begin;
      obj.begin = TObjNew<Size>(temp, size);
      if (using_heap)
        delete[] begin;
      else
        obj.factory = TStrandFactory<Size, kHeap>;
      return 0;
    }
    case kFactoryClone: {
      if (!arg) return kFactoryNilArg;
      CObject* other = reinterpret_cast<CObject*>(arg);
      begin = obj.begin;
      size = *reinterpret_cast<Size*>(begin);
      other->begin = TObjClone<Size>(begin, size);
      other->factory = TObjFactory<Size, kHeap>;
      return 0;
    }
    case kFactoryInfo: {
      const CH1** ptr = *reinterpret_cast<const CH1**>(arg);
      *ptr = __FUNCTION__;
      return 0;
    }
  }
  return 0;
}

}  // namespace _

/* Writes a nil-terminated UTF-8 to the strand.
@return The strand.
@param  strand The strand.
@param  value   The value to strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, const Char* string) {
  return strand.Print(string);
}

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value   The value to strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, Char c) {
  return strand.Print(c);
}

/* Writes the given value to the strand.
@param  strand The strand.
@param  value The value to write to the strand.
@return The strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, UI1 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@param  strand The strand.
@param  value The value to write to the strand.
@return The strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, SI2 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@param  strand The strand.
@param  value The value to write to the strand.
@return The strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, UI2 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, SI4 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, UI4 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, SI8 value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, UI8 value) {
  return strand.Print(value);
}

#if SEAM >= _0_0_0__03
/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, FLT value) {
  return strand.Print(value);
}

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  value The value to write to the strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TStrand<Char, kLengthMax_, kFactory_>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, DBL value) {
  return strand.Print(value);
}
#endif

/* Writes the given value to the strand.
@return The strand.
@param  strand The strand.
@param  item The item to write to strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, _::TCenter<Char> item) {
  return strand.Print(item);
}

/* Writes the given value to the strand justified right.
@return The strand.
@param  strand The strand.
@param  item The item to strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, _::TRight<Char> item) {
  return strand.Print(item);
}

/* Prints a line of the given column_count to the strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand, _::TLineChar<Char> item) {
  return strand.Print(item);
}

/* Prints a line strand of the given column_count to the strand. */
template <typename Char, SIN kLengthMax_, AsciiFactory kFactory_>
inline _::TUTF<Char>& operator<<(
    _::TStrand<Char, kLengthMax_, kFactory_>& strand,
    _::TLineString<Char> item) {
  return strand.Print(item);
}

#endif  //< #if SCRIPT2_TSTRAND
#endif  //< #if SEAM >= _0_0_0__04
