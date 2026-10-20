// Copyright AStarship <https://astarship.net>.
/// Interprocess pipe Chinese Room demo.
///
/// Connects two Chinese Rooms through in-process pipes, replacing the simulated
/// shared-memory ring buffers from 17.Room.hxx with the actual Pipe class
/// implementation from CrabsTK/IPC/. This exercises the full interprocess
/// protocol stack (§13.7, §5 BSQ encoding) over in-process pipes for testing
/// before linking to real OS pipes (Linux: Unix domain sockets, Windows: named pipes).
///
/// Usage: compile and run; expected output: PIPE_ROOM_PASS
///
/// Design:
///   Room A (producer)  -->  Pipe  -->  Room B (consumer)
///   Room B (producer)  -->  Pipe  -->  Room A (consumer)
///
/// The Pipe class uses POSIX shared memory (/crabs_pipe_test) with
/// length-prefixed framing per RPC protocol §1.2-§1.3 and §5 BSQ encoding.
/// The two-room test from 17.Room.hxx is adapted to use Pipe::Master()/Pipe::Slave()
/// instead of TRoom<>* + TBox<>* + BInAttach() ring buffers.
///
/// See also: 15.CrabsOp.hxx (operand testing), 16.CrabsOp.hxx (Crabs machine),
///          17.Room.hxx (two-room ring regression).

#pragma once
#ifndef CRABS_IPC_ROOM_DEMO_H
#define CRABS_IPC_ROOM_DEMO_H

#include "Pipe.h"
#include "_Config.h"
#include "_Debug.h"
#include <cstdio>
#include <cstring>
#include <cerrno>

/// Run the interprocess pipe Chinese Room demo.
/// Connects two rooms through in-process pipes and exercises the full
/// round-trip protocol: write -> transmit -> read -> respond.
/// @return 0 on success, non-zero on failure.
IPC_DEMO_RESULT RunIPCRoomDemo();

/// Result enum for the IPC room demo.
enum IPC_DEMO_RESULT {
  IPC_DEMO_PASS    = 0,  ///< All round-trips succeeded
  IPC_DEMO_FAIL    = 1,  ///< A round-trip or protocol error occurred
  IPC_DEMO_TIMEOUT = 2   ///< Polling / liveness timeout
};

/// Write a BSQ-encoded payload to the pipe's master end.
/// @param pipe  Reference to the Pipe instance (must be Master()).
/// @param payload  Byte array of the payload to send.
/// @param n_bytes  Number of bytes to write.
/// @return Number of bytes written, or negative on error.
IPC_NWRITE_RESULT PipeWriteMaster(Pipe& pipe, const CHA* payload, ISN n_bytes);

/// Read a BSQ-encoded payload from the pipe's slave end.
/// @param pipe  Reference to the Pipe instance (must be Slave()).
/// @param buf  Output buffer for the received payload.
/// @param max_bytes  Maximum bytes to read.
/// @return Number of bytes read, or negative on error.
IPC_NREAD_RESULT PipeReadSlave(Pipe& pipe, CHA* buf, ISN max_bytes);

/// Simple itoa for small non-negative integers into a CHA buffer.
/// @param val  The integer value.
/// @param buf  Output buffer (must be at least 20 CHA).
/// @param buf_size  Size of the output buffer.
static void IPC_itoa(IUC val, CHA* buf, ISN buf_size);

/// Protocol payload size constants, matching the RPC frame BSQ header.
enum IPC_PAYLOAD_SIZES {
  IPC_MIN_PAYLOAD = 1,    ///< Minimum 1-byte payload (single char)
  IPC_INT_PAYLOAD = sizeof(IUC),  ///< 4-byte (or 8-byte on 64-bit) integer
  IPC_STR_PAYLOAD_MAX = 64  ///< Maximum string payload (response buffer size)
};

/// Error codes specific to the IPC room demo.
enum IPC_DEMO_ERRORS {
  IPC_ERR_PIPE_INIT    = -1,  ///< Pipe pair initialization failed
  IPC_ERR_WRITE        = -2,  ///< Write to pipe failed
  IPC_ERR_READ         = -3,  ///< Read from pipe failed
  IPC_ERR_TIMEOUT      = -4,  ///< No data available within polling limit
  IPC_ERR_PROTOCOL     = -5,  ///< BSQ protocol framing error
  IPC_ERR_MISMATCH     = -6,  ///< Round-trip data mismatch
  IPC_ERR_BOOFER_OVER  = -7  ///< Pipe buffer overflow (payload > capacity)
};

#endif // CRABS_IPC_ROOM_DEMO_H