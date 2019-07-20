# [SCRIPT Specification RFC](../../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

### ASCII Factory

Memory management for ASCII Data Types is handled using a C-function pointer called an ASCII Factory, or AsciiFactory, that uses the prototype:

```C++
/* ASCII Factory manages memory for ASCII Objects.
@return Nil upon failure or if no return socket is expected, or a pointer to a
word-aligned socket upon success.
@param obj      Pointer to an existing ASCII Object socket if there is one.
@param function A jump table function index.
@param arg      Pointer to the ASCII Factory argument. */
typedef int (*AsciiFactory)(UIW* obj, SIW function, void* arg);
```

An AsciiFactory is essentially switch statement jump table with an index for a function and one argument that can be a pointer to any type of object, which allows for multiple parameters.

#### ASCII Factory Functions

 All ASCII Object share the same set of AsciiFactory functions:

```C++
enum AsciiFactoryFunctions {
  kFactoryCanGrow = 0, //< AsciiFactory function checks if the size can double.
  kFactoryDelete = 1,  //< AsciiFactory function deletes an OBJ.
  kFactoryNew = 2,     //< AsciiFactory function creates a new OBJ.
  kFactoryClone = 3,   //< AsciiFactory function clones the OBJ.
  kFactoryGrow = 4,    //< AsciiFactory function double OBJ size in bytes.
  kFactoryInfo = 5     //< Returns an info _::TStrand<> about the data type.
};
```
