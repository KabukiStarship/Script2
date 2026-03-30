// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_AUTOJECT_DECL
#define CRABS_AUTOJECT_DECL
#include <_Config.h>
#if SEAM >= CRABS_UNIPRINTER

/* RAMFactory manages memory for ASCII Objects.
@return A word-aligned boofer, rounding up if unaligned.
@param origin Origin of a contiguous auto-object.
@param bytes  Autoject size in bytes. */
typedef IUW* (*RAMFactory)(IUW* origin, ISW bytes);

namespace _ {

/* Automatic object contains the ASCII Object and RAMFactory that auto-grows 
from Stack-to-heap.
Both the RAMFactory Stack or Heap can create dynamic memory, but the 
RAMFactory Stack doesn't delete the memory, as it's on the program stack,creates
and the RAMFactory Heap deletes the dynamic memory. This allows a DLL to produce 
the memory and the EXE to consume it, and vice versa.
*/
struct Autoject {
  IUW* origin;    //< Pointer to the Autoject.
  RAMFactory ram; //< Autoject RAM Factory for managing memory.
};

enum RAMFactoryFunction {
  RAMFactoryDelete = 0, //< Factory function deletes an OBJ.
  RAMFactoryNew    = 1, //< Factory function checks if the size can double.
  RAMFactoryFunctionCount = 2,  //< Factory function count.
};

enum RAMFactoryError {
  RAMFactorySuccess = 0,     //< Factory operation completed successfully error.
  RAMFactoryNil = 1,         //< Factory missing error.
  RAMFactoryNilOBJ = 2,      //< Factory found nil obj.origin pointer error.
  RAMFactoryNilArg = 3,      //< Factory arg nil error.
  FactoryCantGrow = 4,       //< Factory can't grow.
  RAMFactorySizeInvalid = 5, //< Factory size invalid.
  RAMFactoryErrorCount = 6,  //< Factory function count.
};

/* RAMFactory for Autojects on the program stack that doesn't delete the
boofer. */
IUW* ObjectFactoryStack(IUW* boofer, ISW bytes);

/* RAMFactory for Autojects on the heap that deletes a the boofer. */
IUW* ObjectFactoryHeap(IUW* boofer, ISW bytes);

/* RAMFactory for Auto-array of total elements on the program stack that 
doesn't delete the boofer. */
IUW* ArrayFactoryStackA(IUW* boofer, ISW total);

/* RAMFactory for Auto-array of total elements on the heap that deletes a the 
boofer. */
IUW* ArrayFactoryHeapA(IUW* boofer, ISW total);

/* RAMFactory for Auto-array of total elements on the program stack that
doesn't delete the boofer. */
IUW* ArrayFactoryStackB(IUW* boofer, ISW total);

/* RAMFactory for Auto-array of total elements on the heap that deletes a the
boofer. */
IUW* ArrayFactoryHeapB(IUW* boofer, ISW total);

/* RAMFactory for Auto-array of total elements on the program stack that
doesn't delete the boofer. */
IUW* ArrayFactoryStackC(IUW* boofer, ISW total);

/* RAMFactory for Auto-array of total elements on the heap that deletes a the
boofer. */
IUW* ArrayFactoryHeapC(IUW* boofer, ISW total);

/* RAMFactory for Auto-array of total elements on the program stack that
doesn't delete the boofer. */
IUW* ArrayFactoryStackD(IUW* boofer, ISW total);

/* RAMFactory for Auto-array of total elements on the heap that deletes a the
boofer. */
IUW* ArrayFactoryHeapD(IUW* boofer, ISW total);

}  //< namespace _
#endif
#endif
