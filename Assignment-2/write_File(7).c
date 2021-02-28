#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 


int main() 
{
    int file_Direc; 
    char * my_FIFO = "/tmp/my_FIFO";
    mkfifo(my_FIFO, 0666);
    char data1[200], data2[200];
    while (1)
    {
    file_Direc = open(my_FIFO, O_WRONLY);
    fgets(data2, 100, stdin);
    write(file_Direc, data2, strlen(data2)+1);
    close(file_Direc);
    read(file_Direc, data1, sizeof(data1));
    printf("client1: %s\n", data1);
    close(file_Direc);
    }
return 0;
}
