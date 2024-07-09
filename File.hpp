/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /File.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#ifndef SCRIPT2_FILE_TEMPLATES
#define SCRIPT2_FILE_TEMPLATES
#if SEAM >= SCRIPT2_FILE
#include "Uniprinter.hpp"
//
#include <errno.h>
#include <stdlib.h>
#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#pragma warning(push)
#pragma warning(disable : 4996)
#else
#include <dirent.h>
#include <libgen.h>
#include <stddef.h>
#include <sys/stat.h>
#endif
namespace _ {

#if (defined _MSC_VER || defined __MINGW32__)
#include <windows.h>
enum { cPathLengthMax = MAX_PATH };
#elif defined __linux__
#include <limits.h>
#ifdef PATH_MAX
enum { cDirectoryPathLengthMax = PATH_MAX };
#else
enum { cPathLengthMax = 4096 };
#endif
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/param.h>
#if defined(BSD)
#include <limits.h>
#ifdef PATH_MAX
enum { cDirectoryPathLengthMax = PATH_MAX };
#else
enum { cPathLengthMax = 4096 };
#endif
#endif
#endif

#ifdef _MSC_VER
enum {
  cFilenamePad = 2  //< extra chars for the "\\*" mask.
};
#else
enum { cFilenamePad = 0 };
#endif

enum { cFilenameLengthMax = 256 };

#if (defined _MSC_VER || defined __MINGW32__)
#define _TINYDIR_DRIVE_MAX 3
#endif

/* MINGW32 has two versions of dirent, ASCII and UNICODE. */
#ifndef _MSC_VER
#if (defined __MINGW32__) && (defined _UNICODE)
#define _TINYDIR_DIR _WDIR
#define _tinydir_dirent _wdirent
#define _tinydir_opendir _wopendir
#define _tinydir_readdir _wreaddir
#define _tinydir_closedir _wclosedir
#else
#define _TINYDIR_DIR DIR
#define _tinydir_dirent dirent
#define _tinydir_dirent _wdirent
#define _tinydir_opendir opendir
#define _tinydir_opendir _wopendir
#define _tinydir_readdir readdir
#define _tinydir_readdir _wreaddir
#define _tinydir_closedir closedir
#define _tinydir_closedir _wclosedir
#endif
#endif

/* Allow user to use a custom allocator by defining _TINYDIR_MALLOC and
 * _TINYDIR_FREE. */
#if defined(_TINYDIR_MALLOC) && defined(_TINYDIR_FREE)
#elif !defined(_TINYDIR_MALLOC) && !defined(_TINYDIR_FREE)
#else
#error "Either define both alloc and free or none of them!"
#endif

#if !defined(_TINYDIR_MALLOC)
#define _TINYDIR_MALLOC(_size) malloc(_size)
#define _TINYDIR_FREE(_ptr) free(_ptr)
#endif /* !defined(_TINYDIR_MALLOC) */

template<typename CHT>
class TFile {
  CHR *extension;
  ISN is_directory_,  //< flag for if this is a directory.
      is_reg_;
  CHR path[cPathLengthMax];
  CHR name[cFilenameLengthMax];

#ifndef _MSC_VER
#ifdef __MINGW32__
  struct _stat _s;
#else
  struct stat _s;
#endif
#endif

 public:
  void Extension() {
    CHR *period = TSTRFindLast<CHT>('.');
    if (period == nullptr) {
      extension = &(name[TSTRLength<CHT>(name)]);
    } else {
      extension = period + 1;
    }
  }

