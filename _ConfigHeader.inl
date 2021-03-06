/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_ConfigHeader.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_Seams.inl>

#define SCRIPT2 0

#define YES_0 0
#define NO_0 1

#define STRING_TYPE_A 1  //< UTF-8
#define STRING_TYPE_B 2  //< UTF-16
#define STRING_TYPE_C 3  //< UTF-32
#define StringTypeD   4  //< MSB-variant encoding.

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

typedef char CHA;
typedef char16_t CHB;
typedef char32_t CHC;
typedef wchar_t CHN;

typedef int8_t ISA;
typedef uint8_t IUA;
typedef int16_t ISB;
typedef uint16_t IUB;
typedef bool BOL;
typedef int32_t ISC;
typedef uint32_t IUC;
typedef int32_t TMC;
typedef int64_t TMD;
typedef int64_t ISD;
typedef uint64_t IUD;

typedef IUA DTA;
typedef IUB DTB;
typedef IUC DTC;
typedef IUD DTD;

typedef IUB FPB;
typedef float FPC;
typedef double FPD;

typedef uintptr_t IUW;
typedef intptr_t ISW;

typedef int ISN;
typedef unsigned int IUN;

typedef ISC TM4;  //< A 32-bit seconds since epoch timestamp.
typedef ISD TM8;  //< A 64-bit seconds since epoch timestamp.

typedef void* PTR;
typedef const void* PTC;

typedef IUW DTW;  //< Word-sized Ascii Data Type.
typedef IUA DT1;  //< 8-bit Ascii Data Type.
typedef IUB DT2;  //< 16-bit Ascii Data Type.
typedef IUC DT4;  //< 32-bit Ascii Data Type.
typedef IUD DT8;  //< 64-bit Ascii Data Type.

typedef ISN Error; //< An error code.

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
  cSI,         //< ASCII C0 IS 15
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
  NIL = 0,   //< 00. Nil/void.
  cNIL = 0,  //< 00. Nil/void.
  cCHA,      //< 01. 1-byte character.
  cISA,      //< 02. 1-byte signed integer.
  cIUA,      //< 03. 1-byte unsigned integer.
  cCHB,      //< 04. 2-byte character.
  cISB,      //< 05. 2-byte signed integer.
  cIUB,      //< 06. 2-byte unsigned integer.
  cFPB,      //< 07. 2-byte floating-point number.
  cBOL,      //< 08. 2 or 4-byte boolean value.
  cCHC,      //< 09. 4-byte character.
  cISC,      //< 10. 4-byte signed integer.
  cIUC,      //< 11. 4-byte unsigned integer.
  cFPC,      //< 12. 4-byte floating-point number.
  cTME,      //< 13. 8-byte sub-second timestamp with TM4 and an IUC tick.
  cISD,      //< 14. 8-byte signed integer.
  cIUD,      //< 15. 8-byte unsigned integer.
  cFPD,      //< 16. 8-byte floating-point number.
  cISE,      //< 17. 16-byte (Hexadeca-byte) signed integer.
  cIUE,      //< 18. 16-byte (Hexadeca-byte) unsigned integer.
  cFPE,      //< 19. 16-byte (Hexadeca-byte) floating-point number.
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
  cSTA = 1,  //< 01. Nil-terminated string Type 1 (UTF-8).
  cSTB,      //< 02. Nil-terminated string Type 2 (UTF-16).
  cSTC,      //< 03. Nil-terminated string Type 3 (UTF-32).
  cWLD = 26, //< 26. A pointer.
  cVAL,      //< 27. A 2-word value.
  cTVT,      //< 28. A Type-Value tuple.
  cBGV,      //< 29. A 2-word value.
  cTBT,      //< 30. A Type-BigVal tuple.
  cTST,      //< 31. A Type-String tuple.
};

enum {
  cPTR = 1 << 14,          //< 64.  Pointer modifier.
  cCNS = 1 << 15,          //< 128. Constant.
  cCNS_PTR = cCNS | cPTR,  //< 128. Constant Pointer.
  cCNS_STA = cCNS | cCHA,  //< 133. Constant CHA*.
  cCNS_STB = cCNS | cCHB,  //< 134. Constant CHB*.
  cCNS_STC = cCNS | cCHC,  //< 135. Constant CHC*.
};

