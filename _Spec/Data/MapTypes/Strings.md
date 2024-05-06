# [SCRIPT Specification](../)

## [ASCII Data Specification](./)

### Strings

ASCII Strings Types consists of 8-bit (CHA), 16-bit (CHB), and 32-bit (CHC) characters, and Arrays and Vectors of characters called Strands and SPrinters (String Printers) that can be UTF-8, UTF-16, or UTF-32. Additionally, traditional C-style strings can be created using a Pointer (PTR) or Const Pointer (PTC) to a CHA, CHB, or CHC types.

```C++
TKN key                   //< No quotes needed for a TKN.
ADR 123                   //< A ADR is a TKN.
STA  "\"Hello world!\""   //< UTF-8 STR that reads "Hello world!" with double quotes.
ARC_CHC "Foo"             //< STR is shorthand for ARC_CHA
STB "Hello world!"       //< This is a _::TStrand<> that is up to 64KB long.
STC "Hello world!"       //< This is a _::TStrand<> that is up to 4GB long.
```

**[<< Previous Section:Timestamps](Timestamps.md) | [Next Section: B-Sequences >>](BSequences.md)**

## Requirements

[1] ./

## License

Copyright [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
