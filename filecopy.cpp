#include <stdio.h>
#include <unistd.h>
#include<errno.h>
#include<error.h>
#include <sys/types.h> 
#include <fcntl.h> 
#include <time.h>

int copyfile(char filename[],int byt){
    time_t begin,end;
    int newfile = open("/home/wuntap/Desktop/SP-CS-6/random-test-file-assignment4.txt",O_WRONLY|O_CREAT|O_SYNC,S_IRWXU);
            if (newfile==-1){write(STDOUT_FILENO,"Error in newfilefile",20);}
    int copyfile = open(filename,O_RDONLY);
        if (copyfile==-1){write(STDOUT_FILENO,"Error in copy file",20);}
    char readfromfile[byt];
    int fread = read(copyfile,readfromfile,byt);
        if (fread==-1){write(STDOUT_FILENO,"Error cannot read",5);}
    time(&begin);
    while (fread!=0){
        
        int wrerror = write(newfile,readfromfile,fread);
        fread = read(copyfile,readfromfile,byt);

}
time(&end);    
time_t elapsed = end-begin;
    char d[1000];
    int byteswritten =   sprintf(d,"time taken : %li seconds",elapsed);
    write(STDOUT_FILENO,d,byteswritten);
    close(newfile);
    close(copyfile);
    return 0;}
int main (){
    char name[] = "/home/wuntap/Desktop/SP-CS-6/SP-ASSIGNMENT-TEST.txt";
    int err2 = copyfile(name,1000);
    if(err2==-1){write(STDOUT_FILENO,"function failed",15);}
    return 0;
}