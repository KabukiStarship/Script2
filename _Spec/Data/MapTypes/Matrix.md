# Matrix

***C++ Header***

```C++
template<MTX_A>
struct TMatrix {
  ISZ bytes,      //< Size in bytes.
      elems;      //< Total number of matrix elements.
  TStack<T, ISZ> dimensions; //< Stack of dimensions.
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

## Examples

```Crabs
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
fpd_matrix = [FPD#2<1 x 1 x 3>]{ 1.0, 2.0, 3.0 }
3d_matrix  = [IUA#2<1 x 3 x 3>]{ 1, 2, 3; 1, 2, 3; 1, 2, 3 }
/*                                                  ^
                                                    |
Matlab style Multi-dimensional matrix separator ---+   */
4d_matrix  = [IUA#2<2 x 2 x 2>]{ 1, 2; 1, 2 ;; 1, 2; 1, 2 }
/*                                          ^
              Use N semicolons where        |
              N is the Dimension Count -----+  */
```

## Requirements

[1] ./

[SCRIPT Specification](../../) **>** [ASCII Data Specification](../) **>** [Map Types](./)

**[<< Previous Section: Stack](Stack.md) | [Next Section: Map >>](Map.md)**

Copyright [AStarship™](https://astarship.net).
