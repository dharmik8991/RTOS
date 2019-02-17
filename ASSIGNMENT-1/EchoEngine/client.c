#include <stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
  
// structure for message queue 
struct mesg_buffer { 
    char mesg_text; 
} message; 

int main()
{
	 key_t key; 
    int msgid; 
   char m;
    // ftok to generate unique key 
    key = ftok("/home/dharmik/rtos/ASSIGNMENT-1/EchoEngine",'a'); 
    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT); 
 	scanf("%s",&m);
 	message.mesg_text=m;
 	msgsnd(msgid, &message, sizeof(message.mesg_text),IPC_NOWAIT); 
}