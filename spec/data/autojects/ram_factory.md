# [SCRIPT Specification](../../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

### ASCII Factory

Memory management for Autojects is handled using a C-function pointer called an RamFactory that uses the prototype:

```C++
typedef UIW* (*RamFactory)(UIW* heap_block);
```

An AsciiFactory is essentially switch statement jump table with an index for a function and one argument that can be a pointer to any type of object, which allows for multiple parameters.

#### ASCII Factory Functions

 All ASCII Object share the same set of AsciiFactory functions:

```C++
enum AsciiFactoryFunctions {
  kFactoryCanGrow = 0, //< AsciiFactory function checks if the size can double.
  kFactoryDelete = 1,  //< AsciiFactory function deletes an OBJ.
};
```
