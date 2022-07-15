/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-20     Jesven       the first version
 * 2019-10-01     Bernard      code cleanup
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>

#include <rtthread.h>

void *rt_malloc(rt_size_t nbytes)
{
    return malloc(nbytes);
}

void rt_free(void *ptr)
{
    return free(ptr);
}

void *rt_realloc(void *ptr, rt_size_t nbytes)
{
    return realloc(ptr, nbytes);
}

void *rt_calloc(rt_size_t count, rt_size_t size)
{
    return calloc(count, size);
}

rt_int32_t rt_snprintf(char *buf, rt_size_t size, const char *format, ...)
{
    int ret;
    va_list ap;
    va_start(ap, format);
    ret = vsnprintf(buf, size, format, ap);
    va_end(ap);
    return ret;
}

rt_int32_t rt_sprintf(char *buf, const char *format, ...)
{
    int ret;
    va_list ap;
    va_start(ap, format);
    ret = vsprintf(buf, format, ap);
    va_end(ap);
    return ret;
}

rt_int32_t rt_vsnprintf(char *buf,
    rt_size_t size,
    const char *fmt,
    va_list args)
{
    return (rt_int32_t)vsnprintf(buf, size, fmt, args);
}

void rt_kprintf(const char *fmt, ...)
{
    int ret;
    va_list ap;
    char buf[81];

    va_start(ap, fmt);
    ret = vsnprintf(buf, 81, fmt, ap);
    va_end(ap);
    if (ret > 0)
        printf("%s", buf);
}

char *rt_strdup(const char* s)
{
    return strdup(s);
}

char *rt_strstr(const char *s1, const char *s2)
{
    return strstr(s1, s2);
}

rt_int32_t rt_strcmp(const char *cs, const char *ct)
{
    return (rt_int32_t)strcmp(cs, ct);
}

rt_size_t rt_strlen(const char *src)
{
    return strlen(src);
}

rt_int32_t rt_strncmp(const char *cs, const char *ct, rt_ubase_t count)
{
    return strncmp(cs, ct, count);
}

char *rt_strncpy(char *dest, const char *src, rt_ubase_t n)
{
    return strncpy(dest, src, n);
}

rt_uint32_t rt_strcasecmp(const char *a, const char *b)
{
    return strcasecmp(a, b);
}

void *rt_memset(void *src, int c, rt_ubase_t n)
{
    return memset(src, c, n);
}

void *rt_memcpy(void *dest, const void *src, rt_ubase_t n)
{
    return memcpy(dest, src, n);
}

rt_int32_t rt_memcmp(const void *cs, const void *ct, rt_ubase_t count)
{
    return memcmp(cs, ct, count);
}

void *rt_memmove(void *dest, const void *src, rt_ubase_t n)
{
    return memmove(dest, src, n);
}

rt_tick_t rt_tick_from_millisecond(rt_int32_t ms)
{
    rt_tick_t tick;

    if (ms < 0)
    {
        tick = (rt_tick_t)RT_WAITING_FOREVER;
    }
    else
    {
        tick = RT_TICK_PER_SECOND * (ms / 1000);
        tick += (RT_TICK_PER_SECOND * (ms % 1000) + 999) / 1000;
    }

    /* return the calculated tick */
    return tick;
}

/**
 * This function allocates a memory block, which address is aligned to the
 * specified alignment size.
 *
 * @param size the allocated memory block size
 * @param align the alignment size
 *
 * @return the allocated memory block on successful, otherwise returns RT_NULL
 */
void *rt_malloc_align(rt_size_t size, rt_size_t align)
{
    void *ptr;
    void *align_ptr;
    int uintptr_size;
    rt_size_t align_size;

    /* sizeof pointer */
    uintptr_size = sizeof(void*);
    uintptr_size -= 1;

    /* align the alignment size to uintptr size byte */
    align = ((align + uintptr_size) & ~uintptr_size);

    /* get total aligned size */
    align_size = ((size + uintptr_size) & ~uintptr_size) + align;
    /* allocate memory block from heap */
    ptr = rt_malloc(align_size);
    if (ptr != RT_NULL)
    {
        /* the allocated memory block is aligned */
        if (((rt_ubase_t)ptr & (align - 1)) == 0)
        {
            align_ptr = (void *)((rt_ubase_t)ptr + align);
        }
        else
        {
            align_ptr = (void *)(((rt_ubase_t)ptr + (align - 1)) & ~(align - 1));
        }

        /* set the pointer before alignment pointer to the real pointer */
        *((rt_ubase_t *)((rt_ubase_t)align_ptr - sizeof(void *))) = (rt_ubase_t)ptr;

        ptr = align_ptr;
    }

    return ptr;
}

/**
 * This function release the memory block, which is allocated by
 * rt_malloc_align function and address is aligned.
 *
 * @param ptr the memory block pointer
 */
void rt_free_align(void *ptr)
{
    void *real_ptr;

    real_ptr = (void *) * (rt_ubase_t *)((rt_ubase_t)ptr - sizeof(void *));
    rt_free(real_ptr);
}

void rt_assert_handler(const char *ex_string, const char *func, rt_size_t line)
{
    printf("UserAPP: (%s) assertion failed at function:%s, line number:%d \n", ex_string, func, (int)line);
    exit(-1);
}

