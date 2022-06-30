#ifndef MSVC_DEFS_H // !MSVC_DEFS_H
#define MSVC_DEFS_H

#include <stdio.h>
#include <malloc.h>

#define __builtin_clz(x) __lzcnt(x)
#define __builtin_clzll(x) __lzcnt(x)
#define __builtin_ctz(x) __lzcnt(~(x))
#define __builtin_ctzll(x) __lzcnt(~(x))

#define EMSCRIPTEN

#define PATH_MAX MAX_PATH
#define popen _popen
#define pclose _pclose

struct timeval
{
    long tv_sec;  /* seconds */
    long tv_usec; /* and microseconds */
};

int gettimeofday(struct timeval *tp, void *tzp);

#endif // !MSVC_DEFS_H