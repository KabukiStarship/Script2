# [SCRIPT Specification RFC](../readme.md)

## [ASCII Data Specification](readme.md)

### Objects

ASCII Objects shall be composed of contiguous memory and begin with an 8, 16, 32 or 64-bit signed integer that specifies the object's size in bytes; this requirement is to reduce ROM size. There are 8 standard ASCII OBJ types:

|     Class       |      Type      |
|:---------------:|:--------------:|
|    Object       | User Definable |
|     Stack       |      Stack     |
|     Array       |      Array     |
|   B-Sequence    |     Metadata   |
|    B-Stream     |       Set      |
|      List       |       Set      |
|      Book       |       Set      |
|   Dictionary    |       Set      |
|      Map        |       Set      |

*Caption: Object Type Table*
