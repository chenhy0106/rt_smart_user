#ifndef	_UNISTD_H
#define	_UNISTD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

int close(int);
ssize_t read(int, void *, size_t);
ssize_t write(int, const void *, size_t);
off_t lseek(int, off_t, int);

int unlink(const char *);
int rmdir(const char *);

#ifdef __cplusplus
}
#endif

#endif
