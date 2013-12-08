#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <netinet/in.h>                                                                 
#include <fcntl.h>                                                                      
#include <assert.h>                                                                     
#include <errno.h>                                                                      
#include <signal.h>                                                                     
#include <sys/socket.h>                                                                 
#include <sys/times.h>

#include <sys/ioctl.h>
#include <stropts.h>

#include <pthread.h>

struct child_process_info {
	pid_t child_pid;	
	int fd[2];
	int notifyfd[2];
	int status; //0 - avaliable 1-busy
};

typedef struct child_process_info child_process_info_t;
child_process_info_t* child_process_set;
int nchildren;

#define CONTROLLEN sizeof (struct cmsghdr) + sizeof (int)

void* wait_child_notify(void* args)
{
	int nthreadno = (int)args;
	while(1) {
		char buf[4];
		int nread=0;
		if( (nread = read(child_process_set[nthreadno].notifyfd[0], &buf, 1)) <=0) {
			perror("recv child ready notify failed");
		}
		printf("recv child%d ready notify\n", nthreadno);
		child_process_set[nthreadno].status=0;
	}	
	
	return NULL;
}


void child_process(int i, int readfd, int writefd)
{
	for(;;) {
		int newconnfd = -1;
		char tmpbuf[CONTROLLEN];
		struct cmsghdr *cmptr = (struct cmsghdr *) tmpbuf;
		struct iovec iov[1];
		struct msghdr msg;
		char buf[1];
		iov[0].iov_base = buf;
		iov[0].iov_len = sizeof (buf);
		msg.msg_iov = iov;
		msg.msg_iovlen = 1;
		msg.msg_name = NULL;
		msg.msg_namelen = 0;
		msg.msg_control = cmptr;
		msg.msg_controllen = CONTROLLEN;
		if (recvmsg(readfd, &msg, 0) < 0) {
			perror("recvmsg failed");
		}

		newconnfd = *(int *) CMSG_DATA (cmptr);
		char recvbuf[1024];
		memset(recvbuf, 0, 1024);
		int nread;
		while( (nread = recv(newconnfd, recvbuf, 1024, 0)) <= 0) {
			if(errno == EINTR || errno == EAGAIN) {
				continue;
			} 	
			
			if(nread == 0) 
				perror("recv failed");

			printf("error = %s\n", strerror(errno));
		}  
		//printf("child %d recv %s\n", i, recvbuf);

		sprintf(recvbuf, "hello world");
		int nsend = send(newconnfd, recvbuf, strlen(recvbuf), 0);

		char sendbuf[4];
		sendbuf[0] = '\0';	
		nsend = write(writefd, sendbuf, 1);
		if(nsend <= 0)
			 perror("notify parent failed");
		//printf("child%s send notify to parent\n", sendbuf);
		close(newconnfd);
	}
}

void child_make(int i)
{
	pid_t pid;
	if(socketpair(AF_LOCAL, SOCK_STREAM,0, child_process_set[i].fd) == -1)
	{
		perror("socketpair create failed");
	}
	
	if(pipe(child_process_set[i].notifyfd) < 0) {
		perror("create pipe failed");
	} 

	if((pid = fork()) > 0) {
		child_process_set[i].child_pid = pid;	
		//printf("create child%d fd[0]=%d, fd[1]=%d\n", i, child_process_set[i].fd[0], child_process_set[i].fd[1]);
		return;
	}	
	
	child_process(i, child_process_set[i].fd[0], child_process_set[i].notifyfd[1]);
}


