# B-Sequences

B-Sequences (BSQ), as in the B in `A*B`, is a data structure that describes byte sequences using ASCII Data Types. BSQs are composed of a header that defines the byte stream layout. BSQs are similar *scanf* and *printf* format strings only you just use the % format tokens). BSQs are the ideal solution for serializing almost any type of data to save and load from drives, networks or any serial data stream. They are very easy to earn and nearly impossible to forget. There are 5 classes of types of BSQ parameters: types with a fixed POD sizes, types with pre-specified types at runtime **BSQ Headers** must be an array of unsigned integer types that use a single element to represent a single type (which is 8-bit). If a BSQ string starts with a positive integer then that BSQ is pre-allocating memory for the intepreter. If the number of observed parameters is less than the number of specified parameters the rest of the types are implied to be NIL. If the number of observed parameters is greater than the number of specified parameters triggers a warning that may trigger an error. BSQs may be nested.

## POD and Object Headers

```AsciiArt
{ n, p_1, ,..., p_n }
```

## String Headers

```AsciiArt
{ n + 1, STR, max_num_bytes, p_1, ..., p_n }
```

## Array Headers

```AsciiArt
{ n + 1, ARx, cr_data_type, num_items, p_1, ..., p_n }
```

## B-Sequence Header

```AsciiArt
{ num_params, p_1,..., p_n }
```

## B-Sequence Header Example

```Crabs
/*      +--------------- 4 input parameters.
        |   +----------- A _::TStrand<> of max length 31.
        |   |       +--- A signed integer with 1-byte width.
        |   |       |
        |   |       |               +-- There are 0 return parameters.
        |   |       |               |
        v   v       v               v */
   Foo <4, STR:32, ISA, ISB, ISC>:<NIL>
   Foo = <STR:32, ISA, ISB, ISC>:<NIL>    //< This is the same as before but takes more CPU processing power.
   Foo = <1, STR:32>:<3, ISA, ISB, ISC>
/*            ^     ^
              |     |
              |     +----- An 16-bit unsigned integer.
              +----------- A 32-bit dictionary. _B, _C, and _D may be used with any
                           ASCII Object Data Type for 2, 4, and 8-bit types. :-) */
   Bar <DIC, IUD>:<NIL>
   Bar = <<DIC, IUD>:<NIL>, <DIC, IUD>:<NIL>>
```

## Requirements

[1] ./

[SCRIPT Specification](../) **>** [ASCII Data Specification](./)

**[<< Previous Section: Strings](Strings.md) | [Next Section: Homo-tuples >>](HomoTuples.md)**

Copyright [AStarship™](https://astarship.net).
