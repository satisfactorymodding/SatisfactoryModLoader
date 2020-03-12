#ifndef VFS_DIR_VIEW_H
#define VFS_DIR_VIEW_H

#include <vector>
#include "VFSDir.h"

VFS_NAMESPACE_START

class InternalDir;
class File;

class DirView : public DirBase
{
public:
    DirView();
    virtual ~DirView();
    void init(const char *);
    void add(DirBase *);

    File *getFileByName(const char *fn, bool lazyLoad = true);
    void forEachDir(DirEnumCallback f, void *user = NULL, bool safe = false);
    void forEachFile(FileEnumCallback f, void *user = NULL, bool safe = false);
    File *getFileFromSubdir(const char *subdir, const char *file);

    const char *getType() const { return "DirView"; }
    DirBase *createNew(const char *dir) const { return NULL; }

    bool _addToView(char *path, DirView& view);

protected:

    typedef std::vector<CountedPtr<DirBase> > ViewList;
    ViewList _view;

};


VFS_NAMESPACE_END

#endif

