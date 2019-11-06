/* ttvfs -- tiny tree virtual file system

// ttvfs.h - all the necessary includes to get a basic VFS working
// Only include externally, not inside the library.

See VFSDefines.h for compile configration.


---------[ License ]----------
MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


#ifndef TTVFS_VFS_H
#define TTVFS_VFS_H

#include "VFSDefines.h"
#include <cstring>

VFS_NAMESPACE_START

bool _checkCompatInternal(_AbiCheck *abi);

/** It is recommended to call this function early in your code
    and ensure it returns true - if it does not, compiler settings
    are inconsistent, which may cause otherwise hard to detect problems. */
inline static bool checkCompat()
{
    _AbiCheck abi;
    memset(&abi, 0, sizeof(abi));
    abi.structSize = sizeof(abi);
    abi.vfsposSize = sizeof(vfspos);

#ifdef VFS_LARGEFILE_SUPPORT
    abi.largefile = 1;
#endif

#ifdef VFS_IGNORE_CASE
    abi.nocase = 1;
#endif

    return _checkCompatInternal(&abi);
}
VFS_NAMESPACE_END


#include <string>
#include "VFSRoot.h"
#include "VFSFile.h"
#include "VFSDir.h"
#include "VFSDirView.h"
#include "VFSSystemPaths.h"
#include "VFSTools.h"
#include "VFSLoader.h"


// Check to enforce correct including.
#ifdef VFS_INTERNAL_H
#error Oops, VFS_INTERNAL_H is defined, someone messed up and included VFSInternal.h wrongly.
#endif

#endif
