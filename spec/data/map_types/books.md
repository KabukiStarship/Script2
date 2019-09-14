# [SCRIPT Specification](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

#### Books

ASCII Books are dense ordered maps of key-value tuples. Books differ from ASCII Dictionaries in that multiple values with the same key may be stored. Books use the

##### Book Memory Layout

```AsciiArt
    +--------------------------+
    |          List            |
    |--------------------------|
    |          Loom            |
    |--------------------------|  ^ Up in addresses
    |       TBook Struct       |  |
    +--------------------------+ 0xN
```

**[<< Previous Section:Table](table.md) | [Next Section:Dictionary >>](dictionary.md)**

## License

Copyright 2014-9 (C) [Cale McCollough](https://calemccollough.github.io); all rights reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
