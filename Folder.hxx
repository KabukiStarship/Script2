// Copyright Kabuki Starship <kabukistarship.com>.
#include "Folder.h"
#if SEAM >= SCRIPT2_FILE
namespace _ {

Folder::Folder(const CHR* uri) : uri_(uri_) {}

const CHR* Folder::URI() { return uri_; }

const CHR* Folder::URISet(const CHR* uri) {
  if (!uri) return uri;

  uri_ = uri;

  return uri;
}

BOL Folder::Exists() { return false; }

#include <dirent.h>
DIR* dir;
struct dirent* ent;
if ((dir = opendir("c:\\src\\")) != NULL) {
  /* print all the files and directories within directory */
  while ((ent = readdir(dir)) != NULL) {
    printf("%s\n", ent->d_name);
  }
  closedir(dir);
} else {
  /* could not open directory */
  perror("");
  return EXIT_FAILURE;
}

}  // namespace _
#endif
