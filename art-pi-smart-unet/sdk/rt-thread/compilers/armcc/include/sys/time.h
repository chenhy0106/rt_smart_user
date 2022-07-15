#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#include <time.h>

struct timespec {
    time_t  tv_sec;     /* seconds */
    long    tv_nsec;    /* and nanoseconds */
};

#endif
