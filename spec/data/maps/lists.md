# [SCRIPT Specification RFC](../../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

#### List

Lists are stacks of type-value tuples similar in memory layout to Books but they **do not** have keys. Functionally they are identical to B-Sequences expect the offsets are stored as an Array to eliminate the need to scan through the header to calculate the data offset. Sequences are ideal for situations where the fastest possible RW performance is needed.

##### Sequence Memory Layout

```AsciiArt
    +==========================+ -----------
    |_______ Buffer            |   ^     ^
    |_______ ...               |   |     |
    |_______ Data N            |  Data   |
    |_______ ...               |   |     |
    |_______ Data 0            |   v     |
    |==========================| -----   |
    |_______ count_max         |   ^     |
    |_______ ...               |   |     |
    |_______ Data Offset N     |   |     |
    |_______ ...               |   |    Size
    |        Data Offset 1     |   |     |
    |==========================| Header  |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Type byte N       |   |     |
    |_______ ...               |   |     |
    |        Type byte 1       |   |     |   ^ 0x(N+c)+sizeof(AsciiList<UI, SI>)
    |==========================|   |     |   |
    | AsciiList<UI, SI> Struct |   v     v   ^
    +==========================+ ----------- ^ 0xN
```

#### Sequence Memory Overhead

| #Bits | Max # Members | Max Header Size | Max Data Size | Overhead Per Set   |
|:-----:|:-------------:|:---------------:|:-------------:|:------------------:|
|   16  |      255      |     2^16        |       2^16    |   6 + 3 per index. |
|   32  |     2^16 - 1  |     2^32        |       2^32    |   16 + 5 per index.|
|   64  |     2^25 – 1  |     2^32        |       2^64    |   24 + 9 per index.|

* All sizes listed in bytes.