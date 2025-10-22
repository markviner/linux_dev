#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int unlink(const char *pathname) {
    static int (*real_unlink)(const char *) = NULL;
    if (!real_unlink)
        real_unlink = dlsym(RTLD_NEXT, "unlink");

    if (strstr(pathname, "PROTECT") != NULL) {
        fprintf(stderr, "[protect.so] refusing to delete \"%s\"\n", pathname);
        errno = EPERM;
        return -1;
    }

    return real_unlink(pathname);
}

int unlinkat(int dirfd, const char *pathname, int flags) {
    static int (*real_unlinkat)(int, const char *, int) = NULL;
    if (!real_unlinkat)
        real_unlinkat = dlsym(RTLD_NEXT, "unlinkat");

    if (strstr(pathname, "PROTECT") != NULL) {
        fprintf(stderr, "[protect.so] refusing to delete \"%s\"\n", pathname);
        errno = EPERM;
        return -1;
    }

    return real_unlinkat(dirfd, pathname, flags);
}
