# [SCRIPT Specification RFC](../readme.md)

## [Crabs](readme.md)

### Crabs Messages

A **Crabs Message** is similar to an internet datagram and may be enclosed in a IPv4 or IPv6 datagram. A Crabs Message is defined as set of stack operations that start and end with an empty Operand Stack where one or more Operands is pushed, All Unicode Operation indexes being valid, all keys being resolved correctly, and the B-Stream being of a valid length for each B-Sequence argument. Crabs Room Messages may be written in any language using UTF-8. Messages get Unpacked by the Expression Interpreter and translated into the native Unicode format, UTF-8, UTF-16, or UTF-32 for that room and may be compiled directly to a register-based stack machine.

Crabs Messages beginning with a non-printable Unicode Character shall be UI1-encoded with the data immediately following it be a Packed B-Stream. All Crabs Messages beginning in a printable Unicode char shall be Script^2.