// Copyright AStarship <https://astarship.net>.
// Direct low-seam regression: do not pull in Array/Room to format digits.
#include "../_Config.h"
#include "../Puff.hxx"
#include <stdio.h>

namespace _ {
namespace PuffTest {
static ISW checks = 0;
static ISW failures = 0;

static void Check(BOL pass, const CHA* label) {
  ++checks;
  if (!pass) {
    ++failures;
    if (failures <= 10) printf("FAIL: %s\n", label);
  }
}

template<typename CH>
static void Pairs() {
  const IUB* lut = BinaryLUTDecimals();
  for (ISW offset = 0; offset < ISW(sizeof(IUW)); ++offset) {
    for (IUB value = 0; value < 100; ++value) {
      for (ISC variant = 0; variant < 2; ++variant) {
        alignas(IUW) CH text[32];
        for (CH& item : text) item = CH(0x7f);
        CH* start = text + offset + 1;
        if (variant == 0)
          Check(TSPrint2Decimals(start, lut[value]) == start,
                "pair helper preserves return contract");
        else
          SPrintCharPair(start, lut[value]);
        BOL pass = start[0] == CH('0' + value / 10) &&
                   start[1] == CH('0' + value % 10);
        for (ISW i = 0; i < 32; ++i)
          if (i != offset + 1 && i != offset + 2 && text[i] != CH(0x7f))
            pass = false;
        Check(pass, "decimal pair order, character width and canaries");
      }
    }
  }
}
}  //< namespace PuffTest
}  //< namespace _

ISN main() {
  _::PuffTest::Pairs<CHA>();
  _::PuffTest::Pairs<CHB>();
  _::PuffTest::Pairs<CHC>();
  printf("PuffAlignment: checks=%ld failures=%ld\n",
         long(_::PuffTest::checks), long(_::PuffTest::failures));
  return _::PuffTest::failures != 0;
}
