// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_FOLDER_DECL
#define CRABS_FOLDER_DECL 1
#include <_Config.h>
#if SEAM >= CRABS_FILE
namespace _ {

struct CFolder {
  const CHR* uri_;  // Uniform Resource Identifier.
};

/* A file in a filesystem. */
class AFolder {
 public:
  AFolder(const CHR* uri);

  const CHR* URI();
  const CHR* URISet(const CHR* uri);
  BOL Exists();
};
}  //< namespace _
#endif
#endif
