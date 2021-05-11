#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <stdio.h>
char 
int main(){
    int f1 = open("/home/wuntap/Desktop/SP-CS-6/lseek8.txt",O_CREAT|O_WRONLY|O_APPEND,S_IRWXU);
   read(f1,d,1);
  int fp =   lseek(f1,1,SEEK_CUR);
//write(f1,"ab",2);
char d[5];
int n =sprintf(d,"%d",fp);
write(STDOUT_FILENO,d,n);


    return 0;
}