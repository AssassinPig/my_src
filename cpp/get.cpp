#include "Common.hpp"
#include "ClientNode.hpp"

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

	ClientNode client(argv[1], argv[2]);
	if(client.InitConnect())
		client.Run();
}
