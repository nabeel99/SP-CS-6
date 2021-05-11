#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

char buffer1[20];
char buffer3[20];
int a,b;
read(STDIN_FILENO,buffer1,20);
sscanf(buffer1,"%d %d",&a,&b);
int c = a+b;


int totalcount =sprintf(buffer3,"%d + %d is %d",a,b,c);



write(STDOUT_FILENO,buffer3,totalcount);
return 0;

}