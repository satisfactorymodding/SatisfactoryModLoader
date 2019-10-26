// VFSFile.h - basic file interface + classes
// For conditions of distribution and use, see copyright notice in VFS.h

#ifndef VFSFILE_H
#define VFSFILE_H

#include "VFSBase.h"

VFS_NAMESPACE_START


/** -- File basic interface --
  * All functions that return bool should return true on success and false on failure.
  * If an operation is not necessary or irrelevant (for example, files in memory can't be closed),
  *    it is useful to return true anyways, because this operation did not fail, technically.
  *    (Common sense here!)
  * An int/vfspos value of 0 indicates failure, except the size/seek/getpos functions, where npos means failure.
  * Only the functions required or applicable need to be implemented, for unsupported operations
  *    the default implementation should be sufficient.
  **/
class File : public VFSBase
{
public:

    virtual ~File();

    /** Open a file.
        Mode can be "r", "w", "rb", "rb", and possibly other things that fopen supports.
        It is the subclass's choice to support other modes. Default is "rb".
        Closes and reopens if already open (even in the same mode). */
    virtual bool open(const char *mode = NULL) = 0;

    virtual bool isopen() const = 0;
    virtual bool iseof() const = 0;
    virtual void close() = 0;
    virtual bool seek(vfspos pos, int whence) = 0;

    virtual bool flush() = 0;

    /** Current offset in file. Return npos if NA. */
    virtual vfspos getpos() const = 0;

    virtual size_t read(void *dst, size_t bytes) = 0;
    virtual size_t write(const void *src, size_t bytes) = 0;

    /** Return file size. If NA, return npos. If size is not yet known,
        open() and close() may be called (with default args) to find out the size.
        The file is supposed to be in its old state when the function returns,
        that is in the same open state and seek position. */
    virtual vfspos size() = 0;

protected:

    /** The ctor is expected to set both name() and fullname();
    The name must remain static throughout the object's lifetime. */
    File(const char *fn);
};

class DiskFile : public File
{
public:
    DiskFile(const char *name);
    virtual ~DiskFile();
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
    virtual const char *getType() const { return "DiskFile"; }

    inline void *getFP() { return _fh; }

protected:
    
    void *_fh; // FILE*
};

class MemFile : public File
{
public:
    enum DeleteMode
    {
        ON_CLOSE,
        ON_DESTROY
    };
    /** Creates a virtual file from a memory buffer. The buffer is passed as-is,
       so for text files you should make sure it ends with a \0 character.
       A deletor function can be passed optionally, that the buffer will be passed to
       when the memory file is destroyed. Pass NULL or leave away to keep the buffer alive. */
    MemFile(const char *name, void *buf, unsigned int size, delete_func delfunc = NULL, DeleteMode delmode = ON_CLOSE);
    virtual ~MemFile();
    /** In order not to modify the passed buffer, MemFile does NOT respect the mode parameter. */
    virtual bool open(const char *mode = NULL) { return !!_buf; }
    virtual bool isopen() const { return !!_buf; } // always open
    virtual bool iseof() const { return _pos >= _size; }
    virtual void close();
    virtual bool seek(vfspos pos, int whence);
    virtual bool flush() { return true; }
    virtual vfspos getpos() const { return _pos; }
    virtual size_t read(void *dst, size_t bytes);
    virtual size_t write(const void *src, size_t bytes);
    virtual vfspos size() { return _size; }
    virtual const char *getType() const { return "MemFile"; }

protected:

    void _clearMem();

    void *_buf;
    vfspos _pos;
    vfspos _size;
    delete_func _delfunc;
    DeleteMode _delmode;
};

VFS_NAMESPACE_END

#endif
