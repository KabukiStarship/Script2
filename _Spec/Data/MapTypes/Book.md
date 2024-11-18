# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types](./)

### Books

ASCII Books are dense ordered maps of key-value tuples. Books differ from ASCII Dictionaries in that multiple values with the same key may be stored. Books are created by creating an ASCII List with an ASCII Loom as element 0 that contains an empty string at element 0.

#### Book Memory Layout

```AsciiArt
+====================================+
|_______   Buffer                    |
|_______ ^ List Value N              |
|_______ | List Value 1              |
|        | Keys Loom (Value 0)       |
|------------------------------------|
|_______   Buffer                    |
|_______ ^ List Value N Type         |
|_______ | List Value 1 Type         |
|        | Loom Type (Type 0)        |
|------------------------------------|
|_______   Buffer                    |
|_______   Offset to Value N         |
|_______ ^ Offset to Value 1         |
|        | Offset to Keys (Offset 0) |
+====================================+  ^ Up in
|          TList Struct              |  |
+====================================+  + 0xN
```

##### Memory Overhead

| #Bytes | I | Index | Size | Total |    Overhead Per index      |
|:------:|:-:|:-----:|:----:|:-----:|:---------------------------|
|    2   | 1 |   2   |   2  |   8   |  8 + 3 per index + socket. |
|    4   | 2 |   4   |   4  |   16  | 16 + 5 per index + socket. |
|    8   | 4 |   8   |   8  |   32  | 24 + 9 per index + socket. |

* Sizes shown in bytes.

**[<< Previous Section: Table](./Table.md) | [Next Section: Dictionary >>](./Dictionary.md)**

## Requirements

[1] ./

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
