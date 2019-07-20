# [SCRIPT Specification RFC](../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at [https://mozilla.org/MPL/2.0/](https://mozilla.org/MPL/2.0/).

## [SCRIPT Protocol](readme.md)

### Quality of Service

For all operations that return kNIL, there is no checking to see if a function call made. Quality of Service (QoS) is performed using ESC Evaluation. Each Operation with a return value gets a Unicode Operation Index attached to it, which is then used to throw an error if the return arguments were not received.

## 3.11.a Message Delivery Retry

Each time a data transfer is initiated, a Book with a

### 3.11.b Message Receipt

A Message may have attached to it a return address. If the message is marked as having a

### 3.11.c Message Ordering

Message ordering is performed using a Library and ESC.

### 3.11.d Observed Operations

Some Operations may be observed by a list of Observers. When an Operation is Observed, any time any of the operation is called, the Observer will report it's changed to the broker using an ESC.

## 3.12 Profiles

Profiles are used to group sets of security profiles into understandable categories. The official structure has not been set, but it is current **Low, Medium, High, and Vital Security Levels**.

## 3.12.a Slave Profiles

A slave device assumes that there is another Automaton or Automata performing the security role.

## 3.13 Encryption

Script uses DTLS 3.1 provided by the Script. Please see [https://tools.ietf.org/html/rfc4347](https://tools.ietf.org/html/rfc4347) for details.