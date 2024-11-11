// Copyright Kabuki Starship� <kabukistarship.com>.

#define ASSEMBLY_TYPE ASSEMBLE_EXE 1
#define SCRIPT2_RUN_TESTS YES_0

#define CPU_SIZE CPU_8_BYTE
#define CPU_ENDIAN CPU_ENDIAN_LITTLE

#define USING_CONSOLE YES_0

#define USING_UTF8 YES_0
#define USING_UTF16 YES_0
#define USING_UTF32 YES_0
#define DEFAULT_INT_SIZE ATYPE_32BIT

#define LARGEST_CHAR STRING_TYPE_A
#define USING_STR STRING_TYPE_A
#define USING_LOM _ARC_CHA

#define USING_FP 8
#define USING_FPC YES_0
#define USING_FPD YES_0

#define USING_16_BYTE_POD_TYPES NO_0

#define BOL_SIZE 4 //< Size of boolean in bytes.

// Last 128-bit custom type; to disable define as 19 (ASCII BOL).
#define CT5_STOP 19

// Last 64-bit custom type; to disable define as CT5_STOP.
#define CT4_STOP CT5_STOP

// Last 32-bit custom type; to disable define as CT4_STOP.
#define CT3_STOP CT4_STOP

// Last 16-bit custom type; to disable define as CT3_STOP.
#define CT2_STOP CT3_STOP
