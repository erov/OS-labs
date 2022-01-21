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
      printf("socket creation failed\n");
      return 1;
   }

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(PORT);

   if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
      printf("socket bind failed\n");
      close(sockfd);
      return 1;
   }

   if ((listen(sockfd, 5)) != 0) {
      printf("handler listening failed\n");
      close(sockfd);
      return 1;
   }

   int len = sizeof(client);

   int connfd = accept(sockfd, (SA*)&client, &len);
   if (connfd < 0) {
      printf("handler accept failed...\n");
      close(sockfd);
      return 1;
   }


   char mode = '+';
   long long result = 1;

   char buff[MAX];
   int n;

   for (;;) {
      bzero(buff, sizeof(buff));
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
         int positive = 1;
         size_t i = 0;
         
         if (strlen(buff) == 0) {
            valid = 0;
         } else {
            if (buff[i] == '-') {
               positive = 0;
               ++i;
            } else if (buff[i] == '+') {
               positive = 1;
               ++i;
            }
         }
         
         for (; valid && i != strlen(buff) - 1; ++i) {
            if ('0' <= buff[i] && buff[i] <= '9') {
               value = value * 10 + (buff[i] - '0');
            } else {
               printf("handler: input error: %s", buff);
               valid = 0;
            }
         }

         if (valid == 0) {
            break;
         }

         if (positive == 0) {
            value *= -1;
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
