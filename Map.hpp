/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Map.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (ISZ) 2015-2023 Kabuki Starship <kabukistarship.com>;
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
#else
#include "_Release.inl"
#endif
namespace _ {

#undef  MAP_P
#define MAP_P D, ISZ
#undef  MAP_A
#define MAP_A typename D = ISR, typename ISZ = ISR

/* A sparse array map of Sorted Domain Values to Codomain Mappings (i.e. pointer
offsets).
@see ASCII Data Type Specification.
@link file://./_Spec/Data/MapTypes/Map.md

@code
         Map Memory Layout
+-------------------------------+
|_____   Boofer       ISZ       |
|_____ ^ Y_n        Codomain    |
|      | Y_0        Mappings    |
+-------------------------------+
|_____   Boofer                 |
|_____ ^ X_n     Sorted Domain  |
|      | X_0         Values     |
+-------------------------------+  ^ Up in addresses.
|          TMap Header          |  |
+-------------------------------+ 0x0
@endcode
*/
template<MAP_A>
struct TMap {
  ISZ size,   //< Size of the Array in elements.
      count;  //< Element count.
};

/* Utility class for creating an object with the TBUF. */
template<MAP_A>
struct TMapBuf {
  D   domain_value;   //< 
  ISZ codomain_value; //< 
};

/* Returns the start of the domain. */
template<MAP_A>
inline D* TMapDomain(TMap<MAP_P>* map) {
  return TPtr<D>(map, sizeof(TMap<MAP_P>));
}
template<MAP_A>
inline const D* TMapDomain(const TMap<MAP_P>* map) {
  return CPtr<D>(TMapDomain<MAP_P>(CPtr<TMap<MAP_P>>(map)));
}

/* Returns the start of the domain. */
template<MAP_A>
inline D TMapDomain_NC(TMap<MAP_P>* map, ISZ index) {
  return TPtr<D>(map, sizeof(TMap<MAP_P>))[index];
}
template<MAP_A>
inline const D TMapDomain_NC(const TMap<MAP_P>* map, ISZ index) {
  return CPtr<D>(TMapDomain_NC<MAP_P>(CPtr<TMap<MAP_P>>(map), index));
}

/* Returns the start of the codomain. */
template<MAP_A>
inline const ISZ* TMapCodomain(const D* domain, ISZ size) {
  return TPtr<const ISZ>(domain + size);
}
template<MAP_A>
inline ISZ* TMapCodomain(D* domain, ISZ size) {
  return const_cast<ISZ*>(
      TMapCodomain<MAP_P>(const_cast<const D*>(domain), size));
}

/* Returns the start of the codomain. */
template<MAP_A>
inline const ISZ* TMapCodomain(const TMap<MAP_P>* map, ISZ size) {
  return TMapCodomain<MAP_P>(TMapDomain<MAP_P>(map), size);
}
template<MAP_A>
inline ISZ* TMapCodomain(TMap<MAP_P>* map, ISZ size) {
  return const_cast<ISZ*>(
      TMapCodomain<MAP_P>(const_cast<const TMap<MAP_P>*>(map), size));
}

/* Returns the start of the codomain. */
template<MAP_A>
inline const ISZ* TMapCodomain(const TMap<MAP_P>* map) {
  return TMapCodomain<MAP_P>(map, map->size);
}
template<MAP_A>
inline ISZ* TMapCodomain(TMap<MAP_P>* map) {
  return const_cast<ISZ*>(
      TMapCodomain<MAP_P>(const_cast<const TMap<MAP_P>*>(map)));
}

template<MAP_A>
inline ISZ TMapMapping(const TMap<MAP_P>* map, ISZ index) {
  if (index < 0 || index >= map->count) return nullptr;
  return *(TMapCodomain<MAP_P>(map) + index);
}
template<MAP_A>
inline ISZ TMapMapping(TMap<MAP_P>* map, ISZ size) {
  return const_cast<ISZ*>(
      TMapCodomain<MAP_P>(const_cast<const TMap<MAP_P>*>(map), size));
}

/* Clears the map by setting the count to zero. */
template<MAP_A>
inline void TMapClear(TMap<MAP_P>* map) {
  map->count = 0;
}

/* Prints the map to the Printer. */
template<typename Printer, MAP_A>
Printer& TMapPrint(Printer& o, const TMap<MAP_P>* map) {
  enum {
    ColumnWidth = 10,
    DomainColumns = 26,
    CodomainColumns = DomainColumns,
  };

  ISZ size = map->size, count = map->count;

  o << Linef("\n+---\n| TMap<D") << sizeof(D) << ",IS" << CHA('0' + sizeof(ISZ))
    << "> size:" << size << " count:" << count << Linef("\n+---\n|  ")
    << Centerf("i", ColumnWidth)
    << Centerf("Sorted Domain Value", DomainColumns)
    << Centerf("Codomain Mapping", DomainColumns) << Linef("\n+---");

  const D* domain = TMapDomain<MAP_P>(map);
  const ISZ* codomain = TMapCodomain<MAP_P>(map, size);

  for (ISZ i = 0; i < count; ++i) {
    o << "\n| " << Centerf(i, ColumnWidth)
      << Centerf(*domain++, DomainColumns)
      << Centerf(*codomain++, DomainColumns);
  }
#if D_THIS
  return o << Linef("\n+---\n");
  //<< Charsf(map, map->size * sizeof(TMapBuf<MAP_P>));
#else
  return o << Linef("\n+---");
#endif
}

template<MAP_A>
constexpr ISZ CMapOverheadPerIndex() {
  return sizeof(D) + sizeof(ISZ);
};

template<MAP_A>
inline ISZ TMapSizeRequired(ISZ count) {
  return count * CMapOverheadPerIndex + sizeof(TMap<MAP_P>);
};

template<MAP_A>
constexpr ISZ CMapSizeRequired(ISZ count) {
  return count * CMapOverheadPerIndex + sizeof(TMap<MAP_P>);
};

template<MAP_A>
inline TMap<MAP_P>* TMapInit(TMap<MAP_P>* map, ISZ count) {
  D_ASSERT(map);
  D_ASSERT(count >= 0);
  map->count = 0;
  return map;
}

/* Adds the key to the map.
@return An invalid index upon failure or valid index upon success. */
template<MAP_A>
ISZ TMapAdd(TMap<MAP_P>* map, D domain_value, ISZ codomain_mapping) {
  D_ASSERT(map);
  D_COUT("\n\nAdding:" << domain_value << "->" << codomain_mapping);
  ISZ count = map->count, size = map->size;
  if (count >= size) D_RETURNT(ISZ, -ErrorBooferOverflow);
  D  * domain   = TMapDomain<MAP_P>(map);
  ISZ* codomain = TMapCodomain<MAP_P>(domain, size);

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
      return CAInvalidIndex<ISZ>();
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
  D_COUT(" mid:" << mid);
  TArrayInsert_NC<D, SCK_P>(domain, count, mid, domain_value);
  TArrayInsert_NC<ISZ, SCK_P>(codomain, count, mid, codomain_mapping);
  D_COUT("\n      Inserted domain[mid-1], mid, mid+1]: = [" << 
         *(domain + mid - 1) << ", " << *(domain + mid) << ", " << 
         *(domain + mid + 1) << ']');
  map->count = count + 1;
  D_COUT_MAP(map);
  return count;
}

/* Returns the size of th map in bytes. */
template<MAP_A>
constexpr ISZ CMapSizeBytes(ISZ size) {
  return size * (sizeof(D) + sizeof(ISZ)) + sizeof(TMap<MAP_P>);
}
template<MAP_A>
inline ISZ TMapSizeBytes(ISZ size) {
  return size * (sizeof(D) + sizeof(ISZ)) + sizeof(TMap<MAP_P>);
}

/* Attempts to find the domain_member index.
@return An invalid index upon failure or a valid index upon success. */
template<MAP_A>
ISZ TMapFind(const TMap<MAP_P>* map, const D& domain_member) {
  D_ASSERT(map);
  D_COUT("\nSearching for domain_member:" << domain_member);

  const D* domain = TMapDomain<MAP_P>(map);
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
      return TMapCodomain<MAP_P>(domain, size)[mid];
    }
  }
  D_COUT("\n  Domain does not contain domain_member.");
  return CAInvalidIndex<ISZ>();
}

