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
	char g,c;
	int server_fd, new_socket, valread;
	  int opt = 1;
    struct sockaddr_in address;

    int addrlen = sizeof(address);
	// Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
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
    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
   while(1)
   {
    new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
    if(fork()==0)
    {
     while((valread=read( new_socket , &c, sizeof(c)))>0)
    {
      if(c>='a' && c<='z')
      {
        printf("%c\n",toupper(c));
        c=toupper(c);
      }
      else if(c>='A' && c<='Z')
      {
        printf("%c\n",tolower(c));
			  c=tolower(c);
      }	
      send(new_socket,&c,1 , 0 );
	}
}

}
}
