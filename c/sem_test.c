#include <stdio.h>
#include <linux/types.h>
#include <linux/ipc.h>
#include <linux/sem.h>
#include <unistd.h>

int init_sem(int sem_id, int init_value)
{
	union semun sem_union; 	
	sem_union.val = init_value;
	if(semctl(sem_id, 0, SETVAL, sem_union) == -1) {
		perror("init_sem failed");
		return -1;
	} 

	return 0;	
}

int del_sem(int sem_id)
{
	if(semctl(sem_id, 0, IPC_RMID) == -1) {
		perror("del_sem failed");
		return -1;
	} 

	return 0;	
}

int sem_p(int sem_id) 
{
	struct sembuf sem_buf;
	sem_buf.sem_num = 0;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = SEM_UNDO;		
	
	if(semop(sem_id, &sem_buf, 1) == -1) {
		perror("sem_p failed");
		return -1;
	}

	return 0; 
}

int sem_v(int sem_id)
{
	struct sembuf sem_buf;
	sem_buf.sem_num = 0;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = SEM_UNDO;		
	
	if(semop(sem_id, &sem_buf, 1) == -1) {
		perror("sem_v failed");
		return -1;
	}

	return 0; 
}

int main()
{
	pid_t result;
	int sem_id;

	sem_id = semget(ftok(".", 'a'), 1, 0666|IPC_CREAT);
	init_sem(sem_id, 0);

	if( (result = fork())  == -1) {
		perror("fork failed");
		return -1;
	} else if( result == 0 ) {
		printf("child process run\n");
		sleep(2);
		printf("child process continue\n");
		sem_v(sem_id);
   	} else {
		sem_p(sem_id);
		printf("prarent process run\n");
		sem_v(sem_id);
	}
	
	return 0;
}


