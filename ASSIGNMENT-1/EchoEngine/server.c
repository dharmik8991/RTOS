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
    int msgid,mid[5],Id; 
    char c;
    key = ftok("/home/dharmik/rtos/ASSIGNMENT-1/EchoEngine",'s');
    for(int i=0;i<5;i++)
    {
    	clikey=ftok("/home/dharmik/rtos/ASSIGNMENT-1/EchoEngine/clientA",i); 
    	mid[i] = msgget(clikey, 0666 | IPC_CREAT);
    } 
    // msgget creates a message queue  
    msgid = msgget(key, 0666| IPC_CREAT);
   while(1){if(msgrcv(msgid, &message, sizeof(message), 0, IPC_NOWAIT)!=-1){
	c=message.mesg_text;
	Id=message.id;
		if(c>='a' && c<='z')
		{
			printf("%c\n",toupper(c));
			mess.mesg_text=toupper(c);
		}
		else if(c>='A' && c<='Z')
		{
			printf("%c\n",tolower(c));
			mess.mesg_text=tolower(c);

		}
		else
		{
			mess.mesg_text=c;
		}
		msgsnd(mid[Id], &mess, sizeof(mess),IPC_NOWAIT);
	}
}
}
