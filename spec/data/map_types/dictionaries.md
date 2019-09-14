# [SCRIPT Specification](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

#### Dictionaries

Dictionaries are key-type-value sets with a hash table of unique keys. Hash sizes my be 16-bit with up to 120 members, 32-bit with up to 2^24 items, or 64-bit with up to 256 * 10^6 items. Dictionaries have slower insert times than ASCII Books but faster lookup.

##### Dictionary Memory Layout

```AsciiArt
    +--------------------------+
    |          List            |
    |--------------------------|
    |          Table           |
    |--------------------------|  ^ Up in addresses
    |    TDictionary Struct    |  |
    +--------------------------+ 0xN
```

##### Book Memory Overhead

| #Bytes | Index | Offset | Hash  | Total | Overhead Per index |
|:------:|:-----:|:------:|:-----:|:-----:|:-------------------|
|    2   |   1   |    2   |   2   |   8   |  8 + 3  per index + buffer.|
|    4   |   2   |    4   |   4   |   16  | 16 + 4  per index + buffer.|
|    8   |   4   |    8   |   8   |   32  | 24 + 16 per index + buffer.|

* All sizes listed in bytes.

**[<< Previous Section:](./readme.md) | [Next Section: >>](./readme.md)**

## License

Copyright 2014-9 (C) [Cale McCollough](https://calemccollough.github.io); all rights reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
