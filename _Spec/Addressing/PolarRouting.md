# [SCRIPT Specification](../)

## [Universal Addressing Specification](./)

### Polar Routing

It is not possible for any router to be located at the exact center of a 1 degree latitude by 1 degree longitude grid, nor does it need to be because there are a manageably small number of fiber optics cables to route and thus the center of the grid is defined as the fastest internet connection in that Degree Grid. All other organizations that provide the internet backbone are then referenced again in polar coordinates from the Degree Grid Reference.

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

**[<< Previous Section: Universal Addressing Specification](./) | [Next Section: Universal Address Format>>](./UniversalAddressFormat.md)**

## Requirements

[1] ./

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
