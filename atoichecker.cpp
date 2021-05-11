#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <error.h>
int main(){
    char buff[] = "10   20 ";
    int n;
    
buff[7] = "/0";
    char *s = strtok(buff," ");
    int n1=0;
    int sum;
while(s!=NULL){
printf("s is :%s\n", s);

sscanf(s,"%d",&n1);
printf("n1 is :%d\n", n1);
sum = sum+n1;
 s = strtok(NULL," ");
}
 printf("%d\n",sum);
 printf("size of buff is :%u\n",sizeof(buff));
 printf("character at 8 is : %c\n",buff[5]);




    return 0;
}