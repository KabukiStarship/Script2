# SCRIPT Script

[![GitHub version](https://badge.fury.io/gh/kabuki-starship%2Fscript2.svg)](https://badge.fury.io/gh/kabuki-starship%2Fscript2)

The Serial Chinese Room, Interprocess, and Telemetry (SCRIPT) Specification defines A family of technologies, collectively referred to as Script, built with the Automaton Standard Code for Information Interchange (ASCII) Data Types, the Chinese Room Abstract Stack Machine (Crabs), SCRIPT Protocol, and SCRIPT Script (Script^2 or Script2). Script2 provides:

* Cross-platform Modern Embedded-C++11 replacement for C++ std library with optional use of dynamic memory.
* Nanoframework provides the core module for creating Microframeworks and Monolithic frameworks.
* Interprocess communication, data serialization, and marshaling engine.
* Unit test framework with low-cost in-order Seam tree tests for Agile, Test, and Issue Driven Development featuring debug information customized for each tree node.
* Rapid compile time using 3-file translation units and wrapper classes that hide templates and large header files.
* Powerful Unicode engine that allows printing to different streams using some template tricks and simple familiar syntax.
* Crabs Expression scanner uses an impressively small amount of code to scan a crazy large number of data types using only using resources for the ones you use.
* Modeled after AI philosophy of the Chinese Room Thought Experiment and ASCII C0 Control Codes.

## ASCII Data Types

ASCII Data Types provide:

* All of the C++ POD types.
* Convenient and easy-to-read-and-type 3-letter all-caps abbreviations that POP out around lower_snake_case.
* Year 2038-safe 32-bit, 64- bit and dual-32-bit with 32-year epoch and sub-second tick timestamps.
* All data types are word-aligned so they may be rapidly copied from one system to another on homo-endian system.
* MSB variant encoding called Varints provides fast data compression similar to UTF-8.
* Contiguous Objects:
  * Types can be represented as 8, 15, or 32-bit types for 255 8-bit types, 8K 16-bit types, and over 100M 32-bit types.
  * UTF-8, UTF-16, and UTF-32 support.
  * Array - An array with the first word being the element count.
  * Stack - A stack of POD types stored as an array where the second word is the stack count.
  * Loom - A homogeneous array of UTF-8, UTF-16, or UTF-32 strings using a Stack of offsets.
  * B-Sequence - Describes the order and maximum sizes of a Byte-Sequence of ASCII Data.
  * Expression - Chinese Room Expressions capable of concurrently executing scripts in multiple languages with interrupts.
  * Maps - Maps can be created of any of the POD, String, or Loom to any type, including nested Maps.
    * Table - A hash table of contiguous integer mappings.
    * Book - A key-value (dictionary) table of ASCII Data Types without a hash table for fastest push-back performance.
    * Dictionary - A dictionary of ASCII Data Types with hash table.

## ASCII C++ Style Guide

The [ASCII C++ Style Guide](https://github.com/kabuki-starship/script2/style_guide/readme.md) is a modified version of the Google C++ Style Guide that features ASCII Data Types, allowance of all capital letters in public member names, Doxygen comment formatting rules to provide faster access to the most important metadata with Intellisense, and dramatically less clutter with more whitespace and improved readability.

## Quick Start Guide

Please **@see** [Kabuki Toolkit](https://github.com/kabuki-starship/kabuki_toolkit) (KT) for Quick Start Guide.

## Quick Links

* [FAQ](https://github.com/kabuki-starship/script/blob/master/docs/readme.md) - *Frequently asked questions.*
* [SCRIPT Specification](https://github.com/kabuki-starship/script2/blob/master/spec/readme.md) - *Release for Comment for Serial Chinese Room, Interprocess, and Telemetry (SCRIPT) Specification.*
* [Kabuki Toolkit](https://github.com/kabuki-starship/kabuki_toolkit) - *A cross-platform Modern Embedded-C++ toolkit for making intelligent connected technologies, plugins, games, servers, firmware, and art with Script2. This is where you'll find the visual studio projects.*
* [Kabuki Starship Website](https://kabuki-starship.github.io/) - *Official Kabuki Starship website. #WorkInProgress*

## Author

* Cale Jamison McCollough <<calemccollough.github.io>> <<cale@astartup.net>>

## License

Copyright 2014-19 (C) Cale Jamison McCollough <<cale@astartup.net>> and contributors. All rights reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
