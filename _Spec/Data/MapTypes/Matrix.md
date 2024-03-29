# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Vector Types](./)

***C++ Header***

```C++
template <typename SIZ = ISC>
struct TMatrix {
  SIZ size;                //< SIZ of the array in bytes.
  TStack<SIZ> dimensions;  //< The stack of dimensions.
};
```

***Memory Layout***

```AsciiArt
    +-----------------+
    |  C-Style Array  |
    |-----------------|
    | Dimension Stack |
 ^  |-----------------|
 |  |     Header      |
0xN +-----------------+
```

#### Examples

```Script2
/*             +---------------------- Operand Push "[IUA#2" with signature
               |                       <NIL>:<IUB#2>, Creates an Matrix and pushes
               |                       it onto the Operand Vector.
               |   +---------------- Operand '>':<
               |   |                 header onto stack.
               |   |  +------------- Operation 'x'<IUB>:<NIL> pushes a
               |   |  |              dimension on the Vector.
               |   |  | +----------- X Elements
               |   |  | | +--------- By Y elements
               |   |  | | | +------- By Z elements
               |   |  | | | | +----- Element (0,0,0)
               |   |  | | | | |      +------ Operation ','<IUB>:<NIL> sets the next
               |   |  | | | | |      |       matrix element.
               |   |  | | | | |      |  +--- Everything is just a function call so it's
               |   |  | | | | |      |  |    REALLY fast to interpret!
               v   v  v   v v v      v  v
ui1_matrix = [IUA#2<1 x 1 x 3>]{ 1, 2, (3) }
flt_matrix = [FLT#2<1 x 1 x 3>]{ 1.0, 2.0, 3.0 }
3d_matrix  = [IUA#2<1 x 3 x 3>]{ 1, 2, 3; 1, 2, 3; 1, 2, 3 }
/*                                                  ^
                                                    |
Matlab style Multi-dimensional matrix separator ---+   */
4d_matrix  = [IUA#2<2 x 2 x 2>]{ 1, 2; 1, 2 ;; 1, 2; 1, 2 }
/*                                          ^
              Use N semicolons where        |
              N is the Dimension Count -----+  */
```

**[<< Previous Section: Stack](Stack.md) | [Next Section: Map >>](Map.md)**

## Requirements

[1] ./

## License

Copyright [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
