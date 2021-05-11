

/*
 Copyright (c) 1986 Regents of the University of California.
 All rights reserved.  The Berkeley software License Agreement
 specifies the terms and conditions for redistribution.

	@(#)streamread.c	6.2 (Berkeley) 5/8/86
*/
#include <pthread.h>
#include <time.h>
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
#include <netinet/in.h>
#include <arpa/inet.h>

#define TRUE 1

/*
 * This program creates a socket and then begins an infinite loop. Each time
 * through the loop it accepts a connection and prints out messages from it. 
 * When the connection breaks, or a termination message comes through, the
 * program accepts a new connection. 
 */

void* serverWork(void *);
struct process{
        char pName[100];
        pid_t pID;
        int status;
        bool term = false;
        time_t start_time;
        char *start_time_str;
        time_t end_time;
        time_t elapsed_time;
    };
	struct client_DAT{
		sockaddr_in client_network_details;
		process pList[50];
		int clientID;
		int activeProcesses = 0;
		int totalProcesses = 0;
		int connsocket;
	};
	client_DAT clientList[100];
    // int clientList[index].activeProcesses = 0;
    // int clientList[index].totalProcesses = 0;
	int clientCount = 0;
    // process clientList[index].pList[100];
    // process terminated[100];
int main()
{
	int sock, length,length2;
	int msgsock;
	struct sockaddr_in server;
	struct sockaddr_in client_add;
	char buf[1024];
	int rval;
	int i;

	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
		exit(1);
	}
	/* Name socket using wildcards */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(9003);
	if (bind(sock, (struct sockaddr *) &server, sizeof(server))) {
		perror("binding stream socket");
		exit(1);
	}
	/* Find out assigned port number and print it out */
	length = sizeof(server);
	if (getsockname(sock, (struct sockaddr *) &server, (socklen_t*) &length)) {
		perror("getting socket name");
		exit(1);
	}
	printf("Socket has port #%d\n", ntohs(server.sin_port));
	fflush(stdout);

	/* Start accepting connections */
	listen(sock, 2);
//thread creation
//initialize
//create
	while(true){
		length2 = sizeof(client_add);
		msgsock = accept(sock,(struct sockaddr *)&client_add ,(socklen_t *) &length2);
		if(msgsock<0)
			perror("accept");
		write(STDOUT_FILENO,"Accepted\n",strlen("Accepted\n"));
		
		bzero(buf,sizeof(buf));
		write(STDOUT_FILENO,"Accepted\n",strlen("Accepted\n"));

		pthread_t t;
		//client_DAT *c1 = (client_DAT*) (malloc(sizeof(client_DAT)));
		int *index = (int *) malloc(sizeof(int));
				write(STDOUT_FILENO,"Accepted\n",strlen("Accepted\n"));


		*index = clientCount;
		clientList[*index].connsocket = msgsock; 
		clientList[*index].client_network_details = client_add;
		clientList[*index].clientID = clientCount;
		clientList[*index].clientID = clientCount;
				write(STDOUT_FILENO,"Accepted4\n",strlen("Accepted4\n"));

		clientCount++;
		char buf[100];
		char* clientip;
		char buf2[20];
		int test = sprintf(buf2,"index is %d\n",*index);
		write(STDOUT_FILENO,buf2,test);
		write(STDOUT_FILENO,"Accepted5\n",strlen("Accepted5\n"));

		//strcpy(clientip,inet_ntoa(clientList[*(index)].client_network_details.sin_addr));
		write(STDOUT_FILENO,"Accepted6\n",strlen("Accepted6\n"));
		int ts =sprintf(buf,"Client ip is : %s and its id is %d\n",inet_ntoa(clientList[*(index)].client_network_details.sin_addr),*index);
		write(STDOUT_FILENO,buf,ts);
		pthread_create(&t,NULL,serverWork,(void*) &clientList[*index]);
		pthread_detach(t);

		// pthread_create(&t,NULL,serverWork,p_sock);
		// pthread_detach(t);
		 //pid_t client = fork();
		// if(client<0){
		// perror("Fork Error");
		// 	exit(0);
		// 	}
		// else if(client==0){
		// 	char buf[100];
		// 	char* clientip;
		// 	strcpy(clientip,inet_ntoa(client_add.sin_addr));
		// 	int ts =sprintf(buf,"Client ip is : %s\n",clientip);
		// 	write(STDOUT_FILENO,buf,ts);
		// 	clients[clientCount].client_network_details = *(cL);
		// 	clients[clientCount].connsocket = *e;
		// 	pthread_create(&t,NULL,serverWork,(void*)clients[clientCount]);
		// 	pthread_detach(t);
		// 	free(cL);
		// 	free(e);

		
		// }
		// else{
		// 	clients[clientCount].pID = client;
		// 	clients[clientCount].clientPORT = ntohs(client_add.sin_port);
		// 	clients[clientCount].clientID = clientCount;
		// 	clientCount++;
			
			
		
		  // }
	
	}
	/*
	 * Since this program has an infinite loop, the socket "sock" is
	 * never explicitly closed.  However, all sockets will be closed
	 * automatically when a process is killed or terminates normally. 
	 */
