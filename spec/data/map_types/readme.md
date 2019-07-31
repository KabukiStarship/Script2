# [SCRIPT Specification](../readme.md)

## [ASCII Data Specification](readme.md)

### Map Types

ASCII Map Types shall be composed of contiguous memory and begin with an 16, 32 or 64-bit signed integer that specifies the object's size in bytes; this requirement is th need to reduce ROM size. There are 8 standard ASCII OBJ types:

|     Class       |      Type      |
|:---------------:|:--------------:|
|    Object       | User Definable |
|     Stack       |      Stack     |
|     Array       |      Array     |
|   B-Sequence    |     Metadata   |
|    B-Stream     |       Set      |
|      List       |       Set      |
|      Book       |       Set      |
|   Dictionary    |       Set      |
|      Map        |       Set      |

***Caption:*** *Object Type Table*

**<< [Previous Section](.md)** | **[Next Section](.md) >>**

## License

Copyright (C) 2014-9 Cale McCollough <http://calemccollough.github.io/>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
