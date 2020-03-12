#ifndef VFSFILE_ZIP_H
#define VFSFILE_ZIP_H

#include "VFSFile.h"
#include "VFSZipArchiveRef.h"

VFS_NAMESPACE_START

class ZipFile : public File
{
public:
    ZipFile(const char *name, ZipArchiveRef *zref, unsigned int fileIdx);
    virtual ~ZipFile();
    virtual bool open(const char *mode = NULL);
    virtual bool isopen() const;
    virtual bool iseof() const;
    virtual void close();
    virtual bool seek(vfspos pos, int whence);
    virtual bool flush();
    virtual vfspos getpos() const;
    virtual size_t read(void *dst, size_t bytes);
    virtual size_t write(const void *src, size_t bytes);
    virtual vfspos size();
    virtual const char *getType() const { return "ZipFile"; }

protected:
    bool unpack();

    char *_buf;
    vfspos _pos;
    CountedPtr<ZipArchiveRef> _archiveHandle;
    vfspos _bufSize;
    unsigned int _fileIdx;
    std::string _mode;
};

VFS_NAMESPACE_END

#endif
