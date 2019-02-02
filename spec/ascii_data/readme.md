# [SCRIPT Specification RFC](../readme.md)

## [ASCII Data Specification](readme.md)

There are 32 Automaton Standard Code for Information Interchange (ASCII) Data Types composed of 23 Plain-Old-Data and 8 object types composed of contiguous memory. Types are stored as bytes where the 5 LSb are used to store the type and the upper 3 bits are used to store either bit width of the size of the object, 8, 16, 32, or 64-bit, or to store the dimensions of a stack or multi-dimensional array. Implementations shall support types SVI, UVI, ADR, and STR and may support more types.All ASCII Types can be represented as a single byte where the lower 5 bits are used to store the type, and the upper three bits are used to store if the type is an array.

|   b7-b6   |     b5   |   b4-b0   |
|:---------:|:--------:|:---------:|
| bit_width | is_stack | type 0-31 |

### ASCII Data Types Table

| ID | Type |  Alt Name  | Width  | Description         |
|:--:|:----:|:----------:|:------:|:--------------------|
|  0 | NIL  |  null/void |    0   | Nil/null/void type. |
|  1 | SI1  |    int8_t  |   -1   | 8-bit signed integer. |
|  2 | UI1  |   uint8_t  |    1   | 8-bit unsigned integer. |
|  3 | BOL  |    bool    |    4   | Non-zero false Boolean variable. |
|  4 | SI2  |   int16_t  |   -2   | 16-bit signed varint. |
|  5 | UI2  |  uint16_t  |    2   | 16-bit unsigned integer. |
|  6 | FP2  |    half    |    2   | 16-bit floating-point number. |
|  7 | SI4  |   int32_t  |   -4   | 32-bit signed varint. |
|  8 | UI4  |  uint32_t  |    4   | 32-bit unsigned integer. |
|  9 | FP4  |    float   |    4   | 32-bit floating-point number. |
| 10 | TM4  |   int32_t  |   -4   | 32-bit signed integer second since epoch timestamp. |
| 11 | TME  |   int64_t  |   -8   | Dual-SI4 seconds since epoch timestamp and sub-second ticker. |
| 12 | TM8  |   int64_t  |   -8   | 64-bit microsecond since epoch timestamp. |
| 13 | SI8  |   int64_t  |   -8   | 64-bit signed integer. |
| 14 | UI8  |  uint64_t  |    8   | 64-bit unsigned integer. |
| 15 | FP8  |   double   |    8   | 64-bit floating-point number. |
| 16 | SIH  |  int128_t  |  -16   | 128-bit signed integer. |
| 17 | UIH  | uint128_t  |   16   | 128-bit unsigned integer. |
| 18 | FPH  |   Decimal  |   16   | 128-bit floating-point number. |
| 19 | UIX  |  Unsigned  | 32-4KB | Unsigned integer between 32 and 2^12 bits wide. |
| 20 | ADR  |   Address  |  <=N   | Stack Operation Address. |
| 21 | STR  |   String   |  <=N   | UTF-8 _::TStrand<>. |
| 22 | TKN  |   Token    |  <=N   | UTF-8 _::TStrand<> without any whitespace. |
| 23 | BSQ  | B-Sequence |  <=N   | B-Sequence. |
| 24 | OBJ  |   Object   |    N   | N-byte contiguous object staring with the size. |
| 25 | LOM  |   Loom     |    N   | Array of UTF-8, UTF-16, or UTF-32 strings without a hash table. |
| 26 | TBL  |   Table    |    N   | Hash-table of strings with contiguous indexes. |
| 27 | EXP  | Expression |  <=N   | Script expression of B-Sequences. |
| 28 | LST  |   List     |    N   | Stack of type-Records with contiguous indexes starting at zero. |
| 29 | MAP  |    Map     |    N   | Unique map of integer-Record records. |
| 30 | BOK  |    Book    |    N   | Book, or Multidictionary, of Records without a hash table. |
| 31 | DIC  | Dictionary |    N   | Unique map of key-value records with a hash table. |

#### List of Types Key

| Width | Description |
|:-----:|:------------|
|  -X   | Signed integer type.|
|   ?   | Type of unknown size.|
|   N   | Has pre-specified buffer of size N bytes.|
| <=N   | Has pre-specified buffer of size N bytes but can use less than that.|

#### ASCII Word Types

Abstract ASCII Types do not have a pre-defined size.

| ID | Type |  Alt Name  | Width  | Description         |
|:--:|:----:|:----------:|:------:|:--------------------|
|    | SIN  |    int     |    0   | Signed integer of at least 16 bits. |
|    | UIN  |    uint    |    0   | Unsigned integer of at least 16 bits. |
|    | FLN  |            |    0   | Floating-point number of at least 16 bits. |
|    | SIW  |  intptr_t  |    0   | Signed integer of the size of the host CPU's ALU. |
|    | UIW  | uintptr_t  |    0   | Unsigned integer of the size of the host CPU's ALU. |
|    | FLW  |            |    0   | Floating-point number the size of the size of the host CPU's FPU. |
|    | CHR  |   char_t   | 1,2,4  | Default Unicode char type for the console. |
|    | CHN  |   char_t   | 1,2,4  | Unicode character at least 16 bits wide. |

##### Examples of Arrays with Errors

```Script2
[UI2#3<2: 1 x 0>]               // Array type must be 2, 4, or 8!
[UI#2<2: 1 x 70,000>]           // Too many members to fit in an Array2!
[FP2#2<2: 1 x 2> 0.1, 0.0, 0.3] // Too many members!
[MAP#4<1>]                      // Can't contain Hierarchical data types!
```
