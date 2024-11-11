// Copyright Kabuki Starship� <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_FOLDER_DECL
#define SCRIPT2_FOLDER_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_FILE
namespace _ {

struct CFolder {
  const CHR* uri_;  // Uniform Resource Identifier.
};

/* A file in a filesystem. */
class AFolder {
 public:
  Folder(const CHR* uri);

  const CHR* URI();
  const CHR* URISet(const CHR* uri);
  BOL Exists();
};
}  //< namespace _
#endif
#endif
