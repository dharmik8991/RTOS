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
#define PORT 8000
#include <signal.h>
FILE *fp;
void closure(int sig_num) 
{ 
    //signal(SIGINT, sigintHandler); 
    printf("\nExit\n"); 
    fclose(fp);
    exit(0);
} 

int main()
{
    fp=fopen("data.csv","w+");
    char message[200],req[3]="GET";
    fprintf(fp,"Sno,Sensor1,Sensor2,Sensor3,Sensor4,Sensor5");
    struct timeval start, stop;
    long int value;
	 key_t key,clikey; 
   	 struct sockaddr_in address;
    int i,sock = 0, valread;
    struct sockaddr_in serv_addr;
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
    int j=1;
    while(1)
    {
        signal(SIGINT, closure);
        printf("Sending request\n");
        send(sock,req,sizeof(req),0);
        gettimeofday(&start, NULL);
        fprintf(fp,"\n%d",j);
        printf("Recieving response\n");
        for(i=1;i<6;i++)
        {
            if((valread=read(sock,message,sizeof(message))>0))
            {
                fprintf(fp,",%s",message);
                printf("Data%d:%s\n",i,message);
            }
        }
        gettimeofday(&stop, NULL);
        value=(stop.tv_sec-start.tv_sec)+((stop.tv_usec-start.tv_usec)/1000000);
        j=j+1;
        printf("\n");
        sleep(2-value);
    }
}
