#ifndef _GENERAL_
#define _GENERAL_

#include <stddef.h>

static inline int min_i(const int a, const int b)
{
    return a < b ? a : b;
}

static inline int max_i(const int a, const int b)
{
    return a > b ? a : b;
}

#endif
