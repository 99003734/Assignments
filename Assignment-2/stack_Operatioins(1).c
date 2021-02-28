#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>


sem_t semaphore1;
sem_t semaphore2;
int stack[1000],data=-1;

void* tentry_fun1(void* pv)	
{
	int j;
	printf("A welcome\n");
	sem_wait(&semaphore2);
	sem_wait(&semaphore1);

	pop();

	sem_post(&semaphore1);
}


void* tentry_fun2(void* pv)	
{
	int j;
	printf("B welcome\n");
	sem_wait(&semaphore1);
	
	push();

	sem_post(&semaphore1);
	sem_post(&semaphore2);
}

int main()
{

	pthread_t pthread_1,pthread_2;
	sem_init(&semaphore1,0,1);
	sem_init(&semaphore2,0,0);

	pthread_create(&pthread_1,NULL,tentry_fun1,NULL);
	pthread_create(&pthread_2,NULL,tentry_fun2,NULL);
	pthread_join(pthread_1,NULL);
	pthread_join(pthread_2,NULL);
	sem_destroy(&semaphore1);
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
