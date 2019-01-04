# Secure Coding Standards

This is the begging of the Secure Coding Standards Documentation for Script2. I'm not the most knowledgeable about cyber security.

## Array Bounds Checking

Array bounds checking is to be performed on all data that is not known to be a C-style string at compile time. All functions requiring bounds checking shall pass in the end of buffer pointer. Each function shall also contain an additional function that takes the size of the buffer as a signed integer. Bounds are set by the ASCII Data Specification.

## Input Sanitization

All data from the outside world shall be sanitized using the Expr scanner, and each ASCII Data Type shall be scanned using a traditional algorithm to reduce the size of the code in the State Machine. Buffer overflows are detected using Script2 mechanisms defined in the SCRIPT Protocol.

## Interprocess Memory

Unused interprocess memory sockets shall be set to all zeros upon completion of the construction and initial population of the object before the Slot becomes visible to the outside world in order to not expose stack data.
