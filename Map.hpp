/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Map.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (ISZ) 2015-21 Kabuki Starship <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_MAP_TEMPLATES
#define SCRIPT2_MAP_TEMPLATES
#include <_Config.h>
#if SEAM >= SCRIPT2_MAP
#include "Stack.hpp"
#if SEAM == SCRIPT2_MAP
#include "_Debug.inl"
#define D_COUT_MAP(map) TMapPrint<COut, D, ISZ>(COut().Star(), map)
#else
#include "_Release.inl"
#define D_COUT_MAP(map)
#endif
namespace _ {

/* A sparse array map of Sorted Domain Values to Codomain Mappings (i.e. pointer
offsets).
@see ASCII Data Type Specification.
@link file://./spec/data/map_types/map.md

@code
         Map Memory Layout
+-------------------------------+
|_____   Buffer       ISZ       |
|_____ ^ Y_n        Codomain    |
|      | Y_0        Mappings    |
+-------------------------------+
|_____   Buffer                 |
|_____ ^ X_n     Sorted Domain  |
|      | X_0         Values     |
+-------------------------------+  ^ Up in addresses.
|          TMap Header          |  |
+-------------------------------+ 0x0
@endcode
*/
template <typename ISZ = ISW>
struct TMap {
  ISZ size,   //< Size of the Array in elements.
      count;  //< Element count.
};

/* Utility class for creating an object with the TBUF. */
template <typename D = ISN, typename ISZ = ISW>
struct TMapBuf {
  D domain_value;
  ISZ codomain_value;
};

/* Returns the start of the domain. */
template <typename D = ISN, typename ISZ = ISW>
inline D* TMapDomain(const TMap<ISZ>* map) {
  return TPtr<D>(map, sizeof(TMap<ISZ>));
}
template <typename D = ISN, typename ISZ = ISW>
inline ISZ* TMapDomain(TMap<ISZ>* map, ISZ index) {
  return const_cast<ISZ*>(
      TMapDomain<D, ISZ>(const_cast<const TMap<ISZ>*>(map), index));
}

/* Returns the start of the codomain. */
template <typename D = ISN, typename ISZ = ISW>
inline const ISZ* TMapCodomain(const D* domain, ISZ size) {
  return reinterpret_cast<const ISZ*>(domain + size);
}
template <typename D = ISN, typename ISZ = ISW>
inline ISZ* TMapCodomain(D* domain, ISZ size) {
  return const_cast<ISZ*>(
      TMapCodomain<D, ISZ>(const_cast<const D*>(domain), size));
}

/* Returns the start of the codomain. */
template <typename D = ISN, typename ISZ = ISW>
inline const ISZ* TMapCodomain(const TMap<ISZ>* map, ISZ size) {
  return TMapCodomain<D, ISZ>(TMapDomain<D, ISZ>(map), size);
}
template <typename D = ISN, typename ISZ = ISW>
inline ISZ* TMapCodomain(TMap<ISZ>* map, ISZ size) {
  return const_cast<ISZ*>(
      TMapCodomain<D, ISZ>(const_cast<const TMap<ISZ>*>(map), size));
}

/* Returns the start of the codomain. */
template <typename D = ISN, typename ISZ = ISW>
inline const ISZ* TMapCodomain(const TMap<ISZ>* map) {
  return TMapCodomain<D, ISZ>(map, map->size);
}
template <typename D = ISN, typename ISZ = ISW>
inline ISZ* TMapCodomain(TMap<ISZ>* map) {
  return const_cast<ISZ*>(
      TMapCodomain<D, ISZ>(const_cast<const TMap<ISZ>*>(map)));
}

template <typename D = ISN, typename ISZ = ISW>
inline ISZ TMapMapping(const TMap<ISZ>* map, ISZ index) {
  if (index < 0 || index >= map->count) return nullptr;
  return *(TMapCodomain<D, ISZ>(map) + index);
}
template <typename D = ISN, typename ISZ = ISW>
inline ISZ TMapMapping(TMap<ISZ>* map, ISZ size) {
  return const_cast<ISZ*>(
      TMapCodomain<D, ISZ>(const_cast<const TMap<ISZ>*>(map), size));
}

/* Clears the map by setting the count to zero. */
template <typename ISZ = ISW>
inline void TMapClear(TMap<ISZ>* map) {
  map->count = 0;
}

/* Prints the map to the Printer. */
template <typename Printer, typename D = IUN, typename ISZ = ISW>
Printer& TMapPrint(Printer& o, const TMap<ISZ>* map) {
  enum {
    cSIZColumnWidth = 10,
    cDomainColumns = 26,
    cCodomainColumns = cDomainColumns,
  };

  ISZ size = map->size, count = map->count;

  o << Linef("\n+---\n| TMap<D") << sizeof(D) << ",IS" << CHA('0' + sizeof(ISZ))
    << "> size:" << size << " count:" << count << Linef("\n+---\n|  ")
    << Centerf("i", cSIZColumnWidth)
    << Centerf("Sorted Domain Value", cDomainColumns)
    << Centerf("Codomain Mapping", cDomainColumns) << Linef("\n+---");

  const D* domain = TMapDomain<D, ISZ>(map);
  const ISZ* codomain = TMapCodomain<D, ISZ>(map, size);

  for (ISZ i = 0; i < count; ++i) {
    o << "\n| " << Centerf(i, cSIZColumnWidth)
      << Centerf(*domain++, cDomainColumns)
      << Centerf(*codomain++, cDomainColumns);
  }
#if D_THIS
  return o << Linef("\n+---\n");
  //<< Charsf(map, map->size * sizeof(TMapBuf<D, ISZ>));
#else
  return o << Linef("\n+---");
#endif
}

template <typename D = ISN, typename ISZ = ISW>
constexpr ISZ CMapOverheadPerIndex() {
  return sizeof(D) + sizeof(ISZ);
};

template <typename D = ISN, typename ISZ = ISW>
inline ISZ TMapSizeRequired(ISZ count) {
  return count * CMapOverheadPerIndex + sizeof(TMap<ISZ>);
};

template <typename D = ISN, typename ISZ = ISW>
constexpr ISZ CMapSizeRequired(ISZ count) {
  return count * CMapOverheadPerIndex + sizeof(TMap<ISZ>);
};

template <typename D = ISN, typename ISZ = ISW>
inline TMap<ISZ>* TMapInit(TMap<ISZ>* map, ISZ count) {
  D_ASSERT(map);
  D_ASSERT(count >= 0);
  map->count = 0;
  return map;
}

/* Adds the key to the map.
@return An invalid index upon failure or valid index upon success. */
template <typename D = ISN, typename ISZ = ISW>
ISZ TMapAdd(TMap<ISZ>* map, D domain_value, ISZ codomain_mapping) {
  D_ASSERT(map);
  D_COUT("\n\nAdding:" << domain_value << "->" << codomain_mapping);
  ISZ count = map->count, size = map->size;
  if (count >= size) return CInvalidIndex<ISZ>();
  D* domain = TMapDomain<D, ISZ>(map);
  ISZ* codomain = TMapCodomain<D, ISZ>(domain, size);

  if (count == 0) {
    *domain = domain_value;
    *codomain = codomain_mapping;
    D_COUT("\n  Added the first codomain_mapping:(" << domain_value << ','
                                                    << codomain_mapping << ')');
    map->count = 1;
    D_COUT_MAP(map);
    return count;
  };
  D_COUT("\n\n  Searching for index in the domain... ");
  ISZ low = 0, mid = 0, high = count;
  D current_domain_value = 0;
  while (low <= high) {
    mid = (low + high) >> 1;
    current_domain_value = domain[mid];
    D_COUT("\n     low:" << low << " mid:" << mid << " high:" << high
                         << " domain_value:" << current_domain_value);

    if (current_domain_value > domain_value) {
      high = mid - 1;
    } else if (current_domain_value < domain_value) {
      low = mid + 1;
    } else {
      D_COUT(". The value exists in the domain.");
      return CInvalidIndex<ISZ>();
    }
  }
  if (domain_value > current_domain_value) {
    if (mid == count) {
      *(domain + count) = domain_value;
      *(codomain + count) = codomain_mapping;
      map->count = count + 1;
      D_COUT_MAP(map);
      return count;
    }
    ++mid;
  }
  TStackInsert<D>(domain, count, mid, domain_value);
  TStackInsert<ISZ>(codomain, count, mid, codomain_mapping);
  D_COUT("\n      Inserted domain[mid-1], mid, mid+1]: = ["
         << *(domain + mid - 1) << ", " << *(domain + mid) << ", "
         << *(domain + mid + 1) << ']');
  map->count = count + 1;
  D_COUT_MAP(map);
  return count;
}

/* Returns the size of th map in bytes. */
template <typename D = ISN, typename ISZ = ISW>
constexpr ISZ CMapSizeBytes(ISZ size) {
  return size * (sizeof(D) + sizeof(ISZ)) + sizeof(TMap<ISZ>);
}
template <typename D = ISN, typename ISZ = ISW>
inline ISZ MapSizeBytes(ISZ size) {
  return size * (sizeof(D) + sizeof(ISZ)) + sizeof(TMap<ISZ>);
}

/* Attempts to find the domain_member index.
@return An invalid index upon failure or a valid index upon success. */
template <typename D = ISN, typename ISZ = ISW>
ISZ TMapFind(const TMap<ISZ>* map, const D& domain_member) {
  D_ASSERT(map);
  D_COUT("\nSearching for domain_member:" << domain_member);

  const D* domain = TMapDomain<D, ISZ>(map);
  ISZ count = map->count, size = map->size;
  ISZ low = 0, mid = 0, high = count;
  while (low <= high) {
    mid = (low + high) >> 1;
    D x_i = domain[mid];
    D_COUT("\n   low:" << low << " mid:" << mid << " high:" << high
                       << " x_i:" << x_i);

    if (x_i > domain_member) {
      high = mid - 1;
    } else if (x_i < domain_member) {
      low = mid + 1;
    } else {
      D_COUT(". Hit!");
      return TMapCodomain<D, ISZ>(domain, size)[mid];
    }
  }
  D_COUT("\n  Domain does not contain domain_member.");
  return CInvalidIndex<ISZ>();
}

/* Attempts to find the codomain_mapping index.
@return An invalid index upon failure or a valid index upon success. */
template <typename D = ISN, typename ISZ = ISW>
ISZ TMapFindCodomain(const TMap<ISZ>* map, const ISZ& codomain_mapping) {
  const ISZ* codomain = TMapCodomain<D, ISZ>(map);
  return TArrayFind<ISZ, ISZ>(codomain, map->count, codomain_mapping);
}

/* Remaps the */
template <typename D = ISN, typename ISZ = ISW>
void TMapRemapCodomain(TMap<ISZ>* map, ISZ index, ISZ codomain_mapping) {
  D_ASSERT(map);
  TMapCodomain<D, ISZ>(map)[index] = codomain_mapping;
}
/* Removes the codomain_mapping from the domain to the index in the codomain.
@return An invalid index upon failure or the new size of the map upon success.
*/
template <typename D = ISN, typename ISZ = ISW>
ISZ TMapRemove(TMap<ISZ>* map, ISZ index) {
  if (index < 0 || index >= map->count) return CInvalidIndex<ISZ>();
  ISZ size = map->size, count = map->count, zero = 0;
  if (count == zero)
    if (--count == zero) {
      map->count = zero;
      return zero;
    }
  D* domain = TMapDomain<D, ISZ>(map);
  TStackRemove(domain, index, count);
  ISZ* codomain = TMapCodomain<D, ISZ>(domain, size);

  return 0;
}

/* Inline wrapper for the TMap for stack-to-heap growth.
CMapSizeBytes<D, ISZ>(cSize_)
*/
template <typename D = ISN, typename ISZ = ISW, ISZ cSize_ = 16,
          typename BUF = TBUF<cSize_, TMapBuf<D, ISZ>, ISZ, TMap<ISZ>>>
class AMap {
  AArray<TMapBuf<D, ISZ>, ISZ, BUF> array_;

