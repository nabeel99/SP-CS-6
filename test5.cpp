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
            write(STDOUT_FILENO,"Write your command : ",22);
            int inputSize = read(STDIN_FILENO,input,100);
            int serverInputSize = write(pipefd[1],input,inputSize);
            int secondRead = read(pipe2fd[0],serverOutput,100);
            char ex[secondRead];
            int send =sprintf(ex,"%s",serverOutput);
            write(STDOUT_FILENO,ex,send);
            if(strcmp(ex,"exit")==0){
               write(STDOUT_FILENO,"in exit2",9);;
                exit(0);}
            write(STDOUT_FILENO,serverOutput,secondRead);
         }
            
        else if(i==0){
           
            
            char childInput[100];
            int rpError = read(pipefd[0],childInput,100);
          
            char *token = strtok(childInput," ");
            char command[8];
            int n;
            float nfloat;
            int spError = sprintf(command,"%s",token);
            if(strcmp(command,"exit")==0){
                write(STDOUT_FILENO,"in exit",8);
                write(pipe2fd[1],"exit",4);
                exit(0);


            }
           else if(strcmp(command,"add")==0){
                int sum = 0;
                while(token!=NULL){

                if(strcmp(token,"add")!=0){
                    int scError = sscanf(token,"%d",&n);
                write(STDOUT_FILENO,token,2);
                sum = sum+n;

                }
                
                token = strtok(NULL," ");
                
                }
                char *output;
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
                    char *output;
                int sPPError = sprintf(output,"The result is : %d",sum);
            
                write(pipe2fd[1],output,sPPError);
           
                        
            }        

            else if(strcmp(command,"div")==0){
                float  sum;
                token = strtok(NULL," ");
                sscanf(token,"%f",&sum);
                token=strtok(NULL," ");
                while(token!=NULL){

                if(strcmp(token,"div")!=0){
                    int scError = sscanf(token,"%f",&nfloat);
                write(STDOUT_FILENO,token,2);
                sum = sum/nfloat;

                }
                
                token = strtok(NULL," ");
                
                
                }
                char *output;
                int sPPError = sprintf(output,"The result is : %.4f",sum);
                
                 write(pipe2fd[1],output,sPPError);

                        
            }

            else if(strcmp(command,"mult")==0){
                int sum = 1;
                while(token!=NULL){

                   if(strcmp(token,"mult")!=0){
                    int scError = sscanf(token,"%d",&n);
                write(STDOUT_FILENO,token,2);
                sum = sum*n;

                }
                
                token = strtok(NULL," ");}
                    //send output to child
                    char *output;
                    int sPPError = sprintf(output,"The result is : %d ",sum);
                    write(pipe2fd[1],output,sPPError);
            }
            else if(strcmp(command,"run")==0){
               
                
                int num;
                char program[10];
                while (token!=NULL){
                    if(strcmp(token,"run")!=0){
                        num = sprintf(program,"%s",token);

                    }
                    token = strtok(NULL," ");
                }
                write(STDOUT_FILENO,program,10);
                 int execerror =execlp(program,program,NULL);
                 if(execerror==-1){

                     write(STDOUT_FILENO,"Exec error",10);
                 }
            }
           
            else{write(STDOUT_FILENO,"Invalid Command",strlen("Invalid Command"));
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