SCRIPT Specification RFC
========================

# 3 SCRIPT Protocol Specification

Script consists of the Group Automata Theorem, SCRIPT Protocol, Chinese room abstract stack machine (Crabs) and Script^2. In the John Searle's famous Chinese Room Thought Experiment users may talk to the Chinese Room (i.e. end-point) by writing Messages (i.e. Datagrams) on a piece of Paper (B-Input) and passing them through a Slot (i.e. Socket) in a Door (Group of communication links leading to the same room) in the room. An Agent (Program or AIML Entity) then reads the message and uses them to operate the Crabs, and replies by writing a Message on a piece of Paper and passing it back through the Slot.

## 3.1 Chinese Room Abstract Stack Machine (Crabs) Overview

The **Chinese Room Abstract Stack Machine** (**Crabs**) is an abstract machine capable of running *Group Automata* using the SCRIPT Protocol and Script^2. Crabs is the standardized Script^2 API for interacting with a Chinese Room with a text terminal over the Script. Script is designed to run over a standard serial connection that allows users to hack on devices in real-time with a PC keyboard, app GUI, or other serial B-Stream so Script makes use of ASCII C0 Codes and VK Keyboard Codes so you can do alt, shift, or control keys on the keyboard to do stuff like copy and paste and Script Macros.

## 3.1.a Crabs Messages

A **Crabs Message** is similar to an internet datagram and may be enclosed in a IPv4 or IPv6 datagram. A Crabs Message is defined as set of stack operations that start and end with an empty Operand Stack where one or more Operands is pushed, All Unicode Operation indexes being valid, all keys being resolved correctly, and the B-Stream being of a valid length for each B-Sequence argument. Crabs Room Messages may be written in any language using UTF-8. Messages get Unpacked by the Expression Interpreter and translated into the native Unicode format, UTF-8, UTF-16, or UTF-32 for that room and may be compiled directly to a register-based stack machine.

Crabs Messages beginning with a non-printable Unicode Character shall be byte-encoded with the data immediately following it be a Packed B-Stream. All Crabs Messages beginning in a printable Unicode char shall be Script^2.

## 3.1.b Chinese Room Contents

A Chinese Room in John Searle's famous thought experiment is just a plain old office with a person in it who is operating a *pen and paper abstract stack machine* that functions identically to computer, only there are no electronic parts. In this room are Doors that lead to other rooms that have people in them. Each Door has a Slot (i.e. a socket) that allows people in rooms to communicate with other rooms with handwritten messages that can be both synchronous and asynchronous. Consequentially, this is exactly how an optimized piece of internet software works. Rooms consist of Doors that lead to other Rooms, Walls that contain Doors, Slots in Doors, One-way Tables, Books, Dictionaries, Maps, Lists, Arrays, Stacks, and Files, and Boxes.

At the root scope of each system lies a *Interrupt Operations* DC1, DC2, DC3, and DC4 Script Operations defined.

#### Walls

**Walls** are contiguous blocks of word-aligned memory used to construct Chinese Rooms out of. Walls are used to install Doors, Filing Cabinets, Book Shelves, Windows, Mirrors, and Tables.

#### Doors

**Doors** in a *Chinese Rooms* are a MAP ASCII Data Type.

#### Mirrors and Windows

**Mirrors** in a *Chinese Rooms* are *Contiguous Word-Aligned Memory Blocks* used for *Expressions* and *Interprocess IO Portals* that use *Word-Aligned Hashless B-Sequences*. When two one-way Mirrors are combined they create a duplex Slot called a **Window**. Mirror and Windows shall be used to for Interprocess Same-System Terminals.

## 3.1.c Compliant Crabs UML Model Example

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

## 3.2 Group Automata Theorem

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

## 3.3 Time Epoch

The Unix timestamp cycles around in the year 3038, so to ensure stability on 32-bit systems with 32-bit TMS timestamps, the time epoch shall be of the span of a decade, and such systems shall not be made to schedule events beyond a 6 epochs. Systems that require schedulers with more than the maximum number of epochs shall use a 64-bit TME timestamp.

## 3.4 Slots

A Socket is defined a block of memory used to transceived data, and is typically implemented as ring buffer. There are two types of slots, a B-Input (BIn) and B-Output (BOut). A **Slot** is defined as a Ring Buffer Socket. BIn and BOut implementations written in a Hardware Development Language may not strictly comply with the contiguous memory operation but shall operate functionally equivalent to the specified register stack machine implementation. For register stack machines with contiguous memory. Each Slot shall begin a 64-bit aligned memory address and shall have a 64-bit aligned end address.

