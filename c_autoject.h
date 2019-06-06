/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_autoject.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_SEAM_STRAND
#ifndef SCRIPT2_COBJECT
#define SCRIPT2_COBJECT

#include "c_socket.h"
#include "c_test.h"

namespace _ {
struct Autoject;
}

/* ASCII Factory manages memory for ASCII Objects.
@return Nil upon failure, an AsciiFactoryErrors, or a pointer to a word-aligned
socket upon success.
@param obj      The ASCII Object and AsciiFactory.
@param function A jump table function index.
@param arg      A size or pointer to the ASCII Factory argument. */
typedef SIW (*AsciiFactory)(::_::Autoject& obj, SIW function, SIW arg);

namespace _ {

/* ASCII OBJ and AsciiFactory. */
struct Autoject {
  AsciiFactory factory;  //< Autoject Factory function pointer.
  UIW* begin;            //< Pointer to the Autoject.
};

enum AsciiFactoryFunction {
  kFactoryDelete = 0,  //< Factory function deletes an OBJ.
  kFactoryNew = 1,     //< Factory function checks if the size can double.
  kFactoryGrow = 2,    //< Factory function double OBJ size.
  kFactoryClone = 3,   //< Factory function clones the OBJ.
  kFactoryInfo = 4,    //< Factory function gets the info string.
  kFactoryFunctionCount = 5,  //< Factory function count.
};

enum AsciiFactoryError {
  kFactorySuccess = 0,      //< Factory operation completed successfully error.
  kFactoryNil = 1,          //< Factory missing error.
  kFactoryNilOBJ = 2,       //< Factory found nil obj.begin pointer error.
  kFactoryNilArg = 3,       //< Factory arg nil error.
  kFactoryCantGrow = 4,     //< Factory can't grow.
  kFactorySizeInvalid = 5,  //< Factory size invalid.
  kFactoryErrorCount = 6,   //< Factory function count.
};

/* An array of strings corresponding to the AsciiFactoryFunctions. */
SDK const CH1* AsciiFactoryFunction(SIW function);

/* Gets an AsciiFactoryErrors string by index. */
SDK const CH1* AsciiFactoryError(SIW index);

/* Checks if the given factory_result is an error code. */
SDK /*inline*/ SIW IsError(SIW factory_result);

/* Checks if the given factory_result is an error code. */
SDK /*inline*/ SIW IsError(void* factory_result);

/* Utility function to statasfy compiler warning for unused exception. */
SDK void ObjException(const CH1* what);

/* Checks if the given function is an ASCII OBJ function.
@return True if the function is less than or equal to kFactoryInfo.
@desc   ASCII Object functions are 0 through kFactoryInfo.
SDK BOL IsFactoryFunction(SIW function); */

SDK /*inline*/ SIW Do(Autoject& obj, SIW function, SIW* arg = nullptr);

SDK /*inline*/ UIW* AutojectBeginSet(Autoject& obj, void* buffer);

/* Deletes the given obj using the obj.factory. */
SDK void Delete(Autoject& obj);

}  // namespace _
#endif
#endif
