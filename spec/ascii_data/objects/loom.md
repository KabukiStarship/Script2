# [SCRIPT Specification RFC](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

#### Loom

ASCII Loom (LOM) is an array of UTF-8, UTF-16, or UTF-32 strings without a hash table. Strings lengths in Script are capped at type int, which gives a maximum length of 2^31 array elements; in cases where strings grow beyond this length, which is defined as extremely rare, a 64-bit Loom shall be used and the Loom shall be treated as a single long _::TStrand<>.

##### Sequence Memory Layout

```AsciiArt
    +==========================+ -----------
    |_______ Strings 0         |  Strings   |
    |_______ ...               |   |     |
    |_______ Data N            |   v     |
    |_______ ...               |   |     |
    |_______ Buffer            |   ^     ^
    |==========================| -----   |
    |_______ count_max         |   ^     |
    |_______ ...               |   |     |
    |_______ Sorted Mappings N |   |     |
    |_______ ...               |   |     |
    |        Sorted Mappings 1 |   |     |
    |==========================|   |     |
    |_______ count_max         |   |    Size
    |_______ ...               |   |     |
    |_______ Data Offset N     |   |     |
    |_______ ...               | Header  |
    |        Data Offset 1     |   |     |
    |==========================|   |     |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Type byte N       |   |     |
    |_______ ...               |   |     |
    |        Type byte 1       |   |     |   ^ 0x(N+c)+sizeof(AsciiList<UI, SI>)
    |==========================|   |     |   |
    |  AsciiMap<UI, SI> Struct |   v     v   ^
    +==========================+ ----------- ^ 0xN
```
