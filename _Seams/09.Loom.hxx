// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_LOOM
#include "../Loom.hpp"
//
#include "TestWords.h"
#if SEAM == CRABS_LOOM
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
using namespace ::_;
namespace Crabs {

template<typename CH = CHR, typename ISZ = ISN, typename ISY = ISN>
void TestLoom() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    Size = 256 * sizeof(CH),
    Count = 16,
  };
  D_COUT("Testing ALoom<CH" << CSizeCodef<CH>() << ",IS" << CSizeCodef<ISZ>()
         << "> with Size:" << Size << " and Count:" << Count);

  ALoom<CH, ISZ, ISY, Size, TBOF<Size>> loom(Count);
#if D_THIS
  D_COUT("\nPrinting empty loom:\n");
  loom.COut();
#endif

  enum {
    LengthMax = (Size << 2) - 1,
  };

  CH str[LengthMax + 1] = {};
  CH* string_end = &str[LengthMax];
  ISY i = 0;
  for (; i < Count; ++i) {
    TSPrint<CH>(str, string_end, i);
    D_COUT("\nstr:" << str);
    A_AVOW(ISY(i), loom.Insert<CH>(str));
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  TSPrint<CH>(str, string_end, Count);
  loom.Insert(str);
  auto boofer = loom.AJT().origin;
  auto dez_nutz = loom.Insert(str);
  A_AVOW(boofer, loom.AJT().origin);
  //i = Count + 1;
  A_AVOW(++i, dez_nutz);
  for (i; i < 96; ) {
    TSPrint<CH>(str, string_end, i);
    A_AVOW(ISY(++i), loom.Insert(str));
  }

  TSPrint<CH>(str, string_end, i);
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

  static const CH a[] = {'A', '\0'}, b[] = {'B', '\0'}, c[] = {'C', '\0'},
                   d[] = {'D', '\0'}, abc[] = {'a', 'b', 'c', '\0'},
                   bac[] = {'b', 'a', 'c', '\0'}, cba[] = {'c', 'b', 'a', '\0'},
                   cab[] = {'c', 'a', 'b', '\0'},
                   test[] = {'t', 'e', 's', 't', '\0'};

  A_AVOW(ISY(99), loom.Insert(d));
  A_AVOW(ISY(99), loom.Find(d));

  A_AVOW(ISY(100), loom.Insert(c));
  A_AVOW(ISY( 99), loom.Find(d));
  A_AVOW(ISY(100), loom.Find(c));

  A_AVOW(ISY(101), loom.Insert(b));
  A_AVOW(ISY( 99), loom.Find(d));
  A_AVOW(ISY(100), loom.Find(c));
  A_AVOW(ISY(101), loom.Find(b));

  A_AVOW(ISY(102), loom.Insert(a));
  A_AVOW(ISY( 99), loom.Find(d));
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
}  //< namespace Crabs
#endif

namespace Crabs {
static const CHA* Loom(const CHA* args) {
#if SEAM >= CRABS_LOOM
  A_TEST_BEGIN;
  //TestLoom<CHA, ISB, ISB>();
  //TestLoom<CHA, ISC, ISC>();
  //TestLoom<CHA, ISB, ISA>();
  //TestLoom<CHA, ISC, ISB>();
  TestLoom<CHA, ISD, ISC>();
#if USING_STB == YES_0
  //TestLoom<CHB, ISB, ISB>();
  //TestLoom<CHB, ISC, ISC>();
  //TestLoom<CHB, ISB, ISA>();
  //TestLoom<CHB, ISC, ISB>();
  TestLoom<CHB, ISD, ISC>();
#endif
#if USING_STC == YES_0
  //TestLoom<CHC, ISC, ISC>();
  //TestLoom<CHC, ISB, ISA>();
  //TestLoom<CHC, ISC, ISB>();
  TestLoom<CHC, ISD, ISC>();
#endif
#endif
  return NILP;
}
}  //< namespace Crabs
