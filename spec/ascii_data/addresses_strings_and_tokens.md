# [SCRIPT Specification RFC](../readme.md)

## [ASCII Data Specification](readme.md)

### Addresses, Strings, and Tokens

Script supports UTF-8, UTF-16, and UTF-32 strings (STR), and UTF-8 Addresses (ADR) and Tokens (TKN). TKN and ADR shall contain no whitespace or non-printable characters, i.e. no characters with index less than 33. A Script implementation may enforce strict Unicode compliance. Packed Messages shall use nil-terminated strings and Unpacked Script shall use double-quote-terminated strings with C-style escape sequences. Implementation that support Script^2 shall provide a delimiter char.

```C++
TKN key                 //< No quotes needed for a TKN.
ADR 123                 //< A ADR is a TKN.
STR  "\"Hello world!\"" //< String that reads "Hello world!" with double quotes.
                        //< There is no need to use a 1 to make STR1.
STR2 "\"Hello world!\"" //< This is a _::TStrand<> that is up to 64KB long.
STR4 "\"Hello world!\"" //< This is a _::TStrand<> that is up to 4GB long.
STR8 "\"Hello world!\"" //< This is a _::TStrand<> that is up to 2^64-1 bytes long.
```
