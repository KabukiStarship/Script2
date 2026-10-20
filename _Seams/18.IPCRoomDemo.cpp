// Copyright AStarship <https://astarship.net>.
#include "IPCRoomDemo.h"
#include "_Config.h"
#include "_Debug.h"
#include <cstring>
#include <chrono>
#include <thread>

// ------------------------------------------------------------------
// IPC_itoa: simple integer to string conversion
// ------------------------------------------------------------------
void IPC_itoa(IUC val, CHA* buf, ISN buf_size) {
  if (buf == nullptr || buf_size < 2) {
    return;
  }
  if (val == 0) {
    if (buf_size > 0) buf[0] = '0';
    return;
  }
  ISN dcount = 0;
  UC tmp = (UC)val;  // we only need unsigned digits
  while (tmp > 0) {
    buf[dcount++] = CHA('0' + (tmp % 10));
    tmp /= 10;
    if (dcount >= buf_size) break;
  }
  // Reverse the digits
  ISN start = 0;
  ISN end = dcount - 1;
  while (start < end) {
    CHA tmp_ch = buf[start];
    buf[start] = buf[end];
    buf[end] = tmp_ch;
    ++start;
    --end;
  }
  buf[dcount] = '\0';
}

// ------------------------------------------------------------------
// PipeWriteMaster: write to the master (producer) end of the pipe
// ------------------------------------------------------------------
IPC_NWRITE_RESULT PipeWriteMaster(Pipe& pipe, const CHA* payload, ISN n_bytes) {
  if (!pipe) return IPC_ERR_PIPE_INIT;
  ISN written = pipe.Write(payload, n_bytes);
  if (written < 0) return IPC_ERR_WRITE;
  if (written < n_bytes) return IPC_ERR_PROTOCOL;  // partial write
  return (IPC_NWRITE_RESULT)written;
}

