#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <fcntl.h> 
#include <stdlib.h>
int main(){
char readfromfile[100];

char a = 'y';
int fwrite = open("/home/wuntap/Desktop/SP-CS-6/start",O_WRONLY);

if(fwrite==-1){
write(STDOUT_FILENO,"error while opening file",25);exit(EXIT_FAILURE);}

write(fwrite,&a,7);

close(fwrite);

}