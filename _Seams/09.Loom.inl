// Copyright Kabuki Starship™ <kabukistarship.com>.
#if SEAM >= SCRIPT2_LOOM
#include "../Loom.hpp"
//
#include "TestWords.h"
#if SEAM == SCRIPT2_LOOM
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
using namespace _;
namespace Script2 {

template<typename CHT = CHR, typename ISZ = ISN, typename ISY = ISN>
void TestLoom() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    Size = 192 * sizeof(CHT),
    cCount = 32,
  };
  D_COUT("Testing ALoom<CH" << CSizeCodef<CHT>() << ",IS" << CSizeCodef<ISZ>()
         << "> with Size:" << Size << " and cCount:" << cCount);

  ALoom<CHT, ISZ, ISY, Size, TBUF<Size>> loom(cCount);
#if D_THIS
  D_COUT("\nPrinting empty loom:\n");
  loom.COut();
#endif

  enum {
    LengthMax = (Size << 2) - 1,
  };

  CHT str[LengthMax + 1] = {};
  CHT* string_end = &str[LengthMax];

  for (ISN i = 0; i < 32; ++i) {
    TSPrint<CHT>(str, string_end, i);
    A_AVOW(ISY(i), loom.Insert(str));
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  TSPrint<CHT>(str, string_end, 32);
  loom.Insert(str);
  auto boofer = loom.AJT().origin;
  auto dez_nutz = loom.Insert(str);
  auto boofing_dez_nutz = loom.AJT().origin;
  A_AVOW(boofer, boofing_dez_nutz);
  ISY i = 33;
  A_AVOW(i, dez_nutz);
  for (i; i < 96; ) {
    TSPrint<CHT>(str, string_end, i);
    A_AVOW(ISY(++i), loom.Insert(str));
  }

  TSPrint<CHT>(str, string_end, i);
  A_AVOW(++i, loom.Insert(str));

  D_COUT("\n\nAttmpeting to add a very large string...\n");

  for (i = 0; i < LengthMax; ++i) str[i] = '*';

  str[LengthMax] = 0;

  ISY index = loom.Insert(str);
#if D_THIS
  loom.COut();
#endif
  A_AVOW(ISY(98), index);

#if D_THIS
  D_COUT('\n');
  loom.COut();
  D_COUT('\n');
#endif

  D_COUT("\nTesting TLoomFind...\n");

  static const CHT a[] = {'A', '\0'}, b[] = {'B', '\0'}, c[] = {'C', '\0'},
                   d[] = {'D', '\0'}, abc[] = {'a', 'b', 'c', '\0'},
                   bac[] = {'b', 'a', 'c', '\0'}, cba[] = {'c', 'b', 'a', '\0'},
                   cab[] = {'c', 'a', 'b', '\0'},
                   test[] = {'t', 'e', 's', 't', '\0'};

  A_AVOW(ISY(99), loom.Insert(d));
  A_AVOW(ISY(99), loom.Find(d));

  A_AVOW(ISY(100), loom.Insert(c));
  A_AVOW(ISY(99), loom.Find(d));
  A_AVOW(ISY(100), loom.Find(c));

  A_AVOW(ISY(101), loom.Insert(b));
  A_AVOW(ISY(99), loom.Find(d));
  A_AVOW(ISY(100), loom.Find(c));
  A_AVOW(ISY(101), loom.Find(b));

  A_AVOW(ISY(102), loom.Insert(a));
  A_AVOW(ISY(99), loom.Find(d));
  A_AVOW(ISY(100), loom.Find(c));
  A_AVOW(ISY(101), loom.Find(b));
  A_AVOW(ISY(102), loom.Find(a));

  A_AVOW(ISY(103), loom.Insert(abc));
  A_AVOW(ISY(103), loom.Find(abc));

  A_AVOW(ISY(104), loom.Insert(bac));
  A_AVOW(ISY(103), loom.Find(abc));
  A_AVOW(ISY(104), loom.Find(bac));

  A_AVOW(ISY(105), loom.Insert(cba));
  A_AVOW(ISY(103), loom.Find(abc));
  A_AVOW(ISY(104), loom.Find(bac));
  A_AVOW(ISY(105), loom.Find(cba));

  A_AVOW(ISY(106), loom.Insert(cab));
  A_AVOW(ISY(103), loom.Find(abc));
  A_AVOW(ISY(104), loom.Find(bac));
  A_AVOW(ISY(105), loom.Find(cba));
  A_AVOW(ISY(106), loom.Find(cab));

#if D_THIS
  D_COUT('\n');
  loom.COut();
  D_COUT('\n');
#endif

  A_AVOW(ISY(-1), loom.Find(test));
}
}  //< namespace Script2
#endif

namespace Script2 {
static const CHA* Loom(const CHA* args) {
#if SEAM >= SCRIPT2_LOOM
  A_TEST_BEGIN;
  TestLoom<CHA, ISB, ISB>();
  TestLoom<CHA, ISC, ISC>();
#if USING_UTF16 == YES_0
  TestLoom<CHB, ISB, ISB>();
  TestLoom<CHB, ISC, ISC>();
#endif
#if USING_UTF32 == YES_0
  TestLoom<CHC, ISC, ISC>();
#endif
#endif
  return nullptr;
}
}  //< namespace Script2
