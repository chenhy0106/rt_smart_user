#include <stdio.h>
#include <stdarg.h>
#include <reent.h>

extern void sys_log(char *, int);

int printf(const char *__restrict fmt, ...)
{
    int ret;
    va_list ap;
    char buf[81];

    va_start(ap, fmt);
    ret = vsnprintf(buf, 81, fmt, ap);
    va_end(ap);
    if (ret > 0)
        sys_log(buf, ret);

    return ret;
}
