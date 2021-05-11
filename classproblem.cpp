#include <sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include <fcntl.h> 

int main(){
int f1 = open("/home/wuntap/Desktop/SP-CS-6/test.txt",O_WRONLY|O_CREAT,S_IRWXU);
int pid = fork();
write(f1,"ABC",3);
int f2 = open("/home/wuntap/Desktop/SP-CS-6/test.txt",O_APPEND|O_WRONLY);
write(f2,"XYZ",3);


if(pid ==0){

int f3 = open("/home/wuntap/Desktop/SP-CS-6/test.txt",O_WRONLY);


    write(f3,"123",3);
}
else if (pid>0){
int f3 = open("/home/wuntap/Desktop/SP-CS-6/test.txt",O_WRONLY);

    write(f3,"LMN",3);

}
    return 0;
}