#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUF_SIZE 10000

//global
int array[BUF_SIZE];

int main()
{
	printf("global addr %p\n", array);
	//stack
	int stack[BUF_SIZE];
	printf("stack addr %p\n", stack);
	
	//heap	
	void *ptr = malloc(BUF_SIZE);
	printf("head addr %p\n", ptr);
	
	key_t key = ftok(".", 'a');
	int shm_id;	
	//shared memory	
	if( (shm_id = shmget(IPC_PRIVATE, BUF_SIZE, IPC_CREAT|0666)) == -1) {
		perror("create shared memory failed");
		return -1;
	}
	
	void *shm_ptr = NULL;
	shm_ptr = shmat(shm_id, 0, SHM_R);	
	if(shm_ptr == (void*)-1) {
		perror("mat shared memory failed");
	}
	
	printf("shared memory %p\n", shm_ptr);

	if( shmdt(shm_ptr) == -1) {
		perror("dt shm failed");
	}

	if( shmctl(shm_id, IPC_RMID, NULL) == -1) {
		perror("rm shm failed");
	}
	
	return 0;
}

