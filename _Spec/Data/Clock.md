# Clock

The ASCII Clock tells time five different ways: TMC (32-bit Time) are traditional 32-bit unsigned Unix timestamps, TMS are 64-bit Unix signed seconds timestamp, TMT (Time Ticker) uses a 32-bit unsigned seconds timestamp and 32-bit unsigned subsecond spin ticker, and SSD are 64-bit Subsecond Id, and SSE are 128-bit Subsecond Id UUIDs.

The ASCII POD types 0 through 31 only includes 64-bit SSD and 128-bit SSE Subsecond Id, but users can map TMC to the Plain Context Types 20 through 31. In an ideal world we would use a microseconds or better clock, but x86 CPUs use a seconds clock and for the most part we don't need a microsecond clock and converting requires an expensive division instruction. Given the lack of space for TMC, the Subsecond Id had to be a POD type and not the Extended Types.

## SSD

The SSD type is a 64-bit Subsecond Id (SSD) with three bit patterns, a Hot UUID Bit Pattern, a Cold UUID Bit Pattern, and Hot Anonymous UUID Bit Pattern. The Cold and Hot Anonymous UUID Bit Patterns are designed to have a short timestamp epoch of 4.25 years, of which we only use 4 years. All SSD use unsigned seconds and unsigned ticks.

Hot UUID are designed to be used by distributed hot-to-archive databases. Servers may use one randomly generated number for their source id, or a pool of assigned random numbers, or whatever the stakeholders want.

A 34-bit seconds timestamp was chosen for the Cold UUID Bit Pattern because of it's 544.4-year epoch making sure everyone around today is long gone and in the simulation. The Cold UUID's 34-bit subsecond ticker allows for over 500 million UUID generated per second for the entire distributed system. While enough for the vast majority of use cases, no UUID format is a silver bullet, this is good enough for most use cases. We mitigate this using Hot Anonymous Id, which require generating a random number at run time and risking collisions, slowing down the clients to prevent database overload.

All Hot UUID must be moved to the Cold database within 4 years, or be converted to Hot Anonymous UUID. When Hot UUID are converted to Cold UUID, the indexes must be sorted to allow for binary search lookup based on the Hot UUID.

### Hot UUID Bit Pattern

 The Hot UUID bit pattern is designed to look up the Hot UUID after it's been converted to a Cold UUID using a binary search. The MSb of the Hot UUID Bit Pattern is always 1 and the seconds is always less than the number of seconds if four years (126,230,400). The bit pattern is designed to be in groups of 4 bits for fastest conversion to and from hex. The 8-bit subsecond ticker caps the implementation at 255 Hot UUID per second to rate limit the database to protect against DDoS attacks while speeding up SQL row lookups. After that, you'll have to use a Hot Anonymous UUID or User Defined type.

```AsciiArt
+--------------------------------------------------------------------+
| MSb:1 | 27-bit seconds | 8-bit subsecond ticker | 28-bit source id |
+--------------------------------------------------------------------+
```

The Hot UUID Bit Pattern is the anchor the others are based on, which start with a 27-bits seconds timestamp, then we subtracted the number of seconds in four years (4*365.25*24*60*60), leaving 7,987,328 values for us to break into blocks. For each block we subtract the highest power of 2 that results in a positive number until we split the remaining wasted timestamp values into 9 different blocks. User Defined UUID are defined by the implementation and may be routed to various types of databases.

| Leftovers | bits | total bits | UUID Type      |
| 7,987,328 |  22  |     58     | Hot Anonymous  |
| 3,793,024 |  21  |     57     | Evergreen      |
| 1,695,872 |  20  |     56     | User Defined   |
|   647,296 |  19  |     55     | User Defined   |
|   123,008 |  16  |     52     | User Defined   |
|    57,472 |  15  |     51     | User Defined   |
|    24,704 |  14  |     50     | User Defined   |
|     8,320 |  13  |     49     | User Defined   |
|       128 |   7  |     43     | User Defined   |

### Cold UUID Bit Pattern

The MSb of the Cold Bit UUID Pattern is always 0.

```AsciiArt
+------------------------------------------------------------+
|  MSb:0 | 34-bit unsigned seconds | 29-bit Subsecond ticker |
+------------------------------------------------------------+
```

### Hot Anonymous UUID Bit Pattern

The Hot Anonymous UUID bit pattern is created from the Hot UUID bit pattern where the seconds timestamp is always greater than or equal to 126,230,400 (the number of seconds in 4 years), and less than 130,424,704 (126,230,400 + 2^22). The LSB contains a 31-bit cryptographically secure random id. Like Hot UUID, Hot Anonymous UUID must be converted to a Cold UUID within four years.

```AsciiArt
+-----------------------------------+
| 27-bit seconds | 31-bit random id |
+-----------------------------------+
```

### Evergreen UUID Bit Pattern

The Hot Anonymous UUID bit pattern is created from the Hot UUID bit pattern where the seconds timestamp is always greater than or equal to 130,424,704, and less than 132,521,856 (130,424,704 + 2^21), which is the block above the Hot Anonymous UUID Bit Pattern.

```AsciiArt
+--------------------------------------+
| 34-bit seconds | 23-bit unique index |
+--------------------------------------+
```

## SSE

SSE is a 128-bit Subsecond Id that uses a 36-bit unsigned seconds timestamp in the MSB, 16-bit unsigned subsecond ticker, and 76-bit unsigned random id in the LSB. SSE is primarily for high throughput distributed systems that need to generate up to 64K UUIDs per second. Systems may use the same 76-bit random id for all UUIDs, or generate a new random number every time.

### 128-bit Subsecond Id Bit Pattern

```AsciiArt
+--------------------------------------------------------------------------+
| MSB 36-bit unsigned seconds | 16-bit subsecond ticker | 76-bit Random id |
+--------------------------------------------------------------------------+
```

## TMT

TMT (Time Ticker) contains a 32-bit unsigned seconds timestamp and 32-bit subsecond ticker. TMT is the most common way to do a subsecond clock on x86 systems using a dedicated thread.

### 64-bit Time Ticker Bit Pattern

```AsciiArt
+----------------------------------------------+
| MSB 32-bit seconds | 32-bit subsecond ticker |
+----------------------------------------------+
```

## CPU Memory Coherence

Where the Subsecond Ticker lives in memory is outside the scope of this specification. When incrementing the subsecond ticker can be done a variety of ways. Using shared memory can cause race conditions. Please see the [SCRIPT Specification Crabs Section](../Crabs/) for a reference design using CPU cache line alignment.

## Requirements

* [10] ../overview/requirements.md

[SCRIPT Specification](../) **>** [ASCII Data Specification](./)

**[<< Previous Section: Numbers](Numbers.md) | [Next Section: Strings >>](Strings.md)**

Copyright [AStarship™](https://astarship.net).
