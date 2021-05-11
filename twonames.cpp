#include <unistd.h>
#include <stdio.h>
int main(){
char name1[20];
char name2[20];
char name3[20];
int n1 = read(STDIN_FILENO,name1,20);
int n2 = read(STDIN_FILENO,name2,20);
write(STDOUT_FILENO,name1,n1-1  );
write(STDOUT_FILENO,name2,n2);



return 0;

}