int main(int nargc, char* args[])
{
	setvbuf(stdout, NULL, _IONBF, 0);

	nchildren = atoi(args[nargc-1]); 
	if(nchildren <= 0) {
		nchildren = 10;		
	}
	child_process_set = (child_process_info_t*)malloc(sizeof(child_process_info_t)*nchildren);
	if(!child_process_set) {
		perror("malloc child process set failed");
		return 0;
	}
	memset(child_process_set, 0, sizeof(child_process_info_t)*nchildren);
	printf("create %d children\n", nchildren);


	struct sockaddr_in sin;
        sin.sin_family = AF_INET;
	char* BIND_IP = "192.168.0.120";	
        sin.sin_addr.s_addr = inet_addr(BIND_IP);
	int LISTEN_PORT = atoi(args[nargc-2]);
        sin.sin_port = htons(LISTEN_PORT);

        int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd <= 0) {
		perror("socket create failed");
		return -1;
	}

	int f=1;
	if (- 1== setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char*)&f, sizeof(f))) {
		perror("setsockopt");                                                        
		return -1;                                                                   
	}                                                                                

	if (-1 == bind(listenfd, (struct sockaddr*)&sin, sizeof(sin))) {                        
		perror("bind");                                                              
		return -1;                                                                   
	}                                                                                
	
	int LISTENER_MAX = 10;
	if (-1 == listen(listenfd, LISTENER_MAX)) {                                    
		perror("listen");                                                            
		return -1;                                                                   
	}                                  

	
	pthread_t pid; 
	for(int n=0; n<nchildren; ++n) {
		if(pthread_create(&pid, NULL, wait_child_notify, (void*)n) < 0) 
			perror("create thread failed");
	} 

        fd_set read_set;
        fd_set write_set;
	fd_set master_set;
        struct timeval tv;
        tv.tv_sec = 30;
        tv.tv_usec = 0;

	//select loop
	int newconnfd=-1; 
        FD_ZERO(&read_set);
        FD_ZERO(&write_set);
	FD_ZERO(&master_set);
	FD_SET(listenfd, &master_set);
	int navailable=nchildren;
	int maxfd = listenfd;
	for(int i=0; i<nchildren; ++i) {
		child_make(i);
		maxfd = maxfd > child_process_set[i].fd[0] ? maxfd : child_process_set[i].fd[0];	
		FD_SET(child_process_set[i].fd[0], &master_set);
	}	
	
	int nfdevents;
	while(1) {
		read_set = master_set;
		//if(navailable<=0) 
        	//	FD_CLR(listenfd, &read_set);

		if( (nfdevents = select(maxfd+1, &read_set, &write_set, NULL, &tv)) < 0) {
			break;
		}
	
		if(FD_ISSET(listenfd, &read_set)) {
			if( (newconnfd = accept(listenfd, NULL, 0))  < 0)  {
				perror("accept failed");
			}

			int i=0;
			for(i=0; i<nchildren; ++i) {
				if(child_process_set[i].status == 0) {
					break;
				}
			}		

			if(i==nchildren) {
				perror("no enough child process");
			}

			char tmpbuf[CONTROLLEN];
			struct cmsghdr *cmptr = (struct cmsghdr *) tmpbuf;
			struct iovec iov[1];
			struct msghdr msg;
			char buf[1];
			iov[0].iov_base = buf;
			iov[0].iov_len = 1;
			msg.msg_iov = iov;
			msg.msg_iovlen = 1;
			msg.msg_name = NULL;
			msg.msg_namelen = 0;
			msg.msg_control = cmptr;
			msg.msg_controllen = CONTROLLEN;
			cmptr->cmsg_level = SOL_SOCKET;
			cmptr->cmsg_type = SCM_RIGHTS;
			cmptr->cmsg_len = CONTROLLEN;
			*(int *)CMSG_DATA (cmptr) = newconnfd;

			if (sendmsg(child_process_set[i].fd[1], &msg, 0) != 1) {
				perror("sendmsg failed");
			}

			navailable--;
			child_process_set[i].status = 1;
			close(newconnfd);
			if(--nfdevents == 0) {
				continue;
			}
		}
	
	}

	//wait all child process at last
	for(int i=0; i<nchildren; ++i) {
		int status;
		wait(&status);
	}	
	
	pthread_join(pid, NULL);

	return 0;
}
