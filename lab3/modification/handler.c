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

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

int main()
{
   int sockfd, connfd, len;
   struct sockaddr_in servaddr, cli;

   // socket create and verification
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd == -1) {
      printf("socket creation failed...\n");
      exit(0);
   }
   else {
      printf("Socket successfully created..\n");
   }
   bzero(&servaddr, sizeof(servaddr));

   // assign IP, PORT
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(PORT);

   // Binding newly created socket to given IP and verification
   if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
      printf("socket bind failed...\n");
      exit(0);
   }
   else {
      printf("Socket successfully binded..\n");
   }

   // Now server is ready to listen and verification
   if ((listen(sockfd, 5)) != 0) {
      printf("Listen failed...\n");
      exit(0);
   }
   else {
      printf("Server listening..\n");
   }
   len = sizeof(cli);

   // Accept the data packet from client and verification
   connfd = accept(sockfd, (SA*)&cli, &len);
   if (connfd < 0) {
      printf("server accept failed...\n");
      exit(0);
   }
   else{
      printf("server accept the client...\n");
   }


   char mode = '+';
   long long result = 1;

   char buff[MAX];
   int n;

   for (;;) {
      bzero(buff, MAX);

      read(connfd, buff, sizeof(buff));
      // printf("From client: %s", buff);

      if (buff[0] == '+' && strlen(buff) == 2) {
         mode = '+';
      }
      else if (buff[0] == '*' && strlen(buff) == 2) {
         mode = '*';
      }
      else if (buff[0] == 'Q' && buff[1] == 'U' && buff[2] == 'I' && buff[3] == 'T' && strlen(buff) == 5) {
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
