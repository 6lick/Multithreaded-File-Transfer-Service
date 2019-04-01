// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in server_addr; 
    char *hello = "Hello from client";
    char *command; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&server_addr, '0', sizeof(server_addr)); 
   
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr)<=0)  { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }
    //test message 
    // send(sock , hello , strlen(hello) , 0 );
    // valread = read( sock , buffer, 1024); 
    // printf("%s\n",buffer );
    // printf("Hello message sent\n");
    // memset(buffer, 0, sizeof buffer);
    //real program
    while (command != "bye"){
        memset(buffer, 0, sizeof buffer);
        printf("%c", '>');
        fgets(command, 256, stdin);
        //remove trailing newline
        int len=strlen(command); 
        if (command[len-1]=='\n')
            command[len-1]='\0';
        send(sock,command, strlen(command), 0 );
        valread = read( sock , buffer, 1024); 
        printf("buffer: %s\n",buffer );
    }
     

     
    return 0; 
} 