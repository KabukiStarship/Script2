SCRIPT Specification RFC
========================

# 2 ASCII Data Types Specification

There are 32 Automaton Standard Code for Information Interchange (ASCII) Data Types composed of 23 Plain-Old-Data and 8 object types composed of contiguous memory. Types are stored as bytes where the 5 LSb are used to store the type and the upper 3 bits are used to store either bit width of the size of the object, 8, 16, 32, or 64-bit, or to store the dimensions of a stack or multi-dimensional array. Implementations shall support types SVI, UVI, ADR, and STR and may support more types.

## 2.1 Type Byte

All ASCII Types can be represented as a single byte where the lower 5 bits are used to store the type, and the upper three bits are used to store if the type is an array.

|   b7-b6   |     b5   |   b4-b0   |
|:---------:|:--------:|:---------:|
| bit_width | is_stack | type 0-31 |

### 2.1.a ASCII Data Types 0-31

| ID | Type |  Alt Name  | Width  | Description         |
|:--:|:----:|:----------:|:------:|:--------------------|
|  0 | NIL  |  null/void |    0   | Nil/null/void type. |
|  1 | SI1  |    int8_t  |   -1   | 8-bit signed integer. |
|  2 | UI1  |   uint8_t  |    1   | 8-bit unsigned integer. |
|  3 | BOL  |    bool    |    4   | Non-zero false Boolean variable. |
|  4 | SI2  |   int16_t  |   -2   | 16-bit signed varint. |
|  5 | UI2  |  uint16_t  |    2   | 16-bit unsigned integer. |
|  6 | HLF  |    half    |    2   | 16-bit floating-point number. |
|  7 | SI4  |   int32_t  |   -4   | 32-bit signed varint. |
|  8 | UI4  |  uint32_t  |    4   | 32-bit unsigned integer. |
|  9 | FLT  |    float   |    4   | 32-bit floating-point number. |
| 10 | TM4  |   int32_t  |   -4   | 32-bit signed integer second since epoch timestamp. |
| 11 | TME  |   int64_t  |   -8   | 32-bit signed integer second since epoch timestamp with 32-bit signed integer sub-second ticker. |
| 12 | TM8  |   int64_t  |   -8   | 64-bit microsecond since epoch timestamp. |
| 13 | SI8  |   int64_t  |   -8   | 64-bit signed integer. |
| 14 | UI8  |  uint64_t  |    8   | 64-bit unsigned integer. |
| 15 | DBL  |   double   |    8   | 64-bit floating-point number. |
| 16 | SIH  |  int128_t  |  -16   | 128-bit signed integer. |
| 17 | UIH  | uint128_t  |   16   | 128-bit unsigned integer. |
| 18 | DEC  |   Decimal  |   16   | 128-bit floating-point number. |
| 19 | UIX  |  Unsigned  | 32-4KB | Unsigned integer between 32 and 2^12 bits wide. |
| 20 | ADR  |   Address  |  <=N   | Stack Operation Address. |
| 21 | STR  |   String   |  <=N   | UTF-8 string. |
| 22 | TKN  |   Token    |  <=N   | UTF-8 string without any whitespace. |
| 23 | BSQ  | B-Sequence |  <=N   | B-Sequence. |
| 24 | OBJ  |   Object   |    N   | N-byte object composed of contiguous memory. |
| 25 | LOM  |   Loom     |    N   | An array of UTF-8, UTF-16, or UTF-32 strings without a hash table. |
| 26 | TBL  |   Table    |    N   | A hash-table of strings with contiguous indexes. |
| 27 | EXP  | Expression |  <=N   | Script expression of B-Sequences. |
| 28 | LST  |   List     |    N   | Stack of type-Records with contiguous indexes starting at zero. |
| 29 | MAP  |    Map     |    N   | Unique map of integer-Record records. |
| 30 | BOK  | Multidict  |    N   | A Book, or Multidictionary, of Records without a hash table. |
| 31 | DIC  | Dictionary |    N   | Unique map of key-value records with a hash table. |

