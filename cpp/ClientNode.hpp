#ifndef _CLIENT_NODE_H__ 
#define _CLIENT_NODE_H__

#include "Common.hpp"

class ClientNode
{
public:
	ClientNode(const char* szHost, const char* szURL)
	{
		if(!szURL || !szHost)
		{
			perror("Initial ClientNode failed! invalidate url\n");
		}	
		
		memset(m_szURL, 0, URL_MAX);
		memset(m_szHost, 0, HOST_MAX);

		memset(m_szFileName, 0, URL_MAX);
		strcpy(m_szFileName, szHost);	

		sprintf(m_szURL, "http://%s/%s", szHost, szURL);

		struct hostent *answer;
 	    int i;
 	    char ipstr[16];
 	    answer = gethostbyname(szHost);
 	    if (answer == NULL) {
 	        herror("gethostbyname"); //由gethostbyname自带的错误处理函数
 	        exit(1);
 	    }
 	
 	    for (i = 0; (answer->h_addr_list)[i] != NULL; i++) {
 	        inet_ntop(AF_INET, (answer->h_addr_list)[i], ipstr, 16);
			strcpy(m_szHost, ipstr);
 	        printf("%s\n", ipstr);
 	        printf("officail name : %s\n", answer->h_name);
 	    }
	}

	virtual ~ClientNode(){
	}

	virtual bool InitConnect()
	{
		struct sockaddr_in sin;
		memset( (void *)&sin, 0, sizeof( struct sockaddr_in) );
		sin.sin_family = AF_INET;
		sin.sin_port = htons(80);
		sin.sin_addr.s_addr = inet_addr(m_szHost);
		
		printf("m_szHost:%s\n", m_szHost);
		m_socket = socket( AF_INET, SOCK_STREAM, 0 );
		if( m_socket < 0 )
		{
			perror( "Socket creation failed\n");
			return false;
		}
		
		int ret = connect(m_socket, (struct sockaddr *)&sin, sizeof(struct sockaddr_in));
		if(ret)
		{
			perror("connect failed\n");			
			return false;
		}

		m_pFile = fopen(m_szFileName, "wt");
		if(!m_pFile)
		{
			perror("open file failed\n");			
			return false;	
		}

		return true;	
	}
	
	virtual void Run()
	{
		char buff[BUF_MAX];
		memset(buff, 0, BUF_MAX);	

		sprintf(buff, "GET %s HTTP/1.0\r\n"\
				"Host: %s \r\n"\
				"Accept: */*\r\n"\
				"Connection: close\r\n\r\n", m_szURL, m_szHost  	
				);
		
		//printf("buff:%s\n", buff);
		int n = send(m_socket, buff, BUF_MAX, 0); 
		if(n<=0)
		{
			perror("send failed");			
		}
		else
		{
			do{
				memset(buff, 0, BUF_MAX);	
				n = recv(m_socket, buff, BUF_MAX, 0);
				//printf("recv %d :%s", n, buff);

				if(m_pFile && n)
				{
					int nwrite = fwrite(buff, sizeof(char), n, m_pFile);	
					if(!nwrite)
					{
						perror("write failed");
						break;
					}
				}

			}while(n==BUF_MAX || n!=0);
			printf("recv all\n");
		}

		close(m_socket);
		fclose(m_pFile);
	}

private:
	char m_szURL[URL_MAX];
	char m_szHost[HOST_MAX];
	int m_socket;
	FILE* m_pFile;
	char m_szFileName[URL_MAX];
};



#endif //_CLIENT_NODE_H__ 