return 0;
}
void* serverWork(void* client){
	client_DAT *t1 = (client_DAT*) client;
	int serverFD = t1->connsocket;
	int index = t1->clientID;
	char client_name[20];
	int o = sprintf(client_name,"my id is %d\n",index);
	write(STDOUT_FILENO,client_name,o);
	bool pr = true;
	while(pr==true){
	
	int e = write(STDOUT_FILENO,"Enter Your Command - kill <name>,list,list-all,run <program-name> \n",strlen("Enter Your Command - kill <name>,list,list-all,run <program-name> \n"));
	if(e<0){
		perror("Write Error");
		//exit(0);
		}
	char clientInput[100];
	
	if ((e=read(serverFD,clientInput,100))<0){
		perror("Error at reading client input");
		exit(0);
	}
	clientInput[e-1]=NULL;
	char* token = strtok(clientInput," ");
	if (token==NULL){
		write(serverFD,"Bad Input\n",strlen("Bad Input\n"));
		//exit(0);
		}
	else{
		
	
		//^exit
	  if(strcmp(token,"kill")==0){
		token = strtok(NULL," ");
        if(token==NULL){
			write(serverFD,"Incomplete paramaters\n",strlen("Incomplete paramaters\n"));
		//	exit(0);
			}
        else{
            int c = atoi(token);
            pid_t killpid = 0;
            if(c==0){
                //its a name
                char killName[20];
                int index;
                int sp56 =  sprintf(killName,"%s",token);
                //find its pid
                for(int i = 0;i<clientList[index].totalProcesses;i++){
                    if(strcmp(killName,clientList[index].pList[i].pName)==0 && clientList[index].pList[i].term!=true){
                        killpid = clientList[index].pList[i].pID;
                        index = i;
                        break;
                    }
                }
                if(killpid==0){
					write(serverFD,"No Process with this name exists \n",strlen("No Process with this name exists \n"));
					}
                else{
                    int kerro =kill(killpid,SIGTERM);
                    if(kerro==0){clientList[index].pList[index].term = true;
                    clientList[index].pList[index].end_time = time(0)-clientList[index].pList[index].start_time;
                    clientList[index].activeProcesses--;
                    int wr111 = write(serverFD,"Process Terminated Successfully \n",strlen("Process Terminated Successfully \n"));
                    	if(wr111==-1){
							perror("Write Failed");
							exit(0);
        					}
                    //error handling}
            			}
					}
				}
            else{
				bool flag = true;
                killpid = c;
                int kerror2 = kill(killpid,SIGTERM);
                if(kerror2==0){
                    
                    for(int i = 0;i<clientList[index].totalProcesses;i++){

                        if(clientList[index].pList[i].pID==killpid&&clientList[index].pList[i].term==false){clientList[index].pList[i].term= true;
                        clientList[index].pList[i].end_time= time(0)-clientList[index].pList[i].start_time;
						flag=false;
						}
                    }
                    
            if(flag==false){
				clientList[index].activeProcesses--;
            	int wr1111 = write(serverFD,"Process Terminated Successfully \n",strlen("Process Terminated Successfully \n"));
              	if(wr1111==-1){
					perror("Write Failed");
				//	exit(0);
        				}
			}
			else {
				write(serverFD,"No Process with this id exists \n",strlen("No Process with this id exists \n"));
			}

                }
                else {write(serverFD,"No Process with this name exists \n",strlen("No Process with this name exists \n"));
						}
            		}
				}
    		}	
		
	

	//----^ KILL

	else if(strcmp(token,"list")==0){
        write(STDOUT_FILENO,"\n",2);
        char processNames[1000]= " ";
        int sum = 0;
        if(clientList[index].activeProcesses<=0)
			write(serverFD,"No Processes currently running\n",strlen("No Processes currently running\n"));
        else{
           for(int i = 0;i<clientList[index].totalProcesses;i++){
                if(clientList[index].pList[i].term==false){
               sum = sum + sprintf(processNames,"%s Process Name is %s, its pid is %d , elapsed time is %ld seconds \n",processNames,clientList[index].pList[i].pName,clientList[index].pList[i].pID,time(0)-clientList[index].pList[i].start_time);}
            }
    	int wr2 = write(serverFD,processNames,sum); 
        if(wr2<0){
			perror("Write Error");
			exit(0);
			}
        }
    }
	//----^ list

	else if(strcmp(token,"listall")==0){
        write(STDOUT_FILENO,"\n",2);
        char processNames[1000]= " ";
        int sum = 0;
        if(clientList[index].totalProcesses<=0){
			write(serverFD,"No Processes currently running\n",strlen("No Processes currently running\n"));
		}
        else{
           for(int i = 0;i<clientList[index].totalProcesses;i++){
                if(clientList[index].pList[i].term==false){
               		sum = sum + sprintf(processNames,"%s Process Name is %s, its pid is %d , elapsed time is %ld seconds \n",processNames,clientList[index].pList[i].pName,clientList[index].pList[i].pID,time(0)-clientList[index].pList[i].start_time);
			   		}
			   else{
			   		sum = sum + sprintf(processNames,"%s Process Name is %s, its pid is %d , end time is %ld seconds \n",processNames,clientList[index].pList[i].pName,clientList[index].pList[i].pID,clientList[index].pList[i].end_time);
					}
		   }
    	int wr2 = write(serverFD,processNames,sum); 
        if(wr2<0){
			perror("Write Error");
			exit(0);
				}
        	}
    	}
	
	//^ list-all
	else if(strcmp(token,"run")==0){
		int pipefd[2];
		int e3 = pipe2(pipefd,O_CLOEXEC);
		if(e3<0)
		{
			perror("Piping Error");
			exit(0);
		}
            token = strtok(NULL," ");
         	if(token==NULL){
			write(serverFD,"Incomplete paramaters\n",strlen("Incomplete paramaters\n"));
		//	exit(0);
			}

            else{

            char programName[100];
            int sSPFE = sprintf(programName,"%s",token);
            char path[150];
             int sSPFE2 = sprintf(path, "/usr/bin/%s",programName);
         
            pid_t e;
             pid_t cProcess2 = fork();
             
             
             if(cProcess2>0){
                 close(pipefd[1]);
                 char test[100];
                 int b = read(pipefd[0],test,100);
				
            // if exec successful
                 if(b==0){
                    sprintf(clientList[index].pList[clientList[index].totalProcesses].pName,"%s",programName);
                    time_t ttime = time(0);
                    char* dt = ctime(&ttime);
                    clientList[index].pList[clientList[index].totalProcesses].start_time = ttime;


                    clientList[index].pList[clientList[index].totalProcesses].start_time_str = dt;
                    clientList[index].pList[clientList[index].totalProcesses].pID = cProcess2;
                    clientList[index].pList[clientList[index].totalProcesses].term=false;
                    
                    //printf("name is %s : ",clientList[index].pList[count].pName);
                    
                  clientList[index].activeProcesses++;
                  clientList[index].totalProcesses++;
                    write(serverFD, "Exec Successful \n", strlen("Exec Successful \n"));
                  
                    }
                }

             else if(cProcess2 == 0){
                close(pipefd[0]);
                e = getpid();
                int exec_status= execl(path,programName,NULL);
                if (exec_status == -1)
                {
                    write(pipefd[1],"random",strlen("random"));
                    write(serverFD, "Exec Failed\n", strlen("Exec Failed\n"));                                    
				}


            }
            else if(cProcess2 <0){
                perror("fork error; ");
				exit(0);
            }
             
        }
    }
	else{
		int i = write(serverFD,"Invalid Operation\n",strlen("Invalid Operation\n"));
		if(i<0){
			perror("write error");
			exit(0);
				}
			}
		}
//^ run
		
	}
	free(client);
}