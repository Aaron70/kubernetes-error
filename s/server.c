//https://www.geeksforgeeks.org/udp-server-client-implementation-c/

// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
    
#define PORT     20001 
#define MAXLINE 1024 
    
void sendMessage(int fd, char* message, struct sockaddr_in cliaddr){
    int len = sizeof(cliaddr);
    sendto(fd, (const char *)message, strlen(message),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len); 
}

// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
    char *endOfLine = "/0";

    struct sockaddr_in servaddr, cliaddr; 
        
    while( true ) {
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
        
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
        
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
        
      // Bind the socket with the server address 
     if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
             sizeof(servaddr)) < 0 ) 
     {  
         perror("bind failed"); 
         exit(EXIT_FAILURE); 
     } 
     int len, n; 
     len = sizeof(cliaddr);  //len is value/result 
      n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                  MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                  &len); 
      buffer[n] = '\0';
    printf("Client : %s\n", buffer); 
    sendMessage(sockfd,hello,cliaddr);
    sendMessage(sockfd,endOfLine,cliaddr);
    close(sockfd);
    printf("Hello message sent.\0");  
    }
     
        
    return 0; 
}
