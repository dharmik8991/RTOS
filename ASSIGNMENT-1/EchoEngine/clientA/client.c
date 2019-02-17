#include <stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <time.h>
  
// structure for message queue 
struct mesg_buffer { 
	int id;
    char mesg_text; 
} message,mess; 

int main()
{
	clock_t t,t1,t2;
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
	t=clock();
 	msgsnd(msgid, &message, sizeof(message),IPC_NOWAIT);
	t1=clock(); 
 	msgrcv(mid, &mess, sizeof(mess), 0, MSG_NOERROR);
	t2=clock();
 	printf("Output:%c\n",mess.mesg_text);
	printf("Time taken for sending:%f servicing request: %f\n",((double)(t1-t))/CLOCKS_PER_SEC,((double)(t2-t1))/CLOCKS_PER_SEC );
 	//printf("\n");
   }
}
