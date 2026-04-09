# Matrix

An ASCII Matrix is an n-dimensional array of homogeneous plain-old-data (POD)
elements. Dimensions are stored in a `TStack` immediately after the header,
followed by the flat C-style element array.

## C++ Header

```C++
#define MTX_A typename T = ISW, typename ISZ = ISC, typename ISY = ISB
#define MTX_P T, ISZ, ISY

template<MTX_A>
struct TMatrix {
  ISZ bytes,              //< Total allocated bytes for the element array.
      elems;              //< Total number of matrix elements.
  TStack<T, ISZ, ISY> dimensions; //< Stack of per-axis extents.
};
```

| Template param | Role | Default |
|---|---|---|
| `T` | Element type | `ISW` |
| `ISZ` | Size / byte-count type | `ISC` (16-bit) |
| `ISY` | Dimension extent type | `ISB` (8-bit) |

## Memory Layout

```AsciiArt
    +--------------------+
    |   T[] Element      |  <- elem_count * sizeof(T) bytes
    |   Array            |
    |--------------------|
    |   ISY[] Dimension  |  <- dim_count * sizeof(ISY) bytes
    |   Extents          |
 ^  |--------------------|
 |  |   TStack header    |  <- total, count  (2 * sizeof(ISZ))
 |  |--------------------|
 |  |   TMatrix header   |  <- bytes, elems  (2 * sizeof(ISZ))
0xN +--------------------+
```

Total size in bytes:

```
sizeof(TMatrix<T,ISZ,ISY>) + dim_count*sizeof(ISY) + elem_count*sizeof(T)
```

where `elem_count = d0 * d1 * ... * d(N-1)`.

## Compile-time Dimension Metaprogramming

### `TDim<ISZ, N...>()`

Returns a pointer to a contiguous static array `[Count, d0, d1, ..., dN-1]`.

```C++
const ISB* d = TDim<ISB, ISB(4), ISB(3), ISB(2)>();
// d[0]=3  d[1]=4  d[2]=3  d[3]=2
```

Typed convenience wrappers: `TDimB`, `TDimC`, `TDimD`.

### `TDims<ISY, N...>`

Compile-time struct that captures the dimension pack as static constexpr
members and a packed table pointer.  Used as the `Dims` parameter of `AMatrix`.

```C++
using Dims = TDims<ISB, ISB(4), ISB(3), ISB(2)>;
static_assert(Dims::kCount == ISB(3));   // number of axes
static_assert(Dims::kElems == ISB(24));  // 4*3*2
const ISB* p = Dims::Dims();            // -> {3, 4, 3, 2}
```

`TDims<ISY>` (zero-extent specialisation) is the default for runtime-sized
matrices allocated on the heap.

### `TMatrixBOFDataBytes<T, ISY, N...>()`

Computes the data-section byte count (dimension extents + element array)
at compile time; used to size the in-place `TBOF`.

```C++
// 3*sizeof(ISB) + 24*sizeof(FPD) = 3 + 192 = 195
constexpr ISW n = TMatrixBOFDataBytes<FPD, ISB, ISB(4), ISB(3), ISB(2)>();
```

### `TMatrixBOFFromDims<T, ISZ, ISY, Dims>`

`using` alias that produces a `TBOF` exactly sized for the given `Dims`
descriptor. Passed as the `BOF` parameter of `AMatrix`.

### `AMatrix<T, ISZ, ISY, Dims, BOF>`

```C++
// Runtime heap matrix:
AMatrix<FPD> mat(4, 3, 2);

// Compile-time stack matrix (buffer lives inside the object):
AMatrix<FPD, ISC, ISB, TDims<ISB, ISB(4), ISB(3), ISB(2)>> mat;
```

## ASCII Script Examples

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
