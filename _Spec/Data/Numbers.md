# [SCRIPT Specification](../)

## [ASCII Data Specification](./)

### Integers

Script supports both traditional 8, 16, 32, and 64-bit, and n-byte signed 2's complement integers and uncomplemented unsigned integers.

#### 2.2.a Valid Integers Examples

```C++
ISA 0
IUA 255
ISB -32,000
ISC 0xFFFF
```

#### 2.2.b Invalid Integer Examples

```C++
ISA 256       ; Too big for size
ISB 0xFFFFF   ; Too big for size
```

#### 2.2.c Unsigned Not-a-Numbers

Unsigned Not-a-Number (U-NaN) is the bit pattern with all ones as in the following example:

```C++
template<typename UI = UIW>
inline UI NaNUnsigned () {
  UI nan = 0;
  return ~nan;
}
```

#### 2.2.d Signed Not-a-Numbers

Unsigned Not-a-Number (S-NaN) is the bit pattern with only the Most Significant bit asserted as in the following example:

```C++
template<typename SI, typename UI>
inline SI NaNSigned () {
  UI nan = 1;
  return (SI)(nan << (sizeof (UI) * 8 - 1));
}
```

#### 2.2.e Varints

Variants are MSb variant are compressed using MSB-encoded signed and unsigned 1-to-9-byte variable-length integers. Varints use the MSb of each byte to determine if another byte is to be loaded. This allows values less than 128 to be sent using only one byte, 14-bit values in two bytes, 21-bit values in three bytes and so on.  

Both Signed and Unsigned Varints must use the most significant bit asserted is used to marks if another byte is loaded. All Script implementations shall represent signed varints as uncomplemented integers with the sign bit in the LSb.

```C++
IUB_V 128 // = 0b0000_0001_1000_0000
IUC_V 255 // = 0b0000_0001_1111_1111
SID_V -64 // = 0b0011_1111
```

#### 2.2.f BigNum

Unsigned Integer BigNum (IUB) is between 2 and 2048 bytes wide where the 5 LSb of the type are always 0. The width of the unsigned integer is found by shifting the type over 5 bits to the right and adding one[9].

#### Example

```C++
IUB_1 //< 1-byte IUB data type in Hex is 0x20.
IUB_255 //< 1-byte IUB data type in Hex is 0x2000.
IUB_2048 //< 2048-byte IUB data type in Hex is 0xFFE0.
```

#### Boolean

Booleans in Script are stored as signed integer types where the false value is stored as the number zero and labeled false, and asserted values is represented as the number one labeled true or a non-zero integer value.

### Boolean Examples

```C++
// All values less then 127 and greater than -127
BOL true   //< Translates to the number 1
BOL false  //< Translates to the number 0
BOL 0
BOL 1
BOL -129   //< Will require 2 bytes to transceive.
```

### Floating Point

Script supports, 16, 32, 64, and 128-bit floating-point numbers as defined, also called half, float, and double, and quadruple precision float-point numbers, as defined in the IEEE754 specification.

```C++
FPB 0.0     // Use a HLF to save memory and bandwidth!
FPC 0.1     // Wastes a lot of space!
FPD - 0.1;  // Wastes a whole lot of space!
FPE 1.0     // Wastes a TRUCK TON of space but best for repeated addition.
```

**[<< Previous Section: Data Types](DataTypes.md) | [Next Section: Timestamps >>](Timestamps.md)**

## Requirements

[1] ./

## License

Copyright 2015-22 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
