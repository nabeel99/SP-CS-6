#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <iostream>

int main(){
    int a = open("/home/wuntap/Desktop/SP-CS-6/lseek10.txt",O_RDWR|O_CREAT,S_IRWXU);
    char p[15]; 
    //read(a,p,sizeof("nabeel naveed"));
    lseek(a,0,SEEK_SET);
    int b = lseek(a,5,SEEK_CUR);
    std::cout<<b;
    return 0 ;
}
