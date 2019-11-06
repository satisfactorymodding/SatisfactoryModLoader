// VFSDefines.h - compile config and basic setup
// For conditions of distribution and use, see copyright notice in VFS.h

#ifndef VFS_DEFINES_H
#define VFS_DEFINES_H

/* --- Config section -- modify as needed --- */

// Define this to allow dealing with files > 4 GB, using non-standard functions.
// This may or may not work with your platform/compiler, good luck.
//#define VFS_LARGEFILE_SUPPORT

// Define this to make all operations case insensitive.
// Windows systems generally don't care much, but for Linux and Mac this can be used
// to get the same behavior as on windows.
// Additionally, this achieves full case insensitivity within the library,
// if the the same files are accessed multiple times by the program, but with not-uniform case.
// (no sane programmer should do this, anyway).
// However, on non-windows systems this will decrease performance when checking for files
// on disk (see VFSLoader.cpp).
//#define VFS_IGNORE_CASE


/* --- End of config section --- */


#define VFS_NAMESPACE_START namespace ttvfs {
#define VFS_NAMESPACE_END }


// Important that this is included outside of the namespace.
// Note that stdint.h is intentionally NOT included if possible,
// because on gcc it pulls in features.h, which in turn checks for
// _FILE_OFFSET_BITS presence. That means to enable 64bit file I/O,
// _FILE_OFFSET_BITS would have to be defined here.
// For the sake of not polluting the includer, use other means to define
// a 64 bit type.
#if !defined(_MSC_VER) && !defined(__GNUC__)
#  include <stdint.h> // Hope it works.
#endif

VFS_NAMESPACE_START

// vfspos type (signed 64bit integer if possible, 32bit otherwise)
#if defined(_MSC_VER)
     typedef __int64           vfspos;
#elif defined(__GNUC__)
    __extension__ // suppress warnings about long long
    typedef long long int      vfspos;
#elif defined(VFS_LARGEFILE_SUPPORT)
    // fallback using stdint. h, but only if necessary
    typedef int64_t           vfspos;
#else
    // If all else fails
    typedef long int          vfspos; // what fseek() uses, no guarantees whether 64 or 32 bits
#endif

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
#    define VFS_STRICMP _stricmp
#else
#    define VFS_STRICMP strcasecmp
#endif
static const vfspos npos = ~vfspos(0);

typedef void (*delete_func)(void *);

struct _AbiCheck
{
    int structSize;
    int vfsposSize;
    int largefile;
    int nocase;
};

class File;
class DirBase;

typedef void (*FileEnumCallback)(File *vf, void *user);
typedef void (*DirEnumCallback)(DirBase *vd, void *user);


VFS_NAMESPACE_END

#endif
