// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_LIST
#include "../List.hpp"
#include "../RNG.h"
//#include "../Uniprinter.hpp"
#if SEAM == CRABS_LIST
#include "../_Debug.h"
#define TEST_MIN 0
#define TEST_MAX 0xffff
#else
#include "../_Release.h"
#define TEST_MIN 0
#define TEST_MAX 0xffff
#endif
using namespace ::_;
namespace CRTest {

template<LST_A>
static void TestList() {
  D_COUT(Linef("\n\n\n\n+---\n Testing AList<IS")
         << CSizeCodef<ISZ>() << Linef(">\n+---"));
  AList<LST_P, 256> list(8);
  D_COUT("\n\nlist.Size():" << list.Total()
                            << " list.Bytes():" << list.Bytes()
                            << " list.SizeWords():" << list.BytesWords());
  D_COUT_OBJ(list);
  D_COUT("\n\nStep 1: Fill up the list...");
  auto i = list.Count();
  A_AVOW(i, list.Insert(ISA('!' + i)));
  auto tv = TListTypeValue<LST_P>(list.This(), i);
  A_AVOW(DT(_ISA), tv.type);
  A_AVOW(ISA('!' + i++), *TPtr<ISA>(tv.value));

  A_AVOW(i, list.Insert(CHA('!' + i)));
  tv = TListTypeValue<LST_P>(list.This(), i);
  A_AVOW(DT(_CHA), tv.type);
  A_AVOW(IUA('!' + i++), *TPtr<IUA>(tv.value));

  A_AVOW(i, list.Insert(ISB('!' + i)));
  tv = TListTypeValue<LST_P>(list.This(), i);
  A_AVOW(DT(_ISB), tv.type);
  A_AVOW(ISB('!' + i++), *TPtr<ISB>(tv.value));

  A_AVOW(i, list.Insert(IUB('!' + i)));
  tv = TListTypeValue<LST_P>(list.This(), i);
  A_AVOW(DT(_IUB), tv.type);
  A_AVOW(IUB('!' + i++), *TPtr<IUB>(tv.value));

  A_AVOW(i, list.Insert(ISC('!' + i)));
  tv = TListTypeValue<LST_P>(list.This(), i);
  A_AVOW(DT(_ISC), tv.type);
  A_AVOW(ISC('!' + i++), *TPtr<ISC>(tv.value));

  A_AVOW(i, list.Insert(CHC('!' + i)));
  tv = TListTypeValue<LST_P>(list.This(), i);
  A_AVOW(DT(_CHC), tv.type);
  A_AVOW(IUC('!' + i++), *TPtr<IUC>(tv.value));

  A_AVOW(i, list.Insert(ISD('!' + i)));
  tv = TListTypeValue<LST_P>(list.This(), i);
  A_AVOW(DT(_ISD), tv.type);
  A_AVOW(ISD('!' + i++), *TPtr<ISD>(tv.value));

  A_AVOW(i, list.Insert(IUD('!' + i)));
  tv = TListTypeValue<LST_P>(list.This(), i);
  A_AVOW(DT(_IUD), tv.type);
  A_AVOW(IUD('!' + i++), *TPtr<IUD>(tv.value));

  D_COUT_OBJ(list);

  D_COUT("\n\nStep 2b: Testing auto-grow up to 16...");
  for (; i < 16;) {
    A_AVOW(i, list.Insert(ISA('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISA), tv.type);
    A_AVOW(ISA('!' + i++), *TPtr<ISA>(tv.value));

    A_AVOW(i, list.Insert(IUA('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUA), tv.type);
    A_AVOW(IUA('!' + i++), *TPtr<IUA>(tv.value));

    A_AVOW(i, list.Insert(ISB('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISB), tv.type);
    A_AVOW(ISB('!' + i++), *TPtr<ISB>(tv.value));

    A_AVOW(i, list.Insert(IUB('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUB), tv.type);
    A_AVOW(IUB('!' + i++), *TPtr<IUB>(tv.value));

    A_AVOW(i, list.Insert(ISC('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISC), tv.type);
    A_AVOW(ISC('!' + i++), *TPtr<ISC>(tv.value));

    A_AVOW(i, list.Insert(IUC('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUC), tv.type);
    A_AVOW(IUC('!' + i++), *TPtr<IUC>(tv.value));

    A_AVOW(i, list.Insert(ISD('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISD), tv.type);
    A_AVOW(ISD('!' + i++), *TPtr<ISD>(tv.value));

    A_AVOW(i, list.Insert(IUD('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUD), tv.type);
    A_AVOW(IUD('!' + i++), *TPtr<IUD>(tv.value));
  }
  D_COUT_OBJ(list);
  D_COUT("\n\nStep 2c: Testing auto-grow up to 32...");
  for (; i < 32;) {
    A_AVOW(i, list.Insert(ISA('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISA), tv.type);
    A_AVOW(ISA('!' + i++), *TPtr<ISA>(tv.value));

    A_AVOW(i, list.Insert(IUA('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUA), tv.type);
    A_AVOW(IUA('!' + i++), *TPtr<IUA>(tv.value));

    A_AVOW(i, list.Insert(ISB('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISB), tv.type);
    A_AVOW(ISB('!' + i++), *TPtr<ISB>(tv.value));

    A_AVOW(i, list.Insert(IUB('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUB), tv.type);
    A_AVOW(IUB('!' + i++), *TPtr<IUB>(tv.value));

    A_AVOW(i, list.Insert(ISC('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISC), tv.type);
    A_AVOW(ISC('!' + i++), *TPtr<ISC>(tv.value));

    A_AVOW(i, list.Insert(IUC('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUC), tv.type);
    A_AVOW(IUC('!' + i++), *TPtr<IUC>(tv.value));

    A_AVOW(i, list.Insert(ISD('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISD), tv.type);
    A_AVOW(ISD('!' + i++), *TPtr<ISD>(tv.value));

    A_AVOW(i, list.Insert(IUD('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUD), tv.type);
    A_AVOW(IUD('!' + i++), *TPtr<IUD>(tv.value));
  }
  D_COUT_OBJ(list);
  D_COUT("\n\nStep 2d: Testing auto-grow up to 64...");
  for (; i < 64;) {
    A_AVOW(i, list.Insert(ISA('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISA), tv.type);
    A_AVOW(ISA('!' + i++), *TPtr<ISA>(tv.value));

    A_AVOW(i, list.Insert(IUA('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUA), tv.type);
    A_AVOW(IUA('!' + i++), *TPtr<IUA>(tv.value));

    A_AVOW(i, list.Insert(ISB('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISB), tv.type);
    A_AVOW(ISB('!' + i++), *TPtr<ISB>(tv.value));

    A_AVOW(i, list.Insert(IUB('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUB), tv.type);
    A_AVOW(IUB('!' + i++), *TPtr<IUB>(tv.value));

    A_AVOW(i, list.Insert(ISC('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISC), tv.type);
    A_AVOW(ISC('!' + i++), *TPtr<ISC>(tv.value));

    A_AVOW(i, list.Insert(IUC('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUC), tv.type);
    A_AVOW(IUC('!' + i++), *TPtr<IUC>(tv.value));

    A_AVOW(i, list.Insert(ISD('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_ISD), tv.type);
    A_AVOW(ISD('!' + i++), *TPtr<ISD>(tv.value));

    A_AVOW(i, list.Insert(IUD('!' + i)));
    tv = TListTypeValue<LST_P>(list.This(), i);
    A_AVOW(DT(_IUD), tv.type);
    A_AVOW(IUD('!' + i++), *TPtr<IUD>(tv.value));
  }
  A_ASSERT(list.Count() == 64);

  D_COUT("\n\nStep 2: Testing pop...");
  for (ISY i = list.Total() - 1; i >= 0; --i)
    list.Pop();

  list.Clear();
  i = 0;
  D_COUT("\n\nStep 3: Testing SCKPack...");
  //for (IS j = 0; j < 3; ++j)
  //  A_AVOW(count++, list.Insert(test_cha[j]));
  //A_AVOW(IS(3), list.Insert(test_isc[0]));
  //D_COUT_OBJ(list);
  //A_AVOW(IS(3), list.Insert(test_cha[3], SCKPack));
  // @todo Add more SCKPack test cases.
}
}  //< namespace CRTest
#endif

namespace CRTest {
static const CHA* List(const CHA* args) {
#if SEAM >= CRABS_LIST
  A_TEST_BEGIN;
  TestList<ISB, ISA, DTB>();
  TestList<ISC, ISB, DTB>();
  TestList<ISD, ISC, DTB>();
  TestList<ISD, ISD, DTB>();
#endif
  return NILP;
}
}  //< namespace CRTest
#undef TEST_MIN
#undef TEST_MAX
