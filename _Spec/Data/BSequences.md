# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Objects]()

#### B-Sequences

B-Sequences, as in the B in `A*B`, is a data structure that describes byte sequences using the 32 ASCII Data Types. B-Sequences are composed of a header that defines the data and the actual byte stream itself. B-Sequences are similar *scanf* and *printf* format strings only you just use the % format tokens). B-Sequences are the ideal solution for serializing almost any type of data to save and load from drives, networks or any serial data stream. They are very easy to earn and nearly impossible to forget.

##### B-Sequence Headers

There are 5 classes of types of B-Sequence parameters: types with a fixed POD sizes, types with length specified at ahead of time, _::TStrand<> types that must be less than a given number of characters known ahead of time, Array types of the POD types excluding strings, and object types whose size is not known at compile time. **B-Sequences Headers** must be an array of unsigned integer types that use a single element to represent a single type (which is 8-bit).

###### POD and Object Headers

```AsciiArt
{ n, p_1, ,..., p_n }
```

###### String Headers

```AsciiArt
{ n + 1, STR, max_num_bytes, p_1, ..., p_n }
```

###### Array Headers

```AsciiArt
{ n + 1, ARx, cr_data_type, num_items, p_1, ..., p_n }
```

###### B-Sequence Header

```AsciiArt
{ num_params, p_1,..., p_n }
```

####### B-Sequence Header Example

```Script2
/*      +--------------- 4 input parameters
        |   +----------- A _::TStrand<> of max length 31.
        |   |       +--- A signed integer with 1-byte (8-bit) width.
        |   |       |
        |   |       |               +-- There are 0 return parameters.
        |   |       |               |
        v   v       v               v */
   Foo <4, STR:32, ISA, ISB, ISC>:<NIL>
   Bar <1, STR:32>:<3, ISA, ISB, ISC>
   FooBar <DIC, IUD>:<NIL>
/*          ^     ^
            |     |
            |     +----- An 16-bit unsigned integer.
            +----------- A 32-bit dictionary. _2, _4, and _8 may be used with any
                         ASCII Object Data Type for 16, 32, and 64-bit types. DIC4
                         may also make a rather funny or inappropriate joke when put
                         on coworkers foreheads. :-) */
```

**[<< Previous Section: Strings](Strings.md) | [Next Section: Homo-tuples >>](HomoTuples.md)**

## Requirements

[1] ./

## License

Copyright [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
