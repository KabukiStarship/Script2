// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_ERROR_DECL
#define CRABS_ERROR_DECL 1
#include <_Config.h>
#if SEAM >= CRABS_CORE
namespace _ {

// @see _ConfigHeader.hxx for enum of error codes.

/* A CHA[32][32] containing the ASCIIError error strings.
Example:
const CHA* error_string = STRErrors()[error_code * 32]; */
LIB_MEMBER const CHA* ASCIIErrorSTA();

/* Returns one of the STRErrors() ASCIIError Strings. */
inline const CHA* ASCIIErrorSTR(ISA error);
inline const CHA* ASCIIErrorSTR(ISB error);
inline const CHA* ASCIIErrorSTR(ISC error);
inline const CHA* ASCIIErrorSTR(ISD error);

inline BOL AIsError(const void* result);

}  //< namespace _
#endif
#endif
