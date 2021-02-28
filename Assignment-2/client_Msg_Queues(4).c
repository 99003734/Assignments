#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<mqueue.h>
#include<fcntl.h>


int main(char argc,char *argv[])
{
 pid_t ret;
 pid_t cpid;
 int maximum_Size =100;
 char cmd[maximum_Size];
     int ret1,no_Of_Bytes;
    struct mq_attr attr;
    attr.mq_msgsize=256;
    attr.mq_maxmsg=10;
    mqd_t mqid;
    mqd_t mqid1;
    mqid=mq_open("/mque",O_RDONLY|O_CREAT,0666,&attr);
   
        if(mqid<0)
    {
        perror("mq open");
        exit(1);
    }
    char buf[8192];
    char send[8192];
    int maxlen=256,priority;
    no_Of_Bytes=mq_receive(mqid,buf,maxlen,&priority);
    printf("no_Of_Bytes %d\n",no_Of_Bytes);
    if(no_Of_Bytes<0)
    {
        perror("mq_recv");
        exit(2);
    }
    buf[no_Of_Bytes]='\0';
    printf("receive msg:%s,no_Of_Bytes=%d,priority=%d\n",buf,no_Of_Bytes,priority);
   
 ret=fork();
  if(ret==0)
 {
printf("receive msg:%s,no_Of_Bytes=%d,priority=%d\n",buf,no_Of_Bytes,priority);
int k;
 argv[0]=buf;
 k=execlp(buf, argv,NULL);
 if(k<0)
 {
 perror("execl");
 exit(1);
 }

 }
 if(ret>0)
 {
 pid_t status;
 cpid=waitpid(-1,&status,NULL);
 printf("\nExit status %d",status);
 exit(0);
 }
 else
 {
 perror("Process doesn't exist");
 exit(3);
 }
 }
