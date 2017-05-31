#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

#define NITER 1000000
#define SHM_SIZE sizeof(int)

sem_t locker;
key_t my_key = 0xdeadbeef;

void * Count(void * a)
{
    int i, tmp;
    int shmid = shmget(my_key, SHM_SIZE, 0644 | IPC_CREAT);
    int *cnt = shmat(shmid, (void *)0, 0);
    sem_wait(&locker);
    for(i = 0; i < NITER; i++)
    {
        tmp = *cnt;      /* copy the global cnt locally */
        tmp = tmp+1;    /* increment the local copy */
        *cnt = tmp;      /* store the local value into the global cnt */ 
    }
    sem_post(&locker);
    shmdt(cnt);
}

int main(int argc, char * argv[])
{
    pthread_t tid1, tid2;
    int shmid = shmget(my_key, SHM_SIZE, 0644 | IPC_CREAT);
    int *cnt = shmat(shmid, (void *)0, 0);
    *cnt = 0;
    sem_init(&locker, 0, 1);

    if(pthread_create(&tid1, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }

    if(pthread_create(&tid2, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

    if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if (*cnt < 2 * NITER) 
        printf("\n BOOM! cnt is [%d], should be %d\n", *cnt, 2*NITER);
    else
        printf("\n OK! cnt is [%d]\n", *cnt);
  
    pthread_exit(NULL);
    shmdt(cnt);
}

