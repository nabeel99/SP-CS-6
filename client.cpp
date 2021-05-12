/*
 Copyright (c) 1986 Regents of the University of California.
 All rights reserved.  The Berkeley software License Agreement
 specifies the terms and conditions for redistribution.

	@(#)streamwrite.c	6.2 (Berkeley) 5/8/86
*/

#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctime>
#include <pthread.h>
#define DATA "Half a league, half a league . . ."

int sock;
bool connected = true;
/*
 * This program creates a socket and initiates a connection with the socket
 * given in the command line.  One message is sent over the connection and
 * then the socket is closed, ending the connection. The form of the command
 * line is streamwrite hostname portnumber 
 */
void siginthandler(int signo){
	if (signo==SIGINT){
		write(STDOUT_FILENO,"Exiting\n",strlen("Exiting\n"));
		int e =write(sock,"exit",strlen("exit")+1);
		printf("sigint e is %d\n",e);
		if(e<=0){
			perror("cant send exit command");
		exit(0);
		}
	}

}
void* client_send(void * a){
	while(1) {
	//int Bn = write(STDOUT_FILENO,"Enter Command: \n", sizeof("Enter Command: \n"));
	char userInput[100];
    int re = read(STDIN_FILENO,userInput,100);
	if(re<0){
		perror("read error");
		break;
			}
    char bytread[100];
	write(STDOUT_FILENO,"here\n",strlen("here\n"));
    int we = write(sock,userInput,re);
	char out[100];
	int s = sprintf(out,"got %d bytes\n",we);
	write(STDOUT_FILENO,out,s);
	if(we<=0){
		perror("write error");
		break;
			}
    
	}
	close(sock);
	return 0;
}
int main(int argc, char *argv[])
	{
	signal(SIGINT,siginthandler);
	struct sockaddr_in server;
	struct hostent *hp;
	char buf[1024];

	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
		exit(1);
	}
	/* Connect socket using name specified by command line. */
	server.sin_family = AF_INET;
	hp = gethostbyname(argv[1]);
	if (hp == 0) {
		fprintf(stderr, "%s: unknown host\n", argv[1]);
		exit(2);
	}
	bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
	server.sin_port = htons(atoi(argv[2]));

	if (connect(sock,(struct sockaddr *) &server,sizeof(server)) < 0) {
		perror("connecting stream socket");
		exit(1);
	}
	
	 pthread_t send;
	 pthread_create(&send,NULL,client_send,NULL);
	 pthread_detach(send);
	while(1) {
	char serverOutput[1000];
	bzero(serverOutput,sizeof(serverOutput));
    int bytes_read = read(sock,serverOutput,500);

    if(bytes_read<=0){
		perror("read error");
		break;
			}
		char mmsg[100];
		int p =sprintf(mmsg,"Recieved  Message from server of length :%d\n",bytes_read);
		write(STDOUT_FILENO,mmsg,p);
    	int byt =  write(STDOUT_FILENO,serverOutput,bytes_read);
		bzero(mmsg,sizeof(mmsg));
		
		if(byt<0){
			perror("writing error");
		
		break;
		}

			
	}
    
		close(sock);
		return 0;
}