// ------------------------------------------------------------------
// PipeReadSlave: read from the slave (consumer) end of the pipe
// ------------------------------------------------------------------
IPC_NREAD_RESULT PipeReadSlave(Pipe& pipe, CHA* buf, ISN max_bytes) {
  if (!pipe) return IPC_ERR_PIPE_INIT;
  if (buf == nullptr || max_bytes <= 0) return IPC_ERR_READ;

  // Poll with timeout (simple iteration limit)
  ISN attempts = 0;
  ISN max_attempts = ISN(100);  // ~100 polls at ~10us each = 1ms total

  while (attempts < max_attempts) {
    if (pipe.HasData()) break;
    ++attempts;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  if (attempts >= max_attempts) return IPC_ERR_TIMEOUT;

  ISN read = pipe.Read(buf, max_bytes);
  if (read < 0) return IPC_ERR_READ;
  if (read == 0) return IPC_ERR_TIMEOUT;  // polled but nothing came

  return (IPC_NREAD_RESULT)read;
}

// ------------------------------------------------------------------
// RunIPCRoomDemo: the full two-room interprocess demo
// ------------------------------------------------------------------
IPC_DEMO_RESULT RunIPCRoomDemo() {
  printf("=== Interprocess Pipe Chinese Room Demo ===\n");

  // Create pipe pair (shared memory between two "rooms")
  Pipe& pipe_master = Pipe::Master();
  Pipe& pipe_slave = Pipe::Slave();

  if (!pipe_master || !pipe_slave) {
    printf("FAIL: Could not create pipe pair\n");
    return IPC_DEMO_FAIL;
  }
  printf("PASS: Pipe pair created (shared memory)\n");

  // --- Room A (producer) writes a message into the pipe ---
  const CHA* msg_from_a = "Hello from Room A";
  ISN msg_a_len = ISN(strlen(msg_from_a));
  printf("Room A writing: '%s' (%d bytes)\n", msg_from_a, msg_a_len);

  IPC_NWRITE_RESULT write_result = PipeWriteMaster(pipe_master, msg_from_a, msg_a_len);
  if (write_result < 0) {
    printf("FAIL: PipeWriteMaster returned error (%d)\n", write_result);
    return IPC_DEMO_FAIL;
  }
  printf("PASS: Room A wrote %d bytes to pipe\n", write_result);

  // --- Room B (consumer) reads from the pipe ---
  CHA read_buf[IPC_STR_PAYLOAD_MAX] = {0};
  IPC_NREAD_RESULT read_result = PipeReadSlave(pipe_slave, read_buf, IPC_STR_PAYLOAD_MAX);
  if (read_result < 0) {
    printf("FAIL: PipeReadSlave returned error (%d)\n", read_result);
    return IPC_DEMO_FAIL;
  }
  if (read_result == IPC_ERR_TIMEOUT) {
    printf("FAIL: PipeReadSlave timed out (no data)\n");
    return IPC_DEMO_FAIL;
  }
  printf("PASS: Room B read %d bytes from pipe\n", read_result);

  // Verify the round-trip
  if (strcmp(read_buf, msg_from_a) != 0) {
    printf("FAIL: Data mismatch!\n");
    printf("  Expected: '%s'\n", msg_from_a);
    printf("  Got:      '%s'\n", read_buf);
    return IPC_DEMO_MISMATCH;
  }
  printf("PASS: Round-trip data matches: '%s'\n", read_buf);

  // --- Room B (producer) writes a response back ---
  const CHA* greeting = "Hello world";
  IUC replied_int = 0xBEEFDEAD;  // arbitrary payload
  CHA resp_buf[IPC_STR_PAYLOAD_MAX] = {0};

  // Build response: "Hello world <int>"
  ISN resp_len = 0;
  for (ISN g = 0; greeting[g]; ++g) resp_buf[resp_len++] = greeting[g];

  // Append the integer
  IPC_itoa(replied_int, resp_buf + resp_len, IPC_STR_PAYLOAD_MAX - resp_len);
  resp_len = ISN(strlen(resp_buf));  // recompute length after itoa

  printf("Room B writing response: '%s' (%d bytes)\n", resp_buf, resp_len);

  write_result = PipeWriteMaster(pipe_master, resp_buf, resp_len);
  if (write_result < 0) {
    printf("FAIL: PipeWriteMaster (response) returned error (%d)\n", write_result);
    return IPC_DEMO_FAIL;
  }
  printf("PASS: Room B wrote response %d bytes to pipe\n", write_result);

  // --- Room A (consumer) reads the response ---
  CHA resp_read_buf[IPC_STR_PAYLOAD_MAX] = {0};
  IPC_NREAD_RESULT resp_read_result = PipeReadSlave(pipe_slave, resp_read_buf, IPC_STR_PAYLOAD_MAX);
  if (resp_read_result < 0) {
    printf("FAIL: PipeReadSlave (response) returned error (%d)\n", resp_read_result);
    return IPC_DEMO_FAIL;
  }
  if (resp_read_result == IPC_ERR_TIMEOUT) {
    printf("FAIL: PipeReadSlave (response) timed out\n");
    return IPC_DEMO_FAIL;
  }
  printf("PASS: Room A read %d bytes response\n", resp_read_result);

  // Verify the second round-trip
  if (strcmp(resp_read_buf, resp_buf) != 0) {
    printf("FAIL: Second round-trip mismatch!\n");
    printf("  Expected: '%s'\n", resp_buf);
    printf("  Got:      '%s'\n", resp_read_buf);
    return IPC_DEMO_MISMATCH;
  }
  printf("PASS: Second round-trip data matches: '%s'\n", resp_read_buf);

  printf("\n=== IPC Chinese Room Demo: ALL TESTS PASSED ===\n");
  return IPC_DEMO_PASS;
}

// ------------------------------------------------------------------
// (PipePair declaration kept for reference; actual pipe is singletons)
// ------------------------------------------------------------------
