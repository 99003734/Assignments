#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int data, char *argv[])
{
    pid_t ret;
    int temp;

    ret = fork();
    if(ret>0)
    {
       
        ret = waitpid(-1,&temp,0);
    }
    else
    {
        
        for(int i=1;i<data;i++)
        {
            ret = fork();
            if(ret>0)
                ret = waitpid(-1,&temp,0);
            else
                execlp("gcc","gcc",argv[i],"-c",NULL);
        }

        
        for(int i=1;i<data;i++)
        {
            for(int j=0;argv[i][j]!='\0';j++)
                if(argv[i][j]=='.')
                {
                    argv[i][j+1]='o';
                    break;
                }
        }
        ret=fork();
        if(ret>0)
            ret = waitpid(-1,&temp,0);
        else
            execlp("gcc","gcc",argv[1],argv[2],argv[3],"-o","test",NULL);

         
        execlp("./test","./test",NULL);
    }
}
