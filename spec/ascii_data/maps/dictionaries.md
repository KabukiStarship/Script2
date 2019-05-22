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
