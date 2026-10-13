# Portals

A Portal connects Room endpoints through Doors and Slots. Its abstract contract
is message/byte transfer between endpoints, not a hardware device, a change to
an automaton's mathematical state set, or a mandatory network stack. See
[Room Contents](RoomContents.md).

## Direct connections and Hallways

Rooms can communicate in memory without an OS or network. An output path from
one Door feeds an input path on another Door. Two directions form a duplex
connection. A shared ring, a bounded copy between rings, or another equivalent
adapter needs an explicit layout and ownership contract; the two endpoints are
not assumed to share type-punned BIn/BOut headers.

A Hallway connects multiple Rooms through a shared communication arrangement.
If it broadcasts messages, each receiver's delivery and capacity behavior must
be specified. The metaphor alone does not define fan-out, scheduling,
backpressure, or synchronization.

## Endpoint and backend contracts

An endpoint/adapter must state its representation, message boundaries, capacity,
ordering, partial-transfer behavior, disconnect behavior, and recovery rules.
Datagram loss or reordering must not accidentally resume an unrelated previous
expression. A streaming adapter must not treat an incomplete argument as a
completed operation.

Examples of backend bindings include UART, SPI, I2C, CAN, Bluetooth, TCP/UDP,
and OS pipes or shared memory. These are examples, not a claim that all are
implemented or officially standardized here. Concrete device access, OS
syscalls, mapping, and interrupt signaling belong in CrabsTK or the host
integration, not the abstract machine.

Do not assume that wiring implies authorization, or that same-system IPC is
trusted or lossless. Authentication is a separate application contract; see
[Authentication](Authentication.md).

## Concurrency and recovery

A single-threaded in-memory round-trip does not prove thread-safe, lock-free,
or interprocess communication. `volatile` counters alone do not establish
atomicity or the memory-ordering contract required by concurrent endpoints.
Producer/consumer ownership and visibility must be specified and verified for
the actual implementation and platform.

There is no generic hardware reset sequence in this core specification.
Do not prescribe UART/DMX timing, SPI chip-select behavior, or repeated NULs as
universal resynchronization. A backend's recovery method must agree with the
scanner and framing contract; see [Abnormal Behaviors](AbnormalBehaviors.md).
