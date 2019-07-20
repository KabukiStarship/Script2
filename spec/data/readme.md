# [SCRIPT Specification](../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [ASCII Data Specification](readme.md)

Automaton Standard Code for Information Interchange (ASCII) Data Types are mimicked after the the American Standard Code for Information Interchange C0 Control Codes using 3 all capitol letters.

There are 32 Core Data Types composed of 27 Plain-Old-Data (POD) types and 5 Object types (and technically the pointers themselves are POD types). Arrays, Stacks, multi-dimensional matrices, and 2, 3, and 4-homogenous-tuple (homo-tuple) types can be created using the Vector types bit. All data types are word-aligned leaving some illegal Vector types, such as an 8-bit Array of 16-bit types. These illegal types are used in order to create 2, 3, and 4-tuple homogeneous Vectors of a type, such as a 4-tuple of 8-bit unsigned integers (UI1).

Data Types can be represented using 1-byte, 2-byte, and 4-byte data types. 1-byte Data Types are forward compatible with 2 and 4-byte Types, and likewise 2-byte types are forward compatible with 4-byte types.

### Platform-specific POD Types

Platform-specific Plain-Old-Data (POD) Types do not have a pre-defined size and are defined by the target implementation. These types are based on the microprocessor word size and the default character and number types for the target system and application.

| Type |   Alt Name    |  Width  | Description |
|:----:|:-------------:|:-------:|:------------|
| CHN  |   wchar_t     |   2,4   | Unicode character either 16 or 32-bits wide. |
| SIN  |     int       |   2,4   | Signed integer at least 16 bits wide. |
| UIN  | unsigned int  |   2,4   | Unsigned integer at least 16 bits wide. |
| DTW  |   intptr_t    |    W    | A word-sized ASCII Data Type. |
| SIW  |   intptr_t    |    W    | Signed integer of the size of the host CPU's ALU. |
| UIW  |  uintptr_t    |    W    | Unsigned integer of the size of the host CPU's ALU. |
| FLW  |  floatptr_t   |    W    | Floating-point number the size of the size of the host CPU's FPU. |
| CHR  |    char_t     |  1,2,4  | Unicode character at least 8 bits wide. |
| STR  | const char_t* |    ?    | A nil-terminated Unicode string of CHR. |
| SIX  |    int_t      | 1,2,4,8 | Signed integer at least 8 bits wide. |
| UIX  |    uint_t     | 1,2,4,8 | Unsigned integer at least 8 bits wide. |
| FPX  |   float_t     | 1,2,4,8 | Floating-point number at least 16 bits wide. |

### Vector Types

The Vector types are stored in b6:b5 for 1, 2, and 4-byte Data Types. All Data Types are memory aligned thus creating a number of illegal data types, such as an 8-bit Array of 16-bit data types.

| Value |  Type   |     SW == 0     |             Format > 0             |
|:-----:|:--------|:---------------:|:----------------------------------:|
|   0   |   COR   | Core types 0-31 |     One of the Core types 0-31.    |
|   1   | ARY/VH2 |   2-homo-tuple  |      Array of homogenous types     |
|   2   | STK/VH3 |   3-homo-tuple  | Stack (vector) of homogenous types |
|   3   | MAT/VH4 |   4-homo-tuple  |     Matrix of homogenous types     |

### Read-Write Bits

For 2 and 4-byte types, b15:b14 are used to store Read-Write flags. If a type cannot be read or written too, it is hidden from remote systems.

| Value  | Description            |
|:------:|:-----------------------|
|    0   | Hidden.                |
|    1   | Write-only.            |
|    2   | Read-only.             |
|    3   | Read and write access. |

### One-byte Data Type Bit Pattern

1-byte types (DT1) only support 2-byte Size widths and are intended for memory constrained processors.

| b7 | b6:b5  | b4:b0 |
|:--:|:------:|:-----:|
| SW | Vector | Core  |

#### Size Width Pattern b7

| Value |  Type   | Description |
|:-----:|:--------|:------------|
|   0   |   COR   | Core type 0-31, or UTF-8 ADR/STR/TKN types. |
|   1   | SW2/ST1 | 2-byte wide size type, or UTF-16 ADR/STR/TKN types. |

### Two and Four-byte Type Bit Pattern

The difference between a 4-byte and a 2-byte data type are that the 4-byte data type can support heterogeneous tuples. 1 and 2-byte data types both support up to 4 heterogeneous types

#### Size Width Bit Pattern b8:b7

The Size width (SW) bits stores the number of bits uses to store the Object Array Size. If the the number of bits is zero then it is a Core Data Type.

| Value |      Type       | Description |
|:-----:|:----------------|:------------|
|   0   | COR/VH1/VH2/VH4 | Core type 0-31, Homo-tuple type. |
|   1   |       SW2       | 2-byte (16-bit) size-width type, or String Type 1 (UTF-8). |
|   2   |       SW4       | 4-byte (32-bit) size-width type, or String Type 2 (UTF-16). |
|   3   |       SW8       | 8-byte (64-bit) size-width type, or String Type 3 (UTF-32). |

#### 2-byte Type Bit Pattern

2-byte types can be used created a Core Type or a map one Core Type to another such as a ST1_FP4 (UTF-8 string-to-float) map or a CH1_BOL (char-to-bool) map. To create a single core type set the Map type to 0.

| b15:b14 |  b13:b9  | b8:b7 | b6:b5  | b4:b0 |
|:-------:|:--------:|:-----:|:------:|:-----:|
|   RW    | Map type |  SW   | Vector | Core  |

#### 4-byte Map Type Bit Pattern

ASCII Data Types are created from a combination of two types. For mono-types TYP is used for the Map Type.

