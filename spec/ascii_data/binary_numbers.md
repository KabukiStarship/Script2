# [SCRIPT Specification RFC](../readme.md)

## [ASCII Data Specification](readme.md)

### Binary Numbers

Script supports, 16, 32, and 64-bit floating-point numbers, also called half, float, and double precision float-point numbers. Floating-point numbers do not lend themselves very well to varint compression, so using a 16-bit floating-point number can dramatically improve performance when low-precision is needed. Implementations may implement 128-bit floating-point math. 128-bit floating point numbers are compatible with the C# programming language.

```C++
HLF 0.0     // Use a HLF to save memory and bandwidth!
FLT 0.1     // Wastes a lot of space!
DBL - 0.1;  // Wastes a whole lot of space!
DEC 1.0     // Wastes a TRUCK TON of space!
```
