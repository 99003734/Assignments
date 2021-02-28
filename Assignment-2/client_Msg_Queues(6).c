#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
 
#define SERVER_QUEUE_NAME "/sp-example-server"
#define QUEUE_PERMISSIONS 0660
#define MAXIMUM_MESSAGES 10
#define MAXIMUM_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAXIMUM_MSG_SIZE + 10
 
int main (int argc, char **argv)
{
 char client_queue_name [64];
 mqd_t qd_server, qd_client; 
 
 sprintf (client_queue_name, "/sp-example-client-%d", getpid ());
 
 struct mq_attr attr;
 
 attr.mq_flags = 0;
 attr.mq_maxmsg = MAXIMUM_MESSAGES;
 attr.mq_msgsize = MAXIMUM_MSG_SIZE;
 attr.mq_curmsgs = 0;
 
 if ((qd_client = mq_open (client_queue_name, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
 perror ("Client: mq open (client)");
 exit (1);
 }

 if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) 
 {
 perror ("Client: mq open (server)");
 exit (1);
 }
 char in_buffer [MSG_BUFFER_SIZE];
 printf ("Ask for a token (Press <ENTER>): ");
 char temp_buffer [10];

 while (fgets (temp_buffer, 2, stdin)) 
 {
 if (mq_send (qd_server, client_queue_name, strlen (client_queue_name) + 1, 0) == -1) {
 perror ("Client: Not able to send message to server");
 continue;
 }

 if (mq_receive (qd_client, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) 
 {
 perror ("Client: mq_receive");
 exit (1);
 }

 printf ("Client: Token received from server: %s\n\n", in_buffer);
 
 printf ("Ask for a token (Press ): ");
 }

 if (mq_close (qd_client) == -1) 
 {
 perror ("Client: mq close");
 exit (1);
 }

 if (mq_unlink (client_queue_name) == -1) 
 {
 perror ("Client: mq unlink");
 exit (1);
 }
 printf ("Client: bye\n");
 exit (0);
}