### 3.4.a Slot Data Structure in C

```
struct Slot {
    char* begin, //< Beginning of the ring buffer.
        * start, //< Start of the data in the ring buffer.
        * stop,  //< Stop of the data in the ring buffer.
        * end;   //< End of the ring buffer.
};
```

### 3.4.b B-Input Slot

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

### 3.4.e Windows

Windows combine a BIn and BOut in contiguous memory. The ring buffers function similar to BIn and BOut except that the Slot.stop offset in the B-Input Window gets swapped with duplex B-Output Window. This is because one is a read-only and one is a write only that may occur in parallel as opposed to a strictly serial Slot operation where the room may both read and write to the same Slot.

#### Window Memory Layout

```
+------+
| BOut |
|------|   ^
| BIn  |   |
+------+  0xN
```

### 3.4.f Default In Slot and Out Slot

Script implementations may implement a default BIn Slot named In (**in UpperCaseCamel**)
 and default BOut Slot named Out (**in UpperCaseCamel**). In shall stream bytes from a Text keyboard, BOut Slot or Text display input. Out stream bytes to a Abstract text display, BIn Slot, or Abstract serial output.

## 3.5 Expressions

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

### 3.5.a Operation Header

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
                    //< We need to specify the exact number of bytes.
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

## 3.6 Operations

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

### 3.4.a Crabs Operations

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

**Exponent Operations** (**Exp Op** or **Exp Ops**) work similarly to math exponents only with A*B operations. **Exp Ops** work by specifying the number of loops **Varint**. If the value of the varint is **NaN** then it is a **Infinite Exponential Operations** (**IEO**). **IEOs** are functionally identical to while loops. **Loops** are exited prematurely using the **Clear Operation**.

#### Delete Operation

*Delete Operation* deletes the previous char in the ring buffer.

#### Whitespace Operations

Script is whitespace delimited spaces may be skipped by the interpreter or interpreted as a Operating with index 64 (ASCII ' '). For real-time streaming natural language processing Whitespace Operations are used to identify pauses in speech (i.e. dead audio).

### 3.4.b Interrupt Escape Sequence

Each Room has a single **Interrupt Expression** in the index '/'. When an ESC interrupt byte is received the *Interrupt Expression* is pushed onto the stack. If this ESC returns a Result this Result must be inserted into the location of the ESC in the B-Stream.

#### Mandatory Single Byte Interrupt Operations

| ASCII |    Formal Name      | Description |
|:-----:|:-------------------:|:-----------:|
|  EOT  | End of transmission | Disconnects from the host. |
|  CAN  | Cancel              | Cancels the current Expression being scanned. |

### 3.4.c Device Controls 1-4

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

### 3.4.d Reset Operations

Reset Operations are operations that required the slot in the Chinese Door to be closed. This is typically something like remote firmware updating. Each implementation is responsible for initializing the system and proving The Chinese Room Group Automata Theorem.

### 3.4.e Return Values

Return values just need an address of an Operation to send the return value too. Return values shall be written to the BOut that leads to the initiating Operation's BIn in an automated process. In the case that a different Operation's return address is needed Rooms may pass the return address of the as an input parameter as a TKN type.

## 3.5 Generic Handshake

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

## 3.6 Authentication

Authentication in Script shall be done using a sequence of Script Operations.

## 3.7 Crabs Objects

ASCII Data Types LST, MAP, DIC, BOK, and Stacks and Arrays or ASCII Types 4 through 22 shall be created using Crabs.

### Dictionary Example

