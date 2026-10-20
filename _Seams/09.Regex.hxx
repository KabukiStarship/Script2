// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_REGEX
#include "../Regex.hpp"
using namespace ::_;
#if SEAM == CRABS_REGEX
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif

namespace CRTest {

#if SEAM >= CRABS_REGEX
static const CHA* Regex(const CHA* args) {
  A_TEST_BEGIN;
  D_COUT("Testing Regex parser...\n");

  // Test 1: Simple literal
  {
    TRegex regex;
    RegexInit(&regex);
    RegexCompiled* compiled = RegexParse(&regex, "abc");
    A_ASSERT(compiled != NILP);
    A_ASSERT(regex.parser.error == false);
    A_ASSERT(regex.compiled->node_count > 0);
    A_ASSERT(regex.compiled->group_count == 0);
    D_COUT("Test 1 (literal 'abc'): nodes=" << compiled->node_count << " OK\n");
  }

  // Test 2: Dot and literal
  {
    TRegex regex;
    RegexInit(&regex);
    RegexCompiled* compiled = RegexParse(&regex, "a.c");
    A_ASSERT(compiled != NILP);
    A_ASSERT(regex.parser.error == false);
    D_COUT("Test 2 (dot 'a.c'): nodes=" << compiled->node_count << " OK\n");
  }

  // Test 3: Character class
  {
    TRegex regex;
    RegexInit(&regex);
    RegexCompiled* compiled = RegexParse(&regex, "[abc]");
    A_ASSERT(compiled != NILP);
    A_ASSERT(regex.parser.error == false);
    D_COUT("Test 3 (class '[abc]'): nodes=" << compiled->node_count << " OK\n");
  }

  // Test 4: Group
  {
    TRegex regex;
    RegexInit(&regex);
    RegexCompiled* compiled = RegexParse(&regex, "(abc)");
    A_ASSERT(compiled != NILP);
    A_ASSERT(regex.parser.error == false);
    A_ASSERT(regex.compiled->group_count == 1);
    D_COUT("Test 4 (group '(abc)'): nodes=" << compiled->node_count
           << " groups=" << compiled->group_count << " OK\n");
  }

  // Test 5: Alternation
  {
    TRegex regex;
    RegexInit(&regex);
    RegexCompiled* compiled = RegexParse(&regex, "ab|cd");
    A_ASSERT(compiled != NILP);
    A_ASSERT(regex.parser.error == false);
    D_COUT("Test 5 (alt 'ab|cd'): nodes=" << compiled->node_count << " OK\n");
  }

  // Test 6: Invalid pattern (unbalanced group)
  {
    TRegex regex;
    RegexInit(&regex);
    RegexCompiled* compiled = RegexParse(&regex, "(abc");
    A_ASSERT(compiled == NILP);
    A_ASSERT(regex.parser.error == true);
    D_COUT("Test 6 (invalid '(abc'): error=" << regex.parser.error << " OK\n");
  }

  D_COUT("Regex tests complete.\n");
  return NILP;
}
#endif

}  //< namespace CRTest
