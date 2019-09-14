/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /t_array.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_MATRIX
#ifndef INCLUDED_SCRIPT2_MATRIX
#define INCLUDED_SCRIPT2_MATRIX

#include "t_stack.h"

namespace _ {

/* @ingroup AsciiMatrix
Please see the ASCII Data Types Specificaiton for DRY documentation.
@link ./spec/data/vector_types/matrix.md
*/

/* A multi-dimensional array of homogeneous types with a Stack of dimensions.
Please see the ASCII Data Types Specificaiton for DRY documentation.
@link ./spec/data/vector_types/matrix.md

***Memory Layout***

@code
    +-----------------+
    |  C-Style Array  |
    |-----------------|
    | Dimension Stack |
 ^  |-----------------|
 |  |     Header      |
0xN +-----------------+
@endcode
*/
template <typename SIZ = SIN>
struct TMatrix {
  SIZ size;                //< SIZ of the array in bytes.
  TStack<SIZ> dimensions;  //< The stack of dimensions.
};

/* Max number of elements that can fit in the given SIZ. */
template <typename T = SIW, typename SIZ = SIN>
constexpr SIZ CMatrixElementCountMax() {
  return (TSignedMax<SIZ>() - sizeof(TStack<SIZ>)) / sizeof(T);
}

template <typename T = SIW, typename SIZ = SIN>
constexpr SIZ cMatrixCountUpperLimit(SIZ dimension_count, SIZ element_count) {
  SIZ header_size =
      (SIZ)(sizeof(TStack<SIZ>) + AlignUp(dimension_count * sizeof(SIZ)));
  return (SIZ)(((~(SIZ)0) - kWordLSbMask) - header_size) / (SIZ)sizeof(T);
}

/* Prints the TMatrix to the UTF. */
template <typename Printer, typename T = SIW, typename SIZ = SIN>
Printer& TMatrixPrint(Printer& o, TMatrix<SIZ>* matrix) {
  A_ASSERT(matrix);
  SIZ size = matrix->size, dimension_size = matrix->dimensions.count_max,
      dimension_count = matrix->dimensions.count;

  o << "\n\nArray: size:" << size << " dimensions:{" << dimension_count;

  SIZ *dimensions = TStackStart<SIZ, SIZ>(&matrix->dimensions),
      *dimensions_end = dimensions + dimension_count - 1;
  SIZ element_count = *dimensions++;

  while (dimensions < dimensions_end) {
    SIZ dimension = *dimensions++;
    element_count *= dimension;
    if (dimensions == dimensions_end)
      o << dimension << '\n';
    else
      o << dimension << ", ";
  }
  o << '}';

  return o;
}

/* Returns the required size of the given array. */
template <typename T = SIW, typename SIZ = SIN>
SIZ TMatrixElementCount(const SIZ* dimensions) {
  D_ASSERT(dimensions);
  SIZ dimension_count = *dimensions++, element_count = *dimensions++;
  while (dimension_count-- > 0) {
    SIZ current_dimension = *dimensions++;
    if (current_dimension < 1) return -1;
    element_count *= current_dimension;
  }
  if (element_count > cMatrixCountUpperLimit<T, SIZ>()) return -1;
  return element_count(T);
}

/* Returns the required size of the given array. */
template <typename T = SIW, typename SIZ = SIN>
SIZ TMatrixSize(const SIZ* dimensions) {
  D_ASSERT(dimensions);
  SIZ dimension_count = *dimensions++;
  if (dimension_count-- <= 0) return 0;
  SIZ element_count = *dimensions++;
  while (dimension_count-- > 0) {
    SIZ dimension = *dimensions++;
    if (dimension <= 0) return -1;
    element_count *= dimension;
  }
  if (element_count > cMatrixCountUpperLimit<T, SIZ>()) return -1;
  return sizeof(TStack<SIZ>) + element_count * sizeof(T);
}

/* Initializes an stack of n elements of the given type.
@param socket An stack of bytes large enough to fit the stack. */
template <typename T = SIW, typename SIZ = SIN>
TMatrix<SIZ>* TMatrixInit(const SIZ* dimensions) {
  A_ASSERT(dimensions);
  SIZ dimension_count = *dimensions;
  if (dimension_count < 0) return nullptr;
  SIZ size = (SIZ)sizeof(TStack<SIZ>) + dimension_count * sizeof(T);
  UIW* socket = new UIW[size >> kWordBitCount];
  TStack<SIZ>* stack = reinterpret_cast<TStack<SIZ>*>(socket);
  stack->size_array = 0;
  stack->size_stack = size;
  stack->count_max = dimension_count;
  stack->count = 0;
  return stack;
}

/* Calculates the size of the Dimensions Stack with the TMatrix header. */
template <typename SIZ>
inline SIZ TDimensionsSize(SIZ dimension_count) {
  return sizeof(TMatrix<SIZ>) + sizeof(SIZ) * dimension_count;
}

template <typename T, typename SIZ, SIZ kAlignementMask_ = sizeof(T) - 1>
SIZ TMatrixSizeBytes(SIZ dimension_count, SIZ element_count) {
  SIZ size_bytes =
      TDimensionsSize<SIZ>(dimension_count) + sizeof(T) * element_count;
  return AlignUp(size_bytes, kAlignementMask_);
}

/* Creates a dynamically allocated ARY. */
template <typename T = SIW, typename SIZ = SIN>
TMatrix<SIZ>* TMatrixNew(SIZ x) {
  SIZ size = sizeof(TStack<SIZ>) + sizeof(T) * x;
  size = AlignUp(size);
}

/* Creates a dynamically allocated ARY. */
template <typename T = SIW, typename SIZ = SIN>
inline TMatrix<SIZ>* TMatrixNew(SocketFactory socket_factory, SIZ x, SIZ y) {
  if (x < 0 || y < 0) return nullptr;
  SIZ dimension_count = x * y,
      size_bytes = AlignUp(TMatrixSizeBytes<T, SIZ>(dimension_count));
  return TMatrixInit<T, SIZ>(socket_factory(nullptr, size_bytes), x, y);
}

/* Creates a dynamically allocated ARY. */
template <typename T = SIW, typename SIZ = SIN>
inline TMatrix<SIZ>* TMatrixNew(SocketFactory socket_factory, SIZ x, SIZ y, SIZ z) {
  if (x < 0 || y < 0) return nullptr;
  SIZ element_count = z * x * y,
      size_bytes = AlignUp(TDimensionsSize<T, SIZ>(2, element_count));
  return TMatrixInit<T, SIZ>(socket_factory(nullptr, size_bytes), x, y);
}

template <typename T = SIW, typename SIZ = SIN>
inline TMatrix<SIZ>* TMatrixNew(const SIZ* dimensions) {
  D_ASSERT(dimensions);
  const SIZ* origin = dimensions;
  SIZ count = (*origin++) - 1,    //
      element_count = *origin++,  //
      index = count;
  while (index-- > 0) element_count *= *origin++;
  SIZ size = ((SIZ)element_count * (SIZ)sizeof(T));
}

/* Gets the address of the packed array.
@param obj ASCII Array data structure.
@return Pointer to the first element in the array. */
template <typename T, typename SIZ = SIN>
inline T* TMatrixElements(TMatrix<SIZ>* obj) {
  return reinterpret_cast<T*>(TStackStart<SIZ, SIZ>(&obj->dimensions) +
                              obj->size);
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

/* Creates a static array of SI8 dimensions. */
template <const SI8... N>
inline const SI8* TDim8() {
  static const SI8 kCount = (SI8)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &kCount;
}

template <typename T = SIW, typename SIZ = SIN>
inline SIZ TMatrixClone(TMatrix<SIZ>* matrix, SocketFactory socket_factory) {
  return 0;
}

template <typename T = SIW, typename SIZ = SIN>
inline UIW* TMatrixClone(TMatrix<SIZ>* matrix, TMatrix<SIZ>* other,
                         SocketFactory socket_factory) {
  return nullptr;
}

template <typename T = SIW, typename SIZ = SIN>
UIW* TMatrixNew(SocketFactory socket_factory) {}

/* A multi-dimensional array Ascii Object. */
template <typename T = SIW, typename SIZ = SIN, typename BUF = Nil>
class AMatrix {
  AArray<SIZ> obj_;  //< The Auto-array.

 public:
  /* Constructs an empty Matrix with 4 reserved dimensions and 64 elements. */
  AMatrix() : obj_(TMatrixSizeBytes<T, SIZ>(4, 64)) {}

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(SIZ x, const T* elements = nullptr) : obj_(TMatrixNew<T, SIZ>(x)) {
    D_ASSERT(x >= 0);
  }

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(SIZ x, SIZ y, const T* elements = nullptr)
      : obj_(TMatrixSizeBytes<T, SIZ>(2, x * y)) {
    D_ASSERT(x >= 0 && y >= 0);
  }

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(SIZ x, SIZ y, SIZ z, const T* elements = nullptr)
      : obj_(TMatrixSizeBytes<T, SIZ>(3, x * y * z)) {
    D_ASSERT(x >= 0 && y >= 0 && z >= 0);
  }

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(SIZ w, SIZ x, SIZ y, SIZ z, const T* elements = nullptr)
      : obj_(TMatrixSizeBytes<T, SIZ>(4, w * x * y * z)) {}

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(const AMatrix& other) : obj_(other.Obj()) {}

  /* Destructs nothing. */
  ~AMatrix() {}

  /* Clones the other object; up-sizing the socket only if required. */
  inline SIZ Clone(SocketFactory socket_factory = obj_.AJT().socket_factory) {
    TMatrixClone<T, SIZ>(obj_.Obj(), socket_factory);
    return this;
  }

  /* Clones the other object; up-sizing the socket only if required. */
  inline SIZ Clone(AMatrix<T, SIZ>& other,
                   SocketFactory socket_factory = obj_.AJT().socket_factory) {
    TMatrixClone<T, SIZ>(obj_.Obj(), other, socket_factory);
    return this;
  }

  /* Gets the number_ of dimensions. */
  inline SIZ DimensionCount() { return This().dimensions->count; }

  /* Gets the dimensions array. */
  inline T* Dimension() { return TStackStart<T, SIZ>(Array()); }

  /* Gets the underlying array. */
  inline T* Elements() { return TMatrixElements<T, SIZ>(This()); }

  /* Returns the Autoject-Array. */
  inline AArray<SIZ>& AJT_ARY() { return obj_; }

  /* Returns the Autoject. */
  inline Autoject& AJT() { return obj_.AJT(); }

  /* Returns the Autoject::origin cased as a TMap<SIZ>. */
  inline TMatrix<SIZ>* This() {
    return reinterpret_cast<TMatrix<SIZ>*>(AJT().origin);
  }

  /* Returns the Auto-Array. */
  inline AArray<T, SIZ, BUF>& Array() { return obj_; }

  template <typename Printer = COut>
  inline Printer& PrintTo(Printer& o) {
    return TMatrixPrint<Printer, T, SIZ>(o, This());
  }

  /* Operator= overload. */
  inline AMatrix<T, SIZ>& operator=(AMatrix<T, SIZ>& other) {
    Clone(other);
    return *this;
  }
};

}  // namespace _

#endif
#endif
