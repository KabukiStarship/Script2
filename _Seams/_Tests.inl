// Copyright Kabuki Starship™ <kabukistarship.com>.
#include <_Config.h>
//
#include "../_Package.inl"
//
#include "01.COut.inl"
#include "02.RNG.inl"
#include "03.ItoS.inl"
#include "04.FtoS.inl"
#include "05.Uniprinter.inl"
#include "06.Clock.inl"
#include "07.Stack.inl"
#include "08.String.inl"
#include "09.Loom.inl"
#include "10.List.inl"
#include "11.Book.inl"
#include "12.Map.inl"
#include "13.Table.inl"
#include "14.Dic.inl"
#include "15.Crabs.inl"
#include "16.Room.inl"
#include "17.Matrix.inl"
#include "18.File.inl"
#include "19.Autojects.inl"
#include "20.Script2.inl"
#include "21.Release.inl"
using namespace _;

inline const CHA* Script2Tests(const CHA* args) {
  return TTestTree<Script2::COut, Script2::RNG, Script2::ItoS, Script2::FtoS, 
                   Script2::Uniprinter, Script2::Clock, Script2::Stack, 
                   Script2::Matrix, Script2::String, Script2::Loom, 
                   Script2::List, Script2::Book, Script2::Map, Script2::Table, 
                   Script2::Dic, Script2::Crabs, Script2::Room, Script2::Matrix,
                   Script2::Autojects, Script2::File>(args);
}
