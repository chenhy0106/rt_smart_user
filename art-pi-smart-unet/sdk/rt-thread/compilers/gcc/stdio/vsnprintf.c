#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdarg.h>

struct cookie
{
    char *s;
    int n;
};

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static int sn_write(struct _reent *data, void *f, const char *s, int l)
{
    struct cookie *c = ((FILE*)f)->_cookie;
    int k = MIN(c->n, l);

    if (k)
    {
        memcpy(c->s, s, k);
        c->s += k;
        c->n -= k;
    }
    *c->s = 0;

    /* pretend to succeed, even if we discarded extra data */
    return k;
}

int vsnprintf(char *restrict s, size_t n, const char *restrict fmt, va_list ap)
{
    struct cookie c;
    FILE f;

    c.s = s;
    c.n = n -1;

    f._write = sn_write;
    f._cookie = &c;

    *c.s = 0;
    return vfprintf(&f, fmt, ap);
}
