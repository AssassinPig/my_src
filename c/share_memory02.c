#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#include <sys/mman.h>

struct shared_content
{
	sem_t mutex;
	int count;
};

int main()
{
	struct shared_content sc;
	sc.count = 0;

	int fd = open("/tmp/shared_memory02", O_RDWR|O_CREAT, S_IRWXU);
	write(fd, &sc, sizeof(struct shared_content)); 
	struct shared_content* ptr = mmap(NULL, sizeof(struct shared_content), PROT_EXEC|PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0); 
	if(!ptr) 
		perror("mmap memory failed");

	close(fd);
	
	sem_t* pmutex = &ptr->mutex;
	int* pcount = ptr->count;
	if(!sem_init(pmutex, 1, 1) == 0) 
		perror("sem_init failed");
		
	pid_t pid;
	if( (pid = fork()) < 0) {
		perror("fork failed");
	} else if(pid == 0) {
		for(int i=0; i<10; ++i) {
			sem_wait(pmutex);
			printf("child process access count %d\n", (*pcount)++);	
			sem_post(pmutex);
		} 
		exit(0);
	}

	for(int i=0; i<10; ++i) {
		sem_wait(pmutex);
		printf("parent process access count %d\n", (*pcount)++);	
		sem_post(pmutex);
	} 
	
	return 0;
}
