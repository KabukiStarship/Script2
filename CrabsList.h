// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_CRABSLIST_DECL
#define CRABS_CRABSLIST_DECL
#include <_Config.h>
#include "List.hpp"
namespace _ {

/* CrabsList type code — new ASCII Map type for unified List-based stack machine.
This type code identifies a CrabsList (TList-wrapped Crabs stack) in the
ASCII Data Type system. It replaces the old custom CrabsList struct.
*/
enum {
  _CL0 = 100,  //< CrabsList with 1-byte signed int offsets.
  _CL1 = 101,  //< CrabsList with 2-byte signed int offsets.
  _CL2 = 102,  //< CrabsList with 4-byte signed int offsets.
};

/* CrabsList: a TList-wrapped unified Crabs stack machine.
The Crabs machine IS a List of heterogenous Type:Value tuples.
Each stack frame is a (type, value) pair stored in a TList.

This is the Chinese Room Abstract Stack (Crabs) Machine:
a world-champion speed demon, all-contiguous, with optional
dynamic memory via RAMFactory.
*/
template<typename ISZ = ISW, typename ISY = ISZ, typename DT = DTB>
struct CrabsList {
  TList<ISZ, ISY, DT> list;  //< Underlying TList for Type:Value storage.
};

/* Creates a CrabsList from preallocated memory.
@cl       Pointer to preallocated CrabsList memory.
@total    Maximum number of Type:Value tuples.
@bytes    Total bytes available for the CrabsList.
@return   Pointer to initialized CrabsList, or nil on failure.
*/
template<typename ISZ = ISW, typename ISY = ISZ, typename DT = DTB>
CrabsList<ISZ, ISY, DT>* CrabListInit(CrabsList<ISZ, ISY, DT>* cl, ISY total, ISZ bytes);

/* Pushes a Type:Value tuple onto the CrabsList stack.
This is the core stack push operation for the unified Crabs machine.
The value is stored in the TList at the aligned top position.
@cl       Pointer to the CrabsList.
@type     ASCII Data Type code for the value.
@value    Pointer to the value data.
@value_bytes  Number of bytes in the value.
@return   Index of the new entry on the stack, or -1 on failure.
*/
template<typename ISZ = ISW, typename ISY = ISZ, typename DT = DTB>
inline ISY CrabsListPush(CrabsList<ISZ, ISY, DT>* cl, DT type, void* value, ISZ value_bytes);

/* Pops the top Type:Value tuple off the CrabsList stack.
This is the core stack pop operation for the unified Crabs machine.
It decrements the count but does NOT clear the value data.
@cl   Pointer to the CrabsList.
@return Pointer to the popped value, or nullptr if stack is empty.
*/
template<typename ISZ = ISW, typename ISY = ISZ, typename DT = DTB>
inline void* CrabsListPop(CrabsList<ISZ, ISY, DT>* cl);

/* Peeks at the top Type:Value tuple without removing it.
@cl   Pointer to the CrabsList.
@return TATypeValue containing the type and offset of the top element.
        Returns {0, 0} if the stack is empty.
*/
template<typename ISZ = ISW, typename ISY = ISZ, typename DT = DTB>
inline TATypeValue<ISZ, DT> CrabsListPeek(const CrabsList<ISZ, ISY, DT>* cl);

/* Gets the Type:Value tuple at a given index.
@cl       Pointer to the CrabsList.
@index    Index of the element to retrieve.
@return   TATypeValue containing the type and offset of the element.
          Returns {0, 0} if the index is out of bounds.
*/
template<typename ISZ = ISW, typename ISY = ISZ, typename DT = DTB>
inline TATypeValue<ISZ, DT> CrabsListGet(const CrabsList<ISZ, ISY, DT>* cl, ISY index);

/* Clears the CrabsList stack (resets count, keeps data).
The values section is NOT wiped — only the count is reset.
@cl   Pointer to the CrabsList.
*/
template<typename ISZ = ISW, typename ISY = ISZ, typename DT = DTB>
inline void CrabsListClear(CrabsList<ISZ, ISY, DT>* cl);

/* Returns the number of Type:Value tuples on the stack.
@cl   Pointer to the CrabsList.
@return Count of elements on the stack.
*/
template<typename ISZ = ISW, typename ISY = ISZ, typename DT = DTB>
inline ISY CrabsListCount(const CrabsList<ISZ, ISY, DT>* cl);

/* Returns true if the CrabsList is empty (count == 0).
@cl   Pointer to the CrabsList.
@return true if empty, false otherwise.
*/
template<typename ISZ = ISW, typename ISY = ISZ, typename DT = DTB>
inline BOL CrabsListEmpty(const CrabsList<ISZ, ISY, DT>* cl);

/* Returns the minimum bytes needed for a CrabsList with the given total.
This includes the TList struct header, offsets array, and types array.
@total   Maximum number of Type:Value tuples.
@return   Minimum bytes required.
*/
template<typename ISZ = ISW, typename ISY = ISZ, typename DT = DTB>
inline ISZ CrabsListBytesMin(ISY total);

/* Prints the CrabsList to a printer.
@o      Reference to the printer output stream.
@cl     Pointer to the CrabsList.
@return Reference to the printer after printing.
*/
template<typename Printer, typename ISZ = ISW, typename ISY = ISZ, typename DT = DTB>
Printer& CrabsListPrint(Printer& o, const CrabsList<ISZ, ISY, DT>* cl);

}  // namespace _

#endif
