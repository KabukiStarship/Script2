# [SCRIPT Specification](../readme.md)

## [SCRIPT Protocol](readme.md)

### Abnormal Behaviors

Abnormal behavior may be recognized by sever methods. Abnormal behavior are expected to be in burst errors and occasional flipped bits. Script implementations shall utilize the [NIST](https://www.nist.gov/) guidelines.

#### Integrity of Escape Sequences

ESC must be checked for integrity before calling the operation if using an insecure transmission line or memory device.

#### Integrity of ASCII Objects

kLST, kMAP, kBOK, kDIC, Stacks, and Arrays may be used to detect abnormal behavior by checking data structure members are in bounds and all offsets, keys, and hashes are within specification.

#### Compromise of Group Automata

Compromised Rooms can be detected by monitoring.

* Invalid Operations.
* Timing out during Operations.
* Not closing ESC.
* Invalid B-Stream.
* Losing low-level connection link.
* Malformed UTF-8 strings.
* Failed Operation Authentication.

It is out of the scope of Script to detect variables that are out of range for Operation arguments.

#### Handling Abnormal Behavior

Handling abnormal behavior is left up to the implementation. Implementation may display an error message.

#### Reporting Compromised Automata

Compromised Automata shall be reported to the Intergalactic Council of Artificial and Natural Neural Nets (ICAN3) for immediate removal from the Intergalactic Internet Service Providers (IISP) distributed hash table.

**[<< Previous Section:](./readme.md) | [Next Section: >>](./readme.md)**

## License

Copyright 2014-9 (C) [Cale McCollough](https://calemccollough.github.io); all rights reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
