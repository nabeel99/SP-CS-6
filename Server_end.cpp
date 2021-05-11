#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>

#define MAXLIMIT 1000
const int size = 1000;
int n=0;

void work(int);
void sighandler(int signo) {
    if (signo == SIGINT) {
        write(STDOUT_FILENO, "\nYou pressed CTRL-C\n", sizeof("\nYou pressed CTRL-C\n"));
    }
    if (signo == SIGCHLD) {
        write(STDOUT_FILENO, "\nTerminated\n", sizeof("\nTerminated\n"));
}
}

//STRUCTURE FOR PROCESS LIST
typedef struct pList{
    char processName[50];
    int process_id;
    time_t startTime;
    time_t endTime;
    bool isActive;
    }p_list;
struct pList proclist[MAXLIMIT];
int plist_index=0;


int main(int argc, char * argv[]){

    int sockfd, newsockfd, portno, clilen, pid;
    struct sockaddr_in serv_addr, cli_addr;

    if(argc <2) {
    write(STDOUT_FILENO,"Provide Port number\n",sizeof("Provide Port number\n"));
    exit(0);
    }
    //call socket api, for tcp ip connection
    sockfd = socket(AF_INET,SOCK_STREAM,0);
        if (sockfd < 0) {
            perror("Error at Socket Api ");
            exit(0);
        }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);

    //populate structure
    serv_addr.sin_family = AF_INET; //tcp/ip connection
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    //bind API to bind address to server
    int bindcheck = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if (bindcheck < 0) {
            perror("Error at Bind Api ");
            exit(0);
        }

    //listen to connections. Method fails if socket fails
    listen(sockfd,5); 
    clilen = sizeof(cli_addr);
    
    signal(SIGUSR1,SIG_IGN);
    signal(SIGCHLD, &sighandler);

    // server code that deals with multiple clients
    while (1) {
        newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr, &clilen);
            if (newsockfd < 0) {
                perror("Error at Accepting Connection ");
                exit(0);
            }
            //fork helps establish multiple connections
            pid = fork();
                if (pid<0){
                    perror("Error at Fork Api ");
                    exit(0);
                }
                if (pid == 0) {
                    close(sockfd);
                    // call main function
                    work(newsockfd);   
                }
                else {
                    close(newsockfd);
                }
    }
    return 0;
    }



