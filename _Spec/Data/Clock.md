# Clock

The ASCII Clock tells time five different ways: TMC (32-bit Time) are traditional 32-bit unsigned Unix timestamps, TMS are 64-bit Unix signed seconds timestamp, TMT (Time Ticker) uses a 32-bit unsigned Seconds timestamp and 32-bit unsigned subsecond spin ticker, and TMD are 64-bit Subsecond Id, and TME are 128-bit Subsecond Id UUIDs. The POD types 0 through 31 only includes 64-bit TMD and 128-bit TME Subsecond Id, but users can map TMC to the Plain Context Types 20 through 31.

In an ideal world we would use a microseconds or better clock, but x86 CPUs use a seconds clock and for the most part we don't need a microsecond clock and converting requires an expensive division instruction. Given the lack of space for TMC, the Subsecond Id had to be a POD type and not the Extended Types.

## TMD

The TMD type is a 64-bit Subsecond Id with three bit patterns, a Hot UUID Bit Pattern, a Cold UUID Bit Pattern, and Eternal UUID Bit Pattern. The Cold and Eternal UUID Bit Patterns are designed to have a short timestamp epoch of 4.25 years that is easy to look up the Cold UUID Bit Pattern using a binary search. All TMD use unsigned seconds and unsigned ticks because they wrap around after epoch. The number of subsecond ticks has been capped at 192 per second on purpose to rate limit servers data entries per second.

Hot UUID are designed to be used by distributed hot-to-archive databases. Servers may use one randomly generated number for their source id, or a pool of assigned random numbers, or whatever the stakeholders want.

A 34-bit seconds timestamp was chosen for the Cold UUID Bit Pattern because of it's 544.4-year epoch making sure everyone around today is long gone and in a simulation. The Cold UUID's 29-bit subsecond ticker allows for over 5 million UUID generated per second for the entire distributed system, which is enough for the vast majority of use cases but no UUID format is a silver bullet. We mitigate this using Eternal Id, which require generating a random number at run time, rate limiting the UUID per second.

All Hot UUID must be moved to the Cold database within 4 years, or be converted to Eternal UUID. When Hot UUID are converted to Cold UUID, the indexes must be sorted to allow for binary search lookup based on the Hot UUID.

### Hot UUID Bit Pattern

The MSb of the Hot UUID Bit Pattern is always 1 and the subsecond ticker is always less than 192.

```AsciiArt
+--------------------------------------------------------------------+
| MSb:1 | 27-bit seconds | 8-bit subsecond ticker | 28-bit random id |
+--------------------------------------------------------------------+
```

### Eternal UUID Bit Pattern

The MSb and bits 35:34 of the Eternal UUID Bit Pattern are always 1.

```AsciiArt
+------------------------------------------------------------------+
| MSb:1 | 27-bit seconds | Bit 35:1 | Bit 34: 1 | 34-bit random id |
+------------------------------------------------------------------+
```

### Cold UUID Bit Pattern

The MSb of the Cold Bit UUID Pattern is always 0.

```AsciiArt
+------------------------------------------------------------+
|  MSb:0 | 34-bit unsigned seconds | 29-bit Subsecond ticker |
+------------------------------------------------------------+
```

## TMT

TMT (Time Ticker) contains a 32-bit unsigned seconds timestamp and 32-bit subsecond ticker. TMT is the most common way to do a subsecond clock on x86 systems using a dedicated thread.

### 64-bit Time Ticker Bit Pattern

```AsciiArt
+----------------------------------------------+
| MSB 32-bit seconds | 32-bit subsecond ticker |
+----------------------------------------------+
```

## TME

TME is a 128-bit Subsecond Id that uses a 36-bit unsigned seconds timestamp in the MSB, 16-bit unsigned subsecond ticker, and 76-bit unsigned random id in the LSB. TME is primarily for high throughput distributed systems that need to generate up to 64K UUIDs per second. Systems may use the same 76-bit random id for all UUIDs, or generate a new random number every time.

### 128-bit Universally Unique Id Bit Pattern

```AsciiArt
+--------------------------------------------------------------------------+
| MSB 36-bit unsigned seconds | 16-bit subsecond ticker | 76-bit Random id |
+--------------------------------------------------------------------------+
```

## Requirements

* [10] ../overview/requirements

[SCRIPT Specification](../) **>** [ASCII Data Specification](./)

**[<< Previous Section: Strings](Strings) | [Next Section: Strings >>](Strings)**

Copyright [AStarship™](https://astarship.net).
