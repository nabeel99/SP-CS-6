#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    int fd1 = open("/home/wuntap/Desktop/SP-CS-6/testclass.txt",O_CREAT|O_WRONLY,S_IRWXU);
  
    char r[6];
    int k;
    int s = fork();
    if(s>0){
      //  k =write(fd1,"parent",6);
      k = read(STDIN_FILENO,r,6);
      write(STDOUT_FILENO,r,k);


    }
    else if(s==0){

    int fd2 = open("/home/wuntap/Desktop/SP-CS-6/testclass.txt",O_RDONLY);
 // int d  =read(fd2,r,k);
    write(STDOUT_FILENO,"usman",5);
    }



    return 0;
}