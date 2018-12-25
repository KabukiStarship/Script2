SCRIPT Specification RFC
========================

# 1. Overview

The Serial Chinese Room, Interprocess, and Telemetry (SCRIPT) Specification defines this Overview Specification, Automaton Standard Code for Information Interchange (ASCII) Data Types Specification, and the SCRIPT Protocol Specification, and Universal Polar Addressing. Script, which consists of the SCRIPT Protocol, Chinese Room Abstract Stack Machine (Crabs), and Script^2 is best described as a combination of Lua, JavaScript, Python, and LISP that is suitable for embedded purposes and is portable to almost any microprocessor and pen and paper computer. Script works over almost any serial communication protocol or encryption method and has its own multi-master physical reference bus using a series-parallel RS-485 connection over grounded 9-wire Ethernet cable.

Please note that this RFC is not an ISO Specification but is a living document; your comments and criticism are welcome. If you would like to contribute to this RFC, please email [Cale McCollough](https://calemccollough.github.io) at [cale.mccollough@gmail.com](mailto:cale.mccollough@gmail.com).

## 1.1 Content Table

1.  [Overview](#1-overview)
    1.  [Content Table](#11-content-table)
    2.  [Author](#12-overview)
    3.  [License](#13-license)
    4.  [Terminology](#14-terminology)
    5.  [Script Classes](#15-script-classes)
2.  [ASCII Data Types Specification](ascii_data_specification_rfc.md#2-ascii-data-types-specification)
    1.  [ASCII Data Types Table](ascii_data_specification_rfc.md#11-ascii-data-types-table)
    2.  [Integers](ascii_data_specification_rfc.md#12-integers)
    3.  [Boolean Values](ascii_data_specification_rfc.md#13-boolean-values)
    4.  [Floating-point Numbers](ascii_data_specification_rfc.md#14-floating-point-numbers)
    6.  [Timestamps](ascii_data_specification_rfc.md#16-timestamps)
    7.  [B-Sequences](ascii_data_specification_rfc.md#17-b-sequences)
    8.  [Objects](ascii_data_specification_rfc.md#18-objects)
3. [Universal Addressing Specification](script_protocol_specification_rfc.md)
  1. [Longitude and Latitude](script_protocol_specification_rfc.md#31-longitude-and-latitude)
  2. [Most Longitudinal bit](script_protocol_specification_rfc.md#32-most-longitudinal-bit)
  3. [Universal Address Format](script_protocol_specification_rfc.md#33-universal-address-format)
4. [SCRIPT Protocol Specification](script_protocol_specification_rfc.md#3-script-protocol-specification)
    1.  [Chinese Room Abstract Stack Machine (Crabs) Overview](script_protocol_specification_rfc.md#31-chinese-room-abstract-stack-machine-crabs-overview)
    2.  [Group Automata Theorem](script_protocol_specification_rfc.md#332-group-automata-theorem)
    3.  [Time](script_protocol_specification_rfc.md#33-time)
    4.  [Slots](script_protocol_specification_rfc.md#34-slots)
    5.  [Expressions](script_protocol_specification_rfc.md#35-expressions)
    6.  [Operations](script_protocol_specification_rfc.md#36-operations)
    7.  [Generic Handshake](script_protocol_specification_rfc.md#37-generic-handshake)
    8.  [Authentication](script_protocol_specification_rfc.md#38-authentication)
    9.  [Chinese Room Objects](script_protocol_specification_rfc.md#39-chinese-room-objects)
    10. [Quality of Service](script_protocol_specification_rfc.md#310-quality-of-service)
    11. [Profiles](script_protocol_specification_rfc.md#311-profiles)
    12. [Encryption](script_protocol_specification_rfc.md#312-encryption)
    13. [Terminals](script_protocol_specification_rfc.md#313-terminals)
    14. [Quality of Service](script_protocol_specification_rfc.md#314-quality-of-service)
    15. [Congestion Control](script_protocol_specification_rfc.md#315-congestion-control)
    16. [Abnormal Behavior](script_protocol_specification_rfc.md#316-abnormal-behavior)
    17. [Crabs Interpreters and Compilers](script_protocol_specification_rfc.md#317-crabs-interpreters-and-compilers)
    18. [Conformance Targets](script_protocol_specification_rfc.md#318-conformance-targets)
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
|                       ASCII | Automaton Standard Code for Information Interchange. |
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
|              Serial Devices | A *abstract device* that can communicate input and/or output with a *serial UI1 stream*. |
|    Serial Transmission Line | A connection between two *Serial Devices*. |
|        Abstract Serial Port | A conceptually perfect *Serial Transmission Line* with infinite bandwidth and zero data corruption. A **ABS** is operated by writing a UI1 and reading a UI1 simultaneously. |
|     Asynchronous B-Sequence | A B-Sequence that can be processed asynchronously. |
|       Local Procedure Calls | (**LPC**) A procedure call executed on a local computer. |
|      Remote Procedure Calls | (**RPC**) A procedure call executed on a foreign computer. |
|                      Socket | A block of memory, typically a ring buffer, used for interprocess communication. |
|                       Print | The action of converting a binary number to a string or copying from one string to another. |
|                       Write | The action of copying a binary number or string to a buffer.|
|                        Read | The action of reading binary data from a buffer to the Program Stack without converting it. |
|                        Scan | The action of converting a text representation of a number to a string or copying a string from one buffer to another. |

## 1.5 Script Classes

|      Class | Code | Description       |
|-----------:|:----:|:------------------|
|      Array | ARY  | An *ASCII Array*. |
|        Bin | BIN  | A *B-Input Sequence*, or *B-Input*, is an A*B B-Input Stream. |
|       Bout | BOU  | A *B-Output Sequence*, or *B-Output*, is an A*B B-Output Stream. |
|      Clock | CLK  | Used for 32-bit and 64-bit timestamps. |
|       Door | DOR  | A door in a Chinese Room that leads to another Chinese Room or Agent. |
|  Interrupt | INT  | An Interrupt that causes the Room to Reset.  |
| Expression | EXP  | An asynchronous Group structured expression. |
|        Log | LOG  | A EXP used for a log. |
|  Operation | OPN  | A header for an Operation. |
|    Operand | OPD  | A header for an Operation. |
|     Portal | PTL  | A B-Sequence portal to another Chinese Room. |
|       Room | ROO  | A Chinese Room that can read and write B-Sequences. |
|        Set | SET  | Interface for a *ASCII Set Data Type*. |
|       Slot | SLT  | A slot (i.e. Socket) in a Door in a Chinese Room in the form of a Ring Buffer Socket. |
|      Table | TBL  | A Symbol Table implemented as a Set with no data. |
|       Wall | WAL  | A Wall in a Chinese Room composed of a contiguous word-aligned block of memory. |

## 1.6 Hardware Abstraction Layer

Hardware described in the document shall utilize the same abstraction layer called the SCRIPT Hardware Abstraction Layer (HAL).

## 1.5.1 HAL Plain-old Data Types

|        Key | Description |
|-----------:|:-----------:|
|        UIW | Word-sized unsigned integer. |
|        SIW | Word-sized signed integer. |

**|** [ASCII Data Specification >>](script_universal_addressing_specification_rfc.md)
