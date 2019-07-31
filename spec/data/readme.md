# [SCRIPT Specification](../readme.md)

## [ASCII Data Specification](readme.md)

Automaton Standard Code for Information Interchange (ASCII) Data Types are mimicked after the the American Standard Code for Information Interchange C0 Control Codes using 3 all capitol letters. There are 32 POD Data Types, mimicking the number of ASCII C0 Control Codes, that include 5 Object pointer types that point to objects. Arrays, Stacks, multi-dimensional matrices, and 2, 3, and 4-homogenous-tuple (homo-tuple) types can be created using the Vector types bit. All data types are word-aligned leaving some illegal Vector types, such as an 8-bit Array of 16-bit types. These illegal types are used in order to create 2, 3, and 4-tuple homogeneous Vectors of a type, such as a 4-tuple of 8-bit unsigned integers (UI1).

Data Types can be represented using 1-byte, 2-byte, and 4-byte data types. 1-byte Data Types are forward compatible with 2 and 4-byte Types, and likewise 2-byte types are forward compatible with 4-byte types.

### POD Data Types Table

| ID | Type | C++/Alt Name | Width | Description |
|:--:|:----:|:------------:|:-----:|:------------|
|  0 | NIL  |     null     |   0   | Nil/null/void type. |
|  1 | ST1  |     char*    |   ?   | UTF-8 string. |
|  2 | ST2  |   char16_t*  |   ?   | UTF-16 string. |
|  3 | ST3  |   char32_t*  |   ?   | UTF-32 string. |
|  4 | CH1  |     char     |   1   | 8-bit character (CH1). |
|  5 | SI1  |     int8_t   |   1   | 8-bit signed integer. |
|  6 | UI1  |    uint8_t   |   1   | 8-bit unsigned integer. |
|  7 | DT1  |      SI1     |   1   | 8-bit ASCII data type. |
|  8 | CH2  |   char16_t   |   2   | 16-bit character (CH2). |
|  9 | SI2  |    int16_t   |   2   | 16-bit signed integer. |
| 10 | UI2  |   uint16_t   |   2   | 16-bit unsigned integer. |
| 11 | DT2  |      UI2     |   2   | A 16-bit ASCII Data Type. |
| 12 | FP2  |     half     |   2   | 16-bit floating-point number. |
| 13 | BLN  |      SI2     |   2   | A boolean value stored as a SI2. |
| 14 | DTB  |      UI2     |   2   | Two 8-bit ASCII Data Types. |
| 15 | DTC  |      UI2     |   2   | Three 5-bit ASCII POD Types. |
| 16 | CH4  |   char32_t   |   4   | 32-bit character (CH4). |
| 17 | SI4  |    int32_t   |   4   | 32-bit signed varint. |
| 18 | UI4  |   uint32_t   |   4   | 32-bit unsigned integer. |
| 19 | DT4  |     UI4      |   4   | 32-bit ASCII Data Type. |
| 20 | FP4  |     float    |   4   | 32-bit floating-point number. |
| 21 | BOL  |     bool     |   4   | Boolean variable. |
| 22 | TM4  |    int32_t   |   4   | 32-bit signed integer seconds since epoch timestamp. |
| 23 | TME  |    int64_t   |   8   | 64-bit TM4 and UI4 sub-second tick timestamp. |
| 24 | TM8  |    int64_t   |   8   | 64-bit microsecond since epoch timestamp. |
| 25 | SI8  |    int64_t   |   8   | 64-bit signed integer. |
| 26 | UI8  |   uint64_t   |   8   | 64-bit unsigned integer. |
| 27 | DT8  |      UI8     |   8   | 64-bit ASCII Data Type. |
| 28 | FP8  |    double    |   8   | 64-bit floating-point number. |
| 29 | SIH  |   int128_t   |  16   | 128-bit (Hexadeca-byte) signed integer. |
| 30 | UIH  |   uint128_t  |  16   | 128-bit (Hexadeca-byte) unsigned integer. |
| 31 | FPH  |  float128_t  |  16   | 128-bit (Hexadeca-byte) floating-point number. |

#### List of Types Key

| Width | Description |
|:-----:|:------------|
|   ?   | Nil-terminated string type. |
| <=W   | Stored as one CPU word but compressed when transmitted with MSb variant encoding. |
|  2/4  | C++ int type is 16-bits on 16-bit systems and 32-bits on 32-bit and 64-bit systems. |

### Vector Types

The Vector types are stored in b6:b5 for 1, 2, and 4-byte Data Types. All Data Types are memory aligned thus creating a number of illegal data types, such as an 8-bit Array of 16-bit data types.

| Value | Type | Description                              |
|:-----:|:-----|:----------------------------------------:|
|   0   | VHT  | Vector of 1, 2, 3, or 4 POD types 0-31.  |
|   1   | ARY  | Array of homogenous types.               |
|   2   | STK  | Stack (vector) of homogenous types.      |
|   3   | MAT  | Matrix of homogenous types.              |

### One-byte Data Type Bit Pattern

1-byte types (DT1) only support 2-byte Size widths and are intended for memory constrained processors.

| b7 | b6:b5 | b4:b0 |
|:--:|:-----:|:-----:|
| SW |  VHT  | POD  |

#### Size Width Pattern b7

| Value | Type | Description |
|:-----:|:----:|:------------|
|   0   | VHT  | Vector of Homogenous POD Types 0-31. |
|   1   | SW2  | 2-byte wide size type, or UTF-16 ADR/STR/TKN types. |

### Two and Four-byte Type Bit Pattern

The difference between a 4-byte and a 2-byte data type are that the 4-byte data type can support heterogeneous tuples. 1 and 2-byte data types both support up to 4 heterogeneous types