/* Attempts to find the codomain_mapping index.
@return An invalid index upon failure or a valid index upon success. */
template<MAP_A>
inline ISZ TMapFindCodomain(const TMap<MAP_P>* map, const ISZ& codomain_mapping) {
  const ISZ* codomain = TMapCodomain<MAP_P>(map);
  return TArrayFind<ISZ, ISZ>(codomain, map->count, codomain_mapping);
}

/* Remaps the */
template<MAP_A>
inline void TMapRemapCodomain(TMap<MAP_P>* map, ISZ index, ISZ codomain_mapping) {
  D_ASSERT(map);
  TMapCodomain<MAP_P>(map)[index] = codomain_mapping;
}

/* Removes the codomain_mapping from the domain to the index in the codomain.
@return An invalid index upon failure or the new size of the map upon success.
*/
template<MAP_A>
ISZ TMapRemove(TMap<MAP_P>* map, ISZ index) {
  if (index < 0 || index >= map->count) D_RETURNT(ISZ, -ErrorInvalidIndex);
  ISZ size = map->size, count = map->count, zero = 0;
  if (count == zero)
    if (--count == zero) {
      map->count = zero;
      return zero;
    }
  D* domain = TMapDomain<MAP_P>(map);
  TStackRemove(domain, index, count);
  ISZ* codomain = TMapCodomain<MAP_P>(domain, size);

  return 0;
}

