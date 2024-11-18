# Extended Types

Extended ASCII Types are contiguous types that use offsets such that ISZ means the largest signed integer, ISY is half the size of ISZ, and so on to IST. Because ISY and subsequent signed integer types must be half the size of the prior post-fixed letter type, the legal types are packed up contiguously in ascending order. The ASCII Code for the type is when the last character is a letter. Implementations may map the all-letter Extended ASCII Type code to one of the number post-fix ASCII Types to set the Default Extended Type for that implementation; for example thd default DIC may be DI4 and on that implementation DIC is the same integer value as DI4. The Extended ASCII Types are:

All ASCII Data Non-POD Types shall be memory aligned all systems. Some combinations of ASCII Data Types are illegal because they are not word aligned, such as an 8-bit Array of 16-bit types. Users also cannot create a pointer to a NIL type, so there are 15 illegal types mapping a POD type to NIL.

Context Types DTa through CTA through CTL are not defined at this level and those data types may or may not be legal, so they are Context Types that are different in each Chinese Room Wall.

There are a total of 207 Illegal Types that are remapped to 135 [Extended Types](ExtendedTypes.md) and 72 [Context Types](#ContextTypes).

```AsciiArt
| Vector |     POD Type 0-31 (1=Valid, 0=Extended Types, ?=User Types)      |
| Type   | N I I C F I I C F I I C T I I F  F I I T C C C D C C C C C C C C |
| SW:VT  | I U I H P U S H P U S H M U S P  P U S M T T T T T T T T T T T T |
| b8:b5  | L A A A B B B B C C C C D D D D  E E E E A B C D E F G H I J K L |
+--------+------------------------------------------------------------------|
|  8_VHA | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
|  8_ARY | 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
|  8_STK | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
|  8_MAT | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 16_VHB | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 16_ARY | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 16_STK | 0 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 16_MAT | 0 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_VHC | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 32_ARY | 0 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_STK | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_MAT | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 64_VHD | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_ARY | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_STK | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_MAT | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
+--------+------------------------------------------------------------------|
| Total  | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  512   |      Type 0-31      0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
```

## Remapping Algorithm

Remapping 14-bit ASCII Data Type bit pattern to the Extended Types shall be fast as possible. Types are remapped in blocks in order A through H in the table bellow.

The fastest Extended Types to decode is the A column, which are remap transposed to E01 through E0F amd does not require shifting. The rest of the mappings only require subtracting or adding to the lower 5 bits to shift into place. B and C don't require any shifting. Types 1 through 135 are mapped to Extended Types and 136 through 135 are Context Types. This allows a signed integer to return either the Standard or Extended Type with where the Standard Type is positive and the Extended Types are negative.

```AsciiArt
| Vector |      POD Type 0-31 (.=Valid A-H=Order to convert blocks in)      |
| Type   | N I I C F I I C F I I C F I I T  F I I T C C C D C C C C C C C C |
| SW:VT  | I U I H P U S H P U S H P U S M  P U S M T T T T T T T T T T T T |
| b8:b5  | L A A A B B B B C C C C D D D D  E E E E A B C D E F G H I J K L |
+--------+------------------------------------------------------------------|
|  8_VHA | . . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|  8_ARY | A . . . H H H H B B B B B B B B  B B B B B B B B B B B B B B B B |
|  8_STK | A . . . . . . . B B B B B B B B  B B B B B B B B B B B B B B B B |
|  8_MAT | A . . . . . . . B B B B B B B B  B B B B B B B B B B B B B B B B |
| 16_VHB | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
| 16_ARY | A . . . . . . . H H H H F F F F  F F F F D D D D C C C C C C C C |
| 16_STK | A . . . . . . . . . . . F F F F  F F F F D D D D C C C C C C C C |
| 16_MAT | A . . . . . . . . . . . F F F F  F F F F D D D D C C C C C C C C |
| 32_VHC | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
| 32_ARY | A . . . . . . . . . . . H H H H  G G G G E E E E C C C C C C C C |
| 32_STK | A . . . . . . . . . . . . . . .  G G G G E E E E C C C C C C C C |
| 32_MAT | A . . . . . . . . . . . . . . .  H H H H E E E E C C C C C C C C |
+--------+------------------------------------------------------------------|
| Total  | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  512   |      Type 0-31      0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
```

## Remapped Extended Types 1-135

```AsciiArt
| Total | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  135  | Extended Type 0-31  0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
+-------+------------------------------------------------------------------|
|  000  | x A A A A A A A A A A A A A A A  H H H H H H H H H H H H H H H H |
|  001  | F F F F F F F F B B B B B B B B  B B B B B B B B B B B B B B B B |
|  010  | F F F F F F F F B B B B B B B B  B B B B B B B B B B B B B B B B |
|  011  | F F F F F F F F B B B B B B B B  B B B B B B B B B B B B B B B B |
|  111  | G G G G G G G x x x x x x x x x  x x x x x x x x x x x x x x x x |
+-------+------------------------------------------------------------------|
```

## Remapped Context Types 136-208

```AsciiArt
| Total | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  72   | Extended Type 0-31  0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
+-------+------------------------------------------------------------------|
|  00   | E E E E D D D D C C C C C C C C  C C C C C C C C C C C C C C C C |
|  01   | E E E E D D D D C C C C C C C C  C C C C C C C C C C C C C C C C |
|  10   | E E E E D D D D x x x x x x x x  x x x x x x x x x x x x x x x x | 
+-------+------------------------------------------------------------------|
```

## Extended Types Table

| ID  |  Type   |    Name    | Description |
|:---:|:-------:|:----------:|:------------|
| 000 |   IMP   | Impossible | Impossible type. |
| 001 |   INV   |  Invalid   | Invalid type. |
| 002 |   BOB   |  Boolean   | 2-byte BOL value. |
| 003 |   BOC   |  Boolean   | 4-byte BOL value. |
| 004 |   DTA   | Data Type  | 8-bit ASCII Data Type. |
| 005 |   DTB   | Data Type  | 16-bit ASCII Data Type. |
| 006 |   DTC   | Data Type  | Two contiguous 16-bit ASCII Data Types. |
| 007 |   DTD   | Data Type  | Three contiguous 16-bit ASCII Data Types. |
| 008 |   OBA   |  Object    | 1-byte size-width contiguous object. |
| 009 |   OBB   |  Object    | 2-byte size-width contiguous object. |
| 010 |   OBC   |  Object    | 4-byte size-width contiguous object. |
| 011 |   OBD   |  Object    | 8-byte size-width contiguous object. |
| 012 |   BSA   |   BSQ      | 1-byte total B-Sequence.|
| 013 |   BSB   |   BSQ      | 2-byte total B-Sequence.|
| 014 |   BSC   |   BSQ      | 4-byte total B-Sequence.|
| 015 |   BSD   |   BSQ      | 8-byte total B-Sequence.|
| 016 |   LS0   |   List     | TList<ISB, ISA, DTB>. |
| 017 |   LS1   |   List     | TList<ISC, ISB, DTB>. |
| 018 |   LS2   |   List     | TList<ISD, ISC, DTB>. |
| 019 |   ...   |     ...    | ...|
| 010 |   TB0   |   Table    | TTable<ISC, ISB, IUC>.|
| 021 |   TB1   |   Table    | TTable<ISC, ISB, IUC>.|
| 022 |   TB2   |   Table    | TTable<ISC, ISB, IUD>.|
| 023 |   TB3   |   Table    | TTable<ISC, ISB, IUD>.|
| 024 |   DI0   | Dictionary | TDic<CHA, ISC, ISB, IUC, DTB>. |
| 025 |   DI1   | Dictionary | TDic<CHA, ISD, ISC, IUD, DTB>. |
| 026 |   DI2   | Dictionary | TDic<CHB, ISC, ISB, IUC, DTB>. |
| 027 |   DI3   | Dictionary | TDic<CHB, ISD, ISC, IUD, DTB>. |
| 028 |   DI4   | Dictionary | TDic<CHC, ISC, ISB, IUC, DTB>. |
| 029 |   DI5   | Dictionary | TDic<CHC, ISD, ISC, IUD, DTB>. |
| 030 |   BO0   |    Book    | TBook<CHA, ISB, ISA, DTB>. |
| 031 |   BO1   |    Book    | TBook<CHA, ISC, ISB, DTB>. |
| 032 |   BO2   |    Book    | TBook<CHA, ISD, ISC, DTB>. |
| 033 |   BO3   |    Book    | TBook<CHB, ISB, ISA, DTB>. |
| 034 |   BO4   |    Book    | TBook<CHB, ISC, ISB, DTB>. |
| 035 |   BO5   |    Book    | TBook<CHB, ISD, ISC, DTB>. |
| 036 |   BO6   |    Book    | TBook<CHC, ISB, ISA, DTB>. |
| 037 |   BO7   |    Book    | TBook<CHC, ISC, ISB, DTB>. |
| 038 |   BO8   |    Book    | TBook<CHC, ISD, ISC, DTB>. |
| 039 |         |            | .|
| 040 |   ERA   |   Error    | 1-byte Error type. |
| 041 |   ERB   |   Error    | 2-byte Error type. |
| 042 |   ERC   |   Error    | 4-byte Error type. |
| 043 |   ERD   |   Error    | 8-byte Error type. |
| 044 |   EOA   | Err Object | 1-byte size-width Error type. |
| 045 |   EOB   | Err Object | 2-byte size-width Error type. |
| 046 |   EOC   | Err Object | 4-byte size-width Error type. |
| 047 |   EOD   | Err Object | 8-byte size-width Error type. |
|  |   ...   |     ...    | ...|
| 128 |  IUF    |    256     | 32-byte unsigned integer. |
| 129 |  IUG    |    512     | 64-byte unsigned integer. |
| 130 |  IUH    |   1024     | 128-byte unsigned integer. |
| 131 |  IUI    |   2048     | 256-byte unsigned integer. |
| 132 |  IUJ    |   4096     | 512-byte unsigned integer. |
| 133 |  IUK    |   8192     | 1024-byte unsigned integer. |
| 134 |  IUL    |   16384    | 2048-byte unsigned integer. |
| 135 |  IUM    |   32768    | 4096-byte unsigned integer. |


|  Type   |    Name    | Description |
|:-------:|:----------:|:------------|
|   LOM   |    Loom    | An array of strings. |
|   LST   |    List    | A collection of type-value tuples. |
|   BOK   |    Book    | An associative list without a hash-table. |
|   DIC   | Dictionary | An associative list with a hash-table. |
|   BSQ   | B-Sequence | Header for a sequence of bytes. |
|   BIN   |  B-Input   | A Byte-input ring buffer socket. |
|   BOU   |  B-Output  | A Byte-output ring buffer socket. |
|   SLT   |    Slot    | A slot in a Door with a BIn and BOut to pass messages. |

**[<< Previous Section: Types](Types.md) | [Next Section: Numbers >>](Numbers.md)**

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
