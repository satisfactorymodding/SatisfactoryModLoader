// VFSLoader.h - late loading of files not in the tree
// For conditions of distribution and use, see copyright notice in VFS.h

#ifndef VFSLOADER_H
#define VFSLOADER_H

#include <cstddef>
#include "VFSDefines.h"
#include "VFSRefcounted.h"

VFS_NAMESPACE_START

class File;
class Dir;

// VFSLoader - to be called if a file is not in the tree.
class VFSLoader : public Refcounted
{
public:
    VFSLoader();
    virtual ~VFSLoader() {}
    virtual File *Load(const char *fn, const char *unmangled) = 0;
    virtual Dir *LoadDir(const char *fn, const char *unmangled) { return NULL; }

    inline Dir *getRoot() const { return root; }
protected:
    Dir *root;
};

class DiskLoader : public VFSLoader
{
public:
    DiskLoader();
    virtual ~DiskLoader() {}
    virtual File *Load(const char *fn, const char *unmangled);
    virtual Dir *LoadDir(const char *fn, const char *unmangled);
};

VFS_NAMESPACE_END


#endif
