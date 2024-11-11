// Copyright Kabuki Starship™ <kabukistarship.com>.
#if SEAM >= SCRIPT2_CLOCK
#include "../Clock.hpp"
#include "../Uniprinter.hpp"
#if SEAM == SCRIPT2_CLOCK
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif

using namespace _;
namespace Script2 {
static const CHA* Clock(const CHA* args) {
#if SEAM >= SCRIPT2_CLOCK
  A_TEST_BEGIN;

  D_COUT(Headingf("Testing TScanTime..."));

  ISC t, t_found;
  const CHA* result;

  // @note The following dates must be the current day to work right in order
  // to auto-detect the year.
  const CHA* Strings[] = {
    "1/19",
    "01/19",
    "1/9/19",
    "1/19/19",
    "1/9/2019",
    "1/19/2019",
    "1/19/2019",
    "01/19/2019",
    "1/19/2019@00",
    "1.19.2019@00AM",
    "1/19/2019@00:00",
    "1/19/19@00:0AM",
    "1/19/2019@00:00:00",
    "1/19/2019@00:00:00AM",
    "2019-01-19@00:00:00AM",
    "2019-01-19@00:00:00am",
    "2019-01-19@00:00:00A",
    "2019-01-19@00:00:00a ",
  };

  for (ISC i = 0; i < 18; ++i) {
    D_COUT(Linef('-') << "\n    " << i);
    ISC t = 0;
    result = ScanTime(Strings[i], t);
    // Assert (!ClockCompare (t, 2018, 8, 9, 0, 0, 0))
  }

  D_COUT("\n\nTesting more valid input...\n");

  enum { Size = 128 };
  CHA socket[Size];

  t = ClockTimeTMS(8, 9, 17, 4, 20);
  ClockPrint(socket, socket + Size, t);
  result = ScanTime(socket, t_found);
  A_ASSERT(ClockCompare(t_found, t));

  t = ClockTimeTMS(2020, 4, 20, 4, 20);
  ClockPrint(socket, socket + Size, t);
  result = ScanTime(socket, t_found);
  A_ASSERT(ClockCompare(t, t_found));

  t = ClockTimeTMS(1947, 12, 7, 23, 5, 7);
  ClockPrint(socket, socket + Size, t);
  D_COUT("\n  Before:\"" << socket << '\"');
  result = TSScan<CHA>(socket, t_found);
  D_COUT("\n\n\nresult:\"" << TClock<ISC>(t_found) << "\"\"");
  A_ASSERT(ClockCompare(t, t_found));

  D_COUT(Headingf("Testing invalid input"));
  TSScan<CHA>("cat", t);

  TSScan<CHA>("2017-30-40", t);

  D_COUT("\nDone testing date parsing utils! :-)\n");
#endif
  return nullptr;
}
}  //< namespace Script2