#### Extended ASCII Data types

|   Bits   | Index | Type |  Alt Name  | Width   | Description |
|:--------:|:-----:|:----:|:----------:|:-------:|:------------|
| 01010101 |  123  | xyx  |  Example   | Example | The fox jumped over the fence. |

Extended ASCII Data Types are types utilize illegal Primary ASCII Data Types as other data types.

### 2.1.b List of Types Key

| Width | Description |
|:-----:|:------------|
|  -X   | Signed integer type.|
|   ?   | Type of unknown size.|
|   N   | Has pre-specified buffer of size N bytes.|
| <=N   | Has pre-specified buffer of size N bytes but can use less than that.|

## 2.2 Integers

Script supports both traditional 8, 16, 32, and 64-bit, and n-byte signed 2's complement integers and unsigned uncomplemented integers. For n-byte integers, implementations may implement n-byte integer math and may require n to be 8, 16, or 32 bytes.

### 2.2.a Valid Integers Examples

```C++
SI1 0
UI1 255
SI2 -32,000
SI4 0xFFFF
```

### 2.2.b Invalid Integer Examples
```C++
SI1 256       ; Too big for size
SI2 0xFFFFF   ; Too big for size
```

## 2.2.c Unsigned Not-a-Numbers

Unsigned Not-a-Number (U-NaN) is the bit pattern with all ones as in the following example:

```C++
template<typename UI = uintptr_t>
inline UI NaNUnsigned () {
  UI nan = 0;
  return ~nan;
}
```

## 2.2.d Signed Not-a-Numbers

Unsigned Not-a-Number (S-NaN) is the bit pattern with only the Most Significant bit asserted as in the following example:

```C++
template<typename SI, typename UI>
inline SI NaNSigned () {
  UI nan = 1;
  return (SI)(nan << (sizeof (UI) * 8 - 1));
}
```

## 2.2.e Varints

Variants are MSb variant are compressed using MSB-encoded signed and unsigned 1-to-9-byte variable-length integers. Varints use the MSb of each byte to determine if another byte is to be loaded. This allows values less than 128 to be sent using only one byte, 14-bit values in two bytes, 21-bit values in three bytes and so on.  

Both Signed and Unsigned Varints must use the most significant bit asserted is used to marks if another byte is loaded. All Script implementations shall represent signed varints as uncomplemented integers with the sign bit in the LSb.

```C++
UVI 128 // = 0b0000_0001_1000_0000
UVI 255 // = 0b0000_0001_1111_1111
SVI -64 // = 0b0011_1111
```
## 2.2.f X-Byte Unsigned Integers

X-Byte Signed Integers (SIN) and Unsigned Integers (UIN) are integers that may be 0-N bytes in width. SIN and UIN are very useful for transferring 128+ bit hashes and custom data structures. Implementations may implement n-byte arithmetic.

#### Example

```C++
// static const unsigned int sin_uin_bsq_example = { 2, SIN, 8, UIN 16 };
SIX -1
UIX 1
```

## 2.3 Boolean

Booleans in Script are stored as 32-bit types where the deasserted value shall be stored as the number zero and labeled false, and asserted values shall be represented as the number one labeled true or a non-zero SVI value.

### Boolean Examples

```C++
// All values less then 127 and greater than -127
BOL true   //< Translates to the number 1
BOL false  //< Translates to the number 0
BOL 0
BOL 1
BOL -129   //< Will require 2 bytes to transceive.
```

## 2.4 Floating-point Numbers

Script supports, 16, 32, and 64-bit floating-point numbers, also called half, float, and double precision float-point numbers. Floating-point numbers do not lend themselves very well to varint compression, so using a 16-bit floating-point number can dramatically improve performance when low-precision is needed. Implementations may implement 128-bit floating-point math. 128-bit floating point numbers are compatible with the C# programming language.

