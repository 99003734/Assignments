#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>


void signals(int input)
{
    write(1,"Process Killed\n",10);

}

int main()
{
    signal(SIGKILL,signals);
    while(1)
    {
        printf("Process ID= %d\n",getpid());
        sleep(1);
    }
}
