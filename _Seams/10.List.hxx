// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_LIST
#include "../List.hpp"
#include "../RNG.h"
//#include "../Uniprinter.hpp"
#if SEAM == SCRIPT2_LIST
#include "../_Debug.hxx"
#define TEST_MIN 0
#define TEST_MAX 0xffff
#else
#include "../_Release.hxx"
#define TEST_MIN 0
#define TEST_MAX 0xffff
#endif
using namespace _;
namespace Script2 {

template<typename ISZ, typename ISY>
static void TestList() {
  D_COUT(Linef("\n\n\n\n+---\n Testing AList<IS")
         << CSizeCodef<ISZ>() << Linef(">\n+---"));

  AList<ISZ, ISY, 1024, 40> list;
  D_COUT("\n\nlist.Size():" << list.Size()
                            << " list.SizeBytes():" << list.SizeBytes()
                            << " list.SizeWords():" << list.SizeWords());
  D_COUT_OBJ(list);
  D_COUT("\n\nPushing items on to the List stack...\n");

  const CHA test_cha[] = {'a', 'b', 'c', 'd'};
  const ISC test_isc[] = {'0', '1', '2', '3'};
  const FPC test_fpc[] = {1.0f, 2.0f, 3.0f, 4.0f};
  const IUD test_iud[] = {'w', 'x', 'y', 'z'};
  const char* test_sta[] = {"A", "B", "C", "D"};

  enum { TestCount = 1 };
  ISY count = 0;
  for (ISY i = 0; i < TestCount; ++i) {
    for (ISY j = 0; j < 4; ++j) {
      A_AVOW(count++, list.Insert(test_cha[j]));
    }
  }
  
  D_COUT_OBJ(list);
  for (ISY i = 0; i < TestCount; ++i) {
    for (ISY j = 0; j < 4; ++j) {
      A_AVOW(count++, list.Insert(test_isc[j]));
    }
  }
  D_COUT_OBJ(list);
  for (ISY i = 0; i < TestCount; ++i) {
    for (ISY j = 0; j < 4; ++j) {
      A_AVOW(count++, list.Insert(test_cha[j]));
      A_AVOW(count++, list.Insert(test_isc[j]));
      A_AVOW(count++, list.Insert(test_fpc[j]));
      A_AVOW(count++, list.Insert(test_iud[j]));
    }
  }
  D_COUT_OBJ(list);
  for (ISY i = TestCount - 1; i >= 0; --i) list.Pop();
  
  D_COUT("\n\nTesting SCKPack...");
  list.Clear();
  count = 0;

  //for (IS j = 0; j < 3; ++j)
  //  A_AVOW(count++, list.Insert(test_cha[j]));
  //A_AVOW(IS(3), list.Insert(test_isc[0]));
  //D_COUT_OBJ(list);
  //A_AVOW(IS(3), list.Insert(test_cha[3], SCKPack));
  // @todo Add more SCKPack test cases.
}
}  //< namespace Script2
#endif

namespace Script2 {
static const CHA* List(const CHA* args) {
#if SEAM >= SCRIPT2_LIST
  A_TEST_BEGIN;
  TestList<ISB, ISA>();
  TestList<ISC, ISB>();
  TestList<ISD, ISC>();
  TestList<ISD, ISD>();
#endif
  return nullptr;
}
}  //< namespace Script2
#undef TEST_MIN
#undef TEST_MAX
