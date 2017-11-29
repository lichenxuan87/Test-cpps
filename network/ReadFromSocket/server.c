/*
/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_LEN 65536

const char* data = "fdsavcx;klnreqwn;ozuivnerqw;djf;sdjaue9[rwqnklcvnxzm;hiofepjfo;kdsafdsa\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd\
        fdasfdsafdsafdsafasdfdsafdsafdsafdsafdsafdsarewqvczxvcxreqwrewqfdvcjkl;jrekqlw;nmlvczxvd";


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[BUFFER_LEN];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");
     bzero(buffer,BUFFER_LEN);
     n = read(newsockfd,buffer,BUFFER_LEN);
     if (n < 0)
         error("ERROR reading from socket");
     else
         printf("Here is the message: %s\n",buffer);
     n = write(newsockfd, data, strlen(data));
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0;
}




