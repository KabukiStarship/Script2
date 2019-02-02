# [SCRIPT Specification RFC](../readme.md)

## [ASCII Data Specification](readme.md)

### Boolean

Booleans in Script are stored as 32-bit signed integer types where the deasserted value shall be stored as the number zero and labeled false, and asserted values shall be represented as the number one labeled true or a non-zero integer value.

### Boolean Examples

```C++
// All values less then 127 and greater than -127
BOL true   //< Translates to the number 1
BOL false  //< Translates to the number 0
BOL 0
BOL 1
BOL -129   //< Will require 2 bytes to transceive.
```