/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_autoject.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_STACK
#ifndef SCRIPT2_COBJECT
#define SCRIPT2_COBJECT

#include "c_socket.h"
#include "c_test.h"

namespace _ {
struct Autoject;
}

/* ASCII Factory manages memory for ASCII Objects.
@return A word-aligned buffer, rounding up if unaligned.
@param obj  A block of word-aligned heap memory.
@param size The size of the buffer to create in bytes. */
typedef UIW* (*RamFactory)(UIW* obj, SIW size);

namespace _ {

/* ASCII OBJ and RamFactory. */
struct Autoject {
  RamFactory ram_factory;  //< Autoject Factory function pointer.
  UIW* begin;              //< Pointer to the Autoject.
};

enum AsciiFactoryFunction {
  kFactoryDelete = 0,  //< Factory function deletes an OBJ.
  kFactoryNew = 1,     //< Factory function checks if the size can double.
  kFactoryGrow = 2,    //< Factory function double OBJ size.
  kFactoryClone = 3,   //< Factory function clones the OBJ.
  kFactoryName = 4,    //< Factory function gets the info string.
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

/* Creates or destroys a block of heap memory. */
LIB_MEMBER UIW* RamFactoryHeap(UIW* obj, SIW size);

/* Creates a block of heap memory. */
LIB_MEMBER UIW* RamFactoryStack(UIW* ptr, SIW size);

LIB_INLINE UIW* AutojectBeginSet(Autoject& obj, void* buffer);

/* Deletes the given obj using the obj.factory. */
LIB_MEMBER void Delete(Autoject& obj);

}  // namespace _
#endif
#endif
