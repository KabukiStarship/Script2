# [SCRIPT Specification](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Vector Types](readme.md)

#### Stack

```C++
template <typename SIZ = SIN>
struct TStack {
  SIZ size,   //< Size of the Array in elements.
      count;  //< Element count.
};
```

##### Array Memory Layout

```AsciiArt
    +---------------+
    |    Buffer     |
    |---------------|
    | C-Style Array |
 ^  |---------------|
 |  |    Header     |
0xN +---------------+
```

**[<< Previous Section:](./readme.md) | [Next Section: >>](./readme.md)**

## License

Copyright 2015-9 © [Kabuki Starship™](https://kabukistarship.com); all rights reserved.

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
