# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Vector Types]()

#### Array

```C++
template <typename SIZ = ISC>
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

**[<< Previous Section:Vector Types](./) | [Next Section:Stack >>](./stack)**

## License

Copyright 2015-9 © [Kabuki Starship™](https://kabukistarship.com); all rights reserved.

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
