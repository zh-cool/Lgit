#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void sig_chld(int signo)
{
        printf("child exit\n");
}

int main(int argc, char **argv)
{
        FILE *fp;
        signal(SIGCHLD, sig_chld);
        //fp = popen("ls", "r");
        //fclose(fp);

        system("ls");

        while(1){
                pause();
        }

        return 0;
}
