# Stack

```C++
template <typename ISZ = ISN>
struct TStack {
  ISZ total,    //< Size of the Array in elements.
      count;    //< Element count.
};
```

## Array Memory Layout

```AsciiArt
    +---------------+
    |    Buffer     |
    |---------------|
    | C-Style Array |
 ^  |---------------|
 |  |    Header     |
0xN +---------------+
```
