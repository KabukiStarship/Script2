# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types](./)

#### List

Lists are stacks of type-value tuples similar in memory layout to Books but they **do not** have keys. Functionally they are identical to B-Sequences expect the offsets are stored as an Array to eliminate the need to scan through the header to calculate the data offset. Sequences are ideal for situations where the fastest possible RW performance is needed.

##### Memory Layout

```AsciiArt
+----------------------------+
|_______   Buffer            |
|_______ ^ Value N           |
|        | Value 0           |
|----------------------------|
|_______   Buffer            |
|_______ ^ Value Type N      |
|        | Value Type 1      |
|----------------------------|
|_______   Buffer            |
|_______ ^ Value Offset N    |
|        | Value Offset 1    |
|----------------------------|  ^ Up in addresses.
|        TList Struct        |  |
+----------------------------+ 0xN
```

**[<< Previous Section: Map](Map.md) | [Next Section: Table >>](Table.md)**

## Requirements

[1] ./

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
