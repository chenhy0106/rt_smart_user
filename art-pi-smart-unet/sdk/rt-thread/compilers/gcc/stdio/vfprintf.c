#include <reent.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define isdigit(c)  ((unsigned)((c) - '0') < 10)

int32_t divide(long *n, int32_t base)
{
    int32_t res;

    /* optimized for processor which does not support divide instructions. */
    if (base == 10)
    {
        res = ((uint32_t) * n) % 10U;
        *n = ((uint32_t) * n) / 10U;
    }
    else
    {
        res = ((uint32_t) * n) % 16U;
        *n = ((uint32_t) * n) / 16U;
    }

    return res;
}

int skip_atoi(const char **s)
{
    register int i = 0;
    while (isdigit(**s))
        i = i * 10 + *((*s)++) - '0';

    return i;
}

#define ZEROPAD     (1 << 0)    /* pad with zero */
#define SIGN        (1 << 1)    /* unsigned/signed long */
#define PLUS        (1 << 2)    /* show plus */
#define SPACE       (1 << 3)    /* space if plus */
#define LEFT        (1 << 4)    /* left justified */
#define SPECIAL     (1 << 5)    /* 0x */
#define LARGE       (1 << 6)    /* use 'ABCDEF' instead of 'abcdef' */

static int print(FILE *f, const char *s, int l, int *cnt)
{
    int len;

    len = f->_write(NULL, f, s, l);
    if (len == l)
    {
        *cnt += len;
        return 0;
    }

    return -1;
}

