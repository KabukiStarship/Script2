/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_ConfigFooter.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */

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

#if SEAM < SCRIPT2_COUT
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

#if CPU_SIZE == CPU_2_BYTE
#define CPU_IS_LESS_THAN_32_BIT 1
#define CPU_IS_LESS_THAN_64_BIT 1
#define CPU_IS_GREATER_THAN_16_BIT 0
#define CPU_IS_GREATER_THAN_32_BIT 0
#elif CPU_SIZE == CPU_4_BYTE
#define CPU_IS_LESS_THAN_32_BIT 0
#define CPU_IS_LESS_THAN_64_BIT 1
#define CPU_IS_GREATER_THAN_16_BIT 1
#define CPU_IS_GREATER_THAN_32_BIT 0
#elif CPU_SIZE == CPU_8_BYTE
#define CPU_IS_LESS_THAN_32_BIT 0
#define CPU_IS_LESS_THAN_64_BIT 0
#define CPU_IS_GREATER_THAN_16_BIT 1
#define CPU_IS_GREATER_THAN_32_BIT 1
#endif

#if USING_STR == STRING_TYPE_A
typedef CHA CHR;
typedef CHA* STR;
#elif USING_STR == STRING_TYPE_B
typedef CHB CHR;
typedef CHB* STR;
#else
typedef CHC CHR;
typedef CHC* STR;
#endif
namespace _ {
// Default character type.
#if USING_STR == STRING_TYPE_A
enum {
  // Default String type is UTF-8.
  STR_ = (_ARY << (ATypePODBitCount - 1)) | _CHA,
};
#elif USING_STR == STRING_TYPE_B
enum {
  // Default String type is UTF-8.
  STR_ = (_ARY << (cTypePODBitCount - 1)) | _CHB,
};
#elif USING_STR == STRING_TYPE_C
enum {
  // Default String type is UTF-8.
  STR_ = (_ARY << (cTypePODBitCount - 1)) | _CHC,
};
#else
#error Invalid string type.
#endif
enum {
  // Address type, which is the same as the default string type for the system.
  cADR = STR_,
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

#if CPU_SIZE == CPU_8_BYTE
typedef ISB ISM;  //< Half of ISN type
typedef IUB UIL;  //< Half of IUN type
#if COMPILER_SUPPORTS_16_BYTE_INTEGERS
#define LARGEST_POD_TYPE 16
#else
#define LARGEST_POD_TYPE 8
#endif
#elif CPU_SIZE == CPU_4_BYTE
typedef ISB ISM;  //< Half of ISN type
typedef IUB UIL;  //< Half of IUN type
#define LARGEST_POD_TYPE 8
#elif CPU_SIZE == CPU_2_BYTE
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
  CRSlotSizeMin = SLOT_SIZE_MIN,        //< Min size of a Slot.
  AClockEpochInit = CLOCK_EPOCH_YEAR,   //< Timestamp epoch year, default: 1970.
  ACPUCacheLineSize = SCRIPT2_CPU_CACHE_LINE_SIZE,    //< CPU Cache line size.
  CRMaxFloorsCount = SCRIPT2_MAX_WALLS, //< Size of the Room Floor (socket).
  CRErrorCountMax = SCRIPT2_MAX_ERRORS, //< Max errors before blowing up.
  CRParamCountMax = SCRIPT2_MAX_PARAMS, //< Max number_ of parameters.
  CRTimeoutMicroseconds = SCRIPT2_COM_TIMEOUT_TICKS,  //< Sub-second ticks.
  CRAddressLengthMax =
      SCRIPT2_MAX_ADDRESS_LENGTH,  //< Max address (cADR) length.
  CROpNameLengthMax = SCRIPT2_OP_MAX_NAME_LENGTH,
  // Max length of a Op description .
  CrabsOpDescriptionLengthMax = SCRIPT2_OP_MAX_DECRABSION_LENGTH,
  // Max length of a Text.
  ACharCount = SCRIPT2_TEXT_LENGTH,

  // Size of the Display Print Slot.
  ASlotBufferSizeRx = SCRIPT2_BUFFER_SIZE_RX,

  // Size of the KeyboardInBuffer.
  ASlotBufferSizeTx = SCRIPT2_BUFFER_SIZE_TX,

  AWindowSizeMin = SCRIPT2_WINDOW_SIZE_MIN,

  ABufferSizeDefault = SCRIPT2_BUFFER_COUNT_DEFAULT,
  AFloorSize = SCRIPT2_FLOOR_SIZE,  //< Size, or initial size, of the Floor.
  AStackCountMaxDefault = SCRIPT2_STACK_COUNT_MAX_DEFAULT,
  AObjSizeDefault = SCRIPT2_OBJ_SIZE_DEFAULT,

  // Extra reserved memory at the stop of BOut.
  ABOutOverflowSize = 32,

  APrintC0Offset = 176,  //< Value add to values 0-32 when printing.
  ATokenLongest  = 31,   //< Max length of a token plus one.
  AMinStackSize  = 1,    //< Min Crabs stack size.
  ABufferSizeDefaultWords =
      ABufferSizeDefault / sizeof(ISW) + ABufferSizeDefault % sizeof(ISW) ? 1
                                                                          : 0,
  ASTRCount = SCRIPT2_STRING_COUNT_DEFAULT,
  AConsoleWidth = SCRIPT2_CONSOLE_WIDTH,
  CInBufferSize =
      SCRIPT2_CIN_BUFFER_SIZE,         //< Preallocated CIn buffer char count.
  AKeyEnter = 0,                       //< The keyboard value for enter.
  ATypeLargestPOD = LARGEST_POD_TYPE,  //< The largest POD type.
};


enum {
  BOLSizeBits = BOL_SIZE_BITS,
  DTASize = DTA_SIZE,
  DTBSize = DTB_SIZE,
  DTCSize = DTC_SIZE,
  DTDSize = DTD_SIZE,
  DTESize = DTE_SIZE,
  DTFSize = DTF_SIZE,
  DTGSize = DTG_SIZE,
  DTHSize = DTH_SIZE,
  DTISize = DTI_SIZE,
  DTJSize = DTJ_SIZE,
  DTKSize = DTK_SIZE,
  DTLSize = DTL_SIZE,

  BOLAlignMask = BOL_ALIGN_MASK,
  DTAAlignMask = DTA_ALIGN_MASK,
  DTBAlignMask = DTB_ALIGN_MASK,
  DTCAlignMask = DTC_ALIGN_MASK,
  DTDAlignMask = DTD_ALIGN_MASK,
  DTEAlignMask = DTE_ALIGN_MASK,
  DTFAlignMask = DTF_ALIGN_MASK,
  DTGAlignMask = DTG_ALIGN_MASK,
  DTHAlignMask = DTH_ALIGN_MASK,
  DTIAlignMask = DTI_ALIGN_MASK,
  DTJAlignMask = DTJ_ALIGN_MASK,
  DTKAlignMask = DTK_ALIGN_MASK,
  DTLAlignMask = DTL_ALIGN_MASK,
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
