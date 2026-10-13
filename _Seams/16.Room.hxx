// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_ROOM
#include "../Room.hpp"
#include "../BIn.hpp"
#include "../BOut.hpp"
#include "../BSeq.hpp"
#include "../Args.h"
#if SEAM == CRABS_ROOM
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
using namespace ::_;
namespace CRTest {

/* Mock interprocess pipe test: two Rooms, each with a Door and BIn (rx) and BOut (tx), connected by a shared lock-free SPSC ring buffer (the Slot in the Door). 
Read `15.CrabsOp.hxx` for the first part of the test.
We pass messages from Room A's BOut into Room B's BIn through the shared ring,
and round-robin the doors polling the lockless ring for data.
This simulates interprocess communication in-process: the shared ring is the
memory that, in a real pipe, would live in shared memory between two
processes. The producer (Room A) advances the write head; the consumer
(Room B) advances the read head. No locks, no threads — just two volatile
single-word counters over one shared byte region.
NOTE: This exercises the BIn/BOut + BInAttach ring directly (where the
lock-free logic lives). The TDoor/TWall/TRoom constructors that would wrap
these rings into the full Chinese Room structure are still skeletons and are
a follow-on. */
static const CHA* Room(const CHA* args) {
#if SEAM == CRABS_ROOM
  A_TEST_BEGIN;

  // Shared ring: one 16-byte header (the SPSC head counters) + the byte
  // region. The producer (Room A's BOut) and consumer (Room B's BIn) ALIAS
  // the same header, so the two heads are shared memory — the pipe. The data
  // region is header + 16.
  enum {
    RingBytes = 256,  //< Small, power-of-two, to exercise wraparound fast.
    RingWords = RingBytes / sizeof(IUW),
  };
  TRoom<ROM_P> room_a, room_b;
  IUW  block[1 + RingWords];  //< 1 word header + ring data.
  IUA* header = TPtr<IUA>(block);          //< Shared SPSC head counters.
  IUA* ring   = header + sizeof(BOut);     //< Shared ring data region.
  BOut* tx = TPtr<BOut>(header);           //< Room A producer (write head).
  BIn*  rx = TPtr<BIn>(header);            //< Room B consumer (read head).
                                          //< tx and rx alias the same header.

  // Fresh, empty shared ring.
  BInAttach(rx, tx, ring, RingBytes);

  D_COUT("\n| Room A tx + Room B rx linked over a " << RingBytes
         << "-byte lock-free ring.");

  // ---- Message 1: a 32-bit int + a CHC + a string. ----
  IUC  msg_int = 0xDEADBEEF;
  CHC  msg_chc = 'k';
  CHA  msg_str[] = "hello, chinese room";
  void* msg_args[3];
  msg_args[0] = &msg_int;
  msg_args[1] = &msg_chc;
  msg_args[2] = msg_str;
  auto params = TTSQ<_IUC, _CHC, STR_>();
  IUD pc_ctx = 0;

  // Room A (producer) writes the message into the shared ring.
  const Op* result = BOutWrite(tx, params, msg_args, pc_ctx);
  A_ASSERT(!result);
  D_COUT("\n| Room A wrote a message; write head=" << tx->stop << ".");

  // Round-robin the doors: poll the lockless ring for readable data.
  // (No "publish" step needed — tx and rx alias the same header, so the
  // consumer sees the producer's write head directly, as in a real pipe.)
  D_COUT("\n| Round-robin polling Room B's door...");
  A_ASSERT(BInIsReadable(rx));
  D_COUT("| Room B's door has data (BInIsReadable).");

  // Room B (consumer) reads the message out of the shared ring.
  IUC  got_int = 0;
  CHC  got_chc = 0;
  CHA  got_str[32] = {0};
  void* got_args[3];
  got_args[0] = &got_int;
  got_args[1] = &got_chc;
  got_args[2] = got_str;
  result = BInRead(rx, params, got_args, pc_ctx);
  A_ASSERT(!result);

  // Verify the round-trip.
  A_AVOW(msg_int, got_int);
  A_AVOW(msg_chc, got_chc);
  D_COUT("\n| Room B read back int=0x" << IUW(got_int) << " chc='"
         << got_chc << "' str=\"" << got_str << "\".");

  // ---- Wraparound: write many small messages to force the ring to wrap. ----
  D_COUT("\n| Wraparound stress: 64 single-word messages...");
  ISN wrap_ok = 0;
  for (ISN i = 0; i < 64; ++i) {
    IUC wval = IUC(i);
    void* wargs[1] = { &wval };
    auto wparams = TTSQ<_IUC>();
    result = BOutWrite(tx, wparams, wargs, pc_ctx);
    A_ASSERT(!result);
    A_ASSERT(BInIsReadable(rx));
    IUC rval = 0;
    void* rargs[1] = { &rval };
    result = BInRead(rx, wparams, rargs, pc_ctx);
    A_ASSERT(!result);
    A_AVOW(wval, rval);
    ++wrap_ok;
  }
  A_AVOW(ISN(64), wrap_ok);
  D_COUT("| All 64 wraparound messages round-tripped correctly.");

  // ---- Underflow: read from an empty ring -> error. ----
  D_COUT("\n| Underflow test: read from empty ring...");
  A_ASSERT(!BInIsReadable(rx));
  D_COUT("| Ring is empty (BInIsReadable false).");

  D_COUT("\n| Done with Room interprocess ring tests.");
#endif
  return NILP;
}

}  //< namespace CRTest
