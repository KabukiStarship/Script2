# [SCRIPT Specification](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Vector Types](readme.md)

There are four Vector Types:

1. [Homogenous Vector](./homogeneous_vector.md);
2. [Array](./array.md);
3. [Vector](./vector.md); and
4. [Matrix](./matrix).

Array, Vector, and Matrix types store the element count of the data section as the first word, which is called the SIZ word. The first word means that the element width may be one size and the SIZ word might be another, such as an Array of CH1 with less than 2^15 elements.

```AsciiArt
    +--------------+
    | Data Section |
 ^  |--------------|
 |  |    Header    |
0xN +--------------+
```

This allows the size of the Vector type in bytes to be calculated with the formula:

```C++
template <typename T, typename SIZ, typename Class = TArray<SIZ>>
inline SIW TSizeOf(SIZ size) {
  return (SIW)sizeof(Class) + ((SIW)sizeof(T) * (SIW)size);
}
```

**[<< Previous Section:ASCII Data Types Specification](../readme.md) | [Next Section:Homogeneous Vector >>](./homogeneous_vector.md)**

## License

Copyright 2014-9 (C) [Cale McCollough](https://calemccollough.github.io); all rights reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
