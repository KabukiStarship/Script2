# [SCRIPT Specification](../)

## [Overview](./)

The Serial Chinese Room, Interprocess, and Telemetry (SCRIPT) Specification defines this Overview Specification, Automaton Standard Code for Information Interchange (ASCII) Data Types Specification, and the SCRIPT Protocol Specification, and Universal Polar Addressing. Script, which consists of the SCRIPT Protocol, Chinese Room Abstract Stack Machine (Crabs), and Script^2 is best described as a combination of Lua, JavaScript, Python, and LISP that is suitable for embedded purposes and is portable to almost any microprocessor and pen and paper computer. Script works over almost any serial communication protocol or encryption method and has its own multi-master physical reference bus using a series-parallel RS-485 connection over grounded 9-wire Ethernet cable.

Please note that this Release for Comment (RFC) is a living document and not an ISO Specification; your comments and criticism are appreciated. If you would like to contribute to this RFC, please email Cale McCollough at <mailto:https://cale-mccollough.github.io>.

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
|              Serial Devices | A *abstract device* that can communicate input and/or output with a *serial IUA stream*. |
|    Serial Transmission Line | A connection between two *Serial Devices*. |
|        Abstract Serial Port | A conceptually perfect *Serial Transmission Line* with infinite bandwidth and zero data corruption. A **ABS** is operated by writing a IUA and reading a IUA simultaneously. |
|     Asynchronous B-Sequence | A B-Sequence that can be processed asynchronously. |
|       Local Procedure Calls | (**LPC**) A procedure call executed on a local computer. |
|      Remote Procedure Calls | (**RPC**) A procedure call executed on a foreign computer. |
|                      Socket | A block of memory, typically a ring buffer, used for interprocess communication. |
|                       Print | The action of converting a binary number to a string or copying from one string to another. |
|                       Write | The action of copying a binary number or string to a buffer.|
|                        Read | The action of reading binary data from a buffer to the Program Stack without converting it. |
|                        Scan | The action of converting a text representation of a number to a string or copying a string from one buffer to another. |

**[<< Previous Section: Requirements](Requirements.md)** | **[Next Section: Object Classes >>](Terminology.md)**

## License

Copyright [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
