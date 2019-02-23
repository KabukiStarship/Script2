/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_hash.h
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_9

#ifndef SCRIPT2_HASH_C
#define SCRIPT2_HASH_C

namespace _ {

/* Basic prime multiple hash algorithm.
@return hash + value * hash.
@param  value The CH1 value to hash.
@param  hash  The hash. */
SDK inline UI2 Hash16(CH1 value, UI2 hash = kPrimeLargestUI2);

/* Basic prime multiple hash algorithm.
@return hash + value * hash.
@param  value The CH1 value to hash.
@param  hash  The hash. */
SDK inline UI4 Hash32(CH2 value, UI4 hash = PRIME_LARGEST_UI4);

/* Basic prime multiple hash algorithm.
@return hash + value * hash.
@param  value The CH1 value to hash.
@param  hash  The hash. */
SDK inline UI8 Hash64(CH4 value, UI8 hash = PRIME_LARGEST_UI8);

/* Hashes the given CH1 using the primeHash function.
If you are experiencing collisions in your hash table, you may want to change
the see to a different prime number_.
@return A prime multiple hash of the given .
@param   The  to hash.
@param  hash   A prime number_ seed hash. */
SDK UI2 Hash16(const CH1*, UI2 hash = kPrimeLargestUI2);

/* Hashes the given CH1 using the primeHash function.
If you are experiencing collisions in your hash table, you may want to change
the see to a different prime number_.
@return A prime multiple hash of the given .
@param   The  to hash.
@param  hash   A prime number_ seed hash. */
SDK UI4 Hash32(const CH1*, UI4 hash = PRIME_LARGEST_UI4);

/* Hashes the given CH1 using the primeHash function.
If you are experiencing collisions in your hash table, you may want to change
the see to a different prime number_.
@return A prime multiple hash of the given .
@param   The  to hash.
@param  hash   A prime number_ seed hash. */
SDK UI8 Hash64(const CH1*, UI8 hash = PRIME_LARGEST_UI8);

}  // namespace _
#endif
#endif
