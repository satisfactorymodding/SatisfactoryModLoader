// VFSRoot.h - glues it all together and makes use simple
// For conditions of distribution and use, see copyright notice in VFS.h

#ifndef VFSHELPER_H
#define VFSHELPER_H

#include <vector>
#include <list>
#include <string>

#include "VFSRefcounted.h"


VFS_NAMESPACE_START

class DirBase;
class Dir;
class InternalDir;
class File;
class VFSLoader;
class VFSArchiveLoader;
class DirView;


/** Root - simplify working with the VFS tree.
    
    Everything is reference-counted. If you store pointers to contained objects externally,
    use ttvfs::CountedPtr<>.
    To enumerate the file tree for debugging, use ttvfs::debug::dumpTree().
*/
class Root
{
public:
    Root();
    virtual ~Root();

    /** Reset an instance to its initial state.
        Drops all subdirs, loaders, archive loaders, mount points, ...*/
    virtual void Clear();

    /** Do cleanups from time to time. For internal classes, this is a no-op.
        Extensions may wish to override this method do do cleanup jobs. */
    virtual void ClearGarbage();

    /** Mount a directory in the tree to a different location.
        This means that the contents of src will appear in dest.
        Be careful not to create circles! */
    void Mount(const char *src, const char *dest);

    /** Like Mount(), but in reverse.
        Returns true if the mount point does not exist after the call,
        (that is, if it was removed or it never existed in the first place),
        false if src or dst do not exist. */
    bool Unmount(const char *src, const char *dest);

    /** Add an archive file to the tree, which can then be addressed like a folder,
        e.g. "path/to/example.zip/file.txt".
        Returns a pointer to the actual Dir object that represents the added archive, or NULL if failed.
        The opaque pointer is passed directly to each loader and can contain additional parameters,
        such as a password to open the file.
        Read the comments in VFSArchiveLoader.h for an explanation how it works.
        If you have no idea, leave it NULL, because it can easily cause a crash if not used carefully. */
    Dir *AddArchive(File *file, const char *path = NULL, void *opaque = NULL);

    /** Add an archive by file name. This is a quick convenience method using the method above. */
    Dir *AddArchive(const char *arch, void *opaque = NULL);

    /** Add a loader that can look for files on demand.
        Do not add more than one instance of a loader type.
        The optional path parameter is experimental, do not use it.
        Returns the index of the added loader, which is required for RemoveLoader().
        If the loader will not be removed, ignore the return value.*/
    int AddLoader(VFSLoader *ldr, const char *path = NULL);

    /** Remove a previously added loader. Use the index returned by AddLoader(). */
    void RemoveLoader(int index, const char *path = NULL);

    /** Add an archive loader that can open archives of various types.
        Whenever an archive file is requested to be opened by AddArchive(),
        it is sent through each registered loader until one of them recognizes
        the format and can open it.
        Returns the index of the added loader, which is required for RemoveArchiveLoader().
        If the loader will not be removed, ignore the return value.*/
    int AddArchiveLoader(VFSArchiveLoader *ldr);

    /** Remove a previously added archive loader. Use the index returned by AddArchiveLoader(). */
    void RemoveArchiveLoader(int index);

    /** Get a file from the merged tree. Asks loaders if the file is not in the tree.
        If found by a loader, the file will be added to the tree. */
    File *GetFile(const char *fn);

    /** Fills a DirView object with a list of directories that match the specified path.
        This is the preferred way to enumerate directories, as it respects and collects
        mount points during traversal. The DirView instance can be re-used until any mount or unmount
        operation takes place. If the content of a contained directory changes, this is reflected in the view.
        (Added dirs or files will appear, removed ones disappear).
        Use DirView::forEachFile() or DirView::forEachDir() to iterate. */
    bool FillDirView(const char *path, DirView& view);

    /** Convenience method to iterate over all files and subdirs of a given path.
        Returns true if the path exists and iteration was successful.
        Both callback functions are optional, pass NULL if not interested.
        user is an opaque pointer passed to the callbacks.
        Set safe = true if the file tree is modified by a callback function. */
    bool ForEach(const char *path, FileEnumCallback fileCallback = NULL, DirEnumCallback dirCallback = NULL, void *user = NULL, bool safe = false);

    /** Remove a file or directory from the tree */
    //bool Remove(File *vf);
    //bool Remove(Dir *dir);
    //bool Remove(const char *name); // TODO: CODE ME


    // --- Less common functions below ---

    /** Adds a Dir object into the merged tree. If subdir is NULL (the default),
    use the full path of dir. The tree will be extended if target dir does not exist.
    Files in the tree will be overridden if already existing.
    Like with Mount(); be careful not to create cycles. */
    void AddVFSDir(DirBase *dir, const char *subdir = NULL);

    /** Removes a dir from a given path previously added to via AddVFSDir().
    Returns true if dir does not exist at subdir after the call. */
    bool RemoveVFSDir(DirBase *dir, const char *subdir /* = NULL */);

    /** Returns the tree root, which is usually the working directory.
    Same as GetDir("").
    You will most likely not need this function. */
    DirBase *GetDirRoot();

    /** Get a directory from the merged tree. If create is true and the directory does not exist,
    build the tree structure and return the newly created dir. NULL otherwise.
    You will most likely not need this function.
    Use FillDirView() on a DirView object or ForEach() to iterate over directory contents. */
    DirBase *GetDir(const char* dn, bool create = false);

protected:

    InternalDir *_GetDirByLoader(VFSLoader *ldr, const char *fn, const char *unmangled);

    class _LoaderInfo
    {
    public:
        _LoaderInfo(const char *path) : isnull(path == NULL), pathstr(path ? path : "") {}
        inline const char *getPath() { return isnull ? NULL : pathstr.c_str(); }
    private:
        bool isnull;
        std::string pathstr;
    };

    typedef std::vector<CountedPtr<VFSLoader> > LoaderArray;
    typedef std::vector<CountedPtr<VFSArchiveLoader> > ArchiveLoaderArray;
    typedef std::vector<_LoaderInfo> ArchiveLoaderInfoArray;

    LoaderArray loaders; // If files are not in the tree, maybe one of these is able to find it.
    CountedPtr<InternalDir> merged; // contains the merged virtual/actual file system tree
    ArchiveLoaderArray archLdrs;
    ArchiveLoaderInfoArray loadersInfo;
};

VFS_NAMESPACE_END

#endif
