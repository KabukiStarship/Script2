# [SCRIPT Specification](../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [Universal Addressing Specification](readme.md)

### Mathmatical Definitions

#### Longitude and Latitude

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

##### Haversine Formula

Haversine Formula's is used to calculate 3D arc lengths using polar coordinates with a known radius.

* Let power be a function that takes two real number parameters (a, b), and returns *a to the power of b*.
* Let L = degrees_longitude = L_2- L_1
* Let l = degrees_latitude = l_2 - l_1
* Let a = power (power ((sin (l / 2), 2) + cos (l_1) * cos(l_2) * (sin(L / 2), 2)
* Let c = 2 * atan2 ( sqrt(a), sqrt(1 - a) )
* Let d = R * c
