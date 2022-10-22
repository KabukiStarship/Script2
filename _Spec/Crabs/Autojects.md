# [SCRIPT Specification](../../)

## [Crabs Specification](./)

### Autojects

Autojects (Automatic objects) are memory managed objects using the Socket Abstract Data Type and the SocketFactory.

### SocketFactory

Memory management for Autojects is handled using a C-function pointer called an SocketFactory that uses the prototype:

```C++
typedef IUW* (*SocketFactory)(IUW* heap_memory, SIW size, DTW data_type);
```

A SocketFactory the following functions:

1. Returning the SocketFactoryHeap
2. Returning the ASCII Data Type
3. Creating Memory.
4. Deleting Memory.
5. Growing Memory.
6. Cloning Memory.

#### Returning the SocketFactoryHeap

In order to auto-grow from stack-to-heap a different SocketFactory is required because you can't delete stack memory.

```C++
SocketFactory socket_factory = RamFactoryStack;
IUW* buffer = socket_factory(nullptr, 0);
SocketFactory ram_factory_heap = socket_factory
```

#### Returning the ASCII Data Type

The data type is returned by passing in a negative number in as the size_bytes.

```C++
DTW data_type = reinterpret_cast<DTW>(socket_factory(nullptr, -1));
```

#### Creating Memory

Creating memory on the heap is done by passing in a nullptr for the `IUW* socket` parameter and the size of the block in bytes.

```C++
SocketFactory socket_factory = RamFactoryHeap;
IUW* buffer = socket_factory(nullptr, 123);
```

#### Deleting Memory

To delete memory you pass the heap_memory block to be deleted into the SocketFactory as follows:

```C++
SocketFactory socket_factory = RamFactoryHeap;
IUW* buffer = socket_factory(nullptr, 123);
socket_factory(buffer, 0); //< Deletes the buffer created in the last step.
```

#### Getting the ASCII Data Type

The ASCII Data Type of the Autoject is returned when nullptr and 0 are passed in as parameters respectively as follows:

```C++
DTW data_type_word = reinterpret_cast<DTW*>(socket_factory(buffer, 0));
```

#### Growing Memory

To grow the memory you have two options. You can automatically double the size of the socket by passing in a pointer to a buffer and -2 for the size bytes.

```C++
IUW* autoject = socket_factory(buffer, -2);
```

Or you can specify the new size of the socket you would like by passing in the size as negative.

```C++
ISW size_new = 1024;
IUW* buffer = socket_factory (buffer, -size_new);
```

#### Cloning Memory

Cloning memory will create a new copy of that data on the heap. You can clone an autoject by passing in the buffer and -2 for the size_bytes.

```C++
IUW* clone = socket_factory(buffer, -3);
```

**[<< Previous Section: Conformance Targets](./ConformanceTargets.md) | [Next Section: SCRIPT Specification >>](./ScriptSpecification.md)**

## Requirements

[1] ./

## License

Copyright 2015-22 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
