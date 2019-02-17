#include <stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include<string.h>
  
// structure for message queue 
struct mesg_buffer { 
    int id;
    char mesg_text[200]; 
} message,mess; 

int main()
{
	 key_t key,clikey; 
    int msgid; 
   char m[200];
    // ftok to generate unique key 
    key = ftok("/home/dharmik/rtos/ASSIGNMENT-1/EchoEngine",'a'); 
    clikey=ftok("/home/dharmik/rtos/ASSIGNMENT-1/EchoEngine/clientA",2);
    // msgget creates a message queue 
    // and returns identifier 
    msgid=msgget(key, 0666 | IPC_CREAT);
    int mid=msgget(clikey,0666 | IPC_CREAT); 
while(1){
 	scanf(" %[^\n]",m);
 	strcpy(message.mesg_text,m);
 	msgsnd(msgid, &message, sizeof(message),IPC_NOWAIT);
	msgrcv(mid, &mess, sizeof(mess), 0, MSG_NOERROR);
	printf("%s\n",mess.mesg_text);
	}
}
