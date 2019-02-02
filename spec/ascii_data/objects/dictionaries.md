# [SCRIPT Specification RFC](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

#### Dictionaries

Dictionaries are key-type-value sets with a hash table of unique keys. Hash sizes my be 16-bit with up to 120 members, 32-bit with up to 2^24 items, or 64-bit with up to 256 * 10^6 items. Dictionaries have slower insert times than ASCII Books but faster lookup.

##### Dictionary Memory Layout

```AsciiArt
    +==========================+ -----------
    |_______ Buffer            |   ^     ^
    |_______ ...               |   |     |
    |_______ Data N            |  Data   |
    |_______ ...               |   |     |
    |_______ Data 0            |   v     |
    |==========================| -----   |
    |        Key 1             |   ^     |
    |        ...               |   |     |
    |        Key N             |   |     |
    |vvvvvvvvvvvvvvvvvvvvvvvvvv|   |     |
    |        buffer            |   |     |
    |^^^^^^^^^^^^^^^^^^^^^^^^^^|   |     |
    |_______ Collision N       |   |     |
    |_______ ...               |   |     |
    |        Collision 1       |   |     |
    |==========================|   |     |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Collision Index N |   |     |
    |_______ ...               |   |     |
    |        Collision Index 1 |   |     |
    |==========================|   |    Size
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Collision Table N |   |     |
    |_______ ...               |   |     |
    |        Collision Table 1 |   |     |
    |==========================| Header  |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Key Offset N      |   |     |
    |_______ ...               |   |     |
    |        Key Offset 1      |   |     |
    |==========================|   |     |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Sorted Mappings N |   |     |
    |_______ ...               |   |     |
    |        Sorted Mappings 1 |   |     |
    |==========================|   |     |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Data Offset N     |   |     |
    |_______ ...               |   |     |
    |        Data Offset 1     |   |     |
    |==========================|   |     |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Type byte N       |   |     |
    |_______ ...               |   |     |
    |        Type byte 1       |   |     |   ^ Up in addresses
    |==========================|   |     |   |
    |  TMapKey<UI, SI> Struct  |   v     v   ^
    +==========================+ ----------- ^ 0xN
```

##### Book Memory Overhead

| #Bytes | Index | Offset | Hash  | Total | Overhead Per index |
|:------:|:-----:|:------:|:-----:|:-----:|:-------------------|
|    2   |   1   |    2   |   2   |   8   |  8 + 3  per index + buffer.|
|    4   |   2   |    4   |   4   |   16  | 16 + 4  per index + buffer.|
|    8   |   4   |    8   |   8   |   32  | 24 + 16 per index + buffer.|

* All sizes listed in bytes.

### Dictionary Example

```
  +-------------------------- Operation Push "=DIC2" is a function  
  |                           with address stuff that creates a
  |                           dictionary of size 64KB bytes with a
  |                           maximum of 3 entries and pushes it
  |                           onto the stack. This Operation Push
  v                           gets written to the new Expression. */
stuff =DIC4 65536 1 {
/*  +--------------------------- This is a function with key "kUI2".
    |       +------------------- This is a 16-bit unsigned int.
    |       |
    v       v */
    +=kUI2 item1 1
    +----------------------------------- Operation with key "+=DIC2" same as
    |                                    "=DIC4" except it creates a nested
    |                                    dictionary except that it takes a
    |         +------------------------- Token (kTKN) type.
    |         |     +------------------- This reserves about 32KB memory with
    |         |     |   +--------------- Maximum of 3 members.
    |         |     |   |               
    v         v     v   v             */
    +=DIC4 things 32768 3 {           /* This is a nested dictionary.
         +------------------------------ This is a operation with key "kSTR"
         |      +----------------------- Dictionary key.
         |      |    +------------------ Max length 12.
         |      |    |    +------------- kSTR value.
         |      |    |    |
         v      v    v    v         */
        +=kSTR (item1 12 "ABC")
        -=Key item1                  //< Operation "-=Key" removes "item1"
        +=kUI2 item1 1
        +=kUI2 (item2, 2)
        +=kUI2 item3 1
        -=Index 2                    //< Removes index 2:"item3".
        +=kSI2 item3 -1
        +=kUI2 item4 1
        /*< We can't add item4 because we set the max elements to 3.
            This won't generate an error but may generate an error
            message. */
        Shrink  //< We just shrunk the DIC4. Sorry, but I had to. Have fun. :-)
}
/** Using macros to pass return values as arguments.
    Do you have a better abbreviation for a dictionary?
    Example Function:
    FooBar <DIC4, kUI1>:<kNIL>
             ^     ^
             |     |
             |     +----- An 8-bit unsigned integer.
             +----------- That is 32-bit dictionary. ({:-)+=< */
FooBar ($stuff, 1);

Parent .Child1.Foo ("Number conversion Example" stuff.things.item1 stuff.things.item2,
                   stuff things item3)

Parent Child1 Foo "Number conversion Example" stuff things item1 stuff things item2,
                   stuff things item3;
 ```
 