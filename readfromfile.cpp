#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <fcntl.h> 
int main(){
char readfromfile[100];

int fread = open("/home/wuntap/Desktop/SP-CS-6/start",O_RDONLY);
int n1 = read(fread,readfromfile,50);

while (n1!=0){


write(STDOUT_FILENO,readfromfile,n1);
//lseek(fread,50,SEEK_CUR);
n1 = read(fread,readfromfile,50);
}
close(fread);

}