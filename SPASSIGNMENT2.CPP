#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <error.h>
int main(){
char test[100];
char result[100];
int n9;
char p;
int sum  = 0;
int n4 = write(STDOUT_FILENO,"Enter numbers to add \n",sizeof("Enter numbers to add"));
if(n4==-1){perror("error encountered in write");exit(EXIT_FAILURE);}

while (true){
    int n1 = read(STDIN_FILENO,test,100);
if(n1==-1){perror("error encountered in read");exit(EXIT_FAILURE);}
char  errormsg[] = "Invalid input encountered, please give a valid input and try again \n";

char* s = strtok(test," ");
 while (s!=NULL)
 
 {
     int error= sscanf(s,"%c",&p);
    int n5= write(STDOUT_FILENO,s,sizeof(s));
     if(n5==-1){perror("error encountered in write");exit(EXIT_FAILURE);}
    
if(p==';'){
    int totalcount =sprintf(result,"Sum is %d\n",sum);

  int n6 =  write(STDOUT_FILENO,result,totalcount);
    if(n6==-1){perror("error encountered in write");exit(EXIT_FAILURE);}
    sum = 0;
    s = strtok(NULL," ");
    }
    else{
         int error =   sscanf(s,"%d",&n9);
            if(error ==0){write(STDOUT_FILENO,errormsg,sizeof(errormsg));
    exit(EXIT_FAILURE);
    }
            sum = sum+n9;

            if(error ==0){write(STDOUT_FILENO,errormsg,sizeof(errormsg));
            exit(EXIT_FAILURE);}
            s = strtok(NULL," ");
        }
    




}



}




}