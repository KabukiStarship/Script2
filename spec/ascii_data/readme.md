# [SCRIPT Specification RFC](../readme.md)

## [ASCII Data Specification](readme.md)

The Automaton Standard Code for Information Interchange (ASCII) Data Types composed of 25 Plain-Old-Data (POD) Types from which may be created Arrays, Vectors, Matrices, Books of Plain-old-data, Dictionaries of Plain-old-data, and Dictionaries of Keys. Types are identified using three letter capitol abbreviations and acronyms with an additional subscript for the word width in bytes. The convention is that the number right after the 3 letter type is the size of the array in elements, and after the number after the underscore represents the byte pattern. For example, UIX160 is a 160-byte unsigned integer or hash and DIC_4 is a 32-bit Dictionary.

### Abstract POD Types

Abstract Plain-Old-Data Types do not have a pre-defined size. These types are based on the microprocessor word size the default character type for that system.

| ID | Type |  Alt Name  | Width  | Description         |
|:--:|:----:|:----------:|:------:|:--------------------|
|    | SIN  |    int     |    0   | Signed integer of at least 16 bits. |
|    | UIN  |    uint    |    0   | Unsigned integer of at least 16 bits. |
|    | FLN  |            |    0   | Floating-point number of at least 16 bits. |
|    | SIW  |  intptr_t  |    0   | Signed integer of the size of the host CPU's ALU. |
|    | UIW  | uintptr_t  |    0   | Unsigned integer of the size of the host CPU's ALU. |
|    | FLW  |            |    0   | Floating-point number the size of the size of the host CPU's FPU. |
|    | CHN  |   char_t   | 1,2,4  | Unicode character at least 16 bits wide. |
|    | CHR  |   char_t   | 1,2,4  | Default Unicode char type for the Crabs Console. |
|    | STR  |   Strand   |    N   | The default ASCII Strand for the Crabs Console. |

### 16-bit ASCII Type Bit Pattern

|  b15:b14  |  b13:b12  |  b7:b6   | b5:b0 |
|:---------:|:---------:|:--------:|:-----:|
| Bit-depth | Map class | Map type | Class |

#### Bit-depth b15:b14

Bit depths of 8-bits are allowed for ARY, VEC, and MAT of SI2,

| Value | Type | Description |
|:-----:|:-----|:------------|
|   0   | COP  | Class or POD type. |
|   1   | SW2  | size_width of size_bytes is 16-bit wide. |
|   2   | SW4  | size_width of size_bytes is 32-bit wide. |
|   3   | SW8  | size_width of size_bytes is 64-bit wide. |

#### Map Types  b13:b12

| Value | Type | Description |
|:-----:|:-----|:------------|
|   0   | ARY  | Array of one of the types 0-63. |
|   1   | VEC  | Vector of one of the types 0-63. |
|   2   | MAT  | Matrix of one of the types 0-63. |
|   3   | MAP  | Map of one POD or Class to another. |

### ASCII Data Types Table

