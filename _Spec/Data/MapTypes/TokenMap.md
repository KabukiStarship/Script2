# Token Map

***[Spec](../../) > [Data](../) > [Map Types](./)***

A Token Map (TKM) is a input text tokenizer.

## Memory Layout

The TKM uses the Table memory layout with some extra variables.

```C++
template<typename CHT = CHR, typename ISZ = ISR, typename ISY = ISQ, typename HSH = IUN>
struct TTable {
  ISZ bytes,          //< Size of this object in bytes.
      stop;           //< Keys boofer stop offset or start if count == total.
  TStack<SCK_P> map;  //< A Stack of offset mappings to strings.
```

## Requirements

[1] ./

[SCRIPT Specification](../) **>** [ASCII Data Specification](./) **>** [Map Types](.)

**[<< Previous Section: Dictionary](Dictionary.md) | [Next Section: Map Types Overview >>](../)**

Copyright [AStarship™](https://astarship.net).
