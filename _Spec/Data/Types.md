# [SCRIPT Specification](../)

## [ASCII Data Specification](./)

### Types

ASCII Data Types use 3-letter acronyms in all capital letters[1][2]. Whenever possible, the letters in the ASCII Data Type acronyms are such that like-types are grouped alphabetically, and 8, 16, 32, 64, and 128-bit types use the post fix A, B, C, D, and E, and an 8-bit unsigned integer is a IUA and a 16-bit one is a IUB. Data Types can be represented using 1-byte, or two 2-byte such that 1-byte Data Types are forward compatible with 2-byte Types. Given there are only 8, 16, 32, and 64-bit CPUs, the bit pattern of the data type is required to be laid out such that the bit_1 of the 4 bits required to represent these 4 byte depths shall be laid out across the boundary between a IUA and IUB word boundaries.

#### POD Types Table

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
| 20 | CTA  |  Data Type A |   ?   | Custom Data Type A. |
| 21 | CTB  |  Data Type B |   ?   | Custom Data Type B. |
| 22 | CTC  |  Data Type C |   ?   | Custom Data Type C. |
| 23 | CTD  |  Data Type D |   ?   | Custom Data Type D. |
| 24 | CTE  |  Data Type E |   ?   | Custom Data Type E. |
| 25 | CTF  |  Data Type F |   ?   | Custom Data Type F. |
| 26 | CTG  |  Data Type G |   ?   | Custom Data Type G. |
| 27 | CTH  |  Data Type H |   ?   | Custom Data Type H. |
| 28 | CTK  |  Data Type I |   ?   | Custom Data Type I. |
| 29 | CTJ  |  Data Type J |   ?   | Custom Data Type J. |
| 30 | CTK  |  Data Type K |   ?   | Custom Data Type K. |
| 31 | CTL  |  Data Type L |   ?   | Custom Data Type L. |

##### List of Types Key

| Width | Description |
|:-----:|:------------|
|   ?   | Nil-terminated string type. |
|   x   | The numbers 0, 1, 2, 4, 8, and 16 are the number of bytes in the type. |
|   xW  | Word-aligned size determined by implementation. |

##### Justification for Ordering

The table logic is based on the fact that there are only three types of Unicode character types, 8-bit, 16-bit, and 32-bit, and there are only four main types of floating-point numbers, 16-bit, 32-bit, 64-bit, and 128-bit. We always know that 0 will be nil, so thus we may conclude that FPB must be in index 4 because there is no such thing as an 8-bit floating-point number.

It doesn't make sense to start out with FPx, CHx, ISx, IUx, so it must start out either FPx, ISx, IUx, or FPx, IUx, ISx, but you cannot create a signed integer without an unsigned inter, and thus the unsigned integers must come first, yielding the order FPx, IUx, ISx CHx,.

We require a special type for a 64-bit timestamp. With the above order packing there is no room for a 4-bit timestamp, but there is no 64-bit Unicode character value, and thus we may conclude that TME is required to be Type 15.

This leaves one type left we can use to store our BOL type, which is Type 19. After that are all implementation-defined types the user can place any other types where they see fit; and it's arguable that you really actually need any other POD data types for the vast majority of foreseeable of applications.

#### VT Bits

The Vector types are stored in b6:b5 (mask 0x60) for 1, 2, and 4-byte Data Types. All Data Types are word aligned creating a number of illegal data types, such as an 1-byte Array of 2-byte data types.

| Value | Type | Description                                       |
|:-----:|:----:|:-------------------------------------------------:|
|   0   | VHT  | Vector of 1, 2, 3, or 4 POD types 0-31.           |
|   1   | ARY  | Array of homogenous types.                        |
|   2   | STK  | Stack (vector) of homogenous types.               |
|   3   | MTX  | Matrix (n-dimensional array) of homogenous types. |

#### Homotuples

