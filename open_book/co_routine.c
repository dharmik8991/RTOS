#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <pthread.h>
#include <semaphore.h>

pthread_cond_t cond[4]={PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER};
pthread_mutex_t lock[4]={PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER};
static int state[4]={0,0,0,0};
pthread_cond_t rcond= PTHREAD_COND_INITIALIZER;
struct timeval start, stop;
void * player(void* n){
	int i=(int)n;
	while(1){
		pthread_mutex_lock(&lock[i]); 
		pthread_cond_wait(&cond[i], &lock[i]);
		int dice;
		if(state[i]<100){
			dice = rand() % 6 + 1;
			if(state[i]+dice<=100)
				state[i] +=  dice;
			printf("Player %d %d\n",(i+1),state[i]);
		}

		if(state[i]==100){
			gettimeofday(&stop, NULL);
			printf("Player %d has won\n",i+1);
			printf("Time taken to win (micro seconds) %lu\n", (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_usec - start.tv_usec));
			exit(0);
		}
        pthread_cond_signal(&rcond);  
        pthread_mutex_unlock(&lock[i]);

	}
	return NULL;
}
int main(){
	pthread_t  tid[4]; 
	int i;
    srand(time(0));//for getting random values
    for(i=0;i<4;i++)
   {	
	pthread_create(&tid[i], NULL, player, (void *)i); 
    }
    gettimeofday(&start, NULL);
     
    while(1)
    {
	for(i=0;i<4;i++)
	{
	 pthread_cond_signal(&cond[i]);
	 pthread_cond_wait(&rcond,&lock[i]);
	}
    }
}
