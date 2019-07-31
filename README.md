# SCRIPT Script

[![GitHub version](https://badge.fury.io/gh/kabuki-starship%2Fscript2.svg)](https://badge.fury.io/gh/kabuki-starship%2Fscript2)

The Serial Chinese Room, Interprocess, and Telemetry (SCRIPT) Specification defines A family of technologies, collectively referred to as Script, built with the ASCII Data Types, the Chinese Room Abstract Stack Machine (Crabs), SCRIPT Protocol, and SCRIPT Script (Script^2 or Script2). Script2 provides:

* Cross-platform Modern Embedded-C++11 replacement for C++ std library with optional use of dynamic memory.
* Interprocess communication, data serialization, and marshaling engine modeled after AI philosophy of the Chinese Room Thought Experiment and ASCII C0 Control Codes.
* Ultra-fast Unicode string processing with the Uniprinter (Universal Printer), featuring the [Puff Algorithm](https://github.com/kabuki-starship/script2/wiki/Fastest-Method-to-Print-Integers-and-Floating-point-Numbers) and template-friendly Stringf formatting utilities to replace printf and scanf.
* Unit test framework with low-cost in-order Seam tree tests for Agile, Test, and Issue Driven Development featuring debug information customized for each tree node.
* Rapid compile time using 3-file translation units and wrapper classes that hide templates and large header files.
* Crabs Expression scanner uses an impressively small amount of code to scan a crazy large number of data types using only using resources for the ones you use in RPC calls.

## ASCII Data Types

The Automaton Standard Code for Information Interchange (ASCII) Data Types Data Types are mimicked after ASCII C0 Control code and provide:

* All of the C++ POD types.
* Convenient and easy-to-read-and-type 3-letter all-caps abbreviations that POP out around lower_snake_case.
* Year 2038-safe 32-bit, 64- bit and dual-32-bit with 32-year epoch and sub-second tick timestamps.
* MSB variant encoding called Varints provides fast data compression similar to UTF-8.
* Contiguous Objects:
  * Types can be represented as 8-bits for mirocontrollers or 16-bit types for more powerful processors.
  * UTF-8, UTF-16, and UTF-32 support.
  * Loom - A homogeneous array of UTF-8, UTF-16, or UTF-32 strings using a Stack of offsets.
  * B-Sequence - Describes the order and maximum sizes of a Byte-Sequence of ASCII Data.
  * Expression - Chinese Room Expressions capable of concurrently executing scripts in multiple languages with interrupts.
  * Vector Types:
    * Array - An array with the first word being the element count.
    * Stack - A stack of POD types stored as an array where the second word is the stack count.
    * Matrix - A homogeneous multi-dimensional array with a Stack of dimensions.
  * Map Types:
    * Map - A sparse array of one 1, 2, 4, or 8-byte data type to another data type.
    * Table - A Prime Multiple Hash (PMH) hash table of contiguous unsigned integer mappings.
    * Dictionary - A dictionary of heterogeneous types with PMH hash table.
    * Book - A key-value dictionary of heterogeneous without a hash table for fastest push-back performance.

## ASCII C++ Style Guide

The [ASCII C++ Style Guide](https://github.com/kabuki-starship/script2/style_guide/readme.md) is a modified version of the Google C++ Style Guide that uses ASCII Data Types and allows of all capital letters in public member names, Doxygen comment formatting rules to provide faster access to the most important metadata with Intellisense, and dramatically less clutter with dramatically more whitespace and improved readability.

## Quick Start Guide

Please **@see** [Kabuki Toolkit](https://github.com/kabuki-starship/kabuki_toolkit) (KT) for Quick Start Guide.

## Quick Links

* [FAQ](https://github.com/kabuki-starship/script/blob/master/docs/readme.md) - *Frequently asked questions.*
* [SCRIPT Specification](https://github.com/kabuki-starship/script2/blob/master/spec/readme.md) - *Release for Comment for Serial Chinese Room, Interprocess, and Telemetry (SCRIPT) Specification.*
* [Kabuki Toolkit](https://github.com/kabuki-starship/kabuki_toolkit) - *A cross-platform Modern Embedded-C++ toolkit for making intelligent connected technologies, plugins, games, servers, firmware, and art with Script2. This is where you'll find the visual studio projects.*
* [Kabuki Starship Website](https://kabuki-starship.github.io/) - *Official Kabuki Starship website. #WorkInProgress*

## License

Copyright 2014-9 (C) Cale Jamison McCollough <<cale@astartup.net>> and contributors. All rights reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
