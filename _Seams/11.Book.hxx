// Copyright Kabuki Starship™ <kabukistarship.com>.
#if SEAM >= SCRIPT2_BOOK
#include "../Book.hpp"
#include "TestWords.h"
#if SEAM == SCRIPT2_BOOK
#include "../_Debug.hxx"
#else
#include "../_Release.hxx"
#endif
using namespace _;
namespace Script2 {

template<typename ISZ = ISN, typename ISY = ISM, typename CHT = CHR,
         typename DT  = DTB>
void TestBook() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    SizeBytes = 512 * sizeof(CHT)
  };

  D_COUT("\n\nTesting ABook<IS" << CSizeCodef<ISZ>() << ",IS" << CSizeCodef<ISY>() << 
         ",CH" << CSizeCodef<CHT>() << ",DT" << CSizeCodef<DT>() << 
         "> sizeof:" << sizeof(TBook<BOK_P>) << " with SizeBytes : " << SizeBytes);

  ABook<BOK_P, SizeBytes> book;

  D_COUT("\n\nAfter TBookInit book.SizeBytes():" << book.SizeBytes() << 
         " book.Count():" << book.Count() << 
         " book.Total():" << book.Total());
  D_COUT("\nPrinting empty book:\n");
  D_COUT_BOOK(book.This());

  ISZ test_word_count = book.Total();
  D_COUT("\nPopulating " << test_word_count << " test words...");

  const CHT * test_words  = TTestWords<CHT>::Words(),
            * word_cursor = test_words;
  ISZ word_step = TTestWords<CHT>::CharsMax;
  D_COUT("\n\nStep 0:\n" << Linef("---") << '\n');

  D_COUT("\n\nStep 1:\n" << Linef("---") << '\n');
  A_AVOW(ISY(1), book.Insert(word_cursor += word_step, ISA('1')));
  D_COUT("\n\nStep 2:\n" << Linef("---") << '\n');
  A_AVOW(ISY(2), book.Insert(word_cursor += word_step, IUA('2')));
  D_COUT("\n\nStep 3:\n" << Linef("---") << '\n');
  A_AVOW(ISY(3), book.Insert(word_cursor += word_step, ISB('3')));
  D_COUT("\n\nStep 4:\n" << Linef("---") << '\n');
  A_AVOW(ISY(4), book.Insert(word_cursor += word_step, IUB('4')));
  D_COUT("\n\nStep 5:\n" << Linef("---") << 
         "\nWill have 1-byte unused space.\n");
  A_AVOW(ISY(5), book.Insert(word_cursor += word_step, ISC('5')));
  D_COUT("\n\nStep 6:\n" << Linef("---") << '\n');
  A_AVOW(ISY(6), book.Insert(word_cursor += word_step, IUC('6')));
  D_COUT("\n\nStep 7:\n" << Linef("---") << '\n');
  A_AVOW(ISY(7), book.Insert(word_cursor += word_step, ISD('7')));
  //book.COut();

  D_COUT("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  D_COUT("\n\nStep 8: Testing Factory.Grow...\n" << Linef("---") << '\n');
   A_AVOW(ISY(8), book.Insert(word_cursor += word_step, IUD('8')));
  //book.COut();
  ISY i = 9;
  D_COUT("\n\nStep 8b: Testing POD types...\n" << Linef("---\n"));
  for (; i < ISY(TTestWords<CHT>::Total) - 8;) {
    A_AVOW(ISY(i++), book.Insert(word_cursor += word_step, ISA(i)));
    A_AVOW(ISY(i++), book.Insert(word_cursor += word_step, IUA(i)));
    A_AVOW(ISY(i++), book.Insert(word_cursor += word_step, ISB(i)));
    A_AVOW(ISY(i++), book.Insert(word_cursor += word_step, IUB(i)));
    A_AVOW(ISY(i++), book.Insert(word_cursor += word_step, ISC(i)));
    A_AVOW(ISY(i++), book.Insert(word_cursor += word_step, IUC(i)));
    A_AVOW(ISY(i++), book.Insert(word_cursor += word_step, ISD(i)));
    A_AVOW(ISY(i++), book.Insert(word_cursor += word_step, IUD(i)));
  }

  D_COUT("\n\nStep 8c Adding large string...:\n" << Linef("---\n"));
  CHT large_string[SizeBytes] = {0};
  CHT* cursor = large_string;
  for (ISN i = 0; i < SizeBytes - 1; ++i) *cursor++ = '*';
  *cursor = 0;
  ISZ index = book.Insert(large_string, 1);
  const TBook<BOK_P>* dez_nutz = book.This();
  D_COUT_BOOK(dez_nutz);
}
}  //< namespace Script2
#undef TPARAMS
#endif

namespace Script2 {
const CHA* Book(const CHA* args) {
#if SEAM >= SCRIPT2_BOOK
  A_TEST_BEGIN;
#if USING_UTF8 == YES_0
  TestBook<ISB, ISA, CHA>();
  TestBook<ISC, ISB, CHA>();
  TestBook<ISD, ISC, CHA>();
#endif
#if USING_UTF16 == YES_0
  TestBook<ISB, ISA, CHB>();
  TestBook<ISC, ISB, CHB>();
  TestBook<ISD, ISC, CHB>();
#endif
#if USING_UTF32 == YES_0
  TestBook<ISB, ISA, CHC>();
  TestBook<ISC, ISB, CHC>();
  TestBook<ISD, ISC, CHC>();
#endif
#endif
  return nullptr;
}
}  //< namespace Script2
