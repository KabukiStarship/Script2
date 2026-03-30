# Array

ASCII Arrays are C-Style arrays where the number of elements is stored in the header of the array. The number of elements is referred to as the count.

The size of the Array is stored in the number of elements rather than the size in bytes to avoid repetitive calculations.

```C++
template <typename SIZ = ISC>
struct TArray {
  SIZ size;  //< Size of the Array in elements.
};
```

## Memory Layout

```AsciiArt
    +----------------+
    | C-Style Array  |
 ^  |----------------|
 |  |     Header     |
0xN +----------------+
```

## Requirements

[1] ./

[SCRIPT Specification](../../) **>** [ASCII Data Specification](../) **>** [Map Types](./)

**[<< Previous Section: Socket](Socket.md) | [Vector Types](./) | [Next Section: Stack >>](Stack.md)**

Copyright [AStarship™](https://astarship.net).
