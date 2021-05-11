#include <sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include <fcntl.h> 

int main(){
int f1 = open("/home/wuntap/Desktop/SP-CS-6/test1999.txt",O_WRONLY|O_CREAT|O_APPEND,S_IRWXU);

write(f1,"123456",6);
int f2 = open("/home/wuntap/Desktop/SP-CS-6/test1999.txt",O_TRUNC|O_WRONLY);
write(f2,"A",1);
write(f1,"910",3);
write(f1,"000",3);

    return 0;
}