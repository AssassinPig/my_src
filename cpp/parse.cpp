#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <malloc.h>

using namespace std;

#define BUF_MAX 1024*8

void SaveHrefFile(const char* szHref, const char* szEnd)
{
	//printf("SaveHrefFile\n");
	FILE* pFile = fopen("href", "a+");	
	if(!pFile)
	{
		perror("open failed");
		return;
	}
	
//	const char* c = szHref;	
//	while(c <= szEnd)
//	{	
//		printf("%c", *c);
//		++c;
//	}
//	printf("\n");

	char buf[1024];
	memset(buf, 0, 1024);	

	int nlen = szEnd-szHref;
	memcpy(buf, szHref, nlen);
	buf[nlen]='\n';

//	fwrite(buf, sizeof(char), nlen, pFile);	
//	fflush(pFile);
	
	fputs(buf, pFile);
	
	fclose(pFile);	
}

void ParseContent(const char* szStart, const char* szEnd)
{
	//const char* c = szStart;
//	while(c <= szEnd)
//	{	
//		printf("%c", *c);
//		++c;
//	}
//	printf("\n");
	
	
	const char* szHref = strstr(szStart, "href=\"");
	if(!szHref || szHref > szEnd)
	{
		return;
	}

	szHref += 6;
	const char* szHrefEnd = NULL;
	if(szHref)
	{
		szHrefEnd = strstr(szHref, "\"");	
	}
	else
	{
		return;
	}
	
	if(szHref && szHrefEnd)
	{
		SaveHrefFile(szHref, szHrefEnd);
	//	printf("Href:");	
//		while(szHref != szHrefEnd)
//		{	
//			printf("%c", *szHref);
//			++szHref;	
//		}
	}

//	printf("\n");
}

int main(int nargc, char* argv[])
{
	if(nargc != 2)
	{
		perror("input file invalidate");
		return 1;
	}

	FILE* pFile = fopen(argv[1], "rb");
	if(pFile==NULL)
	{
		perror("open file failed\n");
	}

	int nFileSize = fseek(pFile, 0, SEEK_END);
	nFileSize = ftell(pFile);
	printf("file size = %d\n", nFileSize);
	fseek(pFile, 0, SEEK_SET);

	//int nRest = 0;
	//int nOffset = 0;
	char* szStart = NULL;
	char* szEnd = NULL;
	char* buf = (char*)malloc(nFileSize);
	memset(buf, 0, nFileSize);
	if(!buf)
	{
		perror("malloc failed");
	}

	int n = fread(buf, sizeof(char), nFileSize, pFile);
	if(n <= 0)
	{
		perror("read failed");
		return 0;	
	}
	fclose(pFile);
	//nRest = nFileSize;
	
	char *szIndex = buf;
	do{
		szStart = strstr(szIndex, "<");
		if(szStart)
		{
			szEnd = strstr(szStart, ">");	
			//nOffset = szEnd - szStart + 1;
//			printf("offset:%d ", nOffset);	
//
//			printf("\nszStart:");
//			for(int i=0; i<10; ++i)
//			{
//				printf("%c",*(szStart+i));
//			}
//			printf("\nszEnd:");
//			for(int i=0; i<10; ++i)
//			{
//				printf("%c",*(szEnd+i));
//			}
//			printf("\nContent:");


			ParseContent(szStart, szEnd);

			//memmove(buf, szEnd+1, nFileSize - (szStart-buf+nOffset) + 1);

			szIndex = szEnd;
			szStart = NULL;
			szEnd = NULL;
			//nRest -= nOffset;	
		}
		else
		{
			printf("parse : no match <\n");		
			//printf("rest :%d\n", nRest);
			//printf("szStart:%s\n", szStart);
			break;
		}
	}while(true);


	return 0;
}

