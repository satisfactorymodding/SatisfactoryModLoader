// VFSInternal.h - misc things that are not required to be visible outside of the library.
// For conditions of distribution and use, see copyright notice in VFS.h

// !! this file is supposed to be included ONLY from VFS*.cpp files.

#ifndef VFS_INTERNAL_H
#define VFS_INTERNAL_H

// checks to enforce correct including
#ifdef TTVFS_VFS_H
#error Oops, TTVFS_VFS_H is defined, someone messed up and included ttvfs.h wrongly.
#endif

#include "VFSDefines.h"

#if defined(VFS_LARGEFILE_SUPPORT)
# ifndef _LARGEFILE_SOURCE
#  define _LARGEFILE_SOURCE
# endif
# ifndef _LARGEFILE64_SOURCE
#  define _LARGEFILE64_SOURCE
# endif
# ifdef _FILE_OFFSET_BITS
#  undef _FILE_OFFSET_BITS
# endif
# ifndef _FILE_OFFSET_BITS
#  define _FILE_OFFSET_BITS 64
# endif
#endif

#if _MSC_VER
# ifndef _CRT_SECURE_NO_WARNINGS
#   define _CRT_SECURE_NO_WARNINGS
# endif
# ifndef _CRT_SECURE_NO_DEPRECATE
#   define _CRT_SECURE_NO_DEPRECATE
# endif
#endif

#ifdef __GNUC__
# define TTVFS_UNUSED __attribute__((unused))
#else
# define TTVFS_UNUSED
#endif

// These are used for small, temporary memory allocations that can remain on the stack.
// If alloca is available, this is the preferred way.
#include <stdlib.h>
#ifdef _WIN32
#  include <malloc.h> // MSVC/MinGW still need this for alloca. Seems to be windows-specific failure
#endif
#define VFS_STACK_ALLOC(size) alloca(size)
#define VFS_STACK_FREE(ptr)   /* no need to free anything here */
// Fail-safe:
//#define VFS_STACK_ALLOC(size) malloc(size)
//#define VFS_STACK_FREE(ptr)  free(ptr)


#include <string.h>
#include <string>
#include <assert.h>



VFS_NAMESPACE_START

template <typename DST, typename SRC> inline DST safecast(SRC p)
{
#ifndef NDEBUG
    assert(!p || static_cast<DST>(p) == dynamic_cast<DST>(p));
#endif
    return static_cast<DST>(p);
}

template <typename DST, typename SRC> inline DST safecastNonNull(SRC p)
{
#ifndef NDEBUG
    assert(p && static_cast<DST>(p) == dynamic_cast<DST>(p));
#endif
    return static_cast<DST>(p);
}

VFS_NAMESPACE_END

#endif
