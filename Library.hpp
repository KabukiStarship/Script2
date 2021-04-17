/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Library.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
#ifndef SCRIPT2_LIBRARY_CODE_HEADER
#define SCRIPT2_LIBRARY_CODE_HEADER
namespace _ {
#if USING_SCRIPT2_TEXT
template <typename TIndex, typename TKey, typename TData, ISC MaxStackHeight>
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
  ISC GetBagType() { return 0; }

  /* Gets the number_ of keys in the current scope. */
  ISC GetNumKeys() { return num_members_; }

  /* Gets the size of the header in bytes. */
  ISC GetHeaderSize() { return header_size_; }

  /* Gets the data size in bytes. */
  ISC GetDataSize() { return data_size_; }

  /* Attempts to add the Page data into the AArray at the given BaseAddress.
  @return Returns nil upon success and an error CHA upon failure. */
  const Op* Add(IUA type, const CHA* key, void* data) {
    TIndex size_of_type = GetSizeOfType(type);
    if (size_of_type == 0) {
      return 0;
    }
    return 0;
  }

  /* Attempts to insert the Page data into the AArray at the given index.
  @return Returns nil upon success and an error CHA upon failure. */
  const Op* Insert(IUA type, const CHA* key, void* data, TIndex index = 0) {
    TIndex l_numOps = numNumbers;
    if (index > l_numOps) index = l_numOps;

    return 0;
  }

  /* Attempts to remove the Page data into the AArray at the given index.
  @return Returns nil upon success and an error CHA upon failure. */
  const Op* Remove(TIndex index) { return 0; }

  /* Attempts to clear the page at the given index.
  @return Returns nil upon success and an error CHA upon failure. */
  const Op* Clear(TIndex index) { return 0; }

  /* Attempts to find the given op name.
  @return Returns an invalid index upon failure. */
  TIndex Find(const CHA* key) { return 0; }

  /* Searches for the given query and returns a bag of query results.  */
  BOL Search(const CHA* query,
             Library<TIndex, TKey, TData, TData, MaxStackHeight>* results) {
    return false;
  }

  /* gets the size of the item at the given index. */
  IUA GetOpSize(TIndex index) { return 0; }

  /* Sets the size of the item to the given index to the new_size. */
  IUA SetOpSize(TIndex index, TData new_size) { return 0; }

  /* Returns the data address of the given op if it exists.
  @return Returns a pointer to one of the ChineseRoom error Strings upon
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

    IUA type = (*address) & 0x1f;

    IUN array_type = type >> 5;

    switch (array_type) {
      case 0:
#if SCRIPT2_MEMORY_PROFILE >= 16
        /// Library format: { cIUA, cIUA, cIUB, cIUB }
        return size + sizeof(Library) + *(address + 1) * sizeof(IUA) +
               *(UI2_ptr + 2) + *(UI8_ptr + 4);
#else
        return 0;
#endif
      case 1:
#if SCRIPT2_MEMORY_PROFILE >= 32
        /// Library format: { cIUA, cIUA, cIUB, cIUC }
        return size + sizeof(Bag32) + *(UI2_ptr + 2) * sizeof(IUA) +
               *(UI4_ptr + 4) + *(UI8_ptr + 8);
#else
        return 0;
#endif
      case 2:
#if SCRIPT2_MEMORY_PROFILE >= 64
        /// Library format: { cIUB, cIUB, cIUC, cIUD }
        return size + sizeof(Library) + *(UI2_ptr + 2) * sizeof(IUA) +
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
  @param crabs  The Crabs to read and write from. */
  virtual const Op* Star(CHC index, Crabs* crabs) {
    static const Op cThis = {"Library", OpFirst('A'), OpLast('A'),
                             "",        kOpOperand,   0};

    switch (index) {
      case '?':
        return ExprEnquiry(crabs, cThis);
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

  ISC reserved_;       //< Reserved for 64-bit memory alignment.
  Library** root_;     //< Pointer to the dynamically allocated bags.
  Library* bag_;       //< Currently selected bag.
  ISC index_,          //< Index of the currently selected bag.
      height_,         //< Number of bags on the stack.
      num_libraries_;  //< Number of libraries.
  IUA type_;           //< Current type of bag.
  TIndex num_keys_,    //< Current number_ of Star members.
      buffer_size_;    //< Current size of the header and names socket in bytes.
  TKey header_size_,   //< Current size of the header and names in bytes.
      collisions_size_;  //< Current size of the header and names socket in
                         // bytes.
  TData data_size_;      //< Current total size of the bag.
                         // Book<TIndex, TKey, TData, TData> bag;
};

/* Destructs the given bag. */
template <typename TIndex, typename TKey, typename TData, IUN MaxStaccSize>
LIB_MEMBER void Delete(Library<TIndex, TKey, TData, TData, MaxStaccSize>* r) {
  if (r == nullptr) return;
  delete TPtr<CHA>(r);
}
#endif  //< SCRIPT2_MEMORY_PROFILE > 2
}  // namespace _
#endif
#endif
