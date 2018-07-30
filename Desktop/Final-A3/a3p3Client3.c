// Jack Zumwalt
// jsz160130
// CS 3377-0W1
// Assignment 3

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 30000 /*port*/

int main(int argc, char **argv)
{
    
    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE], recvline[MAXLINE];
    
    // alarm(300);  // to terminate after 300 seconds
    
    //Check arguments
    perror(argv[1]);
    perror(argv[2]);
    
    if (argc !=3) {
        
        perror("Usage: TCPClient <Server IP> <Server Port>");
        exit(1);
        
    }
    
    //Create a socket for the client
    //If sockfd<0 there was an error in the creation of the socket
    if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
        
        perror("Cannot create socket");
        exit(2);
        
    }
    
    //Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr= inet_addr(argv[1]);
    servaddr.sin_port =  htons((int) strtol(argv[2], (char **)NULL, 10));
    
    //Connection of the client to the socket
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
        
        perror("Cannot create sockets");
        exit(3);
        
    }
    
    while (fgets(sendline, MAXLINE, stdin) != NULL) {
        
        send(sockfd, sendline, strlen(sendline), 0);
        
        if (recv(sockfd, recvline, MAXLINE,0) == 0){
            
            //error: server terminated prematurely
            perror("The server terminated early");
            exit(4);
            
        }
        
        printf("%s", "String received from the server: ");
        fputs(recvline, stdout);
        
        FILE *fp;
        
        fp = fopen("a3p1ServerLog.txt", "w");
        fprintf(fp, "%s", recvline);
        fclose(fp);
        
    }
    
    exit(0);
}
