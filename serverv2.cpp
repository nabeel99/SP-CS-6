

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
#include <sys/wait.h>
#include <ctype.h>
#define TRUE 1

/*
 * This program creates a socket and then begins an infinite loop. Each time
 * through the loop it accepts a connection and prints out messages from it. 
 * When the connection breaks, or a termination message comes through, the
 * program accepts a new connection. 
 */
int max_Con = 0;
void* serverWork(void *);
void* Interactive_Server(void*);
void termThreadCleaner(void *);

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
		bool status = true;
	};
	client_DAT clientList[100];
    // int clientList[index].activeProcesses = 0;
    // int clientList[index].totalProcesses = 0;
	int clientCount = 0;
    // process clientList[index].pList[100];
    // process terminated[100];
void signalHandler(int signo){
	if(signo==SIGCHLD){
		int status;
		int wNO = waitpid(0,&status,WNOHANG);
		while(wNO>0){
			printf("WNO IS: %d\n",wNO);
			bool found = false;
			for(int i = 0;i<clientCount;i++){
				if(found==true)break;
				printf("WNO in for IS: %d\n",wNO);

				for(int z = 0;z<clientList[i].totalProcesses;z++){
					if(clientList[i].pList[z].pID==wNO&&clientList[i].pList[z].term==false){
						printf("WNO in for if IS: %d\n",wNO);
						printf("wait PID returned is %d, client list pid was %d\n",wNO,clientList[i].pList[z].pID);
						clientList[i].activeProcesses--;
						clientList[i].pList[z].term=true;
						clientList[i].pList[z].end_time = time(0)-clientList[i].pList[z].start_time;
						found = true;
						break;
					}
				}
			}

			
			wNO = wNO = waitpid(0,&status,WNOHANG);
		}
		write(STDOUT_FILENO,"sigchild called\n",strlen("sigchild called\n"));
		

	}
	return ;
}
int main()
{ 
	signal(SIGCHLD,signalHandler);
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
	server.sin_port = ntohs(9003);
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
	 pthread_t interactive;
  int e = pthread_create(&interactive,NULL,Interactive_Server,NULL);
  pthread_detach(interactive);
	/* Start accepting connections */
	listen(sock, 1);
//thread creation

//initialize
//create
//servethread
//thread1

 
	while(true){
		if(max_Con<=25){
		for(int i =0;i<clientCount;i++)
	{
		if(clientList[clientCount].status==false){
	int e =	close(clientList[i].connsocket);
	if(e<0)perror("close error");
		}
	}
		length2 = sizeof(client_add);
		msgsock = accept(sock,(struct sockaddr *)&client_add ,(socklen_t *) &length2);
		char m[20];
		int nf =sprintf(m,"msg sock id is %d\n",msgsock);
		write(STDOUT_FILENO,m,nf);
		if(msgsock<0){
			perror("Accept error");
			break;
		}
		max_Con++;
		if(msgsock<0)
			perror("accept");
		write(STDOUT_FILENO,"Accepted\n",strlen("Accepted\n"));
		bzero(buf,sizeof(buf));
		pthread_t t;
		int *index = (int *) malloc(sizeof(int));
		*index = clientCount;
		clientList[*index].connsocket = msgsock; 
		clientList[*index].client_network_details = client_add;
		clientList[*index].clientID = clientCount;
		clientCount++;
		char buf[100];
		char* clientip;
		char buf2[20];
		int test = sprintf(buf2,"index is %d\n",*index);
		int ts =sprintf(buf,"Client ip is : %s and its id is %d\n",inet_ntoa(clientList[*(index)].client_network_details.sin_addr),*index);
		write(STDOUT_FILENO,buf,ts);
		pthread_create(&t,NULL,serverWork,(void*) &clientList[*index]);
		pthread_detach(t);
		free(index);	
		}
		else{
			msgsock = accept(sock,(struct sockaddr *)&client_add ,(socklen_t *) &length2);
			write(msgsock,"Max Clients reached, try connecting another time.\n",strlen("Max Clients reached, try connecting another time.\n"));
			close(msgsock);
		}	
	}
	max_Con-=1;
	close(sock);
	//pthread_kill(interactive,SIGKILL);
	/*
	 * Since this program has an infinite loop, the socket "sock" is
	 * never explicitly closed.  However, all sockets will be closed
	 * automatically when a process is killed or terminates normally. 
	 */
return 0;
}
void* Interactive_Server(void* arg){
	char buff[1000];
	while(true){
	write(STDOUT_FILENO,"Command so far-Broadcast <msg>,conn_list\n",strlen("Command so far-Broadcast <msg>,conn_list\n"));
	char connections[100];
	int con_count = sprintf(connections,"Number of connections : %d\n",max_Con);
	write(STDOUT_FILENO,connections,con_count);
	int e = read(STDIN_FILENO,buff,1000);
	buff[e-1] = '\0';
	char* token;
	token = strtok(buff," ");
	if (token==NULL){
		write(STDOUT_FILENO,"Bad Input\n",strlen("Bad Input\n"));
		//exit(0);
		}
		else{
			// 3 commands broadcast,display all connections
			if(strcmp(token,"broadcast")==0){
		token = strtok(NULL," ");
        if(token==NULL){
			write(STDOUT_FILENO,"Incomplete paramaters\n",strlen("Incomplete paramaters\n"));
		//	exit(0);
			}
			else{
				int sum;
				char buffer4[1200];
				char broadCastMsg[1000];
				char client_msg[500];
				bzero(buffer4,sizeof(buffer4));
				bzero(broadCastMsg,sizeof(broadCastMsg));
				bzero(client_msg,sizeof(client_msg));
				sum = sprintf(broadCastMsg,"%s",token);
				token = strtok(NULL," ");
				while(token!=NULL){
					sum = sprintf(broadCastMsg,"%s %s",broadCastMsg,token);
					token = strtok(NULL," ");
				}
			int rtl =sprintf(buffer4,"Master Server Emergency Message : %s",broadCastMsg);
			for(int i = 0;i<clientCount;i++){
				if(clientList[i].status==true){
				int ttlmsg = sprintf(client_msg,"Sending to Client with ip : %s, the following message : %s, it is of length : %d\n",inet_ntoa(clientList[i].client_network_details.sin_addr),buffer4,(int)strlen(buffer4));
				write(STDOUT_FILENO,client_msg,ttlmsg);
				int v = write(clientList[i].connsocket,buffer4,rtl);
				if(v<=0)perror("write error in broadcast");
			}
				}
			}
		}
		else if(strcmp(token,"conn_list")==0){
        write(STDOUT_FILENO,"\n",2);
        char client_info_active[1000];
		char client_info_closed[1000];
		bzero(client_info_active,sizeof(client_info_active));
		bzero(client_info_closed,sizeof(client_info_closed));
		for(int i = 0;i<clientCount;i++){
				if(clientList[i].status==true){
				int t = sprintf(client_info_active,"Client#%d IP address is : %s and its status: Active\n",clientList[i].clientID,inet_ntoa(clientList[i].client_network_details.sin_addr));
				int v = write(STDOUT_FILENO,client_info_active,t);
				if(v<=0)perror("write error in broadcast");
			}
			else{
				int t = sprintf(client_info_closed,"Client#%d IP address is : %s and its status: Closed\n",clientList[i].clientID,inet_ntoa(clientList[i].client_network_details.sin_addr));
				int v = write(STDOUT_FILENO,client_info_closed,t);
				if(v<=0)perror("write error in broadcast");
			}
				}	
		
		
	}

		else{
			write(STDOUT_FILENO,"Invalid Operation\n",strlen("Invalid Operation\n"));
		}

		}
	}
	
}
void termThreadCleaner(void* thread_Client){
	
	write(STDOUT_FILENO,"In clean up function\n",strlen("In clean up function\n"));
	int *p = (int *)thread_Client;
	int clientidd = *p;
	char buf[100];
	int o = close(clientList[clientidd].connsocket);	
	if(o<0){perror("closing error");}
	int n =sprintf(buf,"Client#%d had %d total Processes\n",clientidd,clientList[clientidd].totalProcesses);
	write(STDOUT_FILENO,buf,n);
	//so server knows connection has ended
	clientList[clientidd].status = false;
	//decrease connections
	max_Con = max_Con-1;
	for(int i = 0;i<clientList[clientidd].totalProcesses;i++){
		if(clientList[clientidd].pList[i].term==false){

		write(STDOUT_FILENO,"in loopcleanif\n",strlen("in loopcleanif\n"));
			// kill all processes after the thread unexpectedly terminates
			int error =kill(clientList[clientidd].pList[i].pID,SIGTERM);
			clientList[clientidd].activeProcesses--;
			clientList[clientidd].pList[i].term=true;
			if(error<0)perror("error while cleaning process of thread term cleanup");
		}

	}
	//close msgsock
	
}
int inputSanitier(char* arg){
	bool integer = true;
	for(int i = 0;i<strlen(arg);i++)
					{
						int er =isdigit(arg[i]);
						if(er<=0&& arg[i]!='-')
						{	
							integer = false;
							break;						
						}
	}
	if(integer==true)return 5;
	else return -1;
}
void* serverWork(void* client){
	
	client_DAT *t1 = (client_DAT*) client;
	printf("msgsock id is %d",t1->connsocket);
	
	pthread_cleanup_push(&termThreadCleaner,(void*)&(t1->clientID));
	int serverFD = t1->connsocket;
	int index = t1->clientID;
	char client_name[20];
	int test = 0;
	int o = sprintf(client_name,"my id is %d\n",index);
	int wre =write(STDOUT_FILENO,client_name,o);
	if(wre<0)perror("writing to terminal error");
	bool pr = true;
	//thread2?
	//client handler sai baat cheet kar ra hoga while loop
	while(pr==true){
	
	
	int e = write(serverFD,"Enter Your Command - kill <name>,list,list-all,run <program-name>,exit \n",strlen("Enter Your Command - kill <name>,list,list-all,run <program-name>,exit \n"));
	char client_process[200];
	 int total = sprintf(client_process,"Client#%d, Total process is %d and active processes is %d\n",index,clientList[index].totalProcesses,clientList[index].activeProcesses);
	 if(total<=0)perror("sprintf error");
	write(STDOUT_FILENO,client_process,total);
	if(e<0){
		perror("Write Error");
		//exit(0);
		}
	char clientInput[100];
	
	if ((e=read(serverFD,clientInput,100))<=0){
		perror("Error at reading client input");
		break;
	}
	clientInput[e-1]='\0';
	char* token = strtok(clientInput," ");
	if (token==NULL){
		write(serverFD,"Bad Input\n",strlen("Bad Input\n"));
		//exit(0);
		}
	else{
		if(strcmp(token,"add")==0){
			token = strtok(NULL," ");
			char buf[500];
			int sum =0;
			int totalsum = 0;
			bzero(buf,sizeof(buf));
			int bInputFlag =0;
			if(token==NULL){

				write(serverFD,"Incomplete paramaters\n",strlen("Incomplete paramaters\n"));
	
			}
			else
			{
				while(token!=NULL&& bInputFlag!=-1)
				{
					int alpha = inputSanitier(token);
					
					if(alpha==-1)
						{
							bInputFlag = -1;
							break;
						}
					
					//input is fine
					sscanf(token,"%d",&sum);
					totalsum = totalsum+ sum;
					token = strtok(NULL," ");
				}
				if(bInputFlag!=-1)
				{
					int sF = sprintf(buf,"Addition result : %d\n",totalsum);
					int e = write(serverFD,buf,sF);
					if(e<0){
						perror("Write error of addition result");
				}
			}
			else
			write(serverFD,"Bad Input, Input contains non-digits\n",strlen("Bad Input, Input contains non-digits\n"));


			}
	

		}
		
		
	
		//^add
		else if(strcmp(token,"sub")==0){
			token = strtok(NULL," ");
			char buf[500];
			int start =0,other=0;
			int totalsum = 0;
			bzero(buf,sizeof(buf));
			int bInputFlag =0;
			if(token==NULL){
			write(serverFD,"Incomplete paramaters\n",strlen("Incomplete paramaters\n"));
		//	exit(0);
			}
			else
			{	
				int alpha2 = inputSanitier(token);
				if(alpha2<=0)
						{
							bInputFlag = -1;
							
						}
				sscanf(token,"%d",&start);
				token = strtok(NULL," ");
				while(token!=NULL&& bInputFlag!=-1)
				{
					int alpha = inputSanitier(token);
					if(alpha<=0)
						{
							bInputFlag = -1;
							break;
														
						}

					//input is fine
					
					sscanf(token,"%d",&other);
					start = start-other;
					token = strtok(NULL," ");
					
				}
				totalsum = start;
				if(bInputFlag!=-1)
				{
					int sF = sprintf(buf,"Subtraction result : %d\n",totalsum);
					int e = write(serverFD,buf,sF);
					if(e<0){
						perror("Write error of subtraction result");
				}
			}
			else
			write(serverFD,"Bad Input, Input contains non-digits\n",strlen("Bad Input, Input contains non-digits\n"));


			}
	

		}
		//subtract
		else if(strcmp(token,"div")==0){
			token = strtok(NULL," ");
			char buf[500];
			int start,other;
			int divByZero=0;
			int totalsum = 0;
			bzero(buf,sizeof(buf));
			int bInputFlag =0;
			if(token==NULL){
			write(serverFD,"Incomplete paramaters\n",strlen("Incomplete paramaters\n"));
		//	exit(0);
			}
			else
			{	
				int alpha2 = inputSanitier(token);
				if(alpha2<=0)
						{
							bInputFlag = -1;
					
							
						}
				sscanf(token,"%d",&start);
				token = strtok(NULL," ");
				while(token!=NULL&& bInputFlag!=-1&&divByZero!=-1)
				{
					int alpha = inputSanitier(token);
					if(alpha<=0)
						{
							bInputFlag = -1;
							break;
							
						}

					//input is fine
					
					sscanf(token,"%d",&other);
					if(other==0)
					{
						divByZero = -1;
						break;
					}
					start = start/other;
					token = strtok(NULL," ");
					
				}
				
				if(bInputFlag!=-1&&divByZero==0)
				{
					totalsum = start;
					int sF = sprintf(buf,"Division Result result : %d\n",totalsum);
					int e = write(serverFD,buf,sF);
					if(e<0){
						perror("Write error of division result");
					}
				}
				else if(divByZero==-1)
				{
					int error =write(serverFD,"Divide by zero error, you cant divide a number by zero\n",strlen("Divide by zero error, you cant divide a number by zero\n"));
					if(error<0)
					{
						perror("Write error");
					}
				}
				else
				{
				int error =write(serverFD,"Bad Input, Input contains non-digits\n",strlen("Bad Input, Input contains non-digits\n"));
					if(error<0){
						perror("Socket Write error");
					}
				}
			

			}
	

		}
//divide
		else if(strcmp(token,"mul")==0){
		//	sleep(100);
			token = strtok(NULL," ");
			char buf[500];
			int sum;
			int totalsum = 1;
			bzero(buf,sizeof(buf));
			int bInputFlag =0;
			if(token==NULL){

				write(serverFD,"Incomplete paramaters\n",strlen("Incomplete paramaters\n"));
	
			}
			else
			{
				while(token!=NULL&& bInputFlag!=-1)
				{
					int alpha = inputSanitier(token);
					
					if(alpha==-1)
						{
							bInputFlag = -1;
							break;
						}
					
					//input is fine
					sscanf(token,"%d",&sum);
					totalsum = totalsum* sum;
					token = strtok(NULL," ");
				}
				if(bInputFlag!=-1)
				{
					int sF = sprintf(buf,"Multiplication result : %d\n",totalsum);
					int e = write(serverFD,buf,sF);
					if(e<0){
						perror("Write error of Multiplication result");
				}
			}
			else
			write(serverFD,"Bad Input, Input contains non-digits\n",strlen("Bad Input, Input contains non-digits\n"));


			}
	

		}

			  else if(strcmp(token,"kill")==0){
		  write(STDOUT_FILENO,"Here in kill\n",strlen("Here in kill\n"));
		token = strtok(NULL," ");
        if(token==NULL){
			write(serverFD,"Incomplete paramaters\n",strlen("Incomplete paramaters\n"));
		//	exit(0);
			}
        else{
            int c = atoi(token);
            pid_t killpid = 0;
            if(c==0){
				write(STDOUT_FILENO,"Here in killitsname\n",strlen("Here in killitsname\n"));
                //its a name
                char killName[20];
                int indexofProcess;
                int sp56 =  sprintf(killName,"%s",token);
                //find its pid
                for(int i = 0;i<clientList[index].totalProcesses;i++){
					write(STDOUT_FILENO,"Here in killfor\n",strlen("Here in killfor\n"));
                    if(strcmp(killName,clientList[index].pList[i].pName)==0 && clientList[index].pList[i].term!=true){
                        killpid = clientList[index].pList[i].pID;
						write(STDOUT_FILENO,"Here in killloop\n",strlen("Here in killloop\n"));
                        indexofProcess = i;
                        break;
                    }
                }
                if(killpid==0){
					write(serverFD,"No Process with this name exists \n",strlen("No Process with this name exists \n"));
					}
                else{
                    int kerro =kill(killpid,SIGTERM);
                    if(kerro==0){
					clientList[index].pList[indexofProcess].term = true;
                    clientList[index].pList[indexofProcess].end_time = time(0)-clientList[index].pList[indexofProcess].start_time;
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
        char processNames[1000];
		bzero(processNames,sizeof(processNames));
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
        char processNames[1000];
		bzero(processNames,sizeof(processNames));
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
				 char ei[20];
				int ne = sprintf(ei,"number of bytes read is %d",b);
				 write(STDOUT_FILENO,ei,ne);
				
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
                 int d =   write(serverFD, "Exec Successful \n", strlen("Exec Successful \n"));
					if(d<0){perror("write error");}
					

                    }
					else{
					int erro = write(serverFD, "Exec Failed\n", strlen("Exec Failed\n"));
					
					}
					

                }

             else if(cProcess2 == 0){
                close(pipefd[0]);
                e = getpid();
                int exec_status= execl(path,programName,NULL);
                if (exec_status == -1)
                {
						write(pipefd[1],"random",strlen("random"));

						exit(0);
				                                    
				}


            }
            else if(cProcess2 <0){
                perror("fork error; ");
				exit(0);
            }
             
        }

    }
	else if(strcmp(token,"exit")==0){
		write(serverFD,"Server has killed the connection\n",strlen("Server has killed the connection\n"));
	 		
	char client_close[200];
		int close_c = sprintf(client_close,"Closing Connection with client id#%d with ip %s\n",index,inet_ntoa(clientList[index].client_network_details.sin_addr));
		write(STDOUT_FILENO,client_close,close_c);
		//breaking loop so pthread_exit is called and the resulting cleanup handler is called
		break;
	// 	//closing client msgsock
	// 	int e = close(clientList[index].connsocket);
	// 	//closing client processes still running
	// 	for(int i = 0;i<clientList[index].totalProcesses;i++){
	// 		if(clientList[index].pList[i].term==false){

	// 			// kill all processes after the thread unexpectedly terminates
	// 			int error =kill(clientList[index].pList[i].pID,SIGTERM);
	// 			if(error<0)perror("error while cleaning process of thread term cleanup");
	// 			clientList[index].activeProcesses--;
	// 			clientList[index].pList[i].term=true;
	// 		}

	// }
	// 	if (e<0)perror("server cant close socket");
	// 	else{
	//     clientList[index].status= false;
	// 	pr=false;}

	}
		//^ exit
	else{
		int i = write(serverFD,"Invalid Operation\n",strlen("Invalid Operation\n"));
		if(i<0){
			perror("write error");
			break;
				}
			}
		
		}

		
	}
	pthread_exit(NULL);
	pthread_cleanup_pop(0);
	write(STDOUT_FILENO,"here5\n",strlen("here5\n"));

	
	 //free(client);
	 
}