/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_ConfigFooter.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// The below macros can be override in the _Config.h file.

#ifndef SEAM
#define SEAM SCRIPT2_LIST
#endif
#if SCRIPT2_MAX_PARAMS < 0
#error MAX_ERRORS must be greater than 0
#endif
#ifndef SCRIPT2_MAX_WALLS
#define SCRIPT2_MAX_WALLS 65535
#endif
#ifndef SCRIPT2_MAX_ERRORS
#define SCRIPT2_MAX_ERRORS 65535
#endif
#ifndef SCRIPT2_MAX_PARAMS
#define SCRIPT2_MAX_PARAMS 65535
#endif
#ifndef SCRIPT2_COM_TIMEOUT_TICKS
#define SCRIPT2_COM_TIMEOUT_TICKS 65535
#else
#if SCRIPT2_COM_TIMEOUT_TICKS < 0
#error MAX_ERRORS must be greater than 0!
#endif
#endif
#ifndef SCRIPT2_MAX_ADDRESS_LENGTH
#define SCRIPT2_MAX_ADDRESS_LENGTH 65535
#endif
#ifndef SCRIPT2_OP_MAX_NAME_LENGTH
#define SCRIPT2_OP_MAX_NAME_LENGTH 65535
#endif
#ifndef SCRIPT2_OP_MAX_DECRABSION_LENGTH
#define SCRIPT2_OP_MAX_DECRABSION_LENGTH 65535
#endif
#ifndef SCRIPT2_TEXT_LENGTH
#define SCRIPT2_TEXT_LENGTH 65535
#endif
#ifndef SCRIPT2_BUFFER_SIZE_RX
#define SCRIPT2_BUFFER_SIZE_RX 65535
#endif
#ifndef SCRIPT2_BUFFER_SIZE_TX
#define SCRIPT2_BUFFER_SIZE_TX 65535
#endif
#ifndef SCRIPT2_WINDOW_SIZE_MIN
#define SCRIPT2_WINDOW_SIZE_MIN 512
#endif
#ifndef SCRIPT2_CPU_CACHE_LINE_SIZE
#define SCRIPT2_CPU_CACHE_LINE_SIZE 64
#endif
#ifndef SCRIPT2_BUFFER_COUNT_DEFAULT
#define SCRIPT2_BUFFER_COUNT_DEFAULT 1024
#else
#if SCRIPT2_BUFFER_COUNT_DEFAULT < 1
#define SCRIPT2_BUFFER_COUNT_DEFAULT 512
#endif
#endif
#ifndef SCRIPT2_STACK_COUNT_MAX_DEFAULT
#define SCRIPT2_STACK_COUNT_MAX_DEFAULT 32
#endif
#ifndef SCRIPT2_FLOOR_SIZE
#define SCRIPT2_FLOOR_SIZE 1024
#endif
#ifndef SCRIPT2_STACK_COUNT_MAX_DEFAULT
#define SCRIPT2_STACK_COUNT_MAX_DEFAULT 16
#endif
#ifndef SCRIPT2_OBJ_SIZE_DEFAULT
#define SCRIPT2_OBJ_SIZE_DEFAULT 256
#endif
#ifndef SCRIPT2_TOKEN_COUNT
#define SCRIPT2_TOKEN_COUNT 32
#endif
#ifndef SCRIPT2_STRING_COUNT_DEFAULT
#define SCRIPT2_STRING_COUNT_DEFAULT 28
#endif
#ifndef SCRIPT2_CIN_BUFFER_SIZE
#define SCRIPT2_CIN_BUFFER_SIZE 81
#endif
#ifndef SCRIPT2_UNICODE_VERSION_MAJOR
#define SCRIPT2_UNICODE_VERSION_MAJOR 12
#endif
#ifndef SCRIPT2_UNICODE_VERSION_MINOR
#define SCRIPT2_UNICODE_VERSION_MINOR 1
#endif
#ifndef SCRIPT2_UNICODE_ASSIGNED_CODE_POINTS
#define SCRIPT2_UNICODE_ASSIGNED_CODE_POINTS 277576
#endif
#ifndef SCRIPT2_CONSOLE_WIDTH
#define SCRIPT2_CONSOLE_WIDTH 80
#endif
#ifndef SCRIPT2_DTA_WIDTH
#define SCRIPT2_DTA_WIDTH 0
#endif
#ifndef CLOCK_EPOCH_YEAR  
#define CLOCK_EPOCH_YEAR 1970
#endif
#ifndef SLOT_SIZE_MIN
#define SLOT_SIZE_MIN SCRIPT2_CPU_CACHE_LINE_SIZE
#endif