| b31:16 | b15:b14 |   b13:b9 | b8:b7 | b6:b5  | b4:b0 |
|:------:|:-------:|:--------:|:-----:|:------:|:-----:|
|    0   |    RW   | Map type |  SW   | Vector | Core  |

#### 4-byte Type Tuple Bit Pattern

4-byte Data Types are used to create up to a 5-tuples of heterogeneous types (hetero-tuples). To create a Hetero-tuple type you must assert b31.

|      b31       | b30:b26 | b25:b21 | b20:b16 | b15:b14 | b13:b9  | b8:b7 | b6:b5  | b4:b0 |
|:--------------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-----:|:------:|:-----:|
| Hetero-tuple=1 | Tuple 5 | Tuple 4 | Tuple 3 |   RW    | Tuple 2 |  SW   | Vector | Core  |

***Example:*** We have need to internationalize our strings using a Loom. I need to make a:

### Core Data Types Table

| ID | Type | C++/Alt Name | Width | Description |
|:--:|:----:|:------------:|:-----:|:------------|
|  0 | NIL  |     null     |   0   | Nil/null/void type. |
|  1 | ST1  |     char*    |   ?   | UTF-8 string. |
|  2 | ST2  |   char16_t*  |   ?   | UTF-16 string. |
|  3 | ST3  |   char32_t*  |   ?   | UTF-32 string. |
|  4 | CH1  |     char     |   1   | 8-bit character (CH1). |
|  5 | SI1  |     int8_t   |   1   | 8-bit signed integer. |
|  6 | UI1  |    uint8_t   |   1   | 8-bit unsigned integer. |
|  7 | CH2  |   char16_t   |   2   | 16-bit character (CH2). |
|  8 | SI2  |    int16_t   |   2   | 16-bit signed integer. |
|  9 | UI2  |   uint16_t   |   2   | 16-bit unsigned integer. |
| 10 | FP2  |     half     |   2   | 16-bit floating-point number. |
| 11 | BOL  |     bool     |  2/4  | Boolean variable. |
| 12 | CH4  |   char32_t   |   4   | 32-bit character (CH4). |
| 13 | SI4  |    int32_t   |   4   | 32-bit signed varint. |
| 14 | UI4  |   uint32_t   |   4   | 32-bit unsigned integer. |
| 15 | FP4  |     float    |   4   | 32-bit floating-point number. |
| 16 | TM4  |    int32_t   |   4   | 32-bit signed integer seconds since epoch timestamp. |
| 17 | TME  |    int64_t   |   8   | 64-bit TM4 and UI4 sub-second tick timestamp. |
| 18 | TM8  |    int64_t   |   8   | 64-bit microsecond since epoch timestamp. |
| 19 | SI8  |    int64_t   |   8   | 64-bit signed integer. |
| 20 | UI8  |   uint64_t   |   8   | 64-bit unsigned integer. |
| 21 | FP8  |    double    |   8   | 64-bit floating-point number. |
| 22 | SIH  |   int128_t   |  16   | 128-bit (Hexadeca-byte) signed integer. |
| 23 | UIH  |   uint128_t  |  16   | 128-bit (Hexadeca-byte) unsigned integer. |
| 24 | FPH  |  float128_t  |  16   | 128-bit (Hexadeca-byte) floating-point number. |
| 25 | SIV  |   intptr_t   |   W   | Word-sized signed MSb-encoded Variable-length integer (varint). |
| 26 | UIV  |  uintptr_t   |   W   | Word-sized unsigned MSb-encoded Variable-length integer (varint). |
| 27 | PTC  | const void*  |   W   | Word-sized const pointer. |
| 28 | PTR  |    void*     |   W   | Word-sized pointer. |
| 29 | OPD  |   Operand    |   W   | Word-sized pointer to an Operand object. |
| 30 | AJT  |   Autoject   |  2W   | Automatic object with a RamFactory and pointer to an Object. |
| 31 | VAL  |    Value     |  3W   | An ASCII Type-Value tuple. |

#### List of Types Key

| Width | Description |
|:-----:|:------------|
|   ?   | Nil-terminated string type. |
| <=W   | Stored as one CPU word but compressed when transmitted with MSb variant encoding. |
|  2/4  | C++ int type is 16-bits on 16-bit systems and 32-bits on 32-bit and 64-bit systems. |
|   W   | 1 CPU word. |
|  2W   | 2 CPU words. |
|  3W   | 3 CPU words. |

#### Object Types

The collection types start on the first illegal 16-bit types, which is Core type 11, CH2. The Vector bits are repurposed for the SW bits for the Object types, and types 11-31 can be used for 20 different object types.

| ID  |  Type   |    Name    | Description |
|:---:|:-------:|:----------:|:------------|
| 75  |   WLD   |  Wildcard  | Flag type commonly used to pass any of the Data types into a operation parameter. |
| 76  |   LST   |    List    | A collection of type-value tuples. |
| 77  |   BOK   |    Book    | A STR-VAL (String-Value) map without a hash-table. |
| 78  |   BSQ   | B-Sequence | Header for a sequence of bytes. |
| 79  |   BIN   |  B-Input   | A Byte-input ring buffer socket. |
| 80  |   BOU   |  B-Output  | A Byte-output ring buffer socket. |
| 81  |   XPR   | Expression | A SCRIPT Script. |

#### 2-byte and 4-byte Extended Type Bit Pattern

ASCII Data Types are created from a combination of two types. For mono-types TYP is used for the Map Type.

| b31:16 | b15:b14 |   b13:b9 | b8:b7 | b6:b5  | b4:b0  |
|:------:|:-------:|:--------:|:-----:|:------:|:------:|
|    0   |    RW   | Map type |   2   |   SWO  | Object |
