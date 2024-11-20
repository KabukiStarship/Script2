# Standard Types

ASCII Data Types use 3-letter acronyms in all capital letters[1][2]. Whenever possible, the letters in the ASCII Data Type acronyms are such that like-types are grouped alphabetically, and 8, 16, 32, 64, and 128-bit types use the post fix A, B, C, D, and E, and an 8-bit unsigned integer is a IUA and a 16-bit one is a IUB. Data Types can be represented using 1-byte, or two 2-byte such that 1-byte Data Types are forward compatible with 2-byte Types. Given there are only 8, 16, 32, and 64-bit CPUs, the bit pattern of the data type is required to be laid out such that the bit_1 of the 4 bits required to represent these 4 byte depths shall be laid out across the boundary between a IUA and IUB word boundaries.

## POD Types Table

The POD Types table is laid out such that the types are grouped into groups by width growing from NIL to the 16-byte types, and beyond the 16-byte types shall be CPU word-aligned POD types that shall be defined by the target implementation[10].

| ID | Type | C++/Alt Name | Width | Description |
|:--:|:----:|:------------:|:-----:|:------------|
|  0 | NIL  |     null     |   0   | Nil/null/void type. |
|  1 | IUA  |    uint8_t   |   1   | 1-byte unsigned integer. |
|  2 | ISA  |     int8_t   |   1   | 1-byte signed integer. |
|  3 | CHA  |     char     |   1   | 1-byte Unicode/ASCII character. |
|  4 | FPB  |     half     |   2   | 2-byte floating-point number. |
|  5 | IUB  |   uint16_t   |   2   | 2-byte unsigned integer. |
|  6 | ISB  |    int16_t   |   2   | 2-byte signed integer. |
|  7 | CHB  |   char16_t   |   2   | 2-byte Unicode character. |
|  8 | FPC  |    float     |   4   | 4-byte floating-point number. |
|  9 | IUC  |   uint32_t   |   4   | 4-byte unsigned integer. |
| 10 | ISC  |    int32_t   |   4   | 4-byte signed integer. |
| 11 | CHC  |   char32_t   |   4   | 4-byte Unicode character. |
| 12 | FPD  |    double    |   8   | 8-byte floating-point number. |
| 13 | IUD  |   uint64_t   |   8   | 8-byte unsigned integer. |
| 14 | ISD  |    int64_t   |   8   | 8-byte signed integer. |
| 15 | TMD  |    int64_t   |   8   | 8-byte timestamp with ISC second and IUC sub-second tick. |
| 16 | FPE  |  float128_t  |  16   | 16-byte floating-point number. |
| 17 | IUE  |   uint128_t  |  16   | 16-byte unsigned integer. |
| 18 | ISE  |   int128_t   |  16   | 16-byte signed integer. |
| 19 | TME  |   uint128_t  |  16   | 16-byte Linear ID Universally Unique Identifier. |
| 20 | PTa  |      ?       |   ?   | Plain Type a. |
| 21 | PTb  |      ?       |   ?   | Plain Type b. |
| 22 | PTc  |      ?       |   ?   | Plain Type c. |
| 23 | PTd  |      ?       |   ?   | Plain Type d. |
| 24 | PTe  |      ?       |   ?   | Plain Type e. |
| 25 | PTf  |      ?       |   ?   | Plain Type f. |
| 26 | PTg  |      ?       |   ?   | Plain Type g. |
| 27 | PTh  |      ?       |   ?   | Plain Type h. |
| 28 | PTi  |      ?       |   ?   | Plain Type i. |
| 29 | PTj  |      ?       |   ?   | Plain Type j. |
| 30 | PTk  |      ?       |   ?   | Plain Type k. |
| 31 | PTl  |      ?       |   ?   | Plain Type l. |

### List of Types Key

| Width | Description |
|:-----:|:------------|
|   ?   | Nil-terminated string type. |
|   x   | The numbers 0, 1, 2, 4, 8, and 16 are the number of bytes in the type. |
|   xW  | Word-aligned size determined by implementation. |

### Justification for Ordering

The table logic is based on the fact that there are only three types of Unicode character types, 8-bit, 16-bit, and 32-bit, and there are only four main types of floating-point numbers, 16-bit, 32-bit, 64-bit, and 128-bit. We always know that 0 will be nil, so thus we may conclude that FPB must be in index 4 because there is no such thing as an 8-bit floating-point number.

It doesn't make sense to start out with FPx, CHx, ISx, IUx, so it must start out either FPx, ISx, IUx, or FPx, IUx, ISx, but you cannot create a signed integer without an unsigned inter, and thus the unsigned integers must come first, yielding the order FPx, IUx, ISx CHx,.

We require a special type for a 64-bit timestamp. With the above order packing there is no room for a 4-bit timestamp, but there is no 64-bit Unicode character value, and thus we may conclude that TME is required to be Type 15.

This leaves one type left we can use to store our BOL type, which is Type 19. After that are all implementation-defined types the user can place any other types where they see fit; and it's arguable that you really actually need any other POD data types for the vast majority of foreseeable of applications.

## VT Bits

The Vector types are stored in b6:b5 (mask 0x60) for 1, 2, and 4-byte Data Types. All Data Types are word aligned creating a number of illegal data types, such as an 1-byte Array of 2-byte data types.

