/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /vk.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#if SEAM >= SCRIPT2_UNIPRINTER

#ifndef INCLUDED_SCRIPTVK
#define INCLUDED_SCRIPTVK 1

namespace _ {

/* Gets the names of the KeyId. */
inline const CH1* KeyIdName();

/* Gets the array of KeyId offsets. */
inline const SI2* KeyIdOffset();

/* Gets the array of KeyId order. */
inline const UI1* KeyIdOrder();

/* Gets the name from the VK code. */
inline const CH1* KeyIdNameFromCode(SI4 code);

/* Gets the VK code from the name of the key. */
inline SI4 KeyIdCodeFromName(const CH1* name);

/* Convert a key id to an HID code.
@return Pointer to the a LUT.   */
const UI1* KeyboardNativeToHID();

/* Convert an HID code to a key id.
@return Pointer to the a LUT. */
const UI1* KeyboardHIDToNative();

typedef SI4 VKCode;
enum {
  cVKA = 4,
  cVKB = 5,
  cVKC = 6,
  cVKD = 7,
  cVKE = 8,
  cVKF = 9,
  cVKG = 10,
  cVKH = 11,
  cVKI = 12,
  cVKJ = 13,
  cVKK = 14,
  cVKL = 15,
  cVKM = 16,
  cVKN = 17,
  cVKO = 18,
  cVKP = 19,
  cVKQ = 20,
  cVKR = 21,
  cVKS = 22,
  cVKT = 23,
  cVKU = 24,
  cVKV = 25,
  cVKW = 26,
  cVKX = 27,
  cVKY = 28,
  cVKZ = 29,
  cVK1 = 30,
  cVK2 = 31,
  cVK3 = 32,
  cVK4 = 33,
  cVK5 = 34,
  cVK6 = 35,
  cVK7 = 36,
  cVK8 = 37,
  cVK9 = 38,
  cVK0 = 39,
  cVKEnter = 40,
  cVKEscape = 41,
  cVKDelete = 42,
  cVKTab = 43,
  cVKSpace = 44,
  cVKMinus = 45,
  cVKEquals = 46,
  cVKLeftBracket = 47,
  cVKRightBracket = 48,
  cVKBackslash = 49,
  cVKSemicolon = 51,
  cVKQuote = 52,
  cVKGrave = 53,
  cVKComma = 54,
  cVKPeriod = 55,
  cVKSlash = 56,
  cVKCapsLock = 57,
  cVKF1 = 58,
  cVKF2 = 59,
  cVKF3 = 60,
  cVKF4 = 61,
  cVKF5 = 62,
  cVKF6 = 63,
  cVKF7 = 64,
  cVKF8 = 65,
  cVKF9 = 66,
  cVKF10 = 67,
  cVKF11 = 68,
  cVKF12 = 69,
  cVKPrintScreen = 70,
  cVKScrollLock = 71,
  cVKPause = 72,
  cVKInsert = 73,
  cVKHome = 74,
  cVKPageUp = 75,
  cVKDeleteForward = 76,
  cVKEnd = 77,
  cVKPageDown = 78,
  cVKRight = 79,
  cVKLeft = 80,
  cVKDown = 81,
  cVKUp = 82,
  cKPNumLock = 83,
  cKPDivide = 84,
  cKPMultiply = 85,
  cKPSubtract = 86,
  cKPAdd = 87,
  cKPEnter = 88,
  cKP1 = 89,
  cKP2 = 90,
  cKP3 = 91,
  cKP4 = 92,
  cKP5 = 93,
  cKP6 = 94,
  cKP7 = 95,
  cKP8 = 96,
  cKP9 = 97,
  cKP0 = 98,
  cKPPoint = 99,
  cVKNonUSBackslash = 100,
  cKPEquals = 103,
  cVKF13 = 104,
  cVKF14 = 105,
  cVKF15 = 106,
  cVKF16 = 107,
  cVKF17 = 108,
  cVKF18 = 109,
  cVKF19 = 110,
  cVKF20 = 111,
  cVKF21 = 112,
  cVKF22 = 113,
  cVKF23 = 114,
  cVKF24 = 115,
  cVKHelp = 117,
  cVKMenu = 118,
  cVKLeftControl = 224,
  cVKLeftShift = 225,
  cVKLeftAlt = 226,
  cVKLeftGUI = 227,
  cVKRightControl = 228,
  cVKRightShift = 229,
  cVKRightAlt = 230,
  cVKRightGUI = 231
};

/* Gets the next key pressed in the keyboard event cue. */
inline SI4 CInKey();

/* Gets the pressed state of the vk_code. */
inline BOL CInState(SI4 vk_code);

struct KeyId {
  SI4 vk_code;
  const CH1* label;
  const CH1* description;

  KeyId(VKCode code, const CH1* label);

  void ReprogramConsole();
};

}  // namespace _

#endif  //< #ifndef INCLUDED_SCRIPTVK
#endif  //< #if SEAM >= SCRIPT2_UNIPRINTER
