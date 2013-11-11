#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

//int sig_handler(int n)
//{
//	printf("recv sigaction\n");	
//}

int main(int nargc, char* argv[])
{
	struct sigaction act;
	act.sa_handler = SIG_IGN;
	act.sa_flags &= (~SA_RESETHAND);
	sigaction(SIGPIPE, &act, NULL);

	return 0;
}
