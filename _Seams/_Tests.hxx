// Copyright AStarship <https://astarship.net>.
#include <_Config.h>
//
#include "../_Package.hxx"
//
#include "01.COut.hxx"
#include "02.ItoS.hxx"
#include "03.FtoS.hxx"
#include "04.Uniprinter.hxx"
#include "05.Clock.hxx"
#include "06.Array.hxx"
#include "07.Stack.hxx"
#include "08.String.hxx"
#include "09.Loom.hxx"
#include "10.List.hxx"
#include "11.Book.hxx"
#include "12.Map.hxx"
#include "13.Table.hxx"
#include "14.Dic.hxx"
#include "15.MathCore.hxx"
#include "16.RNG.hxx"
#include "17.File.hxx"
#include "18.SGraTe.hxx"
#include "19.CrabsOp.hxx"
#include "20.Room.hxx"
#include "21.CrabsCore.hxx"
#include "22.Release.hxx"
//
#include "../Test.hpp"
using namespace ::_;

inline const CHA* CrabsTests(const CHA* args) {
  return TTestTree<Crabs::COut, Crabs::ItoS, Crabs::FtoS, 
    Crabs::Uniprinter, Crabs::Clock, Crabs::Stack, Crabs::String, 
    Crabs::Loom,  Crabs::List, Crabs::Book, Crabs::Map, Crabs::Table,
    Crabs::Dic, Crabs::MathCore, Crabs::RNG, Crabs::File,
    Crabs::SGraTe, Crabs::CrabsOp, Crabs::Room, 
    Crabs::CrabsCore>(args);
}
