/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /t_map.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (SIZ) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_MAP
#ifndef INCLUDED_CRAPS_TMAP
#define INCLUDED_CRAPS_TMAP

#include "t_stack.h"

#if SEAM == SCRIPT2_MAP
#include "module_debug.inl"
#define D_COUT_MAP(map) TMapPrint<COut, D, SIZ>(COut().Star(), map)
#else
#include "module_release.inl"
#define D_COUT_MAP(map)
#endif

namespace _ {

/* A sparse array map of Sorted Domain Values to Codomain Mappings.
@see ASCII Data Type Specification.
@link file://./spec/data/map_types/map.md

@code
         Map Memory Layout
+-------------------------------+
|_____   Buffer       SIZ       |
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
template <typename SIZ = SIW>
struct TMap {
  SIZ size,   //< Size of the Array in elements.
      count;  //< Element count.
};

/* Utility class for creating an object with the TUIB. */
template <typename D = SIN, typename SIZ = SIW>
struct TMapBuf {
  D domain_value;
  SIZ codomain_value;
};

/* Returns the start of the domain. */
template <typename D = SIN, typename SIZ = SIW>
inline D* TMapDomain(const TMap<SIZ>* map) {
  return TPtr<D>(map, sizeof(TMap<SIZ>));
}
template <typename D = SIN, typename SIZ = SIW>
inline SIZ* TMapDomain(TMap<SIZ>* map, SIZ index) {
  return const_cast<SIZ*>(
      TMapDomain<D, SIZ>(const_cast<const TMap<SIZ>*>(map), index));
}

/* Returns the start of the codomain. */
template <typename D = SIN, typename SIZ = SIW>
inline const SIZ* TMapCodomain(const D* domain, SIZ size) {
  return reinterpret_cast<const SIZ*>(domain + size);
}
template <typename D = SIN, typename SIZ = SIW>
inline SIZ* TMapCodomain(D* domain, SIZ size) {
  return const_cast<SIZ*>(
      TMapCodomain<D, SIZ>(const_cast<const D*>(domain), size));
}

/* Returns the start of the codomain. */
template <typename D = SIN, typename SIZ = SIW>
inline const SIZ* TMapCodomain(const TMap<SIZ>* map, SIZ size) {
  return TMapCodomain<D, SIZ>(TMapDomain<D, SIZ>(map), size);
}
template <typename D = SIN, typename SIZ = SIW>
inline SIZ* TMapCodomain(TMap<SIZ>* map, SIZ size) {
  return const_cast<SIZ*>(
      TMapCodomain<D, SIZ>(const_cast<const TMap<SIZ>*>(map), size));
}

/* Returns the start of the codomain. */
template <typename D = SIN, typename SIZ = SIW>
inline const SIZ* TMapCodomain(const TMap<SIZ>* map) {
  return TMapCodomain<D, SIZ>(map, map->size);
}
template <typename D = SIN, typename SIZ = SIW>
inline SIZ* TMapCodomain(TMap<SIZ>* map) {
  return const_cast<SIZ*>(
      TMapCodomain<D, SIZ>(const_cast<const TMap<SIZ>*>(map)));
}

template <typename D = SIN, typename SIZ = SIW>
inline SIZ TMapMapping(const TMap<SIZ>* map, SIZ index) {
  if (index < 0 || index >= map->count) return nullptr;
  return *(TMapCodomain<D, SIZ>(map) + index);
}
template <typename D = SIN, typename SIZ = SIW>
inline SIZ TMapMapping(TMap<SIZ>* map, SIZ size) {
  return const_cast<SIZ*>(
      TMapCodomain<D, SIZ>(const_cast<const TMap<SIZ>*>(map), size));
}

/* Clears the map by setting the count to zero. */
template <typename SIZ = SIW>
inline void TMapClear(TMap<SIZ>* map) {
  map->count = 0;
}

/* Prints the map to the Printer. */
template <typename Printer, typename D = UIN, typename SIZ = SIW>
Printer& TMapPrint(Printer& o, const TMap<SIZ>* map) {
  enum {
    kSIZColumnWidth = 10,
    kDomainColums = 26,
    kCodomainColumns = kDomainColums,
  };

  SIZ size = map->size, count = map->count;

  o << Linef("\n+---\n| TMap<D") << sizeof(D) << ",SI" << CH1('0' + sizeof(SIZ))
    << "> size:" << size << " count:" << count << Linef("\n+---\n|  ")
    << Centerf("i", kSIZColumnWidth)
    << Centerf("Sorted Domain Value", kDomainColums)
    << Centerf("Codomain Mapping", kDomainColums) << Linef("\n+---");

  const D* domain = TMapDomain<D, SIZ>(map);
  const SIZ* codomain = TMapCodomain<D, SIZ>(map, size);

  for (SIZ i = 0; i < count; ++i) {
    o << "\n| " << Centerf(i, kSIZColumnWidth)
      << Centerf(*domain++, kDomainColums)
      << Centerf(*codomain++, kDomainColums);
  }
#if D_THIS
  return o << Linef("\n+---\n");
  //<< Charsf(map, map->size * sizeof(TMapBuf<D, SIZ>));
#else
  return o << Linef("\n+---");
#endif
}

template <typename D = SIN, typename SIZ = SIW>
constexpr SIZ TMapOverheadPerIndex() {
  return sizeof(D) + sizeof(SIZ);
};

template <typename D = SIN, typename SIZ = SIW>
inline SIZ TMapSizeRequired(SIZ count) {
  return count * TMapOverheadPerIndex + sizeof(TMap<SIZ>);
};

template <typename D = SIN, typename SIZ = SIW>
constexpr SIZ CMapSizeRequired(SIZ count) {
  return count * TMapOverheadPerIndex + sizeof(TMap<SIZ>);
};

template <typename D = SIN, typename SIZ = SIW>
inline TMap<SIZ>* TMapInit(TMap<SIZ>* map, SIZ count) {
  D_ASSERT(map);
  D_ASSERT(count >= 0);
  map->count = 0;
  return map;
}

/* Adds the key to the map.
@return An invalid index upon failure or valid index upon success. */
template <typename D = SIN, typename SIZ = SIW>
SIZ TMapAdd(TMap<SIZ>* map, D domain_value, SIZ codomain_mapping) {
  D_ASSERT(map);
  D_COUT("\n\nAdding:" << domain_value << "->" << codomain_mapping);
  SIZ count = map->count, size = map->size;
  if (count >= size) return CInvalidIndex<SIZ>();
  D* domain = TMapDomain<D, SIZ>(map);
  SIZ* codomain = TMapCodomain<D, SIZ>(domain, size);

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
  SIZ low = 0, mid = 0, high = count;
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
      return CInvalidIndex<SIZ>();
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
  TStackInsert<SIZ>(codomain, count, mid, codomain_mapping);
  D_COUT("\n      Inserted domain[mid-1], mid, mid+1]: = ["
         << *(domain + mid - 1) << ", " << *(domain + mid) << ", "
         << *(domain + mid + 1) << ']');
  map->count = count + 1;
  D_COUT_MAP(map);
  return count;
}

/* Returns the size of th map in bytes. */
template <typename D = SIN, typename SIZ = SIW>
constexpr SIZ CMapSizeBytes(SIZ size) {
  return size * (sizeof(D) + sizeof(SIZ)) + sizeof(TMap<SIZ>);
}
template <typename D = SIN, typename SIZ = SIW>
inline SIZ TMapSizeBytes(SIZ size) {
  return size * (sizeof(D) + sizeof(SIZ)) + sizeof(TMap<SIZ>);
}

/* Attempts to find the domain_member index.
@return An invalid index upon failure or a valid index upon success. */
template <typename D = SIN, typename SIZ = SIW>
SIZ TMapFind(const TMap<SIZ>* map, const D& domain_member) {
  D_ASSERT(map);
  D_COUT("\nSearching for domain_member:" << domain_member);

  const D* domain = TMapDomain<D, SIZ>(map);
  SIZ count = map->count, size = map->size;
  SIZ low = 0, mid = 0, high = count;
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
      return TMapCodomain<D, SIZ>(domain, size)[mid];
    }
  }
  D_COUT("\n  Domain does not contain domain_member.");
  return CInvalidIndex<SIZ>();
}

