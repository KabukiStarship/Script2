# [SCRIPT Specification RFC](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Objects](readme.md)

### ASCII Factory

Memory management for ASCII Data Types is handled using a C-function pointer called an ASCII Factory, or AsciiFactory, that uses the prototype:

```C++
/* ASCII Factory manages memory for ASCII Objects.
@return Nil upon failure or if no return socket is expected, or a pointer to a
word-aligned socket upon success.
@param obj      Pointer to an existing ASCII Object socket if there is one.
@param function A jump table function index.
@param arg      Pointer to the ASCII Factory argument. */
typedef int (*AsciiFactory)(UIW* obj, SIW function, void* arg);
```

An AsciiFactory is essentially switch statement jump table with an index for a function and one argument that can be a pointer to any type of object, which allows for multiple parameters.

#### ASCII Factory Functions

 All ASCII Object share the same set of AsciiFactory functions:

```C++
enum AsciiFactoryFunctions {
  kFactoryDelete = 0,  //< ASCII Factory function deletes an OBJ.
  kFactoryNew = 1,     //< ASCII Factory function creates a new OBJ.
  kFactoryClone = 2,   //< ASCII Factory function clones the OBJ.
  kFactoryGrow = 3,    //< ASCII Factory function double OBJ size in bytes.
  kFactoryInfo = 4,    //< Returns an info _::TStrand<> about the data type.
};
```
