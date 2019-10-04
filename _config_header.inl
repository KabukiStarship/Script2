/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_config_header.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <_seams.inl>

#define SCRIPT2 0

#define YES_0 0
#define NO_0 1

#define STRING_TYPE_1 1
#define STRING_TYPE_2 2
#define STRING_TYPE_3 3

#define PLATFORM_BARE_METAL 1
#define PLATFORM_MBED_BARE_METAL 2
#define PLATFORM_MBED_OS 3
#define PLATFORM_ARDUINO 4
#define PLATFORM_WIN32 5
#define PLATFORM_WINDOWS 6
#define PLATFORM_ANDROID 7
#define PLATFORM_LINUX 8
#define PLATFORM_OSX 9
#define PLATFORM_IOS 10

#define CPU_X86 1
#define CPU_X64 2
#define CPU_ARM8 3
#define CPU_ARM16 4
#define CPU_ARM32 5
#define CPU_ARM64 6

#include <cstdint>
#if defined(_MSC_VER) && defined(_M_AMD64)
#define USING_VISUAL_CPP_X64 1
#include <intrin.h>
#include <intrin0.h>
#pragma intrinsic(_umul128)
#elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#define USING_GCC 1
#if defined(__x86_64__)
#define COMPILER_SUPPORTS_16_BYTE_INTEGERS 1
#endif
#endif
//#include <climits>
//#include <new>

#define ASSEMBLE_EXE 0
#define ASSEMBLE_LIB_STATIC 1
#define ASSEMBLE_LIB_DYNAMIC 1

#define ALU_64_BIT 0
#define ALU_32_BIT 1
#define ALU_16_BIT 2
#define CPU_8_BIT 3

#define CPU_ENDIAN_LITTLE 0

typedef char CH1;
typedef char16_t CH2;
typedef char32_t CH4;
typedef wchar_t CHN;

typedef int8_t SI1;
typedef uint8_t UI1;
typedef int16_t SI2;
typedef uint16_t UI2;
typedef bool BOL;
typedef int32_t SI4;
typedef uint32_t UI4;
typedef int32_t TM4;
typedef int64_t TM8;
typedef int64_t SI8;
typedef uint64_t UI8;

typedef UI2 FP2;
typedef float FP4;
typedef double FP8;

typedef uintptr_t UIW;
typedef intptr_t SIW;

typedef int SIN;
typedef unsigned int UIN;

typedef SI4 TM4;  //< A 32-bit seconds since epoch timestamp.
typedef SI8 TM8;  //< A 64-bit seconds since epoch timestamp.

typedef void* PTR;
typedef const void* PTC;

typedef UIW DTW;  //< Word-sized Ascii Data Type.
typedef UI1 DT1;  //< 8-bit Ascii Data Type.
typedef UI2 DT2;  //< 16-bit Ascii Data Type.
typedef UI4 DT4;  //< 32-bit Ascii Data Type.
typedef UI8 DT8;  //< 64-bit Ascii Data Type.