```C++
HLF 0.0     // Use a HLF to save memory and bandwidth!
FLT 0.1     // Wastes a lot of space!
DBL - 0.1;  // Wastes a whole lot of space!
DEC 1.0     // Wastes a TRUCK TON of space!
```

## 2.5 Addresses, Strings, and Tokens

Script supports UTF-8, UTF-16, and UTF-32 strings (STR), and UTF-8 Addresses (ADR) and Tokens (TKN). TKN and ADR shall contain no whitespace or non-printable characters, i.e. no characters with index less than 33. A Script implementation may enforce strict Unicode compliance. Packed Messages shall use nil-terminated strings and Unpacked Script shall use double-quote-terminated strings with C-style escape sequences. Implementation that support Script^2 shall provide a delimiter char.

```C++
TKN key                 //< No quotes needed for a TKN.
ADR 123                 //< A ADR is a TKN.
STR  "\"Hello world!\"" //< String that reads "Hello world!" with double quotes.
                        //< There is no need to use a 1 to make STR1.
STR2 "\"Hello world!\"" //< This is a string that is up to 64KB long.
STR4 "\"Hello world!\"" //< This is a string that is up to 4GB long.
STR8 "\"Hello world!\"" //< This is a string that is up to 2^64-1 bytes long.
```

## 2.6 Timestamps

ASCII provides three types of timestamps, a 32-bit signed integer TMS seconds from epoch timestamp, a 64-bit signed integer TME seconds from epoch timestamp, and 64-bit Time Sub-second (TSS) timestamp composed of a TMS timestamp and a UI4 tick that gets incremented at a variable time period. The Sub-second Tick Epoch (STE) shall be programmable but shall be set to the defaults of either 1000 or 64, depending on if a microsecond or OS update timer is used respectively. It is important to note that ASCII Timestamps do not contain the STE period by design.

```C++
/* Example functions.
@fn Foo <TMS>:<NIL>
@fn Foo <TME>:<NIL>
@fn Foo <TSS>:<NIL>

# Timestamp Format
| Seconds Since Epoch | Microseconds Since Epoch |
|:-------------------:|:------------------------:|
| YYYY-MM-DD@HH:MM:ss |  YYYY-MM-DD@HH:MM:ss:uu  |

 Month ---v        v—-Minutes  */
Foo 2016-07-13@15:39:23
/*               Hours--^     ^--- seconds
Year --v     v--- Day     v-- ticks */
Foo 2016-07-13@15:39:23:999
```

### 2.6.a Epoch and Invalid Timestamps

The 32-bit time epoch shall be 16 years starting at the January 1st of the beginning of each decade beginning from 0 AD but not starting until January 1st 2032. Before January 1st 2032 the epoch shall be the Unix Timestamp Epoch.

#### Max 32-bit Timestamp Range

`(+/-) ((2^30)-1)/(60*60*24*365) = (+/-) 36 years`

#### Max 64-bit Timestamp Range

`(+/-) ((2^62)-1)/(60*60*24*365) = (+/-) 146,235,604,338 years`

## 2.8 Objects

ASCII Objects shall be composed of contiguous memory and begin with an 8, 16, 32 or 64-bit unsigned integer that specifies the object's size in bytes.

### 2.11.a Object Type Table

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

### 2.11.a Stacks and Arrays

A Stack is a single dimensional array that reserves a total size that and may contain fewer items than the size allows but not more. The Stack Data Structure is designed to be memory aligned on all 16, 32, and 64-bit CPU Word sizes with restricts it's portable use to 16, 32, and 64-bit integer sizes due to the header being word-aligned on all systems with no wasted space. Multi-dimensional arrays are created from a Stack of dimensions that map to a packed 64-bit aligned C-style array.

