/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_array.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_MATRIX
#ifndef INCLUDED_SCRIPT2_ARRAY
#define INCLUDED_SCRIPT2_ARRAY

#include "t_stack.h"

namespace _ {

/* An one-or-more dimensional Array of homogeneous same-sized types.

An array may use two different memory layouts, one for a 1D obj of a
given types, and another for a multi-dimensional array that uses the 1D
array in order to store the dimensions. The only different between them is
that the size_array variable gets set to 0.

# Memory Layout

@code
    +-----------------+
    |  C-Style Array  | <-- Only if header_size > 0
    |-----------------|
    | Dimension Stack |
 ^  |-----------------|
 |  |  TStack Header  |
0xN +-----------------+
@endcode
*/
template <typename SIZ = SI4>
struct TMatrix {
  SIZ size;                //< SIZ of the array in bytes.
  TStack<SIZ> dimensions;  //< The stack of dimensions.
};

template <typename T = SI4, typename SIZ = SI4>
constexpr SIZ TMatrixCountUpperLimit(SIZ dimension_count, SIZ element_count) {
  SIZ header_size = (SIZ)(sizeof(TStack<SIZ>) +
                          TAlignUpSigned<SIZ>(dimension_count * sizeof(SIZ)));
  return (SIZ)(((~(SIZ)0) - 7) - header_size) / (SIZ)sizeof(T);
}

/* Returns the required size of the given array. */
template <typename T = SI4, typename SIZ = SI4>
constexpr SIZ TMatrixElementCount(const SIZ* dimensions) {
  D_ASSERT(dimensions);
  SIZ dimension_count = *dimensions++;
  SIZ size = sizeof(TStack<SIZ>) + sizeof(SIZ);
  while (dimension_count-- > 0) {
    SIZ current_dimension = *dimensions++;
    if (current_dimension < 1) return -1;
    element_count *= current_dimension;
  }
  if (element_count > TMatrixCountUpperLimit<T, SIZ>()) return -1;
  return element_count * sizeof(T);
}

/* Returns the required size of the given array. */
template <typename T = SI4, typename SIZ = SI4>
constexpr SIZ TMatrixSize(const SIZ* dimensions) {
  D_ASSERT(dimensions);
  SIZ dimension_count = *dimensions++;
  if (dimension_count-- <= 0) return 0;
  SIZ element_count = *dimensions++;
  while (dimension_count-- > 0) {
    SIZ dimension = *dimensions++;
    if (dimension <= 0) return -1;
    element_count *= dimension;
  }
  if (element_count > TMatrixCountUpperLimit<T, SIZ>()) return -1;
  return sizeof(TStack<SIZ>) + element_count * sizeof(T);
}

/* Initializes an stack of n elements of the given type.
@param socket An stack of bytes large enough to fit the stack. */
template <typename T = SI4, typename SIZ = SI4>
TStack<SIZ>* TMatrixInit(const SIZ* dimensions) {
  A_ASSERT(dimensions);
  SIZ dimension_count = *dimension;
  if (dimension_count < 0 || dimension_count > kStackCountMax) return nullptr;
  SIZ size = (SIZ)sizeof(TStack<SIZ>) + dimension_count * sizeof(T);
  UIW* socket = new UIW[size >> kWordBitCount];
  TStack<SIZ>* stack = reinterpret_cast<TStack<SIZ>*>(socket);
  stack->size_array = 0;
  stack->size_stack = size;
  stack->size = dimension_count;
  stack->count = 0;
  return stack;
}

template <typename T = SI4, typename SIZ = SI4>
SIZ TMatrixElementCountMax() {
  return (UnsignedMax<SIZ>() - (SIZ)sizeof(TStack<SIZ>)) / sizeof(T);
}

/* Creates a dynamically allocated ARY. */
template <typename T = SI4, typename SIZ = SI4>
TStack<SIZ>* TMatrixNew(SIZ x) {
  SIZ size = sizeof(TStack<SIZ>) + sizeof(T) * x;
  size = TAlignUpSigned<SIZ>(size);
}

template <typename T = SI4, typename SIZ = SI4>
TStack<SIZ>* TMatrixNew(const SIZ* dimensions) {
  D_ASSERT(dimensions);
  const SIZ* begin = dimensions;
  SIZ count = (*begin++) - 1,    //
      element_count = *begin++,  //
      index = count;
  while (index-- > 0) element_count *= *begin++;
  SIZ size = ((SIZ)element_count * (SIZ)sizeof(T));
}

/* Gets the address of the packed array.
@param obj ASCII Array data structure.
@return Pointer to the first element in the array. */
template <typename T, typename SIZ = SI4>
T* TMatrixElements(TStack<SIZ>* obj) {
  CH1* elements = reinterpret_cast<CH1*>(obj) + obj->size_stack;
  return reinterpret_cast<T*>(elements);
}

/* Gets the address of the packed SIZ dimensions.
@param obj ASCII Array data structure.
@return Pointer to the first element in the array. */
template <typename T, typename SIZ = SI4>
SIZ* TMatrixDimensions(TStack<SIZ>* obj) {
  CH1* elements = reinterpret_cast<CH1*>(obj) + sizeof(TStack<SIZ>);
  return reinterpret_cast<SIZ*>(elements);
}

/* Gets the stop address of the packed SIZ dimensions.
@param obj ASCII Array data structure.
@return Pointer to the first element in the array. */
template <typename T, typename SIZ = SI4>
SIZ* TMatrixDimensionsEnd(TStack<SIZ>* obj) {
  A_ASSERT(obj);
  return TMatrixDimensions<T, SIZ>(obj) + obj->count - 1;
}

/* Prints the TMatrix to the UTF. */
template <typename Printer, typename T = SI4, typename SIZ = SI4>
Printer& TPrintArray(Printer& o, TStack<SIZ>* obj) {
  A_ASSERT(obj);
  SIZ size_array = obj->size_array;
  SIZ count = obj->count;
  if (size_array == 0) {
    return TStackPrint<T, SIZ>(o, obj);
  }
  if (count <= 0) o << "Array: Error! Dimension count must be positive!";

  o << "\n\nArray: dimension_count: " << count << " count_max:" << obj->size
    << " size_stack:" << obj->size_stack << " size_array:" << obj->size_array
    << "\nDimensions:\n";

  SIZ *dimensions = TMatrixDimensions<T, SIZ>(obj),
      *dimensions_end = dimensions + count - 1;
  SIZ element_count = *dimensions++;

  while (dimensions < dimensions_end) {
    SIZ dimension = *dimensions++;
    element_count *= dimension;
    if (element_count > TMatrixElementCountMax<T, SIZ>())
      return o << "Max element count exceeded";
    if (dimensions == dimensions_end)
      o << dimension << kLF;
    else
      o << dimension << ", ";
  }
  return o;
}

/* Creates a immutable array of dimensions. */
template <typename SI, const SI... N>
inline const SI* TDim() {
  static const SI kCount = (SI)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &kCount;
}

/* Creates a immutable array of SI2 dimensions. */
template <const SI2... N>
inline const SI2* TDim2() {
  static const SI2 kCount = (SI2)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &kCount;
}

/* Creates a immutable array of SI4 dimensions. */
template <const SI4... N>
inline const SI4* TStack4() {
  static const SI4 kCount = (SI4)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &kCount;
}

/* Creates a immutable array of SI8 dimensions. */
template <const SI8... N>
inline const SI8* TDim8() {
  static const SI8 kCount = (SI8)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &kCount;
}

/* A multi-dimensional array Ascii Object.

*/
template <typename T = SI4, typename SIZ = SI4, typename BUF = Nil>
class AMatrix {
 public:
  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(SIZ x, const T* elements = nullptr) : obj_(TMatrixNew<T, SIZ>(x)) {}

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(SIZ x, SIZ y, const T* elements = nullptr)
      : obj_(TMatrixNew<T, SIZ>(x, y)) {}

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(SIZ x, SIZ y, SIZ z, const T* elements = nullptr)
      : obj_(TMatrixNew<T, SIZ>(x, y, z)) {}

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(SIZ w, SIZ x, SIZ y, SIZ z, const T* elements = nullptr)
      : obj_(TMatrixNew<T, SIZ>(w, x, y, z)) {}

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(const AMatrix& other) : obj_(other.Obj()) {}

