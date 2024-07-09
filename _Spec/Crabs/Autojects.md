# [SCRIPT Specification](../../)

## [Crabs Specification](./)

### Autojects

Autojects (Automatic objects) are word-aligned memory managed objects using the Socket Abstract Data Type and the RAMFactory.

### RAMFactory

Memory management for Autojects is handled using a C-function pointer called an RAMFactory that uses the prototype:

```C++
typedef IUW* (*RAMFactory)(IUW* heap_memory, SIW size, DTW data_type);
```

A RAMFactory the following functions:

1. Creating Memory.
2. Deleting Memory.
3. Returning the RAMFactory Heap function.
4. Returning the Data Type.

#### Creating Memory

Creating memory on the heap is done by passing in a nullptr for the `IUW* socket` parameter and the size of the block in bytes. Memory size values must be a multiple of the CPU word size and be at least one word, else it will either return nullptr if it's less than  one word or be rounded down one word if greater than one word. Please note that SCRIPT Spec does not support 8-bit memory sizes.

```C++
RAMFactory socket_factory = RamFactoryHeap;
IUW* boofer = socket_factory(nullptr, 123);
boofer = socket_factor(nullptr,  9); // Rounds 9 down to 8 on all systems.
boofer = socket_factor(nullptr,  1); // ERROR! Returns nullptr.
boofer = socket_factor(nullptr, -1); // ERROR! Returns nullptr.
```

#### Deleting Memory

To delete memory you pass the pointer to the heap_memory block to be deleted into the RAMFactory as follows:

```C++
RAMFactory socket_factory = RamFactoryHeap;
IUW* boofer = socket_factory(nullptr, 123);
socket_factory(boofer, 0); //< Deletes the boofer created in the last step.
```

If the origin pointer is nil, the size_bytes is disregarded.

#### Returning the RAMFactory Heap

In order to auto-grow from stack-to-heap a different RAMFactory is required because you can't delete stack memory. Because an autoject's size must be at least one word, you can pass in any size_bytes value less than one word and it will return the 

```C++
RAMFactory socket_factory = RamFactoryStack;
IUW* boofer = socket_factory(nullptr, 0);
RAMFactory ram_factory_heap = socket_factory
```

#### Getting the ASCII Data Type

The ASCII Data Type of the Autoject is returned when the origin pointer is nil and the size_bytes is less than one word.

```C++
DTW data_type_word = reinterpret_cast<DTW>(socket_factory(nullptr, -1));
data_type_word = reinterpret_cast<DTW>(socket_factory(nullptr, 1));
```

**[<< Previous Section: Conformance Targets](./ConformanceTargets.md) | [Next Section: SCRIPT Specification >>](./ScriptSpecification.md)**

## Requirements

[1] ./

## License

Copyright [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
