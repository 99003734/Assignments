#include <stdio.h>

#include <pthread.h>

#include <stdlib.h>

 
#define array_Size 1000 
   
#define THREAD 10 
  
  
int a[] = { 1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 100, 150, 300, 400 }; 
int sum[10] = { 0 }; 
int temp = 0; 
  
void* parallel_Sum(void* arg) 
{ 
  
     
    int multi_Thread = temp++; 
  
    for (int i = multi_Thread * (array_Size / 10); i < (multi_Thread + 1) * (array_Size / 10); i++) 
        sum[multi_Thread] += a[i]; 
} 
  

int main() 
{ 
  
    pthread_t threads[THREAD]; 
  
    
    for (int i = 0; i < THREAD; i++) 
        pthread_create(&threads[i], NULL, parallel_Sum, (void*)NULL); 
  
    
    for (int i = 0; i < THREAD; i++) 
        pthread_join(threads[i], NULL); 
  
    
    int total_Sum = 0; 
    for (int i = 0; i < THREAD; i++) 
        total_Sum += sum[i]; 
  
    
    printf("sum is %d\n",total_Sum);
  
    return 0; 
} 
