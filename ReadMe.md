# [Script2](github.com/KabukiStarship/Script2)

```AsciiArt
 /\               MP""""""`MM                   oo            dP   d8888b.
( /   @ @    ()   M  mmmmm..M                                 88       `88
 \  __| |__  /    M.      `YM .d8888b. 88d888b. dP 88d888b. d8888P .aaadP'
  -/   "   \-     MMMMMMM.  M 88'  `"" 88'  `88 88 88'  `88   88   88'
 /-|       |-\    M. .MMM'  M 88.  ... 88       88 88.  .88   88   88.
/ /-\     /-\ \   Mb.     .dM `88888P' dP       dP 88Y888P'   dP   Y88888P
 / /-`---'-\ \    MMMMMMMMMMM                      88
  /         \                                      dP
```

[![GitHub version](https://badge.fury.io/gh/KabukiStarship%2Fscript2.svg)](https://badge.fury.io/gh/KabukiStarship%2Fscript2)

The Serial Chinese Room, Interprocess, and Telemetry Specification (SCRIPT Specification), defines the ASCII Data Types, the Chinese Room Abstract Stack Machine (Crabs), SCRIPT Protocol, and Script2 (TM) (Script2). Script2 is an implementation of the SCRIPT Specification that provides:

* Cross-platform Modern Embedded-C++ replacement for C++ std library featuring optional dynamic memory and simplified Kabuki Module format.
* Interprocess communication and data serialization engine modeled after AI philosophy of the Chinese Room Thought Experiment and ASCII C0 Control Codes.
* Ultra-fast Unicode string processing with the Uniprinter (Universal Printer), featuring the [Puff Algorithm](https://github.com/KabukiStarship/Script2/wiki/Fastest-Method-to-Print-Integers-and-Floating-point-Numbers) and template-friendly Stringf formatting utilities to replace printf, sprintf, and sscanf.
* Unit test framework with low-cost in-order Seam tree tests for Agile, Test, and Issue Driven Development featuring debug information customized for each tree node.
* The [Automaton Standard Code for Information Interchange (ASCII) Data Specification](./_Spec/data/) is an Abstract Data Type Specification that defines a contiguous memory layout and test suite optimized for CPU cache performance.
* The [ASCII C++ Style Guide](./_StyleGuide/) is a divergent fork of the Google C++ Style Guide that uses ASCII Data Types and intelligent rules to dramatically reduced clutter and improved readability.

## Status and Help Wanted

I need help debugging contiguous memory data structures. Right now (2022-04-17) we're working on an XML parser and RSS reader. We are working with C++11 and C++20. The best way for you to help out is to help us with test coverage of the data structure. I'm currently working on the Book data structure trying to get up to our custom stream reader and writer that is built on our Uniprinter Unicode library. You can switch seams to the Book seam in the `_Seams/_Config.h`. You can find a list of the seams in the `_Seams/_Seams.inl` file. You will need to Fork this repo to contribute and debug in your own fork, then push the changes to your fork and then merge with the master branch from there.

## Documentation

* [SCRIPT Specification](./Spec/) - *Release for Comment for Serial Chinese Room, Interprocess, and Telemetry (SCRIPT) Specification.*
* [KabukiPress Cookbook Chapter on Script2](https://github.com/CookingWithCale/KabukiPressCookbook/tree/master/Script2) - *The official documentation for Script2.*

## License

Copyright 2015-22 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