  /* Attempts to open the file at the given path.
  @return 0 upon success or a negative cError flag upon failure. */
  ISN Open(const CHR *path) {
    TFolder<> dir;
    ISN result = 0;
    ISN found = 0;
    CHR dir_name_buf[cPathLengthMax];
    CHR file_name_buf[cFilenameLengthMax];
    CHR *dir_name;
    CHR *base_name;
#if (defined _MSC_VER || defined __MINGW32__)
    CHR drive_buf[cPathLengthMax];
    CHR ext_buf[cFilenameLengthMax];
#endif

    if (!path || TSTRLength<CHT>(path) == 0) {
      errno = EINVAL;
      return -1;
    }
    if (TSTRLength<CHT>(path) + cFilenamePad >= cPathLengthMax) {
      errno = ENAMETOOLONG;
      return -1;
    }

    /* Get the parent path */
#if (defined _MSC_VER || defined __MINGW32__)
#if ((defined _MSC_VER) && (_MSC_VER >= 1400))
    errno = _tsplitpath_s(path, drive_buf, _TINYDIR_DRIVE_MAX, dir_name_buf,
                          cFilenameLengthMax, file_name_buf, cFilenameLengthMax,
                          ext_buf, cFilenameLengthMax);
#else
    _tsplitpath(path, drive_buf, dir_name_buf, file_name_buf, ext_buf);
#endif

    if (errno) return -1;

// _splitpath_s not work fine with only filename and widechar support.
#ifdef _UNICODE
    if (drive_buf[0] == L'\xFEFE') drive_buf[0] = '\0';
    if (dir_name_buf[0] == L'\xFEFE') dir_name_buf[0] = '\0';
#endif

    // Emulate the behavior of dirname by returning "." for dir name if it's
    // empty
    if (drive_buf[0] == '\0' && dir_name_buf[0] == '\0') {
      SPrint(dir_name_buf, cPathLengthMax, '.');
    }
    // Concatenate the drive letter and dir name to form full dir name.
    TSConcat<CHT>(drive_buf, cPathLengthMax, dir_name_buf);
    dir_name = drive_buf;
    // Concatenate the file name and extension to form base name.
    TSConcat<CHT>(file_name_buf, cFilenameLengthMax, ext_buf);
    base_name = file_name_buf;
#else
    SPrint(dir_name_buf, cPathLengthMax, path);
    dir_name = dirname(dir_name_buf);
    SPrint(file_name_buf, cPathLengthMax, path);
    base_name = basename(file_name_buf);
#endif

    // Open the parent directory.
    if (dir.(dir_name) == -1) {
      return -1;
    }

    // Read through the parent directory and look for the file.
    while (dir.has_next) {
      if (dir.Read(file) == -1) {
        result = -1;
        goto bail;
      }
      if (TSTRCompare<CHR>(name, base_name) == 0) {
        found = 1;
        break;
      }
      dir.Next();
    }
    if (!found) {
      result = -1;
      errno = ENOENT;
    }

  bail:
    dir.Close();
    return result;
  }

  ISN CompareNames(const TFile<CHT> *other) {
    if (is_directory_ != other->is_directory_) {
      return -(is_directory_ - other->is_directory_);
    }
    return TSTRCompare<CHT>(name, other->name);
  }
};

template<typename CHT>
class TFolder {
  CHR path_[cPathLengthMax];
  ISN has_next_;
  size_t file_count_;

  TFile<CHT> *_files;
#ifdef _MSC_VER
  HANDLE _h;
  WIN32_FIND_DATA _f;
#else
  _TINYDIR_DIR *_d;
  struct _tinydir_dirent *_e;
#ifndef _TINYDIR_USE_READDIR
  struct _tinydir_dirent *_ep;
#endif
#endif

