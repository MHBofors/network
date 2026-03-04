#ifndef INET_SOCKET_H
#define INET_SOCKET_H

#include <sys/socket.h>
#include <netdb.h>

int inet_connect(const char *host, const char *service, int type);
int inet_bind(const char *host, const char *service, int type);

#endif /* INET_SOCKET_H */
