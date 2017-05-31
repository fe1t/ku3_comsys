#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_THREAD 4
#define CHUNK_SIZE 1000
#define FILENAME "./test.nt"

char STRING[] = "<http://www.w3.org/2001/XMLSchema#string>";
char SPLIT_CHAR[] = {' ', '\n', '<'};
int STRING_LENGTH = 41;

FILE *fp;
int sharedByteRead = 0;
int sharedTotalCount = 0;

pthread_mutex_t lock;

void *countByte(void *param){
    char *buf = param;

    int TARGET_SIZE = strlen(buf);
    // printf("Buff: %s\n",buf);
    // printf("TotalSize: %d\n", TARGET_SIZE);
    int DIFF_LENGTH = TARGET_SIZE - STRING_LENGTH;
    for (int i = 0 ; i <= DIFF_LENGTH ; i++){
       if (strncmp(&buf[i], STRING, STRING_LENGTH) == 0){
            pthread_mutex_lock(&lock);
            sharedTotalCount++;
            pthread_mutex_unlock(&lock);
       }
    }
    return NULL;
}

void countKUY(){
    FILE *fp = fopen(FILENAME, "rb");
    char buf[100000] = { 0 };
    fscanf(fp, "%s", buf);
    int TARGET_SIZE = strlen(buf);
    int DIFF_LENGTH = TARGET_SIZE - STRING_LENGTH;
    for (int i = 0 ; i < DIFF_LENGTH ; i++){
       if (strncmp(&buf[i], STRING, STRING_LENGTH) == 0){
            sharedTotalCount += 1;
       }
    }
}

int main(){
    pthread_t thread[NUM_THREAD];

    if (pthread_mutex_init(&lock, NULL) != 0){
	fprintf(stderr, "\n mutex initialization failed\n");
	return 1;
    }

    fp = fopen(FILENAME, "rb");
    char buf[CHUNK_SIZE + 1];
    size_t nread;
    int i;
    int err;
    memset(buf, 0, sizeof(buf));

    if(fp){
        i = 0;
        while( (nread = fread(buf, sizeof(char), CHUNK_SIZE, fp)) > 0){
            buf[nread] = 0;
	    if(!feof(fp)) {
    		while(!strchr(SPLIT_CHAR, fgetc(fp))) {
		    buf[--nread] = '\0';
		    fseek(fp, -2, SEEK_CUR);
    		}
    		fseek(fp,-1,SEEK_CUR);
	    }
            err = pthread_create(&(thread[i]), NULL, &countByte, (void *) buf);
            //printf("nread: %d\n", nread);
            if (err){
                fprintf(stderr, "\n cannot create thread[%d]: %s", i, strerror(err));
                return 1;
            }
            pthread_join(thread[i], NULL);
            //printf("%d\n", sharedTotalCount);
            i = (i + 1) % NUM_THREAD;
        }
        if(ferror(fp)){
            fprintf(stderr, "\n error reading file\n");
            return 1;
        }
    }
    fclose(fp);
    pthread_mutex_destroy(&lock);

    printf("Total count: %d", sharedTotalCount);

    return 0;
}