enum {
  cRS1 = 97,  //< 97. A type-value tuple list with 2-byte signed size_bytes.
  cRS2 = 98,  //< 98. A type-value tuple list with 4-byte signed size_bytes.
  cRS4 = 99,  //< 99. A type-value tuple list with 8-byte signed size_bytes.
  cINV = 64,  //< The number of Ascii Data Type base types.
  cTypePODBitCount = 5,           //< Bit
  cTypeCount = 32,                //< The starting index of invalid types.
  cTypePODMask = cTypeCount - 1,  //< The starting index of invalid types.
};

enum {
  cSW1 = 0,  //< 0. Class or POD type.
  cSW2 = 1,  //< 1. size_width of size_bytes is 16-bits wide.
  cSW4 = 2,  //< 2. size_width of size_bytes is 32-bits wide.
  cSW8 = 3,  //< 3. size_width of size_bytes is 64-bits wide.
};

enum {
  cPOD = 0,   //< A POD type.
  cARY = 1,   //< Array of POD types.
  cVEC = 2,   //< Vector of POD types.
  cMAT = 3,   //< Matrix of POD types.
  cLST = 48,  //< ASCII List type.
};

enum {
  cWordBitCount = (sizeof(void*) == 2)
                      ? 1
                      : (sizeof(void*) == 4) ? 2 : (sizeof(void*) == 8) ? 3 : 0,
  cWordLSbMask = sizeof(void*) - 1,
  cNaNInt = sizeof(ISC) == 4 ? static_cast<ISC>(0xFFFFFFFF)
                             : sizeof(ISC) == 2 ? static_cast<ISC>(0xFFFF) : 0,
  cExit = -1,      //< Flag to exit the Room.
  cSuccess = 0,    //< Universal successful return value.
  cAnywhere = -1,  //< Flag to place an item anywhere in a collection.
  cPush = -2,      //< Flag to place an item on the top of a stack.
};

enum {
  cErrorInputInvalid = -1,          //< Script2  1: Input invalid.
  cErrorInputNil = -2,              //< Script2  2: Input nil.
  cErrorInvalidHash = -3,           //< Script2  3: Invalid hash.
  cErrorInvalidType = -4,           //< Script2  4: Invalid type.
  cErrorInvalidIndex = -5,          //< Script2  5: Invalid index.
  cErrorInvalidEnquery = -6,        //< Script2  6: Invalid inquiry.
  cErrorInvalidArgument = -7,       //< Script2  7: Invalid argument.
  cErrorInvalidDoor = -8,           //< Script2  8: Invalid door.
  cErrorInvalidErrorHandler = -9,   //< Script2  9: Invalid error handler.
  cErrorInvalidOperand = -10,       //< Script2 10: Invalid operand.
  cErrorInvalidOp = -11,            //< Script2 11: Invalid op.
  cErrorInvalidArgs = -12,          //< Script2 12: Invalid args.
  cErrorTooManyParameters = -13,    //< Script2 13: Too many parameters.
  cErrorTooManyPops = -14,          //< Script2 14: Too many pops.
  cErrorStackOverflow = -15,        //< Script2 15: Buffer overflow.
  cErrorVarintOverflow = -16,       //< Script2 16: Varint overflow.
  cErrorTextOverflow = -17,         //< Script2 17: Text overflow.
  cErrorArrayOverflow = -18,        //< Script2 18: Array overflow.
  cErrorBufferOverflow = -19,       //< Script2 19: Buffer overflow.
  cErrorBufferUnderflow = -20,      //< Script2 20: Buffer underflow.
  cErrorMalformedUTF8 = -21,        //< Script2 21: Malformed UTF-8.
  cErrorMalformedUTF16 = -22,       //< Script2 22: Malformed UTF-16.
  cErrorMalformedUTF32 = -23,       //< Script2 23: Malformed UTF-32.
  cErrorObjLocked = -24,            //< Script2 24: AArray locked.
  cErrorAuthenticationError = -25,  //< Script2 25: Authentication error.
  cErrorRoomNotFound = -26,         //< Script2 26: Room not found.
  cErrorImplementation = -27,       //< Script2 27: Implementation error.
};
}  // namespace _
