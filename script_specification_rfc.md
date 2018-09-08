SCRIPT Specification RFC
========================

# 1. Overview

The Searle's Chinese Room, Interposes, and Telemetry (SCRIPT in all caps) Specification defines this Overview Specification, ASCII Data Types Specification, and the SCRIPT Protocol Specification, Universal Polar Addressing, and ICAN3 Distributed Nomination System. Script, which consists of the SCRIPT Protocol, Chinese Room Abstract Stack Machine (Crabs), and Script^2 is best described as a combination of Lua, JavaScript, Python, and LISP that is suitable for embedded purposes and is portable to almost any microprocessor and pen and paper computer. Script works over almost any serial communication protocol or encryption method and has its own multi-master physical reference bus using a series-parallel RS-485 connection over grounded 9-wire Ethernet cable.

Please note that this RFC is not an ISO Specification but is a living document; your comments and criticism are welcome. If you would like to contribute to this RFC, please email [Cale McCollough](https://calemccollough.github.io) at [cale.mccollough@gmail.com](mailto:cale.mccollough@gmail.com).

## 1.1 Content Table

1.  [Overview](#1-overview)
    1.  [Content Table](#11-content-table)
    2.  [Author](#12-overview)
    3.  [License](#13-license)
    4.  [Terminology](#14-terminology)
    5.  [Script Classes](#15-script-classes)
2.  [ASCII Data Types Specification](#2-ascii-data-types-specification)
    1.  [ASCII Data Types Table](#11-ascii-data-types-table)
    2.  [Integers](#12-integers)
    3.  [Boolean Values](#13-boolean-values)
    4.  [Floating-point Numbers](#14-floating-point-numbers)
    6.  [Timestamps](#16-timestamps)
    7.  [B-Sequences](#17-b-sequences)
    8.  [Objects](#18-objects)
4. [SCRIPT Protocol Specification](#4-script-protocol-specification-rfc)
    1.  [Chinese Room Abstract Stack Machine (Crabs) Overview](#41-chinese-room-abstract-stack-machine-crabs-overview)
    2.  [Group Automata Theorem](#432-group-automata-theorem)
    3.  [Time](#43-time)
    4.  [Slots](#44-slots)
    5.  [Expressions](#45-expressions)
    6.  [Operations](#46-operations)
    7.  [Generic Handshake](#47-generic-handshake)
    8.  [Authentication](#48-authentication)
    9.  [Chinese Room Objects](#49-chinese-room-objects)
    10. [Quality of Service](#410-quality-of-service)
    11. [Profiles](#411-profiles)
    12. [Encryption](#412-encryption)
    13. [Terminals](#413-terminals)
    14. [Quality of Service](#414-quality-of-service)
    15. [Congestion Control](#415-congestion-control)
    16. [Abnormal Behavior](#416-abnormal-behavior)
    17. [Crabs Interpreters and Compilers](#417-crabs-interpreters-and-compilers)
    18. [Conformance Targets](#418-conformance-targets)
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
