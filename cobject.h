/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script.git
@file    /cobject.h
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

#if SEAM >= _0_0_0__02

#ifndef INCLUDED_SCRIPTCOBJECT
#define INCLUDED_SCRIPTCOBJECT

#include "csocket.h"
#include "ctest.h"

typedef uintptr_t* (*HeapManager)(uintptr_t* buffer);

namespace _ {

/* C header for an ASCII kOBJ with programmable destructor. */
struct CObject {
  uintptr_t* begin;     //< Pointer to the contiguous ASCII kOBJ.
  HeapManager manager;  //< Pointer to the destructor.
};

/* Deletes the given objects dynamic memory if any is used. */
API inline void Delete(CObject obj);

/* Checks if the value is a valid object index, that it's 7 less than the max
value or less. */
API inline BOL ObjCountIsValid(SI1 value, SI1 count_min = 1);

/* Checks if the value is a valid object index, that it's 7 less than the max
value or less. */
API inline BOL ObjCountIsValid(SI2 value, SI2 count_min = 1);

/* Checks if the value is a valid index, that it's 7 less than the max
value or less. */
API inline BOL ObjCountIsValid(SI4 value, SI4 count_min = 1);

/* Checks if the value is a valid index, that it's 7 less than the max
value or less. */
API inline BOL ObjCountIsValid(SI8 value, SI8 count_min = 1);

/* Checks if the value is a valid object size, that it's an even multiple of
8. */
API inline BOL ObjSizeIsValid(SI2 value, SI2 count_min = 1);

/* Checks if the value is a valid object size, that it's an even multiple of
8. */
API inline BOL ObjSizeIsValid(SI4 value, SI4 count_min = 1);

/* Checks if the value is a valid object size, that it's an even multiple of
8. */
API inline BOL ObjSizeIsValid(SI8 value, SI8 count_min = 1);

/* Clones the given ASCII kOBJ. */
API uintptr_t* ObjClone(uintptr_t* ascii_object, SI1 size);

/* Clones the given ASCII kOBJ. */
API uintptr_t* ObjClone(uintptr_t* ascii_object, SI2 size);

/* Clones the given ASCII kOBJ. */
API uintptr_t* ObjClone(uintptr_t* ascii_object, SI4 size);

/* Clones the given ASCII kOBJ. */
API uintptr_t* ObjClone(uintptr_t* ascii_object, SI8 size);

}  // namespace _
#endif  //< #if SEAM >= _0_0_0__02
#endif  //< INCLUDED_SCRIPTCOBJECT
