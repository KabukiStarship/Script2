/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_hash.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

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
