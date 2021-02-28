#include <unistd.h> 
#include <sys/types.h>
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
int main() 
{ 
    int file_Desc; 
    char *temp = "/tmp/temp"; 
    mkfifo(temp, 0666); 
    char temp1[300], temp2[300]; 
    while (1) 
    { 
     file_Desc = open(temp,O_RDONLY); 
     read(file_Desc, temp1, 100); 
     printf("Client2: %s \n", temp1); 
     close(file_Desc); 
     file_Desc = open(temp,O_WRONLY); 
     fgets(temp2, 100, stdin); 
     write(file_Desc, temp2, strlen(temp2)+1); 
     close(file_Desc); 
    } 
    return 0; 
}