 public:
  /* Constructs a Map with the given size.
  If size is less than 0 it will be set to the default value. If the
  */
  AMap() : array_() { TMapInit<D, ISZ>(This(), cSize_); }

  /* Destructs the dynamically allocated socket. */
  ~AMap() {}

  /* Gets the sorted domain array. */
  inline D* Domain() { return TMapDomain<D, ISZ>(This()); }

  /* Gets the array of mappings from the domain to the codmain. */
  inline ISZ* Codomain() { return TMapCodomain<D, ISZ>(This()); }

  /* Adds the given domain_member and it's mapped codomain_mapping. */
  inline ISZ Add(D domain_member) {
    return TMapAdd<D, ISZ>(This(), domain_member, Count());
  }

  /* Removes the domain codomain_mapping at the codomain_index. */
  inline ISZ Remove(D domain_member) {
    return TMapRemove<D, ISZ>(This(), domain_member);
  }

  /* Removes the domain codomain_mapping at the codomain_index. */
  inline ISZ RemoveCodomain(ISZ codomain_mapping) {
    return TMapRemove<D, ISZ>(This(), codomain_mapping);
  }

  /* Searches for the domain_member in the domain.
  @return True if the pointer lies in this socket. */
  inline ISZ Find(D domain_member) {
    return TMapFind<D, ISZ>(This(), domain_member);
  }

