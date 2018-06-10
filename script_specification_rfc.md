# 1. Overview

The Searle's Chinese Room, Interposes, and Telemetry (SCRIPT in all caps) Specification defines this Overview, ASCII Data Types, Script (in UppercaseCamel), Universal Polar Addressing, and ICAN3 Distributed Nomination System. Script, which consists of the SCRIPT Protocol, Chinese Room Abstract Stack Machine (Crabs), and Interprocess LISP is best described as a combination of Lua, JavaScript, Python, and LISP that is suitable for embedded purposes and is portable to almost any microprocessor and pen and paper stack computer. Script works over almost any serial communication protocol or encryption method and has its own multi-master physical bus using a series-parallel RS-485 connection over grounded 9-wire Ethernet cable.

Please note that this RFC is not an ISO Specification but is a living document; your comments and criticism are welcome. If you would like to contribute to this RFC, please email [Cale McCollough](https://calemccollough.github.io) at [cale.mccollough@gmail.com](mailto:cale.mccollough@gmail.com).

## 1.1 Content Table

1.  [Overview](#1-overview)
    1.  [Content Table](#11-content-table)
    2.  [Author](#12-overview)
    3.  [License](#13-license)
    4.  [Terminology](#14-terminology)
    5.  [Script Classes](#15-script-classes)
2.  [ASCII Data Types](#2-ascii-data-types)
    1.  [ASCII Data Types Table](#11-ascii-data-types-table)
    2.  [Integers](#12-integers)
    3.  [Boolean Values](#13-boolean-values)
    4.  [Floating-point Numbers](#14-floating-point-numbers)
    6.  [Timestamps](#16-timestamps)
    7.  [B-Sequences](#17-b-sequences)
    8.  [Objects](#18-objects)
3.  [Universal Polar IP Addressing](#3-universal-polar-ip-addressing)
    1.  [Longitude and Latitude](#31-longitude-and-latitude)
    2.  [Universal Address Format](#32-universal-address-format)
    3.  [Off-planet Signals](#33-off-planet-signals)
3. [SCRIPT Protocol and Virtual Machine](#4-script-protocol-and-virtual-machine)
    1.  [Chinese Room Abstract Stack Machine (Crabs) Overview](#41-chinese-room-abstract-stack-machine-crabs-overview)
    2.  [Group Automata Theorem](432-group-automata-theorem)
    3.  [Slots](#43-slots)
    4.  [Expressions](#44-expressions)
    5.  [Operations](#45-operations)
    6.  [Generic Handshake](#46-generic-handshake)
    7.  [Authentication](#47-authentication)
    8.  [Crabs Objects](#48-crabs-objects)
    9.  [Quality of Service](#49-quality-of-service)
    10. [Profiles](#410-profiles)
    11. [Encryption](#411-encryption)
    12. [Terminals](#412-terminals)
    13. [Quality of Service](#413-quality-of-service)
    14. [Congestion Control](#414-congestion-control)
    15. [Abnormal Behavior](#415-abnormal-behavior)
    16. [Crabs Interpreters and Compilers](#416-crabs-interpreters-and-compilers)
    17. [Conformance Targets](#417-conformance-targets)
5.  [ICAN3 Distributed Nomination System](#5-ican3-distributed-nomination-system)
    1. [Internet Guilds](#51-ascii-internet-guilds)
    2. [Geographic Coordinate Grid Guild](#52-geographic-coordinate-guild)
    3. [ICAN3 DNS Authority Hierarchy](#53-ican3-dns-authority-hierachy)
    4. [Registering an Internet Guild](#54-registering-an-internet-guild)
    5. [Key Promotion](#55-key-promotion)
    6. [DNS Caching](#56-dns-caching)
    7. [Abnormal Behaviors](#57-abnormal-behavior)

### 1.2. Author 
Cale Jamison McCollough

### 1.3. License 
Copyright 2015-2017 (C) [Cale McCollough](mailto:cale.mccollough@gmail.com) 

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at:
* [http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0).

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.

### 1.4. Terminology 


|                         Key | Description |
|----------------------------:|:------------|
|                       ASCII | Automata Standard Code for Information Interchange. |
|              Natural Number | An integer greater than or equal to zero. |
|                         I2C | Inter-IC bus is a serial bus protocol like SPI and UART (@wiki I2C Bus). |
|                         SPI | SPI is a serial port bus like I2C and UART (@wiki SPI Bus). |
|                 Serial Port | Universal asynchronous receiver/transmitter serial port bus (@wiki UART). |
| Inter-process Communication | Communication between threads in computers either on the same or foreign systems. (@wiki Inter-process communication). |
|            Script Automaton | A single threaded process, background process, app, or state-based machine under the control of an Automata. |
|             Script Automata | A Chinese Room Group Automata. |
|                Script Agent | A Script agent refers to either a Script Automaton or Automata. |
|             Script Terminal | The extremity of a Script Slot that facilitates reading and writing on the Crabs Stack. |
|                         UDP | Universal Datagram Packet. |
|      Abstract Stack Machine | (**ASM**) A conceptually perfect digital or manual pen and paper stack machine (@wiki Stack Machine @wiki Automata Theory). |
|                   Real-time | Happening in real-time in the physical and not virtual world. |
|          Virtual Simulation | A simulation in a computer. |
|         Abstract Simulation | A **thought experiment** under conceptually ideal environment and not a virtual or physical simulation. |
|             Simulation Time | A period of time existing in a **abstract simulation** or **virtual simulation** that is not real-time. |
|          Serial Byte Stream | A stream of octets of bits in real or simulation time. |
|              Serial Devices | A *abstract device* that can communicate input and/or output with a *serial byte stream*. |
|    Serial Transmission Line | A connection between two *Serial Devices*. |
|        Abstract Serial Port | A conceptually perfect *Serial Transmission Line* with infinite bandwidth and zero data corruption. A **ABS** is operated by writing a byte and reading a byte simultaneously. |
|     Asynchronous B-Sequence | A B-Sequence that can be processed asynchronously. |
|       Local Procedure Calls | (**LPC**) A procedure call executed on a local computer. |
|      Remote Procedure Calls | (**RPC**) A procedure call executed on a foreign computer. |
|                      Socket | A block of memory, typically a ring buffer, used for interprocess communication. |
|                       Print | The action of converting a binary number to a string or copying from one string to another. |
|                       Write | The action of copying a binary number or string to a buffer.|
|                        Read | The action of reading binary data from a buffer to the Program Stack without converting it. |
|                        Scan | The action of converting a text representation of a number to a string or copying a string from one buffer to another. |

## 1.5 Script Classes

|      Class | Description       |
|-----------:|:------------------|
|      Array | An *ASCII Array*. |
|        Bin | A *B-Input Sequence*, or *B-Input*, is an A*B B-Input Stream. |
|       Bout | A *B-Output Sequence*, or *B-Output*, is an A*B B-Output Stream. |
|      Clock | Used for 32-bit and 64-bit timestamps. |
|       Door | A door in a Chinese Room that leads to another Chinese Room or Agent. |
|  Interrupt | An Interrupt that causes the Room to Reset.  |
| Expression | An asynchronous Group structured expression. |
|        Log | A B-Sequence used for a log. |
|  Operation | A header for an Operation. |
|     Portal | A B-Sequence portal to another Chinese Room. |
|       Room | A Chinese Room that can read and write B-Sequences. |
|        Set | Interface for a *ASCII Set Data Type*. |
|       Slot | A slot (i.e. Socket) in a Door in a Chinese Room in the form of a Ring Buffer Socket. |
|      Table | A Symbol Table implemented as a Set with no data. |
|       Wall | A Wall in a Chinese Room composed of a contiguous word-aligned block of memory. |

---

# 2. ASCII Data Types

There are 32 Automata Standard Code for Information Interchange (ASCII) Data Types composed of 23 Plain-Old-Data and 8 object types composed of contiguous memory. Types are stored as bytes where the 5 LSb are used to store the type and the upper 3 bits are used to store either bit width of the size of the object, 8, 16, 32, or 64-bit, or to store the dimensions of a stack or multi-dimensional array. Implementations shall support types SVI, UVI, ADR, and STR and may support more types.

## 2.1 Type Byte 

All ASCII Types can be represented as a single byte where the lower 5 bits are used to store the type, and the upper three bits are used to store if the type is an array.

|   b7-b6   |     b5   |   b4-b0   |
|:---------:|:--------:|:---------:|
| bit_width | is_stack | type 0-31 |

### 2.1.a Types 0-31

| ID | Type |  Alt Name  | Width  | Description          |
|:--:|:----:|:----------:|:------:|:---------------------|
| 0  | NIL  |  null/void |    0   | Nil/null/void type.  |
| 1  | ADR  |   Address  |  <=N   | Stack Operation Address.   |
| 2  | STR  |   String   |  <=N   | UTF-8 string.|
| 3  | TKN  |   Token    |  <=N   | UTF-8 string without any whitespace.|
| 4  | SI1  |    int8_t  |   -1   | 8-bit signed integer.|
| 5  | UI1  |   uint8_t  |    1   | 8-bit unsigned integer.|
| 6  | BOL  |    bool    |   -1   | Non-zero false boolean variable.|
| 7  | SI2  |   int16_t  |   -2   | 16-bit signed varint.|
| 8  | UI2  |  uint16_t  |    2   | 16-bit unsigned integer.|
| 9  | HLF  |    half    |    2   | 16-bit floating-point number.|
| 10 | SVI  |    int     | -1 - 5 | 16-bit or 32-bit signed varint (int).|
| 11 | UVI  |    uint    |  1 - 5 | 32-bit or 32-bit unsigned varint (int).|
| 12 | SI4  |   int32_t  |   -4   | 32-bit signed varint.|
| 13 | UI4  |  uint32_t  |    4   | 32-bit unsigned integer.|
| 14 | FLT  |    float   |    4   | 32-bit floating-point number.|
| 15 | TMS  |   time_s   |   -4   | 32-bit second since epoch timestamp.|
| 16 | TMU  |   time_us  |   -8   | 64-bit microsecond since epoch timestamp.|
| 15 | SI8  |   int64_t  |   -8   | 64-bit signed integer.|
| 16 | UI8  |  uint64_t  |    8   | 64-bit unsigned integer.|
| 17 | DBL  |   double   |    8   | 64-bit floating-point number.|
| 18 | SV8  |   int64_t  | -1 - 9 | 64-bit signed varint.|
| 19 | UV8  |  uint64_t  |  1 - 9 | 64-bit unsigned varint.|
| 20 | DEC  |   Decimal  |   16   | 128-bit floating-point number. |
| 21 | SIN  |   intn_t   |    N   | N-bit signed integer. |
| 22 | UIN  |   uintn_t  |    N   | N-bit signed integer. |
| 25 | OBJ  |   Object   |    N   | N-byte object composed of contiguous memory.|
| 26 | BSQ  |    Bsq     |  <=N   | B-Sequence.|
| 27 | ESC  |    Esc     |  <=N   | Escape sequence of B-Sequences.|
| 28 | LST  |   List     |    N   | Stack of Type-Value tuples.|
| 29 | BOK  |   Book     |    N   | Unordered map of Key-{Type-Value} tuples.|
| 30 | DIC  | Dictionary |    N   | One-to-one map of Key-{Type-Value} tuples.|
| 31 | MAP  |    Map     |    N   | One-to-one map of Id-{Type-Value} tuples.|

### 2.1.b List of Types Key

| Width | Description |
|:-----:|:------------|
|  -X   | Signed integer type.|
|   ?   | Type of unknown size.|
|   N   | Has pre-specified buffer of size N bytes.|
| <=N   | Has pre-specified buffer of size N bytes but can use less than that.|

## 2.2 Integers
Script supports both traditional 8, 16, 32, and 64-bit, and n-byte signed 2's complement integers and unsigned uncomplemented integers. For n-byte integers, implementations may implement n-byte integer math and may require n to be 8, 16, or 32 bytes.

### Valid Integers Examples
```
SI1 0
UI1 255
SI2 -32,000
SI4 0xFFFF
```

### Invalid Integer Examples
```
SI1 256       ; Too big for size
SI2 0xFFFFF   ; Too big for size
```

## 2.2.a Varints

Variants are MSb variant are compressed using MSB-encoded signed and unsigned 1-to-9-byte variable-length integers. Varints use the MSb of each byte to determine if another byte is to be loaded. This allows values less than 128 to be sent using only one byte, 14-bit values in two bytes, 21-bit values in three bytes and so on.  

Both Signed and Unsigned Varints must use the most significant bit asserted is used to marks if another byte is loaded. All Script implementations shall represent signed varints as uncomplemented integers with the sign bit in the LSb.

```
UVI 128 // = 0b0000_0001_1000_0000 
UVI 255 // = 0b0000_0001_1111_1111 
SVI -64 // = 0b0011_1111
```
## 2.2.b N-Byte Integers

N-Byte Signed Integers (SIN) and Unsigned Integers (UIN) are integers that may be 0-N bytes in width. SIN and UIN are very useful for transferring 128+ bit hashes and custom data structures. Implementations may implement n-byte arithmetic.

#### Example

```
// static const unsigned int sin_uin_bsq_example = { 2, SIN, 8, UIN 16 };
SIN -1
UIN 1
```
 
## 2.3 Boolean

Booleans in Script are transceived as a SVI type where the deasserted value shall be stored as the number zero and labeled false, and asserted values shall be represented as the number one labeled true or a non-zero SVI value.

### Boolean Examples

```
// All values less then 127 and greater than -127
BOL true   //< Translates to the number 1
BOL false  //< Translates to the number 0
BOL 0
BOL 1
BOL -129   //< Will require 2 bytes to transceive.
```

## 2.4 Floating-point Numbers 

Script supports, 16, 32, and 64-bit floating-point numbers, also called half, float, and double precision float-point numbers. Floating-point numbers do not lend themselves very well to varint compression, so using a 16-bit floating-point number can dramatically improve performance when low-precision is needed. Implementations may implement 128-bit floating-point math. 128-bit floating point numbers are compatible with the C# programming language.

```
HLF 0.0     // Use a HLF to save memory and bandwidth! 
FLT 0.1     // Wastes a lot of space! 
DBL - 0.1;  // Wastes a whole lot of space!
DEC 1.0     // Wastes a TRUCK TON of space!
```

## 2.5 Addresses, Strings, and Tokens

Script supports UTF-8, UTF-16, and UTF-32 strings (STR), and UTF-8 Addresses (ADR) and Tokens (TKN). TKN and ADR shall contain no whitespace or non-printable characters, i.e. no characters with index less than 33. A Script implementation may enforce strict Unicode compliance. Packed Messages shall use nil-terminated strings and Unpacked Script shall use double-quote-terminated strings with C-style escape sequences. Implementation that support Interprocess LISP shall provide a delimiter char.

```
TKN key                 //< No quotes needed for a TKN.
ADR 123                 //< A ADR is a TKN.
STR  "\"Hello world!\"" //< String that reads "Hello world!" with double quotes.
                        //< There is no need to use a 1 to make STR1.
STR2 "\"Hello world!\"" //< This is a string that is up to 64KB long.
STR4 "\"Hello world!\"" //< This is a string that is up to 4GB long.
STR8 "\"Hello world!\"" //< This is a string that is up to 2^64-1 bytes long.
```

## 2.6 Timestamps

There are two types of timestamps, a 31-bit Unix timestamp, and 63-bit microsecond timestamp in C++11 chrono format. Both second and microsecond timestamps are Plain Old Data types that may be read from text as a TKN in the following formats: 

```
/** Example functions.
    @fn TimeSeconds <TMS>:<NIL>
    @fn TimeMicroseconds <TMU>:<NIL>

    # Timestamp Format
    | Seconds Since Epoch | Microseconds Since Epoch |
    |:-------------------:|:------------------------:|
    | YYYY-MM-DD@HH:MM:ss |  YYYY-MM-DD@HH:MM:ss:uu  |

         Month ---v        v—-Minutes  */
TimeSeconds 2016-07-13@15:39:23 
/*               Hours--^     ^--- seconds 
            Year ---v     v--- Day     v-- microseconds */
TimeMicroseconds 2016-07-13@15:39:23:999 
```

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
    |==================|
    |   Packed Array   |
    |==================|
 +  | Dimensions Stack |
 ^  |==================|
 |  |      Header      |
0xN |==================|
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
 
## 3. Universal Polar IP Addressing

**Universal Polar IP Addressing**, **Universal IP Addressing**, **UIP Addressing**, or **UIPA** is the Telemetry aspect of Script; it is a method of Addressing physical and Internet Protocol Addressing that works identically on every planet and can be used to route internet signals around the universe. Before we talk about a UP Addressing it helps to see a map of the internet wires on Earth. Here is Earth's Internet Superhighway in the year 2017 center about 0 degrees longitude.

![Earth's Internet Superhighway in the year 2017](http://img.labnol.org/di/undersea_cable_map.png)

The method uses a minimum of a 5 to 40 byte IP Address that conveys latitude, longitude, and height above or below sea level in the minimum unit of one-degree longitude and latitude. Exact precision is possible using varints and the **Least Significant Longitudinal Unit**, a standard metric unit used to represent the height above or below sea-level in terms of one-degree longitude at the equator. Because a Script Datagram may be of 0 bytes in length but a header may be up to 40 bytes in length, implementations may require a minimum Datagram length of 40 bytes.

## 3.1  Longitude and Latitude

Latitude and longitude are useful to know in an IP Address because it helps the system route signals to the fastest possible routes through the network.

```
         Longitude           |             Latitude
                             |
        /---> -180           |            /----> 90
       /      _  _           |           /      _  _
      /    =        =        |          /    =        =
     /   =            =      |         /   =            = 
  0 |  =     North     =     |      0 |  = _____________ = 
    |  =     Pole      =     |        |  =    Equator    =
     \   =            =      |         \   =            = 
      \    =        =        |          \    =        = 
       \     ~  ~            |           \     ~  ~
        ---> +180            |            ---> -90
```

### 3.1.a Haversine Formula

Haversine Formula's is used to calculate 3D arc lengths using polar coordinates with a known radius.

* Let power be a function that takes two real number parameters (a, b), and returns *a to the power of b*.
* Let L = degrees_longitude = L_2- L_1
* Let l = degrees_latitude = l_2 - l_1
* Let a = power (power ((sin (l / 2), 2) + cos (l_1) * cos(l_2) * (sin(L / 2), 2)
* Let c = 2 * atan2 ( sqrt(a), sqrt(1 - a) ) 
* Let d = R * c

## 3.2 Most Longitudinal bit

A Most Longitudinal bit (MLb) is a metric unit invented for the SCRIPT Protocol measured in meters per Most Significant bit (M/MSb) and defined by the arc length of one-degree longitude at the equator per MSb. Each one degree latitude by one degree longitude grid shall be referred to as a **Degree Grid**. The MLb is used to route signals to orbiting satellites, aircraft, ground, ultra-high speed fiber optic, and submarine Script Networks.

## 3.3 Universal Address Format

The Universal IP Address Format consists of a 3 integer values for Longitude, latitude, and Height above or below sea level. The *UIP Address Format* uses a data compression technique called *MSb Variant Encoding* to create a **Varint**, which uses the *Most Significant bit* to signal whether to load another octet consisting of 7 more MSb plus one stop bit in the MSb. Varints are used to give exact precision with up to address length cap, and can also be used for transmitting ultra-precise laser signals and receiving sub-centimeter level accurate GPS coordinates.

Polar coordinates are used in 2D polar subnets in order to sort systems based on fastest to slowest connections in a *Star Configuration*. The closest you are to the center of the circles, the faster the internet runs by the natures of light speed electrical signal propagation.

### 3.3.a Universal Address Format Packet

|  b39  | b38-b32 |  b31  | b30-b24 |  b23  | b22-b12  |  b14  |  b13-b5   |  b_4  | b_3-b_0 |
|:-----:|:-------:|:-----:|:-------:|:-----:|:--------:|:-----:|:---------:|:-----:|:-------:|
|   0   | Radians |   0   |  Radius |   0   | Latitude |   0   | Longitude |   0   | Height  |
|       |   (-)   |       |   (+)   |       |   (-)    |       |   (-)     |       |   (-)   |
|       |    A    |       |    R    |       |    l     |       |    L      |       |    H    |
|       | Varint  |       |  Varint |       |  Varint  |       |  Varint   |       | Varint  |
| 1 bit | 7 bits  | 1 bit |  7 bits | 1 bit |  9 bits  | 1 bit |  8 bits   | 1 bit | 4 bits  |

* Key: (+) means unsigned and (-) means signed.

@warning Notice of Possible Format Change: The following format uses varints because it was originally thought it might help but this might not be an optimal solution due to unrecorded behavior of varints at 40+ gigabit per second connections. As far as this specification is aware of for routing purposes we're not even interested in the end of the number so the varint bits should work well with Verilog implementations as the port order may be easily rerouted. The use of variable length headers shall be reexamined after physical hardware routers have been constructed.

### 3.3.b Address Ranges

All address ranges with (longitude greater than +180 or less than -180) and (latitude greater than +90 or less than -90) are reserved for authoritative endpoints. All address ranges with height equal to -32 and height_varint_bit belong to *off-planet addresses*. Most *off-planet address* require very precise coordinates, so each *Interstellar Internet Route* shall have a minimum number of varint bytes required of each type.

## 3.4 Off-planet Signals

All off-planet signs are routed using the UAF Height Value of all logic level 1(s). For a 5-byte packet, this is a value of -16. When this Height is detected, the signal gets routed to one of 64800 possible directions based on 360 degrees longitude times 180 latitude. Currently, no starships exist for this task but they are being designed by the Kabuki Starship team; the open-source organization behind Script.

## 3.5 1 Degree Grid Routing

It is not possible for any router to be located at the exact center of a 1 degree latitude by 1 degree longitude grid, nor does it need to be because there are a manageably small number of fiber optics cables to route and thus the center of the grid is defined as the fastest internet connection in that Degree Grid. All other organizations that provide the internet backbone are then referenced again in polar coordinates from the Degree Grid Reference

---

# 4. Script

Script consists of the Group Automata Theorem, SCRIPT Protocol, Chinese room abstract stack machine (Crabs) and Interprocess LISP. In the John Searle's famous Chinese Room Thought Experiment users may talk to the Chinese Room (i.e. end-point) by writing Messages (i.e. Datagrams) on a piece of Paper (B-Input) and passing them through a Slot (i.e. Socket) in a Door (Group of communication links leading to the same room) in the room. An Agent (Program or AIML Entity) then reads the message and uses them to operate the Crabs, and replies by writing a Message on a piece of Paper and passing it back through the Slot.

## 4.1 Chinese Room Abstract Stack Machine (Crabs) Overview

The **Chinese Room Abstract Stack Machine** (**Crabs**) is an abstract machine capable of running *Group Automata* using the SCRIPT Protocol and Interprocess LISP. Crabs is the standardized Interprocess LISP API for interacting with a Chinese Room with a text terminal over the Script. Script is designed to run over a standard serial connection that allows users to hack on devices in real-time with a PC keyboard, app GUI, or other serial B-Stream so Script makes use of ASCII C0 Codes and VK Keyboard Codes so you can do alt, shift, or control keys on the keyboard to do stuff like copy and paste and Script Macros.

## 4.1.a Crabs Messages

A **Crabs Message** is similar to an internet datagram and may be enclosed in a IPv4 or IPv6 datagram. A Crabs Message is defined as set of stack operations that start and end with an empty Operand Stack where one or more Operands is pushed, All Unicode Operation indexes being valid, all keys being resolved correctly, and the B-Stream being of a valid length for each B-Sequence argument. Crabs Room Messages may be written in any language using UTF-8. Messages get Unpacked by the Expression Interpreter and translated into the native Unicode format, UTF-8, UTF-16, or UTF-32 for that room and may be compiled directly to a register-based stack machine.

Crabs Messages beginning with a nonprintable Unicode Character shall be byte-encoded with the data immediately following it be a Packed B-Stream. All Crabs Messages beginning in a printable Unicode char shall be Interprocess LISP.

## 4.1.b Chinese Room Contents

A Chinese Room in Searle's famous thought experiment is just a plain old office with a person in it who is operating a *pen and paper abstract stack machine* that functions identically to computer, only there are no electronic parts. In this room are Doors that lead to other rooms that have people in them. Each Door has a Slot (i.e. a socket) that allows people in rooms to communicate with other rooms with handwritten messages that can be both synchronous and asyncronous. Consequentially, this is exactly how an optimized piece of internet software works. Rooms consist of Doors that lead to other Rooms, Walls that contain Doors, Slots in Doors, One-way Tables, Books, Dictionaries, Maps, Lists, Arrays, Stacks, and Files, and Boxes.

At the root scope of each system lies a *Interrupt Operations* DC1, DC2, DC3, and DC4 Script Operations defined.

#### Walls

**Walls** are contiguous blocks of word-aligned memory used to construct Chinese Rooms out of. Walls are used to install Doors, Filing Cabinets, Book Shelves, Windows, Mirrors, and Tables.

#### Doors

**Doors** in a *Chinese Rooms* are a MAP ASCII Data Type.

#### Mirrors and Windows

**Mirrors** in a *Chinese Rooms* are *Contiguous Word-Aligned Memory Blocks* used for *Expressions* and *Interprocess IO Portals* that use *Word-Aligned Hashless B-Sequences*. When two one-way Mirrors are combined they create a duplex Slot called a **Window**. Mirror and Windows shall be used to for Interprocess Same-System Terminals.

## 4.1.c Compliant Crabs UML Model Example

The following is an example of a Script Compliant UML diagram with pseudo-templates. Pseudo-templates are method of describing templates in UML using underscores and the typename. For instance, **SI** as a templated Signed Integer, **UI** as a templated Unsigned Integer, **T** for a templated Script POD Numbers, and **_ptr** as a byte pointer unaligned to a 64-bit boundary.

For Crabs UML Model, you will need to download StarUML from [http://staruml.io/](http://staruml.io/) and open ~/docs/kabuki_toolkit.mdj.

### UML Pseudo-template Example

```
// Example_UI_SI

template<typename UI, typename SI>
struct Example {
    UI alpha;
    SI beta;
}
```

## 4.2 Group Automata Theorem

Script, and all formal intelligence, can be recursively defined as follows:

* Let an **automata** be composed of concurrent **automatons**.
* Let a **Chinese Room** be an *Abstract Stack Machine (ASM)* able to reset to the **initial state** and run **automata** with **Script Operations** indexed by a single *Unicode character*.
* Let **A** be a set of states in a *state machine* that composes a **Chinese Room**.
* Let **B** be a set of *abstract parameters* in the form of a *byte stream* of **ASCII Data Types**.
* Let * be an *abstract binary operation* on sets **A** and **B**.
* Let **on** be a set of states where a **Chinese Room** is accepting **words**.
* While in the **on** state, **A** = **A** * **B**.
* Syntax changes semantics, thus **A** has no *commutative property*.
* **A** has an *inverse*, **A^(-1)**, in the form of a **Reset Operation**, thus (**A** * **B**)*(**A^(-1)**) = **A**.
* All *ASMs* have *total function*.
* **Conclusion**: **A** has *totality*, *associative*, *identity*, *inverse* *properties* but no *commutative* *property*, thus **A** is **group** in structure proving that the **Chinese Room** is a **Group Automata**, meaning **Many robots acting as one**:
    * *Group Automata*
        * **组自动机**
        * *Zǔ zìdòng jī*
    * *Many robots acting as one*
        * *许多机器人作为一个*
        * *Xǔduō jīqìrén zuòwéi yīgè*

## 4.3 B-Stream Slots

A Socket is defined a block of memory used to transceived data, and is typically implemented as ring buffer. There are two types of slots, a B-Input (BIn) and B-Output (BOut). A **Slot** is defined as a Ring Buffer Socket. BIn and BOut implementations written in a Hardware Development Language may not strictly comply with the contiguous memory operation but shall operate functionally equivalent to the specified register stack machine implementation. For register stack machines with contiguous memory. Each Slot shall begin a 64-bit aligned memory address and shall have a 64-bit aligned end address.

### 4.3.a Slot Data Structure in C

```
struct Slot {
    char* begin, //< Beginning of the ring buffer.
        * start, //< Start of the data in the ring buffer.
        * stop,  //< Stop of the data in the ring buffer.
        * end;   //< End of the ring buffer.
};
```

### 4.3.b B-Input Slot

A B-Input, BIn, is a type of Slot for incoming Messages that uses offsets from the beginning of the data structure in memory.

#### BIn C Data Structure

```
typedef unsigned int uint_t;
struct BIn {
    uint_t          size,   //< The size of the buffer.
                    start;  //< The starting index of the ring buffer data.
    volatile uint_t stop;   //< The stopping index of the ring buffer data.
    uint_t          read;   //< The read variable.
};
```

#### B-Input Slot Memory Layout

```
+--------------------+
|     Ring Buffer    |
|------------------- |  +
| BIn Data Structure |  |
+--------------------+ 0xN
```

#### B-Input Compliant Finite State Machine Example

Finite State Machine uses a stack of state indexes for all states that have bidirectional arrows. Once the Crabs Message has been interpreted and the hash is verified, the data has thought to be in the correct format but has not been verified to be bound into determinant ranges (@see Bounding Escape Sequences).

![B-Input Interpreter FSM](https://github.com/kabuki-starship/kabuki-toolkit/wiki/expression-scanner-fsm.jpg)

### B-Output Slot

A B-Output Slot, BOut, almost works similarly to the BIn except the BOut reserves N bytes at the end of the ring buffer, where N equals 0, 8, 16, or 24, for writing integers and floating-point numbers to string. If an integer type is written to the buffer and the string overflows the buffer, the implementation may copy the overflowed string to the beginning of the slot. The number N shall be chosen such that the desired number of bytes that can be overflowed without overflowing the buffer. When a number is written to a BOut in RAM, the BOut shall be required to contain enough free space to write the maximum length of the number string.

#### BOut C Data Structure

```
struct KABUKI BOut {
    uint_t          size;  //< Size of the B-Output.
    volatile uint_t start; //< Starting index of the ring-buffer data.
    uint_t          stop,  //< Stopping index of the ring-buffer data.
                    read;  //< Address that the BOut device is reading from.
};
```

#### B-Output Memory Layout

```
+------------------------------------+
| Slot number string overflow buffer |
|------------------------------------|
|            Ring Buffer             |
|------------------------------------|
|        BOut Data Structure         |
+------------------------------------+
```

### 4.3.e Windows

Windows combine a BIn and BOut in contiguous memory. The ring buffers function similar to BIn and BOut except that the Slot.stop offset in the B-Input Window gets swapped with duplex B-Output Window. This is because one is a read-only and one is a write only that may occur in parallel as opposed to a strictly serial Slot operation where the room may both read and write to the same Slot.

#### Window Memory Layout

```
+------+
| BOut |
|------|   ^
| BIn  |   |
+------+  0xN
```

### 4.3.f Default In Slot and Out Slot

Script implementations may implement a default BIn Slot named In (**in UpperCaseCamel**)
 and default BOut Slot named Out (**in UpperCaseCamel**). In shall stream bytes from a Text keyboard, BOut Slot or Text display input. Out stream bytes to a Abstract text display, BIn Slot, or Abstract serial output.

## 4.4 Expressions

Expressions are a sequence of *Stack Operations* that end when all of the Operands are popped off the Expression Stack. Each Operand may have its own instruction that pops one Operand off the stack or pops all the Operands off performing a Closure Operation.

Everything in Script is a real-time **A** = **A** * **B** **Abstract Algebra Expression** where B is a B-Stream, or Byte Stream. Expression are a sequence of **Operations** performed on **Operand Objects** on a **Operand Stack**. *Operations* are *abstract function calls* that shall be able to take one or more input and output parameters in the form of **B-Sequences** (**BSQ** or *Byte Sequence*). A BSQ only the description of the data format packed that may be word aligned, thus a BSQ is describes the parameters not the arguments and a B-Stream describes the arguments. *Operations* shall be performed using a UTF-8 Index followed by the BSQ input arguments for that Op. When an *Operand* is pushed onto the stack, all Unicode indexes shall be mapped to that Operand until it is popped off the stack and is no longer the **Current Operand**.

Once a valid Expression has been received, a room may then **Evaluate** that expression from one of potentially many asynchronous BIn in the program's main loop in any order.

#### Hyphenated Script Expression Example

```
/* typedef uint8_t uint_t;
   static const uint_t in_params[]  = { 1, UI4, UI8 }, 
                       out_params[] = { 1, NILL, NIL };
    static const Op kOp= { “Example-Function_with_hypens_and_underscores”,
                          rxHeader, txHeader,
                          “Description”, '(', ')', ' ', "-_", nullptr };
                                          ^    ^    ^    ^
                                          |    |    |    |
                Pop One Operation --------+    |    |    |
                Pop All Operation -------------+    |    |
                Default Operation ------------------+    |
                Chars '-' and '_'                        |
                allowed in Tokens -----------------------+    */

Example-Function_with_hypens_and_underscores {
    1 2     // Index 64 is the first user-definable function index.
    A 1 2;  // Index 64 is the first user-definable function index.
}
```

### 4.3.a Operation Header 

```
struct Op {
    const char   * name;          //< Op name.
    const uint_t * in,            //< Input BSQ params or OpFirst.
                 * out;           //< Output BSQ params or OpLast.
    const char   * description;   //< Op description.
    wchar_t        pop,           //< Index of the Pop Operation.
                   close,         //< Index of the Close Operation.
                   default_op;    //< Index of the Default Operation.
    const char   * allowed_chars; //< String of allowed symbols in keys.
    const Slot   * evaluation;    //< Evaluated expression Slot.
};
```

### C++ Header Examples

```
static const uint_t rx_header_without_strings[] = { 2, UI1, SI2 },   
                    rx_header_with_strings[]    = { 2, UI1, STR, 32 },
                    //< We need to specify the max string length.
                    rx_header_with_array[]      = { 2, UI1, Array (UI1, 32) },
                    //< We need ot specifiy the exact number of bytes.
                    tx_header_with_strings[]    = { 2, UI1, STR };
                    //< We don’t specify the max length for tx output. 
```

#### Operation C++ Example

```
#include <crabs/global.h> 
using namespace _;

const Op* Star (wchar_t index, Expression* expr)  {
    void* params[2]; 
    
    if (index != 'A') return 0;  //< switch statements are normally use used.
    
    static const unsigned int params[] = { 2, ADR, UI4, STR, 32 }, 
                              result[] = { 2, UI4, STR }; 
    static const Operation kOpExample= { “expression-name”,
                                         params, result,
                                         “Description”, 0 };
    // Script uses the a nil expr pointer as a flag to get the Operation header.
    if (!expr) return &kOpExample;
    
    // Example RPC variables.
    uint32_t input_a, 
             input_b, 
             output_a = 1, 
             output_b = 2; 
     
    if (Read (expr, kOpExample, Args (params, &input_a, &input_b)))
         return expr->result; 
     
    // Operation logic here.

    return Write (expr, kOpExample, Args (params, &output_a, &output_b));
}
```

## 4.4 Operations

**Script Operations** are **Abstract Stack Machine Functions** implemented as either *Local Procedure Calls*  or *Remote Procedure Calls* that are indexed by a single *UTF-8 Character*. *Script Operations* may take a *Packed B-Stream* or *Word-Aligned B-Stream* of parameter arguments.

#### UTF-8 Format

| Byte 1   | Byte 2   | Byte 3   | Byte 4   | UTF-32 Result         |
|:--------:|:--------:|:--------:|:--------:|:---------------------:|
| 0aaaaaaa |          |          |          | 00000000000000aaaaaaa |
| 110aaaaa | 10bbbbbb |          |          | 0000000000aaaaabbbbbb |
| 1110aaaa | 10bbbbbb | 10cccccc |          | 00000aaaabbbbbbcccccc |
| 11110aaa | 10bbbbbb | 10cccccc | 10dddddd | aaabbbbbbccccccdddddd |

#### UTF-16 Format

| Bytes {4N, 4N+ 1} | Bytes {4N + 2, 4N+ 3} | UTF-32 Result        |
|:-----------------:|:---------------------:|:--------------------:|
| 110110aaaaaaaaaa  | 110111bbbbbbbbbb      | aaaaaaaaaabbbbbbbbbb |

### 4.4.a Crabs Operations

#### Default Operation

The Default Operation shall be set by each Operand and when the Interpreter or Compiler is resolving keys and sees a number, that Operand's Default Operation shall be called.

#### Cache Search Operation

A *Cache Search Operation* is an operation that searches for a locally cached version of an object before consulting the ICAN3 DNS authority.

#### Clear Expression Operation

Clears Expression Operation clears the current Expression Slots without deleting it.

#### Open Expression Operation

*ASCII SI Operation* is used to open a *Expression Stack Level*. The operation may be hooked using the *ASCII '(' Operation* before calling SI.

#### Close Expression Operation

**ASCII SO Operation** is used to open a *Expression Stack Level*. The operation may be hooked using the *ASCII '(' Operation* before calling SI.

#### Importance Operation

**Importance Operation** performs  Raises the *Importance Level* for each consecutive ASCII '!' byte.

#### Division Operation

*Division Operation* by default performs a mathematical division of the current object and *B-Sequence Operand*. The operation may be overwritten in non-root context.

#### Multiply Operation

*Multiply Operation* by default performs a mathematical multiplication of the current object and *B-Sequence Operand*. The operation may be overwritten in non-root context.

#### Plus Operation

*Plus Operation* by default performs a mathematical addition of the current object and *B-Sequence Operand*. The operation may be overwritten in non-root context.

#### Subtraction Operation

*Subtraction Operation* by default performs a mathematical subtraction of the current object and *B-Sequence Operand*. The operation may be overwritten in non-root context.

#### Closure Operation

Signals the current automaton to finish processing a word.

#### Separation Operator

*Separation Operator* does nothing by default but may be overridden to allow for faster parsing of *Separation of Ideas*.

#### Exponent Operation

**Exponent Operations** (**Exp Op** or **Exp Ops**) work similarly to math exponents only with A*B operations. **Exp Ops** work by specifying the number of loops **Varint**. If the value of the Varint is **NaN** then it is a **Infinite Exponential Operations** (**IEO**). **IEOs** are functionally identical to while loops. **Loops** are exited prematurely using the **Clear Operation**.

#### Delete Operation

*Delete Operation* deletes the previous char in the ring buffer.

#### Whitespace Operations

Script is whitespace delimited spaces may be be skipped by the interpreter or interpreted as a Operating with index 64 (ASCII ' '). For real-time streaming natural language processing Whitespace Operations are used to identify pauses in speech (i.e. dead audio).

### 4.4.b Interrupt Escape Sequence

Each Room has a single **Interrupt Expression** in the index '/'. When an ESC interrupt byte is received the *Interrupt Expression* is pushed onto the stack. If this ESC returns a Result this Result must be inserted into the location of the ESC in the B-Stream.

#### Mandatory Single Byte Interrupt Operations

| ASCII |    Formal Name      | Description |
|:-----:|:-------------------:|:-----------:|
|  EOT  | End of transmission | Disconnects from the host. |
|  CAN  | Cancel              | Cancels the current Expression being scanned. |

### 4.4.c Device Controls 1-4

Device Controls 1 through 4 are the ASCII DC1, DC2, DC3, and DC4 Operations. These Operations may be directly mapped the VK_SHIFT, VK_CONTROL, VK_ALT, and VK_PAUSE buttons on the keyboard. DC1, DC2, and DC3 may be used with momentary switch where that Device Control Operation is called when the button is pressed and depressed. DC4 is may be used with a momentary switch where the Device Control Operation is called when the button is pressed or depressed.

#### DC1 - XON -VK_SHIFT

DC4 must be an <NIL>:<NIL> Operand that does nothing by default and uses ASCII DC4 for it's Closure Operation. DC4 may be used for Shift Keyboard Shortcuts the system and may be overridden by the user for application specific purposes.

#### DC2 - VK_CONTROL

DC4 must be an <NIL>:<NIL> Operand that does nothing by default and uses ASCII DC4 for it's Closure Operation. DC4 may be used for Control Keyboard Shortcuts the system and may be overridden by the user for application specific purposes.

#### DC3 - XOFF - VK_ALT

DC4 must be an <NIL>:<NIL> Operand that does nothing by default and uses ASCII DC4 for it's Closure Operation. DC4 may be used for Alt Keyboard Shortcuts the system and may be overridden by the user for application specific purposes.

DC3 must be a device that does nothing by default and uses DC3 for a Closure Operation. XOFF may be overridden by the user for application specific purposes.

#### DC4 - App - VK_PAUSE

DC4 must be an <NIL>:<NIL> Operand that does nothing by default and uses ASCII DC4 for it's Closure Operation. DC4 may be used to pause the system and may be overridden by the user for application specific purposes.

### 4.4.d Reset Operations

Reset Operations are operations that required the slot in the Chinese Door to be closed. This is typically something like remote firmware updating. Each implementation is responsible for initializing the system and proving The Chinese Room Group Automata Theorem.

### 4.4.e Return Values

Return values just need an address of an Operation to send the return value too. Return values shall be written to the BOut that leads to the initiating Operation's BIn in an automated process. In the case that a different Operation's return address is needed Rooms may pass the return address of the as an input parameter as a TKN type.

## 4.5 Generic Handshake

@todo Change from IPv4 to UP IP Addressing

1. Let **host_a** and **host_b** be *Chinese Rooms* connected through a serial connection or package switched network.
2. Let **host_a** and **host_b** exchange packets of size 1 byte and ** be 16-bit prime multiple hashes of the packets with single bytes.
3. Let └¿�☺ be the IPv4 address 192.168.0.1 of **host_a** and ☻�¿└ be the address from **host_b** to host_a**.
4. Let └¿�☻  be the IPv4 address 192.168.0.1 of **host_b** and ☺�¿└ be the address from **host_a** to **host_b**.
5. Let **A**, **B**, and **C** be a generic 3-way handshake on a generic application in some generic upper-level communication protocol over Script.
5. **host_a** initiates a connection handshake by sending the sequence of bytes:
    * ☺└¿�☻A**
6. **Script Router** automatically adds the inverse router return address, each stage executing the Script Hash Function to create the final byte sequence:
    * ☺└¿�☻A**☺�¿└**
7. **host_b** response from the handshake with the sequence of bytes:
    * ☺└¿�☺B☻�¿└**
8. **Script Router** adds return address and hash:
    * ☺└¿�☺B**☻�¿└**
9. **host_a** responds with the connection response with the sequence of bytes:
    * ☺└¿�☻C**
10. **Script Router** adds return address and hash:
    * ☺└¿�☺B**☻�¿└**
11. **host_a** and **host_b** are now connected.

## 4.6 Authentication

Authentication in Script shall be done using a sequence of Script Operations.

## 4.7 Crabs Objects

ASCII Data Types LST, MAP, DIC, BOK, and Stacks and Arrays or ASCII Types 4 through 22 shall be created using Crabs.

### Dictionary Example

```
/*
 +-------------------------------------- Operation with key "let" that takes a
 |                                       Token (TKN), which is UTF-8 string 
 |                                       without any whitespace or symbols.
 |                                       Operation basically creates a 
 |                                       Expression that we then start writing 
 |                                       to.
 |           +-------------------------- Operation Push "=DIC2" is a function  
 |           |                           with address stuff that creates a 
 |           |                           dictionary of size 64KB bytes with a 
 |           |                           maximum of 3 entries and pushes it 
 |           |                           onto the stack. This Operation Push 
 |           |                           gets written to the new Expression.
 v           v                    */
let stuff =DIC4 65536 1 {
/*  +--------------------------- This is a function with key "UI2".
    |       +------------------- This is a 16-bit unsigned int.
    |       |
    v       v */
    +=UI2 item1 1
    +----------------------------------- Operation with key "+=DIC2" same as
    |                                    "=DIC4" except it creates a nested 
    |                                    dictionary except that it takes a 
    |         +------------------------- Token (TKN) type.
    |         |     +------------------- This reserves about 32KB memory with
    |         |     |   +--------------- Maximum of 3 members.
    |         |     |   |               
    v         v     v   v             */
    +=DIC4 things 32768 3 {           /* This is a nested dictionary.
         +------------------------------ This is a operation with key "STR"
         |      +----------------------- Dictionary key.
         |      |    +------------------ Max length 12.
         |      |    |    +------------- STR value.
         |      |    |    |
         v      v    v    v         */
        +=STR (item1 12 "ABC")
        -=Key item1                  //< Operation "-=Key" removes "item1"
        +=UI2 item1 1
        +=UI2 (item2, 2)
        +=UI2 item3 1
        -=Index 2                    //< Removes index 2:"item3".
        +=SI2 item3 -1
        +=UI2 item4 1
        /*< We can't add item4 because we set the max elements to 3.
            This won't generate an error but may generate an error 
            message. */
        Shrink
    }
}
/** Using macros to pass return values as arguments.
    Do you have a better abbreviation for a dictionary?
    Example Function:
    FooBar <DIC4, UI1>:<NIL>
             ^     ^
             |     |
             |     +----- An 8-bit unsigned integer.
             +----------- That is 32-bit dictionary. ({:-)+=< */
FooBar ($stuff, 1);

Parent .Child1.Foo ("Number conversion Example" stuff.things.item1 stuff.things.item2,
                   stuff things item3)

Parent Child1 Foo "Number conversion Example" stuff things item1 stuff things item2,
                   stuff things item3;
 ```

## 4.8 Abnormal Behaviors

Abnormal behavior may be recognized by sever methods. Abnormal behavior are expected to be in burst errors and occasional flipped bits. Script implementations shall utilize the [NIST](https://www.nist.gov/) guidelines.

### 4.8.a Integrity of Escape Sequences

ESC must be checked for integrity before calling the operation if using an insecure transmission line or memory device.

### 4.8.b Integrity of ASCII Objects

LST, MAP, BOK, DIC, Stacks, and Arrays may be used to detect abnormal behavior by checking data structure members are in bounds and all offsets, keys, and hashes are within specification.

### 4.8.c Compromise of Group Automata

Compromised Rooms can be detected by monitoring. 

* Invalid Operations.
* Timing out during Operations. 
* Not closing ESC.
* Invalid B-Stream.
* Losing low-level connection link. 
* Malformed UTF-8 strings.
* Failed Operation Authentication.

It is out of the scope of Script to detect variables that are out of range for Operation arguments.

### 4.7.d Handling Abnormal Behavior

Handling abnormal behavior is left up to the implementation. Implementation may display an error message.

### 4.7.e Reporting Compromised Automata

Compromised Automata shall be reported to the Intergalactic Council of Artifical and Natural Neural Nets (ICAN3) for immediate removal from the Intergalactic Internet Service Providers (IISP) distributed hash table.

## 4.8 Quality of Service 

For all operations that return NIL, there is no checking to see if a function call made. Quality of Service (QoS) is performed using ESC Evaluation. Each Operation with a return value gets a Unicode Operation Index attached to it, which is then used to throw an error if the return arguments were not received. 

## 4.8.a Message Delivery Retry

Each time a data transfer is initiated, a Book with a 

### 4.8.b Message Receipt

A Message may have attached to it a return address. If the message is marked as having a

### 3.8.c Message Ordering

Message ordering is performed using a Library and ESC.

### 3.8.d Observed Operations

Some Operations may be observed by a list of Observers. When an Operation is Observed, any time any of the operation is called, the Observer will report it's changed to the broker using an ESC.

## 3.10 Profiles

Profiles are used to group sets of security profiles into understandable categories. The official structure has not been set, but it is current **Low, Medium, High, and Vital Security Levels**.

## 3.10.a Slave Profiles

A slave device assumes that there is another Automaton or Automata performing the security role.

## 3.11 Encryption

Script uses DTLS 3.1 provided by the Kabuki Toolkit. Please see [https://tools.ietf.org/html/rfc4347](https://tools.ietf.org/html/rfc4347) for details.

## 3.12 Portals
 
A portal is a connection that connects two or more rooms. The following is a short list of some of the officially supported protocol transport layers. This is a living document that will be standardized many times thus do not expect this to be the only Portals; as that would be silly.

## 3.12.a Configurations

#### Room-to-Room Portals

Room-to-Room (R2R) Portals are connections from one Chinese Room to another without any network in between. SPI and UART are primary examples. In these cases, synchronization is different, and often dependent on the specific UART hardware. Due to Script's ESC, Script can be streamed serially without the need for any special hardware to start the sequence or control traffic. Often is the case with devices with non-ideal electronic components, the connection will sometimes cut out, and junk data will get streamed to the target. In this situation, streaming a stream of NIL commands will. Sometimes a target will be expecting much more data streamed to it, so to snap the device out of it, an interrupt method is required. There is a different interrupt protocol for each communication protocol. 

#### Hallway Portals

Hallways connect multiple rooms. For each hallway, there exists a Slot that broadcasts messages to Slot in each Door.

### 3.10.b Known Portal Types

#### UART

UART ports operate like a **Abstract Serial Port** with a *Imperfect Transmission Line*. For UART transmission lines Script uses the same interrupt system as the DMX512 Protocol, the difference being rather than 512 bytes an ESC is sent.

#### SPI

SPI connections operate similarly to **UART Portals**. Interrupts are triggered with the SPI Chip Select pin.

#### I2C

Devices connected to I2C, Serial, and SPI do not require additional security measures. These are hard-wired devices so they are assumed to be a slave-master relationship.

#### CAN

Devices connected to I2C, Serial, and SPI do not require additional security measures. These are hard-wired devices so they are assumed to be a slave-master relationship.

#### Bluetooth

Bluetooth connections operate similarly to **UART Portals**.

#### UDP

When using the User Datagram Protocol packets may get dropped. Script runs over UDP by each UDP packet running from root scope. It is advised to not use the *Push Last Operation*.

#### Interprocess

Inter-process communication is assumed to be a secure connection without data loss, but this behavior is not guaranteed.


## 3.13 Congestion Control Table

The **Script Congestion Control Table** (**CCT**) is an array of 2^16 (65536) time slices of 15-bit integers per day offset from midnight. Each value represents the average load of the network from 0 through 32767. This value is then translated directly into the maximum length of a *ASCII Packet*. Endpoints may request a copy of the CCT using the *ENQ Operation*.

Upon opening a *Packet Portal* between a *ASCII Router* and *ASCII Endpoint* the router sends the endpoint the 15-bit maximum packet size. The end-point then readjusts it's *US Book Header Entries* once per time slice.

Three years of data must be stored in order to detect annual cycles such as holidays. To calculate contention the following formula is used:

   current_sample = Sigma (0.85* previos_sample + 0.15 * current) / num_samples

### 3.13.a. Memory Footprint

* *60 (seconds/minute) × 60 (minutes/hour) × 24 (hours/day)* = ***86400 (seconds/day)***
* *(86400 seconds/day) / 2^16(samples/day* = ***1.318359375 (seconds/sample)***

| One Day's Memory | One Week's Memory | Three Year's Memory |
|:----------------:|:-----------------:|:-------------------:|
|      128KB       |        1MB        |      140.928MB      |

## 3.14 Conformance Targets

Script has two currently supported conformance targets: Automaton and Automata.

### 3.14.a Automaton

The Target shall be certified to be a Script Automaton if the Target does not support Interprocess LISP.

### 3.14.b Group Automata

The Target shall be certified as a Group Automata if the Target supports Interprocess LISP.

### 3.15 Crabs Compilers

```
@warning This is a new section and it will change as soon as the code is 
         actually working
```

The Chinese Room Abstract Stack Machine Compiler shall translate be translated to a register stack machine by using a hardware assisted stack where the B-Stream is pushed onto the stack in the C function call convention. Operations shall be precompiled or JIT compiled and ESC Stack Operations shall be translated from Stack Vector Addresses directly to the Operand's address in memory. For example Object A is pushed onto the Operand Stack followed by Operand B, then C followed by an Operation on C, followed by two Pop Operations and another Operation on Operand A. Rather than inserting code for the Operand Stack Operations for A to C and back, Crabs Compilers shall translate the ADR directly to a single pointer Operands A and C in this example.

---

# 5 ICAN3 Distributed Nomination System

The **ICAN3 Distributed Nomination Systems** (**ICAN3 DNS**) is a technology for the fair promotion of unique key domains to the **Global Namespace** (i.e. ".com websites"). It's designed to make corporate control of the .com a domain a thing of the past. In ICAN3 DNS, keys without and .tags are Global in scopes, meaning they go to the DNS Authorities for that planet.

## 5.1 Internet Guilds

Internet Guilds (IG or IGs) are closely or loosely associated groups of people who provide the internet and form the **Internet Guild System** (**IG System**). It's designed to be an equalizing flexible structure that doesn't discriminate against people based on income or lack of preemptive domain registration ability. The IG System is built around the concept of a *registered entity*, which could be a human, business, organization, government, alien, AI, etc; it is an entity that is legally able to sign a legally binding contract under a Government. Every registered entity is a **ASCII Guild Member** that operates under the **me DNS Service**.

### 5.1.a Government

A tree structure of one or more levels of hierarchies of *ICAN3 Recognized Governments* that provide the **gov DNS Service**. A *registered gov entity* must be a member of one or more Guilds and may not be a member of an Organization. The top-level DNS is "ican3.gov". ICAN3 more like a free open-source engineering consultant board for *Guild Members* than an elected government. ICAN3 has no political power other than as a technology infrastructure advisor and provider role.

### 5.1.b School

An accredited school that provides the **edu DNS Service**. A *registered edu entity* must be a member of a *Guild*.

### 5.1.c Organization

A tree hierarchy of one or more levels of hierarchies of Organizations of **registered entities** that provide DNS and uses the **org DNS Service**. Every Organization is required to be a member of a Government but entities of *Governments* may not be members of *Organizations*. *Organizations* that exist without *Governments* are by definition a *Government*. An IISP is an example of an organization.

## 5.2 Geographic Coordinate Grid Guild
There is one **Geographic Coordinate Grid (GCG) Guild** per one-degree longitude and latitude. There is a maximum of 2,008,800 (= (360 longitudes * 180 latitudes) * 32 heights) GCG Guilds on every planet, most of which are **uninhabited** meaning there is no internet there.

### 5.2.a GCG Guild Example

There is an imaginary single boat running the only Script network an Ocean on some planet. This boat automatically becomes the *Local GCG Guild* and *Local DNS Authority* with UP IP address 0.0.0.0.1. An assault craft comes with the slower internet than the boats. This assault craft then becomes 0.0.0.0.0.2 A starship shows up with a **Intergalactic Internet Hub** (**IIH**) that is much faster. This starship then becomes 0.0.0.0.0.1, the boat becomes 0.0.0.0.0.3, and the assault craft becomes 0.0.0.0.3. A second boat then comes with a Script Network that is the same speed as the boats. This boat then becomes 0.0.0.0.0.3 the assault craft becomes 0.0.0.0.4. A second starship shows up with an IIH. This ship then becomes 0.0.0.0..2, shifting all of the addresses above them up one. This process continues with each network self-optimizing in priority of fastest connections.

In order to keep track of the change in IP Addresses, each Script Network must keep a **UPI Address Forwarding Table**. This is a table used for forwarding packets to the correct destination when there is peer churn and nodes come in and out of the system. *Guild Keys* are then used to ensure the identity of the correct recipient.

## 5.3 ICAN3 DNS Authority Hierarchy

The *Intergalactic Council of Artificial and Natural Neural Nets (ICAN3) DNS Authority* operates under the key **ican3.gov**. ICAN3 is a massively parallel AI supercomputer Chinese Room and Group Automata distributed around the universe. ICAN3 uses Artificial Intelligence and Machine Learning (AIML) to optimize the internet and provide free and democratized AIML to the world through *Intergalactic Internet Service Providers (IISP)*. *IISPs* provide supercomputer time for the **ICAN3 Authorities**. Each *IISP* and it's subscribers are a member of a *Internet Guild* as well as the *ICAN3 Governance*, which is in turn governed by the local government in that *GCG Guild*. If multiple governments have land claims in that grid, all governments will be part of that *GCG Guild*.


```     
                 _________
                 | ICAN3 |
                 |   L0  |
                 |_______|
          ___________|_____________
          |                       |
      _________               _________   
      | SDNSA |               | SDNSA |
      |   L1  |               |   L1  |
      |_______|               |_______|
    _____|______             _____|______
   |            |           |           |
_________   _________   _________   _________
| LDNSA |   | LDNSA |   | LDNSA |   | LDNSA |
|   L2  |   |   L2  |   |   L2  |   |   L2  |
|_______|   |_______|   |_______|   |_______|
    |           |           |           |
   ...         ...         ...         ...
```

## 5.4 Registering an Internet Guild

Registering a *Internet Guild* requires a server computer with fixed *UP IP Address*. This server is responsible for resolving DNS Queries for the *guild*.

## 5.5 Key Promotion

Keys are promoted through the *Internet Guilds*. Each registered entity gets a free web page that is used by free open-source ad-free social networking software. There can only be a single unique key per *ASCII Guild* and *Guild Member*. Keys are promoted to the *Planetary Namespace* on a *Most Unique Hits Basis*. Hit counts shall be tracked through the *Local ICAN3 Authority* and occasional .

## 5.6 DNS Caching

The **Local DNS Authority** (**LDNSA**) is located at address 0.0.0.0.1. In Chinese Rooms expressions are indexed with printable Unicode characters and 0 is a no-op command. 0.0.0.0.1 gets turned into 4 no-ops and a single ASCII SOH Operation that pushes the Library onto the *Expression Stack*. If the key doesn't exist in the Local Cache, the DNS Query is passed on to a *Superior DNS Authority*, if the key does not exist in its cache it will be passed on to the next highest up authority until it is either resolved or returns a **Key Not Found Error**. All Automata have a cache and *Script Automata* shall regularly check with *Superior DNS Authorities* to update and remove keys.

