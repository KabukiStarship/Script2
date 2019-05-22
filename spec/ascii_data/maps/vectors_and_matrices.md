# [SCRIPT Specification RFC](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

#### Vectors and Matrices

A Vector is a single dimensional matrix that reserves a total size that and may contain fewer items than the size allows but not more. The Vector Data Structure is designed to be memory aligned on all 16, 32, and 64-bit CPU Word sizes with restricts it's portable use to 16, 32, and 64-bit integer sizes due to the header being word-aligned on all systems with no wasted space. Multi-dimensional matrixs are created from a Vector of dimensions that map to a packed 64-bit aligned C-style matrix.

Matrices shall be created using an Operand Vector Push the type abbreviation followed by #1, #2, #4, or #8 for 8, 16, 32, or 64-bit Matrix Types.

##### Vector Data Structure

```C++
template<typename SI = int>
struct Vector {
    SI size_bytes,  //< The total size of the Vector Matrix in 64-bit aligned bytes.
       size_header, //< The total Dimensions Header in 64-bit aligned bytes.
       height,      //< The total height of the Vector in elements.
       count;       //< The count of elements on the stack.
};
```

##### Vector Memory Layout

```AsciiArt
    +-----------------+
    | 64-bit Aligned  |
    |     Buffer      |
    |-----------------|
 +  | Vector Elements |
 ^  |-----------------|
 |  |  Vector struct  |
0xN +-----------------+
```

##### Matrix Data Structure C++ Example

```C++
template<typename SI = int>
struct Matrix {
    Vector<SI> stack;
};
```

##### Matrix Memory Layout

```AsciiArt
    +-------------------+
    |    Packed Matrix   |
    |-------------------|
 +  | Dimensions Vector |
 ^  |-------------------|
 |  |      Header       |
0xN +-------------------+
```

#### Matrix Examples

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
                                               /*   ^
                                                    |
Matlab style Multi-dimensional matrix separator ---+   */
4d_matrix  = [UI1#2<2 x 2 x 2>]{ 1, 2; 1, 2 ;; 1, 2; 1, 2 }
/*                                          ^
              Use N semicolons where        |
              N is the Dimension Count -----+  */
```
