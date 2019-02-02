#include "global_release.inl"
#include "test_footer.inl"

#define PRINT_ARGS

#if COMPILER == VISUAL_CPP
#define FORMAT_SI8 "%I64i"
#define FORMAT_UI8 "%I64u"
#else
#define FORMAT_SI8 "%lld"
#define FORMAT_UI8 "%llu"
#endif
