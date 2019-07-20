# [SCRIPT Specification](../../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [ASCII Data Specification](../readme.md)

### [Vector Types](./readme.md)

***C++ Header***

```C++
template <typename SIZ = SI4>
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
/*             +---------------------- Operand Push "[UI1#2" with signature
               |                       <NIL>:<UI2#2>, Creates an Matrix and pushes
               |                       it onto the Operand Vector.
               |   +---------------- Operand '>':<
               |   |                 header onto stack.
               |   |  +------------- Operation 'x'<UI2>:<NIL> pushes a
               |   |  |              dimension on the Vector.
               |   |  | +----------- X Elements
               |   |  | | +--------- By Y elements
               |   |  | | | +------- By Z elements
               |   |  | | | | +----- Element (0,0,0)
               |   |  | | | | |      +------ Operation ','<UI2>:<NIL> sets the next
               |   |  | | | | |      |       matrix element.
               |   |  | | | | |      |  +--- Everything is just a function call so it's
               |   |  | | | | |      |  |    REALLY fast to interpret!
               v   v  v   v v v      v  v
ui1_matrix = [UI1#2<1 x 1 x 3>]{ 1, 2, (3) }
flt_matrix = [FLT#2<1 x 1 x 3>]{ 1.0, 2.0, 3.0 }
3d_matrix  = [UI1#2<1 x 3 x 3>]{ 1, 2, 3; 1, 2, 3; 1, 2, 3 }
/*                                                  ^
                                                    |
Matlab style Multi-dimensional matrix separator ---+   */
4d_matrix  = [UI1#2<2 x 2 x 2>]{ 1, 2; 1, 2 ;; 1, 2; 1, 2 }
/*                                          ^
              Use N semicolons where        |
              N is the Dimension Count -----+  */
```
