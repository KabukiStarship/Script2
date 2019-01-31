# [SCRIPT Specification RFC](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

#### Stacks and Arrays

A Stack is a single dimensional array that reserves a total size that and may contain fewer items than the size allows but not more. The Stack Data Structure is designed to be memory aligned on all 16, 32, and 64-bit CPU Word sizes with restricts it's portable use to 16, 32, and 64-bit integer sizes due to the header being word-aligned on all systems with no wasted space. Multi-dimensional arrays are created from a Stack of dimensions that map to a packed 64-bit aligned C-style array.

Arrays shall be created using an Operand Stack Push the type abbreviation followed by #1, #2, #4, or #8 for 8, 16, 32, or 64-bit Array Types.

##### Stack Data Structure

```C++
template<typename SI = int>
struct Stack {
    SI total_size,  //< The total size of the Stack Array in 64-bit aligned bytes.
       header_size, //< The total Dimensions Header in 64-bit aligned bytes.
       height,      //< The total height of the Stack in elements.
       count;       //< The count of elements on the stack.
};
```

##### Stack Memory Layout

```AsciiArt
    +----------------+
    | 64-bit Aligned |
    |     Buffer     |
    |----------------|
 +  | Stack Elements |
 ^  |----------------|
 |  |  Stack struct  |
0xN +----------------+
```

##### Array Data Structure C++ Example

```C++
template<typename SI = int>
struct Array {
    Stack<SI> stack;
};
```

##### Array Memory Layout

```AsciiArt
    +------------------+
    |   Packed Array   |
    |------------------|
 +  | Dimensions Stack |
 ^  |------------------|
 |  |      Header      |
0xN +------------------+
```

#### Array Examples

```Script2
/*            +---------------------- Operand Push "[UI1#2" with signature
              |                       <NIL>:<UI2#2>, Creates an Array and pushes
              |                       it onto the Operand Stack.
              |   +---------------- Operand '>':<
              |   |                 header onto stack.
              |   |  +------------- Operation 'x'<UI2>:<NIL> pushes a
              |   |  |              dimension on the Stack.
              |   |  | +----------- X Elements
              |   |  | | +--------- By Y elements
              |   |  | | | +------- By Z elements
              |   |  | | | | +----- Element (0,0,0)
              |   |  | | | | |      +------ Operation ','<UI2>:<NIL> sets the next
              |   |  | | | | |      |       array element.
              |   |  | | | | |      |  +--- Everything is just a function call so it's
              |   |  | | | | |      |  |    REALLY fast to interpret!
              v   v  v   v v v      v  v
ui1_array = [UI1#2<1 x 1 x 3>]{ 1, 2, (3) }
flt_array = [FLT#2<1 x 1 x 3>]{ 1.0, 2.0, 3.0 }
3d_array  = [UI1#2<1 x 3 x 3>]{ 1, 2, 3; 1, 2, 3; 1, 2, 3 }
                                               /*   ^
                                                    |
Matlab style Multi-dimensional array separator ---+   */
4d_array  = [UI1#2<2 x 2 x 2>]{ 1, 2; 1, 2 ;; 1, 2; 1, 2 }
/*                                          ^
              Use N semicolons where        |
              N is the Dimension Count -----+  */
```