  /* Destructs nothing. */
  ~AMatrix() {}

  /* Clones the other object; up-sizing the socket only if required. */
  inline AMatrix<T, SIZ>* Clone(AMatrix<T, SIZ>& other) {
    TMatrixClone<T, SIZ>(obj_.Obj(), other);
    return this;
  }

  /* Gets the number_ of dimensions. */
  inline SIZ DimensionCount() { return stack->count; }

  /* Gets the dimensions array. */
  inline T* Dimension() { return TStackStart<T, SIZ>(Array()); }

  /* Gets the underlying array. */
  inline T* Elements() { return TMatrixElements<T, SIZ>(Array()); }

  /* Operator= overload. */
  inline AMatrix<T, SIZ>& operator=(AMatrix<T, SIZ>& other) {
    Clone(other);
    return *this;
  }

  /* Gets the Autoject. */
  inline Autoject& AObj() {
    return reinterpret_cast<AMatrix<SIZ>*>(obj_.Begin());
  }

  /* Gets the S-Object. */
  inline AArray<T, SIZ, BUF> Array() {
    return reinterpret_cast<AMatrix<SIZ>*>(obj_.Begin());
  }

 private:
  AArray<SIZ> obj_;  //< The Ascii Object.
};

}  // namespace _

#endif
#endif
