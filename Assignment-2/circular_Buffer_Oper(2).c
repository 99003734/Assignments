#include<pthread.h>
#include<unistd.h>

#include<stdio.h>
#include<stdlib.h>

#include<semaphore.h>


#define buffer_Size 1000

struct buffer_Oper {
        int input;
};

struct buffer_Oper buf[buffer_Size];

sem_t filled, empty;

int data, i;

void *producer(void *input);
void *consumer(void *input);

int main(void)
{
    int seller, product_input, constant_input;
    int j;

    if (sem_init(&empty, 0, buffer_Size)) {
        printf("Error: Semaphore is not Initialized\n");
        return -1;
    }
    if (sem_init(&filled, 0, 0)) {
        printf("Error: Semaphore is not Initialized\n");
        return -1;
    }

    while (1) {
        printf(".................................................\n");
        printf("Select the seller section\n");
        printf("Producer : 1 | Consumer : 2 | Display : 3 | Exit : 0 || ");
        scanf("%d",&seller);
        printf(".........................................................\n");

        switch (seller) {
        case 1:
            sem_getvalue(&empty, &data);
            sem_getvalue(&filled, &data);
            printf("\nProducer\n");
            pthread_t prod_t;
            printf("Enter the input:");
            scanf("%d", &product_input);
            if (pthread_create(&prod_t, NULL, producer, (void *) &product_input)) {
                printf("Error: thread is not created\n");
                return -1;
            }
            break;
        case 2:
            printf("\nConsumer\n");
            sem_getvalue(&empty, &data);
            sem_getvalue(&filled, &data);
            pthread_t con_t;
            if (pthread_create(&con_t, NULL, consumer, (void *) &constant_input)) {
                printf("Error: Thread is not created\n");
                return -1;
            }
            if (i == 0) {
                printf("Buffer operation is empty\n");
                break;
            }
            printf("Consumer input: %d\n", constant_input);
            break;
        case 3:
                if (i == 0) {
                    printf("Buffer operation is empty\n");
                    break;
                }
                for (j = 0; j < i; j++)
                    printf("buf[%d]: %d\n", j, buf[j].input);
                break;
        case 0:
            sem_destroy(&filled);
            sem_destroy(&empty);
            exit (0);
            break;
        }
    }
    sem_destroy(&filled);
    sem_destroy(&empty);
    return 0;
}

void *producer(void *arg)
{
    int input = *(int *) arg;

    if (sem_wait(&empty)) { 
        printf("Error: Sem wait fail\n");
        pthread_exit(NULL);
    }

    buf[i].input = input;
    i++;

    if (sem_post(&filled)) { 
        printf("Error: Sem wait fail\n");
        pthread_exit(NULL);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{

    if (sem_wait(&filled)) { 
        printf("Error: Sem wait fail\n");
        pthread_exit(NULL);
    }

    i--;
    *(int *) arg = buf[i].input;

    if (sem_post(&empty)) { 
        printf("Error: Sem wait fail\n");
        pthread_exit(NULL);
    }
    pthread_exit(NULL);
}