static int print_number(FILE *fp,
                        long num,
                        int  base,
                        int  s,
                        int  precision,
                        int  type,
                        int  *cnt)
{
    char c, sign;
#ifdef RT_PRINTF_LONGLONG
    char tmp[32];
#else
    char tmp[16];
#endif
    char buf[32];
    int pos = 0;

    const char *digits;
    static const char small_digits[] = "0123456789abcdef";
    static const char large_digits[] = "0123456789ABCDEF";
    register int i;
    register int size;

    size = s;

    digits = (type & LARGE) ? large_digits : small_digits;
    if (type & LEFT)
        type &= ~ZEROPAD;

    c = (type & ZEROPAD) ? '0' : ' ';

    /* get sign */
    sign = 0;
    if (type & SIGN)
    {
        if (num < 0)
        {
            sign = '-';
            num = -num;
        }
        else if (type & PLUS)
            sign = '+';
        else if (type & SPACE)
            sign = ' ';
    }

#ifdef RT_PRINTF_SPECIAL
    if (type & SPECIAL)
    {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
#endif

    i = 0;
    if (num == 0)
        tmp[i++] = '0';
    else
    {
        while (num != 0)
            tmp[i++] = digits[divide(&num, base)];
    }

    if (i > precision)
        precision = i;
    size -= precision;

    if (!(type & (ZEROPAD | LEFT)))
    {
        if ((sign) && (size > 0))
            size--;

        while (size-- > 0)
        {
            buf[pos] = ' ';
            pos ++;
        }
    }

    if (sign)
    {
        buf[pos] = sign;
        pos ++;
        -- size;
    }

#ifdef RT_PRINTF_SPECIAL
    if (type & SPECIAL)
    {
        if (base == 8)
        {
            if (buf <= end)
                *buf = '0';
            ++ buf;
        }
        else if (base == 16)
        {
            if (buf <= end)
                *buf = '0';
            ++ buf;
            if (buf <= end)
            {
                *buf = type & LARGE ? 'X' : 'x';
            }
            ++ buf;
        }
    }
#endif

    /* no align to the left */
    if (!(type & LEFT))
    {
        while (size-- > 0)
        {
            buf[pos] = c;
            pos ++;
        }
    }

    while (i < precision--)
    {
        buf[pos] = '0';
        pos ++;
    }

    /* put number in the temporary buffer */
    while (i-- > 0)
    {
        buf[pos] = tmp[i];
        pos ++;
    }

    while (size-- > 0)
    {
        buf[pos] = ' ';
        pos ++;
    }

    return print(fp, buf, pos, cnt);
}

static int32_t _vfprintf(FILE *fp, const char *fmt, va_list args)
{
#ifdef RT_PRINTF_LONGLONG
    unsigned long long num;
#else
    uint32_t num;
#endif
    int i, len;
    char c;
    const char *s;

    uint8_t base;            /* the base of number */
    uint8_t flags;           /* flags to print number */
    uint8_t qualifier;       /* 'h', 'l', or 'L' for integer fields */
    int32_t field_width;     /* width of output field */

    int precision;      /* min. # of digits for integers and max for a string */
    int cnt = 0;

    for (; *fmt ; ++fmt)
    {
        if (*fmt != '%')
        {
            if (print(fp, fmt, 1, &cnt))
                goto err;
            continue;
        }

        /* process flags */
        flags = 0;

        while (1)
        {
            /* skips the first '%' also */
            ++ fmt;
            if (*fmt == '-')
                flags |= LEFT;
            else if (*fmt == '+')
                flags |= PLUS;
            else if (*fmt == ' ')
                flags |= SPACE;
            else if (*fmt == '#')
                flags |= SPECIAL;
            else if (*fmt == '0')
                flags |= ZEROPAD;
            else
                break;
        }

        /* get field width */
        field_width = -1;
        if (isdigit(*fmt))
            field_width = skip_atoi(&fmt);
        else if (*fmt == '*')
        {
            ++ fmt;
            /* it's the next argument */
            field_width = va_arg(args, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

        /* get the precision */
        precision = -1;
        if (*fmt == '.')
        {
            ++ fmt;
            if (isdigit(*fmt))
                precision = skip_atoi(&fmt);
            else if (*fmt == '*')
            {
                ++ fmt;
                /* it's the next argument */
                precision = va_arg(args, int);
            }
            if (precision < 0)
                precision = 0;
        }

        /* get the conversion qualifier */
        qualifier = 0;
#ifdef RT_PRINTF_LONGLONG
        if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L')
#else
        if (*fmt == 'h' || *fmt == 'l')
#endif
        {
            qualifier = *fmt;
            ++ fmt;
#ifdef RT_PRINTF_LONGLONG
            if (qualifier == 'l' && *fmt == 'l')
            {
                qualifier = 'L';
                ++ fmt;
            }
#endif
        }

        /* the default base */
        base = 10;

        switch (*fmt)
        {
        case 'c':
            if (!(flags & LEFT))
            {
                while (--field_width > 0)
                {
                    c = ' ';
                    if (print(fp, &c, 1, &cnt))
                        goto err;
                }
            }

            /* get character */
            c = (uint8_t)va_arg(args, int);

            if(print(fp, &c, 1, &cnt))
                goto err;

            /* put width */
            while (--field_width > 0)
            {
                c = ' ';
                if (print(fp, &c, 1, &cnt))
                    goto err;
            }
            continue;

        case 's':
            s = va_arg(args, char *);
            if (!s)
                s = "(NULL)";

            len = strlen(s);

            if (precision > 0 && len > precision)
                len = precision;

            if (!(flags & LEFT))
            {
                while (len < field_width--)
                {
                    c = ' ';
                    if (print(fp, &c, 1, &cnt))
                        goto err;
                }
            }

            if (print(fp, s, len, &cnt))
                goto err;

            s += len;
            c = ' ';
            while (len < field_width--)
            {
                if(print(fp, &c, 1, &cnt))
                    goto err;
            }
            continue;

        case 'p':
        {
            if (field_width == -1)
            {
                field_width = sizeof(void *) << 1;
                flags |= ZEROPAD;
            }

            i = print_number(fp,
                             (long)va_arg(args, void *),
                             16, field_width, precision, flags, &cnt);
            if (i)
                goto err;
        }
        continue;

        case '%':
            c = '%';
            if (print(fp, &c, 1, &cnt))
                goto err;

            continue;

        /* integer number formats - set up the flags and "break" */
        case 'o':
            base = 8;
            break;

        case 'X':
            flags |= LARGE;
        case 'x':
            base = 16;
            break;

        case 'd':
        case 'i':
            flags |= SIGN;
        case 'u':
            break;

        default:
            c = '%';
            if (print(fp, &c, 1, &cnt))
                goto err;

            if (*fmt)
            {
                if (print(fp, fmt, 1, &cnt))
                    goto err;
            }
            else
            {
                -- fmt;
            }
            continue;
        }

#ifdef RT_PRINTF_LONGLONG
        if (qualifier == 'L')
            num = va_arg(args, long long);
        else if (qualifier == 'l')
#else
        if (qualifier == 'l')
#endif
        {
            num = va_arg(args, uint32_t);
            if (flags & SIGN)
                num = (int32_t)num;
        }
        else if (qualifier == 'h')
        {
            num = (uint16_t)va_arg(args, int32_t);
            if (flags & SIGN)
                num = (int16_t)num;
        }
        else
        {
            num = va_arg(args, uint32_t);
            if (flags & SIGN)
                num = (int32_t)num;
        }

        i = print_number(fp, num, base, field_width, precision, flags, &cnt);

        if (i)
            goto err;
    }

err:
    return cnt;
}

int vfprintf(FILE * fp, const char *fmt, va_list ap)
{

    return _vfprintf(fp, fmt, ap);
}
