/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cobject.h
@author  Cale McCollough <cale.mccollough@gmail.com>
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

#if SEAM >= _0_0_0__03
#ifndef SCRIPT2_COBJECT
#define SCRIPT2_COBJECT

#include "csocket.h"
#include "ctest.h"

namespace _ {
struct CObject;
}

/* ASCII Factory manages memory for ASCII Objects.
@return Nil upon failure or if no return socket is expected, or a pointer to a
word-aligned socket upon success.
@param obj      The ASCII Object and AsciiFactory.
@param function A jump table function index.
@param arg      Pointer to the ASCII Factory argument. */
typedef int (*AsciiFactory)(::_::CObject& obj, SIW function, void* arg);

namespace _ {

/* ASCII OBJ and AsciiFactory. */
struct CObject {
  UIW* begin;            //< Pointer to the contiguous ASCII CObject.
  AsciiFactory factory;  //< ASCII CObject Factory function pointer.
};

enum AsciiFactoryFunctions {
  kFactoryDelete = 0,  //< ASCII Factory function deletes an OBJ.
  kFactoryNew = 1,     //< ASCII Factory function creates a new OBJ.
  kFactoryClone = 2,   //< ASCII Factory function clones the OBJ.
  kFactoryGrow = 3,    //< ASCII Factory function double OBJ size in bytes.
  kFactoryInfo = 4,    //< The last ASCII Factory function.
};

enum AsciiFactoryErrors {
  kFactorySuccess = 0,      //< Factory operation completed successfully.
  kFactoryNilOBJ = 1,       //< Factory found nil obj.begin pointer.
  kFactoryNilArg = 2,       //< Factory arg nil.
  kFactoryOutOfRAM = 3,     //< Factory out of memory.
  kFactorySizeInvalid = 4,  //< Factory ASCII Type Size limit reached.
};

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

/* Destructs the given ASCII CObject Factory. */
API void Delete(CObject& object);

/* Checks if the given function is an ASCII OBJ function.
@return True if the function is less than or equal to kFactoryInfo.
@desc   ASCII Object functions are 0 through kFactoryInfo. */
inline API BOL IsOBJFactoryFunction(SIW function);

}  // namespace _
#endif  //< SCRIPT2_COBJECT
#endif  //< #if SEAM >= _0_0_0__03
