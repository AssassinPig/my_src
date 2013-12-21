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

int main( int argc, char *argv[] )
{
	if( argc != 2 )
	{
		return 1;
	}
	
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(struct sockaddr_in)); 
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80);
	//sin.sin_addr.s_addr = inet_addr([]);
	sin.sin_addr.s_addr = "192.168.4.48";
	
	int sock = socket(AF_INET, SOCK_RAW, 0);
	if(sock < 0)
	{
		perror("create socket failed");
		return 0;
	}

	int ret = connect(sock, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));	
	if(ret)
	{
		perror("connect failed");
	}
	
	char buff[1024];
	int n = 0;	
	do{
		memset(buff, 0, 1024);	
		n = recv(sock, buff, 1024, 0);
		
		for(int i=0; i<n; ++i)
		{
			printf("%d\t", buff[n]);	
		}
		printf("\n");	
	}while(n==1024||n!=0);
	
	close(sock);	

	return 0;	
}
