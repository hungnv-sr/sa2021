#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
    int pid_write;
    char s[100];
    struct sockaddr_in saddr;
    struct hostent *h;
    int sockfd;
    // unsigned short port = 8784;
    unsigned short port = 8080;
    // char host[100] = "127.0.0.1";
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
        exit(1);
    }
    if ((h=gethostbyname("localhost")) == NULL) {
        printf("Unknown host\n");
        exit(1);
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    saddr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect\n");
        exit(1);
    }

    pid_write = fork();
    if (pid_write == 0)
    {   
        // Read + send message
        while (1) {
            fgets(s, sizeof(s), stdin);
            int numwrite = write(sockfd, s, strlen(s) + 1);
        }
        
    }
    // read + write message
    while(1){
        int numread = read(sockfd, s, sizeof(s));
        if (numread != 0)
        {
            printf("server says: %s\n", s);    
        } else {
            // read fail or server down,...
            printf("server disconnected\n");
            kill(pid_write,SIGKILL);
            break;
        }
        
    }
    close(sockfd);
    return 0;
}
