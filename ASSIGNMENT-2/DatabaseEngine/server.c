#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#define PORT 8081

int main()
{
	char g[200],response[1024],data[100];
	int server_fd, new_socket, valread;
	  int opt = 1;
    struct sockaddr_in address;
    pid_t child_pid = -1 ; 
    int addrlen = sizeof(address);
	// Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
        if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

	printf("SERVER IS RUNNING\n");
	while(1)
  {
    new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
    child_pid=fork();
    if(child_pid==0)
    {
      while( (valread=read( new_socket , g, 200))>0)
      {
        printf("%s\n",g);
        char *split_text = strtok (g," ,.-");
        printf("%s\n",split_text );
        strcpy(response,"");
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
                strcat(response,data);
                strcat(response,"\n");
  					    //msgsnd(mid,&mess,sizeof(mess),1);
  					    fscanf(fp,"%s",data);
  					    strcat(response,data);
  				    }
  			    }
            else
            {
              strcpy(response,"Data not found ");
  			    }
          }
          else
          {
            strcpy(response,"Input incomplete ");
          }
        }
        else
        {
          strcpy(response,"Incorrect input");
        }
        printf("dvdsgh%sdbfmn\n",response);
        write(new_socket,response,strlen(response));
	strcpy(response," ");
      }
    }
  }
}
