# [SCRIPT Specification](../../readme.md)

## [ASCII Data Specification](../readme.md)

### Autojects

Autojects are Auto-Objects with automatic memory management.

#### Autoject Types Table

| ID | Type | C++/Alt Name | Width | Description |
|:--:|:----:|:------------:|:-----:|:------------|
| 26 | OPD  |   Operand    |  1W   | Pointer to an Operand object. |
| 27 | AJT  |   Autoject   |  2W   | An Auto-Object that stores Pointer to an object and a SocketFactory. |


### RamFactory

Memory management for Autojects is handled using a C-function pointer called an RamFactory that uses the prototype:

```C++
typedef UIW* (*RamFactory)(UIW* heap_memory, SIW size);
```

A RamFactory has three functions:

1. Return the RamFactoryHeap.
2. Create new heap_memory.
3. Delete heap_memory.
4. Getting the ASCII Data Type.

#### RamFactoryHeap

In order to auto-grow from stack-to-heap a different RamFactory is required because you can't delete stack memory. T

```C++
RamFactory ram_factory = RamFactoryStack;
UIW* buffer = ram_factory(nullptr, 0);
RamFactory ram_factory_heap = ram_factory
```

#### Creating new Memory

```C++
RamFactory ram_factory = RamFactoryHeap;
UIW* buffer = ram_factory(nullptr, 123);
```

#### Deleting Memory

To delete memory you pass the heap_memory block to be deleted into the RamFactory as follows:

```C++
RamFactory ram_factory = RamFactoryHeap;
UIW* buffer = ram_factory(nullptr, 123);
ram_factory(buffer, 0); //< Deletes the buffer created in the last step.
```

#### Getting the ASCII Data Type

The ASCII Data Type of the Autoject is returned when nullptr and -1 are passed in as parameters respectively as follows:

```C++
DTW data_type_word = reinterpret_cast<DTW*>(ram_factory(buffer, -1));
```

**[<< Previous Section:](./.md) | [Next Section: >>](./.md)**

## License

Copyright 2014-9 © [Kabuki Starship™](https://kabukistarship.com); all rights reserved.

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
