// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_DIC_TEMPLATES
#define SCRIPT2_DIC_TEMPLATES
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
#include "Table.hpp"
#if SEAM == SCRIPT2_DIC
#include "_Debug.hxx"
#else
#include "_Release.hxx"
#endif
namespace _ {
/* @ingroup Dic
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/MapTypes/Dictionary.md */
#define DIC_A \
  typename CHT = CHR, typename ISZ = ISR, typename ISY = ISQ, \
  typename DT = DTB, typename HSH = IUN
#define DIC_P CHT, ISZ, ISY, DT, HSH

/* @ingroup Dic
@brief A contiguous memory Associative List created from a List and a Table.
@code
+-----------------+
|      List       |
|-----------------|
|      Table      |
|-----------------|  ^ Up in addresses
|  TDic Struct    |  |
+-----------------+ 0xN
@endcode */
template<DIC_A>
struct TDic {
  TList<LST_P> values;  //< A list of values with a Table of keys in index 0.
};

#define DIC TDic<CHT, ISZ, ISY, DT, HSH>

/* The minimum count a good with the given template parameters can have. */
template<DIC_A>
constexpr ISY CDicMinCount() {
  return 8 / sizeof(ISZ);
}

enum {
  // The number of bits to shift a Dic's bytes right by to calculate the 
  // size_keys (Example: size_keys = bytes >> 2).
  DicDefaultKeysFractionShift = -1,
  // The number of bits to shift a Dic's bytes right by to calculate the 
  // total (Example: total = bytes >> 5).
  DicDefaultTotalFractionShift = -6,
  DicDefaultLengthKey = 15,
  DicDefaultSizeBytes = 1024,
  DicDefaultCount = DicDefaultSizeBytes >> -(DicDefaultKeysFractionShift),
};

/* The minimum size of a Dic based on the CCountMin. */
template<DIC_A>
constexpr ISZ CDicMinSize() {
  enum {
    SizeMin = sizeof(DIC) + CDicMinCount<DIC_P>() * (sizeof(ISZ) + 2),
  };
  return SizeMin;
}

/* Gets the default count of a good with the given template parameters. */
template<DIC_A>
constexpr ISY CDicDefaultCount() {
  return 32;
}

/* Gets the default size of a Dic with the CDicCountDefault. */
template<DIC_A>
constexpr ISZ CDicDefaultSize() {
  return (32 * CDicDefaultCount<DIC_P>() * sizeof(CHT)) & (sizeof(ISW) - 1);
}

/* Points to the base of the value offsets array. */
template<DIC_A>
inline ISZ* TDicValuesMap(DIC* dic) {
  return TListValuesMap<LST_P>(&dic->values);
}
template<DIC_A>
inline const ISZ* TDicValuesMap(const DIC* dic) {
  return CPtr<ISZ>(TDicValuesMap<DIC_P>(CPtr<DIC>(dic)));
}

/* Gets the keys Table (index 0 of the ASCII List). */
template<DIC_A>
inline TBL* TDicKeys(DIC* dic) {
  return TPtr<TBL>(dic, *TDicValuesMap<DIC_P>(dic));
}
template<DIC_A>
inline const TBL* TDicKeys(const DIC* dic) {
  return CPtr<TBL>(TDicKeys<DIC_P>(CPtr<DIC>(dic)));
}

/* Gets the values List. */
template<DIC_A>
inline ISZ* TDicKeysMap(DIC* dic) {
  return TTableKeysMap<TBL_P>(TDicKeys<DIC_P>(dic));
}
template<DIC_A>
inline const ISZ* TDicKeysMap(const DIC* dic) {
  return CPtr<ISZ>(TDicKeysMap<DIC_P>(CPtr<DIC>(dic)));
}

/* Gets the start of the dic as a templated-defined character. */
template<DIC_A>
inline CHT* TDicStart(DIC* dic, ISY total) {
  ISZ* top = &TStackStart<ISZ, ISZ>(&dic->offsets)[total];
  return TPtr<CHT>(top);
}
template<DIC_A>
inline const ISZ* TDicStart(const DIC* dic, ISY total) {
  return CPtr<ISZ>(TDicStart<DIC_P>(CPtr<DIC>(dic), total));
}

/* Gets the start byte. */
template<DIC_A>
inline CHT* TDicStart(DIC* dic) {
  return TDicStart<DIC_P>(dic, dic->offsets.total);
}
template<DIC_A>
inline const ISZ* TDicStart(const DIC* dic) {
  return CPtr<ISZ>(TDicStart<DIC_P>(CPtr<DIC>(dic)));
}
template<DIC_A>
inline CHA* TDicEnd(DIC* dic) {
  return TListEnd<ISZ>(&dic->values);
}
template<DIC_A>
inline const ISZ* TDicEnd(const DIC* dic) {
  return CPtr<ISZ>(TDicEnd<DIC_P>(CPtr<DIC>(dic)));
}

/* Checks if the dic size values result are valid.
You must have enough room in the bytes with given total. */
template<DIC_A>
inline BOL TDicSizesAreValid(ISZ bytes, ISZ size_keys, ISY total) {
  return size_keys <= TListSizeFreeMax<LST_P>(bytes, total);
}

// Freespace left in bytes for the given dic's keys Table and values List.
// @return Returns -1 upon failure.
template<DIC_A>
inline ISZ TDicFreeSpace(const DIC* dic) {
  auto keys = TDicKeys<DIC_P>(dic);
  if (!keys) return -1;
  return TListFreeSpace<LST_P>(&dic->values) + TTableFreeSpace<TBL_P>(keys);
}

/* Prints the dic to the printer. */
template<typename Printer, DIC_A>
Printer& TDicPrint(Printer& o, const DIC* dic) {
  auto total       = ISY(dic->values.map.total);
  auto count       = ISY(dic->values.map.count);
  auto item_map    = TPtr<ISZ>(dic, sizeof(DIC));
  auto types       = TPtr<DT>(item_map + total);
  auto keys_offset = *item_map++;
  const TBL* keys  = TPtr<TBL>(dic, keys_offset);
  auto keys_size   = keys->bytes;
  D_COUT("\ntotal:" << total << " count:" << count <<
    " keys_size:" << keys_size);
  D_AVOW(total, ISY(keys->map.total));
  D_AVOW(count, ISY(keys->map.count));
  const ISZ* keys_map = TTableKeysMap<TBL_P>(keys, total);
  o << Linef("\n+---\n| Dic<CH") << CSizeCodef<CHT>() 
    << ",IS" << CSizeCodef<ISZ>() << ",IS"
    << CSizeCodef<ISY>() << "> bytes:" << dic->values.bytes
    << " total:" << total << " count:" << count 
    << Linef("\n+---\n| list_top:") << dic->values.top
    << " values_free_space:" << TListFreeSpace<ISZ>(&dic->values)
    << " TypeOf(keys):" << ATypef(types[0])
    << "\n| keys_offset:" << keys_offset
    << " keys_free_space:" << TTableFreeSpace<TBL_P>(keys)
    << " keys.bytes:" << keys_size;
  for (ISY i = 1; i < count; ++i) {
    o << "\n| " << i << ".) \"" << TPtr<CHT>(keys_map, keys_map[i]) << "\" type:";
    auto type = *(++types);
    auto voffset = *(++item_map);
    o << ATypef(type) << " voffset:" << voffset << " value:";
  }
  D_COUT(Linef("\n+---") << ' ' << Charsf(dic, dic->values.bytes));
  return o << '\n';
}
/* Prints the dic to the printer. */
template<typename Printer, DIC_A>
Printer& TDicPrintStruct(Printer& o, const DIC* dic) {
  auto total = ISY(dic->values.map.total);
  auto count = ISY(dic->values.map.count);
  auto voffsets = TPtr<ISZ>(dic, sizeof(DIC));
  auto types = TPtr<DT>(voffsets + total);
  auto keys_offset = *voffsets++;
  const TBL* keys = TPtr<TBL>(dic, keys_offset);
  auto keys_size = keys->bytes;
  D_COUT("\ntotal:" << total << " count:" << count <<
    " keys_size:" << keys_size);
  o << "\nDIC<CH" << CSizeCodef<CHT>() << ",IS" << CSizeCodef<ISZ>() << ",IS"
    << CSizeCodef<ISY>() << "> bytes:" << dic->values.bytes
    << " total:" << total << " count:" << count << '\n'
    << " list_top:" << dic->values.top << " keys_offset:" << keys_offset
    << " keys_free_space:" << TTableFreeSpace<TBL_P>(keys)
    << " values_free_space:" << TListFreeSpace<ISZ>(&dic->values)
    << " keys.bytes:" << keys_size << " TypeOf(keys):" << ATypef(types[0])
    << '\n';
  return o;
}

/* ASCII Data Type for the given templated DIC.
We are mapping an offset to a CH type, and thus the VT bits are 0.
@todo Look into if VT bits should be 0 and not
| b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
|:-------:|:------:|:-----:|:-----:|:-----:|
|   MOD   |   MT   |  SW   |  VT   |  POD  |
1. POD: Plain Old Data bits.
2. VT : Vector Type bits.
3. SW : Size Width bits.
4. MT : Map Type bits.
5. MOD: Modifier bits. */
template<DIC_A>
constexpr DTB CTableKeysType() {
  enum {
    PODBits = CATypeIS<ISY>() << ATypeMTBit0,
    VTBits  = 1 << ATypeVTBit0,
    SWBits  = CBitCount<ISZ>() << ATypeSWBit0,
    MTBits  = CATypeCH<CHR, DT>()
  };
  return MTBits | SWBits | VTBits | PODBits;
}

/* Initializes the dic to the given total using the CDicSizeDefault. */
template<DIC_A>
inline DIC* TDicInit(DIC* dic,
                     ISY total = DicDefaultTotalFractionShift,
                     ISZ size_keys = DicDefaultKeysFractionShift) {
  D_ASSERT(dic);
  TList<LST_P>* values = &dic->values;
  ISZ bytes = values->bytes;
  D_COUT("\n\nTDicInit bytes: " << bytes << " total:" <<
    total << " size_keys:" << size_keys);
  D_ARRAY_WIPE(TPtr<>(dic, sizeof(DIC)), bytes - sizeof(DIC));
  if (size_keys < 0) {
    size_keys *= -1;
    if (size_keys >= TBitCount<ISZ>()) {
      D_COUT("\nInvalid total bit shift value.");
      return nullptr;
    }
    size_keys = bytes >> size_keys;
    D_COUT("\nnew size_keys:" << size_keys);
  }
  if (total < 0) {
    total *= -1;
    if (total >= TBitCount<ISZ>()) {
      D_COUT("\nInvalid total bit shift value.");
      return nullptr;
    }
    total = ISY(bytes >> ISZ(total));
    D_COUT("\nnew total:" << total);
  }
  if (!TDicSizesAreValid<DIC_P>(bytes, size_keys, total)) {
    D_COUT("\nInvalid dic sizes!");
    return nullptr;
  }
  TListInit<LST_P>(values, bytes, total);
  DTB KeysType = CTableKeysType<TBL_P>();
  ISY keys_index = TListAlloc<LST_P>(values, KeysType, size_keys);
  D_AVOW(ISY(0), keys_index);
  TBL* keys = TListValue<LST_P, TBL>(values, keys_index);
  D_COUT("\nkeys_index  :" << keys_index <<
         "\nkeys offset : " << TDelta<>(dic, keys) <<
         "\nKeysType:0b" << Binaryf(KeysType) << ' ' << ATypef(KeysType) <<
         "\nvalue_offsets_delta:" << TDelta<>(dic, TDicValuesMap<DIC_P>(dic)) <<
         "\nkeys_delta:" << TDelta<>(dic, keys) << 
         " size_bytes_found:" << *TPtr<ISZ>(keys));
  if (!keys) {
    D_COUT("\nTable Keys too large to fit in list! size_keys:" << size_keys);
    return nullptr;
  }
  auto result = TTableInit<TBL_P>(keys, total);
  if (!PtrIsValid(result))
    D_RETURN_TPTR_ERROR(DIC, result);
  TTableAppend<TBL_P>(keys, TStringEmpty<CHT>());
  D_COUT("\nTDelta<>(dic, TDicKeys<DIC_P>(dic)):" <<
    TDelta<>(dic, TDicKeys<DIC_P>(dic)));
  if (!result) return nullptr;
  D_COUT("\n\nTListInit Post bytes: " << bytes <<
    " total:" << total <<
    "\nTable End :" << TDelta<>(dic, TDicEnd<DIC_P>(dic)) <<
    "\nKeys End  :" << TDelta<>(dic, TTableEnd<TBL_P>(keys)) <<
    "\nKeys Start:" << TDelta<>(dic, keys) << "\n\nResult:\n");
  D_COUT_DIC(dic);
  return dic;
}

/* Gets the byte after the end of the DIC's contiguous memory block. */
template<DIC_A>
inline TList<LST_P>* TDicValue(DIC* dic, ISZ bytes) {
  return TPtr<TList<LST_P>>(dic, bytes);
}
template<DIC_A>
inline TList<LST_P>* TDicValue(DIC* dic) {
  return TDicValue<DIC_P>(dic, dic->keys.bytes);
}

/* Gets the TypeValue tuple the given index.
@param tuple Reference to the return type passed in by reference. */
template<DIC_A>
inline ATypeValue TDicATypeValue(const DIC* table, ISY index) {
  return TListTypeValuePtr<ISZ, DT>(&table->values, index);
}

template<DIC_A>
inline DT* TDicTypes(DIC* table, ISY total) {
  return TListTypes<LST_P>(&table->values, total);
}
template<DIC_A>
inline const DT* TDicTypes(const DIC* table, ISY total) {
  return CPtr<DT>(TDicTypes<DIC_P>(CPtr<DIC>(table), total));
}


/* Gets the key at the given index without doing any error checking. */
template<DIC_A>
inline CHT* TDicKey_NC(DIC* table, ISY index) {
  return TTableGet_NC<TBL_P>(TDicKeys<DIC_P>(table), index);
}

/* Gets the key at the given index without doing any error checking. */
template<DIC_A>
inline const CHT* TDicKey_NC(const DIC* table, ISY index) {
  return CPtr<CHT>(TDicKey_NC<TBL_P>(CPtr<DIC>(table), index));
}

/* Gets the keys offsets array. */
template<DIC_A>
inline CHT* TDicKeys_NC(DIC* table, ISY index) {
  return TPtr<CHT>(table, *TPtr<ISZ>(table, sizeof(DIC)));
}
template<DIC_A>
inline const CHT* TDicKeys_NC(const DIC* table) {
  auto bok = CPtr<DIC>(TDicKeys<DIC_P>(table));
  return CPtr<CHT>(TDicKeys_NC<TBL_P>(bok));
}

/* Gets the type at the given index without doing any error checking. */
template<DIC_A>
inline DT TDicType_NC(const DIC* table, ISY total, ISY index) {
  return TListType_NC<LST_P>(&table->values, total, index);
}

/* Gets the keys offsets array. */
template<DIC_A>
inline DT* TDicTypes_NC(DIC* table, ISY total) {
  return TPtr<DT>(table, TDicKeys_NC<DIC_P>(table) + total);
}
template<DIC_A>
inline const CHT* TDicTypes_NC(const DIC* table) {
  auto bok = CPtr<DIC>(TDicValuesMap<DIC_P>(table));
  return CPtr<CHT>(TDicTypes_NC<TBL_P>(bok));
}

/* Gets the type at the given index without doing any error checking. */
template<DIC_A>
inline void* TDicValue_NC(DIC* table, ISY index) {
  return TListValue_NC<LST_P>(&table->values, index);
}
template<DIC_A>
inline const void* TDicValue_NC(const DIC* table, ISY index) {
  return CPtr<void>(TDicValue_NC<DIC_P>(CPtr<DIC>(table), index));
}

/* Gets the type at the given index without doing any error checking. */
template<DIC_A>
inline ISZ TDicValueOffset_NC(const DIC* table, ISY index) {
  //return TListValueOffset_NC<LST_P>(&table->values, index);
  return TPtr<ISZ>(table, sizeof(DIC))[index];
}

/* Gets the TypeValue tuple the given index.
@param tuple Reference to the return type passed in by reference. */
template<DIC_A>
inline TATypeKV<ISZ, DT, CHT> TDicTypeKV(const DIC* table, ISY index) {
  auto count = table->values.map.count;
  if (index < 0 || index >= count)
    return { nullptr, _NIL, 0 };
  return { TDicKey_NC<DIC_P>(table, index),
           TDicType_NC<DIC_P>(table, table->values.map.total, index),
           TDicValueOffset_NC<DIC_P>(table, index) };
}

/* Adds a key-value tuple to the end of the Dic.
@todo Delete this function and replace with void* value.
@return The index upon success or -1 upon failure. */
template<typename T, DIC_A>
inline ISY TDicInsert(DIC* table, TBL* keys, const CHT* key,
  T item) {
  D_CHECK_PTR_TRETURN2(ISY, table, key);
  D_COUT("\nAdding key:\"" << key << "\" item:" << item << "\nKeys offset:" << 
         TDelta<>(table, keys) << "\nValues offsets:" << 
         TDelta<>(table, TDicValuesMap<DIC_P>(table)));
  ISY tbl_index = TTableAppend<TBL_P>(keys, key);
  if (tbl_index < 0) {
    D_COUT("\n\n\nFailed to insert into table:" << tbl_index << ' ' <<
      CrabsErrorSTR(tbl_index));
    D_COUT_TABLE(keys);
    D_COUT_DIC(table);
    return -ErrorKeysBooferOverflow;
  }
  ISY index = TListInsert<LST_P>(&table->values, item);
  if (index < 0) {
    D_COUT("\nFailed to insert into List with error " << index << ':' <<
      CrabsErrorSTR(-index));
    D_COUT_LIST(&table->values);
    D_COUT("\n\nList memory: &table->values.bytes:" << *&table->values.bytes <<
      '\n' << Charsf(&table->values, &table->values.bytes));
    TTableRemove<TBL_P>(keys, index);
  }
  return tbl_index;
}
template<typename T, DIC_A>
inline ISY TDicInsert(DIC* table, const CHT* key, T item,
  ISY index = PSH) {
  return TDicInsert<T, DIC_P>(table, TDicKeys<DIC_P>(table), key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, TBL* keys, const CHT* key,
  ISA item) {
  return TDicInsert<ISA, DIC_P>(table, keys, key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, const CHT* key, ISA item) {
  return TDicInsert<ISA, DIC_P>(table, TDicKeys<DIC_P>(table), key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, TBL* keys, const CHT* key,
  IUA item) {
  return TDicInsert<ISA, DIC_P>(table, keys, key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, const CHT* key, IUA item) {
  return TDicInsert<ISA, DIC_P>(table, TDicKeys<DIC_P>(table), key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, TBL* keys, const CHT* key,
  ISB item) {
  return TDicInsert<ISB, DIC_P>(table, keys, key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, const CHT* key, ISB item) {
  return TDicInsert<ISB, DIC_P>(table, TDicKeys<DIC_P>(table), key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, TBL* keys, const CHT* key,
  IUB item) {
  return TDicInsert<ISB, DIC_P>(table, keys, key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, const CHT* key, IUB item) {
  return TDicInsert<ISB, DIC_P>(table, TDicKeys<DIC_P>(table), key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, TBL* keys, const CHT* key,
  ISC item) {
  return TDicInsert<ISC, DIC_P>(table, keys, key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, const CHT* key, ISC item) {
  return TDicInsert<ISC, DIC_P>(table, TDicKeys<DIC_P>(table), key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, TBL* keys, const CHT* key,
  IUC item) {
  return TDicInsert<ISC, DIC_P>(table, keys, key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, const CHT* key, IUC item) {
  return TDicInsert<ISC, DIC_P>(table, TDicKeys<DIC_P>(table), key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, TBL* keys, const CHT* key,
  ISD item) {
  return TDicInsert<ISD, DIC_P>(table, keys, key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, const CHT* key, ISD item) {
  return TDicInsert<ISD, DIC_P>(table, TDicKeys<DIC_P>(table), key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, TBL* keys, const CHT* key, IUD item) {
  return TDicInsert<IUD, DIC_P>(table, keys, key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, const CHT* key, IUD item) {
  return TDicInsert<IUD, DIC_P>(table, TDicKeys<DIC_P>(table), key, item);
}
#if USING_FPC == YES_0
template<DIC_A>
inline ISY TDicInsert(DIC* table, TBL* keys, const CHT* key,
  FPC item) {
  return TDicInsert<FPC, DIC_P>(table, keys, key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, const CHT* key, FPC item) {
  return TDicInsert<FPC, DIC_P>(table, TDicKeys<DIC_P>(table), key, item);
}
#endif
#if USING_FPD == YES_0
template<DIC_A>
inline ISY TDicInsert(DIC* table, TBL* keys, const CHT* key,
  FPD item) {
  return TDicInsert<FPD, DIC_P>(table, keys, key, item);
}
template<DIC_A>
inline ISY TDicInsert(DIC* table, const CHT* key, FPD item) {
  return TDicInsert<FPD, DIC_P>(table, TDicKeys<DIC_P>(table), key, item);
}
#endif

/* Adds a key-value tuple to the end of the Dic.
@return The index upon success or -1 upon failure. */
template<DIC_A>
inline ISY TDicInsertFrom(DIC* table, TBL* keys, const CHT* key,
  DT type, const void* value, ISY index = PSH) {
  D_COUT("\nAdding \"" << key << "\" type:" << ATypef(type) << ":0d" << type <<
    ":0x" << Hexf(type) << ":\'" << CHA(type) << "\' value(offset):" <<
    TDelta<>(table, value));
  auto key_index = TTableAppend<TBL_P>(keys, key);
  if (key_index < 0) {
    SCRIPT2_FAIL();
    return key_index;
  }
  auto result = TListInsert<LST_P>(&table->values, type, value);
  if (result < 0) {
    TTableRemove<TBL_P>(keys, key_index);
    SCRIPT2_FAIL();
  }
  D_COUT_DIC(table);
  return key_index;
}
template<DIC_A>
inline ISY TDicInsertFrom(DIC* table, TBL* keys,
    const CHT* key, DT type, ISZ value_offset, ISY index = PSH) {
  return TDicInsert<DIC_P>(table, keys, key, type,
    TPtr<>(&table->values, value_offset), index);
}
template<DIC_A>
inline ISY TDicInsertFrom(DIC* table, const CHT* key, DT type,
    const void* value, ISY index = PSH) {
  return TDicInsert<DIC_P>(table, TDicKeys<DIC_P>(table), key, type,
    value, index);
}
template<DIC_A>
inline ISY TDicInsertFrom(DIC* table, const CHT* key, DT type,
  ISZ value_offset, ISY index = PSH) {
  return TDicInsert<DIC_P>(table, TDicKeys<DIC_P>(table), key, type,
    value_offset, index);
}

template<DIC_A>
inline ISY TDicInsert(DIC* table, TATypeKV<ISZ, DT, CHT> item,
  ISY index = PSH) {
  return TDicInsert<DIC_P>(table, item.key, item.tv.type,
    TPtr<>(table, item.tv.value));
}

/* Adds all of the items from the source to the table. */
template<DIC_A>
DIC* TDicAppend(DIC* table, const DIC* source) {
  auto src_values = &source->values;
  auto src_size = src_values->bytes;
  auto src_top = src_values->top;
  ISY src_total = ISY(src_values->map.total),
    src_count = ISY(src_values->map.count);
  D_COUT("\nAdding " << src_count << " of " << src_total <<
         " max items...\nsource:\n");
  D_COUT_DIC(source);
  D_ASSERT(src_count >= 0 && src_count <= src_total && src_top > 0);
  const TBL* src_keys = TDicKeys<DIC_P>(source);
  const ISZ* src_keys_map = TDicKeysMap<DIC_P>(source);
  const ISZ* src_values_map = TDicValuesMap<DIC_P>(source) + 1;
  const DT* src_types = TDicTypes<DIC_P>(source, src_total) + 1;
  TBL* keys = TDicKeys<DIC_P>(table);
#if SEAM == SCRIPT2_CRABS
  TDicPrint<COut, DIC_P>(StdOut(), source);
  StdOut() << "\nsrc_size:" << src_size;
#endif
  for (ISY i = 1; i < src_count; ++i) {
    D_COUT("\n\ni:" << i);
    const CHT* key = TPtr<CHT>(src_keys_map, *(src_keys_map + i));
    ISZ value_offset = *src_values_map++;
#if SEAM == SCRIPT2_CRABS
    StdOut() << "\nvalue_offset:" << value_offset;
#endif
    DT  type   = *src_types++;
    ISY result = TDicInsertFrom<DIC_P>(table, keys, key, type,
      TPtr<>(&table->values, value_offset));
    const CHA* dez_nutz = TAErrors<CHA, ISY>(result);
    D_COUT("\nResult:" << result << ' ' << (result < 0 ? dez_nutz : " "));
    D_ASSERT(result >= 0);
  }
  return table;
}

/* Doubles the size and total of the table.
@return Returns nil if the size is greater than the amount of memory that
can fit in type ISW, the unaltered socket pointer if the Stack has grown to the
size upper bounds, or a new dynamically allocated socket upon failure. */
template<DIC_A>
BOL TDicGrow(Autoject& obj) {
  D_COUT("\n\nGrowing Dic...");
  /* Grow Algoirhm.
  1. Check if we can grow and if so, create a new block of memory.
  2. Copy the Table.
  3. Copy the List. */
  auto origin = obj.origin;
  D_ASSERT(origin);
  auto source = TPtr<DIC>(origin);
  auto bytes  = source->values.bytes;
  auto top    = source->values.top;
  ISY  total  = ISY(source->values.map.total),
       count  = ISY(source->values.map.count);
  D_COUT("\nsize:" << bytes << " top:" << top << " total:" << total <<
    " count:" << count);
  auto bytes_new = ATypeGrow(bytes);
  if (!ATypeCanGrow(bytes, bytes_new)) {
    D_COUT("\n\nError: keys_size cannot grow! keys_size:" << bytes <<
      " keys_size_new:" << bytes_new);
    return false;
  }
  auto total_new = ATypeGrow(total);
  if (!ATypeCanGrow(total, total_new)) {
    D_COUT("\n\nError: total cannot grow! count:" << total <<
      " total_new:" << total_new);
    return false;
  }
  auto keys_size = TDicKeys<DIC_P>(source)->bytes;
  auto keys_size_new = ATypeGrow(keys_size);
  if (!ATypeCanGrow(keys_size, keys_size_new)) {
    D_COUT("\n\nError: keys_size cannot grow! keys_size:" << keys_size <<
      " keys_size_new:" << keys_size_new);
    return false;
  }

  IUW* origin_new = obj.ram(nullptr, bytes_new);
  D_COUT("\n\n*TPtr<ISZ>(origin_new):" << *TPtr<ISZ>(origin_new) <<
    " size_new:" << bytes_new);
  auto destination = TPtr<DIC>(origin_new);
  //D_OBJ_WIPE(TPtr<ISZ>(origin_new));
  TDicInit<DIC_P>(destination, total_new, keys_size_new);
  TDicAppend<DIC_P>(destination, source);
  obj.origin = origin_new;
  D_COUT("\n\nFinished growing. :-)\n\n");
  D_COUT_TABLE(TDicKeys<DIC_P>(TPtr<DIC>(origin_new)));
  return true;
}

/* Adds a string to the end of the Dic, auto-growing if neccissary.
@return The index upon success or -1 if the obj can't grow anymore.
@todo Verify copmile size of this function isolated and in the AArray class. */
template<typename T, DIC_A, typename BUF>
ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, T item,
  ISY index = PSH) {
  D_CHECK_PTR_TRETURN(ISY, key);
  auto table = obj.OriginAs<DIC*>();
  ISY result = TDicInsert<T, DIC_P>(table, key, item, index);
  while (result < 0) {
    if (!TDicGrow<DIC_P>(obj.AJT())) {
      D_RETURNT(ISY, -ErrorBooferOverflow);
    }
    table = obj.OriginAs<DIC*>();
    result = TDicInsert<T, DIC_P>(table, key, item, index);
    if (result < 0) {
      D_COUT("\n\n\nFailed to insert into table:" << result << ' ' <<
        CrabsErrorSTR(result));
      auto keys = TDicKeys<DIC_P>(TPtr<DIC>(obj.This()));
      D_COUT_TABLE(keys);
    }
    D_COUT("\ndez nutz baby!!!\n");
  }
  return result;
}
template<DIC_A, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISA item,
  ISY index) {
  return TDicInsert<ISA, DIC_P, BUF>(obj, key, item, index);
}
template<DIC_A, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUA item,
  ISY index) {
  return TDicInsert<IUA, DIC_P, BUF>(obj, key, item, index);
}
template<DIC_A, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISB item,
  ISY index) {
  return TDicInsert<ISB, DIC_P, BUF>(obj, key, item, index);
}
template<DIC_A, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUB item,
  ISY index) {
  return TDicInsert<IUB, DIC_P, BUF>(obj, key, item, index);
}
template<DIC_A, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISC item,
  ISY index = PSH) {
  return TDicInsert<ISC, DIC_P, BUF>(obj, key, item, index);
}
template<DIC_A, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUC item,
  ISY index = PSH) {
  return TDicInsert<IUC, DIC_P, BUF>(obj, key, item, index);
}
template<DIC_A, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, ISD item,
  ISY index = PSH) {
  return TDicInsert<ISD, DIC_P, BUF>(obj, key, item, index);
}
template<DIC_A, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, IUD item,
  ISY index = PSH) {
  return TDicInsert<IUD, DIC_P, BUF>(obj, key, item, index);
}
#if USING_FPC == YES_0
template<DIC_A, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, FPC item,
  ISY index = PSH) {
  return TDicInsert<FPC, DIC_P, BUF>(obj, key, item, index);
}
#endif
#if USING_FPD == YES_0
template<DIC_A, typename BUF>
inline ISY TDicInsert(AArray<IUA, ISZ, BUF>& obj, const CHT* key, FPD item,
  ISY index = PSH) {
  return TDicInsert<FPD, DIC_P, BUF>(obj, key, item, index);
}
#endif

/* Removes the given index from the Dic.
@return The index upon success or -1 upon failure. */
template<DIC_A>
void* TDicListRemove(DIC* dic, ISY index) {
  if (index < 1) return nullptr;
  TList<LST_P>* list = &dic->values;
  ISY count = ISY(list->map.count);
  ISZ* offsets = TListValuesMap<ISZ>(list);
  TStackRemove<ISZ, ISZ>(offsets, count, index);
  TStackRemove<DTB, ISZ>(TListTypes<ISZ, DTB>(list), count, index);
  TTableRemove<TBL_P>(TDicKeys<DIC_P>(dic), index);
  return offsets + index;
}

/* Removes the given index from the Dic.
@return The index upon success or -1 upon failure. */
template<DIC_A>
void* TDicRemove(DIC* table, ISY index) {
  ISY result = TTableRemove<TBL_P>(TDicKeys<DIC_P>(table), index);
  if (!result) return nullptr;
  return TDicListRemove<DIC_P>(table, index);
}

/* Removes the given key from the Dic.
@return Nil upon failure or a pointer to the item removed upon success. */
template<DIC_A>
void* TDicRemove(DIC* table, const CHT* key) {
  ISY index = TTableFind<TBL_P>(TDicKeys<DIC_P>(table), key);
  if (index < 0) return index;
  TTableRemove<TBL_P>(TDicKeys<DIC_P>(table), index);
  return TDicListRemove<DIC_P>(table, index);
}

/* Adds a string to the end of the Dic.
@return The index upon success or -1 upon failure. */
template<DIC_A>
ISZ TDicPop(DIC* table) {
  return TDicRemove<DIC_P>(table, TDicKeys<DIC_P>(table).map.count - 1);
}

template<DIC_A, typename BUF>
ISZ TDicCharCount(DIC* table) {
  return (ISZ)(TDicEnd<DIC_P>(table) - TDicStart<DIC_P>(table));
}
template<DIC_A, typename BUF>
BOL TDicWrite(DIC* destination, DIC* soure) {
  return true;
}

/* Adds a string to the end of the Dic.
@return The index upon success or -1 upon failure. */
template<DIC_A>
CHT* TDicPop(DIC* table) {
  if (TDicKeys<DIC_P>(table).count == 0) return nullptr;
  ISZ offset = TStackPop<ISZ, ISZ>(TDicKeys<DIC_P>(table)), top = table->top;
  table->top = offset;
  return TPtr<CHT>(ISW(table) + offset);
}

/* Searches for the given string in the table.
@return -1 if the table doesn't contain the string or the index if it does. */
template<DIC_A>
ISY TDicFind(DIC* table, const CHT* string) {
  return TTableFind<TBL_P>(TDicKeys<DIC_P>(table), string);
}

/* An ASCII Dic Autoject.
@code
ADic<DIC_A, 1024, TBuf<>>
@endcode */
template<DIC_A, ISZ SizeInit = 512,
  typename BUF = TBUF<SizeInit, CHT, ISZ, TString<ISN>>>
class ADic {
  AArray<IUA, ISZ, BUF> obj_;  //< An Auto-Array object.
public:

  static constexpr DTB Type() {
    enum {
      //PODBits = _NIL,
      VTBits = 1 << ATypeVTBit0,
      SWBits = CBitCount<ISZ>() << ATypeSWBit0,
      MTBits = CATypeCH<ISY>() << ATypeMTBit0
    };
    return MTBits | SWBits | VTBits; // | PODBits;
  }
  enum {
    SizeBytesDefault = CDicDefaultSize<DIC_P>(),
    TotalDefault = SizeBytesDefault >> -DicDefaultTotalFractionShift,
    BitchWhat_DEZ_NUTZ_BABY = Type()
  };

  ADic(ISY total = DicDefaultTotalFractionShift,
    ISZ size_keys = DicDefaultKeysFractionShift)
    : obj_(SizeInit, TRAMFactory<Type(), ISZ>().Init<BUF>()) {
    TDicInit<DIC_P>(This(), total, size_keys);
  }

  /* Constructs a Dic on the Heap.
  @param factory RAMFactory to call when the String overflows. */
  ADic(RAMFactory ram,
    ISY total = DicDefaultTotalFractionShift,
    ISZ size_keys = DicDefaultKeysFractionShift)
    : obj_(ram) {
    TDicInit<DIC_P>(This(), total);
  }

  /* Returns the size in elements. */
  inline ISZ Size() { return obj_.Size(); }

  /* Shorthand way to get the TDic->keys List. */
  inline TList<LST_P>* Values() { return &This()->values; }

  /* Gets the Keys struct. */
  inline TBL* Keys() { return TDicKeys<DIC_P>(This()); }

  /* Returns the size in bytes. */
  inline ISZ Bytes() { return Values()->bytes; }

  /* Returns the size in words. */
  inline ISZ BytesWords() { return obj_.SizeWords() >> WordSizeLog2; }

  /* Returns the number of keys. */
  inline ISZ Count() { return Values()->map.count; }

  /* Returns the maximum number of keys. */
  inline ISZ Total() { return Values()->map.total; }

  /* Inserts the key and item on into the Table and List at the given index.
  @return The index of the string in the Dic. */
  inline ISY Insert(const CHT* key, ISA item, ISY index = PSH) {
    return TDicInsert<DIC_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUA item, ISY index = PSH) {
    return TDicInsert<DIC_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISB item, ISY index = PSH) {
    return TDicInsert<DIC_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUB item, ISY index = PSH) {
    return TDicInsert<DIC_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISC item, ISY index = PSH) {
    return TDicInsert<DIC_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUC item, ISY index = PSH) {
    return TDicInsert<DIC_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, ISD item, ISY index = PSH) {
    return TDicInsert<DIC_P, BUF>(AJT_ARY(), key, item, index);
  }
  inline ISY Insert(const CHT* key, IUD item, ISY index = PSH) {
    return TDicInsert<DIC_P, BUF>(AJT_ARY(), key, item, index);
  }
#if USING_FPC == YES_0
  inline ISY Insert(const CHT* key, FPC item, ISY index = PSH) {
    return TDicInsert<DIC_P, BUF>(AJT_ARY(), key, item, index);
  }
#endif
#if USING_FPD == YES_0
  inline ISY Insert(const CHT* key, FPD item, ISY index = PSH) {
    return TDicInsert<DIC_P, BUF>(AJT_ARY(), key, item, index);
  }
#endif
  inline ISY Insert(const CHT* key, const CHT* item, ISY index = PSH) {
    return TDicInsert<DIC_P, BUF>(AJT_ARY(), key, item, index);
  }

  /* Removes the string at the given index from the Dic. */
  inline void* Remove(ISY index) { return TDicRemove<DIC_P>(This(), index); }

  /* Removes the string at the given index from the Dic. */
  inline void* Remove(const CHT* key) {
    return TDicRemove<DIC_P>(This(), key);
  }

  /* Removes the string at the given index from the Dic. */
  inline ISZ Pop() { return TDicRemove<DIC_P>(This()); }

  /* Gets the string at the given index. */
  inline CHT* Get(ISY index) { return TDicATypeValue<DIC_P>(This(), index); }

  /* Searches for the given string.
  @return -1 if the Dic doesn't contain the string or the index if it does. */
  inline ISY Find(const CHT* string) {
    return TDicFind<DIC_P>(This(), string);
  }

  /* Gets the Autoject. */
  inline Autoject AJT() { return obj_.AJT(); }

  /* Gets the Auto-Array. */
  inline AArray<IUA, ISZ, BUF>& AJT_ARY() { return obj_; }

  /* Gets the ASCII Object. */
  inline DIC* This() { return obj_.OriginAs<DIC*>(); }

  /* Prints this object to the Printer. */
  template<typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TDicPrint<Printer, DIC_P>(o, This());
  }

  /* Prints this object to the stdout. */
  inline void COut() { PrintTo<_::COut>(_::StdOut()); }
};

}  //< namespace _
#endif
#endif
