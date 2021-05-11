#include <sys/types.h>
#include<unistd.h>
#include<stdio.h>
int main(){
int first = fork();
write(STDOUT_FILENO,"Hi1\n",4);
if (first>0){
    write(STDOUT_FILENO,"Hi2\n",4);

    write(STDOUT_FILENO,"parent\n",7);}
    else if(first==0)
    {write(STDOUT_FILENO,"Hi3\n",4);write(STDOUT_FILENO,"child\n",6);}
    else{
write(STDOUT_FILENO,"error\n",6);


    }
write(STDOUT_FILENO,"Hi4\n",4);
getchar();
write(STDOUT_FILENO,"Hi5\n",4);
    return 0;
}