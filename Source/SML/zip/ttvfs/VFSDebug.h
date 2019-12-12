#ifndef TTVFS_DEBUG_H
#define TTVFS_DEBUG_H

#include "VFSDefines.h"
#include <iosfwd>

VFS_NAMESPACE_START
class Root;

namespace debug {

/** Dump tree structure with debug information to a stream.
    path specifies the subdir to dump; use "" or NULL to dump the whole tree.
    Set level to >= 0 to limit the recursion depth.
    Level < 0 recurses as deep as the tree goes. */
void dumpTree(Root& root, std::ostream& os, const char *path = NULL, int level = -1);


} // end namespace debug
VFS_NAMESPACE_END

#endif
