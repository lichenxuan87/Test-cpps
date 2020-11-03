#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#define BUFFER_LEN 65536

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void* recvMessage(void* newsockfd)
{
	int sockfd = *((int*)newsockfd);
	char buffer[BUFFER_LEN];
	int n = 0;

	while (1)
	{
		bzero(buffer,BUFFER_LEN);
		n = read(sockfd,buffer,BUFFER_LEN);
		if (n < 0)
			 error("ERROR reading from socket");
		else
			printf("Received %d bytes\n", n);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFFER_LEN];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    pthread_t pid = 0;
    pthread_create(&pid, NULL, recvMessage, &sockfd);

    while(1){
		printf("Please enter the message: ");
		bzero(buffer,BUFFER_LEN);
		fgets(buffer,BUFFER_LEN,stdin);
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0){
			 error("ERROR writing to socket");
			 break;
		}
	}

    close(sockfd);
    return 0;
}
