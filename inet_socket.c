#include <arpa/inet.h>
#include <errno.h>

#include <netinet/in.h>
#include <unistd.h>


#include "inet_socket.h"

int inet_connect(const char *host,
				 const char *service,
				 int		 type) {
	struct addrinfo *ai_list = NULL;
	struct addrinfo *ai_node = NULL;
	struct addrinfo	 hints	 = {.ai_canonname = NULL,
								.ai_addr	  = NULL,
								.ai_next	  = NULL,
								.ai_family	  = AF_UNSPEC,
								.ai_socktype  = type};
	int				 sockfd	 = -1;

	if (getaddrinfo(host, service, &hints, &ai_list) != 0) {
		errno = ENOSYS;
		return -1;
	}

	for (ai_node = ai_list; ai_node != NULL; ai_node = ai_node->ai_next) {
		/* ON ERROR */
		if ((sockfd = socket(ai_node->ai_family,
							 ai_node->ai_socktype,
							 ai_node->ai_protocol)) == -1)
			continue;


		/* ON SUCCESS */
		if (connect(sockfd, ai_node->ai_addr, ai_node->ai_addrlen) != -1)
			break;

		/* CLOSE SOCKET ON FAILED CONNECTION */
		close(sockfd);
	}

	freeaddrinfo(ai_list);
	return (ai_node == NULL) ? -1 : sockfd;
}

int inet_bind(const char *host,
			  const char *service,
			  int		  type) {
	struct addrinfo *ai_list = NULL;
	struct addrinfo *ai_node = NULL;
	struct addrinfo	 hints	 = {.ai_canonname = NULL,
								.ai_addr	  = NULL,
								.ai_next	  = NULL,
								.ai_family	  = AF_UNSPEC,
								.ai_socktype  = type};
	int				 sockfd	 = -1;

	if (getaddrinfo(host, service, &hints, &ai_list) != 0) {
		errno = ENOSYS;
		return -1;
	}

	for (ai_node = ai_list; ai_node != NULL; ai_node = ai_node->ai_next) {
		/* ON ERROR */
		if ((sockfd = socket(ai_node->ai_family,
							 ai_node->ai_socktype,
							 ai_node->ai_protocol)) == -1)
			continue;

		/* ON SUCCESS */
		if (bind(sockfd, ai_node->ai_addr, ai_node->ai_addrlen) != -1)
			break;

		/* CLOSE SOCKET ON FAILED CONNECTION */
		close(sockfd);
	}

	freeaddrinfo(ai_list);
	return (ai_node == NULL) ? -1 : sockfd;
}