// End overridable `_Config.h` parameters.
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#ifdef ASSEMBLE_LIBRARY
#ifdef LIB_EXPORT == YES_0
#define LIB_MEMBER __declspec(dllexport)
#else
#define LIB_MEMBER __declspec(dllimport)
#endif
#else
#define LIB_MEMBER
#endif

#if SCRIPT2_PLATFORM == OS_WINDOWS
#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 1
#else
#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 1
#endif

#if USING_16_BYTE_POD_TYPES == YES_0
typedef int128_t ISE;
typedef uint128_t IUE;
#endif

#if SEAM < SCRIPT2_CORE
#undef USING_UTF16
#undef USING_UTF32
#define USING_UTF16 NO_0
#define USING_UTF32 NO_0
#endif

#if SEAM < SCRIPT2_FTOS
#undef USING_FPC
#undef USING_FPD
#define USING_FPC NO_0
#define USING_FPD NO_0
#endif

#if USING_FP == 4
typedef FPC FPW;
#elif USING_FP == 8
typedef FPD FPW;
#endif

#if ALU_SIZE == ALU_16_BIT
#define CPU_IS_LESS_THAN_32_BIT 1
#define CPU_IS_LESS_THAN_64_BIT 1
#define CPU_IS_GREATER_THAN_16_BIT 0
#define CPU_IS_GREATER_THAN_32_BIT 0
#elif ALU_SIZE == ALU_32_BIT
#define CPU_IS_LESS_THAN_32_BIT 0
#define CPU_IS_LESS_THAN_64_BIT 1
#define CPU_IS_GREATER_THAN_16_BIT 1
#define CPU_IS_GREATER_THAN_32_BIT 0
#elif ALU_SIZE == ALU_64_BIT
#define CPU_IS_LESS_THAN_32_BIT 0
#define CPU_IS_LESS_THAN_64_BIT 0
#define CPU_IS_GREATER_THAN_16_BIT 1
#define CPU_IS_GREATER_THAN_32_BIT 1
#endif

namespace _ {
// Default character type.
#if USING_STR == STRING_TYPE_A
typedef CHA CHR;
typedef CHA* STR;
enum {
  // Default String type is UTF-8.
  cSTR = (cARY << (TypePODBitCount - 1)) | cCHA,
};
#elif USING_STR == STRING_TYPE_B
typedef CHB CHR;
typedef CHB* STR;
enum {
  // Default String type is UTF-8.
  cSTR = (cARY << (cTypePODBitCount - 1)) | cCHB,
};
#elif USING_STR == STRING_TYPE_C
typedef CHC CHR;
typedef CHC* STR;
enum {
  // Default String type is UTF-8.
  cSTR = (cARY << (cTypePODBitCount - 1)) | cCHC,
};
#else
#error Invalid string type.
#endif
enum {
  // Address type, which is the same as the default string type for the system.
  cADR = cSTR,
};

//< The Largest char.
#if LARGEST_CHAR == STRING_TYPE_B
#if USING_UTF16 == YES_0
typedef CHB CHL;
#else
#error You must set the LARGEST_CHAR to  STRING_TYPE_A.
#endif
#elif LARGEST_CHAR == STRING_TYPE_C
#if USING_UTF32 == YES_0
typedef CHC CHL;
#else
#error You must set the LARGEST_CHAR to  STRING_TYPE_A or STRING_TYPE_B.
#endif
#else
typedef CHA CHL;
#endif

#if ALU_SIZE == ALU_64_BIT
typedef ISB ISM;  //< Half of ISN type
typedef IUB UIL;  //< Half of IUN type
#if COMPILER_SUPPORTS_16_BYTE_INTEGERS
#define LARGEST_POD_TYPE 16
#else
#define LARGEST_POD_TYPE 8
#endif
#elif ALU_SIZE == ALU_32_BIT
typedef ISB ISM;  //< Half of ISN type
typedef IUB UIL;  //< Half of IUN type
#define LARGEST_POD_TYPE 8
#elif ALU_SIZE == ALU_16_BIT
typedef ISA ISM;  //< Half of ISN type
typedef IUA UIL;  //< Half of IUN type
#else
#define LARGEST_POD_TYPE 4
#endif

#define PRIME_LARGEST_IUB 65521
#define PRIME_LARGEST_UI4 4294967291
#define PRIME_LARGEST_UI8 18446744073709551557

#define SIZEOF_ARRAY(type) ((CHA*)(&type + 1) - (CHA*)(&type))

enum {
  cSlotSizeMin = SLOT_SIZE_MIN,        //< Min size of a Slot.
  cClockEpochInit = CLOCK_EPOCH_YEAR,  //< Timestamp epoch year, default: 1970.
  cCpuCacheLineSize = SCRIPT2_CPU_CACHE_LINE_SIZE,
  cMaxFloorsCount = SCRIPT2_MAX_WALLS, //< Size of the Room Floor (socket).
  cMaxErrors = SCRIPT2_MAX_ERRORS,     //< Max errors before blowing up.
  cParamsMax = SCRIPT2_MAX_PARAMS,     //< Max number_ of parameters.
  cTimeoutMicroseconds = SCRIPT2_COM_TIMEOUT_TICKS,  //< Sub-second ticks.
  cAddressLengthMax =
      SCRIPT2_MAX_ADDRESS_LENGTH,  //< Max address (cADR) length.
  cOpNameLengthMax = SCRIPT2_OP_MAX_NAME_LENGTH,
  // Max length of a Op description .
  cOpDescriptionLengthMax = SCRIPT2_OP_MAX_DECRABSION_LENGTH,
  // Max length of a Text.
  cCharCount = SCRIPT2_TEXT_LENGTH,

