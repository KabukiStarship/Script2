/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_array.cc
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_7
#ifndef INCLUDED_SCRIPT2_ARRAY
#define INCLUDED_SCRIPT2_ARRAY

#include "t_stack.h"

namespace _ {

/* A multi-dimensional array.
ASCII Array uses the same data structure as the ASCII Stack, the
difference being that the size_array of the Stack is set to 0 for the Stack and
the Array has a packed multi-dimensional array after the stack of dimensions. */
template <typename T = SI4, typename Size = SI4, typename Index = SI4>
struct TCArray {
  TCStack<T, Size, Index> stack;
};

template <typename T = SI4, typename Size = SI4, typename Index = SI4>
constexpr Index ArrayCountUpperLimit(Index dimension_count,
                                     Index element_count) {
  Size header_size =
      (Size)(sizeof(TCStack<T, Size, Index>) +
             TAlignUpSigned<Index>(dimension_count * sizeof(Index)));
  return (Index)(((~(Size)0) - 7) - header_size) / (Size)sizeof(T);
}

/* Returns the required size of the given array. */
template <typename T = SI4, typename Size = SI4, typename Index = SI4>
constexpr Index ArrayElementCount(const Index* dimensions) {
  ASSERT(dimensions);
  Index dimension_count = *dimensions++, element_count = *dimensions++;
  if (--dimension_count < 0 || element_count < 0) return -1;
  Size size = dimension_count * sizeof(Index);
  while (dimension_count-- > 0) {
    Index current_dimension = *dimensions++;
    if (current_dimension < 1) return -1;
    element_count *= current_dimension;
  }
  if (element_count > ArrayCountUpperLimit<T, Size, Index>()) return -1;
  return element_count * sizeof(T);
}

/* Returns the required size of the given array. */
template <typename T = SI4, typename Size = SI4, typename Index = SI4>
constexpr Size ArraySize(const Index* dimensions) {
  Index dimension_count = *dimensions++, element_count = *dimensions++;
  Size header_size = sizeof(TCStack<T, Size, Index>);
  if (--dimension_count < 0) return 0;
  while (dimension_count-- > 0) {
    Index current_dimension = *dimensions++;
    if (current_dimension < 1) return 0;
    element_count *= current_dimension;
  }
  if (element_count > ArrayCountUpperLimit<T, Size, Index>()) return 0;
  return element_count * sizeof(T);
}

/* Initializes an stack of n elements of the given type.
@param socket An stack of bytes large enough to fit the stack. */
template <typename T = SI4, typename Size = SI4, typename Index = SI4>
TCStack<T, Size, Index>* ArrayInit(const Index* dimensions) {
  ASSERT(dimensions);
  Index dimension_count = *dimension;
  if (dimension_count < 0 || dimension_count > kStackCountMax) return nullptr;
  Size size =
      (Size)sizeof(TCStack<T, Size, Index>) + dimension_count * sizeof(T);
  UIW* socket = new UIW[size >> kWordBitCount];
  TCStack<T, Size, Index>* stack =
      reinterpret_cast<TCStack<T, Size, Index>*>(socket);
  stack->size_array = 0;
  stack->size_stack = size;
  stack->count_max = dimension_count;
  stack->count = 0;
  return stack;
}

template <typename T = SI4, typename Size = SI4, typename Index = SI4>
Index ArrayElementCountMax() {
  return (UnsignedMax<Size>() - (Size)sizeof(TCStack<T, Size, Index>)) /
         sizeof(T);
}

template <typename T = SI4, typename Size = SI4, typename Index = SI4>
TCStack<T, Size, Index>* ArrayNew(const Index* dimensions) {
  ASSERT(dimensions);
  const Index* begin = dimensions;
  Index count = (*begin++) - 1, element_count = *begin++, index = count;
  while (index-- > 0) element_count *= *begin++;
  Size size = ((Size)element_count * (Size)sizeof(T));
}

/* Gets the address of the packed array.
@param ary ASCII Array data structure.
@return Pointer to the first element in the array. */
template <typename T, typename Size = SI4, typename Index = SI4>
T* ArrayElements(TCStack<T, Size, Index>* ary) {
  CH1* elements = reinterpret_cast<CH1*>(ary) + ary->size_stack;
  return reinterpret_cast<T*>(elements);
}

/* Gets the address of the packed Index dimensions.
@param ary ASCII Array data structure.
@return Pointer to the first element in the array. */
template <typename T, typename Size = SI4, typename Index = SI4>
Index* ArrayDimensions(TCStack<T, Size, Index>* ary) {
  CH1* elements = reinterpret_cast<CH1*>(ary) + sizeof(TCStack<T, Size, Index>);
  return reinterpret_cast<Index*>(elements);
}

/* Gets the stop address of the packed Index dimensions.
@param ary ASCII Array data structure.
@return Pointer to the first element in the array. */
template <typename T, typename Size = SI4, typename Index = SI4>
Index* ArrayDimensionsEnd(TCStack<T, Size, Index>* ary) {
  ASSERT(ary);
  return ArrayDimensions<T, Size, Index>(ary) + ary->count - 1;
}

/* Prints the TCArray to the UTF. */
template <typename T = SI4, typename Size = SI4, typename Index = SI4,
          typename Char = CH1>
TUTF<Char>& PrintArray(TUTF<Char>& utf, TCStack<T, Size, Index>* ary) {
  ASSERT(ary);
  Size size_array = ary->size_array;
  Index count = ary->count;
  if (size_array == 0) {
    return TPrintStack<T, Size, Index>(utf, ary);
  }
  if (count <= 0) utf << "Array: Error! Dimension count must be positive!";

  utf << "\n\nArray: dimension_count: " << count
      << " count_max:" << ary->count_max << " size_stack:" << ary->size_stack
      << " size_array:" << ary->size_array << "\nDimensions:\n";

  Index *dimensions = ArrayDimensions<T, Size, Index>(ary),
        *dimensions_end = dimensions + count - 1;
  Index element_count = *dimensions++;

  while (dimensions < dimensions_end) {
    Index dimension = *dimensions++;
    element_count *= dimension;
    if (element_count > ArrayElementCountMax<T, Size, Index>())
      return utf << "Max element count exceeded";
    if (dimensions == dimensions_end)
      utf << dimension << kLF;
    else
      utf << dimension << ", ";
  }
  return utf;
}

/* Creates a immutable array of dimensions. */
template <const SI4... N>
inline const SI4* Dimensions() {
  static const SI4 kCount = (SI4)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &kCount;
}

/* A multi-dimensional array that uses dynamic memory that can auto-grow.

An ASCII Stack struct is identical to an Array

@todo This is an older data structure that needs to be replace this with
Array.
This class is used to save a little bit of ROM space over the Array.
To use this class with anything other than POD types the class T must have
a overloaded operator= and operator==. */
template <typename T = SI4, typename Size = SI4, typename Index = SI4>
class TArray {
 public:
  /* Initializes an array of n elements of the given type.
      @param max_elements The max number_ of elements in the array socket. */
  TArray(Index demension_count = 1) : begin(ArrayNew<T, Size, Index>(1)) {}

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  TArray(const Array& other)
      : size_array(other.size_array),
        size_stack(other.size_stack),
        count_max(other.count_max),
        count(other.count) {
    Index *elements_other = TStackStart<Index, Size, Index>(other.stack),
          *element = TStackStart<Index, Size, Index>(stack),
          *elements_end = StackStop<Index, Size, Index>(stack);
    while (element < elements_end) *element++ = *elements_other++;
  }

