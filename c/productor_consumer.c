#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t productor_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t consumer_cond = PTHREAD_COND_INITIALIZER;
	
int nput=0;

void* productor(void* args)
{
	while(1) {
		printf("productor process\n");
		pthread_mutex_lock(&mutex);

		while(nput){
			pthread_cond_wait(&productor_cond, &mutex);
			printf("nput = 0 no signal\n");
		}  	

		if(nput==0) 
		{
			nput = 1;		
			pthread_cond_signal(&consumer_cond);
			pthread_mutex_unlock(&mutex);
			printf("nput = 1 send signal\n");
			continue;		
		} 
	}
	return NULL;
}

void* consumer(void* args)
{
	while(1) {
		printf("consumer process\n");
		pthread_mutex_lock(&mutex);

		while(nput==0) {
			pthread_cond_wait(&consumer_cond, &mutex);
			printf("nput = 0 wait succ\n");
		}

		if(nput) {
			nput=0;
			pthread_cond_signal(&productor_cond);
			printf("nput = 0 now\n");
			pthread_mutex_unlock(&mutex);
			continue;
		}

		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main()
{
	pthread_t pid;
	pthread_t cid;
	pthread_create(&pid, NULL, productor, NULL);	
	pthread_create(&cid, NULL, consumer, NULL);	

	pthread_join(pid, NULL);
	pthread_join(cid, NULL);

	return 0;
}
