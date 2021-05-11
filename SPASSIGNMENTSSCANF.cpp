#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <error.h>
int main(){
char test[100];
char result[100];
int n4 = write(STDOUT_FILENO,"Enter numbers to add \n",sizeof("Enter numbers to add"));
if(n4==-1){perror("error encountered in write");exit(EXIT_FAILURE);}
int n1 =read(STDIN_FILENO,test,100);
test[n1-1] = NULL;
if(n1==-1){perror("error encountered in read");exit(EXIT_FAILURE);}
char *s = strtok(test," ");
char  errormsg[] = "Invalid input encountered, please give a valid input and try again \n";
int sum = 0;
while(s!=NULL){
    int n9;
   int error = sscanf(s,"%d",&n9);

    if(error ==0){write(STDOUT_FILENO,errormsg,sizeof(errormsg));
    exit(EXIT_FAILURE);
    }
    
    sum = sum+n9;
    s = strtok(NULL," ");

}
int totalcount =sprintf(result,"Sum is %d\n",sum);

        write(STDOUT_FILENO,result,totalcount);



    return 0;
}

