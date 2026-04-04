// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_TYPES_DECL
#define CRABS_TYPES_DECL
#include <_Config.h>

/* Function that remaps a Standard Data Type to an Extended Plain or Extended
Custom Type or prints it to a SPrinter or writes it to a boofer.
Control Bits:
I have no clue what we're going to do with the control bits right now but we
have a word, we only need 16-bits, so why not reserve the entire word?
@param  begin The first byte in the CHR boofer.
@param  end   The CHR after the last char in the boofer.
@param  type  A 16-bit ASCII Type in the LSB and control bits in the MSb.
@param  value A pointer to a value to print.
@return If start is nil the remapped Extended Plain Type.
        If start and stop are not nil a pointer to the CHR after the nil term
        char upon succes. 
*/
typedef DTW(*ACTXHandler)(void* begin, void* end, DTW type, IUW value,
                          IUW vmsb);

#if USING_VISUAL_CPP_X64
// A 128-bit unsigned integer.
struct IUE {
  IUD lsb,
      msb;
};
#endif


namespace _ {

/* Remaps a Plain Context Type to another POD type 1-19.
Store the 5-bit remapped type for _PCa in b0:b4, _PCb in b5:b9, etc. */
DTB ATypeRemapEP(DTW sw_vt_bits, DTW pod_type, DTD ep_remap);

static DTW ACTXHandlerDefault(void* begin, void* end, DTW type, IUW value,
                              IUW vmsb);

/* A single cache-line-aligned variable set for controlling the Chinese Room.
*/
struct ACTXFrame {
  enum {
    Bytes = 256 + ACPUCacheLineSize,
    BytesReserved = (Bytes - 2 * sizeof(IUW)) >> ACPUBytesLog2,
  };
  ACTXHandler handler;            //< ASCII Context Handler.
  ISW epoch;                      //< 32-bit Unix timestamp epoch.
#if CPU_SIZE != CPU_2_BYTE
  IUW scratchpad[BytesReserved] = {0};  //< Cache line alignment words.
#endif

  ACTXFrame();
};

/* Returns the the Global Chinese Room Entry. */
inline ACTXFrame* ACTX();

// Maps a type to ACTXHandler.
inline DTW ACTXHandle(ACTXHandler actxh, void* begin, void* end, DTW type, 
                      IUW value, IUW vmsb);
// Maps a type to ACTXHandler.
inline DTW ACTXHandle(void* begin, void* end, DTW type, IUW value, IUW vmsb);

// Deasserts the MD bits if it's now CTX type.
inline DTB ATypeMDDeassert(DTW type);

// Asserts the Pointer modifier bits.
inline DTB ATypeMakePtr(DTW type);

// Asserts the Crabs index modifier bits.
inline DTB ATypeMakeCrabsIndex(DTW type);

// Asserts the Context Modifier bits.
inline DTB ATypeMDC(DTW type);

// Asserts the Context Modifier bits.
inline DTB ATypeCNS_MDC(DTW type);

// Asserts the Constant bit.
inline DTB ATypeMakeCNS(DTW type);

// Asserts the Pointer modifier bits.
inline DTB ATypeMakePtrCNS(DTW type);

// Asserts the Crabs index modifier bits.
inline DTB ATypeCrabsIndexCNS(DTW type);

// A 128-bit unsigned integer.
struct IUE {
  IUD lsb;    //< Least significant 64 bits.
  IUD msb;    //< Most significant 64 bits.

  IUE(IUB v1, IUB v2, IUB v3, IUB v4, IUB v5, IUB v6, IUB v7, IUB v8);

  IUE(IUC v1, IUC v2, IUC v3, IUC v4);

  IUE(IUD lsb, IUD msb = 0);
};

// A 128-bit signed integer.
struct ISE {
  IUD lsb;    //< Least significant 64 bits.
  IUD msb;    //< Most significant 64 bits.

