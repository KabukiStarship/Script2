# [SCRIPT Specification RFC](../readme.md)

## [ASCII Data Specification](readme.md)

There are 64K Automaton Standard Code for Information Interchange (ASCII) Data Types composed of 25 Plain-Old-Data (POD) Types from which may be created Arrays, Vectors, Matrices, Books of Plain-old-data, Dictionaries of Plain-old-data, and Dictionaries of Keys. Types are identified using three letter capitol abbreviations and acronyms with an additional subscript for the word width in bytes. The convention is that the number right after the 3 letter type is the size of the array in elements, and after the number after the underscore represents the byte pattern. For example, UIX160 is a 160-byte unsigned integer or hash and DIC_4 is a 32-bit Dictionary.

### Abstract POD Types

Abstract Plain-Old-Data Types do not have a pre-defined size. These types are based on the microprocessor word size the default character type for that system.

| Type |  Alt Name  | Width | Description |
|:----:|:----------:|:-----:|:------------|
| SIN  |    int     |  >=2  | Signed integer of at least 16 bits. |
| UIN  |    uint    |  >=2  | Unsigned integer of at least 16 bits. |
| FLN  |   float_t  |   W   | Floating-point number of at least 16 bits. |
| SIW  |  intptr_t  |   W   | Signed integer of the size of the host CPU's ALU. |
| UIW  | uintptr_t  |   W   | Unsigned integer of the size of the host CPU's ALU. |
| FLW  | floatptr_t |   W   | Floating-point number the size of the size of the host CPU's FPU. |
| CHN  |  wchar_t   | 1,2,4 | Unicode character at least 16 bits wide. |
| CHR  |   char_t   | 1,2,4 | Default Unicode char type for the Crabs Console. |

### 16-bit ASCII Type Bit Pattern

ASCII Data Types are created from a combination of two types. For mono-types TYPE (Type which is 0) is used for the Map Type.

|  b15:b14  |  b13:b12  |  b7:b6   | b5:b0 |
|:---------:|:---------:|:--------:|:-----:|
| Bit-depth | Map class | Map type | Class |

#### Format Bit Pattern b15:b14

Bit-depths of 8-bit types are restricted to situation where they can be memory aligned on 8/16-bit, 32-bit, and 64-bit processors. In order to create an Object (OBJ) that is half the sizes listed by setting the Map type to OBH (Object Half-sized).

| Value | Type | Description |
|:-----:|:-----|:------------|
|   0   | TYP  | ASCII Data Type 0-63. |
|   1   | FM2  | size_bytes is 16-bit wide or is UTF-8 type. |
|   2   | FM4  | size_bytes is 32-bit wide or is UTF-16 type. |
|   3   | FM8  | size_bytes is 64-bit wide or is UTF-32 type. |

#### Map Types  b13:b12

Maps can be created of most of the types to most of the types.

| Value | Type | Description |
|:-----:|:-----|:------------|
|   0   | ARY  | Array of one ore more of the types 0-63. |
|   1   | VEC  | Vector of homogenous types. |
|   2   | MAT  | Matrix of homogenous types. |
|   3   | MAP  | Map of one POD or Class to another. |

### ASCII Data Types Table

