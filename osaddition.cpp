#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

char buffer1[20];
char buffer2[20];
char buffer3[20];
int a,b;
int in = read(STDIN_FILENO,buffer1,20);
sscanf(buffer1,"%d",&a);
int in2 =read(STDIN_FILENO,buffer2,20);
sscanf(buffer2,"%d",&b);
int c = a+b;

int totalcount =sprintf(buffer3,"%d",c);


write(STDOUT_FILENO,buffer3,totalcount);
return 0;

}