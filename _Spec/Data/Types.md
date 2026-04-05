# Standard Types

ASCII Data Types use 3-letter acronyms in all capital letters[1][2]. Whenever possible, the letters in the ASCII Data Type acronyms are such that like-types are grouped alphabetically, and 8, 16, 32, 64, and 128-bit types use the post fix A, B, C, D, and E, and an 8-bit unsigned integer is a IUA and a 16-bit one is a IUB.

Data Types can be represented using 1-byte, or two 2-byte such that 1-byte Data Types are forward compatible with 2-byte Types. Given there are only 8, 16, 32, and 64-bit CPUs, the bit pattern of the data type is required to be laid out such that the bit_1 of the 4 bits required to represent these 4 byte depths shall be laid out across the boundary between a IUA and IUB word boundaries.

## POD Types Table

| ID | Type | C++/Alt Name | Width | Description                     |
|:--:|:----:|:------------:|:-----:|:--------------------------------|
|  0 | NIL  |     void     |   0   | Null/zilch/nada/nothing.        |
|  1 | IUA  |    uint8_t   |   1   | 1-byte unsigned integer.        |
|  2 | ISA  |     int8_t   |   1   | 1-byte signed integer.          |
|  3 | CHA  |     char     |   1   | 1-byte Unicode/ASCII character. |
|  4 | FPB  |     half     |   2   | 2-byte floating-point number.   |
|  5 | IUB  |   uint16_t   |   2   | 2-byte unsigned integer.        |
|  6 | ISB  |    int16_t   |   2   | 2-byte signed integer.          |
|  7 | CHB  |   char16_t   |   2   | 2-byte Unicode character.       |
|  8 | FPC  |    float     |   4   | 4-byte floating-point number.   |
|  9 | IUC  |   uint32_t   |   4   | 4-byte unsigned integer.        |
| 10 | ISC  |    int32_t   |   4   | 4-byte signed integer.          |
| 11 | CHC  |   char32_t   |   4   | 4-byte Unicode character.       |
| 12 | FPD  |    double    |   8   | 8-byte floating-point number.   |
| 13 | IUD  |   uint64_t   |   8   | 8-byte unsigned integer.        |
| 14 | ISD  |    int64_t   |   8   | 8-byte signed integer.          |
| 15 | SSD  |    int64_t   |   8   | 8-byte Subsecond Id timestamp.  |
| 16 | FPE  |  float128_t  |  16   | 16-byte floating-point number.  |
| 17 | IUE  |   uint128_t  |  16   | 16-byte unsigned integer.       |
| 18 | ISE  |   int128_t   |  16   | 16-byte signed integer.         |
| 19 | SSE  |   uint128_t  |  16   | 16-byte Subsecond Id timestamp. |
| 20 | PCa  |      ?       |   ?   | Plain Context Type a.           |
| 21 | PCb  |      ?       |   ?   | Plain Context Type b.           |
| 22 | PCc  |      ?       |   ?   | Plain Context Type c.           |
| 23 | PCd  |      ?       |   ?   | Plain Context Type d.           |
| 24 | PCe  |      ?       |   ?   | Plain Context Type e.           |
| 25 | PCf  |      ?       |   ?   | Plain Context Type f.           |
| 26 | PCg  |      ?       |   ?   | Plain Context Type g.           |
| 27 | PCh  |      ?       |   ?   | Plain Context Type h.           |
| 28 | PCi  |      ?       |   ?   | Plain Context Type i.           |
| 29 | PCj  |      ?       |   ?   | Plain Context Type j.           |
| 30 | PCk  |      ?       |   ?   | Plain Context Type k.           |
| 31 | PCl  |      ?       |   ?   | Plain Context Type l.           |

### List of Types Key

| Width | Description |
|:-----:|:------------|
|   ?   | Context dependent and remapped to another POD type. |
|   x   | The numbers 0, 1, 2, 4, 8, and 16 are the number of bytes in the type. |

### Justification for Ordering

The table logic is based on the fact that there is no 64-bit Unicode character. The POD types cycle though float, unsigned, signed, or { char or timestamp }. It's kind of arbitrary which metric to use to sort the table, but the chosen metric  is to use a 2-bit pattern where bit 1 means it's signed int and bit 0 means it's unsigned int. When neither are asserted, it's not an signed or unsigned, so it's a float. When only bit 0 is asserted, it's an unsigned, when only bit 1 is asserted it's a signed. A char and be both signed and unsigned because it could be an 8-bit signed ASCII value, or an 8-bit unsigned extended ASCII value. A TMD timestamp is also a combination of a signed timestamp and unsigned sub-second ticker. A 128-bit linear id is also signed timestamp with a 20-bit sub-second ticker and a 64-bit source id.

## VT Bits

The Vector types are stored in b6:b5 (mask 0x60) for 1, 2, and 4-byte Data Types. All Data Types are word aligned creating a number of illegal data types, such as an 1-byte Array of 2-byte data types.

| Value | Type | Description                                       |
|:-----:|:----:|:-------------------------------------------------:|
|   0   | VHT  | Vector of 1, 2, 3, or 4 POD types 0-31.           |
|   1   | ARY  | Array of homogenous types.                        |
|   2   | SCK  | Stack of homogenous types or String.              |
|   3   | MAT  | Matrix (n-dimensional array) of homogenous types. |

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

### MWT Bits

A Map Type maps from of one POD type to other set, such as a Dictionary that maps a string, an integer hash, or floating-point number to an unsigned integer offset. Map Types are covered in the [Map Types](MapTypes) section. MWT Bits contain a POD type A such that A maps to B.

### MOD Bits

The Modifier (MOD) Bits turn in the 13 LSb into either a SEC, FPV (Void Floating-point), CHV (Unsigned Void Character), or ISV Void Signed Integer numbers.

