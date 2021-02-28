#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int input, char *argv[])
{
    pid_t data;
    int temp,i;

    data = fork();
    if(data>0)
    {
        
        data = waitpid(-1,&temp,0);
        printf("\nMini Shell END\n");
    }
    else
    {
       
        execlp(argv[1],argv[1],argv[2],NULL);
        sleep(2);

    }
}
