/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/05.String.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_STRING
#include "../String.hpp"
using namespace _;
#if SEAM == SCRIPT2_STRING
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif

namespace Script2 {
#if SEAM >= SCRIPT2_STRING
template <typename CHT = CHR, typename ISZ = ISN>
void TestStringN() {
  static const CHT cTesting123[] = {'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL};
  enum {
    cStringLoopCount = 3,
    cCharSizeChar = '0' + sizeof(CHT),
  };

  AString<CHT, ISZ, 8> str;
  D_COUT_OBJ(str);
  D_COUT("\nbuffer_size:" << str.Array().Size() << " buffer_size_bytes:"
                          << str.Array().SizeBytes() << " buffer_size_words:"
                          << str.Array().SizeWords());
  D_COUT("\n\nExpecting \""
         << cTesting123 << "\"\n\nThe first print function should fail...\n");

  str << "Testing " << 1 << ", " << 2 << ", " << 3 << '.';
  D_COUT("\n\nResult:\"" << str.Start() << "\"\n");
  A_ASSERT(str.Find(cTesting123));
}
#endif

static const CHA* String(const CHA* args) {
#if SEAM >= SCRIPT2_STRING
  A_TEST_BEGIN;

  TestStringN<CHA, ISC>();
#if USING_UTF16 == YES_0
  TestStringN<CHB, ISC>();
#endif
#if USING_UTF32 == YES_0
  TestStringN<CHC, ISC>();
#endif

#endif
  return nullptr;
}
}  // namespace Script2
