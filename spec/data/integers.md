# [SCRIPT Specification RFC](../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at [https://mozilla.org/MPL/2.0/](https://mozilla.org/MPL/2.0/).

## [ASCII Data Specification](readme.md)

### Integers

Script supports both traditional 8, 16, 32, and 64-bit, and n-byte signed 2's complement integers and uncomplemented unsigned integers.

#### 2.2.a Valid Integers Examples

```C++
SI1 0
UI1 255
SI2 -32,000
SI4 0xFFFF
```

#### 2.2.b Invalid Integer Examples

```C++
SI1 256       ; Too big for size
SI2 0xFFFFF   ; Too big for size
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
UVI 128 // = 0b0000_0001_1000_0000
UVI 255 // = 0b0000_0001_1111_1111
SVI -64 // = 0b0011_1111
```

#### 2.2.f X-Byte Unsigned Integers

X-Byte Signed Integers (SIN) and Unsigned Integers (UIN) are integers that may be 0-N bytes in width. SIN and UIN are very useful for transferring 128+ bit hashes and custom data structures. Implementations may implement n-byte arithmetic.

#### Example

```C++
// static const unsigned int sin_uin_bsq_example = { 2, SIN, 8, UIN 16 };
SIX -1
UIX 1
```