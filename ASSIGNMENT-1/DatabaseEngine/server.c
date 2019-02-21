#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include<sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h>
// structure for message queue 
struct mesg_buffer { 
	int Id;
    char mesg_text[200]; 
} message,mess; 

int main()
{
	key_t key,clikey;
	int id,mid[5],num;
	char *search_file,*g,data[200];
	//scanf("%s",g);
	key = ftok("/home/dharmik/rtos/ASSIGNMENT-1/EchoEngine",'a');
	   for(int i=0;i<5;i++)
    {
    	clikey=ftok("/home/dharmik/rtos/ASSIGNMENT-1/EchoEngine/clientA",i); 
    	mid[i] = msgget(clikey, 0666 | IPC_CREAT);
    } 
	id = msgget(key, 0666 | IPC_CREAT);
	printf("SERVER IS RUNNING\n");
	while(1){if(msgrcv(id, &message, sizeof(message), 0, IPC_NOWAIT)!=-1){
	g=message.mesg_text;
	num=message.Id;
	mess.Id=num;
	strcpy(mess.mesg_text,"");
	char *split_text = strtok (g," ,.-");
  if(strcmp(split_text,"GET")==0)
  	{
  		split_text= strtok(NULL," ,-");
  		if(split_text!=NULL)
  		{
  			//strcat(path,split_text);
  			FILE *fp=fopen(split_text,"r");
  			if(fp)
  			{ 
				while(fscanf(fp,"%[^\n]",data)!=EOF)
				{
					strcat(mess.mesg_text,data);
					strcat(mess.mesg_text,"\n");
					//msgsnd(mid,&mess,sizeof(mess),1);
					fscanf(fp,"%s",data);
					strcat(mess.mesg_text,data);
				}
				msgsnd(mid[num],&mess,sizeof(mess),0);
			}
			else
			{
				strcpy(mess.mesg_text,"Data not found");
				msgsnd(mid[num],&mess,sizeof(mess),IPC_NOWAIT);
			}
		}
		else
		{
			strcpy(mess.mesg_text,"Input incomplete");
			msgsnd(mid[num],&mess,sizeof(mess),IPC_NOWAIT);
		}

}
else{
	strcpy(mess.mesg_text,"Incorrect input");
	msgsnd(mid[num],&mess,sizeof(mess),IPC_NOWAIT);
}
}
}
}
