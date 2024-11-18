// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_FTOS
//#include "../RNG.h"
#if SEAM == SCRIPT2_FTOS
#include "../_Debug.hxx"
#else
#include "../_Release.hxx"
#endif
#endif

using namespace std;
using namespace _;
namespace Script2 {
const CHA* FtoS(const CHA* args) {
#if SEAM >= SCRIPT2_FTOS
  A_TEST_BEGIN;

#if SEAM == SCRIPT2_FTOS
  enum { TestCount = 1 << 20 };
#else
  enum { TestCount = 1 << 15 };
#endif
  /*
  enum { Size = 31 };
  CHA socket[Size + 1];

  IUD value;
  FPD dbl_expected, dbl_found;

  D_COUT("\n\nTesting Float Ceiling<Float, IU> (Float)...\n");

  for (ISC i = 0; i < TestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FPD>(value);
    } while (!IsFinite(dbl_expected));
    dbl_found = ceil(dbl_expected);
    dbl_expected = Ceiling(dbl_expected);
    Test(dbl_expected, dbl_found);
  }

  D_COUT(
      "\n\nTesting const CHT* TSScan<CHT> (const CHT*, const CHT*, FPC&) "
      "functions...\n");

  for (ISC i = 0; i < TestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FPD>(value);
    } while (!IsFinite(dbl_expected));
    sprintf_s(socket, Size, "%lf", dbl_expected);
    A_ASSERT(SScan(socket, dbl_found));
    A_AVOW(dbl_expected, dbl_found);
  }

  D_COUT("\n\nTesting CHT* TSPrint<CHT> (CHT*, CHT*, Float)...\n");

  for (ISC i = 0; i < TestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FPD>(value);
    } while (!IsFinite(dbl_expected));
    Print(socket, socket + Size, dbl_expected);
    ISC r = sscanf_s(socket, "%lf", &dbl_found);
    A_ASSERT(r);
    A_AVOW(dbl_expected, dbl_found);
  }
  TBinary<>::PrintDebugInfo();
  */
#endif
  return nullptr;
}
}  //< namespace Script2
