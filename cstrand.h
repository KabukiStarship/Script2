/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/cstrand.h
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

#if SEAM >= SCRIPT2_3
#ifndef INCLUDED_SCRIPTUTF
#define INCLUDED_SCRIPTUTF

#include "csocket.h"

#ifndef USING_UTF8
#define USING_UTF8 YES
#endif

#if USING_UTF8 == YES
#include "cstr1.h"
#endif
#if USING_UTF16 == YES
#include "cstr2.h"
#endif
#if USING_UTF32 == YES
#include "cstr4.h"
#endif


#endif  //< #if INCLUDED_SCRIPTUTF
#endif  //< #if SEAM >= SCRIPT2_3