A Homotuple (Homogenous Tuple) is a Vector of homogeneous types of length 1, 2, 3, or 4. Homotuples are created when the Vector bits are set to zero where the number of homogenous types in the set are determined by the SW (Size Width) one is added to the SW value to store the number of vector elements.

***Bit Pattern***

2-byte types can be used created a Core Type or a map one Core Type to another such as a STA_FPD (UTF-8 string-to-float) map or a CHA_BOL (char-to-bool) map. To create a single core type set the Size Width (SW) bits of the ASCII Data Types word to 1:

| b8:b7 | b6:b5  | b4:b0 |
|:-----:|:------:|:-----:|
|  SW   |  VHT   |  POD  |

#### One-byte Data Type Bit Pattern

1-byte types only support 2-byte Size Width and are intended for memory constrained processors.

| b7 |       b6:b5       | b4:b0 |
|:--:|:-----------------:|:-----:|
| SW | Vector Type (VT)  |  POD  |

##### Size Width Pattern b7

| Value | Type | Description |
|:-----:|:----:|:------------|
|   0   | VHT  | Vector of Homogenous Types 0-31. |
|   1   | SW2  | 2-byte wide size type. |

#### Two and Four-byte Type Bit Pattern

The difference between a 4-byte and a 2-byte data type are that the 4-byte data type can support heterogeneous tuples. 1 and 2-byte data types both support up to 4 heterogeneous types

##### SW Bits

The Size width (SW) bits stores the number of bits uses to store the Object Array Size. If the the number of bits is zero then it is a POD Data Type.

| Value | Type | Description                                                 |
|:-----:|:----:|:------------------------------------------------------------|
|   0   | VHT  | 1, 2, 3, and 4-tuple of POD types 0-31.                     |
|   1   | SWB  | 2-byte (2-byte) size-width type, or String Type 1 (UTF-8).  |
|   2   | SWC  | 4-byte (4-byte) size-width type, or String Type 2 (UTF-16). |
|   3   | SWD  | 8-byte (8-byte) size-width type, or String Type 3 (UTF-32). |

##### Illegal Vector Types

Extended types are created by the Illegal Types. All ASCII data types shall be memory aligned on 8, 16, 32, and 64-bit systems. The Illegal Types are types that are not memory aligned on all processors, such as a Stack of ISB with an ISA size width. Users cannot create a pointer to a NIL type. Custom types BOL and DTA through DTL are not defined at this level, so there are illegal and potentially illegal types which are remapped to the Extended ASCII Types and Extended Custom Types.

```AsciiArt
| Vector |     POD Type 0-31 (1=Valid, 0=Extended Types, ?=User Types)      |
|  Type  | N I I C F I I C F I I C T I I F  F I I T C C C D C C C C C C C C |
| SW:VET | I U I H P U S H P U S H M U S P  P U S M T T T T T T T T T T T T |
| b8:b5  | L A A A B B B B C C C C D D D D  E E E E A B C D E F G H I J K L |
+--------+------------------------------------------------------------------|
|  8_VHA | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
|  8_ARY | 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
|  8_STK | 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
|  8_MAT | 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 16_VHT | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 16_ARY | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 16_STK | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 16_MAT | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_VHB | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 32_ARY | 0 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_STK | 0 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_MAT | 0 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 64_VHC | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_ARY | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_STK | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_MAT | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
+--------+------------------------------------------------------------------|
| Total  | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  512   |      Type 0-31      0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
```

| b13:b9 | b8:b7 | b6:b5 | b4:b0 |
|:------:|:-----:|:-----:|:-----:|
|  MT    |  SW   |  VT   |  POD  |
|  CHA   |   8   |  ARY  |  CHA  |
|  CHA   |  16   |  ARY  |  CHA  |
|  CHA   |  32   |  ARY  |  CHA  |

| Exists | Binary | Missing                   |
|:------:|:------:|:-------------------------:|
|    1   | 0b0001 |                           |
|    2   | 0b0010 | 3                         |
|    4   | 0b0100 | 5, 6, 7                   |
|    8   | 0b1000 | 9, 10, 11, 12, 13, 14, 15 |

