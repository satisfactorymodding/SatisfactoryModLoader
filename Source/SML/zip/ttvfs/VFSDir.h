// VFSDir.h - basic directory interface + classes
// For conditions of distribution and use, see copyright notice in VFS.h

#ifndef VFSDIR_H
#define VFSDIR_H

#include "VFSBase.h"
#include <map>
#include <cstring>

#ifdef VFS_USE_HASHMAP
#  include "VFSHashmap.h"
#  include "VFSTools.h"
#endif

VFS_NAMESPACE_START


#ifdef VFS_IGNORE_CASE

struct ci_less
{
    inline bool operator() (const char *a, const char *b) const
    {
        return VFS_STRICMP(a, b) < 0;
    }
};
typedef ci_less map_compare;

inline int casecmp(const char *a, const char *b)
{
    return VFS_STRICMP(a, b);
}

#else // VFS_IGNORE_CASE

struct cs_less
{
    inline bool operator() (const char *a, const char *b) const
    {
        return strcmp(a, b) < 0;
    }
};
typedef cs_less map_compare;

inline int casecmp(const char *a, const char *b)
{
    return strcmp(a, b);
}


#endif // VFS_IGNORE_CASE



class Dir;
class DirBase;
class DirView;
class File;
class VFSLoader;


// Avoid using std::string as key.
// The file names are known to remain constant during each object's lifetime,
// so just keep the pointers and use an appropriate comparator function.
typedef std::map<const char *, CountedPtr<DirBase>, map_compare> Dirs;
typedef std::map<const char *, CountedPtr<File>, map_compare> Files;


class DirBase : public VFSBase
{
public:
    DirBase(const char *fullpath);
    virtual ~DirBase();

    /** Returns a file for this dir's subtree. Descends if necessary.
    Returns NULL if the file is not found. */
    File *getFile(const char *fn);

    /** Returns a subdir, descends if necessary. If forceCreate is true,
    create directory tree if it does not exist, and return the originally requested
    subdir. Otherwise return NULL if not found. */
    DirBase *getDir(const char *subdir);
    std::pair<DirBase*, DirBase*> _getDirEx(const char *subdir, const char * const fullpath, bool forceCreate = false, bool lazyLoad = true, bool useSubtrees = true);

    /** Returns a file from this dir's file map.
    Expects the actual file name without path - does NOT descend. */
    virtual File *getFileByName(const char *fn, bool lazyLoad = true) = 0;
    virtual DirBase *getDirByName(const char *fn, bool lazyLoad = true, bool useSubtrees = true);

    virtual File *getFileFromSubdir(const char *subdir, const char *file) = 0;

    /** Iterate over all files or directories, calling a callback function,
    optionally with additional userdata. If safe is true, iterate over a copy.
    This is useful if the callback function modifies the tree, e.g.
    adds or removes files. */
    virtual void forEachDir(DirEnumCallback f, void *user = NULL, bool safe = false);
    virtual void forEachFile(FileEnumCallback f, void *user = NULL, bool safe = false) = 0;

    virtual void clearGarbage();

    virtual bool _addToView(char *path, DirView& view) = 0;
    DirBase *_createNewSubdir(const char *name) const;
    DirBase *_createAndInsertSubtree(const char *name);

protected:

    /** Creates a new dir of the same type to be used as child of this. */
    virtual DirBase *createNew(const char *dir) const = 0;



    Dirs _subdirs;

};

class Dir : public DirBase
{
public:

    Dir(const char *fullpath, VFSLoader *ldr);
    virtual ~Dir();

    /** Adds a file directly to this directory, allows any name.
        If the file name contains a path, descend the tree to the target dir.
        Not-existing subdirs are created on the way.
        If another file with this name already exists, drop the old one out.
        Returns whether the file was actually added (false if the same file already existed) */
    bool add(File *f);

    /** Enumerate directory with given path. Clears previously loaded entries. */
    virtual void load() = 0;

    void forEachFile(FileEnumCallback f, void *user = NULL, bool safe = false);
    void forEachDir(DirEnumCallback f, void *user = NULL, bool safe = false);

    virtual void clearGarbage();

    bool _addToView(char *path, DirView& view);
    DirBase *getDirByName(const char *dn, bool lazyLoad = true, bool useSubtrees = true);
    File *getFileByName(const char *fn, bool lazyLoad = true);
    File *getFileFromSubdir(const char *subdir, const char *file);

    bool _addRecursiveSkip(File *f, size_t skip = 0);

protected:

    bool _addSingle(File *f);

    inline VFSLoader *getLoader() const { return _loader; }

    Files _files;

private:
    VFSLoader *_loader;
};

class DiskDir : public Dir
{
public:
    DiskDir(const char *path, VFSLoader *ldr);
    virtual ~DiskDir() {};

    // virtual overloads
    void load();
    DiskDir *createNew(const char *dir) const;
    const char *getType() const { return "DiskDir"; }
};

class MemDir : public Dir
{
public:
    MemDir(const char *fullpath) : Dir(fullpath, NULL) {}
    virtual ~MemDir() {}

    // virtual overloads
    void load() {}
    MemDir *createNew(const char *dir) const;
    const char *getType() const { return "MemDir"; }
};

VFS_NAMESPACE_END

#endif
