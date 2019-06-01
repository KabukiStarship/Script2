/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_object.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_3
#ifndef SCRIPT2_COBJECT
#define SCRIPT2_COBJECT

#include "c_socket.h"
#include "c_test.h"

namespace _ {
struct CObject;
}

/* ASCII Factory manages memory for ASCII Objects.
@return Nil upon failure or if no return socket is expected, or a pointer to a
word-aligned socket upon success.
@param obj      The ASCII Object and AsciiFactory.
@param function A jump table function index.
@param arg      Pointer to the ASCII Factory argument. */
typedef SIN (*AsciiFactory)(::_::CObject& obj, SIW function, void* arg);

namespace _ {

/* ASCII OBJ and AsciiFactory. */
struct CObject {
  AsciiFactory factory;  //< ASCII CObject Factory function pointer.
  UIW* begin;            //< Pointer to the contiguous ASCII CObject.
};

enum AsciiFactoryFunctions {
  kFactoryCanGrow = 0,  //< Factory function checks if the size can double.
  kFactoryDelete = 1,   //< Factory function deletes an OBJ.
  kFactoryClone = 2,    //< Factory function clones the OBJ.
  kFactoryGrow = 3,     //< Factory function double OBJ size in bytes.
  kFactoryInfo = 4,     //< Factory function gets the info string.
  kFactoryFunctionCount = 5,  //< Factory function count.
};

enum AsciiFactoryErrors {
  kFactorySuccess = 0,      //< Factory operation completed successfully error.
  kFactoryNil = 1,          //< Factory missing error.
  kFactoryNilOBJ = 2,       //< Factory found nil obj.begin pointer error.
  kFactoryNilArg = 3,       //< Factory arg nil error.
  kFactoryCantGrow = 4,     //< Factory can't grow.
  kFactorySizeInvalid = 5,  //< Factory size invalid.
  kFactoryErrorCount = 6,   //< Factory function count.
};

/* An array of strings corresponding to the AsciiFactoryFunctions. */
SDK const CH1* STRAsciiFactoryFunction(SIN function);

/* Gets an AsciiFactoryErrors string by index. */
SDK const CH1* STRAsciiFactoryError(SIN index);

SDK /*inline*/ SI4 ObjDo(CObject& obj, SIW function, void* arg = nullptr);

SDK /*inline*/ UIW* ObjBeginSet(CObject& obj, void* buffer);

/* Checks if the value is a valid object index, that it's 7 less than the max
value or less. */
SDK /*inline*/ BOL ObjCountIsValid(SI1 value, SI1 count_min = 1);

/* Checks if the value is a valid object index, that it's 7 less than the max
value or less. */
SDK /*inline*/ BOL ObjCountIsValid(SI2 value, SI2 count_min = 1);

/* Checks if the value is a valid index, that it's 7 less than the max
value or less. */
SDK /*inline*/ BOL ObjCountIsValid(SI4 value, SI4 count_min = 1);

/* Checks if the value is a valid index, that it's 7 less than the max
value or less. */
SDK /*inline*/ BOL ObjCountIsValid(SI8 value, SI8 count_min = 1);

/* Checks if the value is a valid object size, that it's an even multiple of
8. */
SDK /*inline*/ BOL ObjSizeIsValid(SI2 value, SI2 count_min = 1);

/* Checks if the value is a valid object size, that it's an even multiple of
8. */
SDK /*inline*/ BOL ObjSizeIsValid(SI4 value, SI4 count_min = 1);

/* Checks if the value is a valid object size, that it's an even multiple of
8. */
SDK /*inline*/ BOL ObjSizeIsValid(SI8 value, SI8 count_min = 1);

/* Destructs the given ASCII CObject Factory. */
SDK SIN Delete(CObject& obj, BOL using_heap = true);

/* Utility function to statasfy compiler warning for unused exception. */
SDK void ObjException(const CH1* what);

/* Checks if the given function is an ASCII OBJ function.
@return True if the function is less than or equal to kFactoryInfo.
@desc   ASCII Object functions are 0 through kFactoryInfo. */
/*inline*/ SDK BOL IsOBJFactoryFunction(SIW function);

}  // namespace _
#endif
#endif
