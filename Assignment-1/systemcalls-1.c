#include<unistd.h>
#include<fcntl.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    int file1, file2, size1, str_length1, str_length2, size2;
    file1=open("sample.txt",O_RDONLY);
    file2=open("destination.txt",O_WRONLY|O_CREAT, 0666);
    if(file1<0)
    {
        perror("open");
        exit(1);
    }
    if(file2<0)
    {
        perror("open");
        exit(1);
    }
    int size=300;
    char str1[size];
    char str2[size];
    size1= read(file1,str1,size);
    str_length1=strlen(str1);
    strcpy(str2,str1);
    if(size1<0)
    {
        perror("read");
        exit(2);
    }
    str_length1= strlen(str2);
    size2= write(file2, str2, str_length1);
    if(size2<0)
    {
        perror("write");
        exit(2);
    }
    printf("Written successfully, no_of_bytes_1=%d\n",size2);
     close(file2);
     close(file1);
     return 0;
}