##### Extended Types

There are a total of 231 Illegal Types with 159 Extended ASCII Types and 72 Extended Custom Types. Extended Custom Types are defined by the implementation.

###### Extended ASCII Types

The Extended ASCII Types are contiguous types that use offsets such that ISZ means the largest signed integer, ISY is half the size of ISZ, and so on to IST. Because ISY and subsequent signed integer types must be half the size of the prior post-fixed letter type, the legal types are packed up contiguously in ascending order. The ASCII Code for the type is when the last character is a letter. Implementations may map the all-letter Extended ASCII Type code to one of the number post-fix ASCII Types to set the Default Extended Type for that implementation; for example thd default DIC may be DI4 and on that implementation DIC is the same integer value as DI4. The Extended ASCII Types are:

| ID  |  Type   |    Name    | Description |
|:---:|:-------:|:----------:|:------------|
|   |   INV   |  Invalid   | Invalid type. |
|   |   BOA   |  Boolean   | 1-byte BOL value. |
|   |   BOB   |  Boolean   | 2-byte BOL value. |
|   |   BOC   |  Boolean   | 4-byte BOL value. |
|   |   DTA   | Data Type  | 8-bit ASCII Data Type. |
|   |   DTB   | Data Type  | 16-bit ASCII Data Type. |
|   |   DTC   | Data Type  | Two contiguous 16-bit ASCII Data Types. |
|   |   DTD   | Data Type  | Three contiguous 16-bit ASCII Data Types. |
|   |   OBA   |  Object    | 1-byte size-width contiguous object. |
|   |   OBB   |  Object    | 2-byte size-width contiguous object. |
|   |   OBC   |  Object    | 4-byte size-width contiguous object. |
|   |   OBD   |  Object    | 8-byte size-width contiguous object. |
|   |   BSA   |   BSQ      | 1-byte total B-Sequence.|
|   |   BSB   |   BSQ      | 2-byte total B-Sequence.|
|   |   BSC   |   BSQ      | 4-byte total B-Sequence.|
|   |   BSD   |   BSQ      | 8-byte total B-Sequence.|
|   |   LS0   |   List     | TList<ISB, ISA, DTB>. |
|   |   LS1   |   List     | TList<ISC, ISB, DTB>. |
|   |   LS2   |   List     | TList<ISD, ISC, DTB>. |
|   |   DI0   | Dictionary | TDic<CHA, ISC, ISB, IUC, DTB>. |
|   |   DI1   | Dictionary | TDic<CHA, ISD, ISC, IUD, DTB>. |
|   |   DI2   | Dictionary | TDic<CHB, ISC, ISB, IUC, DTB>. |
|   |   DI3   | Dictionary | TDic<CHB, ISD, ISC, IUD, DTB>. |
|   |   DI4   | Dictionary | TDic<CHC, ISC, ISB, IUC, DTB>. |
|   |   DI5   | Dictionary | TDic<CHC, ISD, ISC, IUD, DTB>. |
|   |   BO0   |    Book    | TBook<CHA, ISB, ISA, DTB>. |
|   |   BO1   |    Book    | TBook<CHA, ISC, ISB, DTB>. |
|   |   BO2   |    Book    | TBook<CHA, ISD, ISC, DTB>. |
|   |   BO3   |    Book    | TBook<CHB, ISB, ISA, DTB>. |
|   |   BO4   |    Book    | TBook<CHB, ISC, ISB, DTB>. |
|   |   BO5   |    Book    | TBook<CHB, ISD, ISC, DTB>. |
|   |   BO6   |    Book    | TBook<CHC, ISB, ISA, DTB>. |
|   |   BO7   |    Book    | TBook<CHC, ISC, ISB, DTB>. |
|   |   BO8   |    Book    | TBook<CHC, ISD, ISC, DTB>. |
|   |         |            | .|
|   |         |            | .|
| . |   ...   |     ...    | ...|
|   |   ERA   |   Error    | 1-byte Error type. |
|   |   ERB   |   Error    | 2-byte Error type. |
|   |   ERC   |   Error    | 4-byte Error type. |
|   |   ERD   |   Error    | 8-byte Error type. |
|   |   EOA   | Err Object | 1-byte Error type. |
|   |   EOB   | Err Object | 2-byte Error type. |
|   |   EOC   | Err Object | 4-byte Error type. |
|   |   EOD   | Err Object | 8-byte Error type. |


