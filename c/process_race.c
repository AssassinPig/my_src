#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

static void charatatime(char*);
static int pfd1[2], pfd2[2];

void TELL_WAIT(void)
{
	if(pipe(pfd1) < 0 || pipe(pfd2) < 0) 
		perror("pipe error");
}

void TELL_PARENT(pid_t pid)
{
	if(write(pfd2[1] , "c", 1) != 1)
		perror("write error");
}


void WAIT_PARENT(void)
{
	char c;
	if (read(pfd1[0], &c, 1) != 1)
		perror("read error");
	if(c != 'p')
		perror("WAIT_PARENT: incorrect data");	
}

void TELL_CHILD(pid_t pid)
{
	if(write(pfd1[1], "p", 1) != 1)
		perror("write error");
}

void WAIT_CHILD(void)
{
	char c;
	if(read(pfd2[0], &c, 1) != 1)
		perror("read error");
	if(c != 'c') 
		perror("WAIT_CHILD: incorrect data");
}

int main ()
{
	pid_t pid;
	TELL_WAIT();

	if( (pid = fork()) < 0) {
		perror("fork error");
	}
	else if(pid == 0) {
		WAIT_PARENT();	
		charatatime("output from child\n");
	} else {
		charatatime("output from parent\n");
		TELL_CHILD(pid);
	}

	return 0;
}

static void charatatime(char* str)
{
	char *ptr;
	int c;
	setbuf(stdout, NULL);
	for (ptr = str; c = *ptr++; )
		putc(c, stdout);
}