| ID  |   Type   |  C++/Alt Name   |  Width  | Description         |
|:---:|:--------:|:---------------:|:-------:|:--------------------|
|   0 |   NIL    |    null/void    |    0    | Nil/null/void type. |
|   1 |   CH1    |      char       |    1    | 8-bit character (CH1). |
|   2 |   CH2    |    char16_t     |    2    | 16-bit character (CH2). |
|   3 |   CH4    |     char32_t    |    4    | 32-bit character (CH4). |
|   4 |   SI1    |      int8_t     |    1    | 8-bit signed integer. |
|   5 |   UI1    |     uint8_t     |    1    | 8-bit unsigned integer. |
|   6 |   SI2    |     int16_t     |    2    | 16-bit signed integer. |
|   7 |   UI2    |    uint16_t     |    2    | 16-bit unsigned integer. |
|   8 |   FP2    |      half       |    2    | 16-bit floating-point number. |
|   9 |   BOL    |      bool       |    4    | Boolean variable stored as SI4 type. |
|  10 |   SI4    |     int32_t     |    4    | 32-bit signed varint. |
|  11 |   UI4    |     uint32_t    |    4    | 32-bit unsigned integer. |
|  12 |   FP4    |      float      |    4    | 32-bit floating-point number. |
|  13 |   TM4    |     int32_t     |    4    | 32-bit signed integer seconds since epoch timestamp. |
|  14 |   TME    |     int64_t     |    8    | 64-bit TM4 and UI4 sub-second tick timestamp. |
|  15 |   TM8    |     int64_t     |    8    | 64-bit microsecond since epoch timestamp. |
|  16 |   SI8    |     int64_t     |    8    | 64-bit signed integer. |
|  17 |   UI8    |     uint64_t    |    8    | 64-bit unsigned integer. |
|  18 |   FP8    |     double      |    8    | 64-bit floating-point number. |
|  19 |   SIH    |    int128_t     |    16   | 128-bit signed integer. |
|  20 |   UIH    |    uint128_t    |    16   | 128-bit unsigned integer. |
|  21 |   FPH    |   float128_t    |    16   | 128-bit floating-point number. |
|  22 |   OB1    |     Object      |  <256   | An Array (ARY), Vector (VEC), or Object (OBJ) class less than 256 bytes. |
|  23 |   BNM    |     BigNum      |  1-64   | Unsigned or signed integer between 1 and 512-bits wide. |
|  24 |   TKN    |     Token       |   NE4   | A Strand without whitespace. |
|  25 |   ADR    |     Address     |   NE4   | A UTF-8 abstract stack operation address. |
|  26 |   REC    |     Record      |   NE4   | A key-value tuple of any of the other ASCII Types ending with an empty stack. |
|  27 |   OBJ    |     Object      |   >0    | A object beginning with a 16, 32, or 64-bit wide size_bytes. |
|  28 |   LST    |      List       |    N    | Stack of Wildcards with contiguous indexes. |
|  29 |   SLT    |      Slot       |    N    | An interprocess ring buffer. |
|  30 |   BSQ    |   B-Sequence    |    N    | An OBJ that represent the order of types in a byte-sequence. |
|  31 |   EXP    |   Expression    |    N    | Strand abstract stack machine Expression of BSQ. |
|  32 |   INV    |    Invalid      |    0    | Invalid type. |
|  33 |   LM1    |     Loom        |    N    | An UTF-8 associated array of strings with SI4 size. |
|  34 |   LM2    |     Loom        |    N    | A UTF-16 associated array of strings with SI4 size. |
|  35 |   LM4    |     Loom        |    N    | A UTF-32 associated array of strings with SI4 size. |
| ... |   ...    |      ...        |         | Assert bit 5 to create a complex number of types 1-21. |
|  54 |   PT1    |    Pointer      |         | 16-bit pointer. |
|  55 |   PC1    |    Pointer      |         | 16-bit const pointer. |
|  56 |   PT1    |    Pointer      |         | 32-bit pointer. |
|  57 |   PC1    |    Pointer      |         | 32-bit const pointer. |
|  58 |   PT1    |    Pointer      |         | 64-bit pointer. |
|  59 |   PC1    |    Pointer      |         | 64-bit const pointer. |
|  60 |   OA2    |   Auto Object   |   2W    | A 16-bit AsciiFactory and pointer an instance of an object in memory. |
|  61 |   OA4    |   Auto Object   |   2W    | A 32-bit AsciiFactory and pointer an instance of an object in memory. |
|  62 |   OA8    |   Auto Object   |   2W    | A 64-bit AsciiFactory and pointer an instance of an object in memory. |
|  63 |   WLD    |    WildCard     |   >2    | A one-byte-type-value tuple. |

#### List of Types Key

| Width | Description |
|:-----:|:------------|
|  >0   | Requires at least one byte. |
|  N    | Has pre-specified buffer of size N bytes.|
|  NE   | Has pre-specified element count of N 8, 16, 32, or 64, or 128-bit elements. |
| NE4   | Has pre-specified element count of N 8, 16, 32, or 64, or 128-bit elements. |
| NE+S  | Begins with an n-element array followed by another value. |
|  2W   | 2 Load-and-store machine ALU words. |
| 1-64  | Create 1-64 byte unsigned integer by Map type to BGN or a signed by setting the POD or Class to BGN. |
