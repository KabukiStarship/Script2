// Copyright Kabuki Starship� <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_ERROR_DECL
#define SCRIPT2_ERROR_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_CORE
namespace _ {

// @see _ConfigHeader.hxx for enum of error codes.

/* A CHA[32][32] containing the CrabsError error strings.
Example:
const CHA* error_string = STRErrors()[error_code * 32]; */
LIB_MEMBER const CHA* CrabsError0STA();

/* Returns one of the STRErrors() CrabsError Strings. */
inline const CHA* CrabsErrorSTR(ISA error);
inline const CHA* CrabsErrorSTR(ISB error);
inline const CHA* CrabsErrorSTR(ISC error);
inline const CHA* CrabsErrorSTR(ISD error);

inline BOL AIsError(const void* result);

}  //< namespace _
#endif
#endif
