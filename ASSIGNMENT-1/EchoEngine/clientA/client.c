#include <stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/time.h>
// structure for message queue 
struct mesg_buffer { 
	int id;
    char mesg_text; 
} message,mess; 



int main()
{
	struct timeval start, intermediate,stop;
	 key_t key,clikey; 
    int msgid,mid; 
   char m;
    // ftok to generate unique key 
    key = ftok("/home/dharmik/rtos/ASSIGNMENT-1/EchoEngine",'s');
    clikey=ftok("/home/dharmik/rtos/ASSIGNMENT-1/EchoEngine/clientA",0);  
    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT); 
	mid = msgget(clikey, 0666 | IPC_CREAT);
   while(1)
   {
 	scanf("%s",&m);
 	message.id=0;
 	message.mesg_text=m;
	gettimeofday(&start, NULL);
 	msgsnd(msgid, &message, sizeof(message),IPC_NOWAIT);
  gettimeofday(&intermediate, NULL);
 	msgrcv(mid, &mess, sizeof(mess), 0, MSG_NOERROR);
	gettimeofday(&stop, NULL);
 	printf("Output:%c\n",mess.mesg_text);
	printf("Sending time:%lu Response Time:%lu\n", (intermediate.tv_sec - start.tv_sec)*1000000 + (intermediate.tv_usec - start.tv_usec), (stop.tv_sec - intermediate.tv_sec)*1000000 + (stop.tv_usec - intermediate.tv_usec));
   }
}
