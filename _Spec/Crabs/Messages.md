# [SCRIPT Specification](../)

## [Crabs Specification](./)

### Messages

A **Crabs Message** is similar to an internet datagram and may be enclosed in a IPv4 or IPv6 datagram. A Crabs Message is defined as set of stack operations that start and end with an empty Operand Stack where one or more Operands is pushed, All Unicode Operation indexes being valid, all keys being resolved correctly, and the B-Stream being of a valid length for each B-Sequence argument. Crabs Room Messages may be written in any language using UTF-8. Messages get Unpacked by the Expression Interpreter and translated into the native Unicode format, UTF-8, UTF-16, or UTF-32 for that room and may be compiled directly to a register-based stack machine.

Crabs Messages beginning with a non-printable Unicode Character shall be IUA-encoded with the data immediately following it be a Packed B-Stream. All Crabs Messages beginning in a printable Unicode char shall be Script^2.

**[<< Previous Section: Autojects](./Autojects.md) | [Next Section: Expression Mappings >>](./ExpressionMappings.md)**

## Requirements

[1] ./

## License

Copyright [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
