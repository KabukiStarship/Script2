// Copyright Kabuki Starship™ <kabukistarship.com>.
#if SEAM >= SCRIPT2_CRABS
//#include "../Crabs.h"
//#include "../BIn.hpp"
//#include "../BOut.hpp"
#if SEAM == SCRIPT2_CRABS
#include "../_Debug.hxx"
#else
#include "../_Release.hxx"
#endif
#endif
using namespace _;
namespace Script2 {

static const CHA* Crabs(const CHA* args) {
#if SEAM == SCRIPT2_CRABS
  A_TEST_BEGIN;

  //enum {
  //  BooferSize = 2048,
  //  BooferWords = BooferSize / sizeof(IUW),
  //  StackHeight = 8,
  //};
  //IUW boofer[BooferWords], unpacked_expr[BooferWords];
  //D_COUT("\n|  - Running OperationTests in address ranges: [0x"
  //       << Hexf(&boofer[0]) << ":0x" << Hexf(&boofer[BooferWords - 1]));

  //This a;

  //Crabs* crabs = CrabsInit(boofer, BooferSize, StackHeight, /*&a*/nullptr,
  //                         unpacked_expr, BooferSize);
  //CrabsPrint(crabs);

  //D_COUT("\n|    Testing Root (@see \"a.h\")...\n");

  //void* args[4];
  //uint8_t io_number_ = 98;  //< ASCII:'b'
  //BIn* bin = CrabsBIn(crabs);
  //BOut* bout = CrabsBOut(crabs);

  //const Op* result;
  //CrabsRingBell(crabs);
  //CrabsAckBack(crabs);
  //result =
  //    BOutWrite(bout, TParams<4, _ADR, _IUA, _CHA, Parent::cStringBooferBytes, _ADR>(),
  //              Args(args, TAddress<'A', 'A', 'A'>(), &io_number_, Const("Test"),
  //                   TAddress<_BS, _CR>()));
  //BOutPrint(bout);
  //A_ASSERT(!result);

  //CrabsPrint(crabs);

  // Mirror mirror (bin, bout);
  // Bypass handshake for testing purposes.
  //CrabsScan(crabs);  //, &mirror);
  //CrabsPrint(crabs);
  D_COUT("\n| Done with Crabs tests.");
#endif
  return nullptr;
}
}  //< namespace Script2
