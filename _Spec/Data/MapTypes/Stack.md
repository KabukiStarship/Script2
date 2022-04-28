# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types](./)

#### Stack

```C++
template <typename ISZ = ISN>
struct TStack {
  ISZ count_max,  //< Size of the Array in elements.
      count;      //< Element count.
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

**[<< Previous Section: Array](Array.md) | [Next Section: Matrix >>](Matrix.md)**

## Requirements

[1] ./

## License

Copyright 2015-22 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
