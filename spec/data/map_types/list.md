# [SCRIPT Specification](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

#### List

Lists are stacks of type-value tuples similar in memory layout to Books but they **do not** have keys. Functionally they are identical to B-Sequences expect the offsets are stored as an Array to eliminate the need to scan through the header to calculate the data offset. Sequences are ideal for situations where the fastest possible RW performance is needed.

##### Memory Layout

```AsciiArt
    +--------------------------+
    |_______ Buffer            |
    |_______ Data N            |
    |        Data 0            |
    +--------------------------+
    |_______ Buffer            |
    |_______ Data Offset N     |
    |        Data Offset 1     |
    +--------------------------+
    |_______ Buffer            |
    |_______ Data Type N       |
    |        Data Type 1       |
    +--------------------------+  ^ Up in addresses.
    |       TList Struct       |  |
    +--------------------------+ 0xN
```

#### Memory Overhead

| #Bits | Max # Members | Max Header Size | Max Data Size | Overhead Per Set   |
|:-----:|:-------------:|:---------------:|:-------------:|:------------------:|
|   16  |      255      |     2^16        |       2^16    |   6 + 3 per index. |
|   32  |     2^16 - 1  |     2^32        |       2^32    |   16 + 5 per index.|
|   64  |     2^25 – 1  |     2^32        |       2^64    |   24 + 9 per index.|

* All sizes listed in bytes.

**<< [Previous Section](.md)** | **[Next Section](.md) >>**

## License

Copyright (C) 2014-9 Cale McCollough <http://calemccollough.github.io/>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
