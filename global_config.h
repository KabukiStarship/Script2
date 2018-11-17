/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /kabuki/features/crabs/config.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#ifndef HEADER_FOR_CRABS_CONFIG
#define HEADER_FOR_CRABS_CONFIG

#define ASSERT_FREEZE 0  //< Flag to trigger a crash upon failed assert.
#define ASSERT_LOG 0  //< Flag for if to log the failed assert but do not crash.
#define ASSERT_DNC 1  //< Flag for Do Not Care (DNC) upon failed assert.

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

// Endian nonsense.

#define IS_NOT_STUPID 1
#define IS_STUPID 2  //< Don't ask me what they where thinking.

#define YES 1  //< Logical yes.
#define NO 0   //< Logical no.

#define UTF1 1   //< flag for UTF-8.
#define UTF16 2  //< Flag for UTF-16.
#define UTF32 3  //< Flag for UTF-32.

// Executable assembly type macro.
#define EXECECUTABLE 1

// Statically linked library assembly type macro.
#define STATICALLY_LINKED_LIBRARY 2

// Dynamically linked library assembly type macro.
#define DYNAMICALLY_LINKED_LIBRARY 3

// Dynamically linked library assembly type macro.
#define SINGLE_DLL 4

#define LARGEST_INT 2147483647  //< Use this for 32-bit CPUs

//#include <assembly.inl>  //< Inline config stuff for your project.

#if CRABS_TEXT == UTF1
#if USING_UTF8 == 0
#warning You have the CRABS_TEXT set to UTF1 but USING_UTF8 is 0!
#ifdef USING_UTF8
#undef USING_UTF8
#endif
#define USING_UTF8 YES
#endif
#elif CRABS_TEXT == UTF16
#if USING_UTF16 == 0
#warning You have the CRABS_TEXT set to UTF1 but USING_UTF8 is 0!
#ifdef USING_UTF16
#undef USING_UTF16
#endif
#define USING_UTF16 YES
#endif
#elif CRABS_TEXT == UTF32
#if USING_UTF32 == 0
#warning You have the CRABS_TEXT set to UTF1 but USING_UTF8 is 0!
#ifdef USING_UTF32
#undef USING_UTF32
#endif
#define USING_UTF32 YES
#endif
#endif

#if CRABS_STRING_SIZE == 1
typedef SI1 schar_t;
#elif CRABS_STRING_SIZE == 2
typedef SI2 schar_t;
#elif CRABS_STRING_SIZE == 4
typedef SI4 schar_t;
#elif CRABS_STRING_SIZE == 8
typedef SI8 schar_t;
#endif

#if CRABS_MAX_ERRORS < 0
#error MAX_ERRORS must be greater than 0
#elif CRABS_MAX_ERRORS <= 255
typedef UI1 ticket_t;
#elif MAX_ERRORS <= 65535
typedef UI2 ticket_t;
#else
typedef UI4 ticket_t;
#endif

#if CRABS_MAX_PARAMS < 0
#error MAX_ERRORS must be greater than 0
#endif

#if CRABS_TEXT_SIZE_DEFAULT < 0
#error MAX_ERRORS must be greater than 0
#endif

#if COM_TIMEOUT_TICKS < 0
#error MAX_ERRORS must be greater than 0
#endif

// Big-Endian nonsense
#define IS_NOT_STUPID 1
#define IS_STUPID 2  //< Don't ask me what they where thinking.

// Executable assembly type macro.
#define EXECECUTABLE 1
// Statically linked library assembly type macro.
#define STATICALLY_LINKED_LIBRARY 2
// Dynamically linked library assembly type macro.
#define DYNAMICALLY_LINKED_LIBRARY 3
// Dynamically linked library assembly type macro.
#define SINGLE_DLL 4

namespace _ {
enum {
  kNo = 0,   //< Script no/false value.
  kYes = 1,  //< Script yes/true value.
  // kMinFloorSize  = 256,               //< Min size of a room.
  // kMaxFloorSize  = 0x7FFFFFFC,        //< Max room size: 2GB - 7 bits.
  kMaxFloorsCount = CRABS_MAX_WALLS,  //< Size of the Room Floor (socket).
  kSlotSizeMin = 128,                 //< Min size of a Slot - 1.
  kMaxErrors = CRABS_MAX_ERRORS,      //< Max errors before blowing up.
  kParamsMax = CRABS_MAX_PARAMS,      //< Max number of parameters.
  kWordAddressMask = kWordBitsMask,   //< For masking the word address.
  kTimeoutMicroseconds = COM_TIMEOUT_TICKS,  //< Timeout time in microseconds.
  kAddressLengthMax = CRABS_MAX_ADDRESS_LENGTH,  //< Max address (kADR) length.
  kMinStackSize = 1,                             //< Min CCrabs stack size.
  kOpNameLengthMax = CRABS_OP_MAX_NAME_LENGTH,
  // Max length of a Op description string.
  kOpDescriptionLengthMax = CRABS_OP_MAX_DECRABSION_LENGTH,
  // Max length of a Text.
  kCharCount = CRABS_TEXT_LENGTH,
  // Number of bits to shift to multiply or divide to get num_words.
  kWordBitCount = (sizeof(void*) == 8) ? 3 :      //< Shift left 3 to * by 8.
                      (sizeof(void*) == 4) ? 2 :  //< Shift right 2 to / by 4.
                          1,

  // Extra reserved memory at the stop of BOut.
  kBOutOverflowSize = 32,

  // Size of the Display Print Slot.
  kSlotBufferSizeRx = CRABS_BUFFER_SIZE_RX,