```
  +-------------------------- Operation Push "=DIC2" is a function  
  |                           with address stuff that creates a
  |                           dictionary of size 64KB bytes with a
  |                           maximum of 3 entries and pushes it
  |                           onto the stack. This Operation Push
<<<<<<< HEAD
  v                           gets written to the new Expression. */
=======
  v                           gets written to the new Expression.
 v           v                    */
>>>>>>> 8aa74e7eb95d53324850b2fb8a195d79431287d2
stuff =DIC4 65536 1 {
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
        Shrink  //< We just shrunk the DIC4. Sorry, but I had to. Have fun. :-)
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

## 3.8 Abnormal Behaviors

Abnormal behavior may be recognized by sever methods. Abnormal behavior are expected to be in burst errors and occasional flipped bits. Script implementations shall utilize the [NIST](https://www.nist.gov/) guidelines.

### 3.8.a Integrity of Escape Sequences

ESC must be checked for integrity before calling the operation if using an insecure transmission line or memory device.

### 3.8.b Integrity of ASCII Objects

LST, MAP, BOK, DIC, Stacks, and Arrays may be used to detect abnormal behavior by checking data structure members are in bounds and all offsets, keys, and hashes are within specification.

### 3.8.c Compromise of Group Automata

Compromised Rooms can be detected by monitoring.

* Invalid Operations.
* Timing out during Operations.
* Not closing ESC.
* Invalid B-Stream.
* Losing low-level connection link.
* Malformed UTF-8 strings.
* Failed Operation Authentication.

It is out of the scope of Script to detect variables that are out of range for Operation arguments.

### 3.7.d Handling Abnormal Behavior

Handling abnormal behavior is left up to the implementation. Implementation may display an error message.

### 3.7.e Reporting Compromised Automata

Compromised Automata shall be reported to the Intergalactic Council of Artificial and Natural Neural Nets (ICAN3) for immediate removal from the Intergalactic Internet Service Providers (IISP) distributed hash table.

## 3.8 Quality of Service

For all operations that return NIL, there is no checking to see if a function call made. Quality of Service (QoS) is performed using ESC Evaluation. Each Operation with a return value gets a Unicode Operation Index attached to it, which is then used to throw an error if the return arguments were not received.

## 3.8.a Message Delivery Retry

Each time a data transfer is initiated, a Book with a

### 3.8.b Message Receipt

A Message may have attached to it a return address. If the message is marked as having a

### 3.8.c Message Ordering

Message ordering is performed using a Library and ESC.

### 3.8.d Observed Operations

Some Operations may be observed by a list of Observers. When an Operation is Observed, any time any of the operation is called, the Observer will report it's changed to the broker using an ESC.

## 3.9 Profiles

Profiles are used to group sets of security profiles into understandable categories. The official structure has not been set, but it is current **Low, Medium, High, and Vital Security Levels**.

## 3.9.a Slave Profiles

A slave device assumes that there is another Automaton or Automata performing the security role.

## 3.10 Encryption

Script uses DTLS 3.1 provided by the Kabuki Toolkit. Please see [https://tools.ietf.org/html/rfc4347](https://tools.ietf.org/html/rfc4347) for details.

## 3.11 Portals

A portal is a connection that connects two or more rooms. The following is a short list of some of the officially supported protocol transport layers. This is a living document that will be standardized many times thus do not expect this to be the only Portals; as that would be silly.

## 3.11.a Configurations

#### Room-to-Room Portals

Room-to-Room (R2R) Portals are connections from one Chinese Room to another without any network in between. SPI and UART are primary examples. In these cases, synchronization is different, and often dependent on the specific UART hardware. Due to Script's ESC, Script can be streamed serially without the need for any special hardware to start the sequence or control traffic. Often is the case with devices with non-ideal electronic components, the connection will sometimes cut out, and junk data will get streamed to the target. In this situation, streaming a stream of NIL commands will. Sometimes a target will be expecting much more data streamed to it, so to snap the device out of it, an interrupt method is required. There is a different interrupt protocol for each communication protocol.

#### Hallway Portals

Hallways connect multiple rooms. For each hallway, there exists a Slot that broadcasts messages to Slot in each Door.

### 3.11.b Known Portal Types

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

## 3.12 Congestion Control Table

The **Script Congestion Control Table** (**CCT**) is an array of 2^16 (65536) time slices of 15-bit integers per day offset from midnight. Each value represents the average load of the network from 0 through 32767. This value is then translated directly into the maximum length of a *ASCII Packet*. Endpoints may request a copy of the CCT using the *ENQ Operation*.

Upon opening a *Packet Portal* between a *ASCII Router* and *ASCII Endpoint* the router sends the endpoint the 15-bit maximum packet size. The end-point then readjusts it's *US Book Header Entries* once per time slice.

Three years of data must be stored in order to detect annual cycles such as holidays. To calculate contention the following formula is used:

   current_sample = Sigma (0.85* previos_sample + 0.15 * current) / num_samples

### 3.12.a. Memory Footprint

* *60 (seconds/minute) × 60 (minutes/hour) × 24 (hours/day)* = ***86400 (seconds/day)***
* *(86400 seconds/day) / 2^16(samples/day* = ***1.318359375 (seconds/sample)***

| One Day's Memory | One Week's Memory | Three Year's Memory |
|:----------------:|:-----------------:|:-------------------:|
|      128KB       |        1MB        |      140.928MB      |

## 3.13 Conformance Targets

Script has two currently supported conformance targets: Automaton and Automata.

### 3.13.a Automaton

The Target shall be certified to be a Script Automaton if the Target does not support Script^2.

### 3.13.b Group Automata

The Target shall be certified as a Group Automata if the Target supports Script^2.
