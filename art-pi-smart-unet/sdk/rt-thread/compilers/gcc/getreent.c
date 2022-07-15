#include <reent.h>
#include <stdio.h>

struct _reent impure_data = _REENT_INIT(impure_data);

struct _reent *__getreent(void)
{
    return &impure_data;
}

struct _reent *__getglobal(void)
{
    return &impure_data;
}
