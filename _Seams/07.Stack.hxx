// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_STACK
#include "../Stack.hpp"
using namespace ::_;
#if SEAM == CRABS_STACK
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
namespace CRTest {

#if SEAM >= CRABS_STACK
template<typename T, typename ISZ, typename ISY=ISZ>
void TestStack(const CHA* args) {
  D_COUT("Testing AStack<T" << CSizeCodef<T>() << ",IS" <<
         CSizeCodef<ISZ>() << ">...\n");

  AStack<T, ISZ, ISZ, 8> stack;

  D_COUT(Linef("\n+---\n| AStack: total:") << stack.Total() << 
         " count:" << stack.Count() << " bytes:" << stack.CBytes() <<
         " size_words:" << stack.SizeWords());
  D_COUT_OBJ(stack);

  enum { TestCount = 32 };
  D_COUT("\n\nPushing " << TestCount << " items on to the Stack...\n");
  T i;
  for (i = 0; i < TestCount; ++i) {
    D_COUT("\n| " << i << ".) count:" << stack.Count() <<
           Linef("\n\n+---\n| ") << i << ".) ");
    auto result = stack.Push('0' + i);
    D_COUT("\n| Result:" << result);
    A_ASSERT(result <= stack.Total());
    D_COUT_OBJ(stack);
    D_AVOW(ISZ(i), result);
  }

  D_COUT(Headingf("\n\nPopping items off the Stack... ") << "i:" << i << 'n');
  #if SEAM == CRABS_STACK
  TStackPrint<::_::COut, SCK_P>(StdOut(), stack.This());
  #endif
  for (i=i-1; i >= 0; --i) {
    D_COUT_OBJ(stack);
    auto value = stack.Pop();
    A_AVOW_INDEX(i, value - '0', i);
    D_COUT("\n| " << i << ".) Popping " << value << " count:" << stack.Count());
  }
  D_COUT("\n\nEnding stack.Count(): " << stack.Count() << " i: " << 
         i << '\n');
  D_COUT_OBJ(stack);
  A_ASSERT(stack.Count() == 0);
}
#endif

static const CHA* Stack(const CHA* args) {
#if SEAM >= CRABS_STACK
  A_TEST_BEGIN;
  D_COUT(Headingf("TestStack"));

  // TestStack<ISC, ISA>(args); //< Illegal!
  TestStack<ISC, ISC>(args);
  TestStack<ISD, ISD>(args);
  TestStack<ISD, ISC>(args);
#endif
  return NILP;
}
}  //< namespace CRTest
