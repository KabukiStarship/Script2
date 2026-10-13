# Abnormal Behaviors

Malformed input, corrupted storage, incomplete transmission, capacity exhaustion,
and a failed operation are different conditions. Detect and report the actual
condition; a parser error or lost link alone does not prove that a Room has
been compromised.

## Structural validation

Before exposing arguments to an operation, validate the selected representation:

- Operation identifiers, descriptors, and supported type/context combinations.
- Stream lengths, string bounds and Unicode encoding, nested extents, and any
  integrity field required by that format.
- List/map counts, capacities, value offsets, keys/indexes, and reference bounds.
- Door/Slot ownership and lifetime, including references after removal or growth.
- Expression scopes and available storage for nesting and partial input.

Corruption must not turn an out-of-bounds offset or a low-valued datum into an
operation call. A complete valid frame is required before invoking its operation
with those arguments. Untrusted ESC/control handling must still obey the
scanner, bounds, and applicable access contract.

## Operation arguments and integrity

Structural correctness is the machine's concern. Operation-specific numeric
ranges and semantic invariants belong to the operation contract and must be
checked where that contract requires them; they are not universally out of
scope just because the stream parses.

A checksum/hash is an integrity check, not authentication. Detecting accidental
bit errors does not guarantee secrecy, authorization, or safe application
semantics. See [Authentication](Authentication.md).

## Recovery

An incomplete message can wait for more input under the endpoint's bounded
framing contract. Invalid input requires an explicit error and recovery path.
The endpoint must state whether it cancels the current expression, discards a
frame, resynchronizes, or disconnects. Do not invent a universal byte sequence
or hardware interrupt that repairs every stream.

Cancel, clear, reset, and rollback have different effects. Specify the affected
scope and data lifetimes, keep storage valid on failure, and do not promise
that recovery reverses an already committed operation or external side effect.
Timeouts and retry behavior must be defined by the actual endpoint/operation
contract, not inferred from the office metaphor.

## Diagnostics

Diagnostics should identify the error and its relevant operation, reference,
or stream position without exposing credentials or private message contents.
Presentation, logging, monitoring, and any external registry reporting are
application/backend integrations; this abstract machine specification defines
no automatic authority notification or certification process.

See [Messages](Messages.md), [Portals](Portals.md), and
[Conformance Targets](ConformanceTargets.md).
