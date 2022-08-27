#ifndef USOCKET_H_
#define USOCKET_H_

#include "sal_socket.h"

#ifdef __cplusplus
extern "C" {
#endif

int u_socket (int, int, int);

int u_bind (int, const struct sockaddr *, socklen_t);
int u_connect (int, const struct sockaddr *, socklen_t);
int u_listen (int, int);
int u_accept (int, struct sockaddr *__restrict, socklen_t *__restrict);

ssize_t u_send (int, const void *, size_t, int);
ssize_t u_recv (int, void *, size_t, int);
ssize_t u_sendto (int, const void *, size_t, int, const struct sockaddr *, socklen_t);
ssize_t u_recvfrom (int, void *__restrict, size_t, int, struct sockaddr *__restrict, socklen_t *__restrict);

int u_setsockopt (int, int, int, const void *, socklen_t);

#ifdef __cplusplus
}
#endif

#endif