/* Inline wrapper for the TMap for stack-to-heap growth.
CMapSizeBytes<MAP_P>(Size_)
*/
template<MAP_A, ISZ Size_ = 16,
          typename BUF = TBUF<Size_, TMapBuf<MAP_P>, ISZ, TMap<MAP_P>>>
class AMap {
  AArray<TMapBuf<MAP_P>, ISZ, BUF> array_;

 public:
  /* Constructs a Map with the given size.
  If size is less than 0 it will be set to the default value. If the
  */
  AMap() : array_() { TMapInit<MAP_P>(This(), Size_); }

  /* Destructs the dynamically allocated socket. */
  ~AMap() {}

  /* Gets the sorted domain array. */
  inline D* Domain() { return TMapDomain<MAP_P>(This()); }

  /* Gets the array of mappings from the domain to the codmain. */
  inline ISZ* Codomain() { return TMapCodomain<MAP_P>(This()); }

  /* Adds the given domain_member and it's mapped codomain_mapping. */
  inline ISZ Add(D domain_member) {
    return TMapAdd<MAP_P>(This(), domain_member, Count());
  }

  /* Removes the domain codomain_mapping at the codomain_index. */
  inline ISZ Remove(D domain_member) {
    return TMapRemove<MAP_P>(This(), domain_member);
  }

  /* Removes the domain codomain_mapping at the codomain_index. */
  inline ISZ RemoveCodomain(ISZ codomain_mapping) {
    return TMapRemove<MAP_P>(This(), codomain_mapping);
  }

  /* Searches for the domain_member in the domain.
  @return True if the pointer lies in this socket. */
  inline ISZ Find(D domain_member) {
    return TMapFind<MAP_P>(This(), domain_member);
  }

  /* Searches for the domain_member in the domain.
  @return True if the pointer lies in this socket. */
  inline ISZ FindCodomain(ISZ mapping) {
    return TMapFindCodomain<MAP_P>(This(), mapping);
  }

  /*
  inline ISZ InsertCodomain(ISZ index, D domain_member, ISZ mapping) {
    return TMapInsertCodomain<MAP_P>(This(), domain_member,
                                         mapping);
  }*/

  /* Remaps the codomain at the given index to the codomain_mapping. */
  inline void RemapCodomain(ISZ index, ISZ codomain_mapping) {
    return TMapRemapCodomain<MAP_P>(This(), index, codomain_mapping);
  }

  /* Clears the list. */
  inline void Clear() { TMapClear<MAP_P>(This()); }

  /* Gets the size of the array in bytes*/
  inline ISZ SizeBytes() { return AJT().SizeBytes<TMap<MAP_P>>(); }

  /* Gets the size of the array in CPU words*/
  inline ISZ SizeWords() { return AJT().SizeWords<TMap<MAP_P>>(); }

  /* Gets the size of the array in elements*/
  inline ISZ Size() { return This()->size; }

  /* Gets the count of the mappings. */
  inline ISZ Count() { return This()->count; }

  /* Prints this object to a printer. */
  template<typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TMapPrint<Printer, MAP_P>(o, This());
  }

  /* Prints This object to the COut. */
  inline COut& CPrint() { return PrintTo<COut>(StdOut()); }

  /* Gets the aarray_. */
  inline AArray<TMapBuf<MAP_P>, ISZ, BUF>& AJT() { return array_; }

  /* Gets a pointer to the object at the origin of the aarray_. */
  inline TMap<MAP_P>* This() { return TPtr<TMap<MAP_P>>(AJT().Origin());
  }
};
}  //< namespace _
#undef TARGS
#undef TPARAMS

#endif
#endif
