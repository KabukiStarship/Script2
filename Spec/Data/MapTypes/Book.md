# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types](./)

### Books

ASCII Books are dense ordered maps of key-value tuples. Books differ from ASCII Dictionaries in that multiple values with the same key may be stored. Books use the

#### Book Memory Layout

```AsciiArt
+-----------------+
|      List       |
|-----------------|
|      Loom       |
|-----------------|  ^ Up in addresses
|  TBook Struct   |  |
+-----------------+ 0xN
```

##### Memory Overhead

| #Bytes | I | Index | Size | Total |    Overhead Per index     |
|:------:|:-:|:-----:|:----:|:-----:|:--------------------------|
|    2   | 1 |   2   |   2  |   8   |  8 + 3 per index + socket.|
|    4   | 2 |   4   |   4  |   16  | 16 + 5 per index + socket.|
|    8   | 4 |   8   |   8  |   32  | 24 + 9 per index + socket.|

* Sizes shown in bytes.

**[<< Previous Section: Table](./table) | [Next Section: Dictionary >>](./dictionary)**

## Requirements

[1] ./

## License

Copyright 2015-21 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