  // Size of the Display Print Slot.
  cSlotBufferSizeRx = SCRIPT2_BUFFER_SIZE_RX,

  // Size of the KeyboardInBuffer.
  cSlotBufferSizeTx = SCRIPT2_BUFFER_SIZE_TX,

  cWindowSizeMin = SCRIPT2_WINDOW_SIZE_MIN,

  cBufferSizeDefault = SCRIPT2_BUFFER_COUNT_DEFAULT,
  cFloorSize = SCRIPT2_FLOOR_SIZE,  //< Size, or initial size, of the Floor.
  cStackCountMaxDefault = SCRIPT2_STACK_COUNT_MAX_DEFAULT,
  cObjSizeDefault = SCRIPT2_OBJ_SIZE_DEFAULT,

  // Extra reserved memory at the stop of BOut.
  cBOutOverflowSize = 32,

  cPrintC0Offset = 176,  //< Value add to values 0-32 when printing.
  cTokenLongest = 31,    //< Max length of a token plus one.
  cMinStaccSize = 1,     //< Min Crabs stack size.
  cBufferSizeDefaultWords =
      cBufferSizeDefault / sizeof(ISW) + cBufferSizeDefault % sizeof(ISW) ? 1
                                                                          : 0,
  cSTRCount = SCRIPT2_STRING_COUNT_DEFAULT,
  cConsoleWidth = SCRIPT2_CONSOLE_WIDTH,
  cCInBufferSize =
      SCRIPT2_CIN_BUFFER_SIZE,         //< Preallocated CIn buffer char count.
  cKeyEnter = 0,                       //< The keyboard value for enter.
  cLargestPODType = LARGEST_POD_TYPE,  //< The largest POD type.
};

}  //< namespace _

#undef MAX_ERRORS
#undef MAX_NUM_PARAMS
#undef MAX_STRING_LENGTH
#undef COM_TIMEOUT_TICKS
#undef SCRIPT2_LOG_SIZE
#undef OPERATION_MAX_NAME_LENGTH
#undef OPERATION_MAX_DECRABSION_LENGTH
#undef SCRIPT2_TEXT_LENGTH
#undef SCRIPT2_BUFFER_SIZE_RX
#undef SCRIPT2_BUFFER_SIZE_TX
#undef SCRIPT2_WINDOW_SIZE_MIN
#undef SCRIPT2_BUFFER_COUNT_DEFAULT
#undef SCRIPT2_STACK_COUNT_MAX_DEFAULT
#undef SCRIPT2_FLOOR_SIZE
#undef SCRIPT2_STACK_COUNT_MAX_DEFAULT
#undef SCRIPT2_OBJ_SIZE_DEFAULT
#undef SCRIPT2_TOKEN_COUNT
#undef SCRIPT2_CPU_CACHE_LINE_SIZE
#undef SCRIPT2_STRING_COUNT_DEFAULT
