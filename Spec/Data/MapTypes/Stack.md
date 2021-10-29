# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types](./)

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

**[<< Previous Section: Array](Array) | [Next Section: Matrix >>](Matrix)**

## Requirements

[1] ./

## License

Copyright 2015-21 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