  ISE(IUB v1, IUB v2, IUB v3, IUB v4, IUB v5, IUB v6, IUB v7, IUB v8);

  ISE(IUC v1, IUC v2, IUC v3, IUC v4);

  ISE(IUD lsb, IUD msb = 0);
};

#if USING_SOFTWARE_FPC == YES_0
#if CPU_SIZE == CPU_2_BYTES
// A 32-bit floating-point number.
struct FPC {
  IUB lsb;    //< Least significant 16 bits.
  IUB msb;    //< Most significant 16 bits.

  FPC(IUB lsb, IUB msB = 0);
};
#else
// A 32-bit floating-point number.
struct FPC {
  IUB lsb;    //< Least significant 16 bits.
  IUB msb;    //< Most significant 16 bits.

  FPC(IUB lsb, IUB msB = 0);
};
#endif
#endif
#if CPU_SIZE < CPU_8_BYTES
// A 64-bit floating-point number.
struct FPD {
  IUC lsb;    //< Least significant 32 bits.
  IUC msb;    //< Most significant 32 bits.

  FPD(IUB v1, IUB v2, IUB v3, IUB v4);

  FPD(IUC lsb, IUC msb = 0);
};
#endif

// A 128-bit floating-point number.
struct FPE {
  IUD lsb;    //< Least significant 64 bits.
  IUD msb;    //< Most significant 64 bits.

  FPE(IUB v1, IUB v2, IUB v3, IUB v4, IUB v5, IUB v6, IUB v7, IUB v8);

  FPE(IUC v1, IUC v2, IUC v3, IUC v4);

  FPE(IUD lsb, IUD msb = 0);
};

// Packs the given ASCII Type bitfield values into a DTB.
DTB ATypePack(DTB pod, DTB vt);
DTB ATypePack(DTB pod, DTB vt, DTB sw);
DTB ATypePack(DTB pod, DTB vt, DTB sw, DTB mt);
DTB ATypePack(DTB pod, DTB vt, DTB sw, DTB mt, DTB mod);

// Returns true if the given type is a CHA, CHB, or CHC.
BOL ATypeIsCH(DTB type);

// Returns the size of the given type in bytes.
ISA ATypeSizeOfPOD(DTB type);

/* Gets the alignment mask of the given type. */
inline DTW AlignmentMask(CHA item);
inline DTW AlignmentMask(ISA item);
inline DTW AlignmentMask(IUA item);
inline DTW AlignmentMask(CHB item);
inline DTW AlignmentMask(ISB item);
inline DTW AlignmentMask(IUB item);
inline DTW AlignmentMask(CHC item);
inline DTW AlignmentMask(ISC item);
inline DTW AlignmentMask(IUC item);
inline DTW AlignmentMask(FPC item);
inline DTW AlignmentMask(ISD item);
inline DTW AlignmentMask(IUD item);
inline DTW AlignmentMask(FPD item);
inline DTW AlignmentMask(void* item);
inline DTW AlignmentMask(const void* item);

/* Gets the type of the given item. */
inline DTW TypeOf(CHA item);
inline DTW TypeOf(ISA item);
inline DTW TypeOf(IUA item);
inline DTW TypeOf(CHB item);
inline DTW TypeOf(ISB item);
inline DTW TypeOf(IUB item);
inline DTW TypeOf(CHC item);
inline DTW TypeOf(ISC item);
inline DTW TypeOf(IUC item);
inline DTW TypeOf(FPC item);
inline DTW TypeOf(ISD item);
inline DTW TypeOf(IUD item);
inline DTW TypeOf(FPD item);
inline DTW TypeOf(CHA* item);
inline DTW TypeOf(const CHA* item);
inline DTW TypeOf(CHB* item);
inline DTW TypeOf(const CHB* item);
inline DTW TypeOf(CHC* item);
inline DTW TypeOf(const CHC* item);
inline DTW TypeOf(void* item);
inline DTW TypeOf(const void* item);

/* Returns the size of the given type in bytes.
@return the size bytes of the value. */
ISW ATypeBytes(const void* value, DTB type);
ISW ATypeBytes(const void* value_base, ISA bytes, DTB type);

// Returns the end (byte after last byte) of the given type-value.
void* ATypeValueEnd(void* value, DTB type);

// Returns an array of the customizable POD type sizes.
//const ISA* ATypeCustomSize();

// Returns an array of the user-defined type alignment masks.
//const ISA* ATypeCustomAlignMask();

// Returns the custom time alignment mask for the given type.
//ISA ATypeCustomAlignMask(DTA type);

// Converts a 16-bit ASCII Data Type bit pattern to Extended ASCII Type mapping.
inline DTB ATypeToEXT_NC(DTW type_msb, DTW type);
inline DTB ATypeToEXT(DTW type);
inline DTB ATypeToEXT(DTW type_msb, DTW type_pod);

// Checks if the given type is a Extended Plain or Extended Context Type.
inline BOL ATypeIsCTX(DTW sw_vt, DTW pod);

// Checks if the given type is a Extended Plain or Extended Context Type.
inline BOL ATypeIsCTX(DTW type);

/* Converts an ASCII Type to Context Type without checking.
@pre Dev shall check if the type is a CTX Type before calling. */
inline DTW ATypeToCTX_NC(DTW sw_vt, DTW pod);

/* Remaps EPa-EPl to POD types 0-19 using 12 5-bit maps in an 8-byte type.
@return (type >> (type - _EPa) * 5) & ATypePODMask */
inline DTB ATypeRemapEP_NC(DTW pod_type, DTW ep_remap);

/* Stores a pointer to the ASCII data type and it's value. */
struct ATypePtr {
  DTW   type;         //< ASCII data type word.
  const void* value;  //< Pointer to the value of the type.
};

// Gets the Unicode format: 0=UTF-8, 1=UTF-16, 2=UTF-32.
inline ISA ATypeTextFormat(DTW type);

class Nil {
public:
  /* Constructures nothing. */
  Nil();

