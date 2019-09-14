# [SCRIPT Specification](../readme.md)

## [Crabs](readme.md)

### ASCII Expression Mappings



```Script2
  +-------------------------- Operation Push "=DIC2" is a function  
  |                           with address stuff that creates a
  |                           dictionary of size 64KB bytes with a
  |                           maximum of 3 entries and pushes it
  |                           onto the stack. This Operation Push
  v                           gets written to the new Expression. */
stuff =DIC4 65536 3 {
/*  +--------------------------- This is a function with key "kUI2".
    |       +------------------- This is a 16-bit unsigned int.
    |       |
    v       v */
    +=UI2 item1 1
    +----------------------------------- Operation with key "+=DIC2" same as
    |                                    "=DIC4" except it creates a nested
    |                                    dictionary except that it takes a
    |         +------------------------- Token (TKN) type.
    |         |     +------------------- This reserves about 32KB memory with
    |         |     |   +--------------- Maximum of 3 members.
    |         |     |   |
    v         v     v   v */
    +=DIC4 things 32768 3 {           /* This is a nested dictionary.
         +------------------------------ This is a operation with key "STR"
         |      +----------------------- Dictionary key.
         |      |    +------------------ Max length 12.
         |      |    |    +------------- STR value.
         |      |    |    |
         v      v    v    v */
        +=STR (item1 12 "ABC")
        -= "item1"                 //< Operation "-= STR" removes the key "item1"
        +=UI2 item1 1
        +=UI2 (item2, 2)
        +=UI2 item3 1
        -=Index 2                    //< Removes index 2:"item3".
        +=kSI2 item3 -1
        +=UI2 item4 1
        /*< We can't add item4 because we set the max elements to 3.
        This won't generate an error but may generate an error message. */
        Shrink  //< We just shrunk the DIC4 (i.e. chopped off the whitespace).
}

/** Using macros to pass return values as arguments.
    Do you have a better abbreviation for a dictionary?
    Example Function:
    FooBar <DIC4, UI1>:<NIL>
             ^     ^
             |     |
             |     +----- An 8-bit unsigned integer.
             +----------- That is 32-bit dictionary. ({:-)+=< */

FooBar ($stuff, 1);

Parent .Child1.Foo ("Number conversion Example" stuff.things.item1 stuff.things item2,
                   stuff things item3)

Parent Child1 Foo "Number conversion Example" stuff things item1 stuff things item2,
                   stuff things item3;
```

**[<< Previous Section:](./readme.md) | [Next Section: >>](./readme.md)**

## License

Copyright 2014-9 (C) [Cale McCollough](https://calemccollough.github.io); all rights reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
