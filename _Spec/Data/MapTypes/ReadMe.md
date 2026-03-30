# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### Map Types

ASCII Map Types shall be composed of contiguous memory and begin with an 16, 32 or 64-bit signed integer that specifies the object's size in bytes; this requirement is the need to reduce ROM size. There are 8 standard ASCII OBJ types:

|     Class       |      Type      |
|:---------------:|:--------------:|
|    Object       | User Definable |
|     Array       |      Array     |
|     Stack       |      Stack     |
|     Matrix      |      Matrix    |
|   B-Sequence    |     Metadata   |
|    B-Stream     |       Set      |
|      List       |       Set      |
|      Loom       |       Set      |
|      Book       |       Set      |
|   Dictionary    |       Set      |
|      Map        |       Set      |

***Caption:*** *Object Type Table*

### Why So Many Dictionary Types?

We are running in RAM, and a dictionary could contain millions of key-value
pairs. Adding extra bytes would added megabytes of data we don't need. Also,
on microcontrollers, especially 16-bit ones, will have very little RAM, so we
need a 16-bit object. It is easy to imagine a complex AI software using
more than 4GB RAM, or the need to attach a DVD ISO image as a key-value
pair, so we need a 64-bit dictionary.

## Requirements

[1] ./

[SCRIPT Specification](../../) **>** [ASCII Data Specification](../) **>** [Map Types](./)

**[<< Previous Section: Map Types Overview](../) | [Next Section: Socket >>](Socket.md)**

Copyright [AStarship™](https://astarship.net).
