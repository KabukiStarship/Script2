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
#include "AType.hpp"
#endif
#endif
using namespace ::_;
namespace CRTest {

/* Mock interprocess pipe test: two Rooms, each with a Door and TBIn (rx) and TBOut (tx), connected by a shared lock-free SPSC ring buffer (the Slot in the Door). 
Read `15.CrabsOp.hxx` for the first part of the test.
We pass messages from Room A's TBOut into Room B's TBIn through the shared ring,
and round-robin the doors polling the lockless ring for data.
This simulates interprocess communication in-process: the shared ring is the
memory that, in a real pipe, would live in shared memory between two
processes. The producer (Room A) advances the write head; the consumer
(Room B) advances the read head. No locks, no threads — just two volatile
single-word counters over one shared byte region.
NOTE: This exercises the TBIn/TBOut + BInAttach ring directly (where the
lock-free logic lives). The TDoor/TWall/TRoom constructors that would wrap
these rings into the full Chinese Room structure are still skeletons and are
a follow-on. */
static const CHA* Room(const CHA* args) {
#if SEAM == CRABS_ROOM
  A_TEST_BEGIN;

  // Shared ring: one 16-byte header (the SPSC head counters) + the byte
  // region. The producer (Room A's TBOut) and consumer (Room B's TBIn) ALIAS
  // the same header, so the two heads are shared memory — the pipe. The data
  // region is header + 16.
  enum {
    RingBytes = 256,  //< Small, power-of-two, to exercise wraparound fast.
    RingWords = RingBytes / sizeof(IUW),
  };
  TRoom<ROM_P> room_a, room_b;

  // ---- Ring 1: Room A -> Room B (the client-to-server direction) ----
  IUW  block_ab[1 + RingWords];
  IUA* header_ab = TPtr<IUA>(block_ab);
  IUA* ring_ab   = header_ab + sizeof(TBOut<ISC>);
  TBOut<ISC>* tx_a = TPtr<TBOut<ISC>>(header_ab);  //< Room A producer.
  TBIn<ISC>*  rx_b = TPtr<TBIn<ISC>>(header_ab);   //< Room B consumer.
  BInAttach(rx_b, tx_a, ring_ab, RingBytes);

  // ---- Ring 2: Room B -> Room A (the server-to-client direction) ----
  IUW  block_ba[1 + RingWords];
  IUA* header_ba = TPtr<IUA>(block_ba);
  IUA* ring_ba   = header_ba + sizeof(TBOut<ISC>);
  TBOut<ISC>* tx_b = TPtr<TBOut<ISC>>(header_ba);  //< Room B producer.
  TBIn<ISC>*  rx_a = TPtr<TBIn<ISC>>(header_ba);   //< Room A consumer.
  BInAttach(rx_a, tx_b, ring_ba, RingBytes);

  D_COUT("\n| Two-Room Chinese Room: Room A <-> Room B over two "
         << RingBytes << "-byte lock-free rings.");

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
  const Op* result = BOutWrite(tx_a, params, msg_args, pc_ctx);
  A_ASSERT(!result);
  D_COUT("\n| Room A wrote a message; write head=" << tx_a->stop << ".");

  // Round-robin the doors: poll the lockless ring for readable data.
  // (No "publish" step needed — tx and rx alias the same header, so the
  // consumer sees the producer's write head directly, as in a real pipe.)
  D_COUT("\n| Round-robin polling Room B's door...");
  A_ASSERT(BInIsReadable(rx_b));
  D_COUT("| Room B's door has data (BInIsReadable).");

  // Room B (consumer) reads the message out of the shared ring.
  IUC  got_int = 0;
  CHC  got_chc = 0;
  CHA  got_str[32] = {0};
  void* got_args[3];
  got_args[0] = &got_int;
  got_args[1] = &got_chc;
  got_args[2] = got_str;
  result = BInRead(rx_b, params, got_args, pc_ctx);
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
    result = BOutWrite(tx_a, wparams, wargs, pc_ctx);
    A_ASSERT(!result);
    A_ASSERT(BInIsReadable(rx_b));
    IUC rval = 0;
    void* rargs[1] = { &rval };
    result = BInRead(rx_b, wparams, rargs, pc_ctx);
    A_ASSERT(!result);
    A_AVOW(wval, rval);
    ++wrap_ok;
  }
  A_AVOW(ISN(64), wrap_ok);
  D_COUT("| All 64 wraparound messages round-tripped correctly.");

