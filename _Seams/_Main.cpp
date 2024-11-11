// Copyright Kabuki Starship™ <kabukistarship.com>.
#include <_Config.h>
#include "_Tests.inl"
using namespace _;

ISN main(ISN arg_count, CHA** args) {
  const CHA* argss = ArgsToString(arg_count, args);
#if SEAM == SEAM_N
  return SeamResult(Release(argss));
#else
  return TTestTree<Script2Tests>(arg_count, args);
#endif
}
