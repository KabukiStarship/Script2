// Copyright Kabuki Starship� <kabukistarship.com>.
#include "Error.hpp"
#if SEAM >= SCRIPT2_CORE
namespace _ {
const CHA* CrabsError0STA() {
  return TAErrors<CHA>();
}

const CHA* CrabsErrorSTR(ISA error) {
  error = error < 0 ? -error : error;
  if (error > CrabsErrorCount) error = CrabsErrorCount;
  return &TAErrors<CHA>()[error * 32];
}
const CHA* CrabsErrorSTR(ISB error) {
  return CrabsErrorSTR(ISA(error));
}
const CHA* CrabsErrorSTR(ISC error) {
  return CrabsErrorSTR(ISA(error));
}
const CHA* CrabsErrorSTR(ISD error) {
  return CrabsErrorSTR(ISA(error));
}

BOL AIsError(const void* result) {
  return TDelta<IUW>(result) < CrabsErrorCount;
}

}  //< namespace _
#endif
