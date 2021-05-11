#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <error.h>
#include <iostream>
#include <errno.h>
using namespace std;

int main(){


int first = fork();
    int fwrite = open("/home/wuntap/Desktop/SP-CS-6/SAMADqsqq.txt",O_WRONLY);

cout << fwrite << " Check " << endl;
if(first>0)
{}
else if(first==0){


 int d =   write(fwrite,"Hello testing2904",17);
 perror("Error is ");
 if(d==-1){write(STDOUT_FILENO,"error dera",10);}
}
    return 0;
}