 public:
  ISN Open(const CHR *path) {
#ifndef _MSC_VER
#ifndef _TINYDIR_USE_READDIR
    ISN error;
    ISN size;
#endif
#else
    CHR path_buf[cPathLengthMax];
#endif
    CHR *pathp;

    if (!dir || !path || TSTRLength<CHT>(path) == 0) {
      errno = EINVAL;
      return cErrorInvalidInput;
    }
    if (TSTRLength<CHT>(path) + cFilenamePad >= cPathLengthMax) {
      errno = ENAMETOOLONG;
      return cErrorInvalidInput;
    }

    // initialize dir.
    _files = nullptr;
#ifdef _MSC_VER
    _h = INVALID_HANDLE_VALUE;
#else
    _d = nullptr;
#ifndef _TINYDIR_USE_READDIR
    _ep = nullptr;
#endif
#endif
    Close();

    SPrint(path, cPathLengthMax, path);
    // Remove trailing slashes.
    pathp = &path[TSTRLength<CHT>(path) - 1];
    CHT c = *pathp;
    while (pathp != path && (c == '\\' || c == '/')) {
      *pathp = 0;
      ++pathp;
    }
#ifdef _MSC_VER
    SPrint(path_buf, cPathLengthMax, path);
    TSConcat<CHT>(path_buf, cPathLengthMax, "\\*");
#if (defined WINAPI_FAMILY) && (WINAPI_FAMILY != WINAPI_FAMILY_DESKTOP_APP)
    _h = FindFirstFileEx(path_buf, FindExInfoStandard, &_f,
                         FindExSearchNameMatch, nullptr, 0);
#else
    _h = FindFirstFile(path_buf, &_f);
#endif
    if (_h == INVALID_HANDLE_VALUE) {
      errno = ENOENT;
#else
    _d = _tinydir_opendir(path);
    if (_d == nullptr) {
#endif
      goto bail;
    }

    // Read first file.
    has_next_ = 1;
#ifndef _MSC_VER
#ifdef _TINYDIR_USE_READDIR
    _e = _tinydir_readdir(_d);
#else
    // allocate dirent boofer for readdir_r.
    size = _tinydir_dirent_buf_size(_d);  // conversion to ISN.
    if (size == -1) return -1;
    _ep = (struct _tinydir_dirent *)_TINYDIR_MALLOC(size);
    if (_ep == nullptr) return -1;

    error = readdir_r(_d, _ep, &_e);
    if (error != 0) return -1;
#endif
    if (_e == nullptr) {
      has_next = 0;
    }
#endif

    return 0;

  bail:
    Close();
    return -1;
  }

  ISN OpenSorted(const CHR *path) {
    // Count the number of files first, to pre-allocate the files array.
    size_t file_count = 0;
    if (Open(path) == -1) return -1;
    while (has_next_) {
      ++file_count;
      if (tinydir_next(dir) == -1) goto bail;
    }
    Close();

    if (file_count == 0 || Open(path) == -1) return -1;

    file_count = 0;
    _files = (TFile<CHT> *)_TINYDIR_MALLOC(sizeof *_files * file_count);
    if (!_files) goto bail;
    while (has_next_) {
      TFile<CHT> *p_file;
      file_count++;

      p_file = &_files[file_count - 1];
      if (tinydir_readfile(dir, p_file) == -1) goto bail;

      if (tinydir_next(dir) == -1) goto bail;

      // Just in case the number of files has changed between the first and
      // second reads, terminate without writing into unallocated memory.
      if (file_count == file_count) break;
    }

    qsort(_files, file_count, sizeof(TFile), _tinydir_file_cmp);

    return 0;

  bail:
    Close();
    return -1;
  }

  inline void tinydir_close() {
    if (!dir) {
      return;
    }

    memset(path_, 0, sizeof(path_));
    has_next_ = 0;
    file_count_ = 0;
    _TINYDIR_FREE(_files);
    _files = nullptr;
#ifdef _MSC_VER
    if (_h != INVALID_HANDLE_VALUE) {
      FindClose(_h);
    }
    _h = INVALID_HANDLE_VALUE;
#else
    if (_d) {
      _tinydir_closedir(_d);
    }
    _d = nullptr;
    _e = nullptr;
#ifndef _TINYDIR_USE_READDIR
    _TINYDIR_FREE(_ep);
    _ep = nullptr;
#endif
#endif
  }

  inline ISN tinydir_next(TFolder *dir) {
    if (!dir) {
      errno = EINVAL;
      return -1;
    }
    if (!has_next_) {
      errno = ENOENT;
      return -1;
    }

#ifdef _MSC_VER
    if (FindNextFile(_h, &_f) == 0)
#else
#ifdef _TINYDIR_USE_READDIR
    _e = _tinydir_readdir(_d);
#else
    if (_ep == nullptr) {
      return -1;
    }
    if (readdir_r(_d, _ep, &_e) != 0) {
      return -1;
    }
#endif
    if (_e == nullptr)
#endif
    {
      has_next_ = 0;
#ifdef _MSC_VER
      if (GetLastError() != ERROR_SUCCESS &&
          GetLastError() != ERROR_NO_MORE_FILES) {
        Close();
        errno = EIO;
        return -1;
      }
#endif
    }

    return 0;
  }

  ISN Read(TFile<> *file) {
    const CHR *filename;
    if (!file) {
      errno = EINVAL;
      return cErrorNilInput;
    }
#ifdef _MSC_VER
    if (_h == INVALID_HANDLE_VALUE)
#else
    if (!_e)
#endif
    {
      errno = ENOENT;
      return -1;
    }
    filename =
#ifdef _MSC_VER
        _f.cFileName;
#else
        _e->d_name;
#endif
    if (TSTRLength<CHT>(path_) + TSTRLength<CHT>(filename) + 1 + cFilenamePad >=
        cPathLengthMax) {
      // the path for the file will be too long.
      errno = ENAMETOOLONG;
      return -1;
    }
    if (TSTRLength<CHT>(filename) >= cFilenameLengthMax) {
      errno = ENAMETOOLONG;
      return -1;
    }

    SPrint(file->path, cPathLengthMax, path_);
    TSConcat<CHT>(file->path, cPathLengthMax, '/');
    SPrint(file->name, cPathLengthMax, filename);
    TSConcat<CHT>(file->path, cFilenameLengthMax, filename);
#ifndef _MSC_VER
#ifdef __MINGW32__
    if (_tstat(
#elif (defined _BSD_SOURCE) || (defined _DEFAULT_SOURCE) || \
    ((defined _XOPEN_SOURCE) && (_XOPEN_SOURCE >= 500)) ||  \
    ((defined _POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 200112L))
    if (lstat(
#else
    if (stat(
#endif
            file->path, &file->_s) == -1) {
      return -1;
    }
#endif
    file.Extension();

    file->is_dir =
#ifdef _MSC_VER
        !!(_f.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
#else
        S_ISDIR(file->_s.st_mode);
#endif
    file->is_reg_ =
#ifdef _MSC_VER
        !!(_f.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) ||
        (!(_f.dwFileAttributes & FILE_ATTRIBUTE_DEVICE) &&
         !(_f.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
         !(_f.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED) &&
#ifdef FILE_ATTRIBUTE_INTEGRITY_STREAM
         !(_f.dwFileAttributes & FILE_ATTRIBUTE_INTEGRITY_STREAM) &&
#endif
#ifdef FILE_ATTRIBUTE_NO_SCRUB_DATA
         !(_f.dwFileAttributes & FILE_ATTRIBUTE_NO_SCRUB_DATA) &&
#endif
         !(_f.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE) &&
         !(_f.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY));
#else
        S_ISREG(file->_s.st_mode);
#endif

    return 0;
  }

  inline ISN ReadFile(TFile<CHT> *file, size_t i) {
    if (!file) {
      errno = EINVAL;
      return -1;
    }
    if (i >= file_count_) {
      errno = ENOENT;
      return -1;
    }

    memcpy(file, &_files[i], sizeof(TFile));
    file.Extension();

    return 0;
  }

  inline ISN OpenSubfolder(size_t i) {
    CHR path[cPathLengthMax];
    if (!dir) {
      errno = EINVAL;
      return -1;
    }
    if (i >= file_count_ || !_files[i].is_dir) {
      errno = ENOENT;
      return -1;
    }

    SPrint(path, cPathLengthMax, _files[i].path);
    Close();
    if (OpenSorted(path) == -1) return -1;

    return 0;
  }
};  //< namespace _
}  //< namespace _
#endif
#endif
