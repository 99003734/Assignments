#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mqueue.h>
#include<fcntl.h>
#include<unistd.h>
#include <ctype.h> 
int main()
{
    int ret,no_Of_Bytes;
    struct mq_attr attr;
    attr.mq_msgsize=256;
    attr.mq_maxmsg=10;
    mqd_t mqid;
    mqd_t mqid1;
    mqid=mq_open("/mque",O_RDONLY|O_CREAT,0666,&attr);
    mqid1=mq_open("/mque",O_WRONLY|O_CREAT,0666,&attr);
    if(mqid<0)
    {
        perror("mq open");
        exit(1);
    }
    char buf[8192];
    char send[8192];
    int maximum_Length=256,priority;
    no_Of_Bytes=mq_receive(mqid,buf,maximum_Length,&priority);
    printf("Number of bytes %d\n",no_Of_Bytes);
    if(no_Of_Bytes<0)
    {
        perror("mq received");
        exit(2);
    }
    buf[no_Of_Bytes]='\0';
    printf("receive msg:%s,no_Of_Bytes=%d,priority=%d\n",buf,no_Of_Bytes,priority);

 

    int len=strlen(buf);
    int i;
       for(i=0;i<len;i++){
      if(buf[i]>=65&&buf[i]<=90)
         send[i]=buf[i]+32;
   }

 

    ret=mq_send(mqid1,send,len,10);
    printf("ret %d\n",ret);
    
if(ret<0)
{
perror("mq send");
exit(2);
}
printf("sent %s\n",send);
}
