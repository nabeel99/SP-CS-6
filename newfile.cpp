#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <fcntl.h> 
#include <stdlib.h>
int main(){
int d = open("/home/wuntap/Desktop/SP-CS-6/new2.txt",O_WRONLY|O_CREAT);
if(d==-1){
write(STDOUT_FILENO,"error while opening file",25);exit(EXIT_FAILURE);}

int s =write(d,"abcd",5);
if(s==-1){
write(STDOUT_FILENO,"error while writing to file",25);exit(EXIT_FAILURE);


}

}