  // Size of the KeyboardInBuffer.
  kSlotBufferSizeTx = CRABS_BUFFER_SIZE_TX,

  kWindowSizeMin = 512,

  kBufferSizeDefault = 64 * 1024,
  kBufferSizeDefaultWords =
      kBufferSizeDefault / sizeof(SIW) + kBufferSizeDefault % sizeof(SIW) ? 1
                                                                          : 0,

  kAutoSizeMin = 512,
  kAutoSizeDefault = kAutoSizeMin * 4,

  kStackCountMaxDefault = 32,
  kFloorSize = 1024,  //< Size, or initial size, of the Floor.
};

}  // namespace _

#undef MAX_ERRORS
#undef MAX_NUM_PARAMS
#undef MAX_STRING_LENGTH
#undef COM_TIMEOUT_TICKS
#undef CRABS_LOG_SIZE
#undef OPERATION_MAX_NAME_LENGTH
#undef OPERATION_MAX_DECRABSION_LENGTH
#undef CRABS_TEXT_LENGTH
#undef CRABS_BUFFER_SIZE_RX
#undef CRABS_BUFFER_SIZE_TX

#define API

typedef UI4 word_t;

// Pre-compiled headers: comment out those you're not using.

typedef unsigned char UI1;
typedef unsigned int uint;

typedef SI4 TMS;  //< A 32-bit seconds since epoch timestamp.
typedef SI8 TME;  //< A 64-bit seconds since epoch timestamp.

typedef UI1 SIN;  //< ASCII Data Type UI1.

#if MAX_NUM_SLOTS <= 255
typedef UI1 slot_t;
enum { kMaxNumSlots = 0xff };
#elif MAX_NUM_SLOTS <= 65535
typedef UI2 slot_t;
enum { kMaxNumSlots = 0xffff };
#else
typedef UI4 slot_t;
enum { kMaxNumSlots = 0xffffffff };
#endif

/* Below are representations of not-a-numbers.
With signed integers, there is one additional negative number than positive
numbers due to  the 0. In the CRABS Protocol, this number is used to mark
invalid or corrupted data. If you are not using them and require the ROM
space, it will not harm anything to comment them out.

@code
#include <iostream>
#define NaN_SI4 0xFFFFFFF
void BlowUp () { PRINTF ("The sky is falling!");
if (-1 == NaN_SI4)
    BlowUp ();
@endcode
*/

// int-sized not-a-number.
enum {
  NaNInt = sizeof(int) == 4 ? static_cast<int>(0xFFFFFFFF)
                            : sizeof(int) == 2 ? static_cast<int>(0xFFFF) : 0,
};

typedef UI2 hash16_t;  //< Using unsigned 16-bit hash type.
typedef UI4 hash32_t;  //< Using unsigned 32-bit hash type.
typedef UI8 hash64_t;  //< Using unsigned 64-bit hash type.

enum {
  kLargest16BitPrime = 0xFFE1,      //< Largest 16-bit prime: 65521.
  kLargest32BitPrime = 0xFFFFFFFB,  //< Largest 32-bit prime: 4294967291.
};

static const UI8 kLargest64BitPrime = 0xFFFFFFFFFFFFFFC5;
//< Largest 64-bit prime: 18446744073709551557;

//< A char with a single newline char.

/* The level will more code creating a larger binary. Use one
    underscore to use more memory, and two underscores to use even more. */
#if CRABS_MEMORY_PROFILE == 1
typedef SI1 int_t;     //< Buffer signed index type.
typedef UI1 UIT;       //< Buffer unsigned index type.
typedef SI2 dint_t;    //< Buffer DBL-wide signed index type.
typedef UI2 duint_t;   //< Buffer DBL-wide unsigned index type.
typedef UI1 index_t;   //< Largest bit-depth TIndex this system supports.
typedef UI2 header_t;  //< Largest bit-depth THeader this system supports.
typedef UI2 data_t;    //< Largest bit-depth TData this system supports.

#elif (CRABS_MEMORY_PROFILE == 2) || (CRABS_MEMORY_PROFILE == 3)
typedef SI2 int_t;     //< Buffer signed index type.
typedef UI2 UIT;       //< Buffer unsigned signed index type.
typedef SI4 dint_t;    //< Buffer DBL-wide signed index type.
typedef UI4 duint_t;   //< Buffer DBL-wide unsigned index type.
typedef SI2 index_t;   //< Default TIndex size.
typedef UI2 header_t;  //< Default TKey size.
typedef UI4 data_t;    //< Default TData size.

#else  // CRABS_MEMORY_PROFILE == 5
typedef SI4 int_t;     //< Buffer signed index type.
typedef UI4 UIT;       //< Buffer unsigned signed index type.
typedef SI2 dint_t;    //< Buffer DBL-wide signed index type.
typedef UI8 duint_t;   //< Buffer DBL-wide unsigned index type.
typedef UI2 index_t;   //< Default TIndex size.
typedef UI4 header_t;  //< Default TKey size.
typedef UI8 data_t;    //< Default TData size.
#endif

#if CRABS_MEMORY_PROFILE >= 3 || DEBUG
#define CRABS_TEXT 3
#endif  //< CRABS_MEMORY_PROFILE >= 3

/* Macro declares a class to be non-copyable. */
#define NONCOPYABLE                                 \
  (ClassName) ClassName(const ClassName&) = delete; \
  void operator=(const ClassName&) = delete;
    // ClassName () = default //< Saw this once on the net but do we need it?

#endif  //< HEADER_FOR_CRABS_CONFIG
