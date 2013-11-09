#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h> 
#include <sys/types.h>

pid_t pids[10];
int main(int nargc, char* argv[])
{
	memset(pids, 0, 10*sizeof(pid_t));
	for(int i = 0; i<10; i++) {
		pid_t id = fork();	
		if(id){
			pids[i] = id;
			printf("fork succ time=%d\n", i);	
		} else if(id == 0) {
			int n = 0; 
			while(n++<10) {
				sleep(10);	
				printf("process %d run %d times\n", i, n);
			}

			printf("process %d stop\n", i);
			return 0;
		} else {
			printf("fork failed\n");
		}
	}

	for(int i=0; i < 9; ) {
		int status;
		pid_t id = wait(&status);
		++i;
		printf("wait %d\n", i);
	}	

	return 0;
}
