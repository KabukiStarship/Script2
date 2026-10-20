// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_FILE
#include "../File.h"
#if SEAM == CRABS_FILE
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
using namespace ::_;
namespace CRTest {

static const CHA* File(const CHA* args) {
#if SEAM >= CRABS_FILE
  A_TEST_BEGIN;

  static const CHR* TestURI = "_Seams/Test.crabs";

  ::_::File file(TestURI);

  D_COUT("\nTesting File(\"" << TestURI << "\")");

  A_AVOW(TestURI, file.URI());

  A_ASSERT(file.Exists());

  A_ASSERT(!file.IsOpen());

  A_AVOW(ISN(0), file.Open(TestURI));

  A_ASSERT(file.IsOpen());

  D_({
    
  })

  file.Close();

  A_ASSERT(!file.IsOpen());

  D_COUT("\nFile test complete.");
#endif
  return NILP;
}

}  //< namespace CRTest
