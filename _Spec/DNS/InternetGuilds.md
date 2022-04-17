# [SCRIPT Specification](../)

## [Distributed Nomination System](./)

### Internet Guilds

Internet Guilds (IG or IGs) are closely or loosely associated groups of people who provide the internet and form the **Internet Guild System** (**IG System**). It's designed to be an equalizing flexible structure that doesn't discriminate against people based on income or lack of preemptive domain registration ability. The IG System is built around the concept of a *registered entity*, which could be a human, business, organization, government, alien, AI, etc; it is an entity that is legally able to sign a legally binding contract under a Government. Every registered entity is a **ASCII Guild Member** that operates under the **me DNS Service**.

#### Government

A tree structure of one or more levels of hierarchies of *ICAN3 Recognized Governments* that provide the **gov DNS Service**. A *registered gov entity* must be a member of one or more Guilds and may not be a member of an Organization. The top-level DNS is "ican3.gov". ICAN3 more like a free open-source engineering consultant board for *Guild Members* than an elected government. ICAN3 has no political power other than as a technology infrastructure advisor and provider role.

#### School

An accredited school that provides the **edu DNS Service**. A *registered edu entity* must be a member of a *Guild*.

#### Organization

A tree hierarchy of one or more levels of hierarchies of Organizations of **registered entities** that provide DNS and uses the **org DNS Service**. Every Organization is required to be a member of a Government but entities of *Governments* may not be members of *Organizations*. *Organizations* that exist without *Governments* are by definition a *Government*. An IISP is an example of an organization.

### Geographic Coordinate Grid Guild

There is one **Geographic Coordinate Grid (GCG) Guild** per one-degree longitude and latitude. There is a maximum of `2,008,800 (= (360 longitudes * 180 latitudes) * 32` heights) GCG Guilds on every planet, most of which are **uninhabited** meaning there is no internet there.

### GCG Guild Example

There is an imaginary single boat running the only Script network an Ocean on some planet. This boat automatically becomes the *Local GCG Guild* and *Local DNS Authority* with UP IP address 0.0.0.0.1. An assault craft comes with the slower internet than the boats. This assault craft then becomes 0.0.0.0.0.2 A starship shows up with a **Intergalactic Internet Hub** (**IIH**) that is much faster. This starship then becomes 0.0.0.0.0.1, the boat becomes 0.0.0.0.0.3, and the assault craft becomes 0.0.0.0.3. A second boat then comes with a Script Network that is the same speed as the boats. This boat then becomes 0.0.0.0.0.3 the assault craft becomes 0.0.0.0.4. A second starship shows up with an IIH. This ship then becomes 0.0.0.0..2, shifting all of the addresses above them up one. This process continues with each network self-optimizing in priority of fastest connections.

In order to keep track of the change in IP Addresses, each Script Network must keep a **UPI Address Forwarding Table**. This is a table used for forwarding packets to the correct destination when there is peer churn and nodes come in and out of the system. *Guild Keys* are then used to ensure the identity of the correct recipient.

#### Registering an Internet Guild

Registering a *Internet Guild* requires a server computer with fixed *UP IP Address*. This server is responsible for resolving DNS Queries for the *guild*.

**[<< Previous Section:](./) | [Next Section: >>](./)**

## Requirements

[1] ./

## License

Copyright 2015-22 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
