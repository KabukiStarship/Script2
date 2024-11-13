// Copyright Kabuki Starship™ <kabukistarship.com>.
#include <_Config.h>
//
#include "../_Package.hxx"
//
#include "01.COut.hxx"
#include "02.RNG.hxx"
#include "03.ItoS.hxx"
#include "04.FtoS.hxx"
#include "05.Uniprinter.hxx"
#include "06.Clock.hxx"
#include "07.Stack.hxx"
#include "08.String.hxx"
#include "09.Loom.hxx"
#include "10.List.hxx"
#include "11.Book.hxx"
#include "12.Map.hxx"
#include "13.Table.hxx"
#include "14.Dic.hxx"
#include "15.Crabs.hxx"
#include "16.Room.hxx"
#include "17.Matrix.hxx"
#include "18.File.hxx"
#include "19.Autojects.hxx"
#include "20.Script2.hxx"
#include "21.Release.hxx"
using namespace _;

inline const CHA* Script2Tests(const CHA* args) {
  return TTestTree<Script2::COut, Script2::RNG, Script2::ItoS, Script2::FtoS, 
                   Script2::Uniprinter, Script2::Clock, Script2::Stack, 
                   Script2::Matrix, Script2::String, Script2::Loom, 
                   Script2::List, Script2::Book, Script2::Map, Script2::Table, 
                   Script2::Dic, Script2::Crabs, Script2::Room, Script2::Matrix,
                   Script2::Autojects, Script2::File>(args);
}
