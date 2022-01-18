#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 100
#define PORT 8080
#define SA struct sockaddr

int is_number(char const* buff) {
    for (size_t i = 0; i != strlen(buff) - 1; ++i) {
        if (!('0' <= buff[i] && buff[i] <= '9')) {
            return 0;
        }
    }
    return 1;
}

int main()
{
    struct sockaddr_in servaddr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        return 1;
    } else {
        printf("Socket successfully created..\n");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        close(sockfd);
        return 1;
    } else {
        printf("connected to the server..\n");
    }


    char buff[MAX];
    int n;

    for (;;) {
        bzero(buff, sizeof(buff));
        n = 0;
      
        while ((buff[n++] = getchar()) != '\n') {
            ;
        }
        
        write(sockfd, buff, sizeof(buff));
        
        if (!is_number(buff) && strncmp(buff, "+", 1) != 0 && strncmp(buff, "*", 1) != 0) {
            break;
        }
    }

    close(sockfd);
}
