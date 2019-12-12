#ifndef VFS_ZIP_ARCHIVE_REF
#define VFS_ZIP_ARCHIVE_REF

#include "VFSFile.h"


VFS_NAMESPACE_START

class ZipArchiveRef : public Refcounted
{
public:
    ZipArchiveRef(File *archive);
    ~ZipArchiveRef();
    bool openRead();
    void close();
    bool init();
    void *mz;
    const char *fullname() const;

protected:
    CountedPtr<File> archiveFile;
};


VFS_NAMESPACE_END

#endif

