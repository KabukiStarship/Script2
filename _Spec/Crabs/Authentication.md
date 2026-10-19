# Authentication

Authentication may be expressed as application-defined Crabs operations over
Doors and Slots. The abstract machine does not itself define an authentication
wire protocol, credential format, cryptographic algorithm, key exchange, token
lifetime, or replay-prevention scheme.

## Boundary

An application or backend establishes identity and decides which operations
and data a peer may access. Installing or discovering a Door, completing a
transport handshake, and authenticating a peer are different events. Front
Door/Backdoor names, direct wiring, and same-system IPC confer no implicit
permission.

Authentication inputs are typed message data. Parse and bound them under the
normal descriptor/scanner rules, then apply the application's access decision
before invoking protected operations. An authentication failure is not a
successful operation and must not grant access by default.

## Integrity is not authentication

The short hash used by a B-Sequence integrity check can help detect transmission
errors. It does not establish peer identity, secrecy, message authenticity, or
replay protection. A small hash of a shared secret is not a cryptographic
authentication protocol.

## Unspecified integration

The previous fixed token fields and `OPN`/`OPD` example were not backed by an
implemented authentication protocol and are not normative Crabs syntax.
Credential storage, cryptographic choices, key management, expiration,
replay handling, logging, and rate limiting belong to the application's
security design. This page deliberately assigns no replacement token ABI or
mandatory session duration.

A concrete authentication integration needs its own protocol, threat model,
and tests. No security or certification claim follows from the machine's
symbolic Room/Door model. See [Messages](Messages.md) and [Portals](Portals.md).
