# Extended Types

Extended ASCII Types are contiguous types that use offsets such that ISZ means the largest signed integer, ISY is half the size of ISZ, and so on to IST. Because ISY and subsequent signed integer types must be half the size of the prior post-fixed letter type, the legal types are packed up contiguously in ascending order. The ASCII Code for the type is when the last character is a letter. Implementations may map the all-letter Extended ASCII Type code to one of the number post-fix ASCII Types to set the Default Extended Type for that implementation; for example thd default DIC may be DI4 and on that implementation DIC is the same integer value as DI4. The Extended ASCII Types are:

All ASCII Data Non-POD Types shall be memory aligned all systems. Some combinations of ASCII Data Types are illegal because they are not word aligned, such as an 8-bit Array of 16-bit types. Users also cannot create a pointer to a NIL type, so there are 15 illegal types mapping a POD type to NIL.

Context Types DTa through CTA through CTL are not defined at this level and those data types may or may not be legal, so they are Context Types that are different in each Chinese Room Wall.

There are a total of 207 Illegal Types that are remapped to 135 [Extended Types](ExtendedTypes.md) and 72 [Context Types](#ContextTypes).

```AsciiArt
| Vector |     POD Type 0-31 (1=Valid, 0=Extended Types, ?=User Types)      |
| Type   | N I I C F I I C F I I C T I I F  F I I T C C C D C C C C C C C C |
| SW:VT  | I U S H P U S H P U S H M U S P  P U S M T T T T T T T T T T T T |
| b8:b5  | L A A A B B B B C C C C D D D D  E E E E A B C D E F G H I J K L |
+--------+------------------------------------------------------------------|
|  8_VH1 | 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
|  8_ARY | 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
|  8_STK | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
|  8_MAT | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 |
| 16_VH2 | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 16_ARY | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 16_STK | 0 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 16_MAT | 0 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_VH3 | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 32_ARY | 0 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_STK | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_MAT | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 64_VH4 | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_ARY | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_STK | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_MAT | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
+--------+------------------------------------------------------------------|
| Total  | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  512   |      Type 0-31      0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
```

## Remapping Algorithm

Remapping 14-bit ASCII Data Type bit pattern to the Extended Types shall be fast as possible. Types are remapped in blocks in order A through H in the table bellow.

The fastest Extended Types to decode is the A column, which are remap transposed to E01 through E0F amd does not require shifting. The rest of the mappings only require subtracting or adding to the lower 5 bits to shift into place. B and C don't require any shifting. Types 1 through 135 are mapped to Extended Types and 136 through 135 are Context Types. This allows a signed integer to return either the Standard or Extended Type with where the Standard Type is negative and the Extended Types are positive.

```AsciiArt
| Vector |      POD Type 0-31 (.=Valid A-H=Order to convert blocks in)      |
| Type   | N I I C F I I C F I I C F I I T  F I I T P P P P P P P P P P P P |
| SW:VT  | I U I H P U S H P U S H P U S M  P U S M T T T T T T T T T T T T |
| b8:b5  | L A A A B B B B C C C C D D D D  E E E E a b c d e f g h i j k l |
+--------+------------------------------------------------------------------|
|   0/A  | . . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|   1/B  | A . . . H H H H B B B B B B B B  B B B B B B B B B B B B B B B B |
|   2/C  | A . . . . . . . B B B B B B B B  B B B B B B B B B B B B B B B B |
|   3/D  | A . . . . . . . B B B B B B B B  B B B B B B B B B B B B B B B B |
|   4/E  | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|   5/F  | A . . . . . . . H H H H F F F F  F F F F D D D D C C C C C C C C |
|   6/G  | A . . . . . . . . . . . F F F F  F F F F D D D D C C C C C C C C |
|   7/H  | A . . . . . . . . . . . F F F F  F F F F D D D D C C C C C C C C |
|   8/I  | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|   9/J  | A . . . . . . . . . . . H H H H  G G G G E E E E C C C C C C C C |
|  10/K  | A . . . . . . . . . . . . . . .  G G G G E E E E C C C C C C C C |
|  11/L  | A . . . . . . . . . . . . . . .  H H H H E E E E C C C C C C C C |
+--------+------------------------------------------------------------------|
| Total  | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  512   |      Type 0-31      0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
```

For the optimization for Block H please see "Faster EXT Boolean Method" bellow.

## Remapped Extended Standard Types 1-135

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

## Faster EXT Boolean Method

```AsciiArt
| Vector |    POD Type 0-31 (.=Valid A-C=Order to convert x=Don't care)     |
| Type   | N I I C F I I C F I I C F I I T  F I I T C C C D C C C C C C C C |
| SW:VT  | I U I H P U S H P U S H P U S M  P U S M T T T T T T T T T T T T |
| b8:b5  | L A A A B B B B C C C C D D D D  E E E E A B C D E F G H I J K L |
+--------+------------------------------------------------------------------|
|   0/A  | . . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|   1/B  | A . . . C C C C 0 0 0 0 0 0 0 0  B B B B B B B B B B B B B B B B |
|   2/C  | A . . . . . . . 0 0 0 0 0 0 0 0  B B B B B B B B B B B B B B B B |
|   3/D  | A . . . . . . . 0 0 0 0 0 0 0 0  B B B B B B B B B B B B B B B B |
|   4/E  | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|   5/F  | A . . . . . . . C C C C 0 0 0 0  B B B B B B B B B B B B B B B B |
|   6/G  | A . . . . . . . . . . . 0 0 0 0  B B B B B B B B B B B B B B B B |
|   7/H  | A . . . . . . . . . . . 0 0 0 0  B B B B B B B B B B B B B B B B |
|   8/I  | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|   9/J  | A . . . . . . . . . . . C C C C  B B B B B B B B B B B B B B B B |
|  10/K  | A . . . . . . . . . . . . . . .  B B B B B B B B B B B B B B B B |
|  11/L  | A . . . . . . . . . . . . . . .  B B B B B B B B B B B B B B B B |
+--------+------------------------------------------------------------------|
| Total  | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  512   |      Type 0-31      0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
```

```AsciiArt
| Vector | .=Valid C=Block C x=Don't care  |
| SW:VT  | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 |
| b8:b5  |                     0 1 2 3 4 5 |
+--------+---------------------------------|
|   0/A  | x x x x x x x x x x x x x x x x |
|   1/B  | x . . . C C C C 0 0 0 0 0 0 0 0 |
|   2/C  | x . . . . . . . 0 0 0 0 0 0 0 0 |
|   3/D  | x . . . . . . . 0 0 0 0 0 0 0 0 |
|   4/E  | x . . . . . . . x x x x x x x x |
|   5/F  | x . . . . . . . C C C C 0 0 0 0 |
|   6/G  | x . . . . . . . . . . . 0 0 0 0 |
|   7/H  | x . . . . . . . . . . . 0 0 0 0 |
|   8/I  | x . . . . . . . . . . . x x x x |
|   9/J  | x . . . . . . . . . . . C C C C |
|  10/K  | x . . . . . . . . . . . . . . . |
|  11/L  | x . . . . . . . . . . . . . . . |
+--------+---------------------------------|
```

```AsciiArt
| SW:VT | 0 1 2 3 |
| b8:b5 | type_m4 |
+-------+---------|
|  0/A  | x x x x |
|  1/B  | x x x x |
|  2/C  | x x x x |
|  3/D  | x x x x |
|  4/E  | . C 0 0 |
|  5/F  | . . 0 0 |
|  6/G  | . . 0 0 |
|  7/H  | . . x x |
|  8/I  | . . C 0 |
|  9/J  | . . . 0 |
| 10/K  | . . . 0 |
| 11/L  | . . . x |
| 12/M  | . . . C |
| 13/N  | . . . . |
+-------+---------|
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
