#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

#include "inet_socket.h"

int inet_connect(const char *host, const char *service, int type) {
	struct addrinfo hints = {0};
	struct addrinfo *ai_list, *ai_node;
	int sockfd;

	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = type;

	if(getaddrinfo(host, service, &hints, &ai_list) != 0) {
		errno = ENOSYS;
		return -1;
	}

	for(ai_node = ai_list; ai_node != NULL; ai_node = ai_node->ai_next) {
		if((sockfd = socket(ai_node->ai_family, ai_node->ai_socktype, ai_node->ai_protocol)) == -1) 
			continue; /* ON ERROR */

		if(connect(sockfd, ai_node->ai_addr, ai_node->ai_addrlen) != -1)
			break; /* ON SUCCESS */

		close(sockfd); /* CLOSE SOCKET ON FAILED CONNECTION */
	}

	freeaddrinfo(ai_list);

	return (ai_node == NULL) ? -1 : sockfd;
}

int inet_bind(const char *host, const char *service, int type) {
	struct addrinfo hints = {0};
	struct addrinfo *ai_list, *ai_node;
	int sockfd;

	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = type;

	if(getaddrinfo(host, service, &hints, &ai_list) != 0) {
		errno = ENOSYS;
		return -1;
	}

	for(ai_node = ai_list; ai_node != NULL; ai_node = ai_node->ai_next) {
		if((sockfd = socket(ai_node->ai_family, ai_node->ai_socktype, ai_node->ai_protocol)) == -1) 
			continue; /* ON ERROR */

		if(bind(sockfd, ai_node->ai_addr, ai_node->ai_addrlen) != -1)
			break; /* ON SUCCESS */

		close(sockfd); /* CLOSE SOCKET ON FAILED CONNECTION */
	}

	freeaddrinfo(ai_list);

	return (ai_node == NULL) ? -1 : sockfd;
}
