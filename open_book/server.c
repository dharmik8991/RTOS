#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#define PORT 8000

int main()
{
    int fd_read1;
	int server_fd, new_socket, valread,i;
	  int opt = 1;
    struct sockaddr_in address;

    int addrlen = sizeof(address);
    char file_name[20],response[200],message[3];
	// Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8000
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
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
    if (listen(server_fd, 2) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
   while(1)
   {
    new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
    if(fork()==0)
    {
        while(read(new_socket, message, sizeof(message))>0)
        {
            if(strcmp(message,"GET")==0)
            {
                for(i=1;i<6;i++)
                {
                    sprintf(file_name, "sensor%d.txt", i); 
                    memset(response,0,sizeof(response));
                    fd_read1=open(file_name,O_RDONLY);
                    read(fd_read1,&response,200);
                    close(fd_read1);
                    send(new_socket,response,sizeof(response), 0);
                }
            }
        }
    }
}
}