  /* Deletes the dynamically allocated Array. */
  ~TArray() { delete[] begin; }

  /* Clones the other object; up-sizing the socket only if required. */
  void Clone(Array<T, Size, Index>& other) {}

  /* Gets the number_ of dimensions. */
  Index DimensionCount() { return stack->count; }

  /* Gets the dimensions array. */
  T* Dimension() { return TStackStart<T, Size, Index>(stack); }

  /* Gets the underlying array. */
  T* Elements() { return ArrayElements<T, Size, Index>(stack); }

  /* Operator= overload. */
  inline TArray<T, Size, Index>& operator=(TArray<T, Size, Index>& other) {
    Clone(other);
    return *this;
  }

  inline TCArray<T, Size, Index>* stack {
    return reinterpret_cast<TCArray<T, Size, Index>*>(begin);
  }

 private:
  UIW* begin;             //< OBJ base address.
  AsciiFactory factory_;  //< AsciiFactory.
};
}  // namespace _

template <typename T = SI4, typename Size = SI4, typename Index = SI4,
          typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& printer,
                                 ::_::TCArray<T, Size, Index>* stack) {
  return ::_::PrintArray<T, Size, Index>(printer, stack);
}

template <typename T = SI4, typename Size = SI4, typename Index = SI4,
          typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& printer,
                                 ::_::TCArray<T, Size, Index>& stack) {
  return ::_::PrintArray<T, Size, Index>(printer, stack);
}

#endif  //< INCLUDED_SCRIPT2_ARRAY
#endif  //< #if SEAM >= SCRIPT2_7
