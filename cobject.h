/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
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
#ifndef INCLUDED_SCRIPT2_COBJECT
#define INCLUDED_SCRIPT2_COBJECT

#include "csocket.h"
#include "ctest.h"

/* ASCII Factory manages memory for ASCII Objects.
@return Nil upon failure or if no return socket is expected, or a pointer to a
word-aligned socket upon success.
@param start    Pointer to an existing socket or nil to create a socket.
@param function A jump table function index.
@param arg      Pointer to the ASCII Factory argument. */
typedef UIW* (*AsciiFactory)(UIW* start, SIW function, void* arg);

namespace _ {

/* ASCII Obj with programmable ASCII Factory. */
struct CObject {
  UIW* start;            //< Pointer to the contiguous ASCII Obj.
  AsciiFactory factory;  //< ASCII Obj Factory function pointer.
};

enum {
  kFactoryCreateOrDelete =
      0,          //< ASCII Factory function: Default Create Destroy Obj.
  kFactoryGrow,   //< ASCII Factory function: Grow Obj function index.
  kFactoryClone,  //< ASCII Factory function: Clones Obj the given object.
};

/* Destructs the given ASCII Obj Factory. */
API void Destroy(CObject stack);

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

}  // namespace _
#endif  //< #if SEAM >= _0_0_0__02
#endif  //< INCLUDED_SCRIPT2_COBJECT
