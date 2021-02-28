#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

const int maximum=10;
pthread_mutex_t m1=PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore1;
int stack[1000],data=-1;

void* efunction1(void* pv)
{
	int i;
	
	printf("A  welcome\n");
	pthread_mutex_lock(&m1);
	push();
	pthread_mutex_unlock(&m1);

	sem_post(&semaphore1);
}
void* efunction2(void* pv)
{
	int i;
	printf("B welcome, waiting for semaphore\n");
	sem_wait(&semaphore1);			
	pthread_mutex_lock(&m1);
	pop();

	pthread_mutex_unlock(&m1);

}
int main()
{
	printf("Welcome\n");
	pthread_t pthread1,pthread2;	
	sem_init(&semaphore1,0,1);
	pthread_create(&pthread1,NULL,efunction1,NULL);
	pthread_create(&pthread2,NULL,efunction2,NULL);
	pthread_join(pthread1,NULL);
	pthread_join(pthread2,NULL);
	sem_destroy(&semaphore1);
	pthread_mutex_destroy(&m1);
	printf("Thank you\n");
	return 0;
}

void pop()
{
	printf("The popped elements is %d\n",stack[data]);
        data--;
}

void push()
{
	data++;
        printf("pushed element is 50\n");
        stack[data]=50;
}