/* Attempts to find the codomain_mapping index.
@return An invalid index upon failure or a valid index upon success. */
template <typename D = SIN, typename SIZ = SIW>
SIZ TMapFindCodomain(const TMap<SIZ>* map, const SIZ& codomain_mapping) {
  const SIZ* codomain = TMapCodomain<D, SIZ>(map);
  return TArrayFind<SIZ, SIZ>(codomain, map->count, codomain_mapping);
}

/* Remaps the */
template <typename D = SIN, typename SIZ = SIW>
void TMapRemapCodomain(TMap<SIZ>* map, SIZ index, SIZ codomain_mapping) {
  D_ASSERT(map);
  TMapCodomain<D, SIZ>(map)[index] = codomain_mapping;
}
/* Removes the codomain_mapping from the domain to the index in the codomain.
@return An invalid index upon failure or the new size of the map upon success.
*/
template <typename D = SIN, typename SIZ = SIW>
SIZ TMapRemove(TMap<SIZ>* map, SIZ index) {
  if (index < 0 || index >= map->count) return CInvalidIndex<SIZ>();
  SIZ size = map->size, count = map->count, zero = 0;
  if (count == zero)
    if (--count == zero) {
      map->count = zero;
      return zero;
    }
  D* domain = TMapDomain<D, SIZ>(map);
  TStackRemove(domain, index, count);
  SIZ* codomain = TMapCodomain<D, SIZ>(domain, size);

  return 0;
}

