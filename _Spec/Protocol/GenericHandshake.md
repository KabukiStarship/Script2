# Generic Handshake

1. Let **host_a** and **host_b** be *Chinese Rooms* connected through a serial connection or package switched network.
2. Let **host_a** and **host_b** exchange packets of size 1 IUA and be 16-bit prime multiple hashes of the packets with single bytes.
3. Let **addr_a** be the IPv4 address 192.168.0.1 of **host_a** and **addr_b** be the address from **host_b** to **host_a**.
4. Let **addr_b** be the IPv4 address 192.168.0.1 of **host_b** and **addr_a** be the address from **host_a** to **host_b**.
5. Let **A**, **B**, and **C** be a generic 3-way handshake on a generic application in some generic upper-level communication protocol over Script.
6. **host_a** initiates a connection handshake by sending the sequence of bytes:
    1. 0x41A** (where 0x41 is the ASCII character 'A')
7. **Script Router** automatically adds the inverse router return address, each stage executing the Script Hash Function to create the final IUA sequence:
    1. 0x41A**0x41** (where 0x41 is the ASCII character 'A')
8. **host_b** response from the handshake with the sequence of bytes:
    1. 0x42B**0x42** (where 0x42 is the ASCII character 'B')
9. **Script Router** adds return address and hash:
    1. 0x42B**0x42** (where 0x42 is the ASCII character 'B')
10. **host_a** responds with the connection response with the sequence of bytes:
    1. 0x43C**0x43** (where 0x43 is the ASCII character 'C')
11. **Script Router** adds return address and hash:
    1. 0x43C**0x43** (where 0x43 is the ASCII character 'C')
12. **host_a** and **host_b** are now connected.

**[<< Previous Section: Encryption](Encryption.md) | [Next Section: Quality of Service >>](QualityOfService.md)**

## Requirements

1. The handshake protocol must be compatible with both serial connections and packet-switched networks.
2. All packets exchanged during the handshake must be exactly 1 IUA in size.
3. Hash values must be 16-bit prime multiples of the packet content.
4. The Script Router must automatically add inverse router return addresses to all packets.
5. Each stage of the Script Router must execute the Script Hash Function to create the final IUA sequence.
6. The handshake must support a 3-way protocol (SYN, SYN-ACK, ACK) for reliable connection establishment.
7. The protocol must handle address resolution for both IPv4 and future IP address formats.
