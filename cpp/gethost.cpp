#include "Common.hpp"

int main( int argc, char *argv[] )
{
	if( argc != 2 )
	{
		for(int i=0; i<argc; ++i)
		{
			printf( "argc[%d]: %s\n", i, argv[i]);
		}
		printf( "Usage: <hostname>/<url>\n" );
		return 1;
	}

	struct hostent *answer;
 	int i;
 	char ipstr[16];
	
	char* szStart = strstr(argv[1], "http://");

	if(szStart)
	{
		char buf[1024];	
		memset(buf, 0, 1024);
		memcpy(buf, szStart+strlen("http://"), strlen(szStart)-strlen("http://"));	

		szStart = strstr(buf, "/");
		
		if(szStart)
		{
			*szStart = '\0';
		}

		printf("\nbuf:%s\n", buf);
		answer = gethostbyname(buf);
	}
	else
	{
		answer = gethostbyname(argv[1]);
	}

 	if (answer == NULL) {
 	    herror("gethostbyname"); //由gethostbyname自带的错误处理函数
 	    exit(1);
 	}
 	
 	for (i = 0; (answer->h_addr_list)[i] != NULL; i++) {
 	    inet_ntop(AF_INET, (answer->h_addr_list)[i], ipstr, 16);
 	    printf("ip:%s\n", ipstr);
 	    printf("officail name : %s\n", answer->h_name);
 	}

	return 0;
}
