#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
char test[100];
char result[100];
write(STDOUT_FILENO,"Enter numbers to add",22);
int n1 =read(STDIN_FILENO,test,100);
char *s = strtok(test," ");
int sum = 0;
while(s!=NULL){
    sum = sum+atoi(s);
    s = strtok(NULL," ");

}
int totalcount =sprintf(result,"Sum is %d",sum);

write(STDOUT_FILENO,result,totalcount);



    return 0;
}