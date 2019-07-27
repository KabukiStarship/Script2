# Fastest Method to Align Pointers

## Content Table

1. [Overview](#overview)
   4. [std::align](#stdalign)
2. [Algorithms](#algorihm)
   1. [Negative Offset Method](#negative-offset-method)
   2. [Negative Mask Method](#negative-mask-method)
3. [Script2 Memory Alignment Algorithm](#script2-memory-alignment-algorithm)
4. [Conclusion](#conclusion)

## License

Copyright 2018-9 (C) [Cale McCollough](mailto:calemccollough@gmail.com). All rights reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

This article cites two algorithms for Fair use of educational purposes that are not the creation of the author, one from the GNU GCC compiler which is copyright of the Free Software Foundation, Inc., and the other from Visual-C++ compiler which is copyright of Microsoft Corporation.

### Overview

This paper outlines the fastest possible way to align a pointer to any power of 2 boundaries with 7 single-cycle instructions on x86. There are two methods to perform the alignment, both using the same concept on different halves of the equation, but one is faster for all situations and hence may be preferred. Most pointer alignment algorithms use the modulo instruction which, unbeknownst to most people, takes hundreds of clock cycles and is notorious for introducing bugs in interrupt handlers and real-time systems. This algorithm presented is in little-endian format, and those using big-endian shall be shunned. #FootDown

### std::align

The most commonly used method to align pointers in C++ is std::align. For the purpose of this paper, we're just going to focus on the two most common implementations, GCC and Visual-C++ as of 8/18/2018.

```C++
/* Given a pointer ptr to a buffer of size space, returns a pointer aligned by
the specified alignment for size number of bytes and decreases space argument by
the number of bytes used for alignment. The first aligned address is returned.
@return The adjusted value of ptr, or null pointer value if the space provided
is too small.
@param alignment The desired alignment.
@param size      The size of the storage to be aligned.
@param ptr       Pointer to contiguous storage of at least space bytes.
@param space     The size of the buffer in which to operate.

@desc The function modifies the pointer only if it would be possible to fit the
wanted number of bytes aligned by the given alignment into the buffer. If the
buffer is too small, the function does nothing and returns nullptr.

The behavior is undefined if alignment is not a fundamental or extended
alignment value supported by the implementation (until C++17)power of two (since
C++17). */
void* align(size_t alignment, size_t size, void*& ptr, size_t& space);
```

#### Visual C++ 2018 Implementation


```C++
void* align_vcpp(size_t alignment, size_t size, void*& ptr, size_t& space) {
  // Begin Visual-C++ Implementation
  // try to carve out _Size bytes on boundary _Bound
  size_t offset =
      static_cast<size_t>(reinterpret_cast<uintptr_t>(ptr) & (alignment - 1));
  if (offset != 0) {
    offset = alignment - offset;  // number of bytes to skip
  }

  if (space < offset || space - offset < size) {
    return nullptr;
  }

  // enough room, update
  ptr = static_cast<char*>(ptr) + offset;
  space -= offset;
  return ptr;
  // End Visual-C++ Implementation
}
```

Observations include that in order to align the pointer, the current state of the art algorithm uses a conditional statement comparing the masked off bits to align, which is very slow. This warrants this algorithm being removed from our benchmark for lack of sophistication, but we'll put them in just to shame them.

#### GCC Implementation

```C++
inline void* align(size_t __align, size_t __size, void*& __ptr, size_t& __space)
noexcept {
  const auto __intptr = reinterpret_cast<uintptr_t>(__ptr);
  const auto __aligned = (__intptr - 1u + __align) & -__align;
  const auto __diff = __aligned - __intptr;
  if ((__size + __diff) > __space)
    return nullptr;
  else
    {
      __space -= __diff;
      return __ptr = reinterpret_cast<void*>(__aligned);
    }
}
```

***Observations***

The magic line in this algorithm is `const auto __aligned = (__intptr + __align - 1u) & -__align;`. So what exactly does this do?

First, let's start with 2's complement conversion. In everyone's computer, they handle signed numbers by converting to 2's complement by inverting the bits and adding 1 if it's negative. `-__align` then becomes `(~__align)+1)`, and align will be an even power of 2, which has a single bit asserted, so inverting the bits and adding 1 will turn `0b'00010000` into `0b'11110000`, which is the inverse mask for the Least Significant bits to align.

The second piece to unpack is the `(__intptr + __align - 1u)` portion. All this is doing is by subtracting one from the __align, which is an even power of 2, we're guaranteeing that we assert the __align bit is guaranteed to be 1 unless `(__intptr % __align) == 0`; which is pretty clever.

### Optimization

There isn't much to optimize, but we our optimization will come from not throwing the baby out with the bathwater so to speak. Instead, since we have to check to see if we have enough memory to align the pointer without overflowing, we want to find an offset to add to the pointer to align it. We will use the approach where we first define the bits we want to add to then deduce the formula to create the bit pattern.

### Proof by Induction by Truth Table

```
Given the truth table for 2 bits:

~00 = 11 => 00 + 11 + 1 = 0x100
~01 = 10 => 01 + 10 + 1 = 0x100
~10 = 01 => 10 + 01 + 1 = 0x100
~11 = 00 => 11 + 00 + 1 = 0x100

Clearly the bit pattern applies identically to 3 bits:

~000 = 111 => 000 + 111 + 1 = 0x1000
~001 = 110 => 001 + 110 + 1 = 0x1000
~010 = 101 => 010 + 101 + 1 = 0x1000
~011 = 100 => 011 + 100 + 1 = 0x1000
~100 = 011 => 100 + 011 + 1 = 0x1000
~101 = 010 => 101 + 010 + 1 = 0x1000
~110 = 001 => 110 + 001 + 1 = 0x1000
~111 = 000 => 111 + 000 + 1 = 0x1000

And clearly it also applies to 4-bits:

~0000 = 1111 => 0000 + 1111 + 1 = 0x10000
~0001 = 1110 => 0001 + 1110 + 1 = 0x10000
~0010 = 1101 => 0010 + 1101 + 1 = 0x10000
~0011 = 1100 => 0011 + 1100 + 1 = 0x10000
~0100 = 1011 => 0100 + 1011 + 1 = 0x10000
~0101 = 1010 => 0101 + 1010 + 1 = 0x10000
~0110 = 1001 => 0110 + 1001 + 1 = 0x10000
~0111 = 1000 => 0111 + 1000 + 1 = 0x10000
~1000 = 0111 => 1000 + 0111 + 1 = 0x10000
~1001 = 0110 => 1001 + 0110 + 1 = 0x10000
~1010 = 0101 => 1010 + 0101 + 1 = 0x10000
~1011 = 0100 => 1011 + 0100 + 1 = 0x10000
~1100 = 0011 => 1100 + 0011 + 1 = 0x10000
~1101 = 0010 => 1101 + 0010 + 1 = 0x10000
~1110 = 0001 => 1110 + 0001 + 1 = 0x10000
~1111 = 0000 => 1111 + 0000 + 1 = 0x10000

Thus we can conclude by induction the pattern holds true for all powers of 2.
```

For those who are not familiar with 2's complement math, what we did here by inverting the bits and adding was actually multiplying by negative one! We can use this to allow the compiler to automatically optimize our algorithm for us. But there is still one problem: We can't just invert 3 of the bits of a register, we have to invert them all so we will have to use a mask to mask off the bits that we want to align. Luckily for us, the mask we need just so happens to be one less than the power of 2 we want to align to. This unintentional consequence of using an offset that we then add to the word to align it also provides a rather nifty optimization to the std::align function we'll reveal in the next section.

## Script2 Memory Alignment Algorithm

```C++
namespace _ {
/* Aligns the given pointer to a power of two boundaries with a premade mask.
@return An aligned pointer of typename T.
@brief Algorithm is a 2's compliment trick that works by masking off
the desired number of bits in 2's compliment and adding them to the
pointer.
@param pointer The pointer to align.
@param mask The mask for the Least Significant bits to align. */
template <typename T = char>
inline T* AlignUp(void* pointer, intptr_t mask) {
  intptr_t value = reinterpret_cast<intptr_t>(pointer);
  value += (-value ) & mask;
  return reinterpret_cast<T*>(value);
}
inline void* align(size_t align, size_t size, void*& ptr,
                          size_t& space) noexcept {
  // Begin Script2 Implementation
  intptr_t int_ptr = reinterpret_cast<intptr_t>(ptr),
           offset = (-int_ptr) & (align - 1);
  if ((space -= offset) < size) {
    space += offset;
    return nullptr;
  }
  return reinterpret_cast<void*>(int_ptr + offset);
  // End Script2 Implementation
}
} //< namespace _
```

## Example calls using the faster mask technique.

```C++
enum { kSize = 256 };
char buffer[kSize + 64];

char* aligned_to_64_byte_cache_line = AlignUp<> (buffer, 63);

char16_t* aligned_to_64_byte_cache_line2 = AlignUp<char16_t> (buffer, 63);
```

## Example slower std::align CPU Cache-line Alignment

```C++
enum { kSize = 1024 + 64; };

char buffer
void* ptr;
size_t space = kSize;
std::align (64, kSize , ptr, space);
```

## 3.1 std::align Script2 Implementation

```C++
inline void* align_kabuki(size_t align, size_t size, void*& ptr,
                          size_t& space) noexcept {
  // Begin Script2 Implementation
  intptr_t int_ptr = reinterpret_cast<intptr_t>(ptr),
           offset = (-int_ptr) & (align - 1);
  if ((space -= offset) < size) {
    space += offset;
    return nullptr;
  }
  return reinterpret_cast<void*>(int_ptr + offset);
  // End Script2 Implementation
}
```

#### Disassembly

```C++
?align_kabuki@@YAPEAX_K0AEAPEAXAEA_K@Z PROC    ; align_kabuki, COMDAT

  mov  r10, QWORD PTR [r8]

  dec  rcx

  mov  r8, QWORD PTR [r9]
  mov  rax, r10
  neg  rax
  and  rcx, rax
  mov  rax, r8
  sub  rax, rcx
  mov  QWORD PTR [r9], rax
  cmp  rax, rdx
  jae  SHORT $LN2@align_kabu

  mov  QWORD PTR [r9], r8

  xor  eax, eax

  ret  0
$LN2@align_kabu:

  lea  rax, QWORD PTR [rcx+r10]

  ret  0
?align_kabuki@@YAPEAX_K0AEAPEAXAEA_K@Z ENDP    ; align_kabuki
```

***Total Instructions in Success Path:*** **13**

***Total Instructions in Fail Path:*** **14**

### GCC (Slightly Modified) vs Script2 x86 Disassembly

```C++
inline void* align_gcc(size_t align, size_t size, void*& ptr,
                       size_t& space) noexcept {
  // Begin GCC Implementation
  intptr_t int_ptr = reinterpret_cast<intptr_t>(ptr),
           signed_align = ((intptr_t)align),
           aligned = (int_ptr + signed_align - 1) & -signed_align,
           diff = aligned - int_ptr;
  if ((size + diff) > space) return nullptr;
  space -= diff;
  return reinterpret_cast<void*>(aligned);
  // End GCC Implementation
}
```

***Disassembly***

```C++

?align_gcc@@YAPEAX_K0AEAPEAXAEA_K@Z PROC    ; align_gcc, COMDAT

  mov  rax, QWORD PTR [r8]

  lea  r8, QWORD PTR [rcx-1]
  add  r8, rax
  neg  rcx
  and  r8, rcx

  mov  rcx, QWORD PTR [r9]
  mov  r10, r8
  sub  r10, rax
  lea  rax, QWORD PTR [r10+rdx]
  cmp  rax, rcx
  jbe  SHORT $LN2@align_gcc
  xor  eax, eax

  ret  0
$LN2@align_gcc:

  sub  rcx, r10

  mov  rax, r8
  mov  QWORD PTR [r9], rcx

  ret  0
?align_gcc@@YAPEAX_K0AEAPEAXAEA_K@Z ENDP    ; align_gcc
```

***Total Instructions for Success Path:*** **15**

***Total Instructions for Fail Path:*** **13**

---

#### Visual-C++ Shaming

```C++
void* align_vcpp(size_t alignment, size_t size, void*& ptr, size_t& space) {
  // Begin Visual-C++ Implementation
  // try to carve out _Size bytes on boundary _Bound
  size_t offset =
      static_cast<size_t>(reinterpret_cast<uintptr_t>(ptr) & (alignment - 1));
  if (offset != 0) {
    offset = alignment - offset;  // number of bytes to skip
  }

  if (space < offset || space - offset < size) {
    return nullptr;
  }

  // enough room, update
  ptr = static_cast<char*>(ptr) + offset;
  space -= offset;
  return ptr;
  // End Visual-C++ Implementation
}
```

***Disassembly***

```C++
?align_vcpp@@YAPEAX_K0AEAPEAXAEA_K@Z PROC    ; align_vcpp, COMDAT

  mov   r10, QWORD PTR [r8]
  lea   rax, QWORD PTR [rcx-1]
  and   rax, r10

  sub   rcx, rax
  test  rax, rax
  cmove rcx, rax
  mov   rax, QWORD PTR [r9]
  cmp   rax, rcx
  jb    SHORT $LN4@align_vcpp
  sub   rax, rcx
  cmp   rax, rdx
  jb    SHORT $LN4@align_vcpp

  lea   rax, QWORD PTR [rcx+r10]
  mov   QWORD PTR [r8], rax

  sub   QWORD PTR [r9], rcx

  mov   rax, QWORD PTR [r8]

  ret   0
$LN4@align_vcpp:

  xor   eax, eax

  ret   0
?align_vcpp@@YAPEAX_K0AEAPEAXAEA_K@Z ENDP    ; align_vcpp
```

***Total Instructions for Success Path:*** **17**

***Total Instructions for Fail Path:*** **11**

---

## Conclusion

The algorithms, because they all use single-cycle instructions, were rated divided into a number of instructions in the success path versus the fail path; to do otherwise would introduce overhead and benchmark into the system that would be less accurate.

The fail path is defined as the path when aligning the pointer causes a buffer overflow situation. First, we must start by giving an award to Microsoft, they failed the fastest at 11 instructions. Bravo! The GCC implementation comes in second with 13 instructions and the Script2 implementation comes in last with 14 instructions. However, it is assumed a buffer overflow is going is rare so the performance of the fail path is irrelevant because their counts are within +/- 2 instructions.

The success path is defined as when there is no buffer overflow event. In this benchmark with O2 optimizations on, the Script2 implementation comes in first with 13 instructions, followed by the GCC implementation with 15 instructions, and Visual studio coming in last with 17 instructions. This makes the Script2 implementation 13.3% faster as a direct replacement for std::align and 23.5% faster than the Visual-C++ implementation.

In order to convert the algorithm from using the pow_2 (i.e. integer power of 2), one instruction may be shaved off of the Success path making the instruction count 12, which is 20% faster than the GCC algorithm and 29.4% faster than the Visual-C++ implementation.

The Script2 implementation is based on proven 2's complement math with all single-cycle instructions and is the fastest of the options presented for the Success path, and the performance of the fail path is still acceptable for high-performance computing, so it is reasonable to conclude the implementation is more suitable for general-purpose computing than the GCC algorithm. Given the Script2 implementation both provides two methods to call the function, the offset and pow_2 methods, and it is faster, it should be the preferred implementation.
