# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types](./)

#### Table

The Table is a string-to-unsorted-index map with a hash table. The acronym for a Table is a TBL.

##### Memory Layout

The memory layout shall be optimized by need to minimize lookup time, which starts with a binary search of the hash table. The second

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
+--------------------------------------+ 0x0
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
    while © {
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
    while © {
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
    while © {
        hash = Hash64 (c, hash);
        ++s;
        c = *s;
    }
    return hash;
}
```

**[<< Previous Section:Map](map) | [Next Section:Book >>](book)**

## License

Copyright 2015-9 © [Kabuki Starship™](https://kabukistarship.com); all rights reserved.

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
