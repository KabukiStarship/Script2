# SCRIPT Specification RFC

## 1. Overview

The Serial Chinese Room, Interprocess, and Telemetry (SCRIPT) Specification defines this Overview Specification, Automaton Standard Code for Information Interchange (ASCII) Data Types Specification, and the SCRIPT Protocol Specification, and Universal Polar Addressing. Script, which consists of the SCRIPT Protocol, Chinese Room Abstract Stack Machine (Crabs), and Script^2 is best described as a combination of Lua, JavaScript, Python, and LISP that is suitable for embedded purposes and is portable to almost any microprocessor and pen and paper computer. Script works over almost any serial communication protocol or encryption method and has its own multi-master physical reference bus using a series-parallel RS-485 connection over grounded 9-wire Ethernet cable.

Please note that this RFC is not an ISO Specification but is a living document; your comments and criticism are welcome. If you would like to contribute to this RFC, please email Cale Jamison McCollough <<cale@astartup.net>> at [cale.mccollough@gmail.com](mailto:cale.mccollough@gmail.com).

### 1.1 Content Table

1. [Overview](overview)
    1. [Content Table](#content-table)
    1. [Author](#overview)
    1. [License](#license)
    1. [Terminology](#terminology.md)
    1. [Script Classes](#script2_classes.md)
2. [ASCII Data Types Specification](ascii_data/readme.md)
    1. [Integers](ascii_data/integers.md)
    1. [Boolean Values](ascii_data/boolean_values.md)
    1. [Floating-point Numbers](ascii_data/floating-point_numbers.md)
    1. [Timestamps](ascii_data/timestamps.md)
    1. [B-Sequences](ascii_data/b-sequences.md)
    1. [Objects](ascii_data/objects.md)
3. [Universal Addressing Specification](script_protocol/readme.md)
    1. [Longitude and Latitude](script_protocol/longitude_and_latitude.md)
    1. [Most Longitudinal bit](script_protocol/most_longitudinal_bit.md)
    1. [Universal Address Format](script_protocol/universal_address_format.md)
4. [SCRIPT Protocol Specification](script_protocol/readme.md)
    1. [Group Automata Theorem](script_protocol/group_automata_theorem.md)
    1. [Time](script_protocol/time.md)
    1. [Slots](script_protocol/slots.md)
    1. [Expressions](script_protocol/expressions.md)
    1. [Operations](script_protocol/operations.md)
    1. [Generic Handshake](script_protocol/generic-handshake.md)
    1. [Chinese Room Objects](script_protocol/chinese_room_objects.md)
    1. [Profiles](script_protocol/profiles.md)
    1. [Encryption](script_protocol/encryption.md)
    1. [Terminals](script_protocol/terminals.md)
    1. [Quality of Service](script_protocol/quality_of_service.md)
    1. [Congestion Control](script_protocol/congestion_control.md)
    1. [Abnormal Behavior](script_protocol/abnormal_behavior.md)
5. [Crabs Specification](crabs/readme.md)
    1. [Authentication](crabs/authentication.md)
    1. [Conformance Targets](crabs/conformance-targets.md)
    1. [Crabs Interpreters and Compilers](crabs/interpreters_and_compilers.md)
    1. [Room Contents](crabs/room_contents.md)

### Author

Cale Jamison McCollough

### License

Copyright 2014-19 (C) Cale Jamison McCollough <<cale@astartup.net>>. All rights reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

### Terminology

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

### Script2 Classes

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

**|** [ASCII Data Specification >>](../universal_addressing/readme.md)
