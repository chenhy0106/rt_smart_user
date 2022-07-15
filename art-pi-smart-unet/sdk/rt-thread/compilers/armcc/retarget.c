#include <stdio.h>
#include <sys/syslog.h>
#include <rt_sys.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define STDIN       0
#define STDOUT      1
#define STDERR      2

#pragma import(__use_no_semihosting_swi)

/* Standard IO device name defines. */
const char __stdin_name[]  = "STDIN";
const char __stdout_name[] = "STDOUT";
const char __stderr_name[] = "STDERR";

FILEHANDLE _sys_open(const char *name, int openmode)
{
    int fd = -1;
    int mode = O_RDONLY;

    /* Register standard Input Output devices. */
    if (strcmp(name, __stdin_name) == 0)
        return (STDIN);
    if (strcmp(name, __stdout_name) == 0)
        return (STDOUT);
    if (strcmp(name, __stderr_name) == 0)
        return (STDERR);

    /* Correct openmode from fopen to open */
    if (openmode & OPEN_PLUS)
    {
        if (openmode & OPEN_W)
        {
            mode |= (O_RDWR | O_TRUNC | O_CREAT);
        }
        else if (openmode & OPEN_A)
        {
            mode |= (O_RDWR | O_APPEND | O_CREAT);
        }
        else
            mode |= O_RDWR;
    }
    else
    {
        if (openmode & OPEN_W)
        {
            mode |= (O_WRONLY | O_TRUNC | O_CREAT);
        }
        else if (openmode & OPEN_A)
        {
            mode |= (O_WRONLY | O_APPEND | O_CREAT);
        }
    }

    fd = open(name, mode, 0);

    return fd;
}

int _sys_close(FILEHANDLE fh)
{
    return close(fh);
}

int _sys_read(FILEHANDLE fh, unsigned char *buf, unsigned len, int mode)
{
    int size;

    size = read(fh, buf, len);
    if (size >= 0)
        return len - size;
    else
        return -1;
}

int _sys_write(FILEHANDLE fh, const unsigned char *buf, unsigned len, int mode)
{
    int size;

    if (fh == 1) //todo
    {
        sys_log(buf, len);
        return 0;
    }

    size = write(fh, buf, len);
    if (size >= 0)
        return len - size;
    else
        return -1;
}

int _sys_seek(FILEHANDLE fh, long pos)
{
    if (fh < STDERR)
        return -1;

    /* position is relative to the start of file fh */
    return lseek(fh, pos, 0);
}

int _sys_tmpnam(char *name, int fileno, unsigned maxlength)
{
    return -1;
}

char *_sys_command_string(char *cmd, int len)
{
    /* no support */
    return cmd;
}

/* This function writes a character to the console. */
void _ttywrch(int ch)
{
    char c;

    c = (char)ch;
    sys_log(&c, 1);
}

long _sys_flen(FILEHANDLE fh)
{
    return -1;
}

int _sys_istty(FILEHANDLE fh)
{
    return 0;
}

void _sys_exit(int return_code)
{
    _exit(return_code);
}
