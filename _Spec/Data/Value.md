# [SCRIPT Specification](../)

## [ASCII Data Specification](./)

### Value

Values are POD types used to store or point to one of the other other types. There are two types of Values, a Type-Value Tuple and a Type-String Tuple.

#### Type-Value Tuple

Types TV2, TV4, or TV8  are Binary-Form Type-Value Tuples referred to as TVT. TVT are designed to work with up POD types with up to two ALU Words. The type is stored as word for memory alignment purposes. Please note, the following reference TVT data structure is not listed in template format because each system should only have one instance of the TVT struct.

```C++
struct TypeValue {
  DTW type_;    //< ASCII Data type stored as a word.
  UIW word_,    //< Lower ALU register word.
      word_2_;  //< Upper ALU register word.
};
```

#### Type-String Tuples

Types TS2, TS4, and TS8 are Type-String Tuples (TST) where the value is stored in UTF-8 format and the type is stored as a IUB. The TST is designed to be able to print a number up to twice the size of an ALU word. TS2 are designed for 16-bit systems that can print up to 32-bit numbers that are less than 10 characters long. TS4 is designed to print up to 64-bit numbers less than 22 characters long, and TS8 is designed to print up to 128-bit numbers less than 40 characters long.

```C++
struct TypeString {
  enum {
    // Max length of the buffer in ALU words.
    kBufferWordCount = (sizeof(void*) == 4) ? 6 : 5,
    // Max length of a string in characters.
    kLengthMax = kBufferWordCount * sizeof(void*) - 1,
  };
  DTW type_;
  UIW buffer_[cBufferWordCount];
};
```

A TST may store a pointer to another string type or object using the second element of the buffer.

**[<< Previous Section:Platform-specific Types](PlatformSpecificPODTypes) | [Next Section:Map Types >>](./MapTypes/)**

## Requirements

[1] ./

## License

Copyright 2015-22 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
