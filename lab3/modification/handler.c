#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define MAX 100
#define PORT 8080
#define SA struct sockaddr

int main()
{
   struct sockaddr_in servaddr, client;

   int sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd == -1) {
      printf("socket creation failed...\n");
      return 1;
   } else {
      printf("Socket successfully created..\n");
   }

   bzero(&servaddr, sizeof(servaddr));

   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(PORT);

   if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
      printf("socket bind failed...\n");
      close(sockfd);
      return 1;
   } else {
      printf("Socket successfully binded..\n");
   }

   if ((listen(sockfd, 5)) != 0) {
      printf("Listen failed...\n");
      close(sockfd);
      return 1;
   } else {
      printf("Server listening..\n");
   }

   int len = sizeof(client);

   int connfd = accept(sockfd, (SA*)&client, &len);
   if (connfd < 0) {
      printf("server accept failed...\n");
      close(sockfd);
      return 1;
   } else {
      printf("server accept the client...\n");
   }


   char mode = '+';
   long long result = 1;

   char buff[MAX];
   int n;

   for (;;) {
      bzero(buff, MAX);
      read(connfd, buff, sizeof(buff));

      if (strncmp(buff, "+", 1) == 0) {
         mode = '+';
      }
      else if (strncmp(buff, "*", 1) == 0) {
         mode = '*';
      }
      else if (strncmp(buff, "QUIT", 1) == 0) {
         break;
      }
      else {
         int valid = 1;
         long long value = 0;
         for (size_t i = 0; i != strlen(buff) - 1; ++i) {
            if ('0' <= buff[i] && buff[i] <= '9') {
               value = value * 10 + (buff[i] - '0');
            } else {
               printf("input error: %s", buff);
               valid = 0;
               break;
            }
         }

         if (valid == 0) {
            break;
         }

         if (mode == '+') {
            result += value;
         } else {
            result *= value;
         }
      }

      printf("%lld\n", result);
   }

   close(sockfd);
}
