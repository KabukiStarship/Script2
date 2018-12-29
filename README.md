# SCRIPT Script

Serial Chinese Room, Interprocess, and Telemetry (SCRIPT) Specification defines A family of technologies, collectively referred to as Script, that are built on the Chinese Room Abstract Stack Machine (Crabs), SCRIPT Protocol, and SCRIPT Script (Script^2 or Script2) and provides:

* Replacement for C++ std library suitable for embedded systems.
* Seam Trees provide low-cost in-order unit tests for Agile, Test, and Issue Driven Development with debug information customized for each tree node.
* Cross-platform Modern `Embedded-C++11` IoT Nanoframework with Cross-language C Application Binary Interface (ABI) and Doxygen API docs.
* ASCII Data Types and the ASCII Factory operate seamlessly across assembly boundary with optimal RAM usage and CPU cache performance from ROM-able ASCII Contiguous Objects.
* Rapid compile time using 3-file Translation Units with unique names an separated C++ templates.
* Modeled after AI philosophy and ASCII mimicry of the Chinese Room Thought Experiment and C0 Control Codes.
* ASCII C++ Style Guide is a modified version of the Google C++ Style Guide.

## ASCII Data

ASCII Data Types provide:

* All of the C++ POD types.
* Year 2038-safe 32-bit, 64- bit and dual-32-bit with 32-year epoch and sub-second tick timestamps.
* All data types are 64-bit aligned so they may be rapidly copied from one system to another on homo-endian system.
* Optional MSB variant encoding provides fast data compression similar to UTF-8.
* Convenient and easy-to-read-and-type 3-letter all-caps abbreviations that POP out around lower_snake_case.
* Contiguous Objects
  * UTF-8, UTF-16, and UTF-32 strings.
  * Stack - A stack of POD types in the form of a bounded-sized array.
  * Array - A multidimensional array with Stack of dimensions.
  * Loom - A homogeneous array of UTF-8, UTF-16, or UTF-32 strings.
  * Table - A hash table of contiguous mappings.
  * Map - A sparse map of unsigned integers to ASCII Data Types.
  * Book - A multidictionary (i.e. unordered map) without hash table.
  * Dictionary - A dictionary of ASCII Data Types with hash table.
  * B-Sequence - Describes the order and maximum sizes of a Byte-Sequence of ASCII Data.
  * Expression - Asynchronous Chinese Room Script Expressions capable of concurrently executing scripts in multiple languages in real-time.

## Quick Links

* [FAQ](https://github.com/kabuki-starship/script/blob/master/docs/readme.md)
  - *Frequently asked questions.*
* [Script Specification RFC](https://github.com/kabuki-starship/script2/blob/master/docs/rfc/readme.md)
  - *Release for Comment for Serial Chinese Room, Interprocess, and Telemetry (SCRIPT) Specification.*
* [Script2](https://github.com/kabuki-starship/script2)
  - *Primary repository of the SCRIPT Specification and Script2.*
* [Kabuki Starship Website](https://kabuki-starship.github.io/)
  - *Official Kabuki Starship website. #WorkInProgress*

## Quick Start Guide

**1.** Clone the repo:

> https://github.com/kabuki-starship/script2.git

**2.** Read the

**3.** Open the `script2.sln` Visual Studio 2017 Project. For Eclipse projects **@see** [Kabuki Toolkit](https://github.com/kabuki-starship/kabuki-toolkit).

**4.** Open the `global_config.inl` and look at the typedef(s) and seam macros, then set the seam number in the `pch.h` file. Then look through the `test_debug.inl` and `test_release.inl`, the look through the seam tree tests in the files that start with `0_0_0` and the called functions.

**5.** In order to save the stack debug data when an assert occurs, set breakpoint in the file `script2_test.cc` at the return line for:

```C++
BOL TestWarn(const CH1* function, const CH1* file, int line);
```

## Author

* [Cale McCollough](https://calemccollough.github.io) <[cale.mccollough@gmail.com](mailto:cale.mccollough@gmail.com)>

## License

Copyright 2014-18 (C) [Cale McCollough](mailto:calemccollough@gmail.com) and contributors. All rights reserved (R).

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License [here](http://www.apache.org/licenses/LICENSE-2.0).

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
