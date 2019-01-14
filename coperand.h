/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /operand.h
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
#if SEAM >= _0_0_0__14
#ifndef SCRIPT2_OPERAND
#define SCRIPT2_OPERAND
// Dependencies:
#include "slot.h"
// End dependencies.

namespace _ {

struct SDK CCrabs;

/* Interface for an abstract A*B Op operand.
    A Script Operand is an object that is being operated on.
    Let A be a set of states in a Chinese Room state machine.
    Let B be a set of bytes in a set of Abstract Serial Ports.

    @code
    +----------- Result: The set of finite states
    | +--------- Op
    | | +------- Set of finite states
    | | | +----- Star Op
    | | | | +--- Operands (input values)
    | | | | |
    v v v v v
    A = A * B
        |<->|   Op
    |<----->|   Evaluation
    @endcode

    When a device is selected by a Slot, the caller can then call functions
    of that device. The Slot has a stack of devices that it then pushes the
    Star* on top of. This object is now selected, and agents can now call
    functions of this object via the Data Controller (DC).

    @see Console for example of how to use Operand interface.
*/

struct SDK Operand {
  /* Script2 Operations.
      @param index The index of the expression.
      @param crabs  The CCrabs to read and write from.
      @return      Returns nil upon success, a Set header upon query, and an
                   error_t ticket upon Read-Write failure. */
  virtual const Op* Star(CHW index, CCrabs* crabs) = 0;
};

/* Returns the name of the given Operand. */
SDK const CH1* OperandName(Operand* op);

/* Gets the number_ of ops in the given expressions. */
SDK UIW OperandCount(Operand* op);

/* Returns the index of the given Op using the given slot.
    @param  key_begin Beginning of the key slot socket.
    @param  key_end   End of the key slot socket.
    @return A value printable Unicode CH1 or invalid if the Operand doesn't
            Contain the given key. */
SDK CHW OperandIndex(Operand* operand, CH1* key_begin, CH1* key_end);

#if USING_CRABS_TEXT
/* Queries the given Operand Op Header.
    @param  crabs The expression to write the query to. Set to nil to return
                 op.
    @param  op   The Op header.
    @return Returns nil upon success and an error Op upon failure.
SDK const Op* OperandQuery (CCrabs* crabs, const Op* op);*/

/* Queries the operand for the given ??? @todo fix me */
Slot& OperandQuery(Operand* root, const CH1* address, Slot& key);

/* Prints the Operand to the Text.
    @param  text     The Text to utf to.
    @param  operand The Operand to utf.
    @return text. */
SDK UTF1& PrintOperand(UTF1& slot, Operand* operand);
#endif

}  // namespace _

#if USING_CRABS_TEXT
/* Overloaded operator<< prints the given operand to the text. */
inline ::_::UTF1& operator<<(::_::UTF1& printer, ::_::Operand* operand) {
  return ::_::PrintOperand(printer, operand);
}

#endif
#endif  //< SCRIPT2_OPERAND
#endif  //< #if SEAM >= _0_0_0__14
