# Messages

A Crabs Message carries operations and their typed arguments between Room
endpoints. It is an abstract expression/message contract, not an IPv4 or IPv6
datagram format. A backend may carry it in datagrams, a serial stream, an OS
pipe, or an in-memory connection. See [Portals](Portals.md).

## Data and expression lifetime

The machine's heterogeneous data stack is the ASCII List. A message may load
type-value tuples, call operations that refer to existing entries, and produce
typed results. Nested map values use the same expression/scanner machinery.

An expression opens and closes operation scopes. Closing its temporary scopes
does not require the persistent List stack to be empty at either message
boundary. Scope metadata and stored data must not be confused. What cancel,
clear, and reset preserve is an explicit operation contract, not an assumption
that all data or side effects are undone.

## B-Sequences and representations

A B-Sequence describes argument types and layout; the B-Stream carries the
argument bytes. [B-Sequences](../Data/BSequences.md) describes the older format
and [Op.h](../../Op.h) declares the current input/output descriptor pointers.
Header and wire-format differences remain to be reconciled with the unified
machine; this page does not redefine descriptor widths or a new packet header.

Text operation indexes and strings use the Unicode encoding required by their
format. Packed binary and word-aligned in-memory representations are distinct.
A receiver must know its representation from the operation and endpoint
contract, not assume that printable/non-printable first bytes alone identify
all message formats. C0 controls inside typed argument data are not instructions.

Native pointers and allocator callbacks are local implementation details, not
portable remote addresses. An operation that refers to a stored tuple or Door
must resolve and validate the agreed reference representation in the receiving
Room. Its exact encoding is still a Data/machine reconciliation item.

## Validation and completion

Validate operation selection, descriptors, lengths, nesting, references, and
any required integrity check before invoking the operation with those
arguments. An incomplete stream is not a completed message. Framing,
continuation after partial input, root-scope entry, and resynchronization must
be specified by the selected endpoint/protocol contract.

Bounded-memory implementations report capacity errors rather than overwrite
storage or silently discard arguments. Results leave through the selected
Door/BOut path. Neither successful message transfer nor a hash check proves
identity, authorization, or reliable delivery. See
[Abnormal Behaviors](AbnormalBehaviors.md) and
[Authentication](Authentication.md).
