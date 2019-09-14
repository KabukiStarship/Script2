# [SCRIPT Specification](../readme.md)

## [ASCII Data Specification](readme.md)

### Data Types

Data Types can be represented using 1-byte, or two 2-byte such that 1-byte Data Types are forward compatible with 2-byte Types. Given there are only 8, 16, 32, and 64-bit CPUs, the bit pattern of the data type is required to be laid out such that the bit_1 of the 4 bits required to represent these 4 byte depths shall be laid out across the boundary between a UI1 and UI2 type[].

#### POD Types Table

The POD Types table is laid out such that the types are grouped into groups by width growing from NIL to the 16-byte types, and beyond the 16-byte types shall be CPU word-aligned POD types that shall be defined by the target implementation[10].

| ID | Type | C++/Alt Name | Width | Description |
|:--:|:----:|:------------:|:-----:|:------------|
|  0 | NIL  |     null     |   0   | Nil/null/void type. |
|  1 | CH1  |     char     |   1   | 1-byte Unicode/ASCII character. |
|  2 | SI1  |     int8_t   |   1   | 1-byte signed integer. |
|  3 | UI1  |    uint8_t   |   1   | 1-byte unsigned integer. |
|  4 | CH2  |   char16_t   |   2   | 2-byte Unicode character. |
|  5 | SI2  |    int16_t   |   2   | 2-byte signed integer. |
|  6 | UI2  |   uint16_t   |   2   | 2-byte unsigned integer. |
|  7 | FP2  |     half     |   2   | 2-byte floating-point number. |
|  8 | BOL  |     bool     |  2/4  | 2 or 4-byte boolean value. |
|  9 | CH4  |   char32_t   |   4   | 4-byte Unicode character. |
| 10 | SI4  |    int32_t   |   4   | 4-byte signed varint. |
| 11 | UI4  |   uint32_t   |   4   | 4-byte unsigned integer. |
| 12 | FP4  |    float     |   4   | 4-byte floating-point number. |
| 13 | TME  |    int64_t   |   8   | SI4 seconds since epoch timestamp with a UI4 sub-second tick. |
| 14 | SI8  |    int64_t   |   8   | 8-byte signed integer. |
| 15 | UI8  |   uint64_t   |   8   | 8-byte unsigned integer. |
| 16 | FP8  |    double    |   8   | 8-byte floating-point number. |
| 17 | SIH  |   int128_t   |  16   | 16-byte (Hexadeca-byte) signed integer. |
| 18 | UIH  |   uint128_t  |  16   | 16-byte (Hexadeca-byte) unsigned integer. |
| 19 | FPH  |  float128_t  |  16   | 16-byte (Hexadeca-byte) floating-point number. |
| 20 | DTA  |  Data Type A |  xW   | Implementation-defined word-aligned Data Type A. |
| 21 | DTB  |  Data Type B |  xW   | Implementation-defined word-aligned Data Type B. |
| 22 | DTC  |  Data Type C |  xW   | Implementation-defined word-aligned Data Type C. |
| 23 | DTD  |  Data Type D |  xW   | Implementation-defined word-aligned Data Type D. |
| 24 | DTE  |  Data Type E |  xW   | Implementation-defined word-aligned Data Type E. |
| 25 | DTF  |  Data Type F |  xW   | Implementation-defined word-aligned Data Type F. |
| 26 | DTG  |  Data Type G |  xW   | Implementation-defined word-aligned Data Type G. |
| 27 | DTH  |  Data Type H |  xW   | Implementation-defined word-aligned Data Type H. |
| 28 | DTI  |  Data Type I |  xW   | Implementation-defined word-aligned Data Type I. |
| 29 | DTJ  |  Data Type J |  xW   | Implementation-defined word-aligned Data Type J. |
| 30 | DTK  |  Data Type K |  xW   | Implementation-defined word-aligned Data Type K. |
| 31 | DTL  |  Data Type L |  xW   | Implementation-defined word-aligned Data Type L. |

##### List of Types Key

| Width | Description |
|:-----:|:------------|
|   ?   | Nil-terminated string type. |
|   x   | The numbers 0, 1, 2, 4, 8, and 16 are the number of bytes in the type. |
|   xW  | Word-aligned size determined by implementation. |

#### Vector Types

The Vector types are stored in b6:b5 for 1, 2, and 4-byte Data Types. All Data Types are memory aligned thus creating a number of illegal data types, such as an 1-byte Array of 2-byte data types.

| Value | Type | Description                              |
|:-----:|:----:|:----------------------------------------:|
|   0   | VHT  | Vector of 1, 2, 3, or 4 POD types 0-31.  |
|   1   | ARY  | Array of homogenous types.               |
|   2   | STK  | Stack (vector) of homogenous types.      |
|   3   | MAT  | Matrix of homogenous types.              |

