

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
	struct clientList{
		pid_t pID;
		bool term = false;
		char * clientIP;
		int clientPORT;
		int clientID;
	};
    int activeCount = 0;
    int totalCount = 0;
	int clientCount = 0;
    process active[100];
    process terminated[100];
	clientList clients[100];
int main(void)
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
		
		bzero(buf,sizeof(buf));
		pthread_t t;
		int *p_sock = (int*) malloc(sizeof(int));
		*p_sock = msgsock;
		pthread_create(&t,NULL,serverWork,p_sock);
		// pid_t client = fork();
		// if(client>0){
		// 	clients[clientCount].pID = client;
		// 	clients[clientCount].clientPORT = ntohs(client_add.sin_port);
		// 	clients[clientCount].clientID = clientCount;
		// 	clientCount++;
		// 	}
		// else if(client ==0){
		// 	char buf[100];
		// 	char* clientip;
		// 	strcpy(clientip,inet_ntoa(client_add.sin_addr));
		// 	int t =sprintf(buf,"Client ip is : %s\n",clientip);
		// 	write(STDOUT_FILENO,buf,t);
		
		// }
		// else{
		// 	perror("Fork Error");
		// 	exit(0);
			
		
		//    }
//		return 0;
	}
	/*
	 * Since this program has an infinite loop, the socket "sock" is
	 * never explicitly closed.  However, all sockets will be closed
	 * automatically when a process is killed or terminates normally. 
	 */
}
void* serverWork(void* p_serverFD){
	int serverFD = *((int *) p_serverFD);
	free(p_serverFD);
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
		
		if(strcmp(token,"exit")==0){
			// int index = 9999;
			// for(int i = 0;i<clientCount;i++){
			// 	if(clients[i].clientID==clientpid){index = i;
			// 	break;}
			// }
			// if(index!=9999){
			// 	int k = kill(clients[index].pID,SIGKILL);
			// 	if(k<0)perror("KIlling error");

			// }
			// else{
			// 	write(serverFD,"Cannot exit\n",strlen("Cannot exit\n"));
			// 	char b[10];
			// 	int e = sprintf(b,"%d\n",clients[clientCount].pID);
			// 	write(STDOUT_FILENO,b,e);
			// }
			pr=false;
		}
		//^exit
	 else if(strcmp(token,"kill")==0){
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
                for(int i = 0;i<totalCount;i++){
                    if(strcmp(killName,active[i].pName)==0 && active[i].term!=true){
                        killpid = active[i].pID;
                        index = i;
                        break;
                    }
                }
                if(killpid==0){
					write(serverFD,"No Process with this name exists \n",strlen("No Process with this name exists \n"));
					}
                else{
                    int kerro =kill(killpid,SIGTERM);
                    if(kerro==0){active[index].term = true;
                    active[index].end_time = time(0)-active[index].start_time;
                    activeCount--;
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
                    
                    for(int i = 0;i<totalCount;i++){

                        if(active[i].pID==killpid&&active[i].term==false){active[i].term= true;
                        active[i].end_time= time(0)-active[i].start_time;
						flag=false;
						}
                    }
                    
            if(flag==false){
				activeCount--;
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
        if(activeCount<=0)
			write(serverFD,"No Processes currently Active\n",strlen("No Processes currently Active\n"));
        else{
           for(int i = 0;i<totalCount;i++){
                if(active[i].term==false){
               sum = sum + sprintf(processNames,"%s Process Name is %s, its pid is %d , elapsed time is %ld seconds \n",processNames,active[i].pName,active[i].pID,time(0)-active[i].start_time);}
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
        if(totalCount<=0){
			write(serverFD,"No Processes currently Active\n",strlen("No Processes currently Active\n"));
		}
        else{
           for(int i = 0;i<totalCount;i++){
                if(active[i].term==false){
               		sum = sum + sprintf(processNames,"%s Process Name is %s, its pid is %d , elapsed time is %ld seconds \n",processNames,active[i].pName,active[i].pID,time(0)-active[i].start_time);
			   		}
			   else{
			   		sum = sum + sprintf(processNames,"%s Process Name is %s, its pid is %d , end time is %ld seconds \n",processNames,active[i].pName,active[i].pID,active[i].end_time);
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
                    sprintf(active[totalCount].pName,"%s",programName);
                    time_t ttime = time(0);
                    char* dt = ctime(&ttime);
                    active[totalCount].start_time = ttime;


                    active[totalCount].start_time_str = dt;
                    active[totalCount].pID = cProcess2;
                    active[totalCount].term=false;
                    
                    //printf("name is %s : ",active[count].pName);
                    
                  activeCount++;
                  totalCount++;
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
}