/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_library.h
@author  Cale McCollough <cale@astartup.net>
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
#if SEAM >= SCRIPT2_14
#ifndef INCLUDED_SCRIPT2_LIBRARY_T
#define INCLUDED_SCRIPT2_LIBRARY_T
#include "c_onfig.h"

namespace _ {
#if USING_SCRIPT2_TEXT
template <typename TIndex, typename TKey, typename TData, SI4 MaxStackHeight>
class Library : public Operand {
 public:
  /* Creates an empty automata. */
  Library()
      : num_members_(0),
        num_collisions_(0),
        header_size_(0),
        collisions_size_(0),
        data_size_(0) {}

  virtual ~Library() {}

  /* Returns true if the current Book has a hash table. */
  BOL HasHashTable() { return collisions_size_ != 0; }

  /* Gets the number_ of keys in the current scope. */
  SI4 GetBagType() { return 0; }

  /* Gets the number_ of keys in the current scope. */
  SI4 GetNumKeys() { return num_members_; }

  /* Gets the size of the header in bytes. */
  SI4 GetHeaderSize() { return header_size_; }

  /* Gets the data size in bytes. */
  SI4 GetDataSize() { return data_size_; }

  /* Attempts to add the Page data into the CObject at the given BaseAddress.
  @return Returns nil upon success and an error CH1 upon failure. */
  const Op* Add(UI1 type, const CH1* key, void* data) {
    TIndex size_of_type = GetSizeOfType(type);
    if (size_of_type == 0) {
      return 0;
    }
    return 0;
  }

  /* Attempts to insert the Page data into the CObject at the given index.
  @return Returns nil upon success and an error CH1 upon failure. */
  const Op* Insert(UI1 type, const CH1* key, void* data, TIndex index = 0) {
    TIndex l_numOps = numNumbers;
    if (index > l_numOps) index = l_numOps;

    return 0;
  }

  /* Attempts to remove the Page data into the CObject at the given index.
  @return Returns nil upon success and an error CH1 upon failure. */
  const Op* Remove(TIndex index) { return 0; }

  /* Attempts to clear the page at the given index.
  @return Returns nil upon success and an error CH1 upon failure. */
  const Op* Clear(TIndex index) { return 0; }

  /* Attempts to find the given op name.
  @return Returns an invalid index upon failure. */
  TIndex Find(const CH1* key) { return 0; }

  /* Searches for the given query and returns a bag of query results.  */
  BOL Search(const CH1* query,
             Library<TIndex, TKey, TData, TData, MaxStackHeight>* results) {
    return false;
  }

  /* gets the size of the item at the given index. */
  UI1 GetOpSize(TIndex index) { return 0; }

  /* Sets the size of the item to the given index to the new_size. */
  UI1 SetOpSize(TIndex index, TData new_size) { return 0; }

  /* Returns the data address of the given op if it exists.
  @return Returns a pointer to one of the ChineseRoom error strings upon
  failure. */
  void* GetDataAddress(TIndex index) {
#if SCRIPT2_MEMORY_PROFILE >= 64
    Index64* UI8_ptr = (Index64*)address;
#elif SCRIPT2_MEMORY_PROFILE >= 32
    Index32* UI4_ptr = (Index32*)address;
#elif SCRIPT2_MEMORY_PROFILE >= 16
    Index16* UI2_ptr = (Index16*)address;
#elif SCRIPT2_MEMORY_PROFILE != 8
#error Index_t invalid size!
#endif

    Index_t size = 0;

    UI1 type = (*address) & 0x1f;

    UIN array_type = type >> 5;

    switch (array_type) {
      case 0:
#if SCRIPT2_MEMORY_PROFILE >= 16
        /// Library format: { kUI1, kUI1, kUI2, kUI2 }
        return size + sizeof(Library) + *(address + 1) * sizeof(UI1) +
               *(UI2_ptr + 2) + *(UI8_ptr + 4);
#else
        return 0;
#endif
      case 1:
#if SCRIPT2_MEMORY_PROFILE >= 32
        /// Library format: { kUI1, kUI1, kUI2, kUI4 }
        return size + sizeof(Bag32) + *(UI2_ptr + 2) * sizeof(UI1) +
               *(UI4_ptr + 4) + *(UI8_ptr + 8);
#else
        return 0;
#endif
      case 2:
#if SCRIPT2_MEMORY_PROFILE >= 64
        /// Library format: { kUI2, kUI2, kUI4, kUI8 }
        return size + sizeof(Library) + *(UI2_ptr + 2) * sizeof(UI1) +
               *(UI4_ptr + 4) + *(UI8_ptr + 8);
#else
        return 0;
#endif
      case 2: {
        break;
      }
    }
    return 0;
  }

  /* Shrinks the currently selected bag's socket to the min size. */
  void Shrink() {}

  /* Script2 Operations.
  @return       Returns nil upon success, a Set header upon query, and an
  error_t ticket upon Read-Write failure.
  @param index The index of the expression.
  @param crabs  The CCrabs to read and write from. */
  virtual const Op* Star(CHN index, CCrabs* crabs) {
    static const Op kThis = {"Library", OpFirst('A'), OpLast('A'),
                             "",        kOpOperand,   0};

    switch (index) {
      case '?':
        return ExprEnquiry(crabs, kThis);
      case 'A': {
        static const Op This = {"Foo", Params<0>(), Params<0>(), "Foo.",
                                '(',   ')',         nullptr};
        return 0;
      }
      default:
        return 0;
    }
    return 0;
  }

 private:
  // NONCOPYABLE (Library)

  SI4 reserved_;       //< Reserved for 64-bit memory alignment.
  Library** root_;     //< Pointer to the dynamically allocated bags.
  Library* bag_;       //< Currently selected bag.
  SI4 index_,          //< Index of the currently selected bag.
      height_,         //< Number of bags on the stack.
      num_libraries_;  //< Number of libraries.
  UI1 type_;           //< Current type of bag.
  TIndex num_keys_,    //< Current number_ of Star members.
      buffer_size_;    //< Current size of the header and names socket in bytes.
  TKey header_size_,   //< Current size of the header and names in bytes.
      collisions_size_;  //< Current size of the header and names socket in
                         // bytes.
  TData data_size_;      //< Current total size of the bag.
                         // Book<TIndex, TKey, TData, TData> bag;
};

/* Destructs the given bag. */
template <typename TIndex, typename TKey, typename TData, UIN MaxStackSize>
SDK void Delete(Library<TIndex, TKey, TData, TData, MaxStackSize>* r) {
  if (r == nullptr) return;
  delete reinterpret_cast<CH1*>(r);
}
#endif  //< SCRIPT2_MEMORY_PROFILE > 2
}  // namespace _
#endif  //< INCLUDED_SCRIPT2_LIBRARY_T
#endif  //< #if SEAM >= SCRIPT2_14