#### One-byte Data Type Bit Pattern

1-byte types only support 2-byte Size Width and are intended for memory constrained processors.

| b7 |    b6:b5    | b4:b0 |
|:--:|:-----------:|:-----:|
| SW | Vector Type |  POD  |

##### Size Width Pattern b7

| Value | Type | Description |
|:-----:|:----:|:------------|
|   0   | VHT  | Vector of Homogenous POD Types 0-31. |
|   1   | SW2  | 2-byte wide size type, or UTF-16 ADR/STR/TKN types. |

#### Two and Four-byte Type Bit Pattern

The difference between a 4-byte and a 2-byte data type are that the 4-byte data type can support heterogeneous tuples. 1 and 2-byte data types both support up to 4 heterogeneous types

##### Size Width Bit Pattern b8:b7

The Size width (SW) bits stores the number of bits uses to store the Object Array Size. If the the number of bits is zero then it is a POD Data Type.

| Value | Type | Description |
|:-----:|:----:|:------------|
|   0   | VHT  | 1, 2, 3, and 4-tuple of POD types 0-31. |
|   1   | SW2  | 2-byte (2-byte) size-width type, or String Type 1 (UTF-8). |
|   2   | SW4  | 4-byte (4-byte) size-width type, or String Type 2 (UTF-16). |
|   3   | SW8  | 8-byte (8-byte) size-width type, or String Type 3 (UTF-32). |

##### Illegal Vector Types

Extended types are created by the Illegal Types. The Illegal Types are types that are not memory aligned on any processor, such as a Stack of SI2 with an SI1 size width. If the POD type is 8 or more bytes wide then the stack or array must use a SW8 (8-byte Size Width).

```AsciiArt
| Vector |                   POD Type 0-31 (1=Yes, 0=No)                    |
|  Type  | N S S S C S U C S U F B C S U F  B T T T S U F S U F O A T B T T |
| SW:VET | I T T T H I I H I I P O H I I P  O M M M I I P I I P P D V G B S |
| b8:b5  | L 1 2 3 1 1 1 2 2 2 2 2 4 4 4 4  4 4 E 8 8 8 8 H H H D J T N T T |
+--------+------------------------------------------------------------------|
| 00_VH1 | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 00_ARY | 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 00_STK | 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 00_MAT | 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 01_VHT | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 01_ARY | 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 01_STK | 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 01_MAT | 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 10_VH4 | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 10_ARY | 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 10_STK | 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 10_MAT | 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 11_VH4 | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 11_ARY | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 11_STK | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 11_MAT | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
+--------+------------------------------------------------------------------|
| Total  | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  512   |      Type 0-31      0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
```

##### Extended Types

Extended Types are created from the Illegal Types.

| ID  |  Type   |    Name    | Description |
|:---:|:-------:|:----------:|:------------|
| 39  |   LST   |    List    | A collection of type-value tuples. |
| 40  |   BOK   |    Book    | An associative list without a hash-table. |
| 41  |   BSQ   | B-Sequence | Header for a sequence of bytes. |
| 42  |   BIN   |  B-Input   | A Byte-input ring buffer socket. |
| 43  |   BOU   |  B-Output  | A Byte-output ring buffer socket. |
| 44  |   BIO   |    B-IO    | A BIn and BOut. |
| 45  |   XPR   | Expression | A SCRIPT Script. |

##### Modifier Bits

The Modifier Bits (MB) allow for the creation of pointers and const pointers to POD and Vector types.

| Value | Type | Description     |
|:-----:|:----:|:----------------|
|   0   |  POD | Plain-Old-Data. |
|   1   |  PTR | Pointer.        |
|   2   |  CNS | Const.          |
|   3   |  PTC | Const Pointer.  |

##### 2-byte Type Bit Pattern

2-byte types can be used created a POD Type or a map one POD Type to another such as a ST1_FP4 (char*-to-float in C++) map or a CH1_BOL (char-to-bool in C++) map. To create a single POD type set the Map type to 0.

| b15:b14 |  b13:b9  | b8:b7 | b6:b5 | b4:b0 |
|:-------:|:--------:|:-----:|:-----:|:-----:|
|   MB    | Map type |  SW   |  VHT  |  POD  |

**[<< Previous Section:ASCII Data Specification >>](./readme.md)  |  [Next Section:Integers >>](integers.md)**

## Requirements

[10]: ../overview/requirements.md

## License

Copyright 2014-9 (C) [Cale McCollough](https://calemccollough.github.io); all rights reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
