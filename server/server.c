#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#define PORT 8080 

char* SERVICES[] =  {"catalog", "download", "upload", "spwd", "bye"};
int main(int argc, char const *argv[]) 
{ 
    
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
            perror("socket failed"); 
            exit(EXIT_FAILURE); 
        } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE); 
        } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen failed"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) { 
        perror("accept failed"); 
        exit(EXIT_FAILURE); 
    } 

    // valread = read( new_socket , buffer, 1024);
    // printf("test: %s\n",buffer ); 
    // send(new_socket , hello , strlen(hello) , 0 );
    //TODO add connection lost condition condition
    while (buffer != SERVICES[4]){
        //reset buffer
        memset(buffer, 0, sizeof buffer); 
        valread = read( new_socket , buffer, 1024);
        printf("Buffer: %s\n",buffer); 
        get_service(&buffer);
        send(new_socket , buffer , strlen(buffer) , 0 ); 
        
    } 
    return 0; 
}




//todo return string array
int get_service(char* service){
    int serviceVal = -1;
    int SIZE_MAX = 1024;
    FILE *fp;
    int status;
    char syscall_buff[1024];
    char return_buff[SIZE_MAX];

    printf("service requested: %s\n", service);
    
    //check args 
    for (int i=0; i < 5; i++ ){
        if (strcmp(service, SERVICES[i]) ==0){
            printf("FOUND: %s\n", SERVICES[i]);
            serviceVal = i;
        }    
    }
    if (serviceVal < 0)
        printf("service : %s is not found\n", service);
    else{
        switch(serviceVal){
            //catalog
            case 0:
                printf("entering case 0\n");
                fp = popen("ls *", "r");
                while (fgets(syscall_buff, SIZE_MAX, fp) != NULL)
                    printf("%s", syscall_buff);
                status = pclose(fp);
                // system("ls");
                break;
            //download
            case 1:
                break;
            //upload
            case 2:
                break;
            //spwd
            case 3:
                system("pwd");
                break;
            //bye
            case 4:
                break;
            default:
                printf("Please enter a valid command\n");


        }
    }
    
    return 0;
}