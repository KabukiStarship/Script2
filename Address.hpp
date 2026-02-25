// Copyright AStarship <https://astarship.net>.
#include "Address.h"
#if SEAM >= CRABS_OPERATION
namespace _ {

/* C++11 constexpr function for creating Script addresses headers with less
typing as well as ensuring there is only a single copy in ROM.
Template solves the problem of not being able using array constructors to
create data structures in ROM.

@code
TAddress<'A', 'B', 'C'> ()
@endcode
*/
template<const CHA... N>
LIB_MEMBER const CHA* TAddress() {
  static const CHA path[sizeof...(N)] = {N...};
  static const CHA term_char = 0;
  return path;
}

}  //< namespace _
#endif
