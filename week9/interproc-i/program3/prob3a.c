#include <stdio.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

key_t key = 0xdeadbeef;
sem_t locker;

void counter(char *dirname){
    int shmid = shmget(key, sizeof(int), 0644 | IPC_CREAT);
    int *count_files = shmat(shmid, NULL, 0);
    DIR *dir;
    struct dirent *entry;
    if(!(dir = opendir(dirname))) return;
    if(!(entry = readdir(dir))) return;
    do{
        if(entry->d_type == DT_DIR){
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
            char path[1024];
            int len = snprintf(path, sizeof(path) - 1, "%s/%s", dirname, entry->d_name);
            path[len] = 0;
            pid_t pid = fork();
            if(pid == 0){
                counter(path);
                exit(0);
            }
            else{
                int status;
                waitpid(pid, &status, 0);
            }
        }else{
            sem_wait(&locker);
            ++*count_files;
            sem_post(&locker);
        }
    }while(entry = readdir(dir));
    closedir(dir);
    shmdt(count_files);
}

void main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr, "usage: ./prob3a DIRECTORY");
        exit(-1);
    }
    int shmid = shmget(key, sizeof(int), 0644 | IPC_CREAT);
    int *count_files = shmat(shmid, NULL, 0);
    *count_files = 0;
    sem_init(&locker, 0, 1);
    counter(argv[1]);
    printf("%d files count!\n", *count_files);
    shmdt(count_files);
}
