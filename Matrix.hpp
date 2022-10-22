/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Matrix.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef INCLUDED_SCRIPT2_MATRIX
#define INCLUDED_SCRIPT2_MATRIX
#include <_Config.h>
#if SEAM >= SCRIPT2_MATRIX
#include "Stack.hpp"
namespace _ {

/* @ingroup AsciiMatrix
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/vector_types/matrix.md
*/

/* A multi-dimensional array of homogeneous types with a Stack of dimensions.
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/vector_types/matrix.md

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
template <typename ISZ = ISN>
struct TMatrix {
  ISZ size;                //< ISZ of the array in bytes.
  TStack<ISZ> dimensions;  //< The stack of dimensions.
};

/* Max number of elements that can fit in the given ISZ. */
template <typename T = ISW, typename ISZ = ISN>
constexpr ISZ CMatrixElementCountMax() {
  return (TSignedMax<ISZ>() - sizeof(TStack<ISZ>)) / sizeof(T);
}

template <typename T = ISW, typename ISZ = ISN>
constexpr ISZ CMatrixCountUpperLimit(ISZ dimension_count, ISZ element_count) {
  ISZ header_size =
      (ISZ)(sizeof(TStack<ISZ>) + AlignUp(dimension_count * sizeof(ISZ)));
  return (ISZ)(((~(ISZ)0) - cWordLSbMask) - header_size) / (ISZ)sizeof(T);
}

/* Prints the TMatrix to the UTF. */
template <typename Printer, typename T = ISW, typename ISZ = ISN>
Printer& TMatrixPrint(Printer& o, TMatrix<ISZ>* matrix) {
  A_ASSERT(matrix);
  ISZ size = matrix->size, dimension_size = matrix->dimensions.count_max,
      dimension_count = matrix->dimensions.count;

  o << "\n\nArray: size:" << size << " dimensions:{" << dimension_count;

  ISZ *dimensions = TStackStart<ISZ, ISZ>(&matrix->dimensions),
      *dimensions_end = dimensions + dimension_count - 1;
  ISZ element_count = *dimensions++;

  while (dimensions < dimensions_end) {
    ISZ dimension = *dimensions++;
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
template <typename T = ISW, typename ISZ = ISN>
ISZ TMatrixElementCount(const ISZ* dimensions) {
  D_ASSERT(dimensions);
  ISZ dimension_count = *dimensions++, element_count = *dimensions++;
  while (dimension_count-- > 0) {
    ISZ current_dimension = *dimensions++;
    if (current_dimension < 1) return -1;
    element_count *= current_dimension;
  }
  if (element_count > CMatrixCountUpperLimit<T, ISZ>()) return -1;
  return element_count(T);
}

/* Returns the required size of the given array. */
template <typename T = ISW, typename ISZ = ISN>
ISZ TMatrixSize(const ISZ* dimensions) {
  D_ASSERT(dimensions);
  ISZ dimension_count = *dimensions++;
  if (dimension_count-- <= 0) return 0;
  ISZ element_count = *dimensions++;
  while (dimension_count-- > 0) {
    ISZ dimension = *dimensions++;
    if (dimension <= 0) return -1;
    element_count *= dimension;
  }
  if (element_count > CMatrixCountUpperLimit<T, ISZ>()) return -1;
  return sizeof(TStack<ISZ>) + element_count * sizeof(T);
}

/* Initializes an stack of n elements of the given type.
@param socket An stack of bytes large enough to fit the stack. */
template <typename T = ISW, typename ISZ = ISN>
TMatrix<ISZ>* TMatrixInit(const ISZ* dimensions) {
  A_ASSERT(dimensions);
  ISZ dimension_count = *dimensions;
  if (dimension_count < 0) return nullptr;
  ISZ size = (ISZ)sizeof(TStack<ISZ>) + dimension_count * sizeof(T);
  IUW* socket = new IUW[size >> cWordBitCount];
  TStack<ISZ>* stack = reinterpret_cast<TStack<ISZ>*>(socket);
  stack->size_array = 0;
  stack->size_stack = size;
  stack->count_max = dimension_count;
  stack->count = 0;
  return stack;
}

/* Calculates the size of the Dimensions Stack with the TMatrix header. */
template <typename ISZ>
inline ISZ TDimensionsSize(ISZ dimension_count) {
  return sizeof(TMatrix<ISZ>) + sizeof(ISZ) * dimension_count;
}

template <typename T, typename ISZ, ISZ kAlignementMask_ = sizeof(T) - 1>
ISZ TMatrixSizeBytes(ISZ dimension_count, ISZ element_count) {
  ISZ size_bytes =
      TDimensionsSize<ISZ>(dimension_count) + sizeof(T) * element_count;
  return AlignUp(size_bytes, kAlignementMask_);
}

/* Creates a dynamically allocated ARY. */
template <typename T = ISW, typename ISZ = ISN>
TMatrix<ISZ>* TMatrixNew(ISZ x) {
  ISZ size = sizeof(TStack<ISZ>) + sizeof(T) * x;
  size = AlignUp(size);
}

/* Creates a dynamically allocated ARY. */
template <typename T = ISW, typename ISZ = ISN>
inline TMatrix<ISZ>* TMatrixNew(SocketFactory socket_factory, ISZ x, ISZ y) {
  if (x < 0 || y < 0) return nullptr;
  ISZ dimension_count = x * y,
      size_bytes = AlignUp(TMatrixSizeBytes<T, ISZ>(dimension_count));
  return TMatrixInit<T, ISZ>(socket_factory(nullptr, size_bytes), x, y);
}

/* Creates a dynamically allocated ARY. */
template <typename T = ISW, typename ISZ = ISN>
inline TMatrix<ISZ>* TMatrixNew(SocketFactory socket_factory, ISZ x, ISZ y,
                                ISZ z) {
  if (x < 0 || y < 0) return nullptr;
  ISZ element_count = z * x * y,
      size_bytes = AlignUp(TDimensionsSize<T, ISZ>(2, element_count));
  return TMatrixInit<T, ISZ>(socket_factory(nullptr, size_bytes), x, y);
}

template <typename T = ISW, typename ISZ = ISN>
inline TMatrix<ISZ>* TMatrixNew(const ISZ* dimensions) {
  D_ASSERT(dimensions);
  const ISZ* origin = dimensions;
  ISZ count = (*origin++) - 1,    //
      element_count = *origin++,  //
      index = count;
  while (index-- > 0) element_count *= *origin++;
  ISZ size = ((ISZ)element_count * (ISZ)sizeof(T));
}

/* Gets the address of the packed array.
@param obj ASCII Array data structure.
@return Pointer to the first element in the array. */
template <typename T, typename ISZ = ISN>
inline T* TMatrixElements(TMatrix<ISZ>* obj) {
  return reinterpret_cast<T*>(TStackStart<ISZ, ISZ>(&obj->dimensions) +
                              obj->size);
}

/* Creates a immutable array of dimensions. */
template <typename ISZ, const ISZ... N>
inline const ISZ* TDim() {
  static const ISZ cCount = (ISZ)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &cCount;
}

/* Creates a immutable array of ISB dimensions. */
template <const ISB... N>
inline const ISB* TDim2() {
  static const ISB cCount = (ISB)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &cCount;
}

/* Creates a immutable array of ISC dimensions. */
template <const ISC... N>
inline const ISC* TStack4() {
  static const ISC cCount = (ISC)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &cCount;
}

/* Creates a static array of ISD dimensions. */
template <const ISD... N>
inline const ISD* TDim8() {
  static const ISD cCount = (ISD)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &cCount;
}

template <typename T = ISW, typename ISZ = ISN>
inline ISZ TMatrixClone(TMatrix<ISZ>* matrix, SocketFactory socket_factory) {
  return 0;
}

template <typename T = ISW, typename ISZ = ISN>
inline IUW* TMatrixClone(TMatrix<ISZ>* matrix, TMatrix<ISZ>* other,
                         SocketFactory socket_factory) {
  return nullptr;
}

template <typename T = ISW, typename ISZ = ISN>
IUW* TMatrixNew(SocketFactory socket_factory) {}

/* A multi-dimensional array Ascii Object. */
template <typename T = ISW, typename ISZ = ISN, typename BUF = Nil>
class AMatrix {
  AArray<ISZ> obj_;  //< The Auto-array.

 public:
  /* Constructs an empty Matrix with 4 reserved dimensions and 64 elements. */
  AMatrix() : obj_(TMatrixSizeBytes<T, ISZ>(4, 64)) {}

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(ISZ x, const T* elements = nullptr) : obj_(TMatrixNew<T, ISZ>(x)) {
    D_ASSERT(x >= 0);
  }

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(ISZ x, ISZ y, const T* elements = nullptr)
      : obj_(TMatrixSizeBytes<T, ISZ>(2, x * y)) {
    D_ASSERT(x >= 0 && y >= 0);
  }

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(ISZ x, ISZ y, ISZ z, const T* elements = nullptr)
      : obj_(TMatrixSizeBytes<T, ISZ>(3, x * y * z)) {
    D_ASSERT(x >= 0 && y >= 0 && z >= 0);
  }

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(ISZ w, ISZ x, ISZ y, ISZ z, const T* elements = nullptr)
      : obj_(TMatrixSizeBytes<T, ISZ>(4, w * x * y * z)) {}

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(const AMatrix& other) : obj_(other.Obj()) {}

  /* Destructs nothing. */
  ~AMatrix() {}

  /* Clones the other object; up-sizing the socket only if required. */
  inline ISZ Clone(SocketFactory socket_factory = obj_.AJT().socket_factory) {
    TMatrixClone<T, ISZ>(obj_.Obj(), socket_factory);
    return this;
  }

  /* Clones the other object; up-sizing the socket only if required. */
  inline ISZ Clone(AMatrix<T, ISZ>& other,
                   SocketFactory socket_factory = obj_.AJT().socket_factory) {
    TMatrixClone<T, ISZ>(obj_.Obj(), other, socket_factory);
    return this;
  }

  /* Gets the number_ of dimensions. */
  inline ISZ DimensionCount() { return This().dimensions->count; }

  /* Gets the dimensions array. */
  inline T* Dimension() { return TStackStart<T, ISZ>(Array()); }

  /* Gets the underlying array. */
  inline T* Elements() { return TMatrixElements<T, ISZ>(This()); }

  /* Returns the Autoject-Array. */
  inline AArray<ISZ>& AJT_ARY() { return obj_; }

  /* Returns the Autoject. */
  inline Autoject& AJT() { return obj_.AJT(); }

  /* Returns the Autoject::origin cased as a TMap<ISZ>. */
  inline TMatrix<ISZ>* This() {
    return reinterpret_cast<TMatrix<ISZ>*>(AJT().origin);
  }

  /* Returns the Auto-Array. */
  inline AArray<T, ISZ, BUF>& Array() { return obj_; }

  template <typename Printer = COut>
  inline Printer& PrintTo(Printer& o) {
    return TMatrixPrint<Printer, T, ISZ>(o, This());
  }

  /* Operator= overload. */
  inline AMatrix<T, ISZ>& operator=(AMatrix<T, ISZ>& other) {
    Clone(other);
    return *this;
  }
};

}  //< namespace _
#endif
#endif
