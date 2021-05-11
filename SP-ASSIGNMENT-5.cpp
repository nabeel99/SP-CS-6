#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <ctime>
#include <stdlib.h>
#include <time.h>
using namespace std;
static void siginthandler(int signo){
    int status;

    if (signo==SIGCHLD){

       //     int e = waitpid(-1,&status,WNOHANG);
            
            
            write(STDOUT_FILENO,"Hellofromsighandler\n",strlen("Hellofromsighandler\n"));
            


        }
    }


int main(){
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
    int activeCount = 0;
    int totalCount = 0;
    process active[100];
    process terminated[100];
    int pipefd[2];
    int pipe2fd[2];
    int pipe3fd[2];
    int e = pipe(pipefd);
    int e2 = pipe(pipe2fd);
    int ef=1;
    pid_t cProcess = fork();
    while(true){
    
    if(cProcess==0){
            signal(SIGCHLD,siginthandler);

        close(pipefd[1]);

        write(STDOUT_FILENO,"\n",2);
        

        if(ef==1){
        int wSE = write(STDOUT_FILENO,"Enter Your Command - kill <name>,list,listall,run <program-name> \n",strlen("Enter Your Command - kill <name>,list,listall,run <program-name> \n"));
        }
        ef=0;
        char clientInput[100];
        int rSE = read(pipefd[0],clientInput,100);
        clientInput[rSE-1]=NULL;
        if(rSE-1<=0){write(pipe2fd[1],"Bad Input\n",strlen("Bad Input\n"));}
        else{

        char* token = strtok(clientInput," ");
      //  write(STDOUT_FILENO,"Hellofromserver\n",strlen("Hellofromserver\n"));
        if(token==NULL){write(pipe2fd[1],"Invalid Command\n",strlen("Invalid Command\n"));}
        else{
        
     
        if(strcmp(token,"kill")==0){
        //    write(STDOUT_FILENO,"Hellofromserverinkill\n",strlen("Hellofromserverinkill\n"));
            close(pipe2fd[0]);
            //printf("%s",token);
            token = strtok(NULL," ");
            if(token==NULL){
                int wr11 = write(pipe2fd[1],"Incomplete parameters \n",strlen("Incomplete parameters \n"));
                if(wr11==-1){
           // write(pipe2fd[1],"Error",6);
        }
            
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
                if(killpid==0){write(pipe2fd[1],"No Process with this name exists \n",strlen("No Process with this name exists \n"));}
                else{
                    int kerro =kill(killpid,SIGTERM);
                    if(kerro==0){active[index].term = true;
                    active[index].end_time = time(0)-active[index].start_time;
                    activeCount--;
                    int wr111 = write(pipe2fd[1],"Process Terminated Successfully \n",strlen("Process Terminated Successfully \n"));
                      if(wr111==-1){
           // write(pipe2fd[1],"Error",6);
        }
                    }
                    //error handling

                }
            }
            else{
                killpid = c;
                int kerror2 = kill(killpid,SIGTERM);
                if(kerror2==0){
                    
                    for(int i = 0;i<totalCount;i++){

                        if(active[i].pID==killpid){active[i].term= true;
                        active[i].end_time= time(0)-active[i].start_time;}
                    }
                    activeCount--;
                
            int wr1111 =     write(pipe2fd[1],"Process Terminated Successfully \n",strlen("Process Terminated Successfully \n"));
              if(wr1111==-1){
            //write(pipe2fd[1],"Error",6);
        }
                }
                else {write(pipe2fd[1],"No Process with this name exists \n",strlen("No Process with this name exists \n"));}
            }}
            // kill code

        }
           else if(strcmp(token,"list")==0){
                   write(STDOUT_FILENO,"Hellofromserverinlist\n",strlen("Hellofromserverinlist\n"));
            


               close(pipe2fd[0]);
          write(STDOUT_FILENO,"\n",2);
   
            char processNames[1000]= " ";
            int sum = 0;
            if(activeCount<=0){write(pipe2fd[1],"No Processes currently Active\n",strlen("No Processes currently Active\n"));}
            else{
           for(int i = 0;i<totalCount;i++){
                if(active[i].term==false){
               sum = sum + sprintf(processNames,"%s Process Name is %s, its pid is %d , elapsed time is %ld seconds \n",processNames,active[i].pName,active[i].pID,time(0)-active[i].start_time);}
            }
    int wr2 = write(pipe2fd[1],processNames,sum);
         
             if(wr2==-1){
            //write(pipe2fd[1],"Error",6);
        }


            // kill code
            }
        }
 else if(strcmp(token,"listall")==0){
   //  write(STDOUT_FILENO,"Hellofromserverinlistall\n",strlen("Hellofromserverinlistall\n"));
               close(pipe2fd[0]);
          //  printf("here %s",token);
          write(STDOUT_FILENO,"\n",2);
        //  write(STDOUT_FILENO,iop,l);
            char processNames[1000]= " ";
            int sum = 0;
                 if(totalCount<=0){write(pipe2fd[1],"No Processes currently Active\n",strlen("No Processes currently Active\n"));}
            else{
           
           for(int i = 0;i<totalCount;i++){
                if(active[i].term==false){
               sum = sum + sprintf(processNames,"%s Process Name is %s, its pid is %d , elapsed time is %ld seconds \n",processNames,active[i].pName,active[i].pID,time(0)-active[i].start_time);}
            
            else{
          sum = sum + sprintf(processNames,"%s Process Name is %s, its pid is %d , end time is %ld seconds \n",processNames,active[i].pName,active[i].pID,active[i].end_time);}}
            write(pipe2fd[1],processNames,sum);


            // kill code
            }
        }


//run code

        else if(strcmp(token,"run")==0){
            write(STDOUT_FILENO,"Hellofromserverinrun\n",strlen("Hellofromserverinrun\n"));
            close(pipe2fd[0]);
          //  printf("%s ",token);
            //run code
            token = strtok(NULL," ");
         if(token==NULL){
                write(pipe2fd[1],"Incomplete parameters \n",strlen("Incomplete parameters \n"));
            }

            else{

            char programName[100];
            int sSPFE = sprintf(programName,"%s",token);
            char path[150];
             int sSPFE2 = sprintf(path, "/usr/bin/%s",programName);
                 int e3 = pipe2(pipe3fd,O_CLOEXEC);
            pid_t e;
             pid_t cProcess2 = fork();
             
             
             if(cProcess2>0){
                 close(pipe3fd[1]);
                 char test[100];
                 int b = read(pipe3fd[0],test,100);
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
                    write(pipe2fd[1], "Exec Successful \n", strlen("Exec Successful \n"));
                  
                    }
                  

                }
                 


             else if(cProcess2 == 0){
                close(pipe3fd[0]);
              e = getpid();
                
                int exec_status= execl(path,programName,NULL);
                if (exec_status == -1)
                {
                    write(pipe3fd[1],"random",strlen("random"));
                    char error_buffer[4] = {0};
                    int error = errno;
                    sprintf(error_buffer, "%d", error);
                    
                    write(pipe2fd[1], "Exec Failed\n", strlen("Exec Failed\n"));
                    
                   

                                         
}


            }
            else if(cProcess2 <0){
                perror("fork error; ");
            }
             
        }
    }
       

else{
    write(pipe2fd[1],"Invalid Operation\n",strlen("Invalid Operation\n"));

}
        }
        }
    }

    //parent | client, gives command run/kill


     else if(cProcess>0){
        close(pipefd[0]);
        char userInput[100];
        int re = read(STDIN_FILENO,userInput,100);
        char bytread[100];
        int i = sprintf(bytread,"Bytes read is %d\n",re);
                         //   write(STDOUT_FILENO,"Hellofromclient\n",strlen("Hellofromclient\n"));

write(STDOUT_FILENO,bytread,i);
        int we = write(pipefd[1],userInput,re);
        char serverOutput[1000];
        close(pipe2fd[1]);
        
        
        int bytes_read = read(pipe2fd[0],serverOutput,1000);
               //             write(STDOUT_FILENO,"backromserver\n",strlen("backfromserver\n"));

        if(bytes_read==-1){
            write(STDOUT_FILENO,"Error",6);
        }
                // char buffer[4] = {0};
        // int bytes_read = read(pipe2fd[0], buffer, sizeof(int));
        
       int byt =  write(STDOUT_FILENO,serverOutput,bytes_read);
       write(STDOUT_FILENO,"Enter Your Command - kill <name>,list,listall,run <program-name> \n",strlen("Enter Your Command - kill <name>,list,listall,run <program-name> \n"));
            if(byt==-1){
            write(STDOUT_FILENO,"Error",6);
        }

        
        //     int error = atoi(buffer);
        //     errno = error;
        //     perror("Process Status ");
        



    }
    // child/server
 
    // error if fork fails
    if(cProcess<0){
          
            write(pipe2fd[1],"fork error",11);
        
    }




        
    }
}