  /* Searches for the domain_member in the domain.
  @return True if the pointer lies in this socket. */
  inline ISZ FindCodomain(ISZ mapping) {
    return TMapFindCodomain<D, ISZ>(This(), mapping);
  }

  /*
  inline ISZ InsertCodomain(ISZ index, D domain_member, ISZ mapping) {
    return TMapInsertCodomain<D, ISZ>(This(), domain_member,
                                         mapping);
  }*/

  /* Remaps the codomain at the given index to the codomain_mapping. */
  inline void RemapCodomain(ISZ index, ISZ codomain_mapping) {
    return TMapRemapCodomain<D, ISZ>(This(), index, codomain_mapping);
  }

  /* Clears the list. */
  inline void Clear() { TMapClear<D, ISZ>(This()); }

  /* Gets the size of the array in bytes*/
  inline ISZ SizeBytes() { return AJT().SizeBytes<TMap<ISZ>>(); }

  /* Gets the size of the array in CPU words*/
  inline ISZ SizeWords() { return AJT().SizeWords<TMap<ISZ>>(); }

  /* Gets the size of the array in elements*/
  inline ISZ Size() { return This()->size; }

  /* Gets the count of the mappings. */
  inline ISZ Count() { return This()->count; }

  /* Prints this object to a printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TMapPrint<Printer, D, ISZ>(o, This());
  }

  /* Prints This object to the COut. */
  inline COut& CPrint() { return PrintTo<COut>(COut().Star()); }

  /* Gets the aarray_. */
  inline AArray<TMapBuf<D, ISZ>, ISZ, BUF>& AJT() { return array_; }

  /* Gets a pointer to the object at the origin of the aarray_. */
  inline TMap<ISZ>* This() {
    return reinterpret_cast<TMap<ISZ>*>(AJT().Origin());
  }
};
}  //< namespace _
#undef TARGS
#undef TPARAMS

#endif
#endif
