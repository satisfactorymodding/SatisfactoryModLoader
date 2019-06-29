// VFSBase.h - bass class for VFSDir and VFSFile
// For conditions of distribution and use, see copyright notice in VFS.h

#ifndef VFS_BASE_H
#define VFS_BASE_H

#include <string>
#include "VFSDefines.h"
#include "VFSRefcounted.h"

VFS_NAMESPACE_START

// Used internally. No special properties, just holds some common code.
class VFSBase : public Refcounted
{
public:
    virtual ~VFSBase();

    /** Returns the plain file name. Never NULL. */
    inline const char *name() const { return _name; }

    /** Returns the file name with full path. Never NULL. */
    inline const char *fullname() const { return _fullname.c_str(); }

    /** To avoid strlen() */
    inline size_t fullnameLen() const { return _fullname.length(); }
    // We know that mem addr of _name > _fullname:
    // _fullname: "abc/def/ghi/hjk.txt" (length = 19)
    // _name:                 "hjk.txt" <-- want that length
    // ptr diff: 12
    // so in total: 19 - 12 == 7
    inline size_t nameLen() const { return _fullname.length() - (_name - _fullname.c_str()); }

    /** Basic RTTI, for debugging purposes */
    virtual const char *getType() const = 0;

    /** Can be overloaded to close resources this object keeps open */
    virtual void close() {}

    /** Can be overloaded if necessary. Called by VFSHelper::ClearGarbage() */
    virtual void clearGarbage() {}

protected:
    VFSBase();
    void _setName(const char *n);

private:

    const char *_name; // must point to an address constant during object lifetime (like _fullname.c_str() + N)
                       // (not necessary to have an additional string copy here, just wastes memory)
    std::string _fullname;
};



VFS_NAMESPACE_END

#endif