| Value | Type | Description                                       |
|:-----:|:----:|:-------------------------------------------------:|
|   0   | VHT  | Vector of 1, 2, 3, or 4 POD types 0-31.           |
|   1   | ARY  | Array of homogenous types.                        |
|   2   | STK  | Stack (vector) of homogenous types.               |
|   3   | MTX  | Matrix (n-dimensional array) of homogenous types. |

## Vector of Homotuples

A VHT or Vector of Homotuple (Homogenous Tuple) is a packed contiguous set of 1, 2, 3, or 4 of any of the POD types 0-31. Homotuples are created when the Vector bits are set to zero where the number of homogenous types in the set are determined by the SW (Size Width) one is added to the SW value to store the number of vector elements.

***Bit Pattern***

2-byte types can be used created a Core Type or a map one Core Type to another such as a STA_FPD (UTF-8 string-to-float) map or a CHA_BOL (char-to-bool) map. To create a single core type set the Size Width (SW) bits of the ASCII Data Types word to 1:

| b8:b7 | b6:b5  | b4:b0 |
|:-----:|:------:|:-----:|
|  SW   |  VHT   |  POD  |

## One-byte Data Type Bit Pattern

1-byte types only support 2-byte Size Width and are intended for memory constrained processors.

| b7 |       b6:b5       | b4:b0 |
|:--:|:-----------------:|:-----:|
| SW | Vector Type (VT)  |  POD  |

### Size Width Pattern b7

| Value | Type | Description |
|:-----:|:----:|:------------|
|   0   | VHT  | Vector of Homogenous Types 0-31. |
|   1   | SW2  | 2-byte wide size type. |

## Two and Four-byte Type Bit Pattern

The difference between a 4-byte and a 2-byte data type are that the 4-byte data type can support heterogeneous tuples. 1 and 2-byte data types both support up to 4 heterogeneous types

### SW Bits

The Size width (SW) bits stores the number of bits uses to store the Object Array Size. If the the number of bits is zero then it is a POD Data Type.

| Value | Type | Description                                                 |
|:-----:|:----:|:------------------------------------------------------------|
|   0   | VHT  | 1, 2, 3, and 4-tuple of POD types 0-31.                     |
|   1   | SWB  | 2-byte (2-byte) size-width type, or String Type 1 (UTF-8).  |
|   2   | SWC  | 4-byte (4-byte) size-width type, or String Type 2 (UTF-16). |
|   3   | SWD  | 8-byte (8-byte) size-width type, or String Type 3 (UTF-32). |

## Illegal Types

### MT Bits

A Map Type maps from of one POD type to other set, such as a Dictionary that maps a string, an integer hash, or floating-point number to an unsigned integer offset. Map Types are covered in the [Map Types](MapTypes) section. MT Bits contain a POD type A such that A maps to B.

### MOD Bits

The Modifier Bits (MOD) allow for the creation of pointers and const pointers to POD and Vector types.

| Value | Type | Description           |
|:-----:|:----:|:----------------------|
|   0   | CNS  | Const.                |
|   1   | PTC  | Const Crabs pointer.  |
|   2   | CTG  | Contiguous data.      |
|   3   | PTR  | Crabs Crabs pointer.  |

## Two-byte Type Bit Pattern

2-byte types can be used created a POD Type or a map one POD Type to another such as a STA_FPC (string-to-float in C++) map or a CHA_BOL (char-to-bool in C++) map. To create a single POD type set the Map type to 0.

| b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
|:-------:|:------:|:-----:|:-----:|:-----:|
|   MOD   |   MT   |  SW   |  VT   |  POD  |

|  b15  | b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
|:-----:|:---:|:------:|:-----:|:-----:|:-----:|
| Const | PTR |   MT   |  SW   |  VT   |  POD  |

1. POD: Plain Old Data bits
2. VT: Vector Type bits
3. SW: Size Width bits
4. MT: Map Type bits
5. MOD: Modifier bits

## Variable Byte Lengths

Variable Byte Length (VBL) Types 1 to 2048 bytes long are created when the five Least Significant bits of any 16-bit ASCII Type are 0. The size is calculated by shifting the byte to the right 5 bits (i.e. shift bit_5 into bit-0).

## Plain Types

Plain Types PTa through PTl are implementation defined and may be 8, 16, 32, 64, or 128-bits wide. Plain types must be sorted descending by width, which is reverse order from POD types 1 through 18. All Plain Types except for 8-bit Plain Types can be deleted, which would make all of the Plain Data types 8-bit, hence why they are reverse sorted.

Plain Types are set by defining the last Plain Type index of that size such that `CT0 = 31 >= CT1 >= CT2 >= CT3 >= CT4 >= CT5 > 19`. When the machine is configured these values are CT0_STOP, CT1_STOP, CT2_STOP, CT3_STOP, CT4_STOP, and CT5_STOP respectively. After the machine has been configured the codes then turn into integer values _CT0, _CT1, _CT2, _CT3, _CT4, and _CT5.

To delete all 128-bit Plain Types set CT4_STOP to BOL (19). To delete all 64-bit Plain Types set CT3_STOP to CT4_STOP. To delete all 32-bit Plain Types set CT2_STOP to CT3_STOP. To delete all 16-bit Plain Types set CT1_STOP to CT2_STOP. All unspecified Plain Types are then 8-bit types that cannot be deleted.

**[<< Previous Section: ASCII Data Specification Overview](./)  |  [Next Section: Extended Types >>](ExtendedTypes.md)**

## Requirements

[1]: ../Requirements#Optimal-Transceiving

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
