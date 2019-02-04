# [SCRIPT Specification RFC](../readme.md)

## [ASCII Data Specification](readme.md)

### Text

ASCII Text consists of the Strand (STR), the Address (ADR), and Token (TKN) which may be formatted in UTF-8, UTF-16, and UTF-32 strings using the STR. The difference between a string and a strand is that a string is exactly one string, but a strand is a socket that may contain one or more strings.

```C++
TKN key                  //< No quotes needed for a TKN.
ADR 123                  //< A ADR is a TKN.
STR1  "\"Hello world!\"" //< String that reads "Hello world!" with double quotes.
STR2 "\"Hello world!\""  //< This is a _::TStrand<> that is up to 64KB long.
STR4 "\"Hello world!\""  //< This is a _::TStrand<> that is up to 4GB long.
```