namespace _ {
/* ASCII C0 Control codes. */
enum {
  cNUL = 0,    //< ASCII C0 NUL 0
  cSOH,        //< ASCII C0 NUL 1
  cSTX,        //< ASCII C0 STX 2
  cETX,        //< ASCII C0 ETX 3
  cEOT,        //< ASCII C0 EOT 4
  cENQ,        //< ASCII C0 ENQ 5
  cACK,        //< ASCII C0 ACK 6
  cBEL,        //< ASCII C0 BEL 7
  cBS,         //< ASCII C0 BS 8
  cTAB,        //< ASCII C0 TAB 9
  cLF,         //< ASCII C0 LF 10
  cVT,         //< ASCII C0 VT 11
  cFF,         //< ASCII C0 FF 12
  cCR,         //< ASCII C0 CR 13
  cSO,         //< ASCII C0 SO 14
  cSI,         //< ASCII C0 SI 15
  cDLE,        //< ASCII C0 DLE 16
  cDC1,        //< ASCII C0 DC1 17
  cDC2,        //< ASCII C0 DC2 18
  cDC3,        //< ASCII C0 DC3 19
  cDC4,        //< ASCII C0 DC4 20
  cNAK,        //< ASCII C0 NAK 21
  cSYN,        //< ASCII C0 SYN 22
  cETB,        //< ASCII C0 ETB 23
  cCAN,        //< ASCII C0 CAN 24
  cEM,         //< ASCII C0 EM 25
  cSUB,        //< ASCII C0 SUB 26
  cESC,        //< ASCII C0 ESC 27
  cFS,         //< ASCII C0 FS 28
  cGS,         //< ASCII C0 GS 29
  cRS,         //< ASCII C0 RS 30
  cUS,         //< ASCII C0 US 31
  cDEL = 127,  //< ASCII C0 DEL 127
};

/* List of the 32 ASCII POD Data Types.
@link ./spec/data/readme.md */
enum {
  NIL = 0,
  cNIL = 0,  //< 00. Nil/void type or a BigNum (BGN) of 1 to 2047 bytes wide.
  cCH1,      //< 01. 1-byte character.
  cSI1,      //< 02. 1-byte signed integer.
  cUI1,      //< 03. 1-byte unsigned integer.
  cCH2,      //< 04. 2-byte character.
  cSI2,      //< 05. 2-byte signed integer.
  cUI2,      //< 06. 2-byte unsigned integer.
  cFP2,      //< 07. 2-byte floating-point number.
  cBOL,      //< 08. 2 or 4-byte boolean value.
  cCH4,      //< 09. 4-byte character.
  cSI4,      //< 10. 4-byte signed integer.
  cUI4,      //< 11. 4-byte unsigned integer.
  cFP4,      //< 12. 4-byte floating-point number.
  cTME,      //< 13. 8-byte sub-second timestamp with TM4 and an UI4 tick.
  cSI8,      //< 14. 8-byte signed integer.
  cUI8,      //< 15. 8-byte unsigned integer.
  cFP8,      //< 16. 8-byte floating-point number.
  cSIH,      //< 17. 16-byte (Hexadeca-byte) signed integer.
  cUIH,      //< 18. 16-byte (Hexadeca-byte) unsigned integer.
  cFPH,      //< 19. 16-byte (Hexadeca-byte) floating-point number.
  cDTA,      //< 20 Implementation-defined word-aligned Data Type A.
  cDTB,      //< 21 Implementation-defined word-aligned Data Type B.
  cDTC,      //< 22 Implementation-defined word-aligned Data Type C.
  cDTD,      //< 23 Implementation-defined word-aligned Data Type D.
  cDTE,      //< 24 Implementation-defined word-aligned Data Type E.
  cDTF,      //< 25 Implementation-defined word-aligned Data Type F.
  cDTG,      //< 26 Implementation-defined word-aligned Data Type G.
  cDTH,      //< 27 Implementation-defined word-aligned Data Type H.
  cDTI,      //< 28 Implementation-defined word-aligned Data Type I.
  cDTJ,      //< 29 Implementation-defined word-aligned Data Type J.
  cDTK,      //< 30 Implementation-defined word-aligned Data Type K.
  cDTL,      //< 31 Implementation-defined word-aligned Data Type L.
};

enum {
  cSTA = 1,   //< 01. Nil-terminated string Type 1 (UTF-8).
  cSTB,       //< 02. Nil-terminated string Type 2 (UTF-16).
  cSTC,       //< 03. Nil-terminated string Type 3 (UTF-32).
  cWLD = 26,  //< 26. A pointer.
  cVAL,       //< 27. A 2-word value.
  cTVT,       //< 28. A Type-Value tuple.
  cBGV,       //< 29. A 2-word value.
  cTBT,       //< 30. A Type-BigVal tuple.
  cTST,       //< 31. A Type-String tuple.
};

enum {
  cPTR = 1 << 14,          //< 64. Pointer modifier.
  cCNS = 1 << 15,          //< 128. Constant.
  cCNS_PTR = cCNS | cPTR,  //< 128. Constant Pointer.
  cCNS_STA = cCNS | cCH1,  //< 133. Constant CH1*.
  cCNS_STB = cCNS | cCH2,  //< 134. Constant CH2*.
  cCNS_STC = cCNS | cCH4,  //< 135. Constant CH4*.
};

enum {
  cRS1 = 97,  //< 97. A type-value tuple list with 2-byte signed size_bytes.
  cRS2 = 98,  //< 98. A type-value tuple list with 4-byte signed size_bytes.
  cRS4 = 99,  //< 99. A type-value tuple list with 8-byte signed size_bytes.
  cINV = 64,  //< The number of Ascii Data Type base types.
  cTypePODBitCount = 5,   //< Bit
  cTypeCount = 32,        //< The starting index of invalid types.
  cTypePODMask = 32 - 1,  //< The starting index of invalid types.
};

enum {
  cSW1 = 0,  //< 0. Class or POD type.
  cSW2 = 1,  //< 1. size_width of size_bytes is 16-bits wide.
  cSW4 = 2,  //< 2. size_width of size_bytes is 32-bits wide.
  cSW8 = 3,  //< 3. size_width of size_bytes is 64-bits wide.
};

enum {
  cPOD = 0,  //< A POD type.
  cARY = 1,  //< Array of POD types.
  cVEC = 2,  //< Vector of POD types.
  cMAT = 3,  //< Matrix of POD types.
};

enum {
  cLST = 48,  //< ASCII List type.
};

enum {
  cWordBitCount = (sizeof(void*) == 2)
                      ? 1
                      : (sizeof(void*) == 4) ? 2 : (sizeof(void*) == 8) ? 3 : 0,
  cWordLSbMask = sizeof(void*) - 1,
  cNaNInt = sizeof(SI4) == 4 ? static_cast<SI4>(0xFFFFFFFF)
                             : sizeof(SI4) == 2 ? static_cast<SI4>(0xFFFF) : 0,
  cSuccess = 0,    //< Universal successful return value.
  cAnywhere = -1,  //< Flag to place an item anywhere in a collection.
  cPush = -2,      //< Flag to place an item on the top of a stack.
};

enum {
  cErrorUnspecified = 1,      //< Script2 Error  1: Unspecified.
  cErrorNilInput,             //< Script2 Error  2: Nil input.
  cErrorInputTooLow,          //< Script2 Error  3: Input too low.
  cErrorInputTooHigh,         //< Script2 Error  4: Input too high.
  cErrorBufferOverflow,       //< Script2 Error  5: Buffer overflow.
  cErrorBufferUnderflow,      //< Script2 Error  6: Buffer underflow.
  cErrorVarintOverflow,       //< Script2 Error  7: Varint overflow.
  cErrorInvalidHash,          //< Script2 Error  8: Invalid hash.
  cErrorInvalidType,          //< Script2 Error  9: Invalid type.
  cErrorInvalidIndex,         //< Script2 Error 10: Invalid index.
  cErrorInvalidEnquery,       //< Script2 Error 11: Invalid inquiry.
  cErrorInvalidArgument,      //< Script2 Error 12: Invalid argument.
  cErrorInvalidDoor,          //< Script2 Error 13: Invalid door.
  cErrorTooManyParameters,    //< Script2 Error 14: Too many parameters.
  cErrorStackOverflow,        //< Script2 Error 15: Stack overflow.
  cErrorTooManyPops,          //< Script2 Error 16: Too many pops.
  cErrorTextOverflow,         //< Script2 Error 17: Text overflow.
  cErrorInvalidErrorHandler,  //< Script2 Error 18: Invalid error handler.
  cErrorInvalidOperand,       //< Script2 Error 19: Invalid operand.
  cErrorArrayOverflow,        //< Script2 Error 20: Array overflow.
  cErrorInvalidOp,            //< Script2 Error 21: Invalid op.
  cErrorMalformedUTF8,        //< Script2 Error 22: Malformed UTF-8.
  cErrorMalformedUTF16,       //< Script2 Error 23: Malformed UTF-16.
  cErrorMalformedUTF32,       //< Script2 Error 24: Malformed UTF-32.
  cErrorObjLocked,            //< Script2 Error 25: AArray locked.
  cErrorInvalidArgs,          //< Script2 Error 26: Invalid args.
  cErrorAuthenticationError,  //< Script2 Error 27: Authentication error.
  cErrorRoomNotFound,         //< Script2 Error 28: Room not found.
  cErrorImplementation,       //< Script2 Error 29: Implementation error.
};
}  // namespace _
