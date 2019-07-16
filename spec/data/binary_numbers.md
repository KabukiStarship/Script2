# [SCRIPT Specification RFC](../readme.md)

## [ASCII Data Specification](readme.md)

### Binary Numbers

Script supports, 16, 32, 64, and 128-bit floating-point numbers as defined, also called half, float, and double, and quadruple precision float-point numbers, as defined in the IEEE754 specificaiton.

```C++
FP2 0.0     // Use a HLF to save memory and bandwidth!
FP4 0.1     // Wastes a lot of space!
FP8 - 0.1;  // Wastes a whole lot of space!
FPH 1.0     // Wastes a TRUCK TON of space but best for repeated addition.
```
