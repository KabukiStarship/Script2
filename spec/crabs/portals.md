# [SCRIPT Specification](../readme.md)

## [Crabs](readme.md)

### Portals

A portal is a connection that connects two or more rooms. The following is a short list of some of the officially supported protocol transport layers. This is a living document that will be standardized many times thus do not expect this to be the only Portals; as that would be silly.

#### Configurations

#### Room-to-Room Portals

Room-to-Room (R2R) Portals are connections from one Chinese Room to another without any network in between. SPI and UART are primary examples. In these cases, synchronization is different, and often dependent on the specific UART hardware. Due to Script's ESC, Script can be streamed serially without the need for any special hardware to start the sequence or control traffic. Often is the case with devices with non-ideal electronic components, the connection will sometimes cut out, and junk data will get streamed to the target. In this situation, streaming a stream of kNIL commands will. Sometimes a target will be expecting much more data streamed to it, so to snap the device out of it, an interrupt method is required. There is a different interrupt protocol for each communication protocol.

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

**[<< Previous Section:](./readme.md) | [Next Section: >>](./readme.md)**

## License

Copyright 2014-9 © [Kabuki Starship™](https://kabukistarship.com); all rights reserved.

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
