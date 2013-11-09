#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

int daemon_init()
{
	pid_t pid;
	if ( (pid = fork()) < 0) 
		return (-1);
	else if (pid != 0)
		exit(0);
	
	setsid();
	chdir("/");
	umask(0);

	return 0;
}

int main()
{
	daemon_init();
	sleep(10);
	return 0;
}