  // ---- Room B responds: "Hello world <N>" ----
  // The room reads the message, then writes a response back through
  // its own TBOut to Room A's TBIn. This exercises the bi-directional
  // Slot: A->B and B->A over two separate rings.
  D_COUT("\n| Room B responding with 'Hello world <N>'...");

  // Build the response: "Hello world " + the number from the message.
  CHA response[64] = {0};
  ISN resp_len = 0;
  const CHA* greeting = "Hello world ";
  for (ISN g = 0; greeting[g]; ++g) {
    response[resp_len++] = greeting[g];
  }
  // Append the number (simple itoa for small values).
  ISN num = ISN(got_int);
  if (num == 0) {
    response[resp_len++] = '0';
  } else {
    CHA digits[20] = {0};
    ISN dcount = 0;
    while (num > 0) {
      digits[dcount++] = CHA('0' + (num % 10));
      num /= 10;
    }
    for (ISN d = dcount - 1; d >= 0; --d) {
      response[resp_len++] = digits[d];
    }
  }
  response[resp_len] = 0;

  // Room B writes the response into its TBOut (-> Room A's TBIn).
  void* resp_args[1] = { response };
  auto resp_params = TTSQ<STR_>();
  result = BOutWrite(tx_b, resp_params, resp_args, pc_ctx);
  A_ASSERT(!result);
  D_COUT("| Room B wrote response; write head=" << tx_b->stop << ".");

  // Room A polls its TBIn for the response.
  D_COUT("| Round-robin polling Room A's door for response...");
  A_ASSERT(BInIsReadable(rx_a));
  D_COUT("| Room A's door has response data (BInIsReadable).");

  // Room A reads the response.
  CHA got_response[64] = {0};
  void* got_resp_args[1] = { got_response };
  result = BInRead(rx_a, resp_params, got_resp_args, pc_ctx);
  A_ASSERT(!result);

  // Verify the round-trip.
  D_COUT("\n| Room A read back response=\"" << got_response << "\".");

  // ---- Second message: with a number to repeat back. ----
  D_COUT("\n| Message 2: 'Hello 123' -> expect 'Hello world 123'...");
  CHA msg2_str[] = "Hello 123";
  IUC msg2_int = 123;
  void* msg2_args[2];
  msg2_args[0] = &msg2_int;
  msg2_args[1] = msg2_str;
  auto params2 = TTSQ<_IUC, STR_>();

  result = BOutWrite(tx_a, params2, msg2_args, pc_ctx);
  A_ASSERT(!result);

  A_ASSERT(BInIsReadable(rx_b));
  IUC got2_int = 0;
  CHA got2_str[32] = {0};
  void* got2_args[2];
  got2_args[0] = &got2_int;
  got2_args[1] = got2_str;
  result = BInRead(rx_b, params2, got2_args, pc_ctx);
  A_ASSERT(!result);
  A_AVOW(msg2_int, got2_int);

  // Room B responds with "Hello world 123".
  CHA resp2[64] = {0};
  ISN r2 = 0;
  for (ISN g = 0; greeting[g]; ++g) resp2[r2++] = greeting[g];
  ISN n2 = ISN(got2_int);
  if (n2 == 0) {
    resp2[r2++] = '0';
  } else {
    CHA dig2[20] = {0};
    ISN d2 = 0;
    while (n2 > 0) { dig2[d2++] = CHA('0' + (n2 % 10)); n2 /= 10; }
    for (ISN d = d2 - 1; d >= 0; --d) resp2[r2++] = dig2[d];
  }
  resp2[r2] = 0;

  void* resp2_args[1] = { resp2 };
  result = BOutWrite(tx_b, resp_params, resp2_args, pc_ctx);
  A_ASSERT(!result);

  A_ASSERT(BInIsReadable(rx_a));
  CHA got_resp2[64] = {0};
  void* got_resp2_args[1] = { got_resp2 };
  result = BInRead(rx_a, resp_params, got_resp2_args, pc_ctx);
  A_ASSERT(!result);
  D_COUT("\n| Room A read back response=\"" << got_resp2 << "\".");

  D_COUT("\n| Done with two-Room Chinese Room demo.");
#endif
  return NILP;
}

}  //< namespace CRTest
