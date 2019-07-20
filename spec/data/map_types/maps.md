# [SCRIPT Specification](../../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

#### Maps

Maps are one-to-one maps of Id-{Type-Value} tuples identical in structure to Lists with the exception that the . are stacks of type-value tuples similar in memory layout to Books but they **do not** have keys. Functionally they are identical to B-Sequences expect the offsets are stored as an Array to eliminate the need to scan through the header to calculate the data offset. Sequences are ideal for situations where the fastest possible RW performance is needed.

##### Memory Layout

```
    +==========================+ -----------
    |_______ Buffer            |   ^     ^
    |_______ ...               |   |     |
    |_______ Data N            |  Data   |
    |_______ ...               |   |     |
    |_______ Data 0            |   v     |
    |==========================| -----   |
    |_______ count_max         |   ^     |
    |_______ ...               |   |     |
    |_______ Sorted Mappings N |   |     |
    |_______ ...               |   |     |
    |        Sorted Mappings 1 |   |     |
    |==========================|   |     |
    |_______ count_max         |   |    Size
    |_______ ...               |   |     |
    |_______ Data Offset N     |   |     |
    |_______ ...               | Header  |
    |        Data Offset 1     |   |     |
    |==========================|   |     |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Type byte N       |   |     |
    |_______ ...               |   |     |
    |        Type byte 1       |   |     |   ^ 0x(N+c)+sizeof(AsciiList<UI, SI>)
    |==========================|   |     |   |
    |  AsciiMap<UI, SI> Struct |   v     v   ^
    +==========================+ ----------- ^ 0xN
```

##### Set C++ Data Structure

```C++
template<typename UI, typename SI, typename I>
struct TMap {
    UI size;       //< ASCII Object size.
    SI table_size, //< Size of the key strings in bytes.
       pile_size;  //< Size of the collisions pile in bytes, or 0 if unused.
    I  item_count, //< Number of items.
       count_max;  //< Max number of items that can fit in the header.
};
```

##### Hash Function

**@warning** *Hash function used may change to use an XOR method*.

All strings are hashed using a prime multiple with the initial value of the largest possible prime that can fit in a 16, 32, or 64-bit size.

##### Hash Function and Overhead

16, 32, and 64-bit hashes all use the same formula. You multiply the current byte by the magic prime (i.e. the largest 16, 32, or 64-bit prime) and add it to the current hash.

##### C Hash Functions

```C++
inline hash16_t Hash16 (char c, hash16_t hash) {
    return cprime + (c * 65521);
}

hash16_t Hash16 (const char* s, hash16_t hash) {
    byte c = *s;
    while (c) {
        hash = Hash16 (c, hash);
        ++s;
        c = *s;
    }
    return hash;
}

inline hash32_t Hash32 (char c, hash32_t hash) {
    hash32_t cprime = c * 4294967291;
    return cprime + hash;
}

hash16_t Hash32 (const char* s, hash32_t hash) {
    byte c = *s;
    while (c) {
        hash = Hash32 (c, hash);
        ++s;
        c = *s;
    }
    return hash;
}

inline hash64_t Hash64 (char c, hash64_t hash) {
    hash64_t cprime = c * 18446744073709551557;
    return cprime + hash;
}

hash64_t Hash64 (const char* s, hash64_t hash) {
    byte c = *s;
    while (c) {
        hash = Hash64 (c, hash);
        ++s;
        c = *s;
    }
    return hash;
}
```
