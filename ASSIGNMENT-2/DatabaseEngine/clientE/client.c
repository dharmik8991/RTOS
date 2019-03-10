#include <stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include<string.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 8081
// structure for message queue 

int main()
{
    struct timeval start,intermediate, stop;
	 key_t key,clikey; 
   	 struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char m[200],response[1024];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address2/ Address not supported \n");
        return -1;
    }
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
   printf("Client Ready\n");
while(1){
 	strcpy(m,"GET server.c");
	gettimeofday(&start, NULL);
 	send(sock,m,sizeof(m),0);
	gettimeofday(&intermediate, NULL);
	read(sock,response,sizeof(response));
 	gettimeofday(&stop, NULL);
	printf("Sending time:%lu Response Time:%lu\n", (intermediate.tv_sec - start.tv_sec)*1000000 + (intermediate.tv_usec - start.tv_usec), (stop.tv_sec - intermediate.tv_sec)*1000000 + (stop.tv_usec - intermediate.tv_usec));
	printf("%s\n",response);
	}
}
