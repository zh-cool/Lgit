#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static pthread_key_t key;
static pthread_once_t key_once = PTHREAD_ONCE_INIT;

static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void make_key(void)
{
        pthread_key_create(&key, NULL);
}

void* t_func(void *argc)
{
        void *ptr = NULL;
        pthread_once(&key_once, make_key);
        if((ptr=pthread_getspecific(key)) == NULL){
                ptr = malloc(sizeof(int));
                *(int*)ptr = *(int*)argc;
                pthread_setspecific(key, ptr);
        }

        sigset_t sig;
        sigemptyset(&sig);
        if(*(int*)argc == 1){
                sigaddset(&sig, SIGUSR2);
        }else{
                sigaddset(&sig, SIGUSR1);
        }
        pthread_sigmask(SIG_BLOCK, &sig, NULL);

        while(1){
                pthread_mutex_lock(&mutex);
                pthread_cond_wait(&cond, &mutex);
                pthread_mutex_unlock(&mutex);
                printf("Recv cond %lu\n", pthread_self());
                //ptr = pthread_getspecific(key);
                //printf("argc:%d pthread id:%lu\n", *(int*)ptr, pthread_self());
        }
}

#define sincd (*(int*)pthread_getspecific(key))

void sig_usr(int sig)
{
        void *ptr = NULL;

        ptr = pthread_getspecific(key);
        printf("argc:%d pthread id:%lu\n", *(int*)ptr, pthread_self());
        pthread_cond_signal(&cond);
}

int main(int argc, char **argv)
{
        pthread_t tid1, tid2;
        int arg1=1, arg2=2;

        pthread_create(&tid1, NULL, t_func, &arg1);
        pthread_create(&tid2, NULL, t_func, &arg2);

        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        //pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);

        sigset_t sig;
        sigemptyset(&sig);
        sigaddset(&sig, SIGUSR1);
        sigaddset(&sig, SIGUSR2);
        pthread_sigmask(SIG_BLOCK, &sig, NULL);

        signal(SIGUSR1, sig_usr);
        signal(SIGUSR2, sig_usr);

        while(1)
                pause();
        return 0;
}
