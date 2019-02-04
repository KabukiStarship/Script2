#include "global_debug.inl"

#include "module_footer.inl"

#define PRINT_ARGS                                    \
  Printf("\nargs_count:%i args:%p", arg_count, args); \
  for (SI4 i = 0; i < arg_count; ++i) Printf("\n%i:\"%s", i, args[i])

#if COMPILER == VISUAL_CPP
#define FORMAT_SI8 "%I64i"
#define FORMAT_UI8 "%I64u"
#else
#define FORMAT_SI8 "%lld"
#define FORMAT_UI8 "%llu"
#endif
