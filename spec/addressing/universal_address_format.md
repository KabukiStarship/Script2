# [SCRIPT Specification](../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [Universal Addressing Specification](readme.md)

### Universal Address Format

The Universal IP Address Format consists of a 3 integer values for Longitude, latitude, and Height above or below sea level. The *UIP Address Format* uses a data compression technique called *MSb Variant Encoding* to create a **Varint**, which uses the *Most Significant bit* to signal whether to load another octet consisting of 7 more MSb plus one stop bit in the MSb. Varints are used to give exact precision with up to address length cap, and can also be used for transmitting ultra-precise laser signals and receiving sub-centimeter level accurate GPS coordinates.

Polar coordinates are used in 2D polar subnets in order to sort systems based on fastest to slowest connections in a *Star Configuration*. The closest you are to the center of the circles, the faster the internet runs by the natures of light speed electrical signal propagation.

#### Most Longitudinal bit

A Most Longitudinal bit (MLb) is a metric unit invented for the SCRIPT Protocol measured in meters per Most Significant bit (M/MSb) and defined by the arc length of one-degree longitude at the equator per MSb. Each one degree latitude by one degree longitude grid shall be referred to as a **Degree Grid**. The MLb is used to route signals to orbiting satellites, aircraft, ground, ultra-high speed fiber optic, and submarine Script Networks.

#### Universal Address Format Packet

***Notice of change*** *This packet format is not set in stone or tested. The IPv6 protocol uses 128-bit headers, but that just isn't necessary with UPIP because routing MAY require fewer stages of translation or it may not depending on how the circuits pan out.*

|  b95-b64  | b38-b32 |  b31  | b30-b24 |  b23  | b22-b12  |  b14  |  b13-b5   |  b_4  | b_3-b_0 |
|:---------:|:-------:|:-----:|:-------:|:-----:|:--------:|:-----:|:---------:|:-----:|:-------:|
|     0     | Radians |   0   |  Radius |   0   | Latitude |   0   | Longitude |   0   | Height  |
|       |   (-)   |       |   (+)   |       |   (-)    |       |   (-)     |       |   (-)   |
|       |    A    |       |    R    |       |    l     |       |    L      |       |    H    |
|       | Varint  |       |  Varint |       |  Varint  |       |  Varint   |       | Varint  |
| 1 bit | 7 bits  | 1 bit |  7 bits | 1 bit |  9 bits  | 1 bit |  8 bits   | 1 bit | 4 bits  |

* Key: (+) means unsigned and (-) means signed.

#### Address Ranges

All address ranges with (longitude greater than +180 or less than -180) and (latitude greater than +90 or less than -90) are reserved for authoritative endpoints. All address ranges with height equal to -32 and height_varint_bit belong to *off-planet addresses*. Most *off-planet address* require very precise coordinates, so each *Interstellar Internet Route* shall have a minimum number of varint bytes required of each type.

#### Off-planet Signals

All off-planet signs are routed using the UAF Height Value of all logic level 1(s). For a 5-byte packet, this is a value of -16. When this Height is detected, the signal gets routed to one of 64800 possible directions based on 360 degrees longitude times 180 latitude. Currently, no starships exist for this task but they are being designed by the Kabuki Starship team; the open-source organization behind Script.
