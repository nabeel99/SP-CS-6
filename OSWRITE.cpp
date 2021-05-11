#include <unistd.h>
#include <stdio.h>


int main(){
    char s[20];
    //write(STDOUT_FILENO,"Hello World ",12);
    read(STDIN_FILENO,s,20);
    //write(STDOUT_FILENO,s,b);
    printf("%s",s);

    return 0;
}