/* Inline wrapper for the TMap for stack-to-heap growth.
CMapSizeBytes<D, SIZ>(kSize_)
*/
template <typename D = SIN, typename SIZ = SIW, SIZ kSize_ = 16,
          typename BUF = TUIB<kSize_, TMapBuf<D, SIZ>, SIZ, TMap<SIZ>>>
class AMap {
  AArray<TMapBuf<D, SIZ>, SIZ, BUF> array_;

 public:
  /* Constructs a Map with the given size.
  If size is less than 0 it will be set to the default value. If the
  */
  AMap() : array_() { TMapInit<D, SIZ>(This(), kSize_); }

  /* Destructs the dynamically allocated socket. */
  ~AMap() {}

  /* Gets the sorted domain array. */
  inline D* Domain() { return TMapDomain<D, SIZ>(This()); }

  /* Gets the array of mappings from the domain to the codmain. */
  inline SIZ* Codomain() { return TMapCodomain<D, SIZ>(This()); }

  /* Adds the given domain_member and it's mapped codomain_mapping. */
  inline SIZ Add(D domain_member) {
    return TMapAdd<D, SIZ>(This(), domain_member, Count());
  }

  /* Removes the domain codomain_mapping at the codomain_index. */
  inline SIZ Remove(D domain_member) {
    return TMapRemove<D, SIZ>(This(), domain_member);
  }

  /* Removes the domain codomain_mapping at the codomain_index. */
  inline SIZ RemoveCodomain(SIZ codomain_mapping) {
    return TMapRemove<D, SIZ>(This(), codomain_mapping);
  }

  /* Searches for the domain_member in the domain.
  @return True if the pointer lies in this socket. */
  inline SIZ Find(D domain_member) {
    return TMapFind<D, SIZ>(This(), domain_member);
  }

  /* Searches for the domain_member in the domain.
  @return True if the pointer lies in this socket. */
  inline SIZ FindCodomain(SIZ mapping) {
    return TMapFindCodomain<D, SIZ>(This(), mapping);
  }

  /*
  inline SIZ InsertCodomain(SIZ index, D domain_member, SIZ mapping) {
    return TMapInsertCodomain<D, SIZ>(This(), domain_member,
                                         mapping);
  }*/

  /* Remaps the codomain at the given index to the codomain_mapping. */
  inline void RemapCodomain(SIZ index, SIZ codomain_mapping) {
    return TMapRemapCodomain<D, SIZ>(This(), index, codomain_mapping);
  }

  /* Clears the list. */
  inline void Clear() { TMapClear<D, SIZ>(This()); }

  /* Gets the size of the array in bytes*/
  inline SIZ SizeBytes() { return AJT().SizeBytes<TMap<SIZ>>(); }

  /* Gets the size of the array in CPU words*/
  inline SIZ SizeWords() { return AJT().SizeWords<TMap<SIZ>>(); }

  /* Gets the size of the array in elements*/
  inline SIZ Size() { return This()->size; }

  /* Gets the count of the mappings. */
  inline SIZ Count() { return This()->count; }

  /* Prints this object to a printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TMapPrint<Printer, D, SIZ>(o, This());
  }

  /* Prints This object to the COut. */
  inline COut& CPrint() { return PrintTo<COut>(COut().Star()); }

  /* Gets the aarray_. */
  inline AArray<TMapBuf<D, SIZ>, SIZ, BUF>& AJT() { return array_; }

  /* Gets a pointer to the object at the origin of the aarray_. */
  inline TMap<SIZ>* This() {
    return reinterpret_cast<TMap<SIZ>*>(AJT().Begin());
  }
};
}  // namespace _

#endif
#endif
