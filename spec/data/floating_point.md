# [SCRIPT Specification](../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [ASCII Data Specification](readme.md)

### Floating Point

Script supports, 16, 32, 64, and 128-bit floating-point numbers as defined, also called half, float, and double, and quadruple precision float-point numbers, as defined in the IEEE754 specification.

```C++
FP2 0.0     // Use a HLF to save memory and bandwidth!
FP4 0.1     // Wastes a lot of space!
FP8 - 0.1;  // Wastes a whole lot of space!
FPH 1.0     // Wastes a TRUCK TON of space but best for repeated addition.
```
