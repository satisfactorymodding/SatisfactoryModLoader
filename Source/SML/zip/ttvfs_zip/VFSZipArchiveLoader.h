#ifndef VFS_ZIP_ARCHIVE_LOADER_H
#define VFS_ZIP_ARCHIVE_LOADER_H

#include "zip/ttvfs/VFSArchiveLoader.h"

VFS_NAMESPACE_START


class VFSZipArchiveLoader : public VFSArchiveLoader
{
public:
    virtual ~VFSZipArchiveLoader() {}
    virtual Dir *Load(File *arch, VFSLoader **ldr, void *opaque = NULL);
};

VFS_NAMESPACE_END

#endif
