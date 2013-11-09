#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include<sys/stat.h>
#include<fcntl.h>

int main( int argc, char *argv[] )
{
	if( argc != 3 )
	{
		for(int i=0; i<argc; ++i)
		{
			printf( "argc[%d]: %s\n", i, argv[i]);
		}
		printf( "Usage: <hostname> <url>\n" );
		return 1;
	}

	//printf("host:%s, url:%s\n", argv[1], argv[2]);

	struct sockaddr_in sin;
	memset( (void *)&sin, 0, sizeof( struct sockaddr_in) );
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80);
	//sin.sin_addr.s_addr = htonl(atoi(argv[1]));
	sin.sin_addr.s_addr = inet_addr(argv[1]);

	int sock = socket( AF_INET, SOCK_STREAM, 0 );
	if( sock < 0 )
	{
		perror( "Socket creation failed\n");
		return -1;
	}
	
	int ret = connect(sock, (struct sockaddr *)&sin, sizeof(struct sockaddr_in));
	//printf("connect...\n");
	if(ret)
	{
		perror("connect failed");			
	}
	else
	{
		char buff[1024];
		memset(buff, 0, 1024);	
		sprintf(buff, "GET http://www.csdn.net/ HTTP/1.0\r\n"\
				"Host: www.csdn.net \r\n"\
				"Accept: */*\r\n"\	
				"Connection: close\r\n\r\n", argv[2]  	
				);
		
		//printf("buff:%s\n", buff);
		int n = send(sock, buff, 1024, 0); 
		if(n<=0)
		{
			perror("send failed");			
		}
		else
		{
			do{
				memset(buff, 0, 1024);	
				n = recv(sock, buff, 1024, 0);
				//printf("recv %d :%s", n, buff);
				printf("%s",buff);
			}while(n==1024 || n!=0);
			//printf("recv all\n");
		}
	}
	close(sock);

	return 0;
}
