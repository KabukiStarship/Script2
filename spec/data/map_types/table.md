# [SCRIPT Specification](../../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [ASCII Data Specification](../readme.md)

### [Map Types]./(readme.md)

#### Table

##### Memory Layout

```AsciiArt
+--------------------------------------+
|_____ | Key 1                         |
|_____ v Key N                Keys     |
+--------------------------------------+
|        Buffer                        |
+--------------------------------------+
|_____   Buffer                        |
|_____ ^ Collision N        Collision  |
|_____ | Collision 0          Pile     |
+--------------------------------------+
|_____   Buffer                        |
|_____ ^ Collision Index N   Unsorted  |
|      | Collision Index 0   Indexes   |
+--------------------------------------+
|_____   Buffer                        |
|_____ ^ Collision Index N  Collision  |
|      | Collision Index 0   Indexes   |
+--------------------------------------+
|_____   Buffer                        |
|_____ ^ Key Offset N          Key     |
|      | Key Offset 1        Offsets   |
+--------------------------------------+
|_____   Buffer                        |
|_____ ^ Sorted Hash N        Hashes   |
|      | Sorted Hash 1                 |
+--------------------------------------+  ^ Up in addresses.
|            TTable Header             |  |
+-------------------------------------+ 0x0
```
