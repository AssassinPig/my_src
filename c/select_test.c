#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <netinet/in.h>                                                                 
#include <fcntl.h>                                                                      
#include <assert.h>                                                                     
#include <stdio.h>                                                                      
#include <errno.h>                                                                      
                                                                                        
#include <signal.h>                                                                     
#include <unistd.h>                                                                     
                                                                                        
#include <sys/socket.h>                                                                 
#include <sys/types.h> 
#include <sys/times.h>

int main(int nargs, char* args[])
{
	setvbuf(stdout, NULL, _IONBF, 0);

	struct sockaddr_in sin;
        sin.sin_family = AF_INET;
	char* BIND_IP = "127.0.0.1";	
        sin.sin_addr.s_addr = inet_addr(BIND_IP);
	//int LISTEN_PORT = 80;
	int LISTEN_PORT = 12348;
        sin.sin_port = htons(LISTEN_PORT);
        int listenfd = socket(AF_INET, SOCK_STREAM, 0);

	int f=1;
	if (-1== setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char*)&f, sizeof(f))) {
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
	
        fd_set read_set;
        fd_set write_set;
        struct timeval tv;
        tv.tv_sec = 30;
        tv.tv_usec = 0;

	int newconnfd = -1; 
	FD_ZERO(&read_set);
	FD_ZERO(&write_set);

	//select loop
	while(1) {
		if(!FD_ISSET(listenfd, &read_set)) {
			FD_SET(listenfd, &read_set);
		}

		int nfd=0;
		int maxfd = listenfd > newconnfd ? listenfd + 1 : newconnfd + 1;
		if( (nfd=select(maxfd, &read_set, &write_set, NULL, &tv)) < 0) {
			perror("select failed");
			break;
		}
		
		if(nfd)
			printf("select with fd=%d\n", nfd);		

		while(nfd--) {
			if(newconnfd == -1) {
				perror("accept will run");
				if(FD_ISSET(listenfd, &read_set)) {
					struct sockaddr_in newaddr;
					memset(&newaddr, 0, sizeof(struct sockaddr_in));
					if( (newconnfd = accept(listenfd, NULL, 0))  < 0)  {
						perror("accept failed");
						continue;
					}

					printf("newconnfd = %d\n", newconnfd);
					FD_SET(newconnfd, &read_set);
				}
			} 

			if(FD_ISSET(newconnfd, &read_set)) {
				perror("read");
				char buf[1024];
				memset(buf, 0, 1024);	
				recv(newconnfd, buf, 1024, 0); 			
				printf("read %s\n", buf);	
				FD_SET(newconnfd, &write_set);	
				FD_CLR(newconnfd, &read_set);
				//close(newconnfd);
				continue;
			}

			if(FD_ISSET(newconnfd, &write_set)) {
				perror("write");
				char buf[1024];
				//sprintf(buf, "hello world");
				//sprintf(buf, "<html><head>hi</head><body>hello world</body></html>");
				FILE* pFile = fopen("index.html", "r");
				if(pFile){
					fread(buf, 1, 1024, pFile);
					fclose(pFile);
				}
				else {
					perror("open file failed");
				}

				write(newconnfd, buf, strlen(buf)+1);
				FD_CLR(newconnfd, &write_set);
				close(newconnfd);
				newconnfd = -1;
			}
		}
	}

	return 0;
}
