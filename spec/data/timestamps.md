# [SCRIPT Specification](../)

## [ASCII Data Specification](./)

### Timestamps

ASCII provides three types of timestamps, a 32-bit signed integer TM4 seconds from epoch timestamp, a 64-bit signed integer TME seconds from epoch timestamp, and 64-bit Time Sub-second (TME) timestamp composed of a TM4 timestamp and a IUC tick that gets incremented at a variable time period. The Sub-second Tick Epoch (STE) shall be programmable but shall be set to the defaults of either 1000 or 64, depending on if a microsecond or OS update timer is used respectively. The operation of the sub-second tick is intended to use unsigned addition wraparound in order to allow one thread to update the sub-second tick. To calculate the number of ticks implementations shall implement unsigned wrap-around checking.

```C++
/* Example functions.
@fn Foo <TM4>:<NIL>
@fn Foo <TM8>:<NIL>
@fn Foo <TME>:<NIL>

# Timestamp Format
| Seconds Since Epoch | Microseconds Since Epoch |
|:-------------------:|:------------------------:|
| YYYY-MM-DD@HH:MM:ss |  YYYY-MM-DD@HH:MM:ss:uu  |

 Month ---v        v—-Minutes  */
Foo 2016-07-13@15:39:23
/*               Hours--^     ^--- seconds
Year --v     v--- Day     v-- ticks */
Foo 2016-07-13@15:39:23:999
```

#### Epoch

The 32-bit time epoch shall be set to 32 years[] starting at the January 1st of the beginning of each decade beginning from 0 AD and the date of the first epoch is January 1st 2048.

#### Max 64-bit Timestamp Range

`(+/-) ((2^62)-1)/(60*60*24*365) = (+/-) 146,235,604,338 years`

**[<< Previous Section:Text](./text) | [Next Section: >>](./)**

## References

* [10] ../overview/requirements

## License

Copyright 2015-9 © [Kabuki Starship™](https://kabukistarship.com); all rights reserved.

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
