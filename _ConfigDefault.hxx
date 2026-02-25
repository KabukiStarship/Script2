// Copyright AStarship <https://astarship.net>.

#define ASSEMBLY_TYPE ASSEMBLE_EXE 1
#define CRABS_RUN_TESTS YES_0

#define USING_CRABS_1_BYTE_TYPES
#define USING_CRABS_2_BYTE_TYPES
#define USING_CRABS_4_BYTE_TYPES
#define USING_CRABS_8_BYTE_TYPES

#define CPU_SIZE CPU_8_BYTE
#define CPU_ENDIAN CPU_ENDIAN_LITTLE

#define USING_CONSOLE YES_0

#define USING_STA YES_0
#define USING_STB YES_0
#define USING_STC YES_0
#define DEFAULT_INT_SIZE ATYPE_32BIT

#define LARGEST_CHAR STRING_TYPE_A
#define USING_STR STRING_TYPE_A
#define USING_LOM _ARC_CHA

#define USING_FP 8
#define USING_FPC YES_0
#define USING_FPD YES_0

#define USING_SOFTWARE_FPC  NO_0
#define USING_SOFTWARE_FPD  NO_0
#define USING_SOFTWARE_FPE  YES_0

#define USING_16_BYTE_POD_TYPES NO_0

#define BOL_SIZE 4 //< Size of boolean in bytes.

// Last 128-bit custom type; to disable define as 19 (ASCII BOL).
#define ETE_STOP 19

// Last 64-bit custom type; to disable define as CT5_STOP.
#define ETD_STOP ETE_STOP

// Last 32-bit custom type; to disable define as CT4_STOP.
#define ETC_STOP ETD_STOP

// Last 16-bit custom type; to disable define as CT3_STOP.
#define ECB_STOP ETC_STOP

#define ACTX_HANDLER_INIT ACTXHandlerDefault
