// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_CLOCK
#include "../Clock.hpp"
#include "../RNG.h"
#include "../Uniprinter.hpp"
#if SEAM == CRABS_UUID
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif

using namespace ::_;
namespace CRTest {

static const CHA* UUID(const CHA* args) {
#if SEAM >= CRABS_CLOCK

  D_COUT(Headingf("Testing UUID Generation and Conversion"));

  IUD hot_source_id = GenerateHotSourceID();
  D_COUT("Hot UUID Source ID (28-bit): 0x" << Hexf(hot_source_id));
  D_ASSERT(hot_source_id < (IUD(1) << 28));
  
  IUD Evergreen_source_id = GenerateEvergreenSourceID();
  D_COUT("Evergreen UUID Source ID (34-bit): 0x" << Hexf(Evergreen_source_id));
  D_ASSERT(Evergreen_source_id < (IUD(1) << 34));

  ISC seconds = 1234567;
  ISC ticks = 42;
  IUD source_id = GenerateHotSourceID();
  
  IUD hot_uuid = CreateHotUUID(seconds, ticks, source_id);
  D_COUT("Hot UUID: 0x" << Hexf(hot_uuid));
  
  TMD tmd_hot(hot_uuid);
  D_ASSERT(tmd_hot.IsHotUUID());

  IUD Evergreen_uuid = ConvertHotToEvergreenUUID(hot_uuid, Evergreen_source_id);
  D_COUT("Evergreen UUID: 0x" << Hexf(Evergreen_uuid));
  
  TMD tmd_Evergreen(Evergreen_uuid);
  D_ASSERT(tmd_Evergreen.IsEvergreenUUID());
  D_ASSERT(!tmd_Evergreen.IsHotUUID());

  IUD Evergreen_uuid2 = CreateEvergreenUUID(seconds, Evergreen_source_id);
  TMD tmd_Evergreen2(Evergreen_uuid2);
  D_ASSERT(tmd_Evergreen2.IsEvergreenUUID());

  TMD tmd_test(hot_uuid);
  IUD new_source_id = GenerateEvergreenSourceID();
  tmd_test.ConvertToEvergreenUUID(new_source_id);
  D_ASSERT(tmd_test.IsEvergreenUUID());

  D_COUT(Headingf("UUID Tests Complete! :-)\n"));

#endif
  return NILP;
}

}  
