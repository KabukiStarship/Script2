# ASCII List Chinese Room

## Unified machine

The Crabs machine's data stack is the ASCII List: a heterogeneous stack of
ASCII type-value tuples. This is not a List beside a separately implemented
Crabs Machine. Storage, scanning, nested map interpretation, and operations
that refer to stored data are parts of the same design.

This unification removes the duplicated List/machine paths that made scanner
upgrades difficult. A scalar, string, or nested map is typed data on the List
stack. An operation resolves its arguments against that data and acts on it.
An implementation may keep scope, header, and scanner-state metadata, but
that does not create a second heterogeneous data stack.

The Chinese Room name retains the pen-and-paper office metaphor: a person or
agent follows operations over symbols, using the Room's memory and Doors.
The metaphor does not assign extra modules or prove implementation properties.

## Type words and C0 controls

The design uses a 16-bit ASCII Data Type word with 12-bit inline unsigned-
character values and 12-bit inline signed-integer values. An inline value
lives in the type word rather than a separate value payload. Other types have
a value representation determined by their descriptor and context.

ASCII C0 codes are reused to run Crabs expressions. The scanner must distinguish
an expression control from data using the full type/stream context, not just a
small numeric value. A character containing ESC, or an integer equal to a C0
code, is still data when presented as an argument.

**Encoding is not yet reconciled.** [Data Types](../Data/Types.md) and
[Numbers](../Data/Numbers.md) still describe older 13-bit void-value forms.
[_ConfigHeader.h](../../_ConfigHeader.h) currently places `ATypeMDBit0` at 13,
uses the two-bit `ATypeMDMask = 0x6000`, and has a separate const bit at 15.
Those facts do not establish tags for the clarified 12-bit forms. This page
assigns neither new modifier values nor a control-word prefix.

## Room, Wall, and Floor

A Room owns its abstract machine state and exposes its operation and
communication contract through Doors. Its interior is not part of a remote
client's memory layout; native implementation and tests may inspect it.

A Wall is one contiguous, word-aligned block of backing memory. A Room starts
with one Wall. The minimum Room fits its List stack, required interpreter
metadata, and Door/Slot storage in fixed memory without allocating a heap.

The Floor is a Wall: the initial fixed backing memory used by the
no-dynamic-memory Room. It is not a separate module, type code, initial-state
pair, or additional stack. Resetting an expression is not a Floor operation.

Dynamic memory is optional. If enabled, storage may grow through an Autoject
and RAMFactory, or the Room may acquire additional Walls. Each Wall remains
contiguous; multiple Walls need not be adjacent. If disabled, exhausted
capacity returns an error rather than silently enabling allocation.

The allocator and owner govern lifetime. A relocated Wall invalidates raw
addresses into its old block. Door, Slot, and data references must be rebound
or validated according to their representation before use. See
[Autojects](Autojects.md).

## Door and Slot boundary

A Door is the Room's addressable MAP-type interface, installed in a Wall. Its
operations expose entry points and one or more Slots for communication. Door
access belongs on the List stack as typed data or a typed reference to the
installed Door; this does not prescribe a numeric type tag or reference ABI.

BIn and BOut are the input/output ring-buffer machinery associated with Slots.
They are not automatically separate user operands merely because a Door uses
them. A Door is not defined as a type-punned BIn/BOut header pair.

Conceptually:

```text
Room A                                  Room B
  fixed Wall                              fixed Wall
    List stack <-> expressions              expressions <-> List stack
                   |                        |
                  Door                     Door
                   |                        ^
                  BOut ---- Portal -------> BIn
```

The arrows describe byte flow, not an object layout or concurrency guarantee.
A reverse direction uses an output/input path in the other direction.

A Portal connects Room endpoints through Doors and Slots. Direct in-memory
connections are core abstractions. TCP, serial hardware, OS pipes, shared-memory
mapping, and device interrupts are backend concerns. Mirror and Window refer
to in-memory one-way and duplex communication arrangements; they do not make
an OS-specific IPC mechanism mandatory. See [Room Contents](RoomContents.md)
and [Portals](Portals.md).

## Expressions and persistent data

Operations may read or modify existing List entries without retransmitting
their values. Nested map types require the Crabs expression/scanner machinery,
not a standalone POD-only decoder. Expression closure returns to the enclosing
scope; it does not require all persistent List entries to disappear.

The operation/header/state machinery and List data have distinct lifetimes.
Cancel, clear, reset, and rollback must specify which state they affect. A
reset is not a mathematical identity or a general inverse of a side effect.
This specification does not promise automatic reversal of external actions.
See [Messages](Messages.md) and [Expression Mappings](ExpressionMappings.md).

## Implementation status

The checked-in C++ still contains both the intended unification and legacy
paths. Source declarations and constructor calls alone are not integration
or runtime conformance evidence.

- [CrabsList.h](../../CrabsList.h) declares `CrabList` around `TList` and states
  that the machine is a List. [CrabsList.hpp](../../CrabsList.hpp) supplies
  wrapper operations, but the current machine and package do not import it.
- [Crabs.h](../../Crabs.h) and [Crabs.hxx](../../Crabs.hxx) still implement the
  older `Operand*` scope stack and scanner. `CrabsReset` is currently a stub.
- [_Seams/15.CrabsOp.hxx](../../_Seams/15.CrabsOp.hxx) is the investigation entry
  point: it initializes a real machine with its BIn/BOut and calls
  `CrabsScanBIn`. Its isolated ring regressions are useful but do not prove
  unified List or nested-map integration.
- [_Seams/16.Room.hxx](../../_Seams/16.Room.hxx) now constructs two `TRoom`
  objects. The message test still operates on a separate raw ring, not Doors
  installed in those Rooms. That single-threaded test is not proof of
  interprocess or lock-free communication.
- [Room.hpp](../../Room.hpp), [Wall.hpp](../../Wall.hpp), and
  [Door.hpp](../../Door.hpp) contain incomplete construction, storage, and
  dispatch paths. Their remaining Floor names do not define another module.

## Remaining decisions and cross-directory reconciliation

The architectural choices above are settled. The remaining work is concrete:

1. Reconcile the 12-bit inline forms and C0/data distinction with
   [Data Types](../Data/Types.md), [Numbers](../Data/Numbers.md), and the scanner
   before changing bit assignments or the wire format.
2. Specify Door value/reference representation, ownership, invalidation, and
   the fixed-Wall partition and installation API. Do not invent those from
   an empty constructor or the office metaphor.
3. Define which persistent data and installed Doors survive cancel, clear,
   and reset, and test each behavior against the unified machine.
4. Reconcile [Protocol Slots](../Protocol/Slots.md) with the actual Slot,
   BIn, and BOut structures. Its old examples and 64-bit endpoint alignment
   requirement must not be mistaken for an agreed portable ABI.
5. Update [Chinese Room Objects](../Overview/ChineseRoomObjects.md), which
   still lists Floor as a separate class, and the
   [specification index](../README.md), which links the deleted mathematical
   draft. [Socket](../Data/MapTypes/Socket.md) still repeats the stale Door
   alternatives and Slot-layout authority claim.
6. Reconcile [Protocol Expressions](../Protocol/Expressions.md) with the
   unified List data lifetime, current operation headers, and root C0 hooks.
   Its old reset/theorem language is not conformance evidence.
7. Remove the stale deleted-module include from
   [_Package.hxx](../../_Package.hxx) before a full package build; this
   documentation edit does not modify that C++ roll-up.
