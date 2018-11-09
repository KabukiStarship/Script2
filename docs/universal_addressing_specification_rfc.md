SCRIPT Specification Experimental RFC
=====================================

# 3. Universal Addressing Specification

**Universal Addressing** or UA is a method of conveying physical addresses and Internet Protocol Addressing that works identically on every planet or spherical object. Before we talk about a UA it helps to see a map of the internet wires on Earth. Here is Earth's Internet Superhighway in the year 2017 center about 0 degrees longitude.

![Earth's Internet Superhighway in the year 2017](http://img.labnol.org/di/undersea_cable_map.png)

The method uses a minimum of a 96-bit IP Address that conveys latitude, longitude, and height above or below sea level in the minimum unit of one-degree longitude and latitude. Exact precision is possible using varints and the **Least Significant Longitudinal Unit**, a standard metric unit used to represent the height above or below sea-level in terms of one-degree longitude at the equator. Because a Script Datagram may be of 0 bytes in length but a header may be up to 40 bytes in length, implementations may require a minimum Datagram length of 40 bytes.

## 3.1  Longitude and Latitude

Latitude and longitude are useful to know in an IP Address because it helps the system route signals to the fastest possible routes through the network.

```
         Longitude           |             Latitude
                             |
        /---> -180           |            /----> 90
       /      _  _           |           /      _  _
      /    =        =        |          /    =        =
     /   =            =      |         /   =            =
  0 |  =     North     =     |      0 |  = _____________ =
    |  =     Pole      =     |        |  =    Equator    =
     \   =            =      |         \   =            =
      \    =        =        |          \    =        =
       \     ~  ~            |           \     ~  ~
        ---> +180            |            ---> -90
```

### 3.1.a Haversine Formula

Haversine Formula's is used to calculate 3D arc lengths using polar coordinates with a known radius.

* Let power be a function that takes two real number parameters (a, b), and returns *a to the power of b*.
* Let L = degrees_longitude = L_2- L_1
* Let l = degrees_latitude = l_2 - l_1
* Let a = power (power ((sin (l / 2), 2) + cos (l_1) * cos(l_2) * (sin(L / 2), 2)
* Let c = 2 * atan2 ( sqrt(a), sqrt(1 - a) )
* Let d = R * c

## 3.2 Most Longitudinal bit

A Most Longitudinal bit (MLb) is a metric unit invented for the SCRIPT Protocol measured in meters per Most Significant bit (M/MSb) and defined by the arc length of one-degree longitude at the equator per MSb. Each one degree latitude by one degree longitude grid shall be referred to as a **Degree Grid**. The MLb is used to route signals to orbiting satellites, aircraft, ground, ultra-high speed fiber optic, and submarine Script Networks.

## 3.3 Universal Address Format

The Universal IP Address Format consists of a 3 integer values for Longitude, latitude, and Height above or below sea level. The *UIP Address Format* uses a data compression technique called *MSb Variant Encoding* to create a **Varint**, which uses the *Most Significant bit* to signal whether to load another octet consisting of 7 more MSb plus one stop bit in the MSb. Varints are used to give exact precision with up to address length cap, and can also be used for transmitting ultra-precise laser signals and receiving sub-centimeter level accurate GPS coordinates.

Polar coordinates are used in 2D polar subnets in order to sort systems based on fastest to slowest connections in a *Star Configuration*. The closest you are to the center of the circles, the faster the internet runs by the natures of light speed electrical signal propagation.

### 3.3.a Universal Address Format Packet

***Notice of change*** *This packet format is not set in stone or tested. The IPv6 protocol uses 128-bit headers, but that just isn't necessary with UPIP because routing MAY require fewer stages of translation or it may not depending on how the circuits pan out.*

|  b95-b64  | b38-b32 |  b31  | b30-b24 |  b23  | b22-b12  |  b14  |  b13-b5   |  b_4  | b_3-b_0 |
|:---------:|:-------:|:-----:|:-------:|:-----:|:--------:|:-----:|:---------:|:-----:|:-------:|
|     0     | Radians |   0   |  Radius |   0   | Latitude |   0   | Longitude |   0   | Height  |
|       |   (-)   |       |   (+)   |       |   (-)    |       |   (-)     |       |   (-)   |
|       |    A    |       |    R    |       |    l     |       |    L      |       |    H    |
|       | Varint  |       |  Varint |       |  Varint  |       |  Varint   |       | Varint  |
| 1 bit | 7 bits  | 1 bit |  7 bits | 1 bit |  9 bits  | 1 bit |  8 bits   | 1 bit | 4 bits  |

* Key: (+) means unsigned and (-) means signed.

### 3.3.b Address Ranges

All address ranges with (longitude greater than +180 or less than -180) and (latitude greater than +90 or less than -90) are reserved for authoritative endpoints. All address ranges with height equal to -32 and height_varint_bit belong to *off-planet addresses*. Most *off-planet address* require very precise coordinates, so each *Interstellar Internet Route* shall have a minimum number of varint bytes required of each type.

## 3.4 Off-planet Signals

All off-planet signs are routed using the UAF Height Value of all logic level 1(s). For a 5-byte packet, this is a value of -16. When this Height is detected, the signal gets routed to one of 64800 possible directions based on 360 degrees longitude times 180 latitude. Currently, no starships exist for this task but they are being designed by the Kabuki Starship team; the open-source organization behind Script.

## 3.4 1 Binary Degree Grid Routing

It is not possible for any router to be located at the exact center of a 1 degree latitude by 1 degree longitude grid, nor does it need to be because there are a manageably small number of fiber optics cables to route and thus the center of the grid is defined as the fastest internet connection in that Degree Grid. All other organizations that provide the internet backbone are then referenced again in polar coordinates from the Degree Grid Reference

[<< Previous](script_sdnp_specification_rfc.md) **|** [Next >>](universal_addressing_specification_rfc.md)
