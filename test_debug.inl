#include "global_debug.inl"
#include "test_footer.inl"
#define PRINT_ARGS                                    \
  Printf("\nargs_count:%i args:%p", arg_count, args); \
  for (SI4 i = 0; i < arg_count; ++i) Printf("\n%i:\"%s", i, args[i])
