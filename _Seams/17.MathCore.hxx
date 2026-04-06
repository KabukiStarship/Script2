// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_MATHCORE
#include "../Matrix.hpp"
#if SEAM == CRABS_MATHCORE
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
using namespace ::_;
namespace CRTest {

template<typename ISZ, typename ISY, typename T>
void TestMatrixIntegers() {
  //D_LINEF("\n\n+---\n| Testing AMatrix<IS" << CSizef<ISZ>() << ">\n+---");
  D_LINEF("\n\n+---\n| Testing AMatrix<IS");// << ASizeCodef<ISZ>() << Linef(">\n+---");

  static const ISC array_3d_expected[2][2][2] = {{{0, 1}, {2, 3}},
                                                {{4, 5}, {6, 7}}};
  const ISC* dimensions = TDimC<2, 2, 2>();
  AMatrix<MTX_P> matrix(2, 2, 2, &array_3d_expected[0][0][0]);
  D_COUT_OBJ(matrix);
  ISC w = 0;
  T* array_base = matrix.Start();
  for (ISC x = 0; x < 2; ++x) {
    for (ISC y = 0; y < 2; ++y) {
      for (ISC z = 0; z < 2; ++z) {
        A_AVOW(w++, array_3d_expected[x][y][z]);
      }
    }
  }
}
}  //< namespace CRTest
#endif

namespace CRTest {
static const CHA* MathCore(const CHA* args) {
#if SEAM >= CRABS_MATHCORE
  A_TEST_BEGIN;
  TestMatrixIntegers<ISA, ISA, ISA>();
  TestMatrixIntegers<ISA, ISA, ISB>();
  TestMatrixIntegers<ISA, ISA, ISC>();
  TestMatrixIntegers<ISA, ISA, ISD>();
  TestMatrixIntegers<IUB, ISB, ISA>();
  TestMatrixIntegers<IUB, ISB, ISB>();
  TestMatrixIntegers<IUB, ISB, ISC>();
  TestMatrixIntegers<IUB, ISB, ISD>();
  TestMatrixIntegers<ISC, ISC, ISA>();
  TestMatrixIntegers<ISC, ISC, ISB>();
  TestMatrixIntegers<ISC, ISC, ISC>();
  TestMatrixIntegers<ISC, ISC, ISD>();
  TestMatrixIntegers<IUD, ISC, ISA>();
  TestMatrixIntegers<IUD, ISC, ISB>();
  TestMatrixIntegers<IUD, ISC, ISC>();
  TestMatrixIntegers<IUD, ISC, ISD>();
#endif
  return NILP;
}
}  //< namespace CRTest