Arrays shall be created using an Operand Stack Push the type abbreviation followed by #1, #2, #4, or #8 for 8, 16, 32, or 64-bit Array Types.

#### Stack Data Structure

```
template<typename SI = int>
struct Stack {
    SI total_size,  //< The total size of the Stack Array in 64-bit aligned bytes.
       header_size, //< The total Dimensions Header in 64-bit aligned bytes.
       height,      //< The total height of the Stack in elements.
       count;       //< The count of elements on the stack.
};
```

#### Stack Memory Layout

```
    +----------------+
    | 64-bit Aligned |
    |     Buffer     |
    |----------------|
 +  | Stack Elements |
 ^  |----------------|
 |  |  Stack struct  |
0xN +----------------+
```

#### Array Data Structure C++ Example

```
template<typename SI = int>
struct Array {
    Stack<SI> stack;
};
```

#### Array Memory Layout

```
    +------------------+
    |   Packed Array   |
    |------------------|
 +  | Dimensions Stack |
 ^  |------------------|
 |  |      Header      |
0xN +------------------+
````

#### Array Examples

Script uses a modified MatLab/Octave-style syntax that allows for Script Stack Operations.

```
/*              +---------------------- Operand Push "[UI1#2" with signature
                |                       <NIL>:<UI2#2>, Creates an Array and pushes
                |                       it onto the Operand Stack.
                |     +---------------- Operand '>':<
                |     |                 header onto stack.
                |     |  +------------- Operation 'x'<UI2>:<NIL> pushes a
                |     |  |              dimension on the Stack.
                |     |  | +----------- X Elements
                |     |  | | +--------- By Y elements
                |     |  | | | +------- By Z elements
                |     |  | | | | +----- Element (0,0,0)
                |     |  | | | | |      +------ Operation ','<UI2>:<NIL> sets the next
                |     |  | | | | |      |       array element.
                |     |  | | | | |      |  +--- Everything is just a function call so it's
                |     |  | | | | |      |  |    REALLY fast to interpret!
                v     v  v   v v v      v  v
let ui1_array = [UI1#2<1 x 1 x 3>]{ 1, 2, (3) }
let flt_array = [FLT#2<1 x 1 x 3>]{ 1.0, 2.0, 3.0 }
let 3d_array  = [UI1#2<1 x 3 x 3>]{ 1, 2, 3; 1, 2, 3; 1, 2, 3 }
                                               /*   ^
                                                    |
  Matlab style Multi-dimensional array separator ---+   */