| ID  |   Type   |  C++/Alt Name   |  Width   | Description         |
|:---:|:--------:|:---------------:|:--------:|:--------------------|
|   0 |   NIL    |    null/void    |     0    | Nil/null/void type. |
|   1 |   SI1    |      int8_t     |     1    | 8-bit signed integer. |
|   2 |   UI1    |     uint8_t     |     1    | 8-bit unsigned integer. |
|   3 |   SI2    |     int16_t     |     2    | 16-bit signed integer. |
|   4 |   UI2    |    uint16_t     |     2    | 16-bit unsigned integer. |
|   5 |   FP2    |      half       |     2    | 16-bit floating-point number. |
|   6 |   BOL    |      bool       |     4    | Boolean variable stored as SI4 type. |
|   7 |   SI4    |     int32_t     |     4    | 32-bit signed varint. |
|   8 |   UI4    |     uint32_t    |     4    | 32-bit unsigned integer. |
|   9 |   FP4    |      float      |     4    | 32-bit floating-point number. |
|  10 |   SI8    |     int64_t     |     8    | 64-bit signed integer. |
|  11 |   UI8    |     uint64_t    |     8    | 64-bit unsigned integer. |
|  12 |   FP8    |     double      |     8    | 64-bit floating-point number. |
|  13 |   SIH    |    int128_t     |    16    | 128-bit signed integer. |
|  14 |   UIH    |    uint128_t    |    16    | 128-bit unsigned integer. |
|  15 |   FPH    |   float128_t    |    16    | 128-bit floating-point number. |
|  16 |   POD    |      POD        | 1,2,4,8  | 1, 2, 4, or 8-byte wide Plain-Old-Data. |
| ... |   ...    |      ...        |   2-32   | Assert bit 4 to create a complex number of types 1-15. |
|  32 |   CH1    |      char       |     1    | 8-bit character (CH1). |
|  33 |   CH2    |    char16_t     |     2    | 16-bit character (CH2). |
|  34 |   CH4    |     char32_t    |     4    | 32-bit character (CH4). |
|  35 |   TM4    |     int32_t     |     4    | 32-bit signed integer seconds since epoch timestamp. |
|  36 |   TM8    |     int64_t     |     8    | 64-bit microsecond since epoch timestamp. |
|  37 |   TME    |     int64_t     |     8    | 64-bit TM4 and UI4 sub-second tick timestamp. |
|  38 |   PT2    |     Pointer     |     2    | 16-bit pointer. |
|  39 |   PC2    |     Pointer     |     2    | 16-bit const pointer. |
|  40 |   PT4    |     Pointer     |     4    | 32-bit pointer. |
|  41 |   PC4    |     Pointer     |     4    | 32-bit const pointer. |
|  42 |   PT8    |     Pointer     |     8    | 64-bit pointer. |
|  43 |   PC8    |     Pointer     |     8    | 64-bit const pointer. |
|  44 |   OA4    |   Auto Object   |     8    | A 32-bit AsciiFactory and pointer an instance of an OBJ. |
|  45 |   OA8    |   Auto Object   |    16    | A 64-bit AsciiFactory and pointer an instance of an OBJ. |
|  46 |   P16    |      POD        |    16    | 16-byte wide Plain-old-data or 8-byte complex POD. |
|  47 |   P32    |      POD        |    32    | Complex 128-bit Plain-old-data. |
|  49 |   BNM    |     BigNum      |   1-64   | Unsigned or signed integer between 1 and 64-bytes wide. |
|  50 |   VIN    |     Varint      |    >0    | MSb-encoded variable-length integer (Varint) or OBJ. |
|  51 |   ST1    |     Strand      |  (SI4)N  | A UTF-8, UTF-16, or UTF-32 string with SI4 size_width. |
|  52 |   ST2    |     Strand      |  (SI4)N  | A UTF-8, UTF-16, or UTF-32 string with SI4 size_width. |
|  53 |   ST4    |     Strand      |  (SI4)N  | A UTF-8, UTF-16, or UTF-32 string with SI4 size_width. |
|  54 |   TKN    |     Token       |  (SI4)N  | A Strand without whitespace. |
|  55 |   ADR    |     Address     |  (SI4)N  | A Strand abstract stack operation address. |
|  56 |   REC    |     Record      | (SI4)N+W | A Strand followed by a Wildcard. |
|  57 |   LOM    |     Loom        |  (SI4)N  | An "array" of UTF-8, UTF-16, or UTF-32 strings with SI4 or SI2 size_bytes. |
|  58 |   OB1    |     Object      |   1/2    | Types cuts in half the bit-depth of the b15:b14. |
|  59 |   OBJ    |     Object      |    N     | A object beginning with a 16, 32, or 64-bit wide size_bytes. |
|  60 |   SLT    |      Slot       |    N     | An interprocess ring buffer. |
|  61 |   BSQ    |   B-Sequence    |    N     | An OBJ that represent the order of types in a byte-sequence. |
|  62 |   EXP    |   Expression    |    N     | Strand abstract stack machine Expression of BSQ. |
|  63 |   WLD    |    WildCard     |    W     | A type-value tuple. |

#### List of Types Key

|  Width   | Description |
|:--------:|:------------|
|   >0     | Requires at least one byte. |
|    N     | Has pre-specified Object size less than 2^N, where N is a natural number.|
|   1-16   | POD types are typically 16, 32, or 64-bit wide and 8-bit types are created with OB1 and 16-bit POD types with OB1. |
|   1-32   | A complex type consisting of two contiguous POD types. |
|   1-64   | 1-64 byte integer by Map type to BNM. |
|   1/2    | Type cuts in half the Bit-depth b15:b14 when used as Map type. |
|  (SI4)N  | Strand and Loom type uses SI4-wide size_bytes or POD1 Map type to create 16-bit size_bytes. |
| (SI4)N+W | Begins with an n-element array followed by a Wildcard. |
|    W     | Type-value tuple beginning in a 2-byte type. |
