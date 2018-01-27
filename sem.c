#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

int main(int argc, char **argv)
{
        sem_t *sem;
        int val;

        sem = sem_open("/Austin", O_CREAT, S_IRWXU, 2);
        if(sem == SEM_FAILED){
                perror("sem_open fail");
                exit(0);
        }

        sem_getvalue(sem, &val);
        printf("sem value:%d\n", val);
        sem_wait(sem);

        return 0;

}
