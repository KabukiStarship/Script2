/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/_Main.cpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
//
#include "../_Package.inl"
//
#include "00.Core.inl"
#include "01.RNG.inl"
#include "02.ItoS.inl"
#include "03.FtoS.inl"
#include "04.SPrinter.inl"
#include "05.Clock.inl"
#include "06.Stack.inl"
#include "07.Matrix.inl"
#include "08.String.inl"
#include "09.Loom.inl"
#include "10.List.inl"
#include "11.Book.inl"
#include "12.Map.inl"
#include "13.Table.inl"
#include "14.Dic.inl"
#include "15.Crabs.inl"
#include "16.Door.inl"
#include "17.Room.inl"
#include "18.File.inl"
#include "19.Release.inl"
using namespace _;

inline const CHA* Script2Tests(const CHA* args) {
  return TTestTree<Script2::Core, Script2::RNG, Script2::ItoS, Script2::FtoS, 
                   Script2::SPrinter, Script2::Clock, Script2::Stack, 
                   Script2::Matrix, Script2::String, Script2::Loom, 
                   Script2::List, Script2::Book, Script2::Map, Script2::Table, 
                   Script2::Dic, Script2::Crabs, Script2::Door, Script2::Room,
                   Script2::File>(
      args);
}
