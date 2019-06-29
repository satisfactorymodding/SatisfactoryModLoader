#ifndef VFSDIR_ZIP_H
#define VFSDIR_ZIP_H

#include "VFSDir.h"
#include "VFSZipArchiveRef.h"

VFS_NAMESPACE_START


class ZipDir : public Dir
{
public:
    ZipDir(ZipArchiveRef *handle, const char *subpath, bool canLoad);
    virtual ~ZipDir();
    virtual void load();
    virtual const char *getType() const { return "ZipDir"; }
    virtual void close();
    virtual DirBase *createNew(const char *dir) const;

protected:
    CountedPtr<ZipArchiveRef> _archiveHandle;
    bool _canLoad;
    const bool _couldLoad;
};


VFS_NAMESPACE_END

#endif
