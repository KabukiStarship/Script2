/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/_Main.cpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
//
#include "../_Package.inl"
//
#include "00.COut.inl"
#include "01.RNG.inl"
#include "02.ItoS.inl"
#include "03.FtoS.inl"
#include "04.Uniprinter.inl"
#include "05.Clock.inl"
#include "06.Stack.inl"
#include "07.String.inl"
#include "08.Loom.inl"
#include "09.List.inl"
#include "10.Book.inl"
#include "11.Map.inl"
#include "12.Table.inl"
#include "13.Dic.inl"
#include "14.Crabs.inl"
#include "15.Door.inl"
#include "16.Room.inl"
#include "17.Matrix.inl"
#include "18.File.inl"
#include "19.Release.inl"
using namespace _;

inline const CHA* Script2Tests(const CHA* args) {
  return TTestTree<Script2::COut, Script2::RNG, Script2::ItoS, Script2::FtoS, 
                   Script2::Uniprinter, Script2::Clock, Script2::Stack, 
                   Script2::Matrix, Script2::String, Script2::Loom, 
                   Script2::List, Script2::Book, Script2::Map, Script2::Table, 
                   Script2::Dic, Script2::Crabs, Script2::Door, Script2::Room,
                   Script2::File>(args);
}
