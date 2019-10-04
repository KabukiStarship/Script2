/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/07.matrix.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_MATRIX
#include "../matrix.hpp"
using namespace _;
#if SEAM == SCRIPT2_MATRIX
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif

namespace script2 {

template <typename SI, typename SIZ>
void TestMatrixIntegers() {
  D_COUT(Linef("\n\n+---\n| ")
         << "Testing AMatrix<SI" << sizeof(SIZ) << ">" << Linef("\n+---"));

  static const SI4 array_3d_exected[2][2][2] = {{{0, 1}, {2, 3}},
                                                {{4, 5}, {6, 7}}};
  const SI4* dimensions = TStack4<2, 2, 2>();
  AMatrix<SI4> matrix(2, 2, 2, &array_3d_exected[0][0][0]);
  D_COUT_OBJ(matrix);
  SI4 w = 0;
  SI4* array_base = matrix.Elements();
  for (SI4 x = 0; x < 2; ++x)
    for (SI4 y = 0; y < 2; ++y)
      for (SI4 z = 0; z < 2; ++z) A_AVOW(w++, array_3d_exected[x][y][z]);
}
}  // namespace script2
#endif

namespace script2 {
static const CH1* Matrix(const CH1* args) {
#if SEAM >= SCRIPT2_MATRIX
  A_TEST_BEGIN;
  TestMatrixIntegers<SI1, SI1>();
  TestMatrixIntegers<SI1, SI2>();
  TestMatrixIntegers<SI1, SI4>();
  TestMatrixIntegers<SI1, SI8>();
  TestMatrixIntegers<UI2, SI1>();
  TestMatrixIntegers<UI2, SI2>();
  TestMatrixIntegers<UI2, SI4>();
  TestMatrixIntegers<UI2, SI8>();
  TestMatrixIntegers<SI4, SI1>();
  TestMatrixIntegers<SI4, SI2>();
  TestMatrixIntegers<SI4, SI4>();
  TestMatrixIntegers<SI4, SI8>();
  TestMatrixIntegers<UI8, SI1>();
  TestMatrixIntegers<UI8, SI2>();
  TestMatrixIntegers<UI8, SI4>();
  TestMatrixIntegers<UI8, SI8>();
#endif
  return nullptr;
}
}  // namespace script2
