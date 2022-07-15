#include <reent.h>
#include <stdlib.h>
#include <sys/rtt_syscall.h>

_ssize_t _write_r(struct _reent *ptr, int fd, const void *buf, size_t nbytes)
{
    _ssize_t ret;

    ret = syscall(_NRSYS_write, fd, buf, nbytes);

    return ret;
}

int _open_r(struct _reent *ptr, const char *file, int flag, int mode)
{
    return syscall(_NRSYS_open, file, flag, mode);
}

_ssize_t _read_r(struct _reent *ptr, int fd, void *buf, size_t size)
{
    return syscall(_NRSYS_read, fd, buf, size);
}

int _close_r(struct _reent *ptr, int fd)
{
    return syscall(_NRSYS_close, fd);
}

_off_t _lseek_r(struct _reent *ptr, int fd, _off_t pos, int whence)
{
    return syscall(_NRSYS_lseek, fd, pos, whence);
}

int _isatty_r(struct _reent *ptr, int fd)
{
    return 0;
}

int _fstat_r(struct _reent *ptr, int fd, struct stat *pstat)
{
    return syscall(_NRSYS_fstat, fd, pstat);
}

