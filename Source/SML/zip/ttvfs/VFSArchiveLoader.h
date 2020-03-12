#ifndef VFS_ARCHIVE_LOADER_H
#define VFS_ARCHIVE_LOADER_H

#include "VFSDefines.h"
#include "VFSRefcounted.h"

VFS_NAMESPACE_START

class Dir;
class File;
class VFSLoader;

// Generic Archive loader interface that is supposed to return a valid Dir pointer when it
// was able to load 'arch' as an archive, and NULL if there was an error or the loader is
// unable to load that file type.
// 'asSubdir' - if this is true, the archive will be accessible as a folder (as in "test.zip/file.dat"),
//              otherwise the files are mounted in place of the archive.
// 'ldr' - can be set to an external file loader in case the file/folder tree can not be fully generated
//         at load time.
// 'opaque' - a POD struct which *must* have a `void (*)(void*, void*, const char*)`
//            function pointer as first member (at offset 0).
//            The struct pointer is then passed to that function, along with a pointer to an internal object,
//            whatever this is. The derived loader knows what this object is - something that this callback
//            will be interested in modifying, anyways. The rest of the struct can carry the data required to
//            modify this object.
//            The const char parameter is a string unique for each loader (to prevent accessing the pointer
//            in a wrong way by the wrong loader). Example below.
class VFSArchiveLoader : public Refcounted
{
public:
    virtual ~VFSArchiveLoader() {}

    virtual Dir *Load(File *arch, VFSLoader **ldr, void *opaque = NULL) = 0;
};

/* A possible struct for 'opaque' would be:

struct ExampleLoadParams
{
    void (*callback)(void *, void *, const char *);
    const char *key;
    unsigned int keylen;
};

And then the call would look like:
(Assuming PakFile is an archive file class that represents an archive)

void pakSetup(void *data, void *arch, const char *id)
{
    if(strcmp(id, "pak")) // Be sure we're in the right loader.
        return;
    ExampleLoadParams *pm = (ExampleLoadParams*)p;
    PakArchive *pak = (PakArchive*)arch;
    pak->SetKey(pm->key, pm->keylen);
}

ExampleLoadParams p;
p.callback = &pakSetup;
p.key = "123456";
p.keylen = 6;
vfs.AddArchive("data.pak", false, "", &p);

Where p in turn will be passed to the PAK loader.

*/

VFS_NAMESPACE_END

#endif
