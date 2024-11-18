# [SCRIPT Specification](../)

## [Crabs Specification](./)

### Expressions

```Script2
  +-------------------------- Operation Push "=DICB" is a function  
  |                           with address stuff that creates a
  |                           dictionary of size 64KB bytes with a
  |                           maximum of 3 entries and pushes it
  |                           onto the stack. This Operation Push
  v                           gets written to the new Expression. */
stuff =DICD 65536 3 {
/*  +--------------------------- This is a function with key "_UIB".
    |       +------------------- This is a 16-bit unsigned int.
    |       |
    v       v */
    +=IUB item1 1
    +----------------------------------- Operation with key "+=DICB" same as
    |                                    "=DIC4" except it creates a nested
    |                                    dictionary except that it takes a
    |         +------------------------- Token (TKN) type.
    |         |     +------------------- This reserves about 32KB memory with
    |         |     |   +--------------- Maximum of 3 members.
    |         |     |   |
    v         v     v   v */
    +=DICD things 32768 3 {           /* This is a nested dictionary.
         +------------------------------ This is a operation with key "STR"
         |      +----------------------- Dictionary key.
         |      |    +------------------ Max length 12.
         |      |    |    +------------- STR value.
         |      |    |    |
         v      v    v    v */
        +=STR (item1 12 "ABC")
        -= "item1"                 //< Operation "-= STR" removes the key "item1"
        +=IUB item1 1
        +=IUB (item2, 2)
        +=IUB item3 1
        -=Index 2                    //< Removes index 2:"item3".
        +=ISB item3 -1
        +=IUB item4 1
        /*< We can't add item4 because we set the max elements to 3.
        This won't generate an error but may generate an error message. */
        Shrink  //< We just shrunk the DICD (i.e. chopped off the whitespace).
}

/** Using macros to pass return values as arguments.
    Do you have a better abbreviation for a dictionary?
    Example Function:
    FooBar <DICB, IUA>:<NIL>
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

**[<< Previous Section: Messages](./Messages.md) | [Next Section: SCRIPT Specification >>](../)**

## Requirements

[1] ./

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
