# [SCRIPT Specification](../readme.md)

## [Universal Addressing Specification](readme.md)

**Universal Addressing** or UA is a method of conveying physical addresses and Internet Protocol Addressing that works identically on every planet or spherical object. Before we talk about a UA it helps to see a map of the internet wires on Earth. Here is Earth's Internet Superhighway in the year 2017 center about 0 degrees longitude.

![Earth's Internet Superhighway in the year 2017](http://img.labnol.org/di/undersea_cable_map.png)

The method uses a minimum of a 96-bit IP Address that conveys latitude, longitude, and height above or below sea level in the minimum unit of one-degree longitude and latitude. Exact precision is possible using varints and the **Least Significant Longitudinal Unit**, a standard metric unit used to represent the height above or below sea-level in terms of one-degree longitude at the equator. Because a Script Datagram may be of 0 bytes in length but a header may be up to 40 bytes in length, implementations may require a minimum Datagram length of 40 bytes.

### Content Table

1. [Mathematical Definitions](mathmatical_definitions.md)
1. [Universal Address Format](universal_address_format.md)
1. [Polar Routing](polar_routing.md)

**<< [Previous Section](.md)** | **[Next Section](.md) >>**

## License

Copyright (C) 2014-9 Cale McCollough <http://calemccollough.github.io/>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
