#ifndef VFS_SYSTEM_PATHS_H
#define VFS_SYSTEM_PATHS_H

#include <cstddef>
#include <string>
#include "VFSDefines.h"

VFS_NAMESPACE_START

// Returns the current user's home directory, without terminating '/'
std::string GetUserDir();

// Returns a per-user directory suitable to store application specific data,
// without terminating '/'
std::string GetAppDir(const char *appname);


VFS_NAMESPACE_END

#endif
