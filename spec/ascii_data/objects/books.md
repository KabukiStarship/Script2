# [SCRIPT Specification RFC](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

#### Books

ASCII Books are dense ordered maps of key-{type-value} tuples. Books differ from ASCII Dictionaries in that multiple values with the same key may be stored. Books use the

##### Book Memory Layout

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
    |        ...               |   |     |
    |        buffer            |   |     |
    |==========================|   |     |
    |_______ count_max         |   |     |
    |_______ ...               |   |    Size
    |_______ Key Offset N      |   |     |
    |_______ ...               |   |     |
    |        Key Offset 1      |   |     |
    |==========================| Header  |
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