#### Size Width Bit Pattern b8:b7

The Size width (SW) bits stores the number of bits uses to store the Object Array Size. If the the number of bits is zero then it is a POD Data Type.

| Value | Type | Description |
|:-----:|:----:|:------------|
|   0   | VHT  | 1, 2, 3, and 4-tuple of POD types 0-31. |
|   1   | SW2  | 2-byte (16-bit) size-width type, or String Type 1 (UTF-8). |
|   2   | SW4  | 4-byte (32-bit) size-width type, or String Type 2 (UTF-16). |
|   3   | SW8  | 8-byte (64-bit) size-width type, or String Type 3 (UTF-32). |

#### Illegal Vector Types

Extended types are created by the Illegal Types. The Illegal Types are types that are not memory aligned. If the POD type is 8 or more bytes wide then the stack or array must use a SW8 (8-byte Size Width).

| Byte Depth | ARY Range  | STK Range  | MAT Range  | Total |
|:----------:|:----------:|:----------:|:----------:|:-----:|
|     1      | [40 ,  64] | [72 , 128] | [200, 255] |  72   |
|     2      | [280, 295] | [312, 327] | [344, 359] |  36   |
|     3      | [312, 319] | [344, 351] | [376, 383] |  24   |

```AsciiArt
| Vector |                   POD Type 0-31 (1=Yes, 0=No)                    |
|  Type  | N S S S C S U D C S U D F B R R  C S U D F B T T T S U F F S U F |
| SW:VET | I T T T H I I T H I I T P L E E  H I I T P O M M M I I P P I I P |
| b8:b5  | L 1 2 3 1 1 1 1 2 2 2 2 2 N 1 2  4 4 4 4 4 L 4 E 8 8 8 8 G H H H |
+--------+------------------------------------------------------------------|
| 00_VH1 | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 00_ARY | 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 00_STK | 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 00_MAT | 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 01_VHT | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 01_ARY | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 |
| 01_STK | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 |
| 01_MAT | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 |
| 10_VH4 | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 10_ARY | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 |
| 10_STK | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 |
| 10_MAT | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 |
| 11_VH4 | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 11_ARY | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 11_STK | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 11_MAT | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
+--------+------------------------------------------------------------------|
| Total  | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  512   |      Type 0-31      0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
```

#### Extended Types

Extended Types are created from the Illegal Types.

| ID  |  Type   |    Name    | Description |
|:---:|:-------:|:----------:|:------------|
| 39  |   WLD   |  Wildcard  | Flag type commonly used to pass any of the Data types into a operation parameter. |
| 76  |   LST   |    List    | A collection of type-value tuples. |
| 77  |   BOK   |    Book    | A STR-VAL (String-Value) map without a hash-table. |
| 78  |   BSQ   | B-Sequence | Header for a sequence of bytes. |
| 79  |   BIN   |  B-Input   | A Byte-input ring buffer socket. |
| 80  |   BOU   |  B-Output  | A Byte-output ring buffer socket. |
| 81  |   XPR   | Expression | A SCRIPT Script. |

#### 2-byte DTB Bit Pattern

Data Type B (DTB) is two 16-bit words where the first DT2 is the first type.

| b31:b16 | b15:b0 |
|:-------:|:------:|
| Type 2  | Type 1 |

#### 2-byte DTC Bit Pattern

Data Type B (DTB) is two 16-bit words where the first DT2 is the first type.

| b15 | b14:b10 | b9:b5  | b4:b0  |
|:---:|:-------:|:------:|:------:|
|  0  | Type 3  | Type 2 | Type 1 |

### Read-Write Bits

For 2 and 4-byte types, b15:b14 are used to store Read-Write flags. If a type cannot be read or written too, it is hidden from remote systems.

| Value  | Description            |
|:------:|:-----------------------|
|    0   | Hidden.                |
|    1   | Write-only.            |
|    2   | Read-only.             |
|    3   | Read and write access. |

#### 2-byte Type Bit Pattern

2-byte types can be used created a POD Type or a map one POD Type to another such as a ST1_FP4 (UTF-8 string-to-float) map or a CH1_BOL (char-to-bool) map. To create a single POD type set the Map type to 0.

| b15:b14 |  b13:b9  | b8:b7 | b6:b5 | b4:b0 |
|:-------:|:--------:|:-----:|:-----:|:-----:|
|   RW    | Map type |  SW   |  VHT  |  POD  |

#### 2-byte and 4-byte Extended Type Bit Pattern

ASCII Data Types are created from a combination of two types. For mono-types VHT is used for the Map Type.

| b31:16 | b15:b14 |   b13:b9 | b8:b7 | b6:b5 | b4:b0  |
|:------:|:-------:|:--------:|:-----:|:-----:|:------:|
|    0   |   RW    | Map type |   2   |  SWO  | Object |

#### 4-byte Map Type Bit Pattern

ASCII Data Types are created from a combination of two types. For mono-types TYP is used for the Map Type.

| b31:b16 | b15:b0 |
|:-------:|:------:|
| Type 2  | Type 1 |

#### 8-byte Type Tuple Bit Pattern

4-byte Data Types are used to create up to a 4-tuples of heterogeneous types (hetero-tuples) using up to 4 16-bit ASCII Data Types.

| b63:b48 | b55:b32 | b31:b16 | b15:b0 |
|:-------:|:-------:|:-------:|:------:|
| Type 4  | Type 3  | Type 2  | Type 1 |

**<< [Previous Section](.md)** | **[Next Section](.md) >>**

## License

Copyright (C) 2014-9 Cale McCollough <http://calemccollough.github.io/>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
