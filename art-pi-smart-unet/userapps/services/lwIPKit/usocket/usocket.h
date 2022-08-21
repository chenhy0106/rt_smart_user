#ifndef USOCKET_H_
#define USCOKET_H_

#include <sys/socket.h>

int socket_internal (int domain, int type, int protocol);
int accept_internal(int s, struct sockaddr *addr, socklen_t *addrlen);
int bind_internal(int s, const struct sockaddr *name, socklen_t namelen);
int connect_internal(int s, const struct sockaddr *name, socklen_t namelen);
int listen_internal(int s, int backlog);
int send_internal(int s, const void *dataptr, size_t size, int flags);
int recv_internal(int s, void *mem, size_t len, int flags);
int recvfrom_internal(int s, void *mem, size_t len, int flags,
             struct sockaddr *from, socklen_t *fromlen);
int send_internal(int s, const void *dataptr, size_t size, int flags);
int sendto_internal(int s, const void *dataptr, size_t size, int flags,
           const struct sockaddr *to, socklen_t tolen);
int setsockopt_internal(int s, int level, int optname, const void *optval, socklen_t optlen);

#endif