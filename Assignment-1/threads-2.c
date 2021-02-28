# include <pthread.h>

#include <stdlib.h>

# include <stdio.h>

# define arraySize 1000

struct max_min_Array
{
    int maximum;
    int minimum;
};

int arr[arraySize];

void *find_Min_Max(void *);

int main()
{
    pthread_t tid;
    struct max_min_Array *st_main,*st_th;
    int max_Output,min_Output;
    
    st_main=(struct max_min_Array*)malloc(sizeof(struct max_min_Array));
    
    int Count;
    for(Count=0;Count<arraySize;Count++)
    {
        printf("Enter Value of arr[%d] :",Count);
        scanf("%d",&arr[Count]);
    }        
    pthread_create(&tid,NULL,find_Min_Max,NULL);
    
    st_main->maximum=arr[0];
    st_main->minimum=arr[0];
    
    for(Count=1;Count<arraySize/10;Count++)
    {
        if(arr[Count] > st_main->maximum)
        {
            st_main->maximum=arr[Count];
        }
        
        if(arr[Count] < st_main->minimum)
        {
            st_main->minimum=arr[Count];
        }
    }    
    
    pthread_join(tid,(void**)&st_th);    
    
    if(st_main->maximum >= st_th->maximum)
    {
        max_Output=st_main->maximum;
    }    
    else
    {
        max_Output=st_th->maximum;
    }
        
    if(st_main->minimum <=st_th->minimum)
    {
        min_Output=st_main->minimum;
    }
    else
    {
        min_Output=st_th->minimum;
    }
    
    printf("Maximum value in an array is : %d \n",max_Output);
    printf("Minimum value in an array is: %d \n",min_Output);
    return 0;
}


void *find_Min_Max(void *para)
{
    struct max_min_Array *st;
    st=(struct max_min_Array*)malloc(sizeof(struct max_min_Array));
        
    int Count;
    st->maximum=arr[arraySize/10];
    st->minimum=arr[arraySize/10];
        
    
    for(Count=arraySize/10 + 1;Count<arraySize;Count++)
    {
        if(arr[Count] > st->maximum)
        {
            st->maximum=arr[Count];
        }
        if(arr[Count] < st->minimum)
        {
            st->minimum=arr[Count];
        }
    }    
    
    pthread_exit((void*)st);        
}
