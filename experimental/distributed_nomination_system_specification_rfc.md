SCRIPT Specification Experimental RFC
=====================================

# 5 Distributed Nomination System Specification

The **ICAN3 Distributed Nomination Systems** (**ICAN3 DNS**) is a technology for the fair promotion of unique key domains to the **Global Namespace** (i.e. ".com websites"). It's designed to make corporate control of the .com a domain a thing of the past. In ICAN3 DNS, keys without and .tags are Global in scopes, meaning they go to the DNS Authorities for that planet.

## 5.1 Internet Guilds

Internet Guilds (IG or IGs) are closely or loosely associated groups of people who provide the internet and form the **Internet Guild System** (**IG System**). It's designed to be an equalizing flexible structure that doesn't discriminate against people based on income or lack of preemptive domain registration ability. The IG System is built around the concept of a *registered entity*, which could be a human, business, organization, government, alien, AI, etc; it is an entity that is legally able to sign a legally binding contract under a Government. Every registered entity is a **ASCII Guild Member** that operates under the **me DNS Service**.

### 5.1.a Government

A tree structure of one or more levels of hierarchies of *ICAN3 Recognized Governments* that provide the **gov DNS Service**. A *registered gov entity* must be a member of one or more Guilds and may not be a member of an Organization. The top-level DNS is "ican3.gov". ICAN3 more like a free open-source engineering consultant board for *Guild Members* than an elected government. ICAN3 has no political power other than as a technology infrastructure advisor and provider role.

### 5.1.b School

An accredited school that provides the **edu DNS Service**. A *registered edu entity* must be a member of a *Guild*.

### 5.1.c Organization

A tree hierarchy of one or more levels of hierarchies of Organizations of **registered entities** that provide DNS and uses the **org DNS Service**. Every Organization is required to be a member of a Government but entities of *Governments* may not be members of *Organizations*. *Organizations* that exist without *Governments* are by definition a *Government*. An IISP is an example of an organization.

## 5.2 Geographic Coordinate Grid Guild
There is one **Geographic Coordinate Grid (GCG) Guild** per one-degree longitude and latitude. There is a maximum of 2,008,800 (= (360 longitudes * 180 latitudes) * 32 heights) GCG Guilds on every planet, most of which are **uninhabited** meaning there is no internet there.

### 5.2.a GCG Guild Example

There is an imaginary single boat running the only Script network an Ocean on some planet. This boat automatically becomes the *Local GCG Guild* and *Local DNS Authority* with UP IP address 0.0.0.0.1. An assault craft comes with the slower internet than the boats. This assault craft then becomes 0.0.0.0.0.2 A starship shows up with a **Intergalactic Internet Hub** (**IIH**) that is much faster. This starship then becomes 0.0.0.0.0.1, the boat becomes 0.0.0.0.0.3, and the assault craft becomes 0.0.0.0.3. A second boat then comes with a Script Network that is the same speed as the boats. This boat then becomes 0.0.0.0.0.3 the assault craft becomes 0.0.0.0.4. A second starship shows up with an IIH. This ship then becomes 0.0.0.0..2, shifting all of the addresses above them up one. This process continues with each network self-optimizing in priority of fastest connections.

In order to keep track of the change in IP Addresses, each Script Network must keep a **UPI Address Forwarding Table**. This is a table used for forwarding packets to the correct destination when there is peer churn and nodes come in and out of the system. *Guild Keys* are then used to ensure the identity of the correct recipient.

## 5.3 ICAN3 DNS Authority Hierarchy

The *Intergalactic Council of Artificial and Natural Neural Nets (ICAN3) DNS Authority* operates under the key **ican3.gov**. ICAN3 is a massively parallel AI supercomputer Chinese Room and Group Automata distributed around the universe. ICAN3 uses Artificial Intelligence and Machine Learning (AIML) to optimize the internet and provide free and democratized AIML to the world through *Intergalactic Internet Service Providers (IISP)*. *IISPs* provide supercomputer time for the **ICAN3 Authorities**. Each *IISP* and it's subscribers are a member of a *Internet Guild* as well as the *ICAN3 Governance*, which is in turn governed by the local government in that *GCG Guild*. If multiple governments have land claims in that grid, all governments will be part of that *GCG Guild*.


```     
                 _________
                 | ICAN3 |
                 |   L0  |
                 |_______|
          ___________|_____________
          |                       |
      _________               _________   
      | SDNSA |               | SDNSA |
      |   L1  |               |   L1  |
      |_______|               |_______|
    _____|______             _____|______
   |            |           |           |
_________   _________   _________   _________
| LDNSA |   | LDNSA |   | LDNSA |   | LDNSA |
|   L2  |   |   L2  |   |   L2  |   |   L2  |
|_______|   |_______|   |_______|   |_______|
    |           |           |           |
   ...         ...         ...         ...
```

## 5.4 Registering an Internet Guild

Registering a *Internet Guild* requires a server computer with fixed *UP IP Address*. This server is responsible for resolving DNS Queries for the *guild*.

## 5.5 Key Promotion

Keys are promoted through the *Internet Guilds*. Each registered entity gets a free web page that is used by free open-source ad-free social networking software. There can only be a single unique key per *ASCII Guild* and *Guild Member*. Keys are promoted to the *Planetary Namespace* on a *Most Unique Hits Basis*. Hit counts shall be tracked through the *Local ICAN3 Authority* and occasional .

## 5.6 DNS Caching

The **Local DNS Authority** (**LDNSA**) is located at address 0.0.0.0.1. In Chinese Rooms expressions are indexed with printable Unicode characters and 0 is a no-op command. 0.0.0.0.1 gets turned into 4 no-ops and a single ASCII SOH Operation that pushes the Library onto the *Expression Stack*. If the key doesn't exist in the Local Cache, the DNS Query is passed on to a *Superior DNS Authority*, if the key does not exist in its cache it will be passed on to the next highest up authority until it is either resolved or returns a **Key Not Found Error**. All Automata have a cache and *Script Automata* shall regularly check with *Superior DNS Authorities* to update and remove keys.