  /* Gets the size of the socket. */
  static constexpr ISW Size();

  /* Gets the size of the socket. */
  static constexpr ISW Bytes();

  /* Gets the size of the socket. */
  static constexpr ISW SizeWords();

  /* Gets the nil origin word address. */
  IUW* Words();
};

/* An ASCII Type-Value tuple.
An TypeValue can only work with up to two CPU ALU words because when a CPU
multiplies two integers together the result is two ALU-sized words and thus the
CPU can only address 2 words at a time. For types that are larger that two ALU
words wide the word_ stores a pointer to that type in memory and a struct will
be needed to work with the type. */
class ATypeValue {
  DTW type_;    //< Type of the value.
  IUW value_,   //< First or only word of the value.
      vmsb_;    //< Most significant bits of two word type.

 public:
  /* Stores a NIL type with indeterminate word_. */
  ATypeValue();

#if USING_STA == YES_0
  explicit ATypeValue(CHA value);
  explicit ATypeValue(const CHA* value);
#endif
#if USING_STB == YES_0
  explicit ATypeValue(CHB value);
  explicit ATypeValue(const CHB* value);
#endif
#if USING_STC == YES_0
  explicit ATypeValue(CHC value);
  explicit ATypeValue(const CHC* value);
#endif
  explicit ATypeValue(ISA value);
  explicit ATypeValue(IUA value);
  explicit ATypeValue(ISB value);
  explicit ATypeValue(IUB value);
  explicit ATypeValue(ISC value);
  explicit ATypeValue(IUC value);
  explicit ATypeValue(ISD value);
  explicit ATypeValue(IUD value);
#if USING_FPC == YES_0
  explicit ATypeValue(FPC value);
#endif
#if USING_FPD == YES_0
  explicit ATypeValue(FPD value);
#endif

  /* Stores the value to the word_ and the ASCII type of the value. */
  explicit ATypeValue(void* value);
  explicit ATypeValue(const void* value);

