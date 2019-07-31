# [SCRIPT Specification](../readme.md)

## [Crabs](readme.md)

### Platform-specific POD Types

Platform-specific Plain-Old-Data (POD) Types do not have a pre-defined size and are defined by the target implementation. These types are based on the microprocessor word size and the default character and number types for the target system and application.

| Type |   Alt Name   |  Width  | Description |
|:----:|:------------:|:-------:|:------------|
| SIS  |     SI       | (1/2)W  | Half-word sized signed integer. |
| UIS  |     UI       | (1/2)W  | Half-word sized unsigned integer. |
| FLX  |     FP       |    W    | Floating-point number the half the size of the size of the host CPU's FPU. |
| SIW  |   intptr_t   |    W    | Signed integer of the size of the host CPU's ALU. |
| UIW  |  uintptr_t   |    W    | Unsigned integer of the size of the host CPU's ALU. |
| FLW  |  floatptr_t  |    W    | Floating-point number the size of the size of the host CPU's FPU. |
| SIX  |     SI       |   2W    | Double-word sized signed integer. |
| UIX  |     UI       |   2W    | Double-word sized unsigned integer. |
| FLX  |     FP       |   2W    | Floating-point number the twice the size of the size of the host CPU's FPU. |
| STN  |   wchar_t*   |    ?    | A nil-terminated string of CHR. |
| SIN  |     int      |   2,4   | Signed integer at least 16 bits wide. |
| UIN  | unsigned int |   2,4   | Unsigned integer at least 16 bits wide. |
| CHW  |   wchar_t    |   2,4   | Unicode character either 16 or 32-bits wide. |
| PTR  |    void*     |    W    | Word-sized pointer. |
| PTC  | const void*  |    W    | Word-sized const pointer. |
| DTW  |   intptr_t   |    W    | A word-sized ASCII Data Type. |
| OPD  |   Operand    |    W    | Word-sized pointer to an Operand object. |
| AJT  |   Autoject   |   2W    | Automatic object with a RamFactory and pointer to an Object. |
| VAL  |    Value     |   3W    | An ASCII Type-Value tuple. |
| STR  |  const CHR*  |    ?    | A nil-terminated Unicode string of CHR. |
| CHR  |    char_t    |  1,2,4  | Unicode character at least 8 bits wide. |
| SIR  |    int_t     | 1,2,4,8 | Signed integer at least 8 bits wide. |
| UIR  |    uint_t    | 1,2,4,8 | Unsigned integer at least 8 bits wide. |
| FPR  |   float_t    | 1,2,4,8 | Floating-point number at least 16 bits wide. |

**<< [Previous Section](.md)** | **[Next Section](.md) >>**

## License

Copyright (C) 2014-9 Cale McCollough <http://calemccollough.github.io/>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
