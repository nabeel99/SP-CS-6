 #include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
static void  sigint_handler(int signo){


    write(STDOUT_FILENO,"Caught SIGINT \n",strlen("Caught SIGINT \n"));
    exit (EXIT_SUCCESS);
}

int main (void){

    if (signal(SIGINT,sigint_handler)==SIG_ERR){

        fprintf (stderr, "Cannot handle SIGINT!\n");
        exit (EXIT_FAILURE);
    }
    for (;;)
    pause ();
    return 0;
}


    


