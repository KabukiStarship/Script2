#include <global_seams.inl>

#define SCRIPT2 1

#define ALU_SIZE 64

#define SDK

#define UTF8 1
#define UTF16 2
#define UTF32 4

#define STRANDFACTORY TStrandFactoryStack
#define STACKFACTORY TStrandFactoryStack
#define ARRAYFACTORY TStrandFactoryStack
#define MAPFACTORY TStrandFactoryStack
#define BOOKFACTORY TStrandFactoryStack
#define DICFACTORY TStrandFactoryStack

#if PLATFORM == WINDOWS
#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 1
#else
#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 1
#endif

#define ASSERT_FREEZE 0  //< Flag to trigger a crash upon failed DASSERT.

// Flag for if to log the failed DASSERT but do not crash.
#define ASSERT_LOG 0
#define ASSERT_DNC 1  //< Flag for Do Not Care (DNC) upon failed DASSERT.

#define BARE_METAL 1       //< Bare metal (i.e. No OS) OS type macro.
#define BARE_METAL_MBED 2  //< mbed bare-metal OS type macro.
#define MBED_OS 3          //< Arduino bare-metal OS type macro.
#define ARDUINO 4          //< mbed OS type macro.
#define MINGW32 5          //< Win32 OS type macro.
#define WINDOWS 6          //< Slots Universal OS type macro.
#define ANDROID 7          //< Android OS type macro.
#define LINUX 8            //< Linux OS type macro.
#define OSX 9              //< OSX OS type macro.
#define IOS 10             //< iOS OS type macro.

#define X86 1    //< 32-bit x86 processor family macro.
#define X64 2    //< 64-bit x86 processor family macro.
#define ARM8 3   //< ARM8 processor family macro.
#define ARM16 4  //< ARM16 processor family macro.
#define ARM32 5  //< ARM32 processor family macro.
#define ARM64 6  //< ARM64 processor family macro.

#define VISUAL_CPP 1  //< Flag for Visual-C++ compiler.

#define YES 0  //< Logical yes.
#define NO 1   //< Logical no.

// Executable assembly type macro.
#define EXECECUTABLE 1
// Statically linked library assembly type macro.
#define STATICALLY_LINKED_LIBRARY 2
// Dynamically linked library assembly type macro.
#define DYNAMICALLY_LINKED_LIBRARY 3
// Dynamically linked library assembly type macro.
#define SINGLE_DLL 4

// Executable assembly type macro.
#define EXECECUTABLE 1

// Statically linked library assembly type macro.
#define STATICALLY_LINKED_LIBRARY 2

// Dynamically linked library assembly type macro.
#define DYNAMICALLY_LINKED_LIBRARY 3

// Dynamically linked library assembly type macro.
#define SINGLE_DLL 4

#define LARGEST_INT 2147483647  //< Use this for 32-bit CPUs
