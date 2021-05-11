#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    
    int pipefd[2];

    int k = pipe(pipefd);
  
    char r[6];
    int kf;
    int s = fork();
    if(s>0){
   close(pipefd[0]);
   write(pipefd[1],"Test",4);


    }
    else if(s==0){
close(pipefd[1]);
 // sleep(3);
 //   int fd2 = open("/home/wuntap/Desktop/SP-CS-6/readfromprocess.txt",O_RDONLY);
  
int c =  read(pipefd[0],r,4);  
  write(STDOUT_FILENO,r,c);      /* read pipe */
    }



    return 0;
}