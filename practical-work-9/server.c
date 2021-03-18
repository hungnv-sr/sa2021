#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main() {
    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8080;
    char s[100];
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
        exit(1);
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    if ((bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0)) {
        printf("Error binding\n");
        exit(1);
    }
    if (listen(sockfd, 5) < 0) {
        printf("Error listening\n");
        exit(1);
    }
    clen=sizeof(caddr);
    if ((clientfd=accept(sockfd, (struct sockaddr *) &caddr, (socklen_t *)&clen)) < 0) {
        printf("Error accepting connection\n");
        exit(1);
    }
    while (1) {
        // handle multiple client
        if ((clientfd=accept(sockfd, (struct sockaddr *) &caddr, (socklen_t *)&clen)) < 0) {
            printf("Error accepting connection\n");
            exit(1);
        }
        int pid = fork();
        if (pid == 0) {
            printf("client connected\n");

            while (1) {
                read(clientfd, s, sizeof(s));
                printf("client says: %s\n",s);
                // send to client
                printf("server> ");
                scanf("%s", s);
                write(clientfd, s, strlen(s) + 1);
            }
            return 0;
        }
        else {
            // accept more client
            continue;
        }
    }
    close(clientfd);
}