//METHOD CONTAINING ALL COMMANDS
void work(int sock){
    char buff[1000];
    char displaybuffer[1000];
    bool program=true;
    
    write(STDOUT_FILENO,"___________________________________________________\n",sizeof("___________________________________________________\n"));
    write(STDOUT_FILENO,"Welcome! [[SP Final Project - Abdul samad]]\nA client has been connected. We await your command!\nEnter 'help' for more info on how to use this.",sizeof("Welcome! [[SP Final Project - abdul samad]]\nA client has been connected. We await your command!\nEnter 'help' for more info on how to use this."));
    char s[2000]; //Declaring array of characters (string)
    write(STDOUT_FILENO,"\n___________________________________________________\n\n",sizeof("\n___________________________________________________\n\n"));

    //LOOPING PROGRAM TILL PERSON ENTERS EXIT
    while(program==true) {
        bzero(buff,1000);
        n = read(sock,buff,1000);

        if (n < 0){
            perror("Error at Reading Data ");
            exit(0);
            }
        write(STDOUT_FILENO,buff,strlen(buff) +1);

        //User will input string to be tokenized and then executed
        char str[n - 1];
        sscanf(buff, "%[^\n]", str);

        //Assigning pointers that will stimulate what to do in console:
        char point[10];
        char num1[10];
        char add[10]="add";
        char sub[10]="sub";
        char mul[10]="mul";
        char div[10]="div";
        char run[10]="run";
        char list[10]="list";
        char help[10]="help";
        //char* kill="kill";

        //Using strtok to divide words/numbers into tokens by the spaces to differentiate between them
        point=strtok(str," ");
        num1=point; //first token is saved in num1



        //ADD
        int sum=0;
        if(strcmp(num1,add)==0){ //compared first token with add, if it is add, then statements will execute
            while (point!=NULL){
                sum=sum+atoi(point); //converting char to int using atoi.
                point=strtok(NULL," ");
            }
            //int nDigits = floor(log10(abs(sum))) + 1; //USE this function to find out number of digits in the sum result
            char a[100]; //array of same size as no. of digits to be stored is created.
            int n=sprintf(a,"%d\n",sum); //sprintf formats output and stores to string
            write(sock,a,n); //prints output
            }



        //SUBTRACT
        int diff=0;
        if(strcmp(num1,sub)==0){
            //if(point!=NULL){
            point=strtok(NULL," ");
            //}
            diff=atoi(point);
            point=strtok(NULL," ");
            while(point!=NULL){
                diff-=atoi(point);
                point=strtok(NULL," ");
                }
            char a[100];
            int n=sprintf(a,"%d\n",diff); //sprintf formats output and stores to string
            int num=write(sock,a,n);
            if (num==-1){
                perror("no output");
                exit(0);
                    }
        }



        //MULTIPLY
        int res=1;
        //point="1";
        if(strcmp(num1,mul)==0){
            point=strtok(NULL," ");
            while(point!=NULL){
            res=res*atoi(point);
            point=strtok(NULL," ");
        }
        char a[100];
        int n=sprintf(a,"%d\n",res); //sprintf formats output and stores to string
        int num=write(sock,a,n);
        }



        //DIVIDE
        point="1";
        if(strcmp(num1,div)==0){
            point = strtok(NULL," ");
            res = atoi(point);

            if(point!=NULL){
                point=strtok(NULL," ");}
            while(point!=NULL){
                res=res/atoi(point);
                point=strtok(NULL," ");
            }
            char a[100];
            int n=sprintf(a,"%d\n",res); //sprintf formats output and stores to string
            int num=write(sock,a,n);
        }



        //RUN function
        char procname[50];
        char buff[1000];
        if(strcmp(num1,run)==0){
            int pipe1[2];
            pipe(pipe1);
            pid_t pid = fork();
            point=strtok(NULL," ");

            char* ptoken=point;//goes to next token, stores it in variable. used to run process
            sprintf(procname,"%s",point);

            if (pid <0) {
                perror("FORK FAILED");
                exit(0);
            // return;
            }
            //child process
            if (pid==0){
                close(pipe1[0]);
                char cpid[12]={0x0};
                
                int j=(int)getpid();
                int n=sprintf(cpid,"%d",j);
                write(pipe1[1],cpid,n);
                //write(sock,"CHILD ID: ",sizeof("CHILD ID: "));
                //write(sock,cpid,sizeof(cpid));
                write(sock,"success\n",sizeof("success\n"));
                int num=execlp(ptoken,ptoken,NULL); //executes program
                if(num==-1){
                    perror("Error at exec: ");
                    exit(0);
                }
            }
            //parent process
            else{
                close(pipe1[1]);
                int c_pid;
                int n = read(pipe1[0],buff,1000);
                if(n<0){
                    perror("Parent read error");
                    exit(0);
                }
                n=sscanf(buff,"%d",&c_pid);
                proclist[plist_index].process_id=c_pid;
                sprintf(proclist[plist_index].processName,"%s",procname);
                proclist[plist_index].isActive=true;
                time(&proclist[plist_index].startTime);
                plist_index++;
            }
        //wait(NULL);
        }
        if(strcmp(num1,list)==0){
            char buffer[1000];
           char buffz[1000];

            int x=0;
            int y=0;
            int total = 0;
            //int n = sprintf(buff,"Number of processes: %d\n",plist_index);
            //write(sock,buff,n);
            x = sprintf(buffer,"\nProcess Name\tProcess ID\tActive Status\tStart Time\tEnd Time\n");
            total = x+y;
            //write(sock,buff,n);
            for(int i=0;i<plist_index;i++){
                char stime[9];
                char etime[9];
                strftime(stime,9,"%X",gmtime(&proclist[i].startTime));
                strftime(etime,9,"%X",gmtime(&proclist[i].endTime));
                if(proclist[plist_index].isActive=true){
                y=sprintf(buffz,"%s\t\t%d\t\t%d\t\t%s\t%s\n",proclist[i].processName,proclist[i].process_id,proclist[i].isActive,stime,etime);
                strcat(buffer,buffz);
                total +=y;
                }
            }
            write(sock,buffer,total);
        }


        //KILL function
        if(strcmp(num1,"kill")==0){
            char buff[1000];
            int n;
            point=strtok(NULL," ");
            int kpid = atoi(point);
            int ret = kill(kpid,SIGKILL);
            if(ret<0){
                if (errno == ESRCH) {
				n = sprintf(buff, "Invalid pid, Kill Unsuccessful\n");
				write(sock, buff, n);
				return;
			} else if (errno == EPERM) {
				n = sprintf(buff, "Not permitted to kill. Kill unsucessful\n");
				write(sock, buff, n);
				return;
			}
            else{
            n = sprintf(buff,"Kill Process Unsuccessful\n");
                write(sock,buff,n);
            }
            }
            for(int i=0; i<plist_index;i++){
                if(proclist[i].process_id == kpid){
                    proclist[i].isActive=false;
                    time(&proclist[plist_index].endTime);
                }
            }
            n=sprintf(buff,"Process %d - Kill Successful\n",kpid);
            write(sock,buff,n);
        }



        //HELP
        //declare string of what needs to be printed to help
        char h[400]="HERE TO ASSIST YOU!\n\nUse 'add','sub','mul',div' before writing string of numbers with space to perform respective function on those numbers.\nFor e.g ''add 5 7 8''\n\n'run gedit '\n\n'list' to view  processes.\n\n'kill (Processid) to kill process.\n\nTo exit the program, write 'terminate' and enter.\n\nHope you like our program! :)";
        if(strcmp(num1,help)==0){
            write(sock,h,sizeof(h));
            }



        //EXIT function
        if(strcmp(num1,"exit")==0){
            n = sprintf(buff, "Client has Exited\n");
            write(sock, buff, n);
            program=false;
            break;
            exit(0); // break;
        }


        
        //NO OPERATION
        if((strcmp(num1,add)!=0)&&(strcmp(num1,sub)!=0)&&(strcmp(num1,mul)!=0)&&(strcmp(num1,div)!=0)&&(strcmp(num1,run)!=0)&&(strcmp(num1,list)!=0)&&(strcmp(num1,help)!=0)&&(strcmp(num1,"kill")!=0)&&(strcmp(num1,"exit")!=0)){
            char buff[1000];
            int n = sprintf(buff,"Incorrect operation");
        }



    } //End of program loop
} //End of main method
