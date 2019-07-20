# [SCRIPT Specification](../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [SCRIPT Protocol](readme.md)

### Generic Handshake

1. Let **host_a** and **host_b** be *Chinese Rooms* connected through a serial connection or package switched network.
2. Let **host_a** and **host_b** exchange packets of size 1 UI1 and ** be 16-bit prime multiple hashes of the packets with single bytes.
3. Let └¿�☺ be the IPv4 address 192.168.0.1 of **host_a** and ☻�¿└ be the address from **host_b** to host_a**.
4. Let └¿�☻  be the IPv4 address 192.168.0.1 of **host_b** and ☺�¿└ be the address from **host_a** to **host_b**.
5. Let **A**, **B**, and **C** be a generic 3-way handshake on a generic application in some generic upper-level communication protocol over Script.
6. **host_a** initiates a connection handshake by sending the sequence of bytes:
    1. ☺└¿�☻A**
7. **Script Router** automatically adds the inverse router return address, each stage executing the Script Hash Function to create the final UI1 sequence:
    1. ☺└¿�☻A**☺�¿└**
8. **host_b** response from the handshake with the sequence of bytes:
    1. ☺└¿�☺B☻�¿└**
9. **Script Router** adds return address and hash:
    1. ☺└¿�☺B**☻�¿└**
10. **host_a** responds with the connection response with the sequence of bytes:
    1. ☺└¿�☻C**
11. **Script Router** adds return address and hash:
    1. ☺└¿�☺B**☻�¿└**
12. **host_a** and **host_b** are now connected.