  explicit ATypeValue(void* base_ptr, ISW offset);
  explicit ATypeValue(const void* base_ptr, ISW offset);

  explicit ATypeValue(DTW type, void* value);
  explicit ATypeValue(DTW type, const void* value);

  explicit ATypeValue(DTW type, void* base_ptr, ISW offset);
  explicit ATypeValue(DTW type, const void* base_ptr, ISW offset);

  explicit ATypeValue(DTW type, void* value, void* value_end);
  explicit ATypeValue(DTW type, const void* value, const void* value_end);

  explicit ATypeValue(DTW type, void* base_ptr, ISW offset, void* value_end);
  explicit ATypeValue(DTW type, const void* base_ptr, ISW offset, const void* value_end);

  explicit ATypeValue(DTW type, void* base_ptr, ISW offset, ISW base_bytes);
  explicit ATypeValue(DTW type, const void* base_ptr, ISW offset, ISW base_bytes);

  /* Gets the type_. */
  inline DTW Type();

  /* Gets the Unicode string format if any. */
  inline DTW UnicodeFormat();

  /* Gets a pointer to the word_. */
  inline void* WordPTR();

  /* Gets the value as the return type. */
  inline void* ToPTR();
  inline CHA* ToSTA();
  inline CHB* ToSTB();
  inline CHC* ToSTC();
  inline IUA  ToIUA();
  inline IUB  ToIUB();
  inline IUN  ToIUN();
  inline IUC  ToIUC();
  inline IUD  ToUID();

  /* Gets the first word of the word_. */
  inline IUW Value();

  /* Gets the second word of the value if the type is two words wide. */
  inline IUW MSB();

  /* Sets the word to the value. */
  inline void SetWord(IUW value);

  /* Sets the second word to the value. */
  inline void SetWord2(IUW value);

  /*Sets the type_ to _NIL with an indeterminate value. */
  inline void SetNIL();

  /*Sets the type_ to _NIL with an indeterminate value. */
  inline void SetNIL(IUW value);

  inline void* Set(void* value);
  inline const void* Set(const void* value);

  inline void* Set(void* base_ptr, ISW voffset);
  inline const void* Set(const void* base_ptr, ISW voffset);

  inline void* Set(DTW type, void* value);
  inline const void* Set(DTW type, const void* value);

  inline void* Set(DTW type, void* base_ptr, ISW voffset);
  inline const void* Set(DTW type, const void* base_ptr, ISW voffset);

  inline void* Set(DTW type, void* value, void* value_end);
  inline const void* Set(DTW type, const void* value, const void* value_end);

  inline void* Set(DTW type, void* base_ptr, ISW offset, void* value_end);
  inline const void* Set(DTW type, const void* base_ptr, ISW offset, 
                         const void* value_end);

  inline void* Set(DTW type, void* base_ptr, ISW offset, ISW base_byes);
  inline const void* Set(DTW type, const void* base_ptr, ISW offset, 
                         ISW base_byes);

  /*Sets the word_ to the given value and updates the type. */
#if USING_STA == YES_0
  inline void Set(CHA value);
  inline void Set(const CHA* value);
#endif
#if USING_STB == YES_0
  inline void Set(CHB value);
  inline void Set(const CHB* value);
#endif
#if USING_STC == YES_0
  inline void Set(const CHC* value);
  inline void Set(CHC value);
#endif
  inline void Set(ISA value);
  inline void Set(IUA value);
  inline void Set(ISB value);
  inline void Set(IUB value);
  inline void Set(BOL value);
  inline void Set(ISC value);
  inline void Set(IUC value);
  inline void Set(ISD value);
  inline void Set(IUD value);
#if USING_FPC == YES_0
  inline void Set(FPC value);
#endif
#if USING_FPD == YES_0
  inline void Set(FPD value);
#endif
};

}  //< namespace _
#endif