|  Type   |    Name    | Description |
|:-------:|:----------:|:------------|
|   LOM   |    Loom    | An array of strings. |
|   LST   |    List    | A collection of type-value tuples. |
|   BOK   |    Book    | An associative list without a hash-table. |
|   DIC   | Dictionary | An associative list with a hash-table. |
|   BSQ   | B-Sequence | Header for a sequence of bytes. |
|   BIN   |  B-Input   | A Byte-input ring buffer socket. |
|   BOU   |  B-Output  | A Byte-output ring buffer socket. |
|   SLT   |    Slot    | A slot in a Door with a  BIn and BOut to pass messages. |

#### Mandatory User Type

Because boolean type is not well defined, one of the custom types must be BOL and it may be mapped to ISA, ISB, or ISC.

| ID |  Type   |    Name    | Description |
|:--:|:-------:|:----------:|:------------|
| 01 |   BOL   |  Boolean   | A signed integer boolean value. |

##### MT Bits

A Map Type maps from of one POD type to other set, such as a Dictionary that maps a string, an integer hash, or floating-point number to an unsigned integer offset. Map Types are covered in the [Map Types](MapTypes) section. MT Bits contain a POD type A such that A maps to B.

##### MOD Bits

The Modifier Bits (MOD) allow for the creation of pointers and const pointers to POD and Vector types.

| Value | Type | Description           |
|:-----:|:----:|:----------------------|
|   0   | CNS  | Const.                |
|   1   | PTC  | Const Crabs pointer.  |
|   2   | CTG  | Contiguous data.      |
|   3   | PTR  | Crabs Crabs pointer.  |

#### Two-byte Type Bit Pattern

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

#### Variable Byte Lengths

Variable Byte Length (VBL) Types 1 to 2048 bytes long are created when the five Least Significant bits of any 16-bit ASCII Type are 0. The size is calculated by shifting the byte to the right 5 bits (i.e. shift bit_5 into bit-0).

#### Custom Types

Custom Types CTA through CTL are implementation defined and may be 8, 16, 32, 64, or 128-bits wide. Custom types must be sorted descending by width, which is reverse order from POD types 1 through 18. All custom types except for 8-bit custom types can be deleted, which would make all of the custom data types 8-bit, hence why they are reverse sorted.

Custom Types are set by defining the last custom type index of that size such that `CT0 = 31 >= CT1 >= CT2 >= CT3 >= CT4 >= CT5 > 19`. When the machine is configured these values are CT0_STOP, CT1_STOP, CT2_STOP, CT3_STOP, CT4_STOP, and CT5_STOP respectively. After the machine has been configured the codes then turn into integer values _CT0, _CT1, _CT2, _CT3, _CT4, and _CT5.

To delete all 128-bit custom types set CT4_STOP to BOL (19). To delete all 64-bit custom types set CT3_STOP to CT4_STOP. To delete all 32-bit custom types set CT2_STOP to CT3_STOP. To delete all 16-bit custom types set CT1_STOP to CT2_STOP. All unspecified custom types are then 8-bit types that cannot be deleted.

**[<< Previous Section: ASCII Data Specification Overview](./)  |  [Next Section: Numbers >>](Numbers.md)**

## Requirements

[1]: ../Requirements#Optimal-Transceiving

## License

Copyright [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
