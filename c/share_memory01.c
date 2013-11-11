#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#include <sys/mman.h>

#define SEM_NAME "SEM_COUNT"

int main()
{
	int fd = open("file1", O_RDWR|O_CREAT, S_IRWXU);
	int count=0;
	write(fd, &count, sizeof(int)); 
	void* ptr = mmap(NULL, sizeof(int), PROT_EXEC|PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0); 
	if(!ptr) 
		perror("mmap memory failed");

	close(fd);
	
	sem_t * mutex = sem_open(SEM_NAME, O_CREAT | O_EXCL);
	if(!mutex) 
		perror("sem_open failed");
		
	sem_unlink(SEM_NAME);
	pid_t pid;
	if( (pid = fork()) < 0) {
		perror("fork failed");
	} else if(pid == 0) {
		
		for(int i=0; i<10; ++i) {
			sem_wait(mutex);
			printf("child process access count %d\n", (*((int*)ptr))++);	
			sem_post(mutex);
		} 
		exit(0);
	}

	for(int i=0; i<10; ++i) {
		sem_wait(mutex);
		printf("parent process access count %d\n", (*((int*)ptr))++);	
		sem_post(mutex);
	} 
	
	return 0;
}
