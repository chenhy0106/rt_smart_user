#include <stdio.h>

int puts(const char *s)
{
	int r;

    r = strlen(s);
    sys_log(s, r);

	return r;
}
