// Copyright AStarship <https://astarship.net>.
#include "../_Config.h"
#include "../Binary.hpp"
#include <stdio.h>
#include <string.h>

namespace _ {
namespace AlignmentTest {
static ISW checks = 0, failures = 0;
static void Check(BOL pass, const CHA* name) {
  ++checks;
  if (!pass) { ++failures; if (failures <= 12) printf("FAIL: %s\n", name); }
}

template<typename I>
static void Integers() {
  for (ISC mask = 0; mask <= 7; mask = mask * 2 + 1) {
    const ISC alignment = mask + 1;
    for (ISC input = 0; input <= 64; ++input) {
      const I value = I(input), m = I(mask);
      const I down = I(input - input % alignment);
      const I up = I(input + (input % alignment ? alignment - input % alignment : 0));
      Check(AlignDown(value, m) == down, "runtime align down");
      Check(CAlignDown(value, m) == down, "constexpr align down");
      Check(AlignUp(value, m) == up && CAlignUp(value, m) == up, "align up parity");
      Check(TAlignUp(value, m) == up && TAlignDownI(value, m) == down, "template mask parity");
    }
  }
}

static void Pointers() {
  alignas(IUW) CHA bytes[96] = {};
  for (ISW offset = 0; offset < 32; ++offset) {
    CHA* p = bytes + offset;
    const CHA* cp = p;
    for (IUW mask = 0; mask <= 7; mask = mask * 2 + 1) {
      const IUW address = IUW(p), alignment = mask + 1;
      const IUW down = address - address % alignment;
      const IUW up = address + (address % alignment ? alignment - address % alignment : 0);
      Check(IUW(AlignDown(p, mask)) == down, "mutable pointer mask is not an offset");
      Check(IUW(AlignDown(cp, mask)) == down, "const pointer mask is not an offset");
      Check(IUW(AlignUp(cp, mask)) == up, "pointer align up");
      Check(IUW(TPtrUp<CHA>(p, ISW(mask))) == up &&
            IUW(TPtrUp<CHA>(cp, ISW(mask))) == up, "typed pointer up");
      Check(IUW(TPtrDown<CHA>(p, 0, ISW(mask))) == down, "explicit pointer offset/mask");
    }
    Check(AlignUpC(p) == ISC((sizeof(ISC) - IUW(p) % sizeof(ISC)) % sizeof(ISC)),
          "AlignUpC uses ISC width, not word width");
  }
}

template<typename T, typename I>
static void ArrayCounts() {
  const ISW multiple = sizeof(IUW) > sizeof(T) ? sizeof(IUW) / sizeof(T) : 1;
  for (ISC count = 0; count <= 64; ++count) {
    const I expected = I((count + multiple - 1) / multiple * multiple);
    Check(TAlignUpArray<T>(I(count)) == expected, "typed array uses element width");
    if constexpr (__is_same(T, I))
      Check(AlignUpArray(I(count)) == expected, "array count has defined return and alignment");
  }
}

static void Extremes() {
  volatile ISC low_c = ISC(IUC(1) << 31);
  volatile ISD low_d = ISD(IUD(1) << 63);
  volatile IUC high_c = IUC(1) << 31;
  volatile IUD high_d = IUD(1) << 63;
  Check(AlignUp(ISC(low_c), ISC(7)) == low_c, "ISC minimum aligns without signed negation");
  Check(CAlignUp(ISD(low_d), ISD(7)) == low_d, "ISD minimum aligns without signed negation");
  Check(AlignUp(IUC(high_c), IUC(7)) == high_c, "high IUC stays unsigned");
  Check(TAlignUp(IUD(high_d), IUD(7)) == high_d, "high IUD stays unsigned");
}
}  //< namespace AlignmentTest
}  //< namespace _

ISN main(ISN argc, CHA** argv) {
  using namespace _::AlignmentTest;
  const CHA* group = argc > 1 ? argv[1] : "integers";
  if (strcmp(group, "integers") == 0) {
    Integers<ISA>(); Integers<IUA>(); Integers<ISB>(); Integers<IUB>();
    Integers<ISC>(); Integers<IUC>(); Integers<ISD>(); Integers<IUD>();
  } else if (strcmp(group, "pointers") == 0) Pointers();
  else if (strcmp(group, "arrays") == 0) {
    ArrayCounts<ISA, ISA>(); ArrayCounts<IUA, IUA>();
    ArrayCounts<ISB, ISB>(); ArrayCounts<IUB, IUB>();
    ArrayCounts<ISC, ISC>(); ArrayCounts<IUC, IUC>();
    ArrayCounts<ISD, ISD>(); ArrayCounts<IUD, IUD>();
    ArrayCounts<IUA, ISC>(); ArrayCounts<IUB, ISC>();
  } else if (strcmp(group, "extremes") == 0) Extremes();
  else return 2;
  printf("BinaryAlignment %s: checks=%ld failures=%ld\n", group, long(checks), long(failures));
  return failures != 0;
}
