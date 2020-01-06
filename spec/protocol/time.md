# [SCRIPT Specification](../)

## [SCRIPT Protocol](./)

### Time

#### Time Epoch

The Unix timestamp cycles around in the year 3038, so to ensure stability on 32-bit systems with 32-bit kTMS timestamps, the time epoch shall be of the span of a decade, and such systems shall not be made to schedule events beyond a 6 epochs. Systems that require schedulers with more than the maximum number of epochs shall use a 64-bit kTME timestamp.

**[<< Previous Section: Group Automata](./group_automata) | [Next Section: Slots >>](./slots)**

## Requirements

[1] ./

## License

Copyright 2015-9 © [Kabuki Starship™](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
