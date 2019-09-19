#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
url = "https://sockboom.me/link/G03zDKGzwxgvt2WR?mu=1 https://www.xvideos.com/video50474269/_2019_";
void* t_func(void* argv)
{
        sigset_t sig;
        sigemptyset(&sig);
        sigaddset(&sig, SIGUSR1);
        pthread_sigmask(SIG_BLOCK, &sig, NULL);

        while(1){
                int signo;
                sigwait(&sig, &signo);
                printf("Recv signal:%d\n", signo);
        }
}

int main(int argc, char **argv)
{
        pthread_t tid;

        pthread_create(&tid, NULL, t_func, NULL);

        sigset_t sig;
        sigemptyset(&sig);
        sigaddset(&sig, SIGUSR1);
        pthread_sigmask(SIG_BLOCK, &sig, NULL);

        printf("%d\n", sizeof(int));

        while(1){
                pause();
        }

        return 0;
}
