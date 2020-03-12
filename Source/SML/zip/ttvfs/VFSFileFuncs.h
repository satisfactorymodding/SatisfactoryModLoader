#ifndef VFS_FILE_FUNCS_H
#define VFS_FILE_FUNCS_H

#include "VFSDefines.h"


VFS_NAMESPACE_START

void *real_fopen(const char *name, const char *mode);
int real_fclose(void *fh);
int real_fseek(void *fh, vfspos offset, int origin);
vfspos real_ftell(void *fh);
size_t real_fread(void *ptr, size_t size, size_t count, void *fh);
size_t real_fwrite(const void *ptr, size_t size, size_t count, void *fh);
int real_feof(void *fh);
int real_fflush(void *fh);

VFS_NAMESPACE_END

#endif
