#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
int main(){


    int pipefd[2];
    int pipe2fd[2];
    int e = pipe(pipefd);
    int u = pipe(pipe2fd);
    //error checking for pipe
    char delim[] = " ";


    /// fork here


    ///error checking for fork
    pid_t i = fork();
    while(true){
    

     
        //client process
        if (i>0){
      
            char input[100];
            char serverOutput[100];
            write(STDOUT_FILENO,"\n",2);
            write(STDOUT_FILENO,"Write your command : ",strlen("Write your command : "));
            int inputSize = read(STDIN_FILENO,input,100);
            int serverInputSize = write(pipefd[1],input,inputSize);
            int secondRead = read(pipe2fd[0],serverOutput,100);
            
            if(strcmp(serverOutput,"exit")==0){
              // write(STDOUT_FILENO,"in exit2",9);;
                exit(0);}
            write(STDOUT_FILENO,serverOutput,secondRead);
         }
            
        else if(i==0){
           
            
            char childInput[100];
            int rpError = read(pipefd[0],childInput,100);
            childInput[rpError-1] = NULL;
          
            char *token = strtok(childInput," ");
            char command[8];
            int n;
            float nfloat;
            int spError = sprintf(command,"%s",token);
            if(strcmp(command,"exit")==0){
            //    write(STDOUT_FILENO,"in exit",8);
                write(pipe2fd[1],"exit",5);
                exit(0);


            }
           else if(strcmp(command,"add")==0){
                int sum = 0;
                while(token!=NULL){

                if(strcmp(token,"add")!=0){
                    int scError = sscanf(token,"%d",&n);
              //  write(STDOUT_FILENO,token,2);
                sum = sum+n;

                }
                
                token = strtok(NULL," ");
                
                }
                char output[100];
                int sPPError = sprintf(output,"The result is : %d",sum);
                write(pipe2fd[1],output,sPPError);
              
                
             }
             
            else if(strcmp(command,"sub")==0){
                int sum;
                token = strtok(NULL," ");
                sscanf(token,"%d",&sum);
                token=strtok(NULL," ");
                


                while(token!=NULL){

                  if(strcmp(token,"sub")!=0){
                    int scError = sscanf(token,"%d",&n);
                //write(STDOUT_FILENO,token,2);

                sum = sum-n;
                

                }

                
                token = strtok(NULL," ");
                    }
                    char output[100];
                int sPPError = sprintf(output,"The result is : %d",sum);
            
                write(pipe2fd[1],output,sPPError);
           
                        
            }        

            else if(strcmp(command,"div")==0){
                int  sum;
                int divzeroflag = 0;
                token = strtok(NULL," ");
                sscanf(token,"%d",&sum);
                token=strtok(NULL," ");
                while(token!=NULL){

                if(strcmp(token,"div")!=0){
                    int scError = sscanf(token,"%d",&n);
                    if(n==0){
                                        divzeroflag = 1;
                                        break;
                    }
              //  write(STDOUT_FILENO,token,2);
                    else{
                sum = sum/n;}

                }
                
                token = strtok(NULL," ");
                
                
                }
                char output[100];
                
                if(divzeroflag==1){
                     int sPPError = sprintf(output,"Bad input, div by zero error, enter input again");
                
                 write(pipe2fd[1],output,sPPError);}
                 else{
               
                  int sPPError = sprintf(output,"The result is : %d",sum);
                
                 write(pipe2fd[1],output,sPPError);}
                 

                        
            }

           else if(strcmp(command,"mul")==0){
                int sum = 1;
                while(token!=NULL){

                if(strcmp(token,"mul")!=0){
                    int scError = sscanf(token,"%d",&n);
                //write(STDOUT_FILENO,token,2);
                sum = sum*n;

                }
                
                token = strtok(NULL," ");
                
                }
                char output[100];
                int sPPError = sprintf(output,"The result is : %d",sum);
                write(pipe2fd[1],output,sPPError);
              
                
             }
                       else if(strcmp(token,"run") == 0){
            token = strtok(NULL," ");
            char path[300];
            sprintf(path,"/usr/bin/%s",token);
            int ppid = fork();
            if(ppid>0){
                char lev[300];
                int li = sprintf(lev,"Process Running");
                write(pipe2fd[1],lev,li);

            }
            else if(ppid == 0){
                int start = execl(path,NULL);
                if(start == -1){
                    write(STDOUT_FILENO,"\n",2);
                    perror("exec error ");
                }
            }
            else if(ppid == -1){
                perror("fork error; ");
            }

        }           
            else{write(STDOUT_FILENO,"Invalid Command",strlen("Invalid Command"));
            write(STDOUT_FILENO,"\n",2);
             write(pipe2fd[1],"exit",5);
                exit(0);
             //write(STDOUT_FILENO,command,spError);
             

}       
        }
        else{
            write(STDOUT_FILENO,"IN FINAL EXIT",15);
            exit(EXIT_FAILURE);
        }




        
        






    




    }

    return 0;
}