#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <ostream>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
int main(){

 
            char numbers[100];                  // This code does meet the basic requirements of the assignment which are take in numbers in a single line and give their sum
            int Sum=0;    
            char string[100];
            char sprintarr[15];
            char popo;

            while(true){

            int no = read(STDIN_FILENO,numbers,100);

            if(no == -1){ perror("You entered a wrong variable"); }         // tried to do error handling here but havent had much success

            char *token = strtok(numbers," ");               

            while (token !=NULL){
            
            sscanf(token,"%c",&popo);
            //if(atoi(token)== 0 ){ perror("do not put in alphabets");}        //this one works but not perfect
            if(popo != ';'){
            
            //cout<<token<<endl;
            Sum = atoi(token) + Sum;

            }

            else if(popo == ';'){
            
            write(STDOUT_FILENO,"The sum is: ",12);
            int x = sprintf(sprintarr,"%d",Sum);
            write(STDOUT_FILENO,sprintarr,x);
            write(STDOUT_FILENO,"\n",2);
            Sum=0;

            }

            token = strtok(NULL," ");      
            }        
            
            
            }

           return 0;
  

}