| Value | Type | Description            |
|:-----:|:----:|:-----------------------|
| 00/0  | SEC  | Standard, Extended, and Context Types. |
| 01/1  | FPV  | r-bit Void float. |
| 10/2  | CHV  | r-bit Void unsigned char. |
| 11/3  | ISV  | (r-1)-bit Void signed integer or Extended Block Type. |

## Bit Pattern

2-byte types can be used created a POD Type or a map one POD Type to another such as a STA_FPC (string-to-float in C++) map or a CHA_BOL (char-to-bool in C++) map. To create a single POD type set the Map type to 0.

The One-byte, Two-be, Three-four, and Eight-byte ASCII Data Type bit patterns all use the same legend:

| Bit Group Code | Name                 |
|:--------------:|:---------------------|
|      POD       | Plain Old Data bits. |
|      VT        | Vector Type bits.    |
|      SW        | Size Width bits.     |
|      MT        | Map Type bits.       |
|      MD        | Modifier bits.       |
|      CNS       | Constant.            |
|      SPC       | Super 32-bit Types.  |
|      SPD       | Super 64-bit Types.  |

### Two-byte Type Bit Pattern

The two-byte type bit pattern uses r=13-bit.

| b15 | b14:b13 | b12:b9 | b8:b7 | b6:b5 | b4:b0 |
|:---:|:-------:|:------:|:-----:|:-----:|:-----:|
| CNS |    MD   |   MT   |  SW   |  VT   |  POD  |

### Four-byte Type Bit Pattern

The Four-byte Type bit pattern uses the same layout as the two-byte pattern with the exception that SPC turn the FPV, CHV, and ISV into r=29-bit void types spanning b30:b0, and the extra bits on row 0 of the SPC bits when the MOD bits is 0 become the 16-bit SPC (SuperC or Super32 Types) Types.

| b31 | b30:b29 | b28:b13 | b12:b9 | b8:b7 | b6:b5 | b4:b0 |
|:---:|:-------:|:-------:|:------:|:-----:|:-----:|:-----:|
| CNS |    MD   |   SPC   |   MT   |  SW   |  VT   |  POD  |

### Eight-byte Type Bit Pattern

The Eight-byte Type bit pattern uses the same layout as the two-byte pattern with the exception that SPC turn the FPV, CHV, and ISV into 61-bit void types, and the extra bits on row 0 of the SPD (SuperD or Super64 Types) bits when the MOD bits is 0 become the SuperD Types.

| b63 | b62:b61 | b60:b13 | b12:b9 | b8:b7 | b6:b5 | b4:b0 |
|:---:|:-------:|:-------:|:------:|:-----:|:-----:|:-----:|
| CNS |    MD   |   SPD   |   MT   |  SW   |  VT   |  POD  |

## Variable Byte Lengths

Variable Byte Length (VBL) Types 1 to 2048 bytes long are created when the five Least Significant bits of any 16-bit ASCII Type are 0. The size is calculated by shifting the byte to the right 5 bits (i.e. shift bit_5 into bit-0).

## Plain Context Types

Plain Context Types PCa through PCl are implementation defined and may be 8, 16, 32, 64, or 128-bits wide. Plain types must be sorted descending by width, which is reverse order from POD types 1 through 18. All Plain Context Types except for 8-bit Plain Context Types can be deleted, which would make all of the Plain Data types 8-bit, hence why they are reverse sorted.

### Concrete Type Definitions

The following concrete definitions are recommended for Plain Context Types:

| Type | Width | Purpose | Usage |
|:----:|:-----:|:--------|:------|
| PCa | 128-bit | Extended Context Storage | Large-scale context data for complex operations |
| PCb | 64-bit | Context Pointer | Pointer to context data structures |
| PCc | 32-bit | Context Index | Index into context tables |
| PCd | 16-bit | Context Tag | Tag for context classification |
| PCe | 8-bit | Context Flag | Boolean flag for context state |
| PCf | 8-bit | Context Modifier | Additional context modifier bits |
| PCg | 8-bit | Context Reserved | Reserved for future use |
| PCh | 8-bit | Context Reserved | Reserved for future use |
| PCi | 8-bit | Context Reserved | Reserved for future use |
| PCj | 8-bit | Context Reserved | Reserved for future use |
| PCk | 8-bit | Context Reserved | Reserved for future use |
| PCl | 8-bit | Context Reserved | Reserved for future use |

### Configuration and Deletion

Plain Context Types are set by defining the last Plain Type index of that size such that `CT0 = 31 >= CT1 >= CT2 >= CT3 >= CT4 >= CT5 > 19`. When the machine is configured these values are CT0_STOP, CT1_STOP, CT2_STOP, CT3_STOP, CT4_STOP, and CT5_STOP respectively. After the machine has been configured the codes then turn into integer values _CT0, _CT1, _CT2, _CT3, _CT4, and _CT5.

To delete all 128-bit Plain Context Types set CT4_STOP to BOL (19). To delete all 64-bit Plain Context Types set CT3_STOP to CT4_STOP. To delete all 32-bit Plain Context Types set CT2_STOP to CT3_STOP. To delete all 16-bit Plain Context Types set CT1_STOP to CT2_STOP. All unspecified Plain Context Types are then 8-bit types that cannot be deleted.

### Usage Examples

```C++
// Example: Using Plain Context Types for context management
struct Context {
  PCa extended_data;      // 128-bit extended context
  PCb context_ptr;        // 64-bit pointer to context structure
  PCc context_index;      // 32-bit index into context table
  PCd context_tag;        // 16-bit context classification tag
  PCe context_flag;       // 8-bit boolean flag
  PCf context_modifier;   // 8-bit modifier bits
};
```
