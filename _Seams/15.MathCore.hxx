// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_MATRIX
#include "../Matrix.hpp"
#if SEAM == CRABS_MATRIX
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
using namespace ::_;
namespace Crabs {

template<typename ISZ, typename T>
void TestMatrixIntegers() {
  //D_LINEF("\n\n+---\n| Testing AMatrix<IS" << CSizef<ISZ>() << ">\n+---");
  D_LINEF("\n\n+---\n| Testing AMatrix<IS");
  D_COUT(CASizeCodef<ISZ>());
  D_LINEF(">\n+---"); //< @todo Find a better way to do this.

  static const ISC array_3d_exected[2][2][2] = {{{0, 1}, {2, 3}},
                                                {{4, 5}, {6, 7}}};
  const ISC* dimensions = TDimC<2, 2, 2>();
  AMatrix<ISC> matrix(2, 2, 2, &array_3d_exected[0][0][0]);
  D_COUT_OBJ(matrix);
  ISC w = 0;
  ISC* array_base = matrix.Start();
  for (ISC x = 0; x < 2; ++x) {
    for (ISC y = 0; y < 2; ++y) {
      for (ISC z = 0; z < 2; ++z) {
        A_AVOW(w++, array_3d_exected[x][y][z]);
      }
    }
  }
}
}  //< namespace Crabs
#endif

namespace Crabs {
static const CHA* MathCore(const CHA* args) {
#if SEAM >= CRABS_MATRIX
  A_TEST_BEGIN;
  TestMatrixIntegers<ISA, ISA>();
  TestMatrixIntegers<ISA, ISB>();
  TestMatrixIntegers<ISA, ISC>();
  TestMatrixIntegers<ISA, ISD>();
  TestMatrixIntegers<IUB, ISA>();
  TestMatrixIntegers<IUB, ISB>();
  TestMatrixIntegers<IUB, ISC>();
  TestMatrixIntegers<IUB, ISD>();
  TestMatrixIntegers<ISC, ISA>();
  TestMatrixIntegers<ISC, ISB>();
  TestMatrixIntegers<ISC, ISC>();
  TestMatrixIntegers<ISC, ISD>();
  TestMatrixIntegers<IUD, ISA>();
  TestMatrixIntegers<IUD, ISB>();
  TestMatrixIntegers<IUD, ISC>();
  TestMatrixIntegers<IUD, ISD>();
#endif
  return NILP;
}
}  //< namespace Crabs
