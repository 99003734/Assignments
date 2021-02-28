#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int data, char *argv[])
{
    pid_t ret;
    int temp,i;

    ret = fork();
    if(ret>0)
    {
        
        ret = waitpid(-1,&temp,0);
        printf("\nYour File Compiled and Linked\n");
    }
    else
    {
        execlp("gcc","gcc",argv[1],NULL);
        sleep(2);

    }
}
