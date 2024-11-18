# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types](./)

#### Stack

```C++
template <typename ISZ = ISN>
struct TStack {
  ISZ total,  //< Size of the Array in elements.
      count;  //< Element count.
};
```

##### Array Memory Layout

```AsciiArt
    +---------------+
    |    Buffer     |
    |---------------|
    | C-Style Array |
 ^  |---------------|
 |  |    Header     |
0xN +---------------+
```

**[<< Previous Section: Array](Array.md) | [Next Section: Matrix >>](Matrix.md)**

## Requirements

[1] ./

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