let 4d_array  = [UI1#2<2 x 2 x 2>]{ 1, 2; 1, 2 ;; 1, 2; 1, 2 }
/*                                             ^
                 Use N semicolons where        |
                 N is the Dimension Count -----+  */
```

#### Examples of Arrays with Errors
```
[UI2#3<2: 1 x 0>]               // Array type must be 2, 4, or 8!
[UI#2<2: 1 x 70,000>]           // Too many members to fit in an Array2!
[HLF#2<2: 1 x 2> 0.1, 0.0, 0.3] // Too many members!
[MAP#4<1>]                      // Can't contain Hierarchical data types!
```

## 2.9 B-Sequences

B-Sequences, as in the B in A/*B, is a data structure that describes byte sequences using the 32 ASCII Data Types. B-Sequences are composed of a header that defines the data and the actual byte stream itself. B-Sequences are similar *scanf* and *printf* format strings only you just use the % format tokens). B-Sequences are the ideal solution for serializing almost any type of data to save and load from drives, networks or any serial data stream. They are very easy to earn and nearly impossible to forget.

## 2.9 B-Sequence Headers

There are 5 classes of types of B-Sequence parameters: types with a fixed POD sizes, types with length specified at ahead of time, string types that must be less than a given number of characters known ahead of time, Array types of the POD types excluding strings, and object types whose size is not known at compile time. **B-Sequences Headers** must be an array of unsigned integer types that use a single element to represent a single type (which is 8-bit).

#### POD and Object Headers

```
{ n, p_1, ,..., p_n }
```

#### String Headers

```
{ n + 1, STR, max_num_bytes, p_1, ..., p_n }
```

#### Array Headers

```
{ n + 1, ARx, cr_data_type, num_items, p_1, ..., p_n }
```

#### B-Sequence Header

```
{ num_params, p_1,..., p_n }
```

# Example

```
/*      +--------------- 4 input parameters
        |   +----------- A string of max length 31.
        |   |       +--- A signed integer with 1-byte (8-bit) width.
        |   |       |
        |   |       |               +-- There are 0 return parameters.
        |   |       |               |
        v   v       v               v */
   Foo <4, STR:32, SI1, SI2, SI4>:<NIL>
   Bar <1, STR:32>:<3, SI1, SI2, SI4>
   FooBar <DIC4, UI2>:<NIL>
/*          ^     ^
            |     |
            |     +----- An 16-bit unsigned integer.
            +----------- A 32-bit dictionary. _2, _4, and _8 may be used with any
                         ASCII Object Data Type for 16, 32, and 64-bit types. DIC4
                         may also make a rather funny or inappropriate joke when put
                         on coworkers foreheads. :-) */
```

## 2.8 ASCII Maps

ASCII Maps are Associative Arrays of ASCII Data Types that may have one or more levels of hierarchy. ASCII Maps come in 4 flavors: List, Map, Multimap, and Dictionary. All of the ASCII Map types use the same TMap data structure.

ASCII Maps are not created in text like Plain-Old-Data types and are created using CRABS.  Sets shall begin with a word that may be 8, 16, 32, or 64-bits in length. For all systems with DDR RAM, 8 and 16-bit words have the fastest read/lookup but may have slower insert than 32-bit and 64-bit dictionaries.

### 2.8.a Set C++ Data Structure

```
template<typename UI, typename SI, typename I>
struct TMap {
    UI size;       //< ASCII Object size.
    SI table_size, //< Size of the key strings in bytes.
       pile_size;  //< Size of the collisions pile in bytes, or 0 if unused.
    I  item_count, //< Number of items.
       count_max;  //< Max number of items that can fit in the header.
};
```
### 2.10.a Hash Function

**@warning** *Hash function used may change to use an XOR method*.

All strings are hashed using a prime multiple with the initial value of the largest possible prime that can fit in a 16, 32, or 64-bit size.

#### Hash Function and Overhead

16, 32, and 64-bit hashes all use the same formula. You multiply the current byte by the magic prime (i.e. the largest 16, 32, or 64-bit prime) and add it to the current hash.

#### C Hash Functions

```
inline hash16_t Hash16 (char c, hash16_t hash) {
    return cprime + (c * 65521);
}

hash16_t Hash16 (const char* s, hash16_t hash) {
    byte c = *s;
    while (c) {
        hash = Hash16 (c, hash);
        ++s;
        c = *s;
    }
    return hash;
}

inline hash32_t Hash32 (char c, hash32_t hash) {
    hash32_t cprime = c * 4294967291;
    return cprime + hash;
}

hash16_t Hash32 (const char* s, hash32_t hash) {
    byte c = *s;
    while (c) {
        hash = Hash32 (c, hash);
        ++s;
        c = *s;
    }
    return hash;
}

inline hash64_t Hash64 (char c, hash64_t hash) {
    hash64_t cprime = c * 18446744073709551557;
    return cprime + hash;
}

hash64_t Hash64 (const char* s, hash64_t hash) {
    byte c = *s;
    while (c) {
        hash = Hash64 (c, hash);
        ++s;
        c = *s;
    }
    return hash;
}
```

## 2.4 Escape Sequence

An Escape Sequence (ESC) is a sequence of one or more Script Expressions that replaces a B-Sequence and ends with no Operands on the stack. ESC objects may be 8, 16, 32, or 64-bit to represent the Object's Size. Script Expressions may have multiple output parameters and ESC will be evaluated and the socket output, if ESC Operations have the same output signature, may be directly substituted for any BSQ with the same signature.

#### ESC Example

```
Parent.Child1.Foo ("Hello world!", 1, 2, 3); //< () and ',' are optional and
Parent Child1 Foo "Hello world!", 1, 2, 3; //< Pop Operations are programmable.
Parent Child1 Foo "Hello world!" 1 2 3     //< There is no pop instruction here
              Foo "Hello "                 //< so this is a string of Ops.
                  "world!" 1 2
                  3;                      //< The Last 2 Foo calls execute when
                                          //< the ";" operation is read or
                                          //<
Parent {                                  
    Child1 {
        Foo ("Hello world!", 1, 2, 3)
        Foo ("Hello world!", 1, 2, 3)    //< String operations together!
        Bar ("Lets go!")
    }
    Child2 {
        Foo ("Hello world!" 1, 2, 3)
    }
} //< Code won't execute until you close the curly brackets or type ';'
```

### Dictionaries

Dictionaries are key-type-value sets with a hash table of unique keys. Hash sizes my be 16-bit with up to 120 members, 32-bit with up to 2^24 items, or 64-bit with up to 256 * 10^6 items. Dictionaries have slower insert times than ASCII Books but faster lookup.

#### Dictionary Memory Layout

```
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
    |vvvvvvvvvvvvvvvvvvvvvvvvvv|   |     |
    |        buffer            |   |     |
    |^^^^^^^^^^^^^^^^^^^^^^^^^^|   |     |
    |_______ Collision N       |   |     |
    |_______ ...               |   |     |
    |        Collision 1       |   |     |
    |==========================|   |     |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Collision Index N |   |     |
    |_______ ...               |   |     |
    |        Collision Index 1 |   |     |
    |==========================|   |    Size
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Collision Table N |   |     |
    |_______ ...               |   |     |
    |        Collision Table 1 |   |     |
    |==========================| Header  |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Key Offset N      |   |     |
    |_______ ...               |   |     |
    |        Key Offset 1      |   |     |
    |==========================|   |     |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Sorted Mappings N |   |     |
    |_______ ...               |   |     |
    |        Sorted Mappings 1 |   |     |
    |==========================|   |     |
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

#### Book Memory Overhead

| #Bytes | Index | Offset | Hash  | Total | Overhead Per index |
|:------:|:-----:|:------:|:-----:|:-----:|:-------------------|
|    2   |   1   |    2   |   2   |   8   |  8 + 3  per index + buffer.|
|    4   |   2   |    4   |   4   |   16  | 16 + 4  per index + buffer.|
|    8   |   4   |    8   |   8   |   32  | 24 + 16 per index + buffer.|

* All sizes listed in bytes.

##### Dictionary Examples

### b. Books

ASCII Books are dense ordered maps of key-{type-value} tuples. Books differ from ASCII Dictionaries in that multiple values with the same key may be stored. Books use the

#### Book Memory Layout

```
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

### c. List

Lists are stacks of type-value tuples similar in memory layout to Books but they **do not** have keys. Functionally they are identical to B-Sequences expect the offsets are stored as an Array to eliminate the need to scan through the header to calculate the data offset. Sequences are ideal for situations where the fastest possible RW performance is needed.

#### Sequence Memory Layout

```
    +==========================+ -----------
    |_______ Buffer            |   ^     ^
    |_______ ...               |   |     |
    |_______ Data N            |  Data   |
    |_______ ...               |   |     |
    |_______ Data 0            |   v     |
    |==========================| -----   |
    |_______ count_max         |   ^     |
    |_______ ...               |   |     |
    |_______ Data Offset N     |   |     |
    |_______ ...               |   |    Size
    |        Data Offset 1     |   |     |
    |==========================| Header  |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Type byte N       |   |     |
    |_______ ...               |   |     |
    |        Type byte 1       |   |     |   ^ 0x(N+c)+sizeof(AsciiList<UI, SI>)
    |==========================|   |     |   |
    | AsciiList<UI, SI> Struct |   v     v   ^
    +==========================+ ----------- ^ 0xN
```

#### Sequence Memory Overhead
| #Bits | Max # Members | Max Header Size | Max Data Size | Overhead Per Set   |
|:-----:|:-------------:|:---------------:|:-------------:|:------------------:|
|   16  |      255      |     2^16        |       2^16    |   6 + 3 per index. |
|   32  |     2^16 - 1  |     2^32        |       2^32    |   16 + 5 per index.|
|   64  |     2^25 – 1  |     2^32        |       2^64    |   24 + 9 per index.|

* All sizes listed in bytes.

### d. Map

Maps are one-to-one maps of Id-{Type-Value} tuples identical in structure to Lists with the exception that the . are stacks of type-value tuples similar in memory layout to Books but they **do not** have keys. Functionally they are identical to B-Sequences expect the offsets are stored as an Array to eliminate the need to scan through the header to calculate the data offset. Sequences are ideal for situations where the fastest possible RW performance is needed.

#### Sequence Memory Layout

```
    +==========================+ -----------
    |_______ Buffer            |   ^     ^
    |_______ ...               |   |     |
    |_______ Data N            |  Data   |
    |_______ ...               |   |     |
    |_______ Data 0            |   v     |
    |==========================| -----   |
    |_______ count_max         |   ^     |
    |_______ ...               |   |     |
    |_______ Sorted Mappings N |   |     |
    |_______ ...               |   |     |
    |        Sorted Mappings 1 |   |     |
    |==========================|   |     |
    |_______ count_max         |   |    Size
    |_______ ...               |   |     |
    |_______ Data Offset N     |   |     |
    |_______ ...               | Header  |
    |        Data Offset 1     |   |     |
    |==========================|   |     |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Type byte N       |   |     |
    |_______ ...               |   |     |
    |        Type byte 1       |   |     |   ^ 0x(N+c)+sizeof(AsciiList<UI, SI>)
    |==========================|   |     |   |
    |  AsciiMap<UI, SI> Struct |   v     v   ^
    +==========================+ ----------- ^ 0xN
```


### d. Loom

ASCII Loom (LOM) is an array of UTF-8, UTF-16, or UTF-32 strings without a hash table. Strings lengths in Script are capped at type int, which gives a maximum length of 2^31 array elements; in cases where strings grow beyond this length, which is defined as extremely rare, a 64-bit Loom shall be used and the Loom shall be treated as a single long string.

#### Sequence Memory Layout

```
    +==========================+ -----------
    |_______ Strings 0          |  Strings   |
    |_______ ...               |   |     |
    |_______ Data N            |   v     |
    |_______ ...               |   |     |
    |_______ Buffer            |   ^     ^
    |==========================| -----   |
    |_______ count_max         |   ^     |
    |_______ ...               |   |     |
    |_______ Sorted Mappings N |   |     |
    |_______ ...               |   |     |
    |        Sorted Mappings 1 |   |     |
    |==========================|   |     |
    |_______ count_max         |   |    Size
    |_______ ...               |   |     |
    |_______ Data Offset N     |   |     |
    |_______ ...               | Header  |
    |        Data Offset 1     |   |     |
    |==========================|   |     |
    |_______ count_max         |   |     |
    |_______ ...               |   |     |
    |_______ Type byte N       |   |     |
    |_______ ...               |   |     |
    |        Type byte 1       |   |     |   ^ 0x(N+c)+sizeof(AsciiList<UI, SI>)
    |==========================|   |     |   |
    |  AsciiMap<UI, SI> Struct |   v     v   ^
    +==========================+ ----------- ^ 0xN
```
