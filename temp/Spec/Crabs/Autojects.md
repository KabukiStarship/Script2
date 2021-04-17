# [SCRIPT Specification](../../)

## [Crabs Specification](./)

### Autojects

Autojects (Automatic objects) are memory managed objects using the Socket Abstract Data Type and the SocketFactory.

### SocketFactory

Memory management for Autojects is handled using a C-function pointer called an SocketFactory that uses the prototype:

```C++
typedef UIW* (*SocketFactory)(UIW* heap_memory, SIW size);
```

A SocketFactory has three functions:

1. Return the SocketFactoryHeap.
2. Create new heap_memory.
3. Delete heap_memory.
4. Getting the ASCII Data Type.

#### RamFactoryHeap

In order to auto-grow from stack-to-heap a different SocketFactory is required because you can't delete stack memory.

```C++
SocketFactory socket_factory = RamFactoryStack;
UIW* buffer = socket_factory(nullptr, 0);
SocketFactory ram_factory_heap = socket_factory
```

#### Creating new Memory

```C++
SocketFactory socket_factory = RamFactoryHeap;
UIW* buffer = socket_factory(nullptr, 123);
```

#### Deleting Memory

To delete memory you pass the heap_memory block to be deleted into the SocketFactory as follows:

```C++
SocketFactory socket_factory = RamFactoryHeap;
UIW* buffer = socket_factory(nullptr, 123);
socket_factory(buffer, 0); //< Deletes the buffer created in the last step.
```

#### Getting the ASCII Data Type

The ASCII Data Type of the Autoject is returned when nullptr and -1 are passed in as parameters respectively as follows:

```C++
DTW data_type_word = reinterpret_cast<DTW*>(socket_factory(buffer, -1));
```

**[<< Previous Section: Conformance Targets](./conformance_targets) | [Next Section: SCRIPT Specification >>](./script_specification)**

## Requirements

[1] ./

## License

Copyright 2015-21 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
