#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <pthread.h>
#include <semaphore.h>

pthread_cond_t cond[4]={PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER};
pthread_mutex_t lock[4]={PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER};
int i;
static int move[4]={0,0,0,0},state[4];
pthread_cond_t rcond= PTHREAD_COND_INITIALIZER;
struct timeval start, stop;
void * player(void* n){
	int i=(int)n;
	while(1){
		pthread_mutex_lock(&lock[i]); 
		pthread_cond_wait(&cond[i], &lock[i]);
		int dice;
		if(move[i]<100){
			dice = rand() % 6 + 1;
			if(move[i]+dice<=100)
				move[i] +=  dice;
			printf("player %d %d\n",(i+1),move[i]);
		}

		if(move[i]==100){
			gettimeofday(&stop, NULL);
			printf("player%d wins\n",i+1);
			printf("Time taken to win (micro seconds) %lu\n", (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_usec - start.tv_usec));
			exit(0);
		}
        pthread_cond_signal(&rcond);  
        pthread_mutex_unlock(&lock[i]);

	}
	return NULL;
}
/*
void * player2(void *n){
	while(1){
		static int move = 0;
		static int state = 0;

		pthread_mutex_lock(&lock2); 
		pthread_cond_wait(&cond2, &lock2);
		int dice;
		if(move<100){
			dice = rand() % 6 + 1;
			if(move+dice<=100)
				move = move + dice;
			printf("player 2 %d\n",move);
		}

		if(move==100){
			gettimeofday(&stop, NULL);
			printf("player2 wins\n");
			printf("time taken to win (micro seconds) %lu\n", (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_usec - start.tv_usec));
			exit(0);
		}
        pthread_cond_signal(&cond5);  
        pthread_mutex_unlock(&lock2);

	}
	return NULL;
}

void * player3(void *n){
	while(1){
		static int move = 0;
		static int state = 0;

		pthread_mutex_lock(&lock3); 
		pthread_cond_wait(&cond3, &lock3);
		int dice;
		if(move<100){
			dice = rand() % 6 + 1;
			if(move+dice<=100)
				move = move + dice;
			printf("player 3 %d\n",move);
		}

		if(move==100){
			gettimeofday(&stop, NULL);
			printf("player3 wins\n");
			printf("time taken to win (micro seconds) %lu\n", (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_usec - start.tv_usec));
			exit(0);
		}
        pthread_cond_signal(&cond5);  
        pthread_mutex_unlock(&lock3);

	}
	return NULL;
}

void * player4(void *n){
	while(1){
		static int move = 0;
		static int state = 0;

		pthread_mutex_lock(&lock4); 
		pthread_cond_wait(&cond4, &lock4);
		int dice;
		if(move<100){
			dice = rand() % 6 + 1;
			if(move+dice<=100)
				move = move + dice;
			printf("player 4 %d\n",move);
		}

		if(move==100){
			gettimeofday(&stop, NULL);
			printf("player4 wins\n");
			printf("time taken to win (micro seconds) %lu\n", (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_usec - start.tv_usec));
			exit(0);
		}
        pthread_cond_signal(&cond5); 
        pthread_mutex_unlock(&lock4);

	}
	return NULL;
}
*/
int main(){
	pthread_t  tid[4]; 
    int n1 = 1, n2 = 2, n3 = 3, n4 = 4,i;
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
	/*
    	//pthread_mutex_unlock(&lock1);
    	pthread_cond_signal(&cond1);
    	pthread_mutex_unlock(&lock1);
    	pthread_mutex_lock(&lock1);
    	pthread_cond_wait(&cond5, &lock1);
    	//pthread_mutex_lock(&lock1);

    	//pthread_mutex_unlock(&lock2);
    	pthread_cond_signal(&cond2);
    	pthread_mutex_unlock(&lock2);
    	pthread_mutex_lock(&lock2);
    	pthread_cond_wait(&cond5, &lock2);
    	//pthread_mutex_lock(&lock2);

    	//pthread_mutex_unlock(&lock3);
    	pthread_cond_signal(&cond3);
    	pthread_mutex_unlock(&lock3);
    	pthread_mutex_lock(&lock3);
    	pthread_cond_wait(&cond5, &lock3);
    	//pthread_mutex_lock(&lock3);

    	//pthread_mutex_unlock(&lock4);
    	pthread_cond_signal(&cond4);
    	pthread_mutex_unlock(&lock4);
    	pthread_mutex_lock(&lock4);
    	pthread_cond_wait(&cond5, &lock4);
    	//pthread_mutex_lock(&lock4);*/
    }
}
