/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/05.String.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */

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
template<typename CH = CHR, typename IS = ISR>
void TestStringN() {
  static const CH Testing123[] = {'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL};
  enum {
    StringLoopCount = 3,
    SizeChar = '0' + sizeof(CH),
  };

  AString<CH, IS, 8> str;
  D_COUT_OBJ(str);
  D_COUT("\nboofer_size:" << str.Array().Size() << 
         " total_bytes:" << str.Array().SizeBytes());
  D_COUT("\n\nExpecting \"" << Testing123 << 
         "\"\n\nThe first print function should fail...\n");

  str << "Testing ";
  D_COUT("\n\nWORKS HERE!!!\n\n");
  for (ISN i = 1; i < 256; ++i) str << i << ", ";

  D_COUT("\n\nResult:\"" << str.Start() << "\"\n");
  //A_ASSERT(str.Find(Testing123));
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
}  //< namespace Script2
