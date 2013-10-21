#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/epoll.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define MAX_EVENTS 10
#define PORT 9999 

int exit_epoll= 0;
void shutdown_epoll(int signal)
{
	exit_epoll = 1;	
}

void setnonblocking(int sockfd)
{
	int opts;
	opts = fcntl(sockfd, F_GETFL);
	if(opts < 0) {
		perror("fcntl(F_GETFL)\n");
		exit(1);	
	}

	opts = (opts | O_NONBLOCK);
	if(fcntl(sockfd, F_SETFL, opts) < 0) {
		perror("fcntl(F_SETFL)\n");
		exit(1);
	}
}

int main()
{
	struct epoll_event ev,
	events[MAX_EVENTS];	
	int addrlen, listenfd, conn_sock, nfds, epfd, fd, i, nread, n;
	struct sockaddr_in local, remote;
	char buf[BUFSIZ];

	//set signal
	//sigaction act;
//	act.sa_handler = SIG_IGN;
//	act.sa_flags &= ~SA_RESETHAND;
//	sigaction(SIGPIPE, act, NULL);
	
	signal(SIGINT, shutdown_epoll);
	signal(SIGKILL,shutdown_epoll);
	signal(SIGQUIT,shutdown_epoll);
	signal(SIGTERM,shutdown_epoll);

	exit_epoll = 0;

	if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("sockfd\n");
		exit(1);
	}

	setnonblocking(listenfd);
	memset(&local, 0, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(PORT);
	if( bind(listenfd, (struct sockaddr*)&local, sizeof(local)) < 0) {
		perror("bind\n");
		exit(1);
	} 

	listen(listenfd, 20);

	epfd = epoll_create(MAX_EVENTS);
	if(epfd == -1) {
		perror("epoll_create");
		exit(EXIT_FAILURE);	
	}

	ev.events = EPOLLIN;
	ev.data.fd = listenfd;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) {
		perror("epoll_ctl: listen_sock");
		exit(EXIT_FAILURE);
	}

	for (;;) {
		nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
		if (nfds == -1) {
			perror("epoll_pwait");
			exit(EXIT_FAILURE);
		}

		for (i = 0; i < nfds; ++i) {
			fd = events[i].data.fd;
			if (fd == listenfd) {
				while ((conn_sock = accept(listenfd,(struct sockaddr *) &remote, 
								(size_t *)&addrlen)) > 0) {
					setnonblocking(conn_sock);
					ev.events = EPOLLIN | EPOLLET;
					ev.data.fd = conn_sock;
					if (epoll_ctl(epfd, EPOLL_CTL_ADD, conn_sock,
								&ev) == -1) {
						perror("epoll_ctl: add");
						exit(EXIT_FAILURE);
					}
				}
				if (conn_sock == -1) {
					if (errno != EAGAIN && errno != ECONNABORTED 
							&& errno != EPROTO && errno != EINTR) 
						perror("accept");
				}
				continue;
			}  
			if (events[i].events & EPOLLIN) {
				n = 0;
				while ((nread = read(fd, buf + n, BUFSIZ-1)) > 0) {
					n += nread;
				}
				if (nread == -1 && errno != EAGAIN) {
					perror("read error");
				}
				ev.data.fd = fd;
				ev.events = events[i].events | EPOLLOUT;
				if (epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1) {
					perror("epoll_ctl: mod");
				}
			}
			if (events[i].events & EPOLLOUT) {
				sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nHello World", 11);
				int nwrite, data_size = strlen(buf);
				n = data_size;
				while (n > 0) {
					nwrite = write(fd, buf + data_size - n, n);
					if (nwrite < n) {
						if (nwrite == -1 && errno != EAGAIN) {
							perror("write error");
						}
						break;
					}
					n -= nwrite;
				}
				close(fd);
			}
		}

		if (exit_epoll) {
			break;
		}
	}

	close(epfd);
	return 0;
}
