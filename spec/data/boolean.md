# [SCRIPT Specification](../readme.md)

## [ASCII Data Specification](readme.md)

### Boolean

Booleans in Script are stored as 32-bit signed integer types where the deasserted value shall be stored as the number zero and labeled false, and asserted values shall be represented as the number one labeled true or a non-zero integer value.

### Boolean Examples

```C++
// All values less then 127 and greater than -127
BOL true   //< Translates to the number 1
BOL false  //< Translates to the number 0
BOL 0
BOL 1
BOL -129   //< Will require 2 bytes to transceive.
```

**<< [Previous Section](.md)** | **[Next Section](.md) >>**

## License

Copyright (C) 2014-9 Cale McCollough <http://calemccollough.github.io/>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
