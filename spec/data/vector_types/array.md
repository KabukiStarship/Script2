# [SCRIPT Specification](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Vector Types](readme.md)

#### Array

```C++
template <typename SIZ = SI4>
struct TArray {
  SIZ size;  //< Size of the Array in elements.
};
```

##### Memory Layout

```AsciiArt
    +----------------+
    | C-Style Array  |
 ^  |----------------|
 |  |     Header     |
0xN +----------------+
```

**<< [Previous Section](.md)** | **[Next Section](.md) >>**

## License

Copyright (C) 2014-9 Cale McCollough <http://calemccollough.github.io/>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
