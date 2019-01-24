/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/global.h
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

#ifndef INCLUDED_SCRIPTGLOBAL
#define INCLUDED_SCRIPTGLOBAL 1

#if SEAM == SCRIPT2_0
#include "cconsole.h"
#include "crng.h"
#endif
#if SEAM == SCRIPT2_1
#include "cconsole.h"
#include "crng.h"
#endif
#if SEAM == SCRIPT2_2
#include "cconsole.h"
#include "crng.h"
#include "tbinary.h"
#include "tsocket.h"
#endif
#if SEAM == SCRIPT2_3 || SEAM == SCRIPT2_4
#include "cconsole.h"
#include "crng.h"
#include "tbinary.h"
#endif
#if SEAM == SCRIPT2_5
#include "cconsole.h"
#include "crng.h"
#include "tclock.h"
#endif
#if SEAM == SCRIPT2_6
#endif
#if SEAM == SCRIPT2_7
#endif
#if SEAM == SCRIPT2_8
#endif
#if SEAM == SCRIPT2_9
#endif
#if SEAM == SCRIPT2_10
#endif
#if SEAM == SCRIPT2_11
#endif
#if SEAM == SCRIPT2_12
#endif
#if SEAM == SCRIPT2_13
#endif
#if SEAM == SCRIPT2_14
#endif

#endif  //< #ifndef INCLUDED_SCRIPTGLOBAL
