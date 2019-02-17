#include <stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
  
// structure for message queue 
struct mesg_buffer { 
	int id;
    char mesg_text; 
} message,mess; 

int main()
{
	 key_t key,clikey; 
    int msgid,mid; 
   char m;
    // ftok to generate unique key 
    key = ftok("/home/dharmik/rtos/ASSIGNMENT-1/EchoEngine",'s');
    clikey=ftok("/home/dharmik/rtos/ASSIGNMENT-1/EchoEngine/clientA",1);  
    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT); 
	mid = msgget(clikey, 0666 | IPC_CREAT);
   while(1)
   {
 	scanf("%s",&m);
 	message.id=1;
 	message.mesg_text=m;
 	msgsnd(msgid, &message, sizeof(message), MSG_NOERROR); 
 	msgrcv(mid, &mess, sizeof(mess), 0, 1);
 	printf("Output:%c\n",mess.mesg_text);
 	//printf